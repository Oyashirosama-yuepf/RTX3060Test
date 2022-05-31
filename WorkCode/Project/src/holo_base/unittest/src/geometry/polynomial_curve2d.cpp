#include <holo/geometry/polynomial_curve2d.h>

template class holo::geometry::details::PolynomialCurve2DT<holo::float32_t>;
template size_t holo::geometry::details::PolynomialCurve2DT<holo::float32_t>::GetSerializedSize<4U>() const noexcept;
template void
holo::geometry::details::PolynomialCurve2DT<holo::float32_t>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void
holo::geometry::details::PolynomialCurve2DT<holo::float32_t>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);

