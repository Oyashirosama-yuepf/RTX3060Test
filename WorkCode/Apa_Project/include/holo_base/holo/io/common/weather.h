#ifndef HOLO_IO_COMMON_WEATHER_H_
#define HOLO_IO_COMMON_WEATHER_H_

#include <yaml-cpp/yaml.h>
#include <holo/io/utils/utils.h>
#include <holo/common/weather.h>
#include <holo/io/common/timestamp.h>

namespace YAML
{
template <>
struct convert<holo::common::Weather>
{
    using ValueType = holo::common::Weather;
    using Timestamp = holo::common::Timestamp;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["timestamp"]                     = rhs.GetTimestamp();
        node["weather_category"]["cloudy"]    = rhs.IsCloudy();
        node["weather_category"]["rainfall"]  = rhs.GetRainFall();
        node["weather_category"]["snowfall"]  = rhs.GetSnowFall();
        node["weather_category"]["foggy_vis"] = rhs.GetFoggyVisibility();
        node["weather_category"]["sandy_vis"] = rhs.GetSandyVisibility();
        return node;
    };

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetTimestamp(node["timestamp"].as<Timestamp>());
            if (node["weather_category"].Type() == YAML::NodeType::Scalar)
            {
                if (IsDigit(node["weather_category"].as<std::string>()))
                {
                    rhs.SetAllWeather(node["weather_category"].as<holo::uint32_t>());
                }
            }
            else if (node["weather_category"].Type() == YAML::NodeType::Map)
            {
                rhs.SetCloudy(node["weather_category"]["cloudy"].as<holo::bool_t>());
                rhs.SetRainFall(node["weather_category"]["rainfall"].as<holo::uint32_t>());
                rhs.SetSnowFall(node["weather_category"]["snowfall"].as<holo::uint32_t>());
                rhs.SetFoggyVisibility(node["weather_category"]["foggy_vis"].as<holo::uint32_t>());
                rhs.SetSandyVisibility(node["weather_category"]["sandy_vis"].as<holo::uint32_t>());
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
