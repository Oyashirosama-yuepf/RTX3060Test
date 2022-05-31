#ifndef HOLO_METADATA_SENSORS_FORMAT_LIDAR_SCAN_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_SENSORS_FORMAT_LIDAR_SCAN_TYPE_DESCRIPTION_H_

#include <holo/metadata/common/coordinate_type_description.h>
#include <holo/metadata/geometry/pose3_type_description.h>
#include <holo/metadata/sensors/format/packed_data_type_description.h>
#include <holo/metadata/type_description.h>
#include <holo/sensors/format/lidar_scan.h>

namespace holo
{
namespace metadata
{
template <uint32_t N, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::sensors::format::LidarScan<N>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto lidar_type_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::sensors::format::LidarScan::LidarType");
        lidar_type_desc
            ->SetEnumerates({{0, "NONE"},
                             {1, "LIVOX"},
                             {2, "LIVOXHAP"},
                             {3, "PANDAR"},
                             {4, "RSM1"},
                             {5, "RSRUBY"},
                             {6, "VELODYNE"},
                             {7, "PANDAR128"},
                             {8, "RSBPEARL"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::sensors::format::LidarScan");
        desc->SetTemplates({}).SetMembers(
            {{"version", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"type", lidar_type_desc},
             {"parent_coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"child_coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"pose", TypeDescriptionResolver<holo::geometry::Pose3T<float>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"params",
              TypeDescriptionResolver<holo::metadata::SequenceTag<uint8_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"time_sync_offsets", TypeDescriptionResolver<holo::metadata::ArrayTag<int64_t, 2U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"data", TypeDescriptionResolver<holo::sensors::format::SensorCompressedPacket<0>, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
