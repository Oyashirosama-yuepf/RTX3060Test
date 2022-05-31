#ifndef HOLO_METADATA_SENSORS_FORMAT_PAcKED_DATA_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_SENSORS_FORMAT_PAcKED_DATA_TYPE_DESCRIPTION_H_

#include <holo/metadata/common/sensor_id_type_description.h>
#include <holo/metadata/type_description.h>
#include <holo/sensors/format/packed_data.h>

namespace holo
{
namespace metadata
{
namespace sensors
{
static constexpr char PAYLOAD_LENGTH_NAME[] = "compress_data_len";
}
template <uint32_t N, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::sensors::format::SensorCompressedPacket<N>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto alg_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::sensors::format::SensorCompressedPacket::DataCompressAlgorithm");
        alg_desc->SetEnumerates({{0, "NONE"}, {1, "LZ4"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN,
                                                            "holo::sensors::format::SensorCompressedPacket");
        desc->SetTemplates({}).SetMembers(
            {{"header", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"version", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"sensor_id", TypeDescriptionResolver<holo::common::SensorId, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"raw_data_len", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"compress_data_len", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"compress_algorithm", alg_desc},
             {"compress_algorithm_desc", TypeDescriptionResolver<ArrayTag<uint8_t, 16U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"payload", TypeDescriptionResolver<SequenceTag<uint8_t, ValueReferenceTag<1U, sensors::PAYLOAD_LENGTH_NAME>>,
                                                 ALIGN, IS_BIG_ENDIAN>::Get()},
             {"crc", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
