#include <holo/vision/keypoint3.h>
template class holo::vision::KeyPoint3T<holo::float32_t>;
template size_t holo::vision::KeyPoint3T<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void holo::vision::KeyPoint3T<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void holo::vision::KeyPoint3T<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
