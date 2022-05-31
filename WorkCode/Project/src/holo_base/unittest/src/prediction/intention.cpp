#include <holo/prediction/intention.h>
template size_t holo::prediction::Intention::GetSerializedSize<4U>() const noexcept;
template void
holo::prediction::Intention::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::prediction::Intention::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
