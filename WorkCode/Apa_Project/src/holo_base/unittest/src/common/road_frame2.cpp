#include <holo/common/road_frame2.h>
#include <holo/geometry/curve.h>

using ScalarType = holo::float64_t;
using PointType  = holo::geometry::Point2T<ScalarType>;
using CurveType  = holo::geometry::CurvePolynomial<PointType, 64U, 3U>;
using RoadFrameType = holo::common::RoadFrame<CurveType>;

template void RoadFrameType::EmplaceBackConflictPath(RoadFrameType::ConflictPathType&&);
