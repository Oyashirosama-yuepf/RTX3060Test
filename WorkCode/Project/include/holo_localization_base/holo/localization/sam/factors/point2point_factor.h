/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point2point_factor.h
 * @brief This header file defines point2point factor
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-04-30
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_POINT2POINT_FACTOR_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_POINT2POINT_FACTOR_H_

#include <holo/localization/sam/factors/internal/point2point_factor_inl.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup sam
 * @{
 *
 */

using GTPoint2PointFactor = holo::localization::internal::Point2PointFactor;

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_POINT2POINT_FACTOR_H_
