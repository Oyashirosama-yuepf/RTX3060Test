#include <holo/geometry/point3.h>
#include <holo/point_cloud/point_cloud.h>

using PointType = holo::geometry::Point3T<holo::float32_t>;
template class holo::point_cloud::details::PointCloudT<PointType, std::numeric_limits<size_t>::max(), sizeof(PointType),
                                                       holo::point_cloud::details::OrganizedLayoutTag>;

using PcdType =
    holo::point_cloud::details::PointCloudT<PointType, std::numeric_limits<size_t>::max(), sizeof(PointType),
                                            holo::point_cloud::details::OrganizedLayoutTag>;
template size_t PcdType::GetSerializedSize<4U>() const noexcept;
template void   PcdType::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void   PcdType::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
