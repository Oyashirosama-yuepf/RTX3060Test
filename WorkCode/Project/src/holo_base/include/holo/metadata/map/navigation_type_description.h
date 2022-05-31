#ifndef HOLO_METADATA_MAP_NAVIGATION_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_MAP_NAVIGATION_TYPE_DESCRIPTION_H_

#include <holo/map/navigation.h>
#include <holo/metadata/common/odometry_type_description.h>
#include <holo/metadata/common/road_category_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/geometry/point2_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t LANE_PATH_SIZE, size_t LANE_ITEM_SIZE, size_t LANE_REGION_SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::NavigationT<LANE_PATH_SIZE, LANE_ITEM_SIZE, LANE_REGION_SIZE>, ALIGN,
                               IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto status_enum_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationT::Status");
        (void)status_enum_desc
            ->SetEnumerates({{0U, "UNKNOWN"},
                             {1U, "OK"},
                             {2U, "WAITING"},
                             {3U, "WARNING"},
                             {4U, "ERROR"},
                             {200U, "RESERVE_1"},
                             {201U, "RESERVE_2"},
                             {202U, "RESERVE_3"},
                             {203U, "RESERVE_4"},
                             {204U, "RESERVE_5"},
                             {255U, "OTHERS"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto operation_mode_enum_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationT::OperationMode");
        (void)operation_mode_enum_desc
            ->SetEnumerates({{0U, "INVALID"},
                             {1U, "NAVIGATION"},
                             {2U, "CRUISER"},
                             {3U, "YAWING"},
                             {200U, "RESERVE_1"},
                             {201U, "RESERVE_2"},
                             {202U, "RESERVE_3"},
                             {203U, "RESERVE_4"},
                             {204U, "RESERVE_5"},
                             {255U, "OTHERS"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto routing_mode_enum_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationT::RoutingMode");
        (void)routing_mode_enum_desc
            ->SetEnumerates({{0U, "OUT_ROUTE"},
                             {1U, "ON_DH_ROUTE"},
                             {2U, "ON_SD_ROUTE"},
                             {3U, "ON_SD_HD_ROUTE"},
                             {200U, "RESERVE_1"},
                             {201U, "RESERVE_2"},
                             {202U, "RESERVE_3"},
                             {203U, "RESERVE_4"},
                             {204U, "RESERVE_5"},
                             {255U, "OTHERS"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto map_mode_enum_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationT::MapMode");
        (void)map_mode_enum_desc
            ->SetEnumerates({{0U, "NO_MAP"},
                             {1U, "HD_MAP"},
                             {2U, "SD_MAP"},
                             {3U, "SD_HD_MAP"},
                             {200U, "RESERVE_1"},
                             {201U, "RESERVE_2"},
                             {202U, "RESERVE_3"},
                             {203U, "RESERVE_4"},
                             {204U, "RESERVE_5"},
                             {255U, "OTHERS"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto description_desc = std::make_shared<TypeDescriptionBitfield>(
            ALIGN, IS_BIG_ENDIAN, "holo::map::Navigation::LanePath::description");
        (void)description_desc
            ->SetFields({{"is_to_destination", 0, 1, TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"is_lane_level_path", 1, 1, TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"reserved", 2, 14, TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto intersection_status_enum_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationT::LanePath::LaneItem::IntersectionStatus");
        (void)intersection_status_enum_desc
            ->SetEnumerates({{0U, "NO_INTERSECTION"},
                             {1U, "INTERSECTION_NO_TRAFFIC"},
                             {2U, "INTERSECTION_WITH_TRAFFIC"},
                             {200U, "RESERVE_1"},
                             {201U, "RESERVE_2"},
                             {202U, "RESERVE_3"},
                             {203U, "RESERVE_4"},
                             {204U, "RESERVE_5"},
                             {255U, "OTHERS"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto lane_item_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationT::LanePath::LaneItem");
        (void)lane_item_desc->SetTemplates({}).SetMembers(
            {{"lane_id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"length", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"road_category", TypeDescriptionResolver<holo::common::RoadCategory, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"intersection_status", intersection_status_enum_desc},
             {"effective_range_start_percent", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"effective_range_end_percent", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto lane_item_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)lane_item_sequence_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(lane_item_desc);

        auto region_model_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationT::LanePath::RegionModelInfo::RegionModel");
        (void)region_model_desc
            ->SetEnumerates({{0U, "NONE"},
                             {1U, "CHANGE_RIGHT"},
                             {2U, "CHANGE_LEFT"},
                             {3U, "SPLIT_RIGHT"},
                             {4U, "SPLIT_LEFT"},
                             {5U, "MERGE_RIGHT"},
                             {6U, "MERGE_LEFT"},
                             {200U, "RESERVE_1"},
                             {201U, "RESERVE_2"},
                             {202U, "RESERVE_3"},
                             {203U, "RESERVE_4"},
                             {204U, "RESERVE_5"},
                             {255U, "OTHERS"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto region_model_info_desc = std::make_shared<TypeDescriptionStruct>(
            ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationT::LanePath::RegionModelInfo");
        (void)region_model_info_desc->SetTemplates({}).SetMembers(
            {{"region_id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"score", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"model", region_model_desc},
             {"prepare_location", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"dangerous_location", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"limit_location", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"link_lane_path_id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto region_model_info_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)region_model_info_sequence_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(region_model_info_desc);

        auto driving_status_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationT::LanePath::RegionStateInfo::DrivingStatus");
        (void)driving_status_desc
            ->SetEnumerates({{0x00, "NONE"},
                             {0x10, "SPLIT_LEFT"},
                             {0x11, "SPLIT_RIGHT"},
                             {0x12, "MERGE_LEFT"},
                             {0x13, "MERGE_RIGHT"},
                             {0x14, "TURN_LEFT"},
                             {0x15, "TURN_RIGHT"},
                             {0x16, "TURN_AROUND_LEFT"},
                             {0x17, "TURN_AROUND_RIGHT"},
                             {0x18, "BREAKUP"},
                             {0x19, "ACCELERATE_MERGE_LEFT"},
                             {0x1a, "ACCELERATE_MERGE_RIGHT"},
                             {0x1b, "DECELERATE_SPLIT_LEFT"},
                             {0x1c, "DECELERATE_SPLIT_RIGHT"},
                             {0x1d, "MERGE_PASS_BY_LEFT"},
                             {0x1e, "MERGE_PASS_BY_RIGHT"},
                             {0x1f, "SPLIT_PASS_BY_LEFT"},
                             {0x20, "SPLIT_PASS_BY_RIGHT"},
                             {0x21, "TURN_LEFT_AREA"},
                             {0x22, "TURN_RIGHT_AREA"},
                             {0xf0, "RESERVE_1"},
                             {0xf1, "RESERVE_2"},
                             {0xf2, "RESERVE_3"},
                             {0xf3, "RESERVE_4"},
                             {0xf4, "RESERVE_5"},
                             {0xff, "OTHERS"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto section_form_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationT::LanePath::RegionStateInfo::SectionForm");
        (void)section_form_desc
            ->SetEnumerates({{0x00, "NONE"},
                             {0x21, "DIRECT"},
                             {0x22, "PARALLEL"},
                             {0x23, "CORRESPOND"},
                             {0x24, "RESERVE_1"},
                             {0x25, "RESERVE_2"},
                             {0x26, "RESERVE_3"},
                             {0x27, "RESERVE_4"},
                             {0x28, "RESERVE_5"},
                             {0xff, "OTHERS"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto region_state_info_desc = std::make_shared<TypeDescriptionStruct>(
            ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationT::LanePath::RegionStateInfo");
        (void)region_state_info_desc->SetTemplates({}).SetMembers(
            {{"driving_status", driving_status_desc},
             {"section_form", section_form_desc},
             {"id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"start_distance", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"end_distance", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto region_state_info_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)region_state_info_sequence_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(region_state_info_desc);

        auto lane_path_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationT::LanePath");
        (void)lane_path_desc->SetTemplates({}).SetMembers(
            {{"id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"sequence_number", TypeDescriptionResolver<int8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"description", description_desc},
             {"lane_items", lane_item_sequence_desc},
             {"region_model_infos", region_model_info_sequence_desc},
             {"region_state_infos", region_state_info_sequence_desc},
             {"tracked_path_ids",
              TypeDescriptionResolver<holo::metadata::SequenceTag<uint64_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto lane_path_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)lane_path_sequence_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(lane_path_desc);

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationT");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"status", status_enum_desc},
             {"operation_mode", operation_mode_enum_desc},
             {"routing_mode", routing_mode_enum_desc},
             {"map_mode", map_mode_enum_desc},
             {"odometry_precision",
              TypeDescriptionResolver<holo::common::OdometryPrecision, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"distance_to_available_hd_area_entry", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"distance_to_available_hd_area_exit", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"distance_to_hd_area_entry", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"distance_to_hd_area_exit", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"distance_to_sd_destination", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"distance_to_hd_destination", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lane_paths", lane_path_sequence_desc},
             {"current_lanes",
              TypeDescriptionResolver<holo::metadata::SequenceTag<int32_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"recommended_lanes",
              TypeDescriptionResolver<holo::metadata::SequenceTag<int32_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"expected_lane_paths",
              TypeDescriptionResolver<holo::metadata::SequenceTag<uint64_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"history_trace",
              TypeDescriptionResolver<holo::metadata::SequenceTag<uint64_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif