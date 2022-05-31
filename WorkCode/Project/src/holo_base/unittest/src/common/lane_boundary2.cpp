#include <holo/common/lane_boundary2.h>
#include <holo/geometry/curve.h>

using ScalarType       = holo::float64_t;
using PointType        = holo::geometry::Point2T<ScalarType>;
using CurveType        = holo::geometry::CurvePolynomial<PointType, 64U, 1U>;
using CurvePtrType     = std::shared_ptr<CurveType>;
using LaneBoundaryType = holo::common::LaneBoundary<CurveType>;

template std::pair<ScalarType, ScalarType> LaneBoundaryType::GetCoordinateRange() const noexcept;
template PointType                         LaneBoundaryType::GetSampleByCoordinate(ScalarType x) const;
