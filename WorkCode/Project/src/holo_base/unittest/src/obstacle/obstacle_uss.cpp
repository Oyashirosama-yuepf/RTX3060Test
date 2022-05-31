#include <holo/obstacle/obstacle_uss.h>

template class holo::obstacle::details::ObstacleUssT<holo::float32_t>;
using ObstacleUssType = holo::obstacle::details::ObstacleUssT<holo::float32_t>;

template size_t ObstacleUssType::GetSerializedSize<4U>() const noexcept;
template void   ObstacleUssType::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void   ObstacleUssType::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
