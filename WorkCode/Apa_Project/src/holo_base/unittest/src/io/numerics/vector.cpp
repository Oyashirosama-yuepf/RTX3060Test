#include <holo/numerics/vector.h>
#include <holo/io/numerics/vector.h>

template struct YAML::convert<holo::numerics::VectorT<holo::float32_t, 10U>>;