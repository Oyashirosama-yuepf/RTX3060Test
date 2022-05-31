/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file curve.h
 * @brief This header file defines Curve objects.
 * @author ZhangJiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-18
 */

#ifndef HOLO_GEOMETRY_CURVE_H_
#define HOLO_GEOMETRY_CURVE_H_

#include <holo/container/vector.h>
#include <holo/geometry/exception.h>
#include <holo/numerics/exception.h>

#include "details/polynomial_curve.h"
#include "details/bezier_curve.h"

namespace holo
{
namespace geometry
{
/**
 * @addtogroup geometry
 * @{
 */

template <typename Point, size_t SIZE = 256U, size_t DEGREE = 3>
using CurveBezier = holo::geometry::CurveParametric<Point, SIZE, details::CurveBezier<Point, SIZE, DEGREE>>;

template <typename Point, size_t SIZE = 256U, size_t DEGREE = 3>
using CurvePolynomial = holo::geometry::CurveExplicit<Point, SIZE, details::CurvePolynomial<Point, SIZE, DEGREE>>;

/**
 * @}
 */
}  // namespace geometry
}  // namespace holo

#endif
