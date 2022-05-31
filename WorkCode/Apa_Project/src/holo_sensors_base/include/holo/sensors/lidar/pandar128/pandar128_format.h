#ifndef _HOLO_SENSORS_LIDAR_PANDAR128_PANDAR128_FORMAT_H
#define _HOLO_SENSORS_LIDAR_PANDAR128_PANDAR128_FORMAT_H

#include <cstdint>

/* pandar128 packet */
struct __attribute__((packed, aligned(1))) RawPandar128MsopPacket
{
    struct __attribute__((packed)) Pandar128MsopPacketHeader
    {
        uint8_t start[2];       // 0xee 0xff
        uint8_t major_version;  // 0x01
        uint8_t minor_version;  // 0x04
        uint8_t reserved[2];
    };

    struct __attribute__((packed)) Pandar128MsopDataHeader
    {
        uint8_t laser_num;
        uint8_t block_num;
        uint8_t first_block_return; /* reserved */
        uint8_t dis_unit;
        uint8_t return_num;
        uint8_t flags;
    };

    struct __attribute__((packed)) Pandar128MsopData
    {
        struct __attribute__((packed)) ChannelData
        {
            uint16_t distance;  // unit: 0.4cm
            uint8_t  reflection;
        };
        uint16_t    azimuth1;
        ChannelData block1[128];
        uint16_t    azimuth2;
        ChannelData block2[128];
        uint32_t    crc;
    };

    struct Pandar128MsopFunctionalSafety
    {
        uint8_t fs_version;
        uint8_t lidar_state;
        uint8_t total_fault_code_num;
        uint8_t fault_code[2];
        uint8_t reserved[8];
        uint8_t crc32[4];
    };

    struct Pandar128MsopDataTail
    {
        uint8_t reserved[9];
        uint8_t azimuth_flag[2];
        uint8_t operational_state;
        uint8_t return_mode;
        uint8_t motor_speed[2];
        uint8_t timestamp[10];
        uint8_t factory_info;
        uint8_t udp_sequence[4];
        uint8_t imu_temperature[2];
        uint8_t imu_acceleration_unit[2];
        uint8_t imu_angular_velocity_unit[2];
        uint8_t imu_timestamp[4];
        uint8_t imu_axis_acceleration[6];     /* x y z */
        uint8_t imu_axis_angular_velocity[6]; /* x y z */
        uint8_t crc32[4];
    };

    Pandar128MsopPacketHeader     packet_header;
    Pandar128MsopDataHeader       data_header;
    Pandar128MsopData             data;
    Pandar128MsopFunctionalSafety functional_safety;
    Pandar128MsopDataTail         data_tail;
    // uint8_t                       signature[32];
};
HOLO_STATIC_ASSERT(sizeof(RawPandar128MsopPacket) == 861U); /*+ 32*/

#endif
