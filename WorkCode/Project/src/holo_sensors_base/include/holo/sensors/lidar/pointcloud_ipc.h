/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pointcloud_ipc.h.
 * @brief Point Cloud IPC.
 * @author wujie(wujie@holomatic.com).
 * @date 2021-10-08.
 */
#ifndef _HOLO_SENSORS_POINT_CLOUD_IPC_H
#define _HOLO_SENSORS_POINT_CLOUD_IPC_H

#include <iostream>
#include <string>
#include <vector>

#include <holo/os/predefine.h>
#if defined(HOLO_PLATFORM_LINUX)
#include <fcntl.h>
#include <semaphore.h>  // semaphore
#include <sys/mman.h>   // shm_open, shm_ctl, mmap, shum_unlink
#include <sys/stat.h>   // fstat
#include <unistd.h>     // fruncate
#elif defined(HOLO_PLATFORM_QNX)
#include <fcntl.h>
#include <semaphore.h>  // semaphore
#include <sys/mman.h>   // shm_open, shm_ctl, mmap, shum_unlink
#include <unistd.h>     // fruncate( get file descriptor for file that you want to truncate and set memorey object size)
#else
#error "HOLO_BUILD_PLATFORM is wrong, please check it."
#endif

/* point cloud */
#include <holo/core/types.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>

namespace holo
{
namespace sensors
{
namespace lidar
{
using holo::common::SensorId;

static constexpr size_t MAXPOINTS = 700000;

template <typename PointCloudType, size_t PointCount = MAXPOINTS>
class PointCloudIpc
{
public:
    using SerializerType   = holo::serialization::Serializer<false, 4>;
    using DeserializerType = holo::serialization::Deserializer<false, 4>;

    PointCloudIpc(SensorId sensor_id);

    ~PointCloudIpc() noexcept;

    SensorId GetSensorId() const noexcept
    {
        return sensor_id_;
    }

    uint32_t GetCapacity() const noexcept
    {
        return static_cast<uint32_t*>(shm_data_)[1];
    }

    uint32_t GetDataSize() const noexcept
    {
        return static_cast<uint32_t*>(shm_data_)[2];
    }

    uint32_t GetShmemSize() const noexcept
    {
        return shmem_size_;
    }

    bool_t GetPointCloudData(PointCloudType& pointcloud);

    bool_t SetPointCloudData(const PointCloudType& pointcloud);

private:
    void OpenShmFd();

private:
    /*
        |0-------|4-------|8-------|12--|16--|
        |SensorId|Capacity|DataSize|Refs|Data|
    */
    static constexpr uint32_t SHM_HEADER_SIZE = 16;
    SensorId                  sensor_id_;
    uint32_t                  shmem_size_;
    int32_t                   fd_;
    sem_t*                    shm_sem_;
    void*                     shm_data_;
    std::string               shsem_name_;
    std::string               shmem_name_;
};

}  // namespace lidar
}  // namespace sensors
}  // namespace holo

#endif  // _HOLO_SENSORS_POINT_CLOUD_IPC_H
