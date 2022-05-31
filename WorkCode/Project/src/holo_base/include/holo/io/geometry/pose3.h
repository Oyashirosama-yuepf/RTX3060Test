#ifndef HOLO_IO_GEOMETRY_POSE3T_H_
#define HOLO_IO_GEOMETRY_POSE3T_H_

#include <holo/geometry/pose3.h>
#include <holo/io/geometry/point3.h>
#include <holo/io/geometry/rot3.h>
#include <yaml-cpp/yaml.h>

namespace YAML
{
template <typename T>
struct convert<holo::geometry::Pose3T<T>>
{
    using ValueType  = holo::geometry::Pose3T<T>;
    using Rot3Type   = typename ValueType::Rot3Type;
    using Point3Type = typename ValueType::Point3Type;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["rotation"]    = rhs.GetRotation();
        node["translation"] = rhs.GetTranslation();
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetRotation(node["rotation"].as<Rot3Type>());
            rhs.SetTranslation(node["translation"].as<Point3Type>());

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