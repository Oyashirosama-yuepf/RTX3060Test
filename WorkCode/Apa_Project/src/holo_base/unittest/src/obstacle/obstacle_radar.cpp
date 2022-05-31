#include <holo/obstacle/obstacle_radar.h>

template class holo::obstacle::details::ObstacleRadarT<holo::float32_t>;
using ObstacleRadarType = holo::obstacle::details::ObstacleRadarT<holo::float32_t>;

template size_t ObstacleRadarType::GetSerializedSize<4U>() const noexcept;
template void ObstacleRadarType::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void ObstacleRadarType::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
