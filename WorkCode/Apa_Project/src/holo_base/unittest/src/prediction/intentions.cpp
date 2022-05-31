#include <holo/prediction/intentions.h>

template size_t holo::prediction::Intentions::GetSerializedSize<4U>() const noexcept;
template void
holo::prediction::Intentions::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::prediction::Intentions::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
