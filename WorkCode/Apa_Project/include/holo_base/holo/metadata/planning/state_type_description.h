#ifndef HOLO_METADATA_PLANNING_STATE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_PLANNING_STATE_TYPE_DESCRIPTION_H_

#include <holo/metadata/common/alarm_type_description.h>
#include <holo/metadata/type_description.h>
#include <holo/planning/state.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::planning::State::MainState, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::planning::State::MainState");
        (void)desc->SetEnumerates({{0, "INACTIVE"},
             {1, "ACC"},
             {2, "ACC_HOLD"},
             {3, "ASSIST"},
             {4, "ASSIST_HOLD"},
             {5, "PILOT"},
             {6, "PILOT_HOLD"},
             {7, "LLC"},
             {8, "RLC"},
             {9, "SAFE_STOP"},
             {10, "STOP"},
             {11, "LKA"},
             {12, "LDW"}})
             .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::planning::State::LongitudinalState, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::planning::State::LongitudinalState");
        (void)desc->SetEnumerates({{0, "NOT_APPLICABLE"},
             {1, "ACCELERATE_SPEED"},
             {2, "UNIFORM_SPEED"},
             {3, "DECELERATE_SPEED"},
             {4, "BRAKE"},
             {5, "STANDSTILL"},
             {6, "OVERRIDE"},
             {7, "ABLE_TO_START"},
             {8, "UNABLE_TO_START"},
             {9, "ERROR"}})
             .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::planning::State::LateralState, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::planning::State::LateralState");
        (void)desc->SetEnumerates({{0, "NOT_APPLICABLE"},
             {1, "FOLLOW_LANE"},
             {2, "FOLLOW_VEHICLE"},
             {3, "FOLLOW_LEFT_BOUND"},
             {4, "FOLLOW_RIGHT_BOUND"},
             {5, "OBSTACLE_AVOIDENCE_LEFT"},
             {6, "OBSTACLE_AVOIDENCE_RIGHT"},
             {7, "OVERRIDE"},
             {8, "REQUEST_LANE_CHANGE_LEFT"},
             {9, "REQUEST_LANE_CHANGE_RIGHT"},
             {10, "PREPARE_LANE_CHANGE_LEFT"},
             {11, "PREPARE_LANE_CHANGE_RIGHT"},
             {12, "CANCEL_LANE_CHANGE_LEFT"},
             {13, "CANCEL_LANE_CHANGE_RIGHT"},
             {14, "LANE_CHANGE_LEFT"},
             {15, "LANE_CHANGE_RIGHT"},
             {16, "LANE_CORRECTION_LEFT"},
             {17, "LANE_CORRECTION_RIGHT"},
             {18, "ERROR"}})
        .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::planning::State::Function, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::planning::State::Function");
        (void)desc->SetTemplates({}).SetMembers({{"type", TypeDescriptionResolver<holo::planning::State::MainState, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"alarm", TypeDescriptionResolver<holo::common::Alarm, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::planning::State, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::planning::State");
        (void)desc->SetTemplates({}).SetMembers({{"main_state", TypeDescriptionResolver<holo::planning::State::MainState, ALIGN, IS_BIG_ENDIAN>::Get()},
                {"lateral_state",
                 TypeDescriptionResolver<holo::planning::State::LateralState, ALIGN, IS_BIG_ENDIAN>::Get()},
                {"longitudinal_state",
                 TypeDescriptionResolver<holo::planning::State::LongitudinalState, ALIGN, IS_BIG_ENDIAN>::Get()},
                {"functions",
                 TypeDescriptionResolver<holo::metadata::SequenceTag<holo::planning::State::Function, uint32_t>, ALIGN,
                                         IS_BIG_ENDIAN>::Get()},
                {"following_obs_ids",
                 TypeDescriptionResolver<holo::metadata::SequenceTag<uint32_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
                {"cut_in_obs_ids",
                 TypeDescriptionResolver<holo::metadata::SequenceTag<uint32_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
                {"avoiding_obs_ids",
                 TypeDescriptionResolver<holo::metadata::SequenceTag<uint32_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
                {"lane_change_obs_ids",
                 TypeDescriptionResolver<holo::metadata::SequenceTag<uint32_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif