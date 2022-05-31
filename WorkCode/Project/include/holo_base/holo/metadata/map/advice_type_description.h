#ifndef HOLO_METADATA_MAP_ADVICE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_MAP_ADVICE_TYPE_DESCRIPTION_H_

#include <holo/geometry/curve.h>
#include <holo/map/advice.h>
#include <holo/metadata/common/road_frame_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/geometry/curve_type_description.h>
#include <holo/metadata/geometry/point3_type_description.h>
#include <holo/metadata/map/road_speed_limits_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::CrossingInfo, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::CrossingInfo");
        (void)desc->SetTemplates({}).SetMembers(
            {{"type", TypeDescriptionResolver<::holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"distance", TypeDescriptionResolver<::holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::TargetLinkAdviceType, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::TargetLinkAdviceType");
        (void)desc->SetTemplates({}).SetMembers(
            {{"type", TypeDescriptionResolver<::holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"distance_to_start", TypeDescriptionResolver<::holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"distance_to_end", TypeDescriptionResolver<::holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"confidence", TypeDescriptionResolver<::holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"link_id", TypeDescriptionResolver<::holo::uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::TargetLinkAdviceGroupType, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::TargetLinkAdviceGroupType");
        (void)desc->SetTemplates({}).SetMembers(
            {{"advices", TypeDescriptionResolver<holo::metadata::SequenceTag<holo::map::TargetLinkAdviceType, uint32_t>,
                                                 ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::TargetLaneAdviceType, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::TargetLaneAdviceType");
        (void)desc->SetTemplates({}).SetMembers(
            {{"type_with_left", TypeDescriptionResolver<::holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"type_with_right", TypeDescriptionResolver<::holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"type_with_current", TypeDescriptionResolver<::holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lane_type", TypeDescriptionResolver<::holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lane_id", TypeDescriptionResolver<::holo::uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"valid", TypeDescriptionResolver<::holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::TargetLaneAdviceGroupType, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::TargetLaneAdviceGroupType");
        (void)desc->SetTemplates({}).SetMembers(
            {{"link_id", TypeDescriptionResolver<::holo::uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"link_type", TypeDescriptionResolver<::holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"confidence", TypeDescriptionResolver<::holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"left_lane_advice",
              TypeDescriptionResolver<::holo::map::TargetLaneAdviceType, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"right_lane_advice",
              TypeDescriptionResolver<::holo::map::TargetLaneAdviceType, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"current_lane_advice",
              TypeDescriptionResolver<::holo::map::TargetLaneAdviceType, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::Advice, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        size_t const MAX_KNOT_NUMBER   = 0U;
        size_t const ROAD_FRAME_DEGREE = 3U;
        size_t const MAX_CURVE_NUMBER  = 256U;

        auto road_frame_type_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::RoadFrame");
        (void)road_frame_type_desc->SetTemplates({}).SetMembers(
            {{"road_frame_type",
              TypeDescriptionResolver<
                  holo::common::RoadFrame<
                      holo::geometry::CurveExplicit<holo::geometry::Point3d, MAX_KNOT_NUMBER,
                                                    holo::geometry::details::CurvePolynomial<
                                                        holo::geometry::Point3d, MAX_KNOT_NUMBER, ROAD_FRAME_DEGREE>>,
                      MAX_CURVE_NUMBER>,
                  ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::Advice");
        (void)desc->SetTemplates({}).SetMembers(
            {{"valid_indicator_size", TypeDescriptionResolver<::holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"valid_uint32_size", TypeDescriptionResolver<::holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"valid_float32_size_", TypeDescriptionResolver<::holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"indicators", TypeDescriptionResolver<::holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"uint32_values", TypeDescriptionResolver<holo::metadata::SequenceTag<::holo::uint32_t, uint32_t>, ALIGN,
                                                       IS_BIG_ENDIAN>::Get()},
             {"float32_values", TypeDescriptionResolver<holo::metadata::SequenceTag<::holo::float32_t, uint32_t>, ALIGN,
                                                        IS_BIG_ENDIAN>::Get()},

             {"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"crossing_sequence_list", TypeDescriptionResolver<holo::metadata::SequenceTag<::holo::int8_t, uint32_t>,
                                                                ALIGN, IS_BIG_ENDIAN>::Get()},
             {"current_lane_seq_list", TypeDescriptionResolver<holo::metadata::SequenceTag<::holo::int8_t, uint32_t>,
                                                               ALIGN, IS_BIG_ENDIAN>::Get()},
             {"vec_crossing_info",
              TypeDescriptionResolver<holo::metadata::SequenceTag<holo::map::CrossingInfo, uint32_t>, ALIGN,
                                      IS_BIG_ENDIAN>::Get()},
             {"link_advices",
              TypeDescriptionResolver<holo::map::TargetLinkAdviceGroupType, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lane_advices",
              TypeDescriptionResolver<holo::map::TargetLaneAdviceGroupType, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"road_speed_limits",
              TypeDescriptionResolver<holo::map::details::RoadSpeedLimits<9U, 4U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"logic_graph", road_frame_type_desc}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif