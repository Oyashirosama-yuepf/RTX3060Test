/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_ipc.cpp.
 * @brief Image IPC.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-04.
 */

#include <glog/logging.h>
#include <holo/common/timestamp.h>
#include "holo/parking/vision/point_feature_list_ipc.h"

namespace holo
{
namespace parking
{
namespace vision
{
PointFeatureListIpc::PointFeatureListIpc(holo::common::SensorId sensor_id)
  : sensor_id_(sensor_id)
  , shmem_size_(300000)
  , fd_(-1)
  , shm_sem_(nullptr)
  , shm_data_(nullptr)
  , shsem_name_(std::to_string(static_cast<uint32_t>(sensor_id_)))
  , shmem_name_("mlc." + std::to_string(static_cast<uint32_t>(sensor_id_)))
{
    /* mutex for safety */
    shm_sem_ = sem_open(shsem_name_.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, 1);
    if (!shm_sem_)
    {
        std::string error = "failed to open semaphore of share memory";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }

    /* create a new memory object */
    fd_ = shm_open(shmem_name_.c_str(), O_CREAT | O_RDWR, 0666);
    if (fd_ == -1)
    {
        std::string error = "failed to open share memory";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }

    /* set the memory object's size */
    struct stat shm_stat1;
    if (0 != fstat(fd_, &shm_stat1))
    {
        std::string error = "failed to get share memory status";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
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
    /* map the memory object */
    shm_data_ = mmap(0, shmem_size_, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);

    if (shm_data_ == MAP_FAILED)
    {
        std::string error = "failed to map share memory";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    /* x */
    if (sem_wait(shm_sem_) == -1)
    {
        std::string error = "failed to wait shm semaphore";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }

    static_cast<uint32_t*>(shm_data_)[0] += 1;
    sem_post(shm_sem_);
    LOG(INFO) << "point feature list ipc initialized: " << shmem_name_;
}

PointFeatureListIpc::~PointFeatureListIpc()
{
    sem_wait(shm_sem_);
    uint32_t refs = --static_cast<uint32_t*>(shm_data_)[0];
    sem_post(shm_sem_);
    if (shm_data_ != MAP_FAILED)
    {
        munmap(shm_data_, shmem_size_);
        if (fd_ != -1)
        {
            close(fd_);
        }
        if (refs == 0)
        {
            shm_unlink(shmem_name_.c_str());
        }
    }
    if (shm_sem_)
    {
        sem_close(shm_sem_);
        if (refs == 0)
        {
            sem_unlink(shsem_name_.c_str());
        }
    }
}

bool_t PointFeatureListIpc::GetPointFeatureListData(PointFeaturePtrListf& point_feature_list)
{
    if (sem_wait(shm_sem_) == -1)
    {
        LOG(ERROR) << "point feature list ipc mutex wait failed: " << strerror(errno);
        return false;
    }

    /* get */
    uint32_t offset = OFFSET;
    uint32_t sec_nsec[2];
    std::memcpy((uint8_t*)sec_nsec, (uint8_t*)shm_data_ + offset, 2 * sizeof(uint32_t));
    point_feature_list.SetTimestamp(holo::common::Timestamp(sec_nsec[0], sec_nsec[1]));
    offset += 2 * sizeof(uint32_t);

    uint32_t sensor_id;
    std::memcpy(&sensor_id, (uint8_t*)shm_data_ + offset, sizeof(uint32_t));
    point_feature_list.SetSensorId(sensor_id);
    offset += sizeof(uint32_t);

    uint32_t list_size;
    std::memcpy(&list_size, (uint8_t*)shm_data_ + offset, sizeof(uint32_t));
    point_feature_list.SetSize(list_size);
    offset += sizeof(uint32_t);

    uint16_t des_size;
    std::memcpy(&des_size, (uint8_t*)shm_data_ + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    PointFeaturePtrListf::PointFeaturePtrListType point_features;

    // point_features.resize(list_size);
    for (size_t i = 0; i < list_size; i++)
    {
        PointFeaturef::Point2Type point_2;
        std::memcpy(&point_2, (uint8_t*)shm_data_ + offset, sizeof(point_2));
        offset += sizeof(point_2);

        PointFeaturef::DescriptorType des_vec;
        des_vec.resize(des_size);
        std::memcpy(&des_vec[0], (uint8_t*)shm_data_ + offset, des_size * sizeof(PointFeaturef ::ScalarType));
        offset += des_size * sizeof(PointFeaturef ::ScalarType);
        for (size_t i = 0; i < des_vec.size(); i++)
        {
        }

        PointFeaturef::ScalarType confidence;
        std::memcpy(&confidence, (uint8_t*)shm_data_ + offset, sizeof(confidence));
        offset += sizeof(confidence);

        point_features.push_back(std::make_shared<PointFeaturef>(point_2, des_vec, confidence));
    }

    point_feature_list.SetPointFeatureList(point_features);

    sem_post(shm_sem_);
    return true;
}

bool_t PointFeatureListIpc::SetPointFeatureListData(const PointFeaturePtrListf& point_feature_list)
{
    if (sem_wait(shm_sem_) == -1)
    {
        LOG(ERROR) << "point feature list ipc mutex wait failed: " << strerror(errno);
        return false;
    }
    /* set */
    uint32_t                offset = OFFSET;
    int32_t                 sec = 0, nsec = 0;
    holo::common::Timestamp time_stamp = point_feature_list.GetTimestamp();
    sec                                = time_stamp.GetSec();
    nsec                               = time_stamp.GetNsec();
    std::memcpy((uint8_t*)shm_data_ + offset, &sec, sizeof(int32_t));
    offset += sizeof(int32_t);
    std::memcpy((uint8_t*)shm_data_ + offset, &nsec, sizeof(int32_t));
    offset += sizeof(int32_t);

    const uint32_t sensor_id = static_cast<uint32_t>(point_feature_list.GetSensorId());
    std::memcpy((uint8_t*)shm_data_ + offset, &sensor_id, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    const uint32_t list_size = point_feature_list.GetSize();
    std::memcpy((uint8_t*)shm_data_ + offset, &list_size, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    const uint16_t des_size = point_feature_list.GetPointFeatureList()[0]->GetDescriptorDimension();
    std::memcpy((uint8_t*)shm_data_ + offset, &des_size, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    for (size_t i = 0; i < list_size; i++)
    {
        PointFeaturef                 point_feature = *(point_feature_list.GetPointFeatureList().at(i));
        PointFeaturef::Point2Type     point_2       = point_feature.GetPointPosition();
        PointFeaturef::DescriptorType des           = point_feature.GetDescriptor();
        PointFeaturef::ScalarType     confidence    = point_feature.GetConfidence();

        std::memcpy((uint8_t*)shm_data_ + offset, &point_2, sizeof(point_2));
        offset += sizeof(point_2);

        std::memcpy((uint8_t*)shm_data_ + offset, &des[0], des.size() * sizeof(PointFeaturef::ScalarType));
        offset += des.size() * sizeof(PointFeaturef::ScalarType);

        std::memcpy((uint8_t*)shm_data_ + offset, &confidence, sizeof(confidence));
        offset += sizeof(confidence);
    }

    sem_post(shm_sem_);
    return true;
}

}  // namespace vision
}  // namespace parking
}  // namespace holo