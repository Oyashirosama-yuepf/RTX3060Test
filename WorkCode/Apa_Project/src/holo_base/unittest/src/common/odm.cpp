#include <holo/common/odm.h>
template size_t holo::common::OdmStates::GetSerializedSize<4U>() const noexcept;
template void
holo::common::OdmStates::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::OdmStates::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
