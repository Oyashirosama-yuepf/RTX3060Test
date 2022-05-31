/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point3.h
 * @brief This header file defines point in 2d.
 * @author duyanwei@holomatic.com
 * @date 2020-09-14
 */

#ifndef HOLO_GEOMETRY_POINT3_H_
#define HOLO_GEOMETRY_POINT3_H_

#include "./details/point3.h"

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
using Point3T = details::Point3T<T>;

using Point3f = details::Point3T<float32_t>;
using Point3d = details::Point3T<float64_t>;
using Point3  = details::Point3T<float64_t>;

}  // namespace geometry

// @brief deprecated soon

template <typename T>
using Point3T [[deprecated]] = geometry::Point3T<T>;

using Point3f [[deprecated]] = geometry::Point3T<float32_t>;
using Point3d [[deprecated]] = geometry::Point3T<float64_t>;
using Point3 [[deprecated]]  = geometry::Point3T<float64_t>;

}  // namespace holo

#endif  // HOLO_GEOMETRY_POINT3_H_