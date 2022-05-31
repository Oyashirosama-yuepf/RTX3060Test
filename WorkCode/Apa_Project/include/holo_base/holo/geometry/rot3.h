/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rot3.h
 * @brief This header file defines rotation in 3D.
 * @author duyanwei@holomatic.com
 * @date Sep-27-2020
 */

#ifndef HOLO_GEOMETRY_ROT3_H_
#define HOLO_GEOMETRY_ROT3_H_

#include "./details/rot3.h"

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
using Rot3T = details::Rot3T<T>;

using Rot3f = details::Rot3T<float32_t>;
using Rot3d = details::Rot3T<float64_t>;
using Rot3  = details::Rot3T<float64_t>;

}  // namespace geometry

/**
 * @deprecated Deprecated soon, please use holo::geometry::Rot3T<T>
 *
 * @tparam T
 */
template <typename T>
using Rot3T [[deprecated]] = geometry::Rot3T<T>;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Rot3f
 *
 */
using Rot3f [[deprecated]] = geometry::Rot3f;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Rot3d
 *
 */
using Rot3d [[deprecated]] = geometry::Rot3d;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Rot3
 *
 */
using Rot3 [[deprecated]] = geometry::Rot3;

}  // namespace holo

#endif  // HOLO_GEOMETRY_ROT3_H_