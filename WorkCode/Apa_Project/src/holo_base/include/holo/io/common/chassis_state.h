#ifndef HOLO_IO_COMMON_CHASSIS_STATE_H_
#define HOLO_IO_COMMON_CHASSIS_STATE_H_

#include <holo/common/chassis_state.h>
#include <holo/io/common/timestamp.h>
#include <holo/io/utils/utils.h>
#include <holo/utils/yaml.h>

namespace YAML
{
template <>
struct convert<holo::common::ChassisState>
{
    using ValueType    = holo::common::ChassisState;
    using GearPosition = typename ValueType::GearPosition;
    using State        = typename ValueType::State;
    using InvalidFlag  = typename ValueType::InvalidFlag;

    using Timestamp = holo::common::Timestamp;

    static std::vector<std::pair<std::string, GearPosition> > const& GearPositionStringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, GearPosition> > gear_type_str = {
            {"UNKNOWN", GearPosition::UNKNOWN},
            {"P", GearPosition::P},
            {"R", GearPosition::R},
            {"N", GearPosition::N},
            {"D", GearPosition::D},
            {"S", GearPosition::S},
            {"INVALID", GearPosition::INVALID}};
        return gear_type_str;
    };

    static std::vector<std::pair<std::string, State> > const& StateStringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, State> > state_type_str = {
            {"HAND_BRAKE_HOLD", State::HAND_BRAKE_HOLD},
            {"LATERAL_TAKEOVER", State::LATERAL_TAKEOVER},
            {"LATERAL_INACTIVE", State::LATERAL_INACTIVE},
            {"LONGITUDINAL_TAKEOVER", State::LONGITUDINAL_TAKEOVER},
            {"LONGITUDINAL_INACTIVE", State::LONGITUDINAL_INACTIVE},
            {"GEAR_ACTUATOR_INACTIVE", State::GEAR_ACTUATOR_INACTIVE},
            {"GEAR_ACTUATOR_NOT_READY", State::GEAR_ACTUATOR_NOT_READY},
            {"LATERAL_ACTUATOR_INACTIVE", State::LATERAL_ACTUATOR_INACTIVE},
            {"LATERAL_ACTUATOR_NOT_READY", State::LATERAL_ACTUATOR_NOT_READY},
            {"LONGITUDINAL_ACTUATOR_INACTIVE", State::LONGITUDINAL_ACTUATOR_INACTIVE},
            {"LONGITUDINAL_ACTUATOR_NOT_READY", State::LONGITUDINAL_ACTUATOR_NOT_READY},
            {"VEHICLE_MOVE_BACKWARD", State::VEHICLE_MOVE_BACKWARD},
            {"VEHICLE_STANDSTILL", State::VEHICLE_STANDSTILL},
            {"VEHICLE_SLIDE", State::VEHICLE_SLIDE}};
        return state_type_str;
    };

    static std::vector<std::pair<std::string, InvalidFlag> > const& InvalidFlagStringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, InvalidFlag> > invalid_type_str = {
            {"VEHICLE_SPEED_INVALID", InvalidFlag::VEHICLE_SPEED_INVALID},
            {"FL_WHEEL_SPEED_INVALID", InvalidFlag::FL_WHEEL_SPEED_INVALID},
            {"FR_WHEEL_SPEED_INVALID", InvalidFlag::FR_WHEEL_SPEED_INVALID},
            {"RL_WHEEL_SPEED_INVALID", InvalidFlag::RL_WHEEL_SPEED_INVALID},
            {"RR_WHEEL_SPEED_INVALID", InvalidFlag::RR_WHEEL_SPEED_INVALID},
            {"FL_WHEEL_PULSE_INVALID", InvalidFlag::FL_WHEEL_PULSE_INVALID},
            {"FR_WHEEL_PULSE_INVALID", InvalidFlag::FR_WHEEL_PULSE_INVALID},
            {"RL_WHEEL_PULSE_INVALID", InvalidFlag::RL_WHEEL_PULSE_INVALID},
            {"RR_WHEEL_PULSE_INVALID", InvalidFlag::RR_WHEEL_PULSE_INVALID},
            {"FRONT_WHEEL_ANGLE_INVALID", InvalidFlag::FRONT_WHEEL_ANGLE_INVALID},
            {"LONGITUDINAL_CONTROL_VALUE_INVALID", InvalidFlag::LONGITUDINAL_CONTROL_VALUE_INVALID},
            {"BRAKE_INVALID", InvalidFlag::BRAKE_INVALID},
            {"GEAR_ACTUATOR_INVALID", InvalidFlag::GEAR_ACTUATOR_INVALID},
            {"LATERAL_ACTUATOR_INVALID", InvalidFlag::LATERAL_ACTUATOR_INVALID},
            {"LONGITUDINAL_ACTUATOR_INVALID", InvalidFlag::LONGITUDINAL_ACTUATOR_INVALID},
        };
        return invalid_type_str;
    };

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["timestamp"]                 = rhs.GetTimestamp();
        node["vehicle_speed"]             = rhs.GetVehicleSpeed();
        node["front_left_wheel_speed"]    = rhs.GetFrontLeftWheelSpeed();
        node["front_right_wheel_speed"]   = rhs.GetFrontRightWheelSpeed();
        node["rear_left_wheel_speed"]     = rhs.GetRearLeftWheelSpeed();
        node["rear_right_wheel_speed"]    = rhs.GetRearRightWheelSpeed();
        node["front_left_wheel_pulse"]    = rhs.GetFrontLeftWheelPulse();
        node["front_right_wheel_pulse"]   = rhs.GetFrontRightWheelPulse();
        node["rear_left_wheel_pulse"]     = rhs.GetRearLeftWheelPulse();
        node["rear_right_wheel_pulse"]    = rhs.GetRearRightWheelPulse();
        node["longitudinal_acceleration"] = rhs.GetLongitudinalAcceleration();

        node["lateral_acceleration"]       = rhs.GetLateralAcceleration();
        node["yaw_rate"]                   = rhs.GetYawRate();
        node["front_wheel_angle"]          = rhs.GetFrontWheelAngle();
        node["longitudinal_control_value"] = rhs.GetLongitudinalControlValue();
        node["energy_source_level"]        = static_cast<holo::uint16_t>(rhs.GetEnergySourceLevel());
        node["gear_level"]                 = static_cast<holo::uint16_t>(rhs.GetGearLevel());

        for (auto const& value : GearPositionStringTypePairs())
        {
            if (value.second == rhs.GetGearPosition())
            {
                node["gear_position"] = value.first;
            }
        }

        for (auto const& value : StateStringTypePairs())
        {
            if (rhs.IsStateSet(value.second))
            {
                node["states"].push_back(value.first);
            }
        }

        for (auto const& value : InvalidFlagStringTypePairs())
        {
            if (rhs.IsInvalidFlagSet(value.second))
            {
                node["invalid_flags"].push_back(value.first);
            }
        }

        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetTimestamp(node["timestamp"].as<Timestamp>());
            rhs.SetVehicleSpeed(node["vehicle_speed"].as<holo::float32_t>());
            rhs.SetFrontLeftWheelSpeed(node["front_left_wheel_speed"].as<holo::float32_t>());
            rhs.SetFrontRightWheelSpeed(node["front_right_wheel_speed"].as<holo::float32_t>());
            rhs.SetRearLeftWheelSpeed(node["rear_left_wheel_speed"].as<holo::float32_t>());
            rhs.SetRearRightWheelSpeed(node["rear_right_wheel_speed"].as<holo::float32_t>());
            rhs.SetFrontLeftWheelPulse(node["front_left_wheel_pulse"].as<holo::uint32_t>());
            rhs.SetFrontRightWheelPulse(node["front_right_wheel_pulse"].as<holo::uint32_t>());
            rhs.SetRearLeftWheelPulse(node["rear_left_wheel_pulse"].as<holo::uint32_t>());
            rhs.SetRearRightWheelPulse(node["rear_right_wheel_pulse"].as<holo::uint32_t>());
            rhs.SetLongitudinalAcceleration(node["longitudinal_acceleration"].as<holo::float32_t>());
            rhs.SetLateralAcceleration(node["lateral_acceleration"].as<holo::float32_t>());
            rhs.SetYawRate(node["yaw_rate"].as<holo::float32_t>());
            rhs.SetFrontWheelAngle(node["front_wheel_angle"].as<holo::float32_t>());
            rhs.SetLongitudinalControlValue(node["longitudinal_control_value"].as<holo::float32_t>());
            rhs.SetEnergySourceLevel(node["energy_source_level"].as<holo::uint16_t>());
            rhs.SetGearLevel(node["gear_level"].as<holo::uint16_t>());

            bool gear_position_flag = false;
            for (auto const& value : GearPositionStringTypePairs())
            {
                if (value.first == node["gear_position"].as<std::string>())
                {
                    rhs.SetGearPosition(value.second);
                    gear_position_flag = true;
                }
            }
            if (!gear_position_flag)
            {
                if (IsDigit(node["gear_position"].as<std::string>()))
                {
                    GearPosition gear_position = static_cast<GearPosition>(node["gear_position"].as<holo::uint16_t>());
                    rhs.SetGearPosition(gear_position);
                }
                else
                {
                    return false;
                }
            }

            rhs.SetStateValue(0x00);
            if (node["states"].Type() == YAML::NodeType::Sequence)
            {
                for (std::size_t i = 0; i < node["states"].size(); i++)
                {
                    if (YAML::IsDigit(node["states"][i].as<std::string>()))
                    {
                        rhs.SetState(node["states"][i].as<holo::uint32_t>());
                    }
                    else
                    {
                        for (auto const& value : StateStringTypePairs())
                        {
                            if (value.first == node["states"][i].as<std::string>())
                            {
                                rhs.SetState(value.second);
                            }
                        }
                    }
                }
            }
            else if (node["states"].Type() == YAML::NodeType::Scalar)
            {
                if (YAML::IsDigit(node["states"].as<std::string>()))
                {
                    rhs.SetStateValue(node["states"].as<holo::uint32_t>());
                }
            }

            rhs.SetInvalidFlagValue(0x00);
            if (node["invalid_flags"].Type() == YAML::NodeType::Sequence)
            {
                for (std::size_t i = 0; i < node["invalid_flags"].size(); i++)
                {
                    if (YAML::IsDigit(node["invalid_flags"][i].as<std::string>()))
                    {
                        rhs.SetInvalidFlag(node["invalid_flags"][i].as<holo::uint32_t>());
                    }
                    else
                    {
                        for (auto const& value : InvalidFlagStringTypePairs())
                        {
                            if (value.first == node["invalid_flags"][i].as<std::string>())
                            {
                                rhs.SetInvalidFlag(value.second);
                            }
                        }
                    }
                }
            }
            else if (node["invalid_flags"].Type() == YAML::NodeType::Scalar)
            {
                if (YAML::IsDigit(node["invalid_flags"].as<std::string>()))
                {
                    rhs.SetInvalidFlagValue(node["invalid_flags"].as<holo::uint32_t>());
                }
            }

            return true;
        }
        catch (...)
        {
            return false;
        }
    }
};
}  // namespace YAML

#endif