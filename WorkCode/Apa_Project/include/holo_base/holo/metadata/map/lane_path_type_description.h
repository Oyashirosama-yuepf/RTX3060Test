#ifndef HOLO_METADATA_MAP_LANE_PATH_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_MAP_LANE_PATH_TYPE_DESCRIPTION_H_

#include <holo/map/lane_path.h>
#include <holo/common/road_category.h>

#include <holo/metadata/common/road_category_type_description.h>
#include <holo/metadata/geometry/point2_type_description.h>

#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t LANE_PATH_SIZE, size_t LANE_ITEM_SIZE, size_t SEGS, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::AdviceT<LANE_PATH_SIZE, LANE_ITEM_SIZE, SEGS>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto lane_mark_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::map::LanePathT::TerminationType");
        (void)lane_mark_desc
            ->SetEnumerates({{0U, "UNDEFINED"},
                             {1U, "STRAIGHT"},
                             {2U, "STRAIGHT_LEFT"},
                             {3U, "STRAIGHT_RIGHT"},
                             {4U, "LEFT"},
                             {5U, "RIGHT"},
                             {6U, "LEFT_RIGHT"},
                             {7U, "STRAIGHT_LEFT_RIGHT"},
                             {8U, "U_TURN"},
                             {9U, "U_TURN_LEFT"},
                             {10U, "U_TURN_RIGHT"},
                             {11U, "U_TURN_STRAIGHT"},
                             {12U, "U_TURN_STRAIGHT_LEFT"},
                             {13U, "U_TURN_STRAIGHT_RIGHT"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto lane_model_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::map::LanePathT::TerminationType");
        (void)lane_model_desc
            ->SetEnumerates({{1U, "NORMAL"},
                             {2U, "MERGE_TO"},
                             {3U, "MERGE_TO_LEFT"},
                             {4U, "MERGE_TO_RIGHT"},
                             {5U, "MERGE_FROM"},
                             {6U, "MERGE_FROM_LEFT"},
                             {7U, "MERGE_FROM_RIGHT"},
                             {8U, "SPLIT"},
                             {9U, "SPLIT_LEFT"},
                             {10U, "SPLIT_RIGHT"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto lane_item_desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::LaneItem");
        (void)lane_item_desc->SetTemplates({}).SetMembers(
            {{"lane_id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"length", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"road_category", TypeDescriptionResolver<holo::common::RoadCategory, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lane_category", TypeDescriptionResolver<holo::common::LaneCategory, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lane_mark", lane_mark_desc},
             {"lane_model", lane_model_desc},
             {"is_intersection", TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"start_direction",
              TypeDescriptionResolver<holo::geometry::Point2T<float64_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"end_direction",
              TypeDescriptionResolver<holo::geometry::Point2T<float64_t>, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto lane_item_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)lane_item_sequence_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(lane_item_desc);

        auto termination_type_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::map::LanePathT::TerminationType");
        (void)termination_type_desc
            ->SetEnumerates({{0U, "UNDEFINED"}, {1U, "OUT_SEARCH_RANGE"}, {2U, "EXTEND_ROUTE"}, {3U, "NO_SUCCEEDINGS"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto lane_speed_limits_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::LaneSpeedLimits");
        (void)lane_speed_limits_desc->SetTemplates({}).SetMembers(
            {{"start_distance", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"end_distance", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"min_speed", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"max_speed", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto lane_speed_limits_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)lane_speed_limits_sequence_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(lane_speed_limits_desc);

        auto lane_path_desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::LanePathT");
        (void)lane_path_desc->SetTemplates({}).SetMembers(
            {{"lane_item", lane_item_sequence_desc},
             {"id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"sequence_number", TypeDescriptionResolver<int64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"termination_type", termination_type_desc},
             {"lane_speed_limits", lane_speed_limits_sequence_desc}});

        auto lane_path_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)lane_path_sequence_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(lane_path_desc);

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::AdviceT");
        (void)desc->SetTemplates({}).SetMembers(
            {{"lane_paths", lane_path_sequence_desc}});
            return desc;
    }
    };
}  // namespace metadata
}  // namespace holo

#endif