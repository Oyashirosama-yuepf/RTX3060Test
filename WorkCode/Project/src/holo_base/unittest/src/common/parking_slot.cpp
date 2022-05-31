#include <holo/common/parking_slot.h>
template class holo::common::ParkingSlotFrameT<holo::float32_t>;

template size_t holo::common::ParkingSlotFrameT<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void   holo::common::ParkingSlotFrameT<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::common::ParkingSlotFrameT<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);
