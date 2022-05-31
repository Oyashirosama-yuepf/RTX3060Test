#include <holo/common/odometry.h>
template class holo::common::details::OdometryT<holo::float32_t>;
template class holo::common::details::LocalMapOdometryT<holo::float32_t, 3U>;
template class holo::common::details::DrOdometryT<holo::float32_t>;

template size_t holo::common::details::OdometryBaseT<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void   holo::common::details::OdometryBaseT<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::common::details::OdometryBaseT<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);

template size_t holo::common::LocalMapOdometryT<holo::float32_t, 3U>::GetSerializedSize<4U>() const noexcept;
template void   holo::common::LocalMapOdometryT<holo::float32_t, 3U>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::common::LocalMapOdometryT<holo::float32_t, 3U>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);

template size_t holo::common::DrOdometryT<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void   holo::common::DrOdometryT<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::common::DrOdometryT<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);
