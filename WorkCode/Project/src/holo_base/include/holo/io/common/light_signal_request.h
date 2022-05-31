#ifndef HOLO_IO_COMMON_LIGHT_SIGNAL_REQUEST_H_
#define HOLO_IO_COMMON_LIGHT_SIGNAL_REQUEST_H_

#include <holo/common/light_signal_request.h>
#include <holo/io/common/timestamp.h>
#include <holo/io/utils/utils.h>

namespace YAML
{
template <>
struct convert<holo::LightSignalRequest>
{
    using ValueType = holo::LightSignalRequest;
    using Timestamp = holo::common::Timestamp;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["timestamp"] = rhs.GetTimestamp();

        if (rhs.GetBrakeLight())
        {
            node["light_command"].push_back("brake_light");
        }
        if (rhs.GetHazardFlasher())
        {
            node["light_command"].push_back("hazard_flasher");
        }
        if (rhs.GetRightTurnSignal())
        {
            node["light_command"].push_back("right_turn_signal");
        }
        if (rhs.GetLeftTurnSignal())
        {
            node["light_command"].push_back("left_turn_signal");
        }
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetTimestamp(node["timestamp"].as<Timestamp>());
            rhs.SetLightCommand(0x00);
            if (node["light_command"].Type() == YAML::NodeType::Scalar)
            {
                rhs.SetLightCommand(node["light_command"].as<holo::uint16_t>());
            }
            else if (node["light_command"].Type() == YAML::NodeType::Sequence)
            {
                for (std::size_t i = 0; i < node["light_command"].size(); i++)
                {
                    if (node["light_command"][i].as<std::string>() == "brake_light")
                    {
                        rhs.SetBrakeLight(true);
                    }
                    if (node["light_command"][i].as<std::string>() == "hazard_flasher")
                    {
                        rhs.SetHazardFlasher(true);
                    }
                    if (node["light_command"][i].as<std::string>() == "right_turn_signal")
                    {
                        rhs.SetRightTurnSignal(true);
                    }
                    if (node["light_command"][i].as<std::string>() == "left_turn_signal")
                    {
                        rhs.SetLeftTurnSignal(true);
                    }
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
