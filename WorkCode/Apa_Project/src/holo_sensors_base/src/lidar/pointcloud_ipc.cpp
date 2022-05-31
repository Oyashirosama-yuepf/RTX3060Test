/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pointcloud_ipc.cpp.
 * @brief PointCloud_IPC.
 * @author wujie(wujie@holomatic.com).
 * @date 2021-10-09.
 */

#include <holo/common/timestamp.h>
#include <holo/log/hololog.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>

namespace holo
{
namespace sensors
{
namespace lidar
{
template <typename PointCloudType, size_t PointCount>
PointCloudIpc<PointCloudType, PointCount>::PointCloudIpc(SensorId sensor_id)
  : sensor_id_(sensor_id)
  , fd_(-1)
  , shm_sem_(nullptr)
  , shm_data_(nullptr)
  , shsem_name_(std::to_string(static_cast<uint32_t>(sensor_id_)))
  , shmem_name_("lid." + std::to_string(static_cast<uint32_t>(sensor_id_)))
{
    /* shmem_size_ : SHM_HEADER_SIZE + max_pointcloud_capacity */
    PointCloudType pcd;
    pcd.resize(PointCount);
    shmem_size_ = SHM_HEADER_SIZE + pcd.GetSerializedSize();

    shm_sem_ = sem_open(shsem_name_.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, 1);
    if (!shm_sem_)
    {
        std::string error = "failed to open semaphore of share memory";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }

    /* create a new memory object */
    OpenShmFd();

    /* create and map the shm */
    shm_data_ = mmap(0, shmem_size_, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
    if (shm_data_ == MAP_FAILED)
    {
        std::string error = "failed to map share memory";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    /* opt shm */
    /* wait semaphore */
    if (sem_wait(shm_sem_) == -1)
    {
        std::string error = "failed to wait shm semaphore";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    /* init shared memory data */
    const uint32_t init_data[3] = {static_cast<uint32_t>(sensor_id),
                                   static_cast<uint32_t>(shmem_size_ - SHM_HEADER_SIZE), static_cast<uint32_t>(0)};
    (void)std::memcpy(shm_data_, init_data, sizeof(init_data));
    static_cast<uint32_t*>(shm_data_)[3] = 1; /* [3]: refs */

    /* release semaphore */
    (void)sem_post(shm_sem_);
    LOG(INFO) << "pointcloud_ipc server initialized: " << shmem_name_;
}

template <typename PointCloudType, size_t PointCount>
PointCloudIpc<PointCloudType, PointCount>::~PointCloudIpc() noexcept
{
    (void)sem_wait(shm_sem_);
    uint32_t refs = --static_cast<uint32_t*>(shm_data_)[3];
    (void)sem_post(shm_sem_);
    if (shm_data_ != MAP_FAILED)
    {
        (void)munmap(shm_data_, shmem_size_);
        if (fd_ != -1)
        {
            (void)close(fd_);
        }
        if (refs == 0)
        {
            (void)shm_unlink(shmem_name_.c_str());
        }
    }
    if (shm_sem_)
    {
        (void)sem_close(shm_sem_);
        if (refs == 0)
        {
            (void)sem_unlink(shsem_name_.c_str());
        }
    }
}

template <typename PointCloudType, size_t PointCount>
void PointCloudIpc<PointCloudType, PointCount>::OpenShmFd()
{
    fd_ = shm_open(shmem_name_.c_str(), O_CREAT | O_RDWR, 0666);
    if (fd_ == -1)
    {
        std::string error = "failed to open share memory";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    struct stat shm_stat1;
    if (0 != fstat(fd_, &shm_stat1))
    {
        std::string error = "failed to get share memory status";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    /* set the fd size */
    if (shm_stat1.st_size == 0)
    {
        if (ftruncate(fd_, shmem_size_))
        {
            std::string error = "failed to set share memory size";
            LOG(INFO) << error << ": " << strerror(errno);
            throw std::runtime_error(error);
        }
    }
    /* check size */
    struct stat shm_stat2;
    if (0 != fstat(fd_, &shm_stat2))
    {
        std::string error = "failed to get share memory status";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    if (shm_stat2.st_size < shmem_size_)
    {
        std::string error = "failed to validate shm size";
        LOG(INFO) << error << ": " << shm_stat2.st_size << ", assert value: " << shmem_size_;
        throw std::runtime_error(error);
    }
}

template <typename PointCloudType, size_t PointCount>
bool_t PointCloudIpc<PointCloudType, PointCount>::GetPointCloudData(PointCloudType& pointcloud)
{
    if (sem_wait(shm_sem_) == -1)
    {
        LOG(ERROR) << "point cloud ipc mutex wait failed: " << strerror(errno);
        return false;
    }
    /* read point cloud for shm */
    DeserializerType deserializer((uint8_t*)shm_data_ + SHM_HEADER_SIZE,
                                  static_cast<uint32_t*>(shm_data_)[2]); /* [2]: size */
    pointcloud.Deserialize(deserializer);

    (void)sem_post(shm_sem_);
    return true;
}

template <typename PointCloudType, size_t PointCount>
bool_t PointCloudIpc<PointCloudType, PointCount>::SetPointCloudData(const PointCloudType& pointcloud)
{
    /* point cloud data size */
    uint32_t pointcloud_size = pointcloud.GetSerializedSize();

    /* pointcloud too big */
    if (pointcloud_size > static_cast<uint32_t*>(shm_data_)[1])
    {
        /* don't opt */
        LOG(ERROR) << "pointcloud too big!";
        return false;
    }

    if (sem_wait(shm_sem_) == -1)
    {
        LOG(ERROR) << "point cloud ipc mutex wait failed: " << strerror(errno);
        return false;
    }
    /* point cloud data */
    SerializerType serializer((uint8_t*)shm_data_ + SHM_HEADER_SIZE,
                              static_cast<uint32_t*>(shm_data_)[1]); /* [1]: capacity */
    pointcloud.Serialize(serializer);
    /* point cloud data size */
    static_cast<uint32_t*>(shm_data_)[2] = pointcloud_size;

    (void)sem_post(shm_sem_);
    return true;
}

template class PointCloudIpc<holo::point_cloud::PointCloudT<
    holo::point_cloud::PointXYZIRSt<float32_t>, std::numeric_limits<size_t>::max(),
    sizeof(holo::point_cloud::PointXYZIRSt<float32_t>), point_cloud::UnorganizedLayoutTag>>;

}  // namespace lidar
}  // namespace sensors
}  // namespace holo
