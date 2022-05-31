#ifndef HOLO_IO_GEOMETRY_POINT3_H_
#define HOLO_IO_GEOMETRY_POINT3_H_

#include <holo/geometry/point3.h>
#include <yaml-cpp/yaml.h>

namespace YAML
{
template <typename T>
struct convert<holo::geometry::Point3T<T>>
{
    using ValueType  = holo::geometry::Point3T<T>;
    using ScalarType = typename ValueType::ScalarType;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["x"] = rhs.GetX();
        node["y"] = rhs.GetY();
        node["z"] = rhs.GetZ();
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetX(node["x"].as<ScalarType>());
            rhs.SetY(node["y"].as<ScalarType>());
            rhs.SetZ(node["z"].as<ScalarType>());

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