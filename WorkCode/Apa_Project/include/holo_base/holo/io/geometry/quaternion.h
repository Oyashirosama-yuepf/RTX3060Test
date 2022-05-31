#ifndef HOLO_IO_GEOMETRY_QUATERNION_H_
#define HOLO_IO_GEOMETRY_QUATERNION_H_

#include <holo/geometry/quaternion.h>
#include <yaml-cpp/yaml.h>

namespace YAML
{
template <typename T>
struct convert<holo::geometry::QuaternionT<T>>
{
    using ValueType  = holo::geometry::QuaternionT<T>;
    using ScalarType = typename ValueType::ScalarType;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["w"] = rhs.GetW();
        node["x"] = rhs.GetX();
        node["y"] = rhs.GetY();
        node["z"] = rhs.GetZ();

        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs = ValueType(node["w"].as<ScalarType>(), node["x"].as<ScalarType>(), node["y"].as<ScalarType>(),
                            node["z"].as<ScalarType>());
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