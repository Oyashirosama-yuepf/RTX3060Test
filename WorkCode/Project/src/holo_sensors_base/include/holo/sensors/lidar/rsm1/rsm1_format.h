#ifndef _HOLO_SENSORS_LIDAR_RSM1_RSM1_FORMAT_H
#define _HOLO_SENSORS_LIDAR_RSM1_RSM1_FORMAT_H

#include <cstdint>

/* rsm1 format */
struct __attribute__((packed, aligned(1))) RawRsm1MsopPacket
{
    struct Rsm1MsopHeader
    {
        uint32_t pkt_header;  // 0x55，0xaa,，0x5a，0xa5
        uint16_t pkt_psn;
        uint16_t protocol_version;  // UDP
        uint8_t  wave_mode;
        uint8_t  time_sync_mode;  // 0x00: no sync source, 0x01: pps, 0x02: ptp
        uint8_t  timestamp[10];   // 0-3: us, 4-9: s
        uint8_t  reserved[10];
        uint8_t  lidar_type;  // default: 0x10
        uint8_t  mems_tmp;    // temperature = mems_tmp - 80
    };

    struct Rsm1MsopDataBlock
    {
        struct __attribute__((packed)) DataType
        {
            uint16_t radius_;  // 0.5cm
            uint16_t elevation_;
            uint16_t azimuth_;
            uint8_t  intensity_;
            uint16_t reserved;
        };

        uint8_t  time_offset;
        uint8_t  return_seq;
        DataType data[5];
    };

    struct Rsm1MsopTail
    {
        uint8_t reserved[3];
    };

    Rsm1MsopHeader    header;
    Rsm1MsopDataBlock data[25];
    Rsm1MsopTail      tail;
};
HOLO_STATIC_ASSERT(sizeof(RawRsm1MsopPacket) == 1210U);

#endif