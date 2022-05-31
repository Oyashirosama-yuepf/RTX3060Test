#include <holo/common/light_signal_request.h>
template size_t holo::LightSignalRequest::GetSerializedSize<4U>() const noexcept;
template void   holo::LightSignalRequest::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::LightSignalRequest::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);
