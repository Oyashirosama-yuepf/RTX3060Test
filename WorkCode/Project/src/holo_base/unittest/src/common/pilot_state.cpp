#include <holo/common/pilot_state.h>

template size_t holo::common::PilotState::GetSerializedSize<4U>() const noexcept;
template void
holo::common::PilotState::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::PilotState::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
