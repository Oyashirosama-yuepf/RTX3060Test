#include <holo/common/road_category.h>

template size_t holo::common::RoadCategory::GetSerializedSize<4U>() const noexcept;
template void
holo::common::RoadCategory::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::RoadCategory::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);

template size_t holo::common::LaneCategory::GetSerializedSize<4U>() const noexcept;
template void
holo::common::LaneCategory::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::LaneCategory::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
