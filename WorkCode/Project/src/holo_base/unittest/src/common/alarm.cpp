#include <holo/common/alarm.h>

template size_t holo::common::Alarm::GetSerializedSize<4U>() const noexcept;
template void
holo::common::Alarm::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::Alarm::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
