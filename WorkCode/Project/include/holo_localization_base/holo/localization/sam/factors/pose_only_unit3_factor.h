/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pose_only_unit3_facotr.h
 * @brief This header file defines pose only unit3 factor
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2021-12-06
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_POSE_ONLY_UNIT3_FACTOR_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_POSE_ONLY_UNIT3_FACTOR_H_

#include <holo/localization/sam/factors/internal/pose_only_unit3_factor_inl.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup sam
 * @{
 *
 */

using GTPoseOnlyUnit3Factor = holo::localization::internal::PoseOnlyUnit3Factor;

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_POSE_ONLY_UNIT3_FACTOR_H_
