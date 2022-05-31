#include <holo/map/lane_mark_info.h>

template size_t holo::map::LaneMarkInfo::GetSerializedSize<4U>() const noexcept;
template void
holo::map::LaneMarkInfo::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::map::LaneMarkInfo::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
