#ifndef _HOLO_METADATA_SENSORS_LIDAR_PANDAR128_PANDAR128_FORMAT_TYPE_DESCRIPTION_H_
#define _HOLO_METADATA_SENSORS_LIDAR_PANDAR128_PANDAR128_FORMAT_TYPE_DESCRIPTION_H_

#include <holo/metadata/type_description.h>
#include <holo/sensors/lidar/pandar128/pandar128_format.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<::RawPandar128MsopPacket, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto pandar128_msop_packet_header_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::Pandar128MsopPacketHeader");
        pandar128_msop_packet_header_desc->SetTemplates({}).SetMembers(
            {{"start", TypeDescriptionResolver<ArrayTag<uint8_t, 4U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"major_version", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"minor_version", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"reserved", TypeDescriptionResolver<ArrayTag<uint8_t, 2U>, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto pandar128_msop_data_header_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::Pandar128MsopDataHeader");
        pandar128_msop_data_header_desc->SetTemplates({}).SetMembers(
            {{"laser_num", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"block_num", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"first_block_return", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"dis_unit", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"return_num", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"flags", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto channel_data_desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::ChannelData");
        channel_data_desc->SetTemplates({}).SetMembers(
            {{"distance", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"reflection", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto channel_data_array_desc = std::make_shared<TypeDescriptionArray>(ALIGN, IS_BIG_ENDIAN);
        channel_data_array_desc->SetSize(128U).SetElementType(channel_data_desc);

        auto pandar128_msop_data_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::Pandar128MsopData");
        pandar128_msop_data_desc->SetTemplates({}).SetMembers(
            {{"azimuth1", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"block1", channel_data_array_desc},
             {"azimuth2", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"block2", channel_data_array_desc},
             {"crc", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto pandar128_msop_functional_safety_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::Pandar128MsopFunctionalSafety");
        pandar128_msop_functional_safety_desc->SetTemplates({}).SetMembers(
            {{"fs_version", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lidar_state", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"total_fault_code_num", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"fault_code", TypeDescriptionResolver<ArrayTag<uint8_t, 2U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"reserved", TypeDescriptionResolver<ArrayTag<uint8_t, 8U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"crc32", TypeDescriptionResolver<ArrayTag<uint8_t, 4U>, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto pandar128_msop_data_tail_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::Pandar128MsopDataTail");
        pandar128_msop_data_tail_desc->SetTemplates({}).SetMembers(
            {{"reserved", TypeDescriptionResolver<ArrayTag<uint8_t, 9U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"azimuth_flag", TypeDescriptionResolver<ArrayTag<uint8_t, 2U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"operational_state", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"return_mode", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},

             {"motor_speed", TypeDescriptionResolver<ArrayTag<uint8_t, 2U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"timestamp", TypeDescriptionResolver<ArrayTag<uint8_t, 10U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"factory_info", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"udp_sequence", TypeDescriptionResolver<ArrayTag<uint8_t, 4U>, ALIGN, IS_BIG_ENDIAN>::Get()},

             {"imu_temperature", TypeDescriptionResolver<ArrayTag<uint8_t, 2U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"imu_acceleration_unit", TypeDescriptionResolver<ArrayTag<uint8_t, 2U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"imu_angular_velocity_unit", TypeDescriptionResolver<ArrayTag<uint8_t, 2U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"imu_timestamp", TypeDescriptionResolver<ArrayTag<uint8_t, 4U>, ALIGN, IS_BIG_ENDIAN>::Get()},

             {"imu_axis_acceleration", TypeDescriptionResolver<ArrayTag<uint8_t, 6U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"imu_axis_angular_velocity", TypeDescriptionResolver<ArrayTag<uint8_t, 6U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"crc32", TypeDescriptionResolver<ArrayTag<uint8_t, 4U>, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::RawPandar128MsopPacket");
        desc->SetTemplates({}).SetMembers({{"packet_header", pandar128_msop_packet_header_desc},
                                           {"data_header", pandar128_msop_data_header_desc},
                                           {"data", pandar128_msop_data_desc},
                                           {"functional_safety", pandar128_msop_functional_safety_desc},
                                           {"data_tail", pandar128_msop_data_tail_desc}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
