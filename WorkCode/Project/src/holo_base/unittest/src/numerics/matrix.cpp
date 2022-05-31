#include <holo/numerics/matrix.h>

template size_t holo::numerics::MatrixBaseT<holo::float32_t, 2U, 1U>::GetSerializedSize<4U>() const noexcept;
template void
holo::numerics::MatrixBaseT<holo::float32_t, 2U, 1U>::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::numerics::MatrixBaseT<holo::float32_t, 2U, 1U>::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);

template size_t holo::numerics::MatrixXf::GetSerializedSize<4U>() const noexcept;
template void
holo::numerics::MatrixXf::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::numerics::MatrixXf::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
