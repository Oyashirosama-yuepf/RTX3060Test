/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vehicle_location.h
 * @brief This header file defines vehicle location type.
 * @author ZhangJiannan (zhangjiannan@holomatic.com)
 * @date 2019-12-6
 */

#ifndef HOLO_C_COMMON_VEHICLE_LOCATION_H_
#define HOLO_C_COMMON_VEHICLE_LOCATION_H_

#include <holo_c/core/types.h>

/**
 * @brief VehicleLocation object represents a location in a vehicle.
 *
 * @details A location of a vehicle is represented as a `plane id`, `coordinate-x` and `coordinate-y` on that plane.
 *
 * @f[
 * \begin{bytefield}{16}
 *   \bitheader{0-15} \\
 *   \bitbox{8}{plane\_id} & \bitbox{4}{X} & \bitbox{4}{Y}
 * \end{bytefield}
 * @f]
 *
 * @todo Insert a picture here to illustrate the coordinate for each plane.
 *
 * `plane-id`: A 8 bit value indicates a plane on a vehicle. See ::VehicleLocationPlane for possible values.
 *
 * `coordinate-x`: A 4-bit value indicating position in X-axis. 0x0 is reserved as unknown position.
 *
 * `coordinate-y`:A 4-bit value indicating position in Y-axis. 0x0 is reserved as unknown position.
 *
 * In this codec way, each vehicle plane is marked with a 15x15 grid. To simply the usage for ordinary cases,
 * ::VehicleLocationLocation is defined for most commonly used locations.
 *
 * For instance a VehicleLocation 0x018F means the top center of a vehicle's front side plane.
 * A VehicleLocation 0x038C means the middle front of vehicle's left side plane.
 */
typedef uint16_t VehicleLocation_t;

/**
 * @brief Enumerates vehicle planes.
 */
enum VehicleLocationPlane
{
    VEHICLE_LOCATION_PLANE_UNKNOWN      = 0x00,
    VEHICLE_LOCATION_PLANE_FRONT        = 0x01,
    VEHICLE_LOCATION_PLANE_REAR         = 0x02,
    VEHICLE_LOCATION_PLANE_LEFT         = 0x03,
    VEHICLE_LOCATION_PLANE_RIGHT        = 0x04,
    VEHICLE_LOCATION_PLANE_FRONT_WINDOW = 0x05,
    VEHICLE_LOCATION_PLANE_REAR_WINDOW  = 0x06,
    VEHICLE_LOCATION_PLANE_LEFT_WINDOWN = 0x07,
    VEHICLE_LOCATION_PLANE_RIGHT_WINDOW = 0x08,
    VEHICLE_LOCATION_PLANE_ENGINE_HOOD  = 0x09,
    VEHICLE_LOCATION_PLANE_ROOF         = 0x0a,
    VEHICLE_LOCATION_PLANE_TRUNK_DOOR   = 0x0b,
    VEHICLE_LOCATION_PLANE_CHASSIS      = 0x0c,
    VEHICLE_LOCATION_PLANE_TRUNK        = 0x0d,
    VEHICLE_LOCATION_PLANE_COCKPIT      = 0x0e,
    VEHICLE_LOCATION_PLANE_GROUD        = 0x0f,
};

/**
 * @brief Some frequently used locations.
 */
enum VehicleLocationLocation
{
    VEHICLE_LOCATION_LOCATION_UNKNOWN       = 0x0,
    VEHICLE_LOCATION_COORDINATE_TOP_MOST    = 0x1,
    VEHICLE_LOCATION_COORDINATE_FRONT_MOST  = 0x1,
    VEHICLE_LOCATION_COORDINATE_LEFT_MOST   = 0x1,
    VEHICLE_LOCATION_COORDINATE_TOP         = 0x4,
    VEHICLE_LOCATION_COORDINATE_FRONT       = 0x4,
    VEHICLE_LOCATION_COORDINATE_LEFT        = 0x4,
    VEHICLE_LOCATION_COORDINATE_MIDDLE      = 0x8,
    VEHICLE_LOCATION_COORDINATE_CENTER      = 0x8,
    VEHICLE_LOCATION_COORDINATE_BOTTOM      = 0xC,
    VEHICLE_LOCATION_COORDINATE_REAR        = 0xC,
    VEHICLE_LOCATION_COORDINATE_RIGHT       = 0xC,
    VEHICLE_LOCATION_COORDINATE_BOTTOM_MOST = 0xF,
    VEHICLE_LOCATION_COORDINATE_REAR_MOST   = 0xF,
    VEHICLE_LOCATION_COORDINATE_RIGHT_MOST  = 0xF,
};

static inline VehicleLocation_t vehicle_location_create(enum VehicleLocationPlane plane, uint8_t coordinate_x,
                                                        uint8_t coordinate_y)
{
    return (VehicleLocation_t)(((uint16_t)plane << 8) | (((uint16_t)coordinate_x & 0x0f) << 4) |
                               ((uint16_t)coordinate_y & 0x0f));
}

static inline enum VehicleLocationPlane vehicle_location_get_plane(const VehicleLocation_t* location)
{
    return (enum VehicleLocationPlane)(*location >> 8);
}

static inline uint8_t vehicle_location_get_coordinate_x(const VehicleLocation_t* location)
{
    return (uint8_t)((*location >> 4) & 0x0f);
}

static inline uint8_t vehicle_location_get_coordinate_y(const VehicleLocation_t* location)
{
    return (uint8_t)(*location & 0x0f);
}

#endif
