#ifndef _HOLO_SENSORS_LIDAR_LIVOX_LIVOX_FORMAT_H
#define _HOLO_SENSORS_LIDAR_LIVOX_LIVOX_FORMAT_H

#include <cstdint>

/* livox packet */
struct __attribute__((packed, aligned(1))) RawLivoxPacket
{
    struct DataType0
    {
        int32_t x;          // X axis, Unit: mm
        int32_t y;          // Y axis, Unit: mm
        int32_t z;          // Z axis, Unit: mm
        uint8_t intensity;  // Reflectivity
    };

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
        uint32_t depth;         // unit: mm
        uint16_t zenith_angle;  // unit: 0.01
        uint16_t azimuth;       // unit: 0.01
        uint8_t  intensity;     // Reflectivity
    };

    uint8_t  version;  // 5
    uint8_t  slot_id;
    uint8_t  lidar_id;
    uint8_t  reserved;
    uint32_t status_code;
    uint8_t  timestamp_type;  // 0: No sync source, 1: PTP, 2: reserved, 3: GPS, 4: PPS
    uint8_t  data_type;
    uint8_t  timestamp[8U];  // 0-3: yy-mm-dd-hh, 4-7: us
    uint8_t  data[0U];
};

#endif