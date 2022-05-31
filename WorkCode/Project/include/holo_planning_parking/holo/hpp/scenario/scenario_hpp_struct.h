/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file scenario_hpp_struct.h
 * @brief the header of data struct for hpp scenario
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2021-04-08
 */

#ifndef _HOLO_PLANNING_HPP_DECISION_SCENARIO_HPP_STRUCT_H
#define _HOLO_PLANNING_HPP_DECISION_SCENARIO_HPP_STRUCT_H

#include <vector>

#include <holo/common/odometry.h>
#include <holo/common/path.h>
#include <holo/geometry/pose2.h>
#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_list.h>

#include <holo/parking/map/navigation_road_builder.h>
#include <holo/parking/map/parking_navigation.h>
#include <holo/parking/planning/path_attribute.h>

#include <holo/hpp/path_provider.h>

namespace holo
{
namespace planning
{
using MapNavigation = holo::map::ParkingNavigation;

#define DETECTION_OVER_TIME (1 << 0)                    ///< receive detection data over time
#define FREESPACE_OVER_TIME (1 << 1)                    ///< receive freespace data over time
#define FREESPACE_AVM_OVER_TIME (1 << 2)                ///< receive avm freespace data over time(no use)
#define CHASSIS_OVER_TIME (1 << 3)                      ///< receive chassis data over time
#define ODOMETRY_OVER_TIME (1 << 4)                     ///< receive odometry data over time
#define LOAD_PATH_FAILED (1 << 5)                       ///< load path failed
#define MAX_POSITION_CHANGE_OVER_5M (1 << 6)            ///< max_position_change is greater than 5.0m
#define MAX_CURVATURE_OVER_THRESHOLD (1 << 7)           ///< max_curvature_path is greater than max_curvature_check
#define STRAIGHT_FORWARD_SPEED_OVER_THRESHOLD (1 << 9)  ///< speed exceeds threshold in straight forward road
#define TURN_FORWARD_SPEED_OVER_THRESHOLD (1 << 10)     ///< speed exceeds threshold in turn forward road
#define BACK_SPEED_OVER_THRESHOLD (1 << 11)             ///< speed exceeds threshold in back road
#define MAX_POSITION_CHANGE_OVER_10M (1 << 12)          ///< max position change over 10m
#define TRACKING_OVER_TIME (1 << 13)                    ///< tracking over time
#define MAP_OVER_TIME (1 << 14)                         ///< receive map data over time
#define OBSTACLE_EXISTANCE_SCORE_ABNORMAL (1 << 15)     /// obstacle existance score is abnormal

enum class BehaviorState
{
    PATH_FOLLOW_START = 0,
    PATH_FOLLOW_KEEP,
    PATH_FOLLOW_AVP,
    OBSTACLE_AVOIDANCE,
    OBSTACLE_AVOIDANCE_WAITING,
    PARKIN,
    PULLOUT,
    EMERGENCY_STOP,
    EXIT,
};

enum class LonState
{
    PATH_FOLLOW_NORMAL_STRAIGHT,   ///< path follow with normal speed straight
    PATH_FOLLOW_NORMAL_TURN,       ///< path follow with normal speed turn
    PATH_FOLLOW_FOA_STATIC_STOP,   ///< need stop by static obs of foa
    PATH_FOLLOW_FOA_DYNAMIC_STOP,  ///< need stop by dynamic obs of foa
    PATH_FOLLOW_SOA_STATIC_SLOW,   ///< need slow by static obs of soa from PATH_FOLLOW_NORMAL_STRAIGHT
    PATH_FOLLOW_SOA_DYNAMIC_SLOW,  ///< need stop by dynamic obs of soa from PATH_FOLLOW_NORMAL_STRAIGHT
    PATH_FOLLOW_SOA_DYNAMIC_STOP,  ///< need stop by dynamic obs of soa
    AVOIDANCE_SLOW,                ///< normal avoidance
    AVOIDANCE_STOP,                ///< need stop by obstacle in avoidance
    PARK_SLOW,                     ///< normal backward
    PARK_STATIC_STOP,              ///< need stop by static obs in backward
    PARK_DYNAMIC_STOP,             ///< need stop by dynamic obs in backward
    GEAR_CHANGE_STOP,              ///< need stop when change gear
    EMERGENCY_STOP,                ///< emergency stop
    PATH_FOLLOW_SLOW_KEEP,         ///< need wait and keep slow from slow to normal
    WAITING_FIVE_SECONDS,          ///< wait for 5 seconds
    AVP_CROSSROAD,                 ///< at crossroad
    AVP_SLOPE,                     ///< at slope
};

enum class AvoidDirection
{
    BI_DIRECTION = 0,
    LEFT_DIRECTION,
    RIGHT_DIRECTION,
};

struct ObstacleType
{
    bool_t has_dynamic_obstacle              = false;
    bool_t has_same_static_vehicle           = false;
    bool_t has_opposite_static_vehicle       = false;
    bool_t has_oncoming_vehicle              = false;
    bool_t has_same_direction_moving_vehicle = false;
    bool_t has_speed_hump                    = false;
};

struct RoadInfo
{
    /// common info
    bool_t          standstill;
    geometry::Pose2 pose;
    PathProvider    path_provider;
    uint32_t        path_id = 0;

    /// path info
    uint32_t  current_piecewise_id    = 0;
    uint32_t  current_pathpoint_index = 0;
    float32_t remain_distance         = std::numeric_limits<float32_t>().max();
    bool_t    get_whole_path          = false;
    bool_t    finished                = false;

    /// obstacle info
    geometry::Pose2                            pose_free_spaces;
    geometry::Pose2                            pose_detection;
    std::vector<std::vector<geometry::Point2>> free_spaces;
    std::vector<std::vector<geometry::Point2>> avm_free_spaces;
    std::vector<std::vector<geometry::Point2>> ranges;
    std::vector<std::vector<geometry::Point2>> free_spaces_fusioned_obstacles;
    std::vector<std::vector<geometry::Point2>> non_free_spaces_obstacles;
    std::vector<std::vector<geometry::Point2>> detection_obstalces;
    std::vector<std::vector<geometry::Point2>> vehicle_coor_detection_obstalces;
    std::vector<std::vector<geometry::Point2>> vehicle_coor_free_spaces_fusioned_obstacles;
    std::vector<std::vector<geometry::Point2>> vehicle_coor_non_free_spaces_obstacles;
    std::vector<std::vector<geometry::Point2>> vehicle_coor_avm_free_spaces;
    std::vector<std::pair<Classification::MainType, Classification::SubType>> obstacle_types;
    std::vector<holo::obstacle::details::MotionStatus>                        obstacle_motion_status;

    std::shared_ptr<MapNavigation> navigation_point;

    /// lot type info
    int8_t    pullout_dir     = 0;
    int8_t    parkinglot_type = 0;
    float64_t expected_speed  = 0;
    bool_t    stopped_by_obs  = false;
};

struct HppOutput
{
    /// behavior decision
    BehaviorState behavior;

    /// path planning
    common::Path                           ref_path;
    std::vector<CurvePoint>                ref_path_extend;
    std::vector<CurvePoint>                avoid_path;
    holo::parking::planning::PathAttribute path_attribute;
    std::shared_ptr<MapNavigation>         navigation_point;

    // junction road decesion
    uint8_t junction_road_state = 0;  /// 0:non junction   1:cross road   2:turn right   3:turn left

    /// longitudinal decision
    LonState     lon_state;
    uint32_t     fault_state = 0;
    common::Path predict_path;
    float64_t    max_speed               = 0.0;
    float64_t    rest_path_distance      = 0.0;
    float64_t    rest_collision_distance = 0.0;
    float64_t    stop_distance           = 0.0;
    uint8_t      obstacle_stopping       = 0;
    uint8_t      obstacle_avoid          = 0;

    bool max_curvature_over_threshold      = false;
    bool update_path_flag                  = false;
    bool obstacle_existance_score_abnormal = false;

    bool lat_error_over_distance = false;
};

}  // namespace planning
}  // namespace holo

#endif
