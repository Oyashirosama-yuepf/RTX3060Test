/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file speed_limit_info.h
 * @brief get speed limit info along router.
 * @author jiangdianqin(jiangdianqin@holomaitc.com)
 * @date "2021-01-08"
 */
#ifndef HOLO_MAP_CORE_NAVIGATOR_SERVICE_SPEED_LIMIT_ROUTE_INFO_H_
#define HOLO_MAP_CORE_NAVIGATOR_SERVICE_SPEED_LIMIT_ROUTE_INFO_H_

#include "holo/map/common/common_define.h"
#include "holo/map/feature/navigator/router/route_info.h"
#include "holo/map/common/match_info.h"
#include "holo/map/road_speed_limits.h"

namespace holo
{
namespace map
{
namespace speed_limit_info
{
/**
 * @brief Get main lane ids along the main road
 *
 * @param[in] ret
 * @param[in] routing_info
 * @param[in] current_lane_id
 * @param[in] lane_ids
 * @param[in|out] vec_lane_ids
 * @return true
 * @return false
 */
bool GetMainLaneIds(RetrieverSPType const& ret, RouteInfo2 const& routing_info, IdType current_lane_id,
                    std::vector<IdType> lane_ids, std::vector<std::vector<IdType>>& vec_lane_ids);

/**
 * @brief Get router of lane level
 *
 * @param[in] ret
 * @param[in] matching_info
 * @param[in] routing_info
 * @param[out] lane_ids
 * @return true
 * @return false
 */
bool GetRouteInLaneLevel(RetrieverSPType const& ret, MapMatchInfo const& matching_info, RouteInfo2 const& routing_info,
                         std::vector<IdType>& lane_ids);

/**
 * @brief Get route speed limit info v2
 *
 * @param[in] ret
 * @param[in] matching_info
 * @param[in] routing_info
 * @param[out] speed_limit_infos
 * @param[in] max_distance
 * @return true
 * @return false
 */
bool GetRouteSpeedLimitv2(RetrieverSPType const& ret, MapMatchInfo const& matching_info, RouteInfo2 const& routing_info,
                          RoadSpeedLimits& speed_limit_infos, Distance const max_distance = 2000.0f);

/**
 * @brief Get the Panel Speed Limit object
 *
 * @param actual_speed_limit
 * @return holo::float64_t
 */
holo::float64_t GetPanelSpeedLimit(holo::float64_t actual_speed_limit);

/**
 * @brief Get the Actual Speed Limit object from Map Speed Limit
 *
 * @param map_speed_limit
 * @return holo::float64_t
 */
holo::float64_t GetActualSpeedLimit(holo::float64_t const map_speed_limit);

/**
 * @brief  Convert actual speed limit to panel speed limit
 *
 * @param road_speed_limits
 */
void ConvertToPanelSpeedLimit(RoadSpeedLimits& road_speed_limits);
}  // namespace speed_limit_info
}  // namespace map
}  // namespace holo
#endif  // HOLO_MAP_CORE_NAVIGATOR_SERVICE_SPEED_LIMIT_ROUTE_INFO_H_