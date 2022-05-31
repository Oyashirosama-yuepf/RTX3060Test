#ifndef HOLO_IO_COMMON_VEHICLE_LOCATION_H_
#define HOLO_IO_COMMON_VEHICLE_LOCATION_H_

#include <holo/common/vehicle_location.h>
#include <holo/utils/yaml.h>
#include <holo/io/utils/utils.h>

namespace YAML
{
template <>
struct convert<holo::common::VehicleLocation>
{
    using ValueType = holo::common::VehicleLocation;
    using Location  = typename ValueType::Location;
    using Plane     = typename ValueType::Plane;

    static std::vector<std::pair<std::string, Location> > const& LocationStringTypePairs() noexcept
    {
        static std::vector<std::pair<std::string, Location> > location_map = {
            {"UNKNOWN", Location::UNKNOWN},
            {"BOTTOM_MOST", Location::BOTTOM_MOST},
            {"REAR_MOST", Location::REAR_MOST},
            {"LEFT_MOST", Location::LEFT_MOST},
            {"BOTTOM", Location::BOTTOM},
            {"REAR", Location::REAR},
            {"LEFT", Location::LEFT},
            {"MIDDLE", Location::MIDDLE},
            {"CENTER", Location::CENTER},
            {"TOP", Location::TOP},
            {"FRONT", Location::FRONT},
            {"RIGHT", Location::RIGHT},
            {"TOP_MOST", Location::TOP_MOST},
            {"FRONT_MOST", Location::FRONT_MOST},
            {"RIGHT_MOST", Location::RIGHT_MOST}};
        return location_map;
    };

    static std::vector<std::pair<std::string, Plane> > const& PlaneStringTypePairs() noexcept
    {
        static std::vector<std::pair<std::string, Plane> > plane_map = {
            {"UNKNOWN", Plane::UNKNOWN},
            {"FRONT", Plane::FRONT},
            {"REAR", Plane::REAR},
            {"LEFT", Plane::LEFT},
            {"RIGHT", Plane::RIGHT},
            {"FRONT_WINDOW", Plane::FRONT_WINDOW},
            {"REAR_WINDOW", Plane::REAR_WINDOW},
            {"LEFT_WINDOW", Plane::LEFT_WINDOW},
            {"RIGHT_WINDOW", Plane::RIGHT_WINDOW},
            {"EIGINE_HOOD", Plane::EIGINE_HOOD},
            {"ROOF", Plane::ROOF},
            {"TRUNK_DOOR", Plane::TRUNK_DOOR},
            {"CHASSIS", Plane::CHASSIS},
            {"TRUNK", Plane::TRUNK},
            {"COCKPIT", Plane::COCKPIT},
            {"GROUND", Plane::GROUND}};
        return plane_map;
    };

    static Node encode(ValueType const& rhs)
    {
        Node node;

        for (auto const& value : LocationStringTypePairs())
        {
            if (value.second == rhs.GetLocationX())
            {
                node["x"] = value.first;
            }
            if (value.second == rhs.GetLocationY())
            {
                node["y"] = value.first;
            }
        }

        for (auto const& value : PlaneStringTypePairs())
        {
            if (value.second == rhs.GetPlane())
            {
                node["plane"] = value.first;
            }
        }

        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            bool  location_x_flag = false;
            for (auto const& value : LocationStringTypePairs())
            {
                if (value.first == node["x"].as<std::string>())
                {
                    rhs.SetLocationX(value.second);
                    location_x_flag = true;
                }
            }
            if(!location_x_flag)
            {
                if (IsDigit(node["x"].as<std::string>()))
                {
                    Location x = static_cast<Location>(node["x"].as<holo::uint16_t>());
                    rhs.SetLocationX(x);
                }
                else
                {
                    return false;
                }
            }

            bool location_y_flag = false;
            for (auto const& value : LocationStringTypePairs())
            {
                if (value.first == node["y"].as<std::string>())
                {
                    rhs.SetLocationY(value.second);
                    location_y_flag = true;
                }
            }
            if(!location_y_flag)
            {
                if (IsDigit(node["y"].as<std::string>()))
                {
                    Location y = static_cast<Location>(node["y"].as<holo::uint16_t>());
                    rhs.SetLocationY(y);
                }
                else
                {
                    return false;
                }
                
            }
            
            bool plane_flag = false;
            for (auto const& value : PlaneStringTypePairs())
            {
                if (value.first == node["plane"].as<std::string>())
                {
                    rhs.SetPlane(value.second);
                    plane_flag = true;
                }
            }
            if(!plane_flag)
            {
                if (IsDigit(node["plane"].as<std::string>()))
                {
                    Plane plane = static_cast<Plane>(node["plane"].as<holo::uint16_t>());
                    rhs.SetPlane(plane);
                }
                else
                {
                    return false;
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