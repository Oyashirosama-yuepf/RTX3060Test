#ifndef HOLO_METADATA_POINT_CLOUD_POINT_TYPE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_POINT_CLOUD_POINT_TYPE_TYPE_DESCRIPTION_H_

#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/point_cloud/point_type.h>

namespace holo
{
namespace metadata
{
namespace point_cloud_type
{
static constexpr char POINT_TYPE_SCALAR_TYPE_NAME[] = "ScalarType";
}  // namespace point_cloud

template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::point_cloud::PointXYZIRSt<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto point_type_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::point_cloud::PointXYZIRSt");
        (void)point_type_desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"data",
                  TypeDescriptionResolver<ArrayTag<TypeReferenceTag<1U, point_cloud_type::POINT_TYPE_SCALAR_TYPE_NAME>, 3U>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"intensity", TypeDescriptionResolver<TypeReferenceTag<0U, point_cloud_type::POINT_TYPE_SCALAR_TYPE_NAME>,
                                                       ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"ring", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return point_type_desc;
    }
};

template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::point_cloud::PointXYZIRRgbSt<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto point_type_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::point_cloud::PointXYZIRRgbSt");
        (void)point_type_desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"data",
                  TypeDescriptionResolver<ArrayTag<TypeReferenceTag<1U, point_cloud_type::POINT_TYPE_SCALAR_TYPE_NAME>, 3U>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"intensity", TypeDescriptionResolver<TypeReferenceTag<0U, point_cloud_type::POINT_TYPE_SCALAR_TYPE_NAME>,
                                                       ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"ring", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"rgb", TypeDescriptionResolver<ArrayTag<holo::uint8_t, 3U>, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return point_type_desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif