#include <holo/common/odometry.h>
#include <holo/io/common/odometry.h>

template struct YAML::convert<holo::common::OdometryT<holo::float32_t>>;

