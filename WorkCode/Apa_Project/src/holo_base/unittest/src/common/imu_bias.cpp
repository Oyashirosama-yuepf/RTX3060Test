#include <holo/common/imu_bias.h>
template class holo::common::details::ImuBiasT<holo::float32_t>;

using OutputType = holo::geometry::Point3f;
template OutputType holo::common::ImuBiasT<holo::float32_t>::GetAngularVelocityBias<>() const;
template OutputType holo::common::ImuBiasT<holo::float32_t>::GetLinearAccelerationBias<>() const;
template OutputType holo::common::ImuBiasT<holo::float32_t>::GetAngularVelocityBiasCovariance<>() const;
template OutputType holo::common::ImuBiasT<holo::float32_t>::GetLinearAccelerationBiasCovariance<>() const;

template size_t holo::common::ImuBiasT<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void   holo::common::ImuBiasT<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::common::ImuBiasT<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);
