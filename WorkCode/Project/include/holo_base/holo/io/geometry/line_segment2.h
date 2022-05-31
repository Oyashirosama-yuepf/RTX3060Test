#ifndef HOLO_IO_GEOMETRY_LINE_SEGMENT2_H_
#define HOLO_IO_GEOMETRY_LINE_SEGMENT2_H_

#include <holo/geometry/line_segment2.h>
#include <yaml-cpp/yaml.h>

namespace YAML
{
template <typename T>
struct convert<holo::geometry::LineSegment2T<T>>
{
    using ValueType   = holo::geometry::LineSegment2T<T>;
    using ScalarType  = typename ValueType::ScalarType;
    using Vector4Type = typename ValueType::Vector4Type;
    using Point2Type  = typename ValueType::Point2Type;

    static Node encode(ValueType const& rhs)
    {
        Node        node;
        Vector4Type coeffs = rhs.GetCoeffs();
        node["x"]          = coeffs[0];
        node["y"]          = coeffs[1];
        node["v0"]         = coeffs[2];
        node["v1"]         = coeffs[3];

        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            ScalarType x, y, v0, v1;
            x  = node["x"].as<ScalarType>();
            y  = node["y"].as<ScalarType>();
            v0 = node["v0"].as<ScalarType>();
            v1 = node["v1"].as<ScalarType>();

            Point2Type p1(x, y);
            Point2Type p2(x + v0, y + v1);
            rhs = ValueType(p1, p2);
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