#ifndef HOLO_IO_GEOMETRY_POSE2T_H_
#define HOLO_IO_GEOMETRY_POSE2T_H_

#include <yaml-cpp/yaml.h>
#include <holo/geometry/pose2.h>
#include <holo/io/geometry/point2.h>
#include <holo/io/geometry/rot2.h>

namespace YAML
{
template <typename T>
struct convert<holo::geometry::Pose2T<T>>
{
    using ValueType  = holo::geometry::Pose2T<T>;
    using Rot2Type   = typename ValueType::Rot2Type;
    using Point2Type = typename ValueType::Point2Type;

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
            rhs = ValueType(node["rotation"].as<Rot2Type>(), node["translation"].as<Point2Type>());
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