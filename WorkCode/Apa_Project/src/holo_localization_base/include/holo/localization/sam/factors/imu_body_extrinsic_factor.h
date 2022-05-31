/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu_body_extrinsic_factor.h
 * @brief this file define imu body extrinsic factor which can be used to calibrate
 *        roll, pitch, yaw of body in imu frame
 * @author Binbin.Wang wangbinbin@holomatic.com
 * @date 2020-08-13
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_IMU_BODY_EXTRINSIC_FACTOR_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_IMU_BODY_EXTRINSIC_FACTOR_H_

#include <holo/localization/sam/factors/internal/imu_body_extrinsic_factor_inl.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup sam
 * @{
 *
 */

using GTImuBodyExtrinsicFactor = holo::localization::internal::ImuBodyExtrinsicFactor;

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_IMU_BODY_EXTRINSIC_FACTOR_H_
