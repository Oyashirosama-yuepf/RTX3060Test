#include <holo/map/geofence.h>

template size_t holo::map::Geofences::GetSerializedSize<4U>() const noexcept;
template void
holo::map::Geofences::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::map::Geofences::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
