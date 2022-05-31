#include <holo/map/link_info.h>

template size_t holo::map::LinkInfo::GetSerializedSize<4U>() const noexcept;
template void
holo::map::LinkInfo::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::map::LinkInfo::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
