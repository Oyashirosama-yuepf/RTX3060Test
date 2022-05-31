#include <holo/common/intrinsic.h>
template class holo::common::details::PinholeIntrinsicT<holo::float32_t>;
template class holo::common::details::FisheyeIntrinsicT<holo::float32_t>;
template class holo::common::details::OmnidirectionalIntrinsicT<holo::float32_t>;

std::shared_ptr<holo::common::details::CameraIntrinsicBaseT<holo::float32_t>>
CreateCameraIntrinsic(YAML::Node const& node);
