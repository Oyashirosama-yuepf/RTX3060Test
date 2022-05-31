#ifndef HOLO_IO_GEOMETRY_BOX3_H_
#define HOLO_IO_GEOMETRY_BOX3_H_

#include <holo/geometry/box3.h>
#include <holo/io/geometry/pose3.h>
#include <yaml-cpp/yaml.h>

namespace YAML
{
template <typename T>
struct convert<holo::geometry::Box3T<T>>
{
    using ValueType  = holo::geometry::Box3T<T>;
    using ScalarType = typename ValueType::ScalarType;
    using Pose3Type  = typename ValueType::Pose3Type;

    static Node encode(ValueType const& rhs)
    {
        Node node;

        node["width"]  = rhs.GetWidth();
        node["height"] = rhs.GetHeight();
        node["depth"]  = rhs.GetDepth();
        node["pose"]   = rhs.GetPose();

        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs = ValueType(node["width"].as<ScalarType>(), node["height"].as<ScalarType>(),
                            node["depth"].as<ScalarType>(), node["pose"].as<Pose3Type>());
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