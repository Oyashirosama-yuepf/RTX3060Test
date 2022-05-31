#include <holo/common/timestamp.h>
template size_t holo::common::Timestamp::GetSerializedSize<4U>() const noexcept;
template void
holo::common::Timestamp::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::Timestamp::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
