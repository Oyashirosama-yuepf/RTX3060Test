#include <holo/common/apa_control_command.h>
template size_t holo::common::ApaControlCommand::GetSerializedSize<4U>() const noexcept;
template void
holo::common::ApaControlCommand::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::ApaControlCommand::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
