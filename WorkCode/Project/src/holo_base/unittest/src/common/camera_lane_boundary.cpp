#include <holo/common/camera_lane_boundary.h>
template class holo::common::CameraLaneBoundaryT<holo::float32_t, 3U, 4U>;

template size_t holo::common::CameraLaneBoundaryT<holo::float32_t, 3U, 4U>::GetSerializedSize<4U>() const noexcept;
template void holo::common::CameraLaneBoundaryT<holo::float32_t, 3U, 4U>::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void
holo::common::CameraLaneBoundaryT<holo::float32_t, 3U, 4U>::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);

template class holo::common::CameraLaneBoundariesT<holo::common::CameraLaneBoundaryT<holo::float32_t, 3U, 4U>, 4U>;
template size_t holo::common::CameraLaneBoundariesT<holo::common::CameraLaneBoundaryT<holo::float32_t, 3U, 4U>,
                                                    4U>::GetSerializedSize<4U>() const noexcept;
template void
holo::common::CameraLaneBoundariesT<holo::common::CameraLaneBoundaryT<holo::float32_t, 3U, 4U>, 4U>::Serialize<
    holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::CameraLaneBoundariesT<holo::common::CameraLaneBoundaryT<holo::float32_t, 3U, 4U>, 4U>::Deserialize<
    holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);
