#include <holo/common/lane_scene.h>
template size_t holo::common::LaneScene::GetSerializedSize<4U>() const noexcept;
template void
holo::common::LaneScene::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::LaneScene::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
