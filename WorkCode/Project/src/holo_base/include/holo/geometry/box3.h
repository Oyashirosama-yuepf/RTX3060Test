/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box3.h
 * @brief This header file defines box in 3d.
 * @author duyanwei@holomatic.com
 * @date Sep-27-2020
 */

#ifndef HOLO_GEOMETRY_BOX3_H_
#define HOLO_GEOMETRY_BOX3_H_

#include "./details/box3.h"

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
using Box3T = details::Box3T<T>;

using Box3f = details::Box3T<float32_t>;
using Box3d = details::Box3T<float64_t>;
using Box3  = details::Box3T<float64_t>;

}  // namespace geometry

/**
 * @deprecated Deprecated soon, please use holo::geometry::Box3T<T>
 *
 * @tparam T
 */
template <typename T>
using Box3T [[deprecated]] = geometry::Box3T<T>;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Box3f
 *
 */
using Box3f [[deprecated]] = geometry::Box3f;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Box3d
 *
 */
using Box3d [[deprecated]] = geometry::Box3d;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Box3
 *
 */
using Box3 [[deprecated]] = geometry::Box3;

}  // namespace holo

#endif  // HOLO_GEOMETRY_BOX3_H_