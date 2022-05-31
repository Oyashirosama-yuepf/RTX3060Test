#include <holo/common/imu.h>
template class holo::common::details::ImuT<holo::float32_t>;
using OutputType = holo::geometry::Point3f;
template OutputType holo::common::ImuT<holo::float32_t>::GetAngularVelocity<OutputType>() const;
template OutputType holo::common::ImuT<holo::float32_t>::GetLinearAcceleration<OutputType>() const;

template size_t holo::common::ImuT<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void   holo::common::ImuT<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::common::ImuT<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);
