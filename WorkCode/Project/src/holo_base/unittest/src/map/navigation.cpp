#include <holo/map/navigation.h>

template class holo::map::NavigationT<3U, 3U, 3U>;
template size_t holo::map::NavigationT<3U, 3U, 3U>::GetSerializedSize<4U>() const noexcept;
template void   holo::map::NavigationT<3U, 3U, 3U>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::map::NavigationT<3U, 3U, 3U>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);
