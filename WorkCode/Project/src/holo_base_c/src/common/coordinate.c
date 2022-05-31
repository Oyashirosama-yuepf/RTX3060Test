/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file coordinate.c
 * @brief This file implements coordinate system.
 * @author ZhangJiannan (zhangjiannan@holomatic.com)
 * @date 2019-12-2
 */

#include <holo_c/common/coordinate.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>

#define COORDINATE_TYPE_OFFSET 28
#define COORDINATE_TYPE_BASE_MASK 0x0000000f
#define COORDINATE_TYPE_MASK ((COORDINATE_TYPE_BASE_MASK) << (COORDINATE_TYPE_OFFSET))

#define COORDINATE_PARAM_OFFSET 0
#define COORDINATE_PARAM_BASE_MASK 0x0fffffff
#define COORDINATE_PARAM_MASK ((COORDINATE_PARAM_BASE_MASK) << (COORDINATE_PARAM_OFFSET))

#define COORDINATE_VEHICLE_PARAM_SENSOR_ID_OFFSET 0
#define COORDINATE_VEHICLE_PARAM_SENSOR_ID_BASE_MASK 0x0fffffff
#define COORDINATE_VEHICLE_PARAM_SENSOR_ID_MASK                                                                        \
    ((COORDINATE_VEHICLE_PARAM_SENSOR_ID_BASE_MASK) << (COORDINATE_VEHICLE_PARAM_SENSOR_ID_OFFSET))

#define COORDINATE_UTM_PARAM_ZONE_ID_OFFSET 0
#define COORDINATE_UTM_PARAM_ZONE_ID_BASE_MASK 0x0000007f
#define COORDINATE_UTM_PARAM_ZONE_ID_MASK                                                                              \
    ((COORDINATE_UTM_PARAM_ZONE_ID_BASE_MASK) << (COORDINATE_UTM_PARAM_ZONE_ID_OFFSET))

#define COORDINATE_UTM_PARAM_ZONE_OFFSET 0
#define COORDINATE_UTM_PARAM_ZONE_BASE_MASK 0x000000ff
#define COORDINATE_UTM_PARAM_ZONE_MASK ((COORDINATE_UTM_PARAM_ZONE_BASE_MASK) << (COORDINATE_UTM_PARAM_ZONE_OFFSET))

#define COORDINATE_UTM_PARAM_SOUTH_FLAG_OFFSET 7
#define COORDINATE_UTM_PARAM_SOUTH_FLAG_BASE_MASK 0x00000001
#define COORDINATE_UTM_PARAM_SOUTH_FLAG_MASK                                                                           \
    ((COORDINATE_UTM_PARAM_SOUTH_FLAG_BASE_MASK) << (COORDINATE_UTM_PARAM_SOUTH_FLAG_OFFSET))

#define COORDINATE_UTM_PARAM_OFFSET_X_OFFSET 20
#define COORDINATE_UTM_PARAM_OFFSET_X_BASE_MASK 0x000000ff
#define COORDINATE_UTM_PARAM_OFFSET_X_MASK                                                                             \
    ((COORDINATE_UTM_PARAM_OFFSET_X_BASE_MASK) << (COORDINATE_UTM_PARAM_OFFSET_X_OFFSET))

#define COORDINATE_UTM_PARAM_OFFSET_Y_OFFSET 8
#define COORDINATE_UTM_PARAM_OFFSET_Y_BASE_MASK 0x00000fff
#define COORDINATE_UTM_PARAM_OFFSET_Y_MASK                                                                             \
    ((COORDINATE_UTM_PARAM_OFFSET_Y_BASE_MASK) << (COORDINATE_UTM_PARAM_OFFSET_Y_OFFSET))

#define COORDINATE_DR_PARAM_VERSION_OFFSET 0
#define COORDINATE_DR_PARAM_VERSION_BASE_MASK 0x0000ffff
#define COORDINATE_DR_PARAM_VERSION_MASK                                                                               \
    ((COORDINATE_DR_PARAM_VERSION_BASE_MASK) << (COORDINATE_DR_PARAM_VERSION_OFFSET))

enum CoordinateType coordinate_get_type(const Coordinate_t* coordinate)
{
    return (enum CoordinateType)((*coordinate & COORDINATE_TYPE_MASK) >> COORDINATE_TYPE_OFFSET);
}

void coordinate_set_type(Coordinate_t* coordinate, enum CoordinateType type)
{
    *coordinate &= ~COORDINATE_TYPE_MASK;
    *coordinate |= ((type & COORDINATE_TYPE_BASE_MASK) << COORDINATE_TYPE_OFFSET);
}

uint32_t coordinate_get_param(const Coordinate_t* coordinate)
{
    return (*coordinate & COORDINATE_PARAM_MASK);
}

void coordinate_set_param(Coordinate_t* coordinate, uint32_t param)
{
    *coordinate &= ~COORDINATE_PARAM_MASK;
    *coordinate |= (param & COORDINATE_PARAM_BASE_MASK);
}

SensorId_t coordinate_vehicle_get_sensor_id(const Coordinate_t* coordinate)
{
    return (SensorId_t)((*coordinate & COORDINATE_VEHICLE_PARAM_SENSOR_ID_MASK) >>
                        COORDINATE_VEHICLE_PARAM_SENSOR_ID_OFFSET);
}

void coordinate_vehicle_set_sensor_id(Coordinate_t* coordinate, SensorId_t sensor_id)
{
    *coordinate &= ~COORDINATE_VEHICLE_PARAM_SENSOR_ID_MASK;
    *coordinate |= ((uint32_t)sensor_id & COORDINATE_VEHICLE_PARAM_SENSOR_ID_BASE_MASK)
                   << COORDINATE_VEHICLE_PARAM_SENSOR_ID_OFFSET;
}

void coordinate_utm_set_zone_id(Coordinate_t* coordinate, uint8_t zone)
{
    *coordinate &= ~COORDINATE_UTM_PARAM_ZONE_ID_MASK;
    *coordinate |= (zone & COORDINATE_UTM_PARAM_ZONE_ID_BASE_MASK) << COORDINATE_UTM_PARAM_ZONE_ID_OFFSET;
}

void coordinate_utm_set_zone(Coordinate_t* coordinate, uint8_t zone)
{
    *coordinate &= ~COORDINATE_UTM_PARAM_ZONE_MASK;
    *coordinate |= (zone & COORDINATE_UTM_PARAM_ZONE_BASE_MASK) << COORDINATE_UTM_PARAM_ZONE_OFFSET;
}

uint8_t coordinate_utm_get_zone_id(const Coordinate_t* coordinate)
{
    return (uint8_t)((*coordinate & COORDINATE_UTM_PARAM_ZONE_ID_MASK) >> COORDINATE_UTM_PARAM_ZONE_ID_OFFSET);
}

uint8_t coordinate_utm_get_zone(const Coordinate_t* coordinate)
{
    return (uint8_t)((*coordinate & COORDINATE_UTM_PARAM_ZONE_MASK) >> COORDINATE_UTM_PARAM_ZONE_OFFSET);
}

void coordinate_utm_set_south_flag(Coordinate_t* coordinate)
{
    *coordinate |= COORDINATE_UTM_PARAM_SOUTH_FLAG_MASK;
}

void coordinate_utm_reset_south_flag(Coordinate_t* coordinate)
{
    *coordinate &= ~COORDINATE_UTM_PARAM_SOUTH_FLAG_MASK;
}

bool coordinate_utm_get_south_flag(const Coordinate_t* coordinate)
{
    return ((*coordinate & COORDINATE_UTM_PARAM_SOUTH_FLAG_MASK) >> COORDINATE_UTM_PARAM_SOUTH_FLAG_OFFSET);
}

void coordinate_utm_set_offset_x(Coordinate_t* coordinate, uint32_t x)
{
    *coordinate &= ~COORDINATE_UTM_PARAM_OFFSET_X_MASK;
    *coordinate |= (x & COORDINATE_UTM_PARAM_OFFSET_X_BASE_MASK) << COORDINATE_UTM_PARAM_OFFSET_X_OFFSET;
}

uint32_t coordinate_utm_get_offset_x(const Coordinate_t* coordinate)
{
    return (*coordinate & COORDINATE_UTM_PARAM_OFFSET_X_MASK) >> COORDINATE_UTM_PARAM_OFFSET_X_OFFSET;
}

void coordinate_utm_set_offset_y(Coordinate_t* coordinate, uint32_t y)
{
    *coordinate &= ~COORDINATE_UTM_PARAM_OFFSET_Y_MASK;
    *coordinate |= (y & COORDINATE_UTM_PARAM_OFFSET_Y_BASE_MASK) << COORDINATE_UTM_PARAM_OFFSET_Y_OFFSET;
}

uint32_t coordinate_utm_get_offset_y(const Coordinate_t* coordinate)
{
    return (*coordinate & COORDINATE_UTM_PARAM_OFFSET_Y_MASK) >> COORDINATE_UTM_PARAM_OFFSET_Y_OFFSET;
}

void coordinate_dr_set_version(Coordinate_t* coordinate, uint16_t version)
{
    *coordinate &= ~COORDINATE_DR_PARAM_VERSION_MASK;
    *coordinate |= (version & COORDINATE_DR_PARAM_VERSION_BASE_MASK) << COORDINATE_DR_PARAM_VERSION_OFFSET;
}

uint16_t coordinate_dr_get_version(Coordinate_t const* coordinate)
{
    return (*coordinate & COORDINATE_DR_PARAM_VERSION_MASK) >> COORDINATE_DR_PARAM_VERSION_OFFSET;
}

Coordinate_t coordinate_default_create()
{
    return COORDINATE_TYPE_UNKNOWN << COORDINATE_TYPE_OFFSET;
}

Coordinate_t coordinate_vehicle_create(SensorId_t sensor_id)
{
    return (COORDINATE_TYPE_VEHICLE << COORDINATE_TYPE_OFFSET) |
           ((uint32_t)sensor_id & COORDINATE_VEHICLE_PARAM_SENSOR_ID_BASE_MASK);
}

Coordinate_t coordinate_wgs84_create()
{
    return (COORDINATE_TYPE_WGS84 << COORDINATE_TYPE_OFFSET);
}

Coordinate_t coordinate_utm6_create(uint8_t zone_id, bool_t south_flag, uint32_t offset_x, uint32_t offset_y)
{
    return (COORDINATE_TYPE_UTM6 << COORDINATE_TYPE_OFFSET) |
           ((offset_x & COORDINATE_UTM_PARAM_OFFSET_X_BASE_MASK) << COORDINATE_UTM_PARAM_OFFSET_X_OFFSET) |
           ((offset_y & COORDINATE_UTM_PARAM_OFFSET_Y_BASE_MASK) << COORDINATE_UTM_PARAM_OFFSET_Y_OFFSET) |
           ((south_flag & COORDINATE_UTM_PARAM_SOUTH_FLAG_BASE_MASK) << COORDINATE_UTM_PARAM_SOUTH_FLAG_OFFSET) |
           ((zone_id & COORDINATE_UTM_PARAM_ZONE_ID_BASE_MASK) << COORDINATE_UTM_PARAM_ZONE_ID_OFFSET);
}

Coordinate_t coordinate_utm_create(uint8_t zone_id, bool_t south_flag, uint32_t offset_x, uint32_t offset_y)
{
    return (COORDINATE_TYPE_UTM6 << COORDINATE_TYPE_OFFSET) |
           ((offset_x & COORDINATE_UTM_PARAM_OFFSET_X_BASE_MASK) << COORDINATE_UTM_PARAM_OFFSET_X_OFFSET) |
           ((offset_y & COORDINATE_UTM_PARAM_OFFSET_Y_BASE_MASK) << COORDINATE_UTM_PARAM_OFFSET_Y_OFFSET) |
           ((south_flag & COORDINATE_UTM_PARAM_SOUTH_FLAG_BASE_MASK) << COORDINATE_UTM_PARAM_SOUTH_FLAG_OFFSET) |
           ((zone_id & COORDINATE_UTM_PARAM_ZONE_ID_BASE_MASK) << COORDINATE_UTM_PARAM_ZONE_ID_OFFSET);
}

Coordinate_t coordinate_utm3_create(uint8_t zone_id, bool_t south_flag, uint32_t offset_x, uint32_t offset_y)
{
    return (COORDINATE_TYPE_UTM3 << COORDINATE_TYPE_OFFSET) |
           ((offset_x & COORDINATE_UTM_PARAM_OFFSET_X_BASE_MASK) << COORDINATE_UTM_PARAM_OFFSET_X_OFFSET) |
           ((offset_y & COORDINATE_UTM_PARAM_OFFSET_Y_BASE_MASK) << COORDINATE_UTM_PARAM_OFFSET_Y_OFFSET) |
           ((south_flag & COORDINATE_UTM_PARAM_SOUTH_FLAG_BASE_MASK) << COORDINATE_UTM_PARAM_SOUTH_FLAG_OFFSET) |
           ((zone_id & COORDINATE_UTM_PARAM_ZONE_BASE_MASK) << COORDINATE_UTM_PARAM_ZONE_OFFSET);
}

Coordinate_t coordinate_dr_create(uint16_t version)
{
    return (COORDINATE_TYPE_DR << COORDINATE_TYPE_OFFSET) | (version);
}
