#ifndef HOLO_IO_GEOMETRY_CONVEX_POLYGON2_H_
#define HOLO_IO_GEOMETRY_CONVEX_POLYGON2_H_

#include <yaml-cpp/yaml.h>
#include <holo/geometry/convex_polygon2.h>
#include <holo/io/geometry/point2.h>

namespace YAML
{
template <typename T>
struct convert<holo::geometry::ConvexPolygon2T<T>>
{
    using ValueType   = holo::geometry::ConvexPolygon2T<T>;
    using Point2Type  = typename ValueType::Point2Type;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["size"] = rhs.GetSize();
        for (size_t i = 0; i < rhs.GetSize(); ++i)
        {
            node["vertices"].push_back(rhs.GetVertex(i));
        }
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            ValueType convex_polygon;
            for (YAML::const_iterator it = node["vertices"].begin(); it != node["vertices"].end(); ++it)
            {
                convex_polygon.AppendVertex(it->as<Point2Type>());
            }
            rhs = convex_polygon;
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