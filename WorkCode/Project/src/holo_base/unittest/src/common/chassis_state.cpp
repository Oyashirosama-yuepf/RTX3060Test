#include <holo/common/chassis_state.h>

template size_t holo::common::ChassisState::GetSerializedSize<4U>() const noexcept;
template void
holo::common::ChassisState::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::ChassisState::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
