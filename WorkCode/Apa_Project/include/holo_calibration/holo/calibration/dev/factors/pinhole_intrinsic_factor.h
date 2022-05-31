/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pinhole_intrinsic_factor.h
 * @brief  This file defines fisheye intrinsic factor class
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date   2021-10-14
 */

#ifndef HOLO_CALIBRATION_DEV_FACTORS_PINHOLE_INTRINSIC_FACTOR_H_
#define HOLO_CALIBRATION_DEV_FACTORS_PINHOLE_INTRINSIC_FACTOR_H_

#include <holo/calibration/dev/factors/internal/pinhole_intrinsic_factor_inl.h>

namespace holo
{
namespace calibration
{
namespace camera
{
/**
 *  @addtogroup camera
 *  @{
 *
 */

using GTPinholeIntrinsicFactor = holo::calibration::internal::PinholeIntrinsicFactor;

/**
 * @}
 */
}  // namespace camera
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_DEV_FACTORS_PINHOLE_INTRINSIC_FACTOR_H_
