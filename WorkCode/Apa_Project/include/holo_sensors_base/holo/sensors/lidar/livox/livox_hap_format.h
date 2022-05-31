#ifndef _HOLO_SENSORS_LIDAR_LIVOX_LIVOX_HAP_FORMAT_H
#define _HOLO_SENSORS_LIDAR_LIVOX_LIVOX_HAP_FORMAT_H

#include <cstdint>

/* livox hap packet */
struct __attribute__((packed, aligned(1))) RawLivoxHapPacket
{
    struct DataType1
    {
        int32_t x;          // X axis, Unit: mm
        int32_t y;          // Y axis, Unit: mm
        int32_t z;          // Z axis, Unit: mm
        uint8_t intensity;  // Reflectivity
        uint8_t tag;        // Tag
    };

    struct DataType2
    {
        int16_t x;          // X axis, Unit: 10mm
        int16_t y;          // Y axis, Unit: 10mm
        int16_t z;          // Z axis, Unit: 10mm
        uint8_t intensity;  // Reflectivity
        uint8_t tag;        // Tag
    };

    struct DataType3
    {
        float gyro_x;  // unit: rad/s
        float gyro_y;  // unit: rad/s
        float gyro_z;  // unit: rad/s
        float acc_x;   // unit: g
        float acc_y;   // unit: g
        float acc_z;   // unit: g
    };

    uint8_t  version;
    uint8_t  slot_id;
    uint16_t length;
    uint16_t time_interval;
    uint16_t frame_counter;
    uint8_t  data_type;       // 1: pcd(xyz) 2: pcd(xyz 16bit) 3: imu
    uint8_t  timestamp_type;  // 0: no sync source, 1: ptp sync
    uint8_t  reserved[6];
    uint64_t timestamp;  // unit: ns
    uint8_t  data[0];
};
static_assert(sizeof(RawLivoxHapPacket) == 24U);

#endif