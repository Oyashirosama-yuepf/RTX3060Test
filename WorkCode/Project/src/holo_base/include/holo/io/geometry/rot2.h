#ifndef HOLO_IO_GEOMETRY_ROT2_H_
#define HOLO_IO_GEOMETRY_ROT2_H_

#include <holo/geometry/rot2.h>
#include <yaml-cpp/yaml.h>

namespace YAML
{
template <typename T>
struct convert<holo::geometry::Rot2T<T>>
{
    using ValueType  = holo::geometry::Rot2T<T>;
    using ScalarType = typename ValueType::ScalarType;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["theta"] = rhs.GetTheta();

        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs = ValueType(node["theta"].as<ScalarType>());
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