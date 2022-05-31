#include <holo/common/gnss_pvt.h>
#include <holo/geometry/point3.h>
using PointType = std::array<holo::float64_t, 3>;
template PointType holo::common::GnssPvt::GetPosition<PointType>() const noexcept;
template PointType holo::common::GnssPvt::GetVelocity<PointType>() const noexcept;
template PointType holo::common::GnssPvt::GetPositionCov<PointType>() const noexcept;
template PointType holo::common::GnssPvt::GetVelocityCov<PointType>() const noexcept;

template void holo::common::GnssPvt::SetPosition<>(std::array<holo::float32_t, 3U> const& value);
template void holo::common::GnssPvt::SetVelocity<>(holo::geometry::Point3f const& pt) noexcept;
template void holo::common::GnssPvt::SetPositionCov<>(holo::geometry::Point3f const& pt) noexcept;
template void holo::common::GnssPvt::SetVelocityCov<>(PointType const& pt) noexcept;

template size_t holo::common::GnssPvt::GetSerializedSize<4U>() const noexcept;
template void
holo::common::GnssPvt::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::GnssPvt::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
