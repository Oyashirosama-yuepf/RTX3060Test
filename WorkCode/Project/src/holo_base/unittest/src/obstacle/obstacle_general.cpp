#include <holo/obstacle/obstacle_general.h>

template class holo::obstacle::details::ObstacleGeneralT<holo::float32_t>;
using ObstacleGeneralType = holo::obstacle::details::ObstacleGeneralT<holo::float32_t>;

template size_t ObstacleGeneralType::GetSerializedSize<4U>() const noexcept;
template void
ObstacleGeneralType::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
ObstacleGeneralType::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
