/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fisheye_intrinsic_factor.h
 * @brief  This file defines fisheye intrinsic factor class
 * @author bin.chen @ chenbin@holomatic.com
 * @author jiashuo.cui @ cuijiashuo@holomatic.com
 * @date   2020-09-10
 */

#ifndef HOLO_CALIBRATION_DEV_FACTORS_FISHEYE_INTRINSIC_FACTOR_H_
#define HOLO_CALIBRATION_DEV_FACTORS_FISHEYE_INTRINSIC_FACTOR_H_

#include <holo/calibration/dev/factors/internal/fisheye_intrinsic_factor_inl.h>

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

using GTFisheyeIntrinsicFactor = holo::calibration::internal::FisheyeIntrinsicFactor;

/**
 * @}
 */
}  // namespace camera
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_DEV_FACTORS_FISHEYE_INTRINSIC_FACTOR_H_
