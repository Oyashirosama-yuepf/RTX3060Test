#ifndef HOLO_IO_COMMON_PATH_H_
#define HOLO_IO_COMMON_PATH_H_

#include <holo/common/path.h>
#include <holo/io/common/coordinate.h>
#include <holo/io/common/timestamp.h>
#include <holo/io/geometry/point3.h>
#include <holo/io/utils/utils.h>
#include <holo/utils/yaml.h>

namespace YAML
{
template <typename T>
struct convert<holo::common::PathPointT<T>>
{
    using ValueType  = holo::common::PathPointT<T>;
    using ScalarType = typename ValueType::ScalarType;
    using Point3     = typename ValueType::Base;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["theta"]        = rhs.GetTheta();
        node["curvature"]    = rhs.GetCurvature();
        node["speed"]        = rhs.GetSpeed();
        node["acceleration"] = rhs.GetAcceleration();
        node["point"]        = rhs.template As<Point3>();
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        rhs.SetTheta(node["theta"].as<ScalarType>());
        rhs.SetCurvature(node["curvature"].as<ScalarType>());
        rhs.SetSpeed(node["speed"].as<ScalarType>());
        rhs.SetAcceleration(node["acceleration"].as<ScalarType>());
        Point3 point = node["point"].as<Point3>();
        rhs.Set(point[0], point[1], point[2]);

        return true;
    };
};

template <typename T>
struct convert<holo::common::PathT<T>>
{
    using ValueType  = holo::common::PathT<T>;
    using PointType  = typename ValueType::PointType;
    using ValidValue = typename ValueType::ValidValue;
    using Timestamp  = holo::common::Timestamp;
    using Coordinate = holo::common::Coordinate;

    static std::vector<std::pair<std::string, ValidValue>> const& ValidStringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, ValidValue>> valid_type_str = {
            {"POSITION", ValidValue::POSITION},
            {"THETA", ValidValue::THETA},
            {"CURVATURE", ValidValue::CURVATURE},
            {"SPEED", ValidValue::SPEED},
            {"ACCELERATION", ValidValue::ACCELERATION}};
        return valid_type_str;
    };

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["timestamp"]  = rhs.GetTimestamp();
        node["coordinate"] = rhs.GetCoordinate();

        if (rhs.IsPositionValid())
        {
            node["valid_value"].push_back("POSITION");
        }
        if (rhs.IsThetaValid())
        {
            node["valid_value"].push_back("THETA");
        }
        if (rhs.IsCurvatureValid())
        {
            node["valid_value"].push_back("CURVATURE");
        }
        if (rhs.IsSpeedValid())
        {
            node["valid_value"].push_back("SPEED");
        }
        if (rhs.IsAccelerationValid())
        {
            node["valid_value"].push_back("ACCELERATION");
        }
        for (size_t i = 0; i < rhs.size(); ++i)
        {
            node["path_points"].push_back(rhs[i]);
        }
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        rhs.SetTimestamp(node["timestamp"].as<Timestamp>());
        rhs.SetCoordinate(node["coordinate"].as<Coordinate>());

        rhs.SetValidValue(0x00);
        if (node["valid_value"].Type() == YAML::NodeType::Sequence)
        {
            for (std::size_t i = 0; i < node["valid_value"].size(); i++)
            {
                if (YAML::IsDigit(node["valid_value"][i].as<std::string>()))
                {
                    rhs.SetSingleValidValue(static_cast<ValidValue>(node["valid_value"][i].as<holo::uint32_t>()));
                }
                else
                {
                    for (auto const& value : ValidStringTypePairs())
                    {
                        if (value.first == node["valid_value"][i].as<std::string>())
                        {
                            rhs.SetSingleValidValue(value.second);
                        }
                    }
                }
            }
        }
        else if (node["valid_value"].Type() == YAML::NodeType::Scalar)
        {
            if (YAML::IsDigit(node["valid_value"].as<std::string>()))
            {
                rhs.SetValidValue(node["valid_value"].as<holo::uint32_t>());
            }
        }

        rhs.clear();
        for (YAML::const_iterator it = node["path_points"].begin(); it != node["path_points"].end(); ++it)
        {
            rhs.push_back(it->as<PointType>());
        }

        return true;
    };
};
};  // namespace YAML

#endif
