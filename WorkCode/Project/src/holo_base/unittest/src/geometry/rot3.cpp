#include <holo/geometry/rot3.h>

template class holo::geometry::details::Rot3T<holo::float32_t>;
template holo::geometry::details::Rot3T<holo::float32_t>::operator Rot3T<holo::float64_t>() const noexcept;
template size_t holo::geometry::details::Rot3T<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void   holo::geometry::details::Rot3T<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::geometry::details::Rot3T<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);

