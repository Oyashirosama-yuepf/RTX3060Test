#include <holo/obstacle/obstacle_lidar.h>

template class holo::obstacle::details::ObstacleLidarT<holo::float32_t>;
using ObstacleLidarType = holo::obstacle::details::ObstacleLidarT<holo::float32_t>;

template size_t ObstacleLidarType::GetSerializedSize<4U>() const noexcept;
template void ObstacleLidarType::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void ObstacleLidarType::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
