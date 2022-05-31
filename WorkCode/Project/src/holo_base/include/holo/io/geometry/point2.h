#ifndef HOLO_IO_GEOMETRY_POINT2_H_
#define HOLO_IO_GEOMETRY_POINT2_H_

#include <yaml-cpp/yaml.h>
#include <holo/geometry/point2.h>

namespace YAML
{
template <typename T>
struct convert<holo::geometry::Point2T<T>>
{
    using ValueType  = holo::geometry::Point2T<T>;
    using ScalarType = typename ValueType::ScalarType;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["x"] = rhs.GetX();
        node["y"] = rhs.GetY();
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetX(node["x"].as<ScalarType>());
            rhs.SetY(node["y"].as<ScalarType>());

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