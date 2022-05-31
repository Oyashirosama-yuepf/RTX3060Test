#ifndef HOLO_IO_GEOMETRY_ROT3_H_
#define HOLO_IO_GEOMETRY_ROT3_H_

#include <holo/geometry/rot3.h>
#include <holo/io/numerics/matrix.h>
#include <yaml-cpp/yaml.h>

namespace YAML
{
template <typename T>
struct convert<holo::geometry::Rot3T<T>>
{
    using ValueType   = holo::geometry::Rot3T<T>;
    using Matrix3Type = typename ValueType::Matrix3Type;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["rotation_matrix"] = rhs.ToMatrix();
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs = ValueType(node["rotation_matrix"].as<Matrix3Type>());
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