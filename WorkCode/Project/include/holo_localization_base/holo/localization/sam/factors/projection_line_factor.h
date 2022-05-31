/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file projection_line_factor.h
 * @brief A class to define projection lane factor
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date June 20, 2020
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_PROJECTION_LINE_FACTOR_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_PROJECTION_LINE_FACTOR_H_

#include <holo/localization/sam/factors/internal/projection_line_factor_inl.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup sam
 * @{
 *
 */

using GTProjectionLineFactor = holo::localization::internal::ProjectionLineFactor;

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_PROJECTION_LINE_FACTOR_H_
