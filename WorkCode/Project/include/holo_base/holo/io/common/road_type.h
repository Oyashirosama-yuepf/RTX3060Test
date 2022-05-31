#ifndef HOLO_IO_COMMON_ROAD_TYPE_H_
#define HOLO_IO_COMMON_ROAD_TYPE_H_

#include <holo/common/road_type.h>
#include <holo/io/utils/utils.h>
#include <holo/utils/yaml.h>

namespace YAML
{
/**
 * @deprecated Use convert<holo::common::RoadCategory> instead
 */
template <>
struct [[deprecated]] convert<holo::common::RoadType> {
    using ValueType = holo::common::RoadType;

    static std::vector<std::pair<std::string, holo::uint16_t> > const& TypeStringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, holo::uint16_t> > type_type_str = {
            {"UNKNOWN", 0}, {"MAINROAD", 1}, {"RAMP", 2}};
        return type_type_str;
    };

    static std::vector<std::pair<std::string, holo::uint32_t> > const& TagStringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, holo::uint32_t> > tag_type_str = {{"TUNNEL", 0x01},
                                                                                          {"TOLL", 0x02}};
        return tag_type_str;
    };

    static Node encode(ValueType const& rhs)
    {
        Node node;

        if (rhs.IsTypeUnknown())
        {
            node["type"] = "UNKNOWN";
        }
        else if (rhs.IsTypeMainRoad())
        {
            node["type"] = "MAINROAD";
        }
        else if (rhs.IsTypeRamp())
        {
            node["type"] = "RAMP";
        }

        if (rhs.HasTagTunnel())
        {
            node["tags"].push_back("TUNNEL");
        }
        if (rhs.HasTagToll())
        {
            node["tags"].push_back("TOLL");
        }

        return node;
    };

    static void SetTypeValue(ValueType & rhs, std::string type)
    {
        if (type == "UNKNOWN")
        {
            rhs.SetTypeUnknown();
        }
        else if (type == "MAINROAD")
        {
            rhs.SetTypeMainRoad();
        }
        else if (type == "RAMP")
        {
            rhs.SetTypeRamp();
        }
    };

    static void SetTagValue(ValueType & rhs, std::string tag)
    {
        if (tag == "TUNNEL")
        {
            rhs.SetTagTunnel();
        }
        if (tag == "TOLL")
        {
            rhs.SetTagToll();
        }
    };

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            if (node.Type() == YAML::NodeType::Scalar)
            {
                if (YAML::IsDigit(node.as<std::string>()))
                {
                    rhs = ValueType(node.as<holo::uint32_t>());
                }
            }
            else if (node.Type() == YAML::NodeType::Map)
            {
                if (node["type"].Type() == YAML::NodeType::Scalar)
                {
                    if (YAML::IsDigit(node["type"].as<std::string>()))
                    {
                        for (auto const& value : TypeStringTypePairs())
                        {
                            if (value.second == node["type"].as<holo::uint16_t>())
                            {
                                SetTypeValue(rhs, value.first);
                            }
                        }
                    }
                    else
                    {
                        SetTypeValue(rhs, node["type"].as<std::string>());
                    }
                }

                rhs.ResetTagTunnel();
                rhs.ResetTagToll();
                if (node["tags"].Type() == YAML::NodeType::Sequence)
                {
                    for (std::size_t i = 0; i < node["tags"].size(); i++)
                    {
                        if (YAML::IsDigit(node["tags"][i].as<std::string>()))
                        {
                            for (auto const& value : TagStringTypePairs())
                            {
                                if (value.second == node["tags"][i].as<std::uint32_t>())
                                {
                                    SetTagValue(rhs, value.first);
                                }
                            }
                        }
                        else
                        {
                            SetTagValue(rhs, node["tags"][i].as<std::string>());
                        }
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

/**
 * @deprecated Use convert<holo::common::LaneCategory> instead
 */
template <>
struct [[deprecated]] convert<holo::common::LaneType> {
    using ValueType = holo::common::LaneType;

    static std::vector<std::pair<std::string, holo::uint16_t> > const& TypeStringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, holo::uint16_t> > type_type_str = {
            {"UNKNOWN", 0}, {"REGULAR", 1}, {"ACCELERATION", 2}, {"DECELERATION", 3}, {"EMERGENCY", 4}};
        return type_type_str;
    };

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["tags"] = rhs.GetValue() & 0x0fff;

        if (rhs.IsTypeUnknown())
        {
            node["type"] = "UNKNOWN";
        }
        else if (rhs.IsTypeRegular())
        {
            node["type"] = "REGULAR";
        }
        else if (rhs.IsTypeAcceleration())
        {
            node["type"] = "ACCELERATION";
        }
        else if (rhs.IsTypeDeceleration())
        {
            node["type"] = "DECELERATION";
        }
        else if (rhs.IsTypeEmergency())
        {
            node["type"] = "EMERGENCY";
        }
        return node;
    }

    static void SetTypeValue(ValueType & rhs, std::string type)
    {
        if (type == "UNKNOWN")
        {
            rhs.SetTypeUnknown();
        }
        else if (type == "REGULAR")
        {
            rhs.SetTypeRegular();
        }
        else if (type == "ACCELERATION")
        {
            rhs.SetTypeAcceleration();
        }
        else if (type == "DECELERATION")
        {
            rhs.SetTypeDeceleration();
        }
        else if (type == "EMERGENCY")
        {
            rhs.SetTypeEmergency();
        }
    };

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            if (node.Type() == YAML::NodeType::Scalar)
            {
                if (YAML::IsDigit(node.as<std::string>()))
                {
                    rhs = ValueType(node.as<holo::uint32_t>());
                }
            }
            else if (node.Type() == YAML::NodeType::Map)
            {
                rhs.SetValue(node["tags"].as<holo::uint32_t>());

                if (node["type"].Type() == YAML::NodeType::Scalar)
                {
                    if (YAML::IsDigit(node["type"].as<std::string>()))
                    {
                        for (auto const& value : TypeStringTypePairs())
                        {
                            if (value.second == node["type"].as<holo::uint16_t>())
                            {
                                SetTypeValue(rhs, value.first);
                            }
                        }
                    }
                    else
                    {
                        SetTypeValue(rhs, node["type"].as<std::string>());
                    }
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
