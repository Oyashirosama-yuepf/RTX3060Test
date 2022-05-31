/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gnss_position_velocity_factor.h
 * @brief This file define GNSS position and velocity factor used to constraint a pose and a velocity value.
 * @author Lei Gehang (leigehang@holomatic.com)
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @date Aug 24, 2020
 */
#ifndef HOLO_LOCALIZATION_SAM_FACTORS_GNSS_POSITION_VELOCITY_FACTOR_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_GNSS_POSITION_VELOCITY_FACTOR_H_

#include <holo/localization/sam/factors/internal/gnss_position_velocity_factor_inl.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup sam
 * @{
 *
 */

using GTGnssPositionVelocityFactor = holo::localization::internal::GnssPositionVelocityFactor;

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_GNSS_POSITION_VELOCITY_FACTOR_H_
