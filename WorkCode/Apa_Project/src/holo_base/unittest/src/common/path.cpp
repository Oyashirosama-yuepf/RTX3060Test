#include <holo/common/path.h>
template class holo::common::details::PathT<holo::float32_t>;

template size_t holo::common::details::PathT<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void   holo::common::details::PathT<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::common::details::PathT<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);
