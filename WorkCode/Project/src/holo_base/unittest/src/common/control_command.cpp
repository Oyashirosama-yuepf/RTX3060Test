#include <holo/common/control_command.h>
template size_t holo::common::ControlCommand::GetSerializedSize<4U>() const noexcept;
template void
holo::common::ControlCommand::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::ControlCommand::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
