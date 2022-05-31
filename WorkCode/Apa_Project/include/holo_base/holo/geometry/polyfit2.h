/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file polyfit2.h
 * @brief This header file defines polyfit in 2d.
 * @author duyanwei@holomatic.com
 * @date Sep-28-2020
 */

#ifndef HOLO_GEOMETRY_POLYFIT2_H_
#define HOLO_GEOMETRY_POLYFIT2_H_

#include "./details/polyfit2.h"

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
using Polyfit2T = details::Polyfit2T<T>;

using Polyfit2f = details::Polyfit2T<float32_t>;
using Polyfit2d = details::Polyfit2T<float64_t>;
using Polyfit2  = details::Polyfit2T<float64_t>;

}  // namespace geometry

/**
 * @deprecated Deprecated soon, please use holo::geometry::Polyfit2T<T>
 *
 * @tparam T
 */
template <typename T>
using Polyfit2T [[deprecated]] = geometry::Polyfit2T<T>;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Polyfit2f
 *
 */
using Polyfit2f [[deprecated]] = geometry::Polyfit2f;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Polyfit2d
 *
 */
using Polyfit2d [[deprecated]] = geometry::Polyfit2d;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Polyfit2
 *
 */
using Polyfit2 [[deprecated]] = geometry::Polyfit2;

}  // namespace holo

#endif  // HOLO_GEOMETRY_POLYFIT2_H_