#ifndef HOLO_IO_GEOMETRY_BOX2_H_
#define HOLO_IO_GEOMETRY_BOX2_H_

#include <holo/geometry/box2.h>
#include <holo/io/geometry/pose2.h>
#include <yaml-cpp/yaml.h>

namespace YAML
{
template <typename T>
struct convert<holo::geometry::Box2T<T>>
{
    using ValueType  = holo::geometry::Box2T<T>;
    using ScalarType = typename ValueType::ScalarType;
    using Pose2Type  = typename ValueType::Pose2Type;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["width"]  = rhs.GetWidth();
        node["height"] = rhs.GetHeight();
        node["pose"]   = rhs.GetPose();

        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetWidth(node["width"].as<ScalarType>());
            rhs.SetHeight(node["height"].as<ScalarType>());
            rhs.SetPose(node["pose"].as<Pose2Type>());

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