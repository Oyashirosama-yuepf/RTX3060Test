/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file starneto_structure.h
 * @brief A app for starneto messages output
 * @author wangzhaobing<wangzhaobing@holomatic.com>
 * @date 2022/1/28
 */

#ifndef _HOLO_SENSORS_STARNETO_STARNETO_STRUCTURE_H
#define _HOLO_SENSORS_STARNETO_STARNETO_STRUCTURE_H

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/os/endian.h>
#include <holo_c/core/static_assert.h>
#include <map>
#include <string>

#ifndef HOLO_PLATFORM_LITTLE_ENDIAN
#error "starneto structures are based on little-endian machines, fix it if the target machine is big-endian."
#endif

namespace holo
{
namespace sensors
{
namespace starneto
{
static const uint8_t   SYNC1_BYTE         = 0xAA;
static const uint8_t   SYNC2_BYTE         = 0x55;
static const float64_t GPS_SECS_FACTOR    = 1E-3;
static const float64_t LATITUDE_FACTOR    = 1E-7;
static const float64_t LONGITUDE_FACTOR   = 1E-7;
static const float64_t HEIGHT_FACTOR      = 1E-3;
static const float64_t TEMPERATURE_FACTOR = 1E-3;
static const float64_t GRAVITY_FACTOR     = 10;

static const float64_t IMU_HIGH_TEMP = 55;
static const float64_t IMU_LOW_TEMP  = -40;

enum Gpfpdstatus : uint8_t
{
    RTKFIXED    = 75,  // 0X4B, RTK fixed
    RTKFLOAT    = 91,  // 0X5B, RTK float
    GPSDIRETION = 4,   // 0X04, GPS directional
    GPSONLY     = 3,   // 0X03, GPS only point
    SYSINITIAL  = 0,   // 0X00, systecm initialization
    NAVINITIAL  = 12,  // 0X0C, navigate initialization
};

struct GIHeader
{
    uint8_t sync1;    // start of packet first byte (0xAA)
    uint8_t sync2;    // start of packet first byte (0x55)
    uint8_t frameID;  // frame number of packet
    uint8_t length;   // length of packet
};
struct GPFPD_BIN
{
    GIHeader  header;           // message header
    uint32_t  gps_week;         // gps week number
    float64_t gps_secs;         // seconds into gps week
    float64_t azimuth;          // azimuth (deg)
    float64_t pitch;            // pitch (deg)
    float64_t roll;             // roll (deg)
    float64_t latitude;         // latitude - WGS84 (deg)
    float64_t longitude;        // longitude - WGS84 (deg)
    float64_t height;           // height (m)
    float64_t east_velocity;    // velocity in east (m/s)
    float64_t north_velocity;   // velocity in north (m/s)
    float64_t up_velocity;      // velocity in up (m/s)
    float64_t base_length = 0;  // base length
    uint8_t   svs1        = 0;  // number of satellite 1
    uint8_t   svs2        = 0;  // number of satellite 2
    uint8_t   status;           // state of satellite
    uint8_t   ck;               // checksum
};

struct GTIMU_BIN
{
    GIHeader  header;           // message header
    uint32_t  gps_week;         // gps week number
    float64_t gps_secs;         // seconds into gps week
    float64_t x_gyro_rate;      // change in angle aroud x axis (deg/s)
    float64_t y_gyro_rate;      // change in angle aroud y axis (deg/s)
    float64_t z_gyro_rate;      // change in angle aroud z axis (deg/s)
    float64_t x_acceleration;   // change in velocity aroud x axis (g)
    float64_t y_acceleration;   // change in velocity aroud y axis (g)
    float64_t z_acceleration;   // change in velocity aroud z axis (g)
    int16_t   temperature = 0;  // temperature
    uint8_t   ck;               // checksum
};

}  // namespace starneto
}  // namespace sensors
}  // namespace holo

#endif
