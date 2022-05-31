#include <holo/map/lane_info.h>

template size_t holo::map::LaneInfo::GetSerializedSize<4U>() const noexcept;
template void
holo::map::LaneInfo::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::map::LaneInfo::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
