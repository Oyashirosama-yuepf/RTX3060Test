/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file across_zone_conversion.h
 * @brief utm conversion
 * @author Jiangdianqin(jiangdianqin@holomaitc.com)
 * @date 2020-03-30
 */

#ifndef HOLO_MAP_COMMON_ACROSS_ZONE_CONVERSION_H_
#define HOLO_MAP_COMMON_ACROSS_ZONE_CONVERSION_H_

#include <holo/core/types.h>
#include <holo/map/format/common/geo_box.h>
#include <holo/map/format/common/geo_line.h>
#include <holo/map/format/common/geo_point.h>
#include <holo/map/format/common/position.h>
#include <holo_c/core/retcode.h>
#include <holo_c/utils/geographical_transformation.h>

namespace holo
{
namespace map
{
/**
 * @addtogroup across_zone
 *
 * @{
 */
namespace across_zone
{
/**
 * @addtogroup conversion
 *
 * @{
 */

namespace conversion
{

/* @brief Convert a point given in longitude and latitude to UTM coordinate system
 * @note This version use input zone id instead of default zone id
 * @param[in] zone_id zone id for conversion
 * @param[in] is_south_hemisphere true, if it is in southern hemisphere
 * @param[in] lat latitude in units of degrees
 * @param[in] lon longitude in units of degrees
 * @param[out] x utm x to be calculated, given in units of meters
 * @param[out] y utm y to be calculated, given in units of meters
 * @return true, if conversion successfully, return true
 * @return false, if error happens
 * */
::holo::bool_t ConvertLLToUTM(const ::holo::uint8_t zone_id, const ::holo::bool_t is_south_hemisphere,
                              const ::holo::float64_t lat, const ::holo::float64_t lon, ::holo::float64_t& x,
                              ::holo::float64_t& y);

/* @brief Convert a point in UTM coordinate to longitude and latitude
 * @note This version use input zone id instead of default zone id
 * @param[in] zone_id zone id for conversion
 * @param[in] is_south_hemisphere true, if it is in southern hemisphere
 * @param[in] x utm x in units of meters
 * @param[in] y utm y in units of meters
 * @param[out] lat latitude to be calculated in units of degrees
 * @param[out] lon longitude to be calculated in units of degrees
 * @return true, if conversion successfully,return true
 * @return false, if error happens
 * */
::holo::bool_t ConvertUTMToLL(const ::holo::uint8_t zone_id, const ::holo::bool_t is_south_hemisphere,
                              const ::holo::float64_t x, const ::holo::float64_t y, ::holo::float64_t& lat,
                              ::holo::float64_t& lon);

/**
 * @brief Convert a point from one coordinate to another
 *
 * @param[in]  origin_zone_id origin zone id for conversion
 * @param[in]  origin_south_flag origin south flag
 * @param[in]  target_zone_id target zone id
 * @param[in]  target_south_flag target south flag
 * @param[in]  origin_x utm x in units of meters
 * @param[in]  origin_y utm y in units of meters
 * @param[out] target_x utm x to be calculated, given in units of meters
 * @param[out] target_y utm y to be calculated, given in units of meters
 * @return true, if conversion successfully,return true
 * @return false, if error happens
 */
::holo::bool_t ConvertUTMToUTM(const ::holo::uint8_t origin_zone_id, const ::holo::bool_t origin_south_flag,
                               const ::holo::uint8_t target_zone_id, const ::holo::bool_t target_south_flag,
                               const ::holo::float64_t origin_x, const ::holo::float64_t origin_y,
                               ::holo::float64_t& target_x, ::holo::float64_t& target_y);

/**
 * @brief Convert a point from one coordinate to another
 *
 * @param[in]  origin_zone_id origin zone id for conversion
 * @param[in]  origin_south_flag origin south flag
 * @param[in]  target_zone_id target zone id
 * @param[in]  target_south_flag target south flag
 * @param[in]  origin_point
 * @param[out] target_point
 * @return true, if conversion successfully,return true
 * @return false, if error happens
 */
::holo::bool_t ConvertUTMToUTM(const ::holo::uint8_t origin_zone_id, const ::holo::bool_t origin_south_flag,
                               const ::holo::uint8_t target_zone_id, const ::holo::bool_t target_south_flag,
                               const map::format::GeoPoint& origin_point, map::format::GeoPoint& target_point);

/**
 * @brief Convert a vector of point from one coordinate to another
 *
 * @param[in]  origin_zone_id origin zone id for conversion
 * @param[in]  origin_south_flag origin south flag
 * @param[in]  target_zone_id target zone id
 * @param[in]  target_south_flag target south flag
 * @param[in]  origin_points
 * @param[out] target_points
 * @return true, if conversion successfully,return true
 * @return false, if error happens
 */
::holo::bool_t ConvertUTMToUTM(const ::holo::uint8_t origin_zone_id, const ::holo::bool_t origin_south_flag,
                               const ::holo::uint8_t target_zone_id, const ::holo::bool_t target_south_flag,
                               const std::vector<map::format::GeoPoint>& origin_points,
                               std::vector<map::format::GeoPoint>&       target_points);

/**
 * @brief Convert a line from one coordinate to another
 *
 * @param[in]  origin_zone_id origin zone id for conversion
 * @param[in]  origin_south_flag origin south flag
 * @param[in]  target_zone_id target zone id
 * @param[in]  target_south_flag target south flag
 * @param[in]  origin_line
 * @param[out] target_line
 * @return true, if conversion successfully,return true
 * @return false, if error happens
 */
::holo::bool_t ConvertUTMToUTM(const ::holo::uint8_t origin_zone_id, const ::holo::bool_t origin_south_flag,
                               const ::holo::uint8_t target_zone_id, const ::holo::bool_t target_south_flag,
                               const map::format::GeoLine& origin_line, map::format::GeoLine& target_line);
/**
 * @brief Convert a vector of line from one coordinate to another
 *
 * @param[in]  origin_zone_id origin zone id for conversion
 * @param[in]  origin_south_flag origin south flag
 * @param[in]  target_zone_id target zone id
 * @param[in]  target_south_flag target south flag
 * @param[in]  origin_lines
 * @param[out] target_lines
 * @return true, if conversion successfully,return true
 * @return false, if error happens
 */
::holo::bool_t ConvertUTMToUTM(const ::holo::uint8_t origin_zone_id, const ::holo::bool_t origin_south_flag,
                               const ::holo::uint8_t target_zone_id, const ::holo::bool_t target_south_flag,
                               const std::vector<map::format::GeoLine>& origin_lines,
                               std::vector<map::format::GeoLine>&       target_lines);

/**
 * @brief Convert a box from one coordinate to another
 *
 * @param[in]  origin_zone_id origin zone id for conversion
 * @param[in]  origin_south_flag origin south flag
 * @param[in]  target_zone_id target zone id
 * @param[in]  target_south_flag target south flag
 * @param[in]  origin_box
 * @param[out] target_box
 * @return true, if conversion successfully,return true
 * @return false, if error happens
 */
::holo::bool_t ConvertUTMToUTM(const ::holo::uint8_t origin_zone_id, const ::holo::bool_t origin_south_flag,
                               const ::holo::uint8_t target_zone_id, const ::holo::bool_t target_south_flag,
                               const map::format::GeoBox& origin_box, map::format::GeoBox& target_box);

/**
 * @brief Convert a position from one coordinate to another
 *
 * @param[in]  origin_zone_id origin zone id for conversion
 * @param[in]  origin_south_flag origin south flag
 * @param[in]  target_zone_id target zone id
 * @param[in]  target_south_flag target south flag
 * @param[in]  origin_position
 * @param[out] target_position
 * @return true, if conversion successfully,return true
 * @return false, if error happens
 */
::holo::bool_t ConvertUTMToUTM(const ::holo::uint8_t origin_zone_id, const ::holo::bool_t origin_south_flag,
                               const ::holo::uint8_t target_zone_id, const ::holo::bool_t target_south_flag,
                               const map::format::Position& origin_position, map::format::Position& target_position);

/**
 * @brief Convert a vector of position from one coordinate to another
 *
 * @param[in]  origin_zone_id origin zone id for conversion
 * @param[in]  origin_south_flag origin south flag
 * @param[in]  target_zone_id target zone id
 * @param[in]  target_south_flag target south flag
 * @param[in]  origin_positions
 * @param[out] target_positions
 * @return true, if conversion successfully,return true
 * @return false, if error happens
 */
::holo::bool_t ConvertUTMToUTM(const ::holo::uint8_t origin_zone_id, const ::holo::bool_t origin_south_flag,
                               const ::holo::uint8_t target_zone_id, const ::holo::bool_t target_south_flag,
                               const std::vector<map::format::Position>& origin_positions,
                               std::vector<map::format::Position>&       target_positions);

/**
 * @brief Get UTM Zone id by latitude and longitude
 *
 * @param lat latitude in units of degrees
 * @param lon longitude in units of degrees
 * @param zone_id
 * @return true, if Compute UTM Zone successfully
 * @return false, if error happens
 */
::holo::bool_t ComputeUTMZone(const ::holo::float64_t lon, ::holo::uint8_t& zone_id);

}  /// namespace conversion
/**
 * @}
 */
}  /// namespace across_zone

/**
 * @}
 */
}  /// namespace map
}  /// namespace holo
#endif /* HOLO_MAP_COMMON_ACROSS_ZONE_CONVERSION_H_ */