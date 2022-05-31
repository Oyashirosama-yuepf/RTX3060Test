#include <holo/map/advice.h>

template size_t holo::map::TargetLaneAdviceGroupType::GetSerializedSize<4U>() const noexcept;
template void   holo::map::TargetLaneAdviceGroupType::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::map::TargetLaneAdviceGroupType::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);

template size_t holo::map::TargetLinkAdviceType::GetSerializedSize<4U>() const noexcept;
template void
holo::map::TargetLinkAdviceType::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::map::TargetLinkAdviceType::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);

template size_t holo::map::TargetLinkAdviceGroupType::GetSerializedSize<4U>() const noexcept;
template void   holo::map::TargetLinkAdviceGroupType::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::map::TargetLinkAdviceGroupType::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);

template size_t holo::map::Advice::GetSerializedSize<4U>() const noexcept;
template void holo::map::Advice::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void holo::map::Advice::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);

