/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file polynomial_curve2d.h
 * @brief This header file defines polynomial_curve2d
 * @author duyanwei@holomatic.com
 * @date Sep-29-2020
 */

#ifndef HOLO_GEOMETRY_POLYNOMIAL_CURVE2D_H_
#define HOLO_GEOMETRY_POLYNOMIAL_CURVE2D_H_

#include "./details/polynomial_curve2d.h"

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
using PolynomialCurve2DT = details::PolynomialCurve2DT<T>;

using PolynomialCurve2f = details::PolynomialCurve2DT<float32_t>;
using PolynomialCurve2d = details::PolynomialCurve2DT<float64_t>;
using PolynomialCurve2  = details::PolynomialCurve2DT<float64_t>;

}  // namespace geometry

/**
 * @deprecated Deprecated soon, please use holo::geometry::PolynomialCurve2DT<T>
 *
 * @tparam T
 */
template <typename T>
using PolynomialCurve2DT [[deprecated]] = geometry::PolynomialCurve2DT<T>;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::PolynomialCurve2f
 *
 */
using PolynomialCurve2f [[deprecated]] = geometry::PolynomialCurve2f;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::PolynomialCurve2d
 *
 */
using PolynomialCurve2d [[deprecated]] = geometry::PolynomialCurve2d;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::PolynomialCurve2
 *
 */
using PolynomialCurve2 [[deprecated]] = geometry::PolynomialCurve2;

}  // namespace holo

#endif  // HOLO_GEOMETRY_POLYNOMIAL_CURVE2D_H_