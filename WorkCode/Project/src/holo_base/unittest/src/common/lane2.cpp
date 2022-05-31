#include <holo/common/lane2.h>
#include <holo/geometry/curve.h>

using ScalarType = holo::float32_t;
using PointType  = holo::geometry::Point2T<ScalarType>;
using CurveType  = holo::geometry::CurvePolynomial<PointType, 64U, 3U>;
template class holo::common::Lane<CurveType>;

template size_t holo::common::Lane<CurveType>::GetSerializedAttributesSize<4U>() const noexcept;
template void   holo::common::Lane<CurveType>::SerializeAttributes<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::common::Lane<CurveType>::DeserializeAttributes<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);
