#include <holo/common/grid_map.h>
template class holo::common::GridMap<holo::common::GridMapCell, 5U, 6U>;
template size_t holo::common::GridMap<holo::common::GridMapCell, 5U, 6U>::GetSerializedSize<4U>() const noexcept;
template void   holo::common::GridMap<holo::common::GridMapCell, 5U, 6U>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void
holo::common::GridMap<holo::common::GridMapCell, 5U, 6U>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);
