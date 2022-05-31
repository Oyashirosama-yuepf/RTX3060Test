#include <holo/common/app_status.h>
template size_t holo::common::AppStatus::GetSerializedSize<4U>() const noexcept;
template void
holo::common::AppStatus::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::AppStatus::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
