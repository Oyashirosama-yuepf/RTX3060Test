
#include <holo/common/imu_bias.h>
#include <holo/io/common/imu_bias.h>

template struct YAML::convert<holo::common::ImuBiasT<holo::float32_t>>;
 