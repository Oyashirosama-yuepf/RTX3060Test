/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common.h
 * @brief Common functions and definitions
 * @author lisong(lisong@holomatic.com)
 * @date "2020-09-15"
 */

#ifndef HOLO_MAP_FEATURE_ROAD_TYPE_INTERVAL_EXREACTOR_COMMON_H_
#define HOLO_MAP_FEATURE_ROAD_TYPE_INTERVAL_EXREACTOR_COMMON_H_

#include <holo/map/common/common_define.h>
#include <holo/map/feature/map_attributor/road_type_intervals/road_type_interval_extractor.h>

namespace holo
{

namespace map
{

namespace attribute
{

namespace road_type
{

/**
 * @brief Format holo::map::format::Road::RoadType object to json string.
 * 
 * @param[in] road_type A holo::map::format::Road::RoadType object
 * @return Json string
 */
std::string FormatToString(RawRoadTypeV0::RoadType const road_type);

/**
 * @brief Format holo::map::format::RoadAttribute::TollDir object to json string.
 * 
 * @param[in] toll_dir A holo::map::format::RoadAttribute::TollDir object
 * @return Json string
 */
std::string FormatToString(RawRoadAttributeTypeV0::TollDir const toll_dir);

/**
 * @brief Format holo::map::format::RoadAttribute object to json string.
 * 
 * @param[in] attribute A holo::map::format::RoadAttribute object
 * @return Json string
 */
std::string FormatToString(RawRoadAttributeTypeV0 const& attribute);

/**
 * @brief Format RoadTypeIntervalExtractor::RoadTypeInterval object to json string.
 * 
 * @param[in] interval A RoadTypeIntervalExtractor::RoadTypeInterval object
 * @return Json string
 */
std::string FormatToString(RoadTypeIntervalExtractor::RoadTypeInterval const& interval);

/**
 * @brief Format holo::map::format::Road::Direction object to json string.
 * 
 * @param[in] road_dir A holo::map::format::Road::Direction object
 * @return Json string
 */
std::string FormatToString(RawRoadTypeV0::Direction const road_dir);

/**
 * @brief Check if given road direction is unsupported.
 * @details We only support following road direction for road_type_interval needs:
 *      holo::map::format::Road::Direction::DIRECTION_POSITIVE_DIRECTION
 *      holo::map::format::Road::Direction::DIRECTION_NEGATIVE_DIRECTION
 * 
 * @param[in] road_dir Given road direction
 * 
 * @return True if it is unsupported,
 *         False if it is sported.
 */
holo::bool_t IsUnsupportedRoadDir(RawRoadTypeV0::Direction const road_dir);

/**
 * @brief Get length of road attribute, unit: meter.
 * 
 * @param[in] road_ptr Point of road that road attribute belongs to
 * @param[in] start_idx Index of start point of road attribute in geometry points of road 
 * @param[in] end_idx Index of end point of road attribute in geometry points of road 
 * @param[out] length Length of road attribute
 * 
 * @return True if successful,
 *         False if failed.
 */
holo::bool_t GetRoadAttributeLength(RawRoadSPtrTypeV0 const& road_ptr, std::size_t const start_idx,
                                    std::size_t const end_idx,  DistanceTypeV0& length);

/**
 * @brief Get terminal point of geometry points of road.
 * 
 * @param[in] road_ptr Pointer of road
 * @param[in] get_start_point If true get start point of road, else end point
 * @param[out] point Result point
 * 
 * @return True if successful,
 *         False if failed.
 */
holo::bool_t GetTerminalPointOfRoad(RawRoadSPtrTypeV0 const& road_ptr, holo::bool_t const get_start_point,
                                    RawGeoPointTypeV0& point);

/**
 * @brief Get length of line made by sub line of given line and point.
 * 
 * @param[in] ref_points Given line
 * @param[in] is_forward If true, given inner point should added to sub line' tail, else head
 * @param[in] first_idx Index of first point close to given inner point in ref_points
 * @param[in] second_idx Index of second point close to given inner point in ref_points
 * @param[in] inner_point Given point should added to sub line
 * @param[out] subline_length Result length of sub line
 * 
 * @return True if successful,
 *         False if failed.
 */
holo::bool_t GetSublineLength(RawGeometryTypeV0 const& ref_points, holo::bool_t const is_forward,
                              std::size_t const first_idx, std::size_t const second_idx,
                              RawGeoPointTypeV0 const& inner_point, DistanceTypeV0& subline_length);

/**
 * @brief Calculate distance from given point to start point of road along ref points of road
 *
 * @param[in] road_ptr Pointer of road
 * @param[in] point Given point
 * @param[out] to_start Result length, unit: meter
 *
 * @return True if successful,
 *         False if failed.
 */
holo::bool_t CalculateDistanceToRoadStart(RawRoadSPtrTypeV0 const&  road_ptr,
                                        RawGeoPointTypeV0 const& point, DistanceTypeV0& to_start);

/**
 * @brief Get road ids by route path and start index in route path
 * 
 * @param[in] ptr_ret Pointer of retriver
 * @param[in] route_info Route info, contains route path
 * @param[out] start_idx Index of start position in route path
 * @param[out] road_ids Result road ids
 * 
 * @return True if successful,
 *         False if failed.
 */
holo::bool_t GetRoadIDs(RetrieverSPType const& ptr_ret, holo::map::RouteInfo2 const& route_info,
                        std::size_t const start_idx, RawFeatureIdVectorTypeV0& road_ids);

/**
 * @brief Get index of link in current route path
 *
 * @param[in] current_link_id Given link id current car in
 * @param[in] route_info Given route info
 * @param[out] current_idx Index of given link in route path of given route info
 * @return True if successful,
 *         False if failed and current_idx will be max value of std::size_t.
 */
holo::bool_t GetCurrentIdxInRoutePath(RawFeatureIdTypeV0 const    current_link_id,
                                      holo::map::RouteInfo2 const& route_info, std::size_t& current_idx);

}  // end for road_type
}  // end for attribute
}  // end for namespace map
}  // end for namespace holo

#endif  // end for HOLO_MAP_FEATURE_ROAD_TYPE_INTERVAL_EXREACTOR_COMMON_H_
