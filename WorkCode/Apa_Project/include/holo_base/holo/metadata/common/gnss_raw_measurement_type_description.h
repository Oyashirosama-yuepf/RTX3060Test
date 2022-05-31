#ifndef HOLO_METADATA_COMMON_GNSS_RAW_MEASUREMENT_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_GNSS_RAW_MEASUREMENT_TYPE_DESCRIPTION_H_

#include <holo/common/gnss_raw_measurement.h>
#include <holo/metadata/common/gnss_raw_measurement_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace common_type
{
static constexpr char RAW_BLOCK_SIZE_FIELD_NAME[] = "satellite_number";
}

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::GnssRawMeasurement::RawMeasurementBlock, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN,
                                                            "holo::common::GnssRawMeasurement::RawMeasurementBlock");
        (void)desc->SetTemplates({}).SetMembers(
            {{"pseudorange_measurement", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"carrier_phase_measurement", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"doppler_measurement", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"gnss_identifier", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"satellite_identifier", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"frequence_identifier", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"carrier_phase_locktime", TypeDescriptionResolver<holo::uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"carrier_noise_ratio", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"pseudorange_standard_deviation", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"carrier_phase_standard_deviation", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"doppler_standard_deviation", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"tracking_status", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::GnssRawMeasurement, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::GnssRawMeasurement");
        (void)desc->SetTemplates({}).SetMembers(
            {{"gps_second", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"gps_week", TypeDescriptionResolver<holo::uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"leap_second", TypeDescriptionResolver<holo::int8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"satellite_number", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"pdop", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"raw_block",
              TypeDescriptionResolver<SequenceTag<holo::common::GnssRawMeasurement::RawMeasurementBlock,
                                                  ValueReferenceTag<1U, common_type::RAW_BLOCK_SIZE_FIELD_NAME>>,
                                      ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
