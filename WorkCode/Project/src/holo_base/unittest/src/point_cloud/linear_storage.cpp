#include <holo/geometry/point3.h>
#include <holo/point_cloud/details/linear_storage.h>

using PointType = holo::geometry::Point3T<holo::float32_t>;
template class holo::point_cloud::details::LinearStorage<PointType, std::numeric_limits<size_t>::max(),
                                                         sizeof(PointType)>;
