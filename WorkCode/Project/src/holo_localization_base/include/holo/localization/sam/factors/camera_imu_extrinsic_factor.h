/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_imu_extrinsic_factor.h
 * @brief this file defines camera and imu extrinsic factor which can be used to calibrate
 *        roll, pitch, yaw and translation of camera in imu frame individually
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2020-04-20"
 */
#ifndef HOLO_LOCALIZATION_SAM_FACTORS_CAMERA_IMU_EXTRINSIC_FACTOR_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_CAMERA_IMU_EXTRINSIC_FACTOR_H_

#include <holo/localization/sam/factors/internal/camera_imu_extrinsic_factor_inl.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup sam
 * @{
 *
 */

using GTCameraImuExtrinsicFactor = holo::localization::internal::CameraImuExtrinsicFactor;

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_CAMERA_IMU_EXTRINSIC_FACTOR_H_
