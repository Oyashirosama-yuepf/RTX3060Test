/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sensor_id.h
 * @brief This header file defines sensor id.
 * @author ZhangJiannan (zhangjiannan@holomatic.com)
 * @date 2019-12-6
 */

#ifndef HOLO_C_COMMON_SENSOR_ID_H_
#define HOLO_C_COMMON_SENSOR_ID_H_

#include <holo_c/common/vehicle_location.h>
#include <holo_c/core/types.h>

/**
 * @brief Codec for sensor id.
 *
 * @details A sensor-id is consist of three parts: sensor-class, sensor-model and sensor-location.
 *
 * 0                   1                   2                   3
 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-------+-------+---------------+-------------------------------+
 * |  RSV  | CLASS |     MODEL     |           LOCATION            |
 * +-------+-------+---------------+-------------------------------+
 * 
 * RSV: Reserved.
 *
 * sensor-class: Sensor classification. See ::SensorClass for possible values.
 *
 * sensor-model: Model of the sensor. See SensorModel<CLASS> for possible values for each sensor-class.
 *
 * sensor-location: Location of type ::VehicleLocation_t indicating where sensor is mounted.
 */
typedef uint32_t SensorId_t;

/**
 * @brief Values of sensor classes
 */
enum SensorClass
{
    SENSOR_CLASS_UNKNOWN = 0x0, ///< Unknown class
    SENSOR_CLASS_GNSS    = 0x1, ///< GNSS
    SENSOR_CLASS_IMU     = 0x2, ///< IMU
    SENSOR_CLASS_CAMERA  = 0x3, ///< CAMERA
    SENSOR_CLASS_RADAR   = 0x4, ///< RADAR
    SENSOR_CLASS_USS     = 0x5, ///< USS
    SENSOR_CLASS_LIDAR   = 0x6, ///< LIDAR
    SENSOR_CLASS_AUDIO   = 0x7, ///< AUDIO
};

/**
 * @brief Sensor model type.
 */
typedef uint8_t SensorModel_t;

enum SensorModelUnknown
{
    SENSOR_MODEL_UNKNOWN = 0x00,
};

enum SensorModelGnss
{
    SENSOR_MODEL_GNSS_UNKNOWN   = 0x00,
    SENSOR_MODEL_GNSS_NOVATEL   = 0x01,
    SENSOR_MODEL_GNSS_UBLOX_M8L = 0x02,
    SENSOR_MODEL_GNSS_XSENS     = 0x03,
};

enum SensorModelImu
{
    SENSOR_MODEL_IMU_UNKNOWN   = 0x00,
    SENSOR_MODEL_IMU_NOVATEL   = 0x01,
    SENSOR_MODEL_IMU_UBLOX_M8L = 0x02,
    SENSOR_MODEL_IMU_XSENS     = 0x03,
    SENSOR_MODEL_IMU_ACEINNA   = 0x04,
};

enum SensorModelCamera
{
    SENSOR_MODEL_CAMERA_UNKNOWN      = 0x00,
    SENSOR_MODEL_CAMERA_MOBILEYE_EQ3 = 0x01,
    SENSOR_MODEL_CAMERA_MOBILEYE_EQ4 = 0x02,
    SENSOR_MODEL_CAMERA_BOSCH_MPC    = 0x03,
};

enum SensorModelRadar
{
    SENSOR_MODEL_RADAR_UNKNOWN = 0x00,
    // add radar models here.
};

enum SensorModelUss
{
    SENSOR_MODEL_USS_UNKNOWN = 0x00,
};

enum SensorModelLidar
{
    SENSOR_MODEL_LIDAR_UNKNOWN        = 0x00,
    SENSOR_MODEL_LIDAR_IBEO_SCALAR    = 0x01,
    SENSOR_MODEL_LIDAR_IBEO_LUX       = 0x02,
    SENSOR_MODEL_LIDAR_VELODYNE_VPL16 = 0x03,
};

enum SensorModelAudio
{
    SENSOR_MODEL_AUDIO_UNKNOWN = 0x00,
};

static inline SensorId_t sensor_id_create(enum SensorClass cls, uint8_t model, VehicleLocation_t location)
{
    return (SensorId_t)(((uint32_t)cls << 24) | ((uint32_t)model << 16) | ((uint32_t)location));
}

static inline enum SensorClass sensor_id_get_class(const SensorId_t* id)
{
    return (enum SensorClass)(*id >> 24);
}

static inline SensorModel_t sensor_id_get_model(const SensorId_t* id)
{
    return (SensorModel_t)(*id >> 16);
}

static inline VehicleLocation_t sensor_id_get_location(const SensorId_t* id)
{
    return (VehicleLocation_t)(*id);
}

#endif

