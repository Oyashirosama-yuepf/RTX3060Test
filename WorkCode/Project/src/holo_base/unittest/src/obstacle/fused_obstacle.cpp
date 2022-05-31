#include <holo/obstacle/fused_obstacle.h>

template class holo::gh02::obstacle::details::FusedObstacleT<holo::float32_t, 10U>;
using FusedObstacleType = holo::gh02::obstacle::details::FusedObstacleT<holo::float32_t, 10U>;

template size_t FusedObstacleType::GetSerializedSize<4U>() const noexcept;
template void FusedObstacleType::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void FusedObstacleType::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
