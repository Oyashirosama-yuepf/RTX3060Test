#ifndef OPENDDS_MSG_PLANNING_PLANNING_STATE_H_
#define OPENDDS_MSG_PLANNING_PLANNING_STATE_H_

#include <holo/planning/state.h>
#include <opendds_wrapper/traits.h>

#include <holo_base_msg/planning/PlanningStateC.h>
#include <holo_base_msg/planning/PlanningStateS.h>
#include <holo_base_msg/planning/PlanningStateTypeSupportC.h>
#include <holo_base_msg/planning/PlanningStateTypeSupportImpl.h>
#include <holo_base_msg/planning/PlanningStateTypeSupportS.h>

namespace opendds_wrapper
{
/* Planning state traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::planning::State>
{
    using ValueType   = ::holo_base_msg::planning::State;
    using MessageType = ::holo_base_msg::planning::State;
};

template <>
struct DefaultMessageTraits<::holo::planning::State>
{
    using ValueType   = ::holo::planning::State;
    using MessageType = ::holo_base_msg::planning::State;
};

template <>
struct DefaultConversionTraits<::holo::planning::State>
{
    using ValueType   = ::holo::planning::State;
    using MessageType = ::holo_base_msg::planning::State;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.main_state         = static_cast<uint16_t>(value.GetMainState());
        message.longitudinal_state = static_cast<uint8_t>(value.GetLongitudinalState());
        message.lateral_state      = static_cast<uint8_t>(value.GetLateralState());
        message.functions.length(value.GetFunctionStateSize());

        for (size_t i = 0U; i < value.GetFunctionStateSize(); ++i)
        {
            auto p                     = value.GetFunctionState(i);
            message.functions[i].type  = static_cast<uint16_t>(p.first);
            message.functions[i].alarm = static_cast<uint16_t>(p.second);
        }

        // following obs ids
        message.following_obs_ids.length(value.GetFollowingObsIds().size());
        for (size_t i = 0; i < value.GetFollowingObsIds().size(); ++i)
        {
            message.following_obs_ids[i] = value.GetFollowingObsIds()[i];
        }

        // cut in obs ids
        message.cut_in_obs_ids.length(value.GetCutInObsIds().size());
        for (size_t i = 0; i < value.GetCutInObsIds().size(); ++i)
        {
            message.cut_in_obs_ids[i] = value.GetCutInObsIds()[i];
        }

        // avoiding obs ids
        message.avoiding_obs_ids.length(value.GetAvoidingObsIds().size());
        for (size_t i = 0; i < value.GetAvoidingObsIds().size(); ++i)
        {
            message.avoiding_obs_ids[i] = value.GetAvoidingObsIds()[i];
        }

        // lane change obs ids
        message.lane_change_obs_ids.length(value.GetLaneChangeObsIds().size());
        for (size_t i = 0; i < value.GetLaneChangeObsIds().size(); ++i)
        {
            message.lane_change_obs_ids[i] = value.GetLaneChangeObsIds()[i];
        }
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetMainState(static_cast<ValueType::MainState>(message.main_state));
        value.SetLongitudinalState(static_cast<ValueType::LongitudinalState>(message.longitudinal_state));
        value.SetLateralState(static_cast<ValueType::LateralState>(message.lateral_state));
        value.ClearFunctionState();
        for (size_t i = 0U; i < message.functions.length(); ++i)
        {
            value.SetFunctionAlarm(static_cast<ValueType::MainState>(message.functions[i].type),
                                   message.functions[i].alarm);
        }

        // following obs ids
        for (size_t i = 0; i < message.following_obs_ids.length(); ++i)
        {
            value.GetFollowingObsIds().push_back(message.following_obs_ids[i]);
        }

        // cut in obs ids
        for (size_t i = 0; i < message.cut_in_obs_ids.length(); ++i)
        {
            value.GetCutInObsIds().push_back(message.cut_in_obs_ids[i]);
        }

        // avoiding obs ids
        for (size_t i = 0; i < message.avoiding_obs_ids.length(); ++i)
        {
            value.GetAvoidingObsIds().push_back(message.avoiding_obs_ids[i]);
        }

        // lane change obs ids
        for (size_t i = 0; i < message.lane_change_obs_ids.length(); ++i)
        {
            value.GetLaneChangeObsIds().push_back(message.lane_change_obs_ids[i]);
        }
    }
};

}  // namespace opendds_wrapper

#endif
