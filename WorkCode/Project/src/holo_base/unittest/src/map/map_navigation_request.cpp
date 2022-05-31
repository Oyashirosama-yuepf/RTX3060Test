#include <holo/map/map_navigation_request.h>

template class holo::map::RoutingSearchRequestT<2>;
template size_t holo::map::RoutingSearchRequestT<2>::GetSerializedSize<4U>() const noexcept;
template void   holo::map::RoutingSearchRequestT<2>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::map::RoutingSearchRequestT<2>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);
