#include <holo/obstacle/obstacle_list.h>

template class holo::obstacle::details::ObstaclePtrListT<holo::obstacle::ObstacleVisionT<holo::float32_t, 128U>, 0>;

using ObstacleListType =
    holo::obstacle::details::ObstaclePtrListT<holo::obstacle::ObstacleVisionT<holo::float32_t, 128U>, 0>;

template size_t ObstacleListType::GetSerializedSize<4U>() const noexcept;
template void ObstacleListType::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void ObstacleListType::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
