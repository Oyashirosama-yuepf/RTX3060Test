/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sensors_utils.h.
 * @brief the sensors common utils.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-10.
 */

#ifndef _HOLO_SENSORS_COMMON_UTILS_SENSORS_UTILS_H
#define _HOLO_SENSORS_COMMON_UTILS_SENSORS_UTILS_H

#include <cmath>
#include <map>
#include <string>

#include <holo/common/coordinate.h>
#include <holo/common/sensor_id.h>
#include <holo/core/types.h>
#include <holo/utils/holo_root.h>

#if defined(MDC_PRODUCTION_MDC610)
#include <holo/sensors/utils/mdc610_utils.h>
#endif

namespace holo
{
namespace sensors
{
static const float64_t Radius            = 6378245.0;               // earth radius
static const float64_t EarthEccentricity = 0.00669342162296594323;  //

using holo::common::Coordinate;
using holo::common::SensorId;
using holo::common::VehicleLocation;

enum class DataCompressAlgorithm : uint32_t
{
    NONE = 0,
    LZ4  = 1
};

/**
 * @brief Get holo sensors's Lib config file root path
 *
 */
std::string GetHoloSensorsLibConfigDirectory();

/**
 * @brief Get holo sensors's Extrinsics config file root path
 *
 */
std::string GetHoloSensorsExtrinsicsDirectory();

/**
 * @brief Get holo sensors's Intrinsics config file root path
 *
 */
std::string GetHoloSensorsIntrinsicsDirectory();

/**
 * @brief      construct VehicleLocation by strings
 *
 * @param[in]  plane  The plane
 * @param[in]  x      The sector x
 * @param[in]  y      The sector y
 *
 * @return     The VehicleLocation value
 */
VehicleLocation StringToVehicleLocation(const std::string& plane, const std::string& x, const std::string& y);

/**
 * @brief      construct SensorId by strings
 *
 * @param[in]  category  The category
 * @param[in]  model     The model
 * @param[in]  plane     The plane
 * @param[in]  x         The sector x
 * @param[in]  y         The sector y
 *
 * @return     The SensorId value
 */
SensorId StringToSensorId(const std::string& category, const std::string& model, const std::string& plane,
                          const std::string& x, const std::string& y);

/**
 * @brief      construct vehicle coordinate by strings
 *
 * @param[in]  category  The category
 * @param[in]  model     The model
 * @param[in]  plane     The plane
 * @param[in]  x         The sector x
 * @param[in]  y         The sector y
 *
 * @return     The Vehicle Coordinate value
 */
Coordinate StringToVehicleCoordinate(const std::string& category, const std::string& model, const std::string& plane,
                                     const std::string& x, const std::string& y);

/**
 * @brief Convert the latitude and longitude from the WGS84 coordinate to the GCJ-02 coordinate (Mars Geodetic
 *        System)
 *
 * @param latitude The latitude of the WGS84 coordinate
 * @param longitude The longitude of the WGS84 coordinate
 * @return bool_t
 */
bool_t ConvertWgs84ToGcj02(float64_t& latitude, float64_t& longitude);

/**
 * @brief check file exist
 *
 * @param filename path of file
 *
 * @return true file exist
 */
bool_t FileExist(const std::string& filename);

}  // namespace sensors
}  // namespace holo
#endif  // _HOLO_SENSORS_COMMON_UTILS_SENSORS_UTILS_H
