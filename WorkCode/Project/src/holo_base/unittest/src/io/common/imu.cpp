
#include <holo/common/imu.h>
#include <holo/io/common/imu.h>

template struct YAML::convert<holo::common::ImuT<holo::float32_t>>;
