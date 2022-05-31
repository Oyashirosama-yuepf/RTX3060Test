#ifndef HOLO_IO_GEOMETRY_LINE2_H_
#define HOLO_IO_GEOMETRY_LINE2_H_

#include <holo/geometry/line2.h>
#include <yaml-cpp/yaml.h>

namespace YAML
{
template <typename T>
struct convert<holo::geometry::Line2T<T>>
{
    using ValueType   = holo::geometry::Line2T<T>;
    using Vector3Type = typename ValueType::Vector3Type;
    using ScalarType  = typename ValueType::ScalarType;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        Vector3Type coeffs = rhs.GetCoeffs();
        node["a"] = coeffs[0];
        node["b"] = coeffs[1];
        node["c"] = coeffs[2];

        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs = ValueType(node["a"].as<ScalarType>(), node["b"].as<ScalarType>(), node["c"].as<ScalarType>());
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