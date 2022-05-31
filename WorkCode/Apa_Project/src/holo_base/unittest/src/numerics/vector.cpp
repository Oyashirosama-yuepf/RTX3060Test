#include <holo/numerics/vector.h>

template size_t holo::numerics::VectorXf::GetSerializedSize<4U>() const noexcept;
template void
holo::numerics::VectorXf::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::numerics::VectorXf::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
