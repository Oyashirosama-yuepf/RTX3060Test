#ifndef HOLO_METADATA_COMMON_CAMERA_LANE_BOUNDARY_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_CAMERA_LANE_BOUNDARY_TYPE_DESCRIPTION_H_

#include <holo/common/camera_lane_boundary.h>
#include <holo/metadata/common/boundary_feature_type_description.h>
#include <holo/metadata/common/coordinate_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/numerics/utility_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace common_type
{
static constexpr char CAMERA_LANE_BOUNDARY_TYPE_NAME[]   = "ScalarType";
static constexpr char CAMERA_LANE_BOUNDARIES_TYPE_NAME[] = "BoundaryType";
}  // namespace common_type

template <typename T, size_t Degree, size_t AttributeSize, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::CameraLaneBoundaryT<T, Degree, AttributeSize>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto boundary_category_pair_desc = std::make_shared<TypeDescriptionStruct>(
            ALIGN, IS_BIG_ENDIAN,
            "holo::common::CameraLaneBoundaryT::BoundaryCategoriesType::pair<float32_t, BoundaryStyle>");
        (void)boundary_category_pair_desc->SetTemplates({}).SetMembers(
            {{"cut_x", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"style", TypeDescriptionResolver<holo::common::BoundaryStyle, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto boundary_categories_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)boundary_categories_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(boundary_category_pair_desc);

        auto boundary_color_pair_desc = std::make_shared<TypeDescriptionStruct>(
            ALIGN, IS_BIG_ENDIAN,
            "holo::common::CameraLaneBoundaryT::BoundaryColorType::pair<float32_t, BoundaryColor>");
        (void)boundary_color_pair_desc->SetTemplates({}).SetMembers(
            {{"cut_x", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"color", TypeDescriptionResolver<holo::common::BoundaryColor, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto boundary_colors_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)boundary_colors_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(boundary_color_pair_desc);

        auto boundary_widths_pair_desc = std::make_shared<TypeDescriptionStruct>(
            ALIGN, IS_BIG_ENDIAN, "holo::common::CameraLaneBoundaryT::BoundaryWidthsType::pair<float32_t, float32_t>");
        (void)boundary_widths_pair_desc->SetTemplates({}).SetMembers(
            {{"cut_x", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"width", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto boundary_widths_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)boundary_widths_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(boundary_widths_pair_desc);

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::CameraLaneBoundaryT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"track_id", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"boundary_index", TypeDescriptionResolver<::holo::int8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"confidence", TypeDescriptionResolver<::holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"start_x", TypeDescriptionResolver<TypeReferenceTag<0U, common_type::CAMERA_LANE_BOUNDARY_TYPE_NAME>,
                                                     ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"end_x", TypeDescriptionResolver<TypeReferenceTag<0U, common_type::CAMERA_LANE_BOUNDARY_TYPE_NAME>,
                                                   ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"curve",
                  TypeDescriptionResolver<
                      holo::numerics::Polynomial<TypeReferenceTag<1U, common_type::CAMERA_LANE_BOUNDARY_TYPE_NAME>,
                                                 Degree>,
                      ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"boundary_styles", boundary_categories_desc},
                 {"boundary_colors", boundary_colors_desc},
                 {"boundary_widths", boundary_widths_desc}});
        return desc;
    }
};

template <typename T, size_t SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::CameraLaneBoundariesT<T, SIZE>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::CameraLaneBoundariesT");
        (void)desc->SetTemplates({{"BoundaryType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers({{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"boundaries",
                          TypeDescriptionResolver<TypeReferenceTag<0U, common_type::CAMERA_LANE_BOUNDARIES_TYPE_NAME>,
                                                  ALIGN, IS_BIG_ENDIAN>::Get()}});

        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
