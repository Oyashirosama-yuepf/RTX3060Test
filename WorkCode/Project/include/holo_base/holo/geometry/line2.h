/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line2.h
 * @brief This header file defines line in 2d.
 * @author duyanwei@holomatic.com
 * @date 2020-09-14
 */

#ifndef HOLO_GEOMETRY_LINE2_H_
#define HOLO_GEOMETRY_LINE2_H_

#include "./details/line2.h"

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
using Line2T = details::Line2T<T>;

using Line2f = details::Line2T<float32_t>;
using Line2d = details::Line2T<float64_t>;
using Line2  = details::Line2T<float64_t>;

}  // namespace geometry

/**
 * @deprecated Deprecated soon, please use holo::geometry::Line2T<T>
 *
 * @tparam T
 */
template <typename T>
using Line2T [[deprecated]] = geometry::Line2T<T>;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Line2f
 *
 */
using Line2f [[deprecated]] = geometry::Line2f;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Line2d
 *
 */
using Line2d [[deprecated]] = geometry::Line2d;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Line2
 *
 */
using Line2 [[deprecated]] = geometry::Line2;

}  // namespace holo

#endif  // HOLO_GEOMETRY_LINE2_H_