#ifndef HOLO_METADATA_SENSORS_LIDAR_LIVOX_LIVOX_HAP_FORMAT_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_SENSORS_LIDAR_LIVOX_LIVOX_HAP_FORMAT_TYPE_DESCRIPTION_H_

#include <holo/metadata/type_description.h>
#include <holo/sensors/lidar/livox/livox_hap_format.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<::RawLivoxHapPacket, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::RawLivoxHapPacket");
        desc->SetTemplates({}).SetMembers(
            {{"version", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"slot_id", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"length", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"time_interval", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"frame_counter", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"data_type", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"timestamp_type", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"reserved", TypeDescriptionResolver<ArrayTag<uint8_t, 6U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"timestamp", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"data", TypeDescriptionResolver<SequenceTag<uint8_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
