#ifndef HOLO_METADATA_COMMON_ROAD_FRAME_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_ROAD_FRAME_TYPE_DESCRIPTION_H_

#include <holo/common/road_frame2.h>
#include <holo/metadata/common/lane_boundary_type_description.h>
#include <holo/metadata/common/road_category_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/geometry/curve_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace common_type
{
static constexpr char ROAD_FRAME_CURVE_TYPE_NAME[]             = "CurveType";
static constexpr char ROAD_FRAME_POINT_TYPE_NAME[]             = "CurveType.PointType";
static constexpr char ROAD_FRAME_SCALAR_TYPE_NAME[]            = "CurveType.PointType.ScalarType";
static constexpr char ROAD_FRAME_LANE_POINT_TYPE_NAME[]        = "PointType";
static constexpr char ROAD_FRAME_LANE_SCALAR_TYPE_NAME[]       = "ScalarType";
static constexpr char ROAD_FRAME_POLYNOMIAL_SCALAR_TYPE_NAME[] = "ScalarType";
}  // namespace common
template <typename Curve, size_t SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::RoadFrame<Curve, SIZE>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto boundary_desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::boundary");
        (void)boundary_desc->SetTemplates({}).SetMembers(
            {{"curve_index", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"start_knot_index", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"end_knot_index", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"style", TypeDescriptionResolver<holo::common::BoundaryStyle, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"color", TypeDescriptionResolver<holo::common::BoundaryColor, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"width", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"confidence", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto boundaries_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)boundaries_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(boundary_desc);

        auto lane_desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::lane");
        (void)lane_desc
            ->SetTemplates(
                {{"ScalarType", TypeDescriptionResolver<TypeReferenceTag<2U, common_type::ROAD_FRAME_SCALAR_TYPE_NAME>,
                                                        ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"PointType", TypeDescriptionResolver<TypeReferenceTag<2U, common_type::ROAD_FRAME_POINT_TYPE_NAME>, ALIGN,
                                                       IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"left_boundary_index", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"right_boundary_index", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"external_id", TypeDescriptionResolver<holo::uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"speed_limit_min", TypeDescriptionResolver<holo::uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"speed_limit_max", TypeDescriptionResolver<holo::uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"length", TypeDescriptionResolver<TypeReferenceTag<0U, common_type::ROAD_FRAME_LANE_SCALAR_TYPE_NAME>,
                                                    ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"road_category", TypeDescriptionResolver<holo::common::RoadCategory, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"lane_category", TypeDescriptionResolver<holo::common::LaneCategory, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"center_points",
                  TypeDescriptionResolver<
                      SequenceTag<TypeReferenceTag<1U, common_type::ROAD_FRAME_LANE_POINT_TYPE_NAME>, uint32_t>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"conflict_path_indexes",
                  TypeDescriptionResolver<SequenceTag<holo::uint8_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"crosswalks", TypeDescriptionResolver<SequenceTag<ArrayTag<holo::geometry::Point2d, 4U>, uint32_t>,
                                                        ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"stop_lines", TypeDescriptionResolver<SequenceTag<ArrayTag<holo::geometry::Point2d, 2U>, uint32_t>,
                                                        ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto lanes_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)lanes_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()).SetElementType(lane_desc);

        auto conflict_path_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::RoadFrameT::ConflictPathType");
        (void)conflict_path_desc
            ->SetTemplates(
                {{"PointType", TypeDescriptionResolver<TypeReferenceTag<2U, common_type::ROAD_FRAME_POINT_TYPE_NAME>, ALIGN,
                                                       IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"path_id", TypeDescriptionResolver<holo::uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"path", TypeDescriptionResolver<
                              SequenceTag<TypeReferenceTag<1U, common_type::ROAD_FRAME_LANE_POINT_TYPE_NAME>, uint32_t>,
                              ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto conflict_paths_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)conflict_paths_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(conflict_path_desc);

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::RoadFrameT");
        (void)desc->SetTemplates({{"CurveType", TypeDescriptionResolver<Curve, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"default_index", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"conflict_paths", conflict_paths_desc},
                 {"curves",
                  TypeDescriptionResolver<
                      SequenceTag<TypeReferenceTag<1U, common_type::ROAD_FRAME_CURVE_TYPE_NAME>, uint32_t>>::Get()},
                 {"boundaries", boundaries_desc},
                 {"lanes", lanes_desc},
                 {"adjacencies", TypeDescriptionResolver<holo::metadata::SequenceTag<ArrayTag<uint32_t, 8U>, uint32_t>,
                                                         ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <typename T, size_t Degree, size_t SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::RoadFrame<holo::numerics::Polynomial<T, Degree>, SIZE>, ALIGN,
                               IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::RoadFramePolynomialT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers({{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"boundaries",
                          TypeDescriptionResolver<
                              holo::metadata::SequenceTag<
                                  holo::common::LaneBoundary<holo::numerics::Polynomial<
                                      TypeReferenceTag<2U, common_type::ROAD_FRAME_POLYNOMIAL_SCALAR_TYPE_NAME>, Degree>>,
                                  uint32_t>,
                              ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
