#include <holo/common/sensor_id.h>
template size_t holo::common::SensorId::GetSerializedSize<4U>() const noexcept;
template void
holo::common::SensorId::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::SensorId::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
