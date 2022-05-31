#include <holo/common/road_type.h>

template size_t holo::common::RoadType::GetSerializedSize<4U>() const noexcept;
template void
holo::common::RoadType::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::RoadType::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
