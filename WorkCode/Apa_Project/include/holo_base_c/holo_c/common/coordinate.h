/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file coordinate.h
 * @brief This header file defines coordinate system.
 * @author ZhangJiannan (zhangjiannan@holomatic.com)
 * @date 2019-11-26
 */

#ifndef HOLO_C_COMMON_COORDINATE_H_
#define HOLO_C_COMMON_COORDINATE_H_

#include <holo_c/common/sensor_id.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup common
 * @{
 */

/**
 * @brief Coordinate_t type represents a coordinate system.
 *
 * @details The Coordinate_t type consists of two parts: @b type and @b param.
 *
 * The @b type part indicates the type of coordinate system. The value should be one of ::CoordinateType.
 * Coordinate types may associate with parameters.
 *
 * The @b param indicates additional information about the coordinate system.
 * The structure of @b param varies from different coordinate types. See @ref page_coordinate_system "Coordinate System"
 * for more details.
 */
typedef uint32_t Coordinate_t;

#define COORDINATE_UTM_GRID_WIDTH 4096
#define COORDINATE_UTM_GRID_HEIGHT 4096

/**
 * @brief Type of coordinate system.
 */
enum CoordinateType
{
    COORDINATE_TYPE_UNKNOWN = 0,  ///< Unknown coordinate type.
    COORDINATE_TYPE_VEHICLE = 1,  ///< VEHICLE coordinate.
    COORDINATE_TYPE_WGS84   = 2,  ///< WGS84 coordinate.
    COORDINATE_TYPE_UTM6    = 3,  ///< UTM 6 degree sliced coordinate
    COORDINATE_TYPE_UTM3    = 4,  ///< UTM 3 degree sliced coordinate
    COORDINATE_TYPE_DR      = 5,  ///< Dead reckoning coordinate

    COORDINATE_TYPE_GCJ02   = 11,  ///< GCJ02 coordinate.
    COORDINATE_TYPE_CUSTOM0 = 12,  ///< User defined coordinate system 0
    COORDINATE_TYPE_CUSTOM1 = 13,  ///< User defined coordinate system 1
    COORDINATE_TYPE_CUSTOM2 = 14,  ///< User defined coordinate system 2
    COORDINATE_TYPE_CUSTOM3 = 15,  ///< User defined coordinate system 3
};

/**
 * @brief This enumerate lists some predifined VEHICLE sensor_id parameter.
 */
enum COORDINATE_VEHICLE_PARAM_SENSORID
{
    COORDINATE_VEHICLE_PARAM_REAR_AXLE_CENTER = 0x00000c7b,
    COORDINATE_VEHICLE_PARAM_IMU_VEHICLE      = 0x02000c77,
};

/**
 * @brief Get coordinate system type.
 *
 * @param coordinate The coordinate object.
 *
 * @return Coordinate system type.
 */
enum CoordinateType coordinate_get_type(const Coordinate_t* coordinate);

/**
 * @brief Set coordinate system type.
 *
 * @param coordinate The coordinate object
 * @param type Coordinate system type
 */
void coordinate_set_type(Coordinate_t* coordinate, enum CoordinateType type);

/**
 * @brief Get coordinate system parameter
 *
 * @param coordinate The coordinate object.
 *
 * @return Parameter of coordinate.
 */
uint32_t coordinate_get_param(const Coordinate_t* coordinate);

/**
 * @brief Set coordinate system parameter
 *
 * @param coordinate The coordinate object.
 * @param param Parameter of coordinate.
 */
void coordinate_set_param(Coordinate_t* coordinate, uint32_t param);

/**
 * @brief Get VEHICLE coordinate sensor-id parameter
 *
 * @param coordinate The coordinate object in types of VEHICLE.
 *
 * @return VEHICLE coordinate sensor-id parameter.
 */
SensorId_t coordinate_vehicle_get_sensor_id(const Coordinate_t* coordinate);

/**
 * @brief Set VEHICLE coordinate sensor_id parameter
 *
 * @param coordinate The coordinate object in types of VEHICLE.
 * @param sensor_id VEHICLE coordinate sensor_id parameter.
 */
void coordinate_vehicle_set_sensor_id(Coordinate_t* coordinate, SensorId_t sensor_id);

/**
 * @brief Set UTM coordinate system(UTM3 or UTM6) zone number
 *
 * @param coordinate The coordinate object in types of UTM6 of UTM3.
 * @param zone_id Zone number
 */
void coordinate_utm_set_zone_id(Coordinate_t* coordinate, uint8_t zone_id);

/**
 * @brief Set UTM coordinate system(UTM3 or UTM6) zone. Utm zone is consist of two parts: zone_id and south_flag.
 *
 * @param coordinate The coordinate object in types of UTM6 of UTM3.
 * @param zone UTM zone
 */
void coordinate_utm_set_zone(Coordinate_t* coordinate, uint8_t zone);

/**
 * @brief Get UTM coordinate system(UTM3 or UTM6) zone number.
 *
 * @param coordinate The coordinate object in types of UTM6 of UTM3.
 *
 * @return UTM zone number.
 */
uint8_t coordinate_utm_get_zone_id(const Coordinate_t* coordinate);

/**
 * @brief Get UTM coordinate system(UTM3 or UTM6) zone. Utm zone is consist of two parts: zone_id and south_flag.
 *
 * @param coordinate The coordinate object in types of UTM6 of UTM3.
 *
 * @return UTM zone.
 */
uint8_t coordinate_utm_get_zone(const Coordinate_t* coordinate);

/**
 * @brief Set South flag of UTM coordinate.
 *
 * @param coordinate The coordinate object.
 */
void coordinate_utm_set_south_flag(Coordinate_t* coordinate);

/**
 * @brief Reset South flag of UTM coordinate.
 *
 * @param coordinate The coordinate object.
 */
void coordinate_utm_reset_south_flag(Coordinate_t* coordinate);

/**
 * @brief Get south flag of UTM coordinate.
 *
 * @param coordinate The coordinate object.
 *
 * @return South flag
 */
bool coordinate_utm_get_south_flag(const Coordinate_t* coordinate);

/**
 * @brief Set UTM coordinate system(UTM3 or UTM6) latitudinal(Easting) offset number.
 *
 * @param coordinate The coordinate object in types of UTM6 of UTM3.
 * @param x offset number in latitudinal(Easting) direction.
 */
void coordinate_utm_set_offset_x(Coordinate_t* coordinate, uint32_t x);

/**
 * @brief Get UTM coordinate system(UTM3 or UTM6) latitudinal(Easting) offset number.
 *
 * @param coordinate The coordinate object in types of UTM6 of UTM3.
 *
 * @return Offset number in latitudinal(Easting) direction.
 */
uint32_t coordinate_utm_get_offset_x(const Coordinate_t* coordinate);

/**
 * @brief Set UTM coordinate system(UTM3 or UTM6) longitudinal(Northing) offset number.
 *
 * @param coordinate The coordinate object in types of UTM6 of UTM3.
 * @param y offset number in longitudinal(Northing) direction.
 */
void coordinate_utm_set_offset_y(Coordinate_t* coordinate, uint32_t y);

/**
 * @brief Get UTM coordinate system(UTM3 or UTM6) longitudinal(Northing) offset number.
 *
 * @param coordinate The coordinate object in types of UTM6 of UTM3.
 *
 * @return Offset number in longitudinal(Northing) direction.
 */
uint32_t coordinate_utm_get_offset_y(const Coordinate_t* coordinate);

/**
 * @brief Set DR coordinate version.
 *
 * @param coordinate The cooridnate object in type of DR
 * @param version Version of DR coordinate.
 */
void coordinate_dr_set_version(Coordinate_t* coordinate, uint16_t version);

/**
 * @brief Get DR coordinate version.
 *
 * @param coordinate The coordinate object in type of DR
 *
 * @return Version of DR coordinate.
 */
uint16_t coordinate_dr_get_version(Coordinate_t const* coordinate);

/**
 * @brief Create default coordinate object. Coordinate type is COORDINATE_TYPE_UNKNOWN.
 *
 * @return New coordinate object.
 */
Coordinate_t coordinate_default_create();

/**
 * @brief Create VEHICLE type coordinate object.
 *
 * @param sensor_id VEHICLE coordinate sensor_id parameter
 *
 * @return New coordinate object.
 */
Coordinate_t coordinate_vehicle_create(SensorId_t sensor_id);

/**
 * @brief Create WGS84 type coordinate object.
 *
 * @return New coordinate object.
 */
Coordinate_t coordinate_wgs84_create();

/**
 * @brief Create UTM6 type coordinate object.
 *
 * @param zone_id UTM zone number.
 * @param south_flag Flags indicate whether the UTM position is in south hemisphere.
 * @param offset_x Offset number in latitudinal direction.
 * @param offset_y Offset number in longitudinal direction.
 *
 * @return New coordinate object.
 */
Coordinate_t coordinate_utm6_create(uint8_t zone_id, bool_t south_flag, uint32_t offset_x, uint32_t offset_y);

/**
 * @brief Create UTM6 type coordinate object.
 *
 * @param zone_id UTM zone number.
 * @param south_flag Flags indicate whether the UTM position is in south hemisphere.
 * @param offset_x Offset number in latitudinal direction.
 * @param offset_y Offset number in longitudinal direction.
 *
 * @return New coordinate object.
 */
Coordinate_t coordinate_utm_create(uint8_t zone_id, bool_t south_flag, uint32_t offset_x, uint32_t offset_y);

/**
 * @brief Create UTM3 type coordinate object.
 *
 * @param zone_id UTM zone number.
 * @param south_flag Flags indicate whether the UTM position is in south hemisphere.
 * @param offset_x Offset number in latitudinal direction.
 * @param offset_y Offset number in longitudinal direction.
 *
 * @return New coordinate object.
 */
Coordinate_t coordinate_utm3_create(uint8_t zone_id, bool_t south_flag, uint32_t offset_x, uint32_t offset_y);

/**
 * @brief Create dead reckoning coordinate object.
 *
 * @param version dead reckoning coordinate version.
 *
 * @return New coordinate object.
 */
Coordinate_t coordinate_dr_create(uint16_t version);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_COMMON_COORDINATE_H */
