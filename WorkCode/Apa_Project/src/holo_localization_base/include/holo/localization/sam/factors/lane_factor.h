/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_factor.h
 * @brief A class to define lane factor
 * @author Zhang Yelin (zhangyelin@holomatic.com)
 * @date Dec 13, 2019
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_LANE_FACTOR_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_LANE_FACTOR_H_

#include <holo/localization/sam/factors/internal/lane_factor_inl.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup sam
 * @{
 *
 */

using GTLane2Factor = holo::localization::internal::Lane2Factor;

/**
 * @}
 *
 */

}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_LANE_FACTOR_H_
