#ifndef HOLO_METADATA_MAP_MAP_NAVIGATION_RESPONSE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_MAP_MAP_NAVIGATION_RESPONSE_TYPE_DESCRIPTION_H_

#include <holo/map/map_navigation_response.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::RoutingSearchResponseT<SIZE>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto routing_search_item_desc = std::make_shared<TypeDescriptionStruct>(
            ALIGN, IS_BIG_ENDIAN, "holo::map::RoutingSearchResponseT::RoutingSearchItem");
        (void)routing_search_item_desc->SetTemplates({}).SetMembers(
            {{"id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto routing_search_item_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)routing_search_item_sequence_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(routing_search_item_desc);

        auto routing_error_code_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::map::RoutingSearchResponseT::RoutingErrorCode");
        (void)routing_error_code_desc
            ->SetEnumerates({{0U, "NO_ERROR"},
                             {1U, "RETRIEVER_ERROR"},
                             {2U, "REQUEST_PARAM_ERROR"},
                             {3U, "REQUEST_POSITION_ERROR"},
                             {4U, "ROAD_CONNECT_ERROR"},
                             {5U, "FOUND_POI_ERROR"},
                             {6U, "FOUND_PARKING_SPACE"},
                             {7U, "FOUND_ROAD_ERROR"},
                             {8U, "FOUND_PARKING_LOT_ERROR"},
                             {9U, "FOUND_PARKING_FLOOR_ERROR"},
                             {10U, "OTHER_ERROR"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto routing_type_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::map::RoutingSearchResponseT::RoutingType");
        (void)routing_type_desc->SetEnumerates({{0U, "UNKNOWN"}, {1U, "LINK"}, {2U, "LANE"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto status_desc = std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN,
                                                                      "holo::map::RoutingSearchResponseT::Status");
        (void)status_desc->SetEnumerates({{0U, "UNKNOWN"}, {1U, "STARTING"}, {2U, "RUNNING"}, {3U, "YAWING"}, {4U, "ENDING"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto mode_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::map::RoutingSearchResponseT::Mode");
        (void)mode_desc->SetEnumerates({{0U, "UNKNOWN"}, {1U, "NAVIGATION"}, {2U, "CRUISE"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::RoutingSearchResponseT");
        (void)desc->SetTemplates({}).SetMembers(
            {{"routing_search_item", routing_search_item_sequence_desc},
             {"response_id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"total_count", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"start_index", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"error_code", routing_error_code_desc},
             {"routing_type", routing_type_desc},
             {"status", status_desc},
             {"mode", mode_desc},
             {"rolling_counter", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
