#include <holo/common/gnss_raw_measurement.h>
template size_t holo::common::GnssRawMeasurement::GetSerializedSize<4U>() const noexcept;
template void   holo::common::GnssRawMeasurement::Serialize<holo::serialization::Serializer<>>(
    holo::serialization::Serializer<>&) const;
template void holo::common::GnssRawMeasurement::Deserialize<holo::serialization::Deserializer<>>(
    holo::serialization::Deserializer<>&);
