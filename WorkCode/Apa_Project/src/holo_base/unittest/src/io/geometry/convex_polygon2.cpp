#include <holo/geometry/convex_polygon2.h>
#include <holo/io/geometry/convex_polygon2.h>

template struct YAML::convert<holo::geometry::ConvexPolygon2T<holo::float32_t>>;
