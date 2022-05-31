#include <holo/vision/keypoint2.h>
#include <holo/vision/object.h>

using PointType = ::holo::vision::KeyPoint2T<::holo::float32_t>;
template class holo::vision::ObjectT<PointType>;
