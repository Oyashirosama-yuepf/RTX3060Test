#include <holo/geometry/point3.h>
#include <holo/point_cloud/point_type.h>
template class holo::point_cloud::details::PointXYZIRSt<holo::float32_t>;
template size_t holo::point_cloud::details::PointXYZIRSt<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void   holo::point_cloud::details::PointXYZIRSt<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void
holo::point_cloud::details::PointXYZIRSt<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);

template class holo::point_cloud::details::PointXYZIRRgbSt<holo::float32_t>;
template size_t holo::point_cloud::details::PointXYZIRRgbSt<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void
holo::point_cloud::details::PointXYZIRRgbSt<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void
holo::point_cloud::details::PointXYZIRRgbSt<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);
