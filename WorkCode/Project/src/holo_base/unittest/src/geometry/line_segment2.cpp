#include <holo/geometry/line_segment2.h>

template class holo::geometry::details::LineSegment2T<holo::float32_t>;
template holo::geometry::details::LineSegment2T<holo::float32_t>::operator LineSegment2T<holo::float64_t>() const
    noexcept;
template size_t holo::geometry::details::LineSegment2T<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void   holo::geometry::details::LineSegment2T<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::geometry::details::LineSegment2T<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);

