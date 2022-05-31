#ifndef HOLO_METADATA_POINT_CLOUD_POINT_CLOUD_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_POINT_CLOUD_POINT_CLOUD_TYPE_DESCRIPTION_H_

#include <holo/metadata/common/coordinate_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/geometry/pose3_type_description.h>
#include <holo/point_cloud/point_cloud.h>

namespace holo
{
namespace metadata
{
namespace point_cloud_type
{
static constexpr char POINT_CLOUD_POINT_TYPE_NAME[]        = "PointType";
static constexpr char POINT_CLOUD_POINT_SCALAR_TYPE_NAME[] = "PointType.ScalarType";
}  // namespace point_cloud

template <typename Point, size_t SIZE, size_t STRIDE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<
    holo::point_cloud::PointCloudT<Point, SIZE, STRIDE, holo::point_cloud::UnorganizedLayoutTag>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto point_cloud_desc = std::make_shared<TypeDescriptionStruct>(
            ALIGN, IS_BIG_ENDIAN, "holo::point_cloud::PointCloudUnorganizedLayout");
        (void)point_cloud_desc->SetTemplates({{"PointType", TypeDescriptionResolver<Point, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"storage",
                  TypeDescriptionResolver<holo::metadata::SequenceTag<
                                              TypeReferenceTag<1U, point_cloud_type::POINT_CLOUD_POINT_TYPE_NAME>, uint32_t>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"pose",
                  TypeDescriptionResolver<
                      holo::geometry::Pose3T<TypeReferenceTag<1U, point_cloud_type::POINT_CLOUD_POINT_SCALAR_TYPE_NAME>>,
                      ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"is_dense", TypeDescriptionResolver<holo::bool_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return point_cloud_desc;
    }
};

template <typename Point, size_t SIZE, size_t STRIDE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<
    holo::point_cloud::PointCloudT<Point, SIZE, STRIDE, holo::point_cloud::OrganizedLayoutTag>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto point_cloud_desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN,
                                                                        "holo::point_cloud::PointCloudOrganizedLayout");
        (void)point_cloud_desc->SetTemplates({{"PointType", TypeDescriptionResolver<Point, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"storage",
                  TypeDescriptionResolver<holo::metadata::SequenceTag<
                                              TypeReferenceTag<1U, point_cloud_type::POINT_CLOUD_POINT_TYPE_NAME>, uint32_t>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"pose",
                  TypeDescriptionResolver<
                      holo::geometry::Pose3T<TypeReferenceTag<1U, point_cloud_type::POINT_CLOUD_POINT_SCALAR_TYPE_NAME>>,
                      ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"is_dense", TypeDescriptionResolver<holo::bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"width", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"height", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return point_cloud_desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
