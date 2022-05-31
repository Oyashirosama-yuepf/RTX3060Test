/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file convex_polygon2.h
 * @brief This header file defines convex_polygon2 in 2d.
 * @author duyanwei@holomatic.com
 * @date Sep-27-2020
 */

#ifndef HOLO_GEOMETRY_CONVEX_POLYGON2_H_
#define HOLO_GEOMETRY_CONVEX_POLYGON2_H_

#include "./details/convex_polygon2.h"

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
using ConvexPolygon2T = details::ConvexPolygon2T<T>;

using ConvexPolygon2f = details::ConvexPolygon2T<float32_t>;
using ConvexPolygon2d = details::ConvexPolygon2T<float64_t>;
using ConvexPolygon2  = details::ConvexPolygon2T<float64_t>;

}  // namespace geometry

/**
 * @deprecated Deprecated soon, please use holo::geometry::ConvexPolygon2T<T>
 *
 * @tparam T
 */
template <typename T>
using ConvexPolygon2T [[deprecated]] = geometry::ConvexPolygon2T<T>;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::ConvexPolygon2f
 *
 */
using ConvexPolygon2f [[deprecated]] = geometry::ConvexPolygon2f;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::ConvexPolygon2d
 *
 */
using ConvexPolygon2d [[deprecated]] = geometry::ConvexPolygon2d;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::ConvexPolygon2
 *
 */
using ConvexPolygon2 [[deprecated]] = geometry::ConvexPolygon2;

}  // namespace holo

#endif  // HOLO_GEOMETRY_CONVEX_POLYGON2_H_