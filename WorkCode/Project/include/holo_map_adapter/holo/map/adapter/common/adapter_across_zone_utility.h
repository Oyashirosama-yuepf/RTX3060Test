/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file across_zone_adapter_utility.h
 * @brief across zone common function
 * @author jiangdianqin(jiangdianqin@holomaitc.com)
 * @date "2020-08-17"
 */

#ifndef HOLO_MAP_ADATER_COMMON_ACROSS_ZONE_UTILITY_H_
#define HOLO_MAP_ADATER_COMMON_ACROSS_ZONE_UTILITY_H_

#include <vector>

#include "holo/map/adapter/base/geometry_base.h"
#include "holo/map/common/common_type_define.h"
#include "holo/map/common/classes/latlonh.h"
#include "holo/map/common/marshal.h"
#include "holo/map/adapter/base/geometry_base.h"

namespace holo
{
namespace map
{
namespace adapter
{
/**
 * @addtogroup adapter
 * @{
 *
 */

/**
 * @brief Get the extra geo boxes by coordinate
 * 
 * @param[in]  zone_id 
 * @param[in]  extra_zone_id 
 * @param[in]  is_near_equator
 * @param[in]  is_south_hemisphere 
 * @param[in]  box 
 * @param[out] extra_geo_points 
 */
void GetExtraGeoBoxes(const std::uint8_t zone_id, const std::uint8_t extra_zone_id, const bool is_near_equator,
                       const bool is_south_hemisphere, const holo::map::format::GeoBox& box,
                       std::map<std::uint32_t, holo::map::format::GeoBox>& extra_boxes);

/**
 * @brief Get the extra geo boxes by coordinate(Type : GeoBox4)
 *
 * @param[in]  zone_id
 * @param[in]  extra_zone_id
 * @param[in]  is_near_equator
 * @param[in]  is_south_hemisphere
 * @param[in]  box
 * @param[out] extra_boxes
 */
void GetExtraGeoBoxes(const std::uint8_t zone_id, const std::uint8_t extra_zone_id, const bool is_near_equator,
                       const bool is_south_hemisphere, const holo::map::format::GeoBox4& box,
                       std::map<std::uint32_t, holo::map::format::GeoBox4>& extra_boxes);

/**
 * @brief Get the extra geo points by coordinate
 * 
 * @param[in]  zone_id 
 * @param[in]  extra_zone_id 
 * @param[in]  is_near_equator
 * @param[in]  is_south_hemisphere 
 * @param[in]  geo_points 
 * @param[out] extra_geo_points 
 */
void GetExtraGeoPoints(const std::uint8_t zone_id, const std::uint8_t extra_zone_id, const bool is_near_equator,
                       const bool is_south_hemisphere, const std::vector<map::format::GeoPoint> &geo_points,
                       std::map<std::uint32_t, map::format::GeoLine> &extra_geo_points);

/**
 * @brief Get the extra geo points by coordiante
 * 
 * @param[in] zone_id 
 * @param[in] extra_zone_id 
 * @param[in] is_near_equator 
 * @param[in] is_south_hemisphere 
 * @param[in] geo_multi_line 
 * @param[out] extra_geo_multi_line 
 */
void GetExtraGeoPoints(const std::uint8_t zone_id, const std::uint8_t extra_zone_id, const bool is_near_equator,
                       const bool is_south_hemisphere, const std::vector<map::format::GeoLine> &geo_multi_line,
                       std::map<std::uint32_t, map::format::GeoMultiLine> &extra_geo_multi_line);

/**
 * @brief Get the extra positions by coordinate
 * 
 * @param[in] zone_id 
 * @param[in] extra_zone_id 
 * @param[in] is_near_equator 
 * @param[in] is_south_hemisphere 
 * @param[in] positions 
 * @param[out] extra_positions 
 */
void GetExtraPositions(const std::uint8_t zone_id, const std::uint8_t extra_zone_id, const bool is_near_equator,
                       const bool is_south_hemisphere, const std::vector<map::format::Position> &positions,
                       std::map<std::uint32_t, map::format::MultiPosition> &extra_positions);

/**
 * @brief Compute origin geometry points and extra geometry points
 * 
 * @param[in]  lls 
 * @param[out] zone_id
 * @param[out] extra_zone_id
 * @param[out] is_south_hemisphere
 * @param[out] is_near_equator
 */
void ComputeGeometrys(const std::vector<map::LL> &lls, std::uint8_t &zone_id, std::uint8_t &extra_zone_id,
                      bool &is_south_hemisphere, bool &is_near_equator);

/**
 * @brief Set the cross zone info into tile/road/lane_group/lane/lane_boundary/lane_boundary_info feature
 * 
 * @tparam T feature of tile/road/lane_group/lane/lane_boundary/lane_boundary_info
 * @param[in] wgs_geo_points 
 * @param[in] feature 
 * @param[out] near_equator 
 */
template <typename T>
void SetCrossZoneInfo(std::vector<format::GeoPoint> const &wgs_geo_points, std::shared_ptr<T> feature, bool &near_equator);

template <typename T>
void SetCrossZoneInfo(GeoBoxType const &wgs_geo_points, std::shared_ptr<T> feature, bool &near_equator);

template <typename T>
void SetCrossZoneInfo(GeoBox4Type const &wgs_geo_points, std::shared_ptr<T> feature, bool &near_equator);

/**
 * @brief Set the extra geometry to feature
 * 
 * @tparam T feature of tile/road/lane_group/lane/lane_boundary/lane_boundary_info
 * @param[in] utm_geo_points 
 * @param[in] feature 
 * @param[in] near_equator 
 */
template <typename T>
void SetExtraGeometry(std::vector<format::GeoPoint>const &utm_geo_points, std::shared_ptr<T> feature, bool near_equator);
/**
 * @}
 *
 */

} // namespace adapter
} // namespace map
} // namespace holo

#endif //HOLO_MAP_ADATER_COMMON_ACROSS_ZONE_UTILITY_H_
