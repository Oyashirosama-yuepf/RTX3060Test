#include <holo/geometry/polyfit2.h>

template class holo::geometry::details::Polyfit2T<holo::float32_t>;
template size_t holo::geometry::details::Polyfit2T<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void   holo::geometry::details::Polyfit2T<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::geometry::details::Polyfit2T<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);

