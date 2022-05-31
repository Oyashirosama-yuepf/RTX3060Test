#include <holo/geometry/point3.h>
using ScalarType = holo::float32_t;

template class holo::geometry::details::Point3T<holo::float32_t>;
template holo::geometry::details::Point3T<holo::float32_t>::operator Point3T<holo::float64_t>() const noexcept;
template std::array<holo::float32_t, 3U> holo::geometry::details::Point3T<holo::float32_t>::As() const noexcept;
template ScalarType&                     holo::geometry::details::Point3T<holo::float32_t>::Get<0>() noexcept;
template ScalarType const&               holo::geometry::details::Point3T<holo::float32_t>::Get<0>() const noexcept;

template size_t holo::geometry::details::Point3T<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void   holo::geometry::details::Point3T<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::geometry::details::Point3T<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);

