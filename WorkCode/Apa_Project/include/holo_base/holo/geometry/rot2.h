/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rot2.h
 * @brief This header file defines rotation in 2D.
 * @author duyanwei@holomatic.com
 * @date 2020-09-25
 */

#ifndef HOLO_GEOMETRY_ROT2_H_
#define HOLO_GEOMETRY_ROT2_H_

#include "./details/rot2.h"

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
using Rot2T = details::Rot2T<T>;

using Rot2f = details::Rot2T<float32_t>;
using Rot2d = details::Rot2T<float64_t>;
using Rot2  = details::Rot2T<float64_t>;

}  // namespace geometry

/**
 * @deprecated Deprecated soon, please use holo::geometry::Rot2T<T>
 *
 * @tparam T
 */
template <typename T>
using Rot2T [[deprecated]] = geometry::Rot2T<T>;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Rot2f
 *
 */
using Rot2f [[deprecated]] = geometry::Rot2f;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Rot2d
 *
 */
using Rot2d [[deprecated]] = geometry::Rot2d;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Rot2
 *
 */
using Rot2 [[deprecated]] = geometry::Rot2;

}  // namespace holo

#endif  // HOLO_GEOMETRY_ROT2_H_