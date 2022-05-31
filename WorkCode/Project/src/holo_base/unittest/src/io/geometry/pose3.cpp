#include <holo/geometry/pose3.h>
#include <holo/io/geometry/pose3.h>

template struct YAML::convert<holo::geometry::Pose3T<holo::float32_t>>;