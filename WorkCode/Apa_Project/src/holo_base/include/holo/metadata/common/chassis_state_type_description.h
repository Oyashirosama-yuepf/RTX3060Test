#ifndef HOLO_METADATA_COMMON_CHASSIS_STATE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_CHASSIS_STATE_TYPE_DESCRIPTION_H_

#include <holo/common/details/chassis_state.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::details::ChassisState, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto gear_position_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::common::ChassisState::GearPosition");
        (void)gear_position_desc
            ->SetEnumerates({{0, "UNKNOWN"}, {1, "P"}, {2, "R"}, {3, "N"}, {4, "D"}, {5, "S"}, {6, "INVALID"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto state_desc = std::make_shared<TypeDescriptionBitmask>(ALIGN, IS_BIG_ENDIAN,
                                                                   "holo::common::details::ChassisState::State");
        (void)state_desc
            ->SetBits({{0, "HAND_BRAKE_HOLD"},
                       {1, "LATERAL_TAKEOVER"},
                       {2, "LATERAL_INACTIVE"},
                       {3, "LONGITUDINAL_TAKEOVER"},
                       {4, "LONGITUDINAL_INACTIVE"},
                       {5, "GEAR_ACTUATOR_INACTIVE"},
                       {6, "GEAR_ACTUATOR_NOT_READY"},
                       {7, "LATERAL_ACTUATOR_INACTIVE"},
                       {8, "LATERAL_ACTUATOR_NOT_READY"},
                       {9, "LONGITUDINAL_ACTUATOR_INACTIVE"},
                       {10, "LONGITUDINAL_ACTUATOR_NOT_READY"},
                       {11, "VEHICLE_MOVE_BACKWARD"},
                       {12, "VEHICLE_STANDSTILL"},
                       {13, "VEHICLE_SLIDE"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto invalid_flag_desc = std::make_shared<TypeDescriptionBitmask>(
            ALIGN, IS_BIG_ENDIAN, "holo::common::details::ChassisState::InvalidFlag");
        (void)invalid_flag_desc
            ->SetBits({{0, "VEHICLE_SPEED_INVALID"},
                       {1, "FL_WHEEL_SPEED_INVALID"},
                       {2, "FR_WHEEL_SPEED_INVALID"},
                       {3, "RL_WHEEL_SPEED_INVALID"},
                       {4, "RR_WHEEL_SPEED_INVALID"},
                       {5, "FL_WHEEL_PULSE_INVALID"},
                       {6, "FR_WHEEL_PULSE_INVALID"},
                       {7, "RL_WHEEL_PULSE_INVALID"},
                       {8, "RR_WHEEL_PULSE_INVALID"},
                       {9, "FRONT_WHEEL_ANGLE_INVALID"},
                       {10, "LONGITUDINAL_CONTROL_VALUE_INVALID"},
                       {11, "BRAKE_INVALID"},
                       {12, "GEAR_ACTUATOR_INVALID"},
                       {13, "LATERAL_ACTUATOR_INVALID"},
                       {14, "LONGITUDINAL_ACTUATOR_INVALID"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::details::ChassisState");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"vehicle_speed", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"front_left_wheel_speed", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"front_right_wheel_speed", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"rear_left_wheel_speed", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"rear_right_wheel_speed", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"front_left_wheel_pulse", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"front_right_wheel_pulse", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"rear_left_wheel_pulse", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"rear_right_wheel_pulse", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"longitudinal_acceleration", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lateral_acceleration", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"yaw_rate", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"front_wheel_angle", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"longitudinal_control_value", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"energy_source_level", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"gear_position", gear_position_desc},
             {"gear_level", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"state_flags", state_desc},
             {"invalid_flags", invalid_flag_desc}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
