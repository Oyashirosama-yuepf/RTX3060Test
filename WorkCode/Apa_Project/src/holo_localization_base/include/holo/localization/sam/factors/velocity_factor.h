/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file velocity_factor.h
 * @brief this file define velocity factor used to constraint a pose and velocity
 * @author Yetong. Zhang, zhangyetong@holomatic.com
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-06-02"
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_VELOCITY_FACTOR_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_VELOCITY_FACTOR_H_

#include <holo/localization/sam/factors/internal/velocity_factor_inl.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup sam
 * @{
 *
 */

using GTVelocityFactor = holo::localization::internal::VelocityFactor;

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_VELOCITY_FACTOR_H_
