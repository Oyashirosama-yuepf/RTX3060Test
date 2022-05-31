/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file aceinna.h
 * @brief This header file define the function of aceinna driver
 * @author guoguangchao@holomatic.com
 * @date 2020-08-21
 */

#ifndef _HOLO_SENSORS_IMU_ACEINNA_ACEINNA_BASE_H
#define _HOLO_SENSORS_IMU_ACEINNA_ACEINNA_BASE_H

#include <holo/sensors/imu/imu.h>

namespace holo
{
namespace sensors
{
namespace aceinna
{
/* aceinna imu driver template */
template <typename T>
class AceinnaDriverT
{
public:
    AceinnaDriverT() = 0;
};

}  // namespace aceinna
}  // namespace sensors
}  // namespace holo

#endif
