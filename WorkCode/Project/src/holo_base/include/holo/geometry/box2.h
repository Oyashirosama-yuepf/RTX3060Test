/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box2.h
 * @brief This header file defines box in 2d.
 * @author duyanwei@holomatic.com
 * @date Sep-25-2020
 */

#ifndef HOLO_GEOMETRY_BOX2_H_
#define HOLO_GEOMETRY_BOX2_H_

#include "./details/box2.h"

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
using Box2T = details::Box2T<T>;

using Box2f = details::Box2T<float32_t>;
using Box2d = details::Box2T<float64_t>;
using Box2  = details::Box2T<float64_t>;

}  // namespace geometry

/**
 * @deprecated Deprecated soon, please use holo::geometry::Box2T<T>
 *
 * @tparam T
 */
template <typename T>
using Box2T [[deprecated]] = geometry::Box2T<T>;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Box2f
 *
 */
using Box2f [[deprecated]] = geometry::Box2f;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Box2d
 *
 */
using Box2d [[deprecated]] = geometry::Box2d;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Box2
 *
 */
using Box2 [[deprecated]] = geometry::Box2;

}  // namespace holo

#endif  // HOLO_GEOMETRY_BOX2_H_