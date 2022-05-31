/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file plane_factor.h
 * @brief This header file defines point2plane factor
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-03-31
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_POINT2PLANE_FACTOR_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_POINT2PLANE_FACTOR_H_

#include <holo/localization/sam/factors/internal/point2plane_factor_inl.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup sam
 * @{
 *
 */

using GTPoint2PlaneFactor = holo::localization::internal::Point2PlaneFactor;

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_POINT2PLANE_FACTOR_H_
