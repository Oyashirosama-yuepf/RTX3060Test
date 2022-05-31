/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line_segment2.h
 * @brief This header file defines line in 2d.
 * @author duyanwei@holomatic.com
 * @date 2020-09-14
 */

#ifndef HOLO_GEOMETRY_LINE_SEGMENT2_H_
#define HOLO_GEOMETRY_LINE_SEGMENT2_H_

#include "./details/line_segment2.h"

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
using LineSegment2T = details::LineSegment2T<T>;

using LineSegment2f = details::LineSegment2T<float32_t>;
using LineSegment2d = details::LineSegment2T<float64_t>;
using LineSegment2  = details::LineSegment2T<float64_t>;

}  // namespace geometry

/**
 * @deprecated Deprecated soon, please use holo::geometry::LineSegment2T<T>
 *
 * @tparam T
 */
template <typename T>
using LineSegment2T [[deprecated]] = geometry::LineSegment2T<T>;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::LineSegment2f
 *
 */
using LineSegment2f [[deprecated]] = geometry::LineSegment2f;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::LineSegment2d
 *
 */
using LineSegment2d [[deprecated]] = geometry::LineSegment2d;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::LineSegment2
 *
 */
using LineSegment2 [[deprecated]] = geometry::LineSegment2;

}  // namespace holo

#endif  // HOLO_GEOMETRY_LINE_SEGMENT2_H_