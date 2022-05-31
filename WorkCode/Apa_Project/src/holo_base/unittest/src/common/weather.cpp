#include <holo/common/weather.h>

template size_t holo::common::Weather::GetSerializedSize<4U>() const noexcept;
template void
holo::common::Weather::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::Weather::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
