#include <holo/geometry/quaternion.h>
#include <holo/io/geometry/quaternion.h>

template struct YAML::convert<holo::geometry::QuaternionT<holo::float32_t>>;