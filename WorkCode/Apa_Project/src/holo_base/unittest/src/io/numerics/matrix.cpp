#include <holo/numerics/matrix.h>
#include <holo/io/numerics/matrix.h>

template struct YAML::convert<holo::numerics::MatrixT<holo::float32_t, 3U, 3U>>;