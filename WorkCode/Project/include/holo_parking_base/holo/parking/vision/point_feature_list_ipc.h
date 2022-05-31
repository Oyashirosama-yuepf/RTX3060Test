/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_feature_list_ipc.h.
 * @brief Point feature list IPC.
 * @author guo peikai(guopeikai@holomatic.com).
 * @date 2021-06-28.
 */

#ifndef _HOLO_PARKING_VISION_POINT_FEATURE_LIST_IPC_H
#define _HOLO_PARKING_VISION_POINT_FEATURE_LIST_IPC_H

#include <iostream>
#include <string>
#include <vector>

#include <holo/os/predefine.h>
#if defined(HOLO_PLATFORM_LINUX)
#pragma message("compile platform is linux")
#include <fcntl.h>
#include <semaphore.h>  // semaphore
#include <sys/mman.h>   // shm_open, shm_ctl, mmap, shum_unlink
#include <sys/stat.h>   // fstat
#include <unistd.h>     // fruncate
#elif defined(HOLO_PLATFORM_QNX)
#pragma message("compile platform is qnx")
#include <fcntl.h>
#include <semaphore.h>  // semaphore
#include <sys/mman.h>   // shm_open, shm_ctl, mmap, shum_unlink
#include <unistd.h>     // fruncate( get file descriptor for file that you want to truncate and set memorey object size)
#else
#error "HOLO_BUILD_PLATFORM is wrong, please check it."
#endif

#include <holo/core/types.h>
#include "holo/parking/vision/point_feature_list.h"

namespace holo
{
namespace parking
{
namespace vision
{
class PointFeatureListIpc
{
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  sensor_id  The sensor identifier
     */
    PointFeatureListIpc(holo::common::SensorId sensor_id);

    /**
     * @brief      destructor
     */
    ~PointFeatureListIpc();

    /**
     * @brief      Gets the sensor_id.
     *
     * @return     The sensor_id.
     */
    holo::common::SensorId GetSensorId() const noexcept
    {
        return sensor_id_;
    }

    /**
     * @brief      this function is used to get point feature list from shared
     * memory
     *
     * @param[out] point_feature_list  the point feature list got from shared
     * memory
     *
     * @return     Result: true if successfully, false otherwise
     */
    bool_t GetPointFeatureListData(PointFeaturePtrListf& point_feature_list);

    /**
     * @brief      this function is used set  point feature list to shared memory
     * usually the server would use this function
     *
     * @param[out] point_feature_list  the image set to shared memory
     *
     * @return     true if the point feature list is successfully set otherwise
     * return false
     */
    bool_t SetPointFeatureListData(const PointFeaturePtrListf& point_feature_list);

private:
    static constexpr uint32_t OFFSET = 4u;

private:
    holo::common::SensorId sensor_id_;
    uint32_t               shmem_size_;
    int32_t                fd_;
    sem_t*                 shm_sem_;
    void*                  shm_data_;
    std::string            shsem_name_;
    std::string            shmem_name_;
};

}  // namespace vision
}  // namespace parking
}  // namespace holo

#endif  // _HOLO_PARKING_VISION_POINT_FEATURE_LIST_IPC_H