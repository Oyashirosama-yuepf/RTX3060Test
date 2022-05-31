/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point2.h
 * @brief This header file defines point in 2d.
 * @author duyanwei@holomatic.com
 * @date 2020-09-14
 */

#ifndef HOLO_GEOMETRY_POINT2_H_
#define HOLO_GEOMETRY_POINT2_H_

#include "./details/point2.h"

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
using Point2T = details::Point2T<T>;

using Point2f = details::Point2T<float32_t>;
using Point2d = details::Point2T<float64_t>;
using Point2  = details::Point2T<float64_t>;

}  // namespace geometry

// @brief deprecated soon

template <typename T>
using Point2T [[deprecated]] = geometry::Point2T<T>;

using Point2f [[deprecated]] = geometry::Point2T<float32_t>;
using Point2d [[deprecated]] = geometry::Point2T<float64_t>;
using Point2 [[deprecated]]  = geometry::Point2T<float64_t>;

}  // namespace holo

#endif  // HOLO_GEOMETRY_POINT2_H_