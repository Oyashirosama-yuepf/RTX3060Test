#ifndef HOLO_IO_COMMON_COORDINATE_H_
#define HOLO_IO_COMMON_COORDINATE_H_

#include <vector>
#include <yaml-cpp/yaml.h>
#include <holo/common/coordinate.h>
#include <holo/io/common/sensor_id.h>
#include <holo/io/utils/utils.h>

namespace YAML
{
template <>
struct convert<holo::common::Coordinate>
{
    using ValueType = holo::common::Coordinate;
    using Type      = holo::common::Coordinate::Type;
    using SensorId  = holo::common::SensorId;

    static std::vector<std::pair<std::string, Type> > const& StringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, Type> > coordinate_type_str = {
            {"UNKNOWN", Type::UNKNOWN},
            {"VEHICLE", Type::VEHICLE},
            {"WGS84", Type::WGS84},
            {"UTM6", Type::UTM6},
            {"UTM3", Type::UTM3},
            {"DR", Type::DR},
            {"GCJ02", Type::GCJ02},
            {"CUSTOM0", Type::CUSTOM0},
            {"CUSTOM1", Type::CUSTOM1},
            {"CUSTOM2", Type::CUSTOM2},
            {"CUSTOM3", Type::CUSTOM3}
        };
        return coordinate_type_str;
    }

    static Node encode(ValueType const& rhs)
    {
        Node node;
        for (auto const& value : StringTypePairs())
        {
            if (value.second == rhs.GetType())
            {
                node["type"] = value.first;
                if (value.second == Type::VEHICLE)
                {
                    node["param"] = rhs.GetVehicleSensorId();
                }
                else if (value.second == Type::UTM6 || value.second == Type::UTM3)
                {
                    node["param"]["zone"]       = rhs.GetUtmZone();
                    node["param"]["south_flag"] = rhs.GetUtmSouthFlag();
                    node["param"]["offset_x"]   = rhs.GetUtmOffsetX();
                    node["param"]["offset_y"]   = rhs.GetUtmOffsetY();
                }
                else if (value.second == Type::DR)
                {
                    node["param"]["version"] = rhs.GetDrVersion();
                }
                else
                {
                    node["param"] = rhs.GetParam();
                }
            }
        }
        return node;
    };

    static void decodeParam(Node const& node, ValueType& rhs)
    {
        if (node["param"].Type() == YAML::NodeType::Scalar)
        {
            if (YAML::IsDigit(node["param"].as<std::string>()))
            {
                rhs.SetParam(node["param"].as<holo::uint32_t>());
            }
        }
        else if (node["param"].Type() == YAML::NodeType::Map)
        {
            if (rhs.GetType() == Type::VEHICLE)
            {
                rhs.SetVehicleSensorId(node["param"].as<SensorId>());
            }
            else if (rhs.GetType() == Type::UTM6 || rhs.GetType() == Type::UTM3)
            {
                rhs.SetUtmZone(static_cast<holo::uint8_t>(node["param"]["zone"].as<holo::uint16_t>()));
                rhs.SetUtmSouthFlag(node["param"]["south_flag"].as<holo::bool_t>());
                rhs.SetUtmOffsetX(node["param"]["offset_x"].as<holo::uint32_t>());
                rhs.SetUtmOffsetY(node["param"]["offset_y"].as<holo::uint32_t>());
            }
            else if (rhs.GetType() == Type::DR)
            {
                rhs.SetDrVersion(node["param"]["version"].as<holo::uint16_t>());
            }
        }
    };

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            if (node.Type() == YAML::NodeType::Scalar)
            {
                rhs = ValueType(node.as<uint32_t>());
            }
            else if (node.Type() == YAML::NodeType::Map)
            {
                bool type_flag = false;
                for (auto const& value : StringTypePairs())
                {
                    if (value.first == node["type"].as<std::string>())
                    {
                        rhs.SetType(static_cast<Type>(value.second));
                        decodeParam(node, rhs);
                        type_flag = true;
                    }
                }
                if(!type_flag)
                {
                    if (YAML::IsDigit(node["type"].as<std::string>()))
                    {
                        uint32_t coordinate_type = node["type"].as<uint32_t>();
                        rhs.SetType(static_cast<Type>(coordinate_type));
                        decodeParam(node, rhs);
                    }
                    else
                    {
                        return false;
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