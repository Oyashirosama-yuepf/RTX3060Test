#include <holo/common/vehicle_body_state.h>

template size_t holo::common::VehicleBodyState::GetSerializedSize<4U>() const noexcept;
template void
holo::common::VehicleBodyState::Serialize<holo::serialization::Serializer<>>(holo::serialization::Serializer<>&) const;
template void
holo::common::VehicleBodyState::Deserialize<holo::serialization::Deserializer<>>(holo::serialization::Deserializer<>&);

template holo::bool_t holo::common::VehicleBodyState::IsInvalidFlagSet(holo::common::VehicleBodyState::State&) const
    noexcept;
template holo::bool_t holo::common::VehicleBodyState::IsInvalidFlagSetAny(holo::common::VehicleBodyState::State&) const
    noexcept;
template void holo::common::VehicleBodyState::SetInvalidFlag(holo::common::VehicleBodyState::State&&) noexcept;
template void holo::common::VehicleBodyState::ResetInvalidFlag(holo::common::VehicleBodyState::State&&) noexcept;
