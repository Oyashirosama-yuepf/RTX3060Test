#include <holo/common/classification.h>
template size_t holo::common::Classification::GetSerializedSize<4U>() const noexcept;
template void
holo::common::Classification::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::Classification::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
