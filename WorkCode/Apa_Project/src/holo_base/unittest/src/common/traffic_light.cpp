#include <holo/common/traffic_light.h>
template class holo::common::details::TrafficLightT<2U, 2U>;
template class holo::common::details::TrafficLightsT<2U, 2U, 2U>;

template size_t holo::common::details::TrafficLightsT<2U, 2U, 2U>::GetSerializedSize<4U>() const noexcept;
template void   holo::common::details::TrafficLightsT<2U, 2U, 2U>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::common::details::TrafficLightsT<2U, 2U, 2U>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);
