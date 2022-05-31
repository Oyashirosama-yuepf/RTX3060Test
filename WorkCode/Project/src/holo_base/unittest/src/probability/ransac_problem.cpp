#include <holo/geometry/point3.h>
#include <holo/probability/ransac/ransac_problem.h>

using ScalarType = holo::float32_t;
using Point3Type = holo::geometry::Point3T<ScalarType>;
template class holo::RansacProblemT<Point3Type>;

