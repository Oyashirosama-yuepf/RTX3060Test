#ifndef HOLO_IO_COMMON_VEHICLE_BODY_STATE_H_
#define HOLO_IO_COMMON_VEHICLE_BODY_STATE_H_

#include <holo/common/vehicle_body_state.h>
#include <holo/io/common/timestamp.h>
#include <holo/io/utils/utils.h>
#include <holo/utils/yaml.h>

namespace YAML
{
template <>
struct convert<holo::common::VehicleBodyState>
{
    using ValueType   = holo::common::VehicleBodyState;
    using State       = typename ValueType::State;
    using InvalidFlag = typename ValueType::InvalidFlag;
    using Timestamp   = holo::common::Timestamp;

    static std::vector<std::pair<std::string, State> > const& StateStringTypePairs() noexcept
    {
        static std::vector<std::pair<std::string, State> > state_map = {
            {"LEFT_TURN_SIGNAL_ON", State::LEFT_TURN_SIGNAL_ON},
            {"RIGHT_TURN_SIGNAL_ON", State::RIGHT_TURN_SIGNAL_ON},
            {"HARZARD_FLASHER_ON", State::HARZARD_FLASHER_ON},
            {"LOW_BEAM_ON", State::LOW_BEAM_ON},
            {"HIGH_BEAM_ON", State::HIGH_BEAM_ON},
            {"BRAKE_LIGHT_ON", State::BRAKE_LIGHT_ON},
            {"FRONT_FOG_LIGHT_ON", State::FRONT_FOG_LIGHT_ON},
            {"REAR_FOG_LIGHT_ON", State::REAR_FOG_LIGHT_ON},

            {"CHARGING_CAP_OPEN", State::CHARGING_CAP_OPEN},
            {"FAST_CHARGING_CAP_OPEN", State::FAST_CHARGING_CAP_OPEN},
            {"LEFT_REARVIEW_MIRROR_FOLD", State::LEFT_REARVIEW_MIRROR_FOLD},
            {"RIGHT_REARVIEW_MIRROR_FOLD", State::RIGHT_REARVIEW_MIRROR_FOLD},
            {"DRIVER_SEATBELT_UNLOCK", State::DRIVER_SEATBELT_UNLOCK},
            {"CODRIVER_SEATBELT_UNLOCK", State::CODRIVER_SEATBELT_UNLOCK},
            {"PASSENGER_SEATBELT_UNLOCK", State::PASSENGER_SEATBELT_UNLOCK},
            {"DRIVER_ABSENT", State::DRIVER_ABSENT},

            {"FRONT_WIPER_ON", State::FRONT_WIPER_ON},
            {"REAR_WIPER_ON", State::REAR_WIPER_ON},
            {"FRONT_LEFT_DOOR_OPEN", State::FRONT_LEFT_DOOR_OPEN},
            {"FRONT_RIGHT_DOOR_OPEN", State::FRONT_RIGHT_DOOR_OPEN},
            {"REAR_LEFT_DOOR_OPEN", State::REAR_LEFT_DOOR_OPEN},
            {"REAR_RIGHT_DOOR_OPEN", State::REAR_RIGHT_DOOR_OPEN},
            {"CAR_HOOD_OPEN", State::CAR_HOOD_OPEN},
            {"TRUNK_DOOR_OPEN", State::TRUNK_DOOR_OPEN},
            {"FRONT_LEFT_WINDOW_OPEN", State::FRONT_LEFT_WINDOW_OPEN},
            {"FRONT_RIGHT_WINDOW_OPEN", State::FRONT_RIGHT_WINDOW_OPEN},
            {"REAR_LEFT_WINDOW_OPEN", State::REAR_LEFT_WINDOW_OPEN},
            {"REAR_RIGHT_WINDOW_OPEN", State::REAR_RIGHT_WINDOW_OPEN},
            {"SUNROOF_WINDOW_OPEN", State::SUNROOF_WINDOW_OPEN},
            {"POWERTRAIN_NOT_READY", State::POWERTRAIN_NOT_READY}};
        return state_map;
    };

    static std::vector<std::pair<std::string, InvalidFlag> > const& InvalidFlagStringTypePairs() noexcept
    {
        static std::vector<std::pair<std::string, InvalidFlag> > invalid_flag_map = {
            {"LEFT_TURN_SIGNAL_INVALID", InvalidFlag::LEFT_TURN_SIGNAL_INVALID},
            {"RIGHT_TURN_SIGNAL_INVALID", InvalidFlag::RIGHT_TURN_SIGNAL_INVALID},
            {"HARZARD_FLASHER_INVALID", InvalidFlag::HARZARD_FLASHER_INVALID},
            {"LOW_BEAM_INVALID", InvalidFlag::LOW_BEAM_INVALID},
            {"HIGH_BEAM_INVALID", InvalidFlag::HIGH_BEAM_INVALID},
            {"BRAKE_LIGHT_INVALID", InvalidFlag::BRAKE_LIGHT_INVALID},
            {"FRONT_FOG_LIGHT_INVALID", InvalidFlag::FRONT_FOG_LIGHT_INVALID},
            {"REAR_FOG_LIGHT_INVALID", InvalidFlag::REAR_FOG_LIGHT_INVALID},

            {"CHARGING_CAP_INVALID", InvalidFlag::CHARGING_CAP_INVALID},
            {"FAST_CHARGING_CAP_INVALID", InvalidFlag::FAST_CHARGING_CAP_INVALID},
            {"LEFT_REARVIEW_MIRROR_FOLD", InvalidFlag::LEFT_REARVIEW_MIRROR_FOLD},
            {"RIGHT_REARVIEW_MIRROR_FOLD", InvalidFlag::RIGHT_REARVIEW_MIRROR_FOLD},
            {"DRIVER_SEATBELT_INVALID", InvalidFlag::DRIVER_SEATBELT_INVALID},
            {"CODRIVER_SEATBELT_INVALID", InvalidFlag::CODRIVER_SEATBELT_INVALID},
            {"PASSENGER_SEATBELT_INVALID", InvalidFlag::PASSENGER_SEATBELT_INVALID},
            {"DRIVER_ABSENT_INVALID", InvalidFlag::DRIVER_ABSENT_INVALID},

            {"FRONT_WIPER_INVALID", InvalidFlag::FRONT_WIPER_INVALID},
            {"REAR_WIPER_INVALID", InvalidFlag::REAR_WIPER_INVALID},
            {"FRONT_LEFT_DOOR_INVALID", InvalidFlag::FRONT_LEFT_DOOR_INVALID},
            {"FRONT_RIGHT_DOOR_INVALID", InvalidFlag::FRONT_RIGHT_DOOR_INVALID},
            {"REAR_LEFT_DOOR_INVALID", InvalidFlag::REAR_LEFT_DOOR_INVALID},
            {"REAR_RIGHT_DOOR_INVALID", InvalidFlag::REAR_RIGHT_DOOR_INVALID},
            {"CAR_HOOD_INVALID", InvalidFlag::CAR_HOOD_INVALID},
            {"TRUNK_DOOR_INVALID", InvalidFlag::TRUNK_DOOR_INVALID},
            {"FRONT_LEFT_WINDOW_INVALID", InvalidFlag::FRONT_LEFT_WINDOW_INVALID},
            {"FRONT_RIGHT_WINDOW_INVALID", InvalidFlag::FRONT_RIGHT_WINDOW_INVALID},
            {"REAR_LEFT_WINDOW_INVALID", InvalidFlag::REAR_LEFT_WINDOW_INVALID},
            {"REAR_RIGHT_WINDOW_INVALID", InvalidFlag::REAR_RIGHT_WINDOW_INVALID},
            {"SUNROOF_WINDOW_INVALID", InvalidFlag::SUNROOF_WINDOW_INVALID},
            {"POWERTRAIN_INVALID", InvalidFlag::POWERTRAIN_INVALID}};
        return invalid_flag_map;
    };

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["timestamp"]                 = rhs.GetTimestamp();
        node["front_left_tire_pressure"]  = rhs.GetFrontLeftTirePressure();
        node["front_right_tire_pressure"] = rhs.GetFrontRightTirePressure();
        node["rear_left_tire_pressure"]   = rhs.GetRearLeftTirePressure();
        node["rear_right_tire_pressure"]  = rhs.GetRearRightTirePressure();

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
    };

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetTimestamp(node["timestamp"].as<Timestamp>());
            rhs.SetFrontLeftTirePressure(node["front_left_tire_pressure"].as<holo::float32_t>());
            rhs.SetFrontRightTirePressure(node["front_right_tire_pressure"].as<holo::float32_t>());
            rhs.SetRearLeftTirePressure(node["rear_left_tire_pressure"].as<holo::float32_t>());
            rhs.SetRearRightTirePressure(node["rear_right_tire_pressure"].as<holo::float32_t>());

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
    };
};
}  // namespace YAML

#endif