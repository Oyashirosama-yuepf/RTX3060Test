#include <holo/common/ddt.h>
template class holo::common::DdtStates<2U>;
template size_t holo::common::DdtStates<2U>::GetSerializedSize<4U>() const noexcept;
template void
holo::common::DdtStates<2U>::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::DdtStates<2U>::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
