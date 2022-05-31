#include <holo/obstacle/obstacle_vision.h>

template class holo::obstacle::details::ObstacleVisionT<holo::float32_t>;
using ObstacleVisionType = holo::obstacle::details::ObstacleVisionT<holo::float32_t>;

template size_t ObstacleVisionType::GetSerializedSize<4U>() const noexcept;
template void
ObstacleVisionType::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
ObstacleVisionType::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
