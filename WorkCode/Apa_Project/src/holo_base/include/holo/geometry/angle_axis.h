/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file angle_axis.h
 * @brief This header file defines angle-axis.
 * @author duyanwei@holomatic.com
 * @date Oct-10-2020
 */

#ifndef HOLO_GEOMETRY_ANGLE_AXIS_H_
#define HOLO_GEOMETRY_ANGLE_AXIS_H_

#include "./details/angle_axis.h"

namespace holo
{
namespace geometry
{
/**
 * @addtogroup geometry
 * @{
 *
 */

template <typename T>
using AngleAxisT = details::AngleAxisT<T>;

using AngleAxisf = details::AngleAxisT<float32_t>;
using AngleAxisd = details::AngleAxisT<float64_t>;
using AngleAxis  = details::AngleAxisT<float64_t>;

}  // namespace geometry

/**
 * @deprecated Deprecated soon, please use holo::geometry::AngleAxisT<T>
 *
 * @tparam T
 */
template <typename T>
using AngleAxisT [[deprecated]] = geometry::AngleAxisT<T>;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::AngleAxisf
 *
 */
using AngleAxisf [[deprecated]] = geometry::AngleAxisf;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::AngleAxisd
 *
 */
using AngleAxisd [[deprecated]] = geometry::AngleAxisd;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::AngleAxis
 *
 */
using AngleAxis [[deprecated]] = geometry::AngleAxis;

}  // namespace holo

#endif  // HOLO_GEOMETRY_ANGLE_AXIS_H_