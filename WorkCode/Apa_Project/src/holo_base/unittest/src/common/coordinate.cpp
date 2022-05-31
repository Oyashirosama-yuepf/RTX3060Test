#include <holo/common/coordinate.h>
#include <holo/geometry/point2.h>

using CoordinateType = holo::common::Coordinate;
using PointType      = holo::geometry::Point2d;

template CoordinateType CoordinateType::UtmCoordinate<PointType>(PointType const&);
template CoordinateType CoordinateType::Utm6Coordinate<PointType>(PointType const&);
template void           CoordinateType::PointConvertLonLatToUtm(PointType const&, CoordinateType const&, PointType&);
template void           CoordinateType::PointConvertUtmToLonLat(CoordinateType const&, PointType const&, PointType&);
template void CoordinateType::PointConvertUtmToUtm(CoordinateType const&, PointType const&, CoordinateType const&,
                                                   PointType&);
template void CoordinateType::PointConvert(CoordinateType const&, PointType&, CoordinateType const&, PointType&);

template size_t holo::common::Coordinate::GetSerializedSize<4U>() const noexcept;
template void
holo::common::Coordinate::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::Coordinate::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
