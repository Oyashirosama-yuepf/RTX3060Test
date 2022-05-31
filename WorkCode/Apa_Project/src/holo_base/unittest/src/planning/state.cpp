#include <holo/planning/state.h>
template size_t holo::planning::State::GetSerializedSize<4U>() const noexcept;
template void
holo::planning::State::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::planning::State::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);

