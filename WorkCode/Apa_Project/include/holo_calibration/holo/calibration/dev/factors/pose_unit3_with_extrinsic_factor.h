/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pose_unit3_with_extrinsic_facotr.h
 * @brief This header file defines pose unit3 with extrinsic factor
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2022-01-21
 */

#ifndef HOLO_CALIBRATION_DEV_FACTORS_POSE_UNIT3_WITH_EXTRINSIC_FACTOR_H_
#define HOLO_CALIBRATION_DEV_FACTORS_POSE_UNIT3_WITH_EXTRINSIC_FACTOR_H_

#include <holo/calibration/dev/factors/internal/pose_unit3_with_extrinsic_factor_inl.h>

namespace holo
{
namespace calibration
{
/**
 * @addtogroup calibration
 * @{
 *
 */

using GTPoseUnit3WithExtrinsicFactor = holo::calibration::internal::PoseUnit3WithExtrinsicFactor;

/**
 * @}
 *
 */
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_DEV_FACTORS_POSE_UNIT3_WITH_EXTRINSIC_FACTOR_H_
