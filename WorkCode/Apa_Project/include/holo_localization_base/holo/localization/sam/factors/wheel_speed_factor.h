/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file wheel_speed_factor.h
 * @brief this file deines wheel speed factor class
 * @author Binbin.Wang wangbinbin@holomatic.com
 * @date 2020-08-04
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_WHEEL_SPEED_FACTOR_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_WHEEL_SPEED_FACTOR_H_

#include <holo/localization/sam/factors/internal/wheel_speed_factor_inl.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup sam
 * @{
 *
 */

using GTWheelSpeedFactor = holo::localization::internal::WheelSpeedFactor;

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo
#endif  // HOLO_LOCALIZATION_SAM_FACTORS_WHEEL_SPEED_FACTOR_H_
