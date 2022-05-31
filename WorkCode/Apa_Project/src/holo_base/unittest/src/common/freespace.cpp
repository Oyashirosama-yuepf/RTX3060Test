#include <holo/common/freespace.h>
#include <holo/geometry/point2.h>

using AutoFreespace = holo::common::details::Freespace<holo::common::AutoFreespaceExterior<holo::geometry::Point2f>,
                                                       std::numeric_limits<size_t>::max()>;

template size_t AutoFreespace::GetSerializedSize<4U>() const noexcept;
template void   AutoFreespace::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void   AutoFreespace::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
