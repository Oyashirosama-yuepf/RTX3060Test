#ifndef _HOLO_SENSORS_LIDAR_RSBPEARL_RSBPEARL_FORMAT_H
#define _HOLO_SENSORS_LIDAR_RSBPEARL_RSBPEARL_FORMAT_H

#include <cstdint>

/* rsbp packet */
struct __attribute__((packed, aligned(1))) RawRsbpMsopPacket
{
    struct RawRsbpMsopHeader
    {
        uint8_t header[8];  // 0x 55 aa 05 0a 5a a5 50 a0
        uint8_t reserved1[20U];
        uint8_t timestamp[10U];
        uint8_t reserved2[4U];
    };

    struct RawRsbpMsopData
    {
        struct __attribute__((packed)) ChannelData
        {
            uint16_t distance;  // unit: 0.5cm
            uint8_t  reflection;
        };
        uint16_t    header;  // 0xff 0xee
        uint16_t    azimuth;
        ChannelData data[32];
    };

    struct RawRsbpMsopTail
    {
        uint8_t reserved[4U];
        uint8_t tail[2U];  // 0x00 0xff
    };

    RawRsbpMsopHeader header;
    RawRsbpMsopData   data[12U];
    RawRsbpMsopTail   tail;
};
static_assert(sizeof(RawRsbpMsopPacket) == 1248U);

#endif