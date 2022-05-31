#include <holo/core/types.h>
#include <holo/geometry/curve.h>
#include <holo/geometry/point2.h>

using ScalarType = holo::float32_t;
using PointType  = holo::geometry::Point2T<ScalarType>;
template class holo::geometry::CurveParametric<PointType, 10U,
                                               holo::geometry::details::CurveBezier<PointType, 10U, 3U>>;

template class holo::geometry::CurveExplicit<PointType, 10U,
                                             holo::geometry::details::CurvePolynomial<PointType, 10U, 3U>>;
