#include <holo/geometry/box2.h>

template class holo::geometry::details::Box2T<holo::float32_t>;
template holo::geometry::details::Box2T<holo::float32_t>::operator Box2T<holo::float64_t>() const noexcept;
template size_t holo::geometry::details::Box2T<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void   holo::geometry::details::Box2T<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::geometry::details::Box2T<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);

