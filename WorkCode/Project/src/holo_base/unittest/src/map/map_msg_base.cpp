#include <holo/map/map_msg_base.h>

template size_t holo::map::MapMsgBase::GetSerializedSize<4U>() const noexcept;
template void
holo::map::MapMsgBase::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::map::MapMsgBase::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
