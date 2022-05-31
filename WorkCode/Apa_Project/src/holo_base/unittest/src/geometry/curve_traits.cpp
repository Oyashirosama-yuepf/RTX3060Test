#include <holo/core/types.h>
#include <holo/geometry/curve.h>
#include <holo/geometry/details/curve_traits.h>
#include <holo/geometry/point2.h>

using ScalarType = holo::float64_t;
using PointType  = holo::geometry::Point2T<ScalarType>;
using CurveType  = holo::geometry::CurvePolynomial<PointType, 64U, 1U>;

template struct holo::geometry::CurveTraits<CurveType>;

