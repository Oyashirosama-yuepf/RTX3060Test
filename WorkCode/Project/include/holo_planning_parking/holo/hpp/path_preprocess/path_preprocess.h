/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file path preprocess.h
 * @brief the header of path preprocess
 * @author lizhao(lizhao@holomatic.com)
 * @date 2022-01-27
 */

#ifndef _HOLO_PLANNING_PARKING_PATH_PREPROCESS_HPP_H_
#define _HOLO_PLANNING_PARKING_PATH_PREPROCESS_HPP_H_

#include <holo/common/coordinate.h>
#include <holo/hpp/hpp_car_road_state.h>
#include <holo/hpp/scenario/scenario_hpp_struct.h>
#include <holo/parking/map/hpp_path_data.h>
#include <holo/parking/map/map_path_process.h>

namespace holo
{
namespace planning
{
using MapPathPoint   = holo::parking::map::ParkingPointT<float64_t>;
using MapPathLane    = holo::parking::map::ParkingLaneT<float64_t>;
using MapPathData    = holo::parking::map::ParkingPath;
using LaneDir        = holo::parking::map::ParkingLaneT<float64_t>::LaneDir;
using CoordinateType = holo::common::Coordinate;
using namespace holo::parking::map;

#define PATH_PROCESS_OVER_TIME (1 << 0)  ///< path process is over time

/**
 * @brief      Class for behavior selection
 */
class PathPreprocess
{
public:
    /**
     * @brief   Constructor
     */
    PathPreprocess();

    /**
     * @brief   Destroy object
     */
    virtual ~PathPreprocess() = default;

    /**
     * @brief      process odometry file
     *
     * @return     True if no error occur, False otherwise.
     */
    bool_t Process(uint8_t route_id);

private:
    void saveRouteData(uint8_t route_id);

private:
    RoadInfo       info_;
    MapPathProcess map_path_process_;
};

}  // namespace planning
}  // namespace holo

#endif