#include <holo/geometry/curve.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>

using ScalarType = holo::float64_t;
using PointType  = holo::geometry::Point2T<ScalarType>;

using CurveCubicBezierType  = holo::geometry::CurveBezier<PointType, 8U, 3U>;
using CurveLinearBezierType = holo::geometry::CurveBezier<PointType, 8U, 1U>;

