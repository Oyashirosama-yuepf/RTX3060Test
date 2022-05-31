#ifndef HOLO_METADATA_MAP_ROAD_SPEED_LIMITS_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_MAP_ROAD_SPEED_LIMITS_TYPE_DESCRIPTION_H_

#include <holo/map/road_speed_limits.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t LANES, size_t SEGS, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::details::RoadSpeedLimits<LANES, SEGS>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto speed_limit_segment_desc = std::make_shared<TypeDescriptionStruct>(
            ALIGN, IS_BIG_ENDIAN, "holo::map::RoadSpeedLimits::SpeedLimitSegment");
        (void)speed_limit_segment_desc->SetTemplates({}).SetMembers(
            {{"start_distance", TypeDescriptionResolver<::holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"end_distance", TypeDescriptionResolver<::holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"min_speed", TypeDescriptionResolver<::holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"max_speed", TypeDescriptionResolver<::holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto speed_limit_segment_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)speed_limit_segment_sequence_desc->SetSize(TypeDescriptionResolver<uint8_t>::Get())
            .SetElementType(speed_limit_segment_desc);

        auto lane_speed_limits_desc = std::make_shared<TypeDescriptionStruct>(
            ALIGN, IS_BIG_ENDIAN, "holo::map::RoadSpeedLimits::LaneSpeedLimits");
        (void)lane_speed_limits_desc->SetTemplates({}).SetMembers(
            {{"lane_index", TypeDescriptionResolver<::holo::int8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"speed_limits", speed_limit_segment_sequence_desc}});

        auto lane_speed_limits_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)lane_speed_limits_sequence_desc->SetSize(TypeDescriptionResolver<uint32_t>::Get())
            .SetElementType(lane_speed_limits_desc);

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::RoadSpeedLimits");
        (void)desc->SetTemplates({}).SetMembers({{"lanes", lane_speed_limits_sequence_desc}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif