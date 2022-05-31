#ifndef HOLO_METADATA_COMMON_FREESPACE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_FREESPACE_TYPE_DESCRIPTION_H_

#include <holo/common/freespace.h>
#include <holo/metadata/common/coordinate_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace common_type
{
static constexpr char FREESPACE_POINT_TYPE_NAME[]    = "PointType";
static constexpr char FREESPACE_EXTERIOR_TYPE_NAME[] = "ExteriorType";
} 

template <typename Point, size_t POINT_SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::details::FreespaceInteriorPolygon<Point, POINT_SIZE>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto segment_info_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::segment_info_desc");
        (void)segment_info_desc->SetTemplates({}).SetMembers(
            {{"start", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"end", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"type", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto boundaries_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)boundaries_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(segment_info_desc);

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN,
                                                            "holo::common::details::FreespaceInteriorPolygon");
        (void)desc->SetTemplates({{"PointType", TypeDescriptionResolver<Point, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"points",
                  TypeDescriptionResolver<
                      holo::metadata::SequenceTag<TypeReferenceTag<1U, common_type::FREESPACE_POINT_TYPE_NAME>, uint32_t>,
                      ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"boundaries", boundaries_desc}});
        return desc;
    }
};

template <typename Point, size_t POINT_SIZE, size_t INTERIOR_SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::details::FreespaceExteriorPolygon<Point, POINT_SIZE, INTERIOR_SIZE>, ALIGN,
                               IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto segment_info_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::segment_info_desc");
        (void)segment_info_desc->SetTemplates({}).SetMembers(
            {{"start", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"end", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"type", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto boundaries_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)boundaries_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(segment_info_desc);

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN,
                                                            "holo::common::details::FreespaceExteriorPolygon");
        (void)desc->SetTemplates({{"PointType", TypeDescriptionResolver<Point, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"points",
                  TypeDescriptionResolver<
                      holo::metadata::SequenceTag<TypeReferenceTag<1U, common_type::FREESPACE_POINT_TYPE_NAME>, uint32_t>,
                      ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"boundaries", boundaries_desc},
                 {"interiors",
                  TypeDescriptionResolver<holo::metadata::SequenceTag<
                                              holo::common::details::FreespaceInteriorPolygon<
                                                  TypeReferenceTag<2U, common_type::FREESPACE_POINT_TYPE_NAME>, POINT_SIZE>,
                                              uint32_t>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <typename Exterior, size_t POLYGON_SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::details::Freespace<Exterior, POLYGON_SIZE>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::details::Freespace");
        (void)desc->SetTemplates({{"ExteriorType", TypeDescriptionResolver<Exterior, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"exterior_polygons",
                  TypeDescriptionResolver<
                      holo::metadata::SequenceTag<TypeReferenceTag<1U, common_type::FREESPACE_EXTERIOR_TYPE_NAME>, uint32_t>,
                      ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif