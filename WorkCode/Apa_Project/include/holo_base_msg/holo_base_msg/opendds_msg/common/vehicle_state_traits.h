#ifndef OPENDDS_MSG_COMMON_VEHICLE_STATE_TRAITS_H_
#define OPENDDS_MSG_COMMON_VEHICLE_STATE_TRAITS_H_

#include <holo/common/chassis_state.h>
#include <holo/common/vehicle_body_state.h>

#include <opendds_wrapper/traits.h>

#include <opendds_wrapper/builtin/BuiltinC.h>

#include <holo_base_msg/common/VehicleStateC.h>
#include <holo_base_msg/common/VehicleStateS.h>
#include <holo_base_msg/common/VehicleStateTypeSupportC.h>
#include <holo_base_msg/common/VehicleStateTypeSupportImpl.h>
#include <holo_base_msg/common/VehicleStateTypeSupportS.h>

namespace opendds_wrapper
{
/* Chassis state traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::ChassisState>
{
    using ValueType = ::holo_base_msg::common::ChassisState;
    using MessageType = ::holo_base_msg::common::ChassisState;
};

template <>
struct DefaultMessageTraits<::holo::common::ChassisState>
{
    using ValueType = ::holo::common::ChassisState;
    using MessageType = ::holo_base_msg::common::ChassisState;
};

template <>
struct DefaultConversionTraits<::holo::common::ChassisState>
{
    using ValueType   = ::holo::common::ChassisState;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.stamp.sec  = value.GetTimestamp().GetSec();
        message.stamp.nsec = value.GetTimestamp().GetNsec();

        message.vehicle_speed           = value.GetVehicleSpeed();
        message.front_left_wheel_speed  = value.GetFrontLeftWheelSpeed();
        message.front_right_wheel_speed = value.GetFrontRightWheelSpeed();
        message.rear_left_wheel_speed   = value.GetRearLeftWheelSpeed();
        message.rear_right_wheel_speed  = value.GetRearRightWheelSpeed();
        message.front_left_wheel_pulse  = value.GetFrontLeftWheelPulse();
        message.front_right_wheel_pulse = value.GetFrontRightWheelPulse();
        message.rear_left_wheel_pulse   = value.GetRearLeftWheelPulse();
        message.rear_right_wheel_pulse  = value.GetRearRightWheelPulse();
        message.lon_acceleration        = value.GetLongitudinalAcceleration();
        message.lat_acceleration        = value.GetLateralAcceleration();
        message.yaw_rate                = value.GetYawRate();
        message.front_wheel_angle       = value.GetFrontWheelAngle();
        message.longitudinal_control_value = value.GetLongitudinalControlValue();

        message.energy_source_level = value.GetEnergySourceLevel();
        message.gear_pos = static_cast<uint8_t>(value.GetGearPosition());
        message.gear_level = value.GetGearLevel();
        message.state_flags = value.GetStateValue();
        message.invalid_flags = value.GetInvalidFlagValue();
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetTimestamp({message.stamp.sec, message.stamp.nsec});

        value.SetVehicleSpeed(message.vehicle_speed);
        value.SetFrontLeftWheelSpeed(message.front_left_wheel_speed);
        value.SetFrontRightWheelSpeed(message.front_right_wheel_speed);
        value.SetRearLeftWheelSpeed(message.rear_left_wheel_speed);
        value.SetRearRightWheelSpeed(message.rear_right_wheel_speed);
        value.SetFrontLeftWheelPulse(message.front_left_wheel_pulse);
        value.SetFrontRightWheelPulse(message.front_right_wheel_pulse);
        value.SetRearLeftWheelPulse(message.rear_left_wheel_pulse);
        value.SetRearRightWheelPulse(message.rear_right_wheel_pulse);
        value.SetLongitudinalAcceleration(message.lon_acceleration);
        value.SetLateralAcceleration(message.lat_acceleration);
        value.SetYawRate(message.yaw_rate);
        value.SetFrontWheelAngle(message.front_wheel_angle);
        value.SetLongitudinalControlValue(message.longitudinal_control_value);
        value.SetEnergySourceLevel(message.energy_source_level);
        value.SetGearPosition(static_cast<::holo::common::ChassisState::GearPosition>(message.gear_pos));
        value.SetGearLevel(message.gear_level);
        value.SetStateValue(message.state_flags);
        value.SetInvalidFlagValue(message.invalid_flags);
    }
};

/* Vehicle body state traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::VehicleBodyState>
{
    using ValueType   = ::holo_base_msg::common::VehicleBodyState;
    using MessageType = ::holo_base_msg::common::VehicleBodyState;
};

template <>
struct DefaultMessageTraits<::holo::common::VehicleBodyState>
{
    using ValueType   = ::holo::common::VehicleBodyState;
    using MessageType = ::holo_base_msg::common::VehicleBodyState;
};

template <>
struct DefaultConversionTraits<::holo::common::VehicleBodyState>
{
    using ValueType   = ::holo::common::VehicleBodyState;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;
    static void Convert(ValueType const& value, MessageType& message)
    {
        message.stamp.sec                 = value.GetTimestamp().GetSec();
        message.stamp.nsec                = value.GetTimestamp().GetNsec();
        message.front_left_tire_pressure  = value.GetFrontLeftTirePressure();
        message.front_right_tire_pressure = value.GetFrontRightTirePressure();
        message.rear_left_tire_pressure   = value.GetRearLeftTirePressure();
        message.rear_right_tire_pressure  = value.GetRearRightTirePressure();
        message.state_flags               = value.GetStateValue();
        message.invalid_flags             = value.GetInvalidFlagValue();
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetTimestamp({message.stamp.sec, message.stamp.nsec});

        value.SetFrontLeftTirePressure(message.front_left_tire_pressure);
        value.SetFrontRightTirePressure(message.front_right_tire_pressure);
        value.SetRearLeftTirePressure(message.rear_left_tire_pressure);
        value.SetRearRightTirePressure(message.rear_right_tire_pressure);
        value.SetStateValue(message.state_flags);
        value.SetInvalidFlagValue(message.invalid_flags);
    }
};

}  // namespace opendds_wrapper

#endif
