#ifndef _HOLO_METADATA_SENSORS_LIDAR_RSM1_RSM1_FORMAT_TYPE_DESCRIPTION_H_
#define _HOLO_METADATA_SENSORS_LIDAR_RSM1_RSM1_FORMAT_TYPE_DESCRIPTION_H_

#include <holo/metadata/type_description.h>
#include <holo/sensors/lidar/rsm1/rsm1_format.h>

namespace holo
{
namespace metadata
{

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<::RawRsm1MsopPacket, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto rsm1_msop_header_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::Rsm1MsopHeader");
        rsm1_msop_header_desc->SetTemplates({}).SetMembers(
            {{"pkt_header", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"pkt_psn", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"protocol_version", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"wave_mode", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"time_sync_mode", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"timestamp", TypeDescriptionResolver<ArrayTag<uint8_t, 10U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"reserved", TypeDescriptionResolver<ArrayTag<uint8_t, 10U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lidar_type", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"mems_tmp", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto data_type_desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::DataType");
        data_type_desc->SetTemplates({}).SetMembers(
            {{"radius_", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"elevation_", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"azimuth_", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"intensity_", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"reserved", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto data_type_array_desc = std::make_shared<TypeDescriptionArray>(ALIGN, IS_BIG_ENDIAN);
        data_type_array_desc->SetSize(5U).SetElementType(data_type_desc);

        auto rsm1_msop_data_block_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::Rsm1MsopDataBlock");
        rsm1_msop_data_block_desc->SetTemplates({}).SetMembers(
            {{"time_offset", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"return_seq", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"data", data_type_array_desc}});

        auto rsm1_msop_data_block_array_desc = std::make_shared<TypeDescriptionArray>(ALIGN, IS_BIG_ENDIAN);
        rsm1_msop_data_block_array_desc->SetSize(25U).SetElementType(rsm1_msop_data_block_desc);

        auto rsm1_msop_tail_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::Rsm1MsopTail");
        rsm1_msop_tail_desc->SetTemplates({}).SetMembers(
            {{"reserved", TypeDescriptionResolver<ArrayTag<uint8_t, 3U>, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::RawRsm1MsopPacket");
        desc->SetTemplates({}).SetMembers(
            {{"header", rsm1_msop_header_desc},
             {"data", rsm1_msop_data_block_array_desc},
             {"tail", rsm1_msop_tail_desc}});
            return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
