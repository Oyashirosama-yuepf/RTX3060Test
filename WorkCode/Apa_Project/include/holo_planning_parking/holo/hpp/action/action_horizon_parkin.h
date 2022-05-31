/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file action_horizon_parkin.h
 * @brief the header of action horizon parkin
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2020-09-02
 */

#ifndef _HOLO_PLANNING_ACTION_HORIZON_PARKIN_H_
#define _HOLO_PLANNING_ACTION_HORIZON_PARKIN_H_

#include <holo/hpp/collision_checker.h>
#include <holo/hpp/trapezoid_velocity_planner.h>
#include <holo/planning/framework/action/action.h>

namespace holo
{
namespace planning
{
class ActionHorizonParkin : public Action
{
public:
    typedef holo::ObstacleGeneralT<holo::float32_t> Obstacle;
    typedef std::shared_ptr<Obstacle>               ObstaclePtr;
    typedef holo::ObstaclePtrListT<Obstacle>        ObstacleList;
    typedef std::shared_ptr<ObstacleList>           ObstacleListPtr;

    enum class State : uint8_t
    {
        PREPARE,
        OUTSIDE,
        TURNIN,
        TURNINSIDE,
        FORWARD,
        BACKWARD,
        FINETUNING,
    };

public:
    ActionHorizonParkin();

    virtual bool Check(const CarRoadState& car_road_state, PlanRoute& route);

    virtual bool Perform(const CarRoadState& car_road_state, PlanRoute& route);

    virtual void Reset();

private:
    bool hybridAStar(geometry::Pose2 const& start, geometry::Pose2 const& end, float64_t speed, common::Path& path);
    bool turnIn(geometry::Pose2 const& pose, common::Path& path);
    bool turnInside(geometry::Pose2 const& pose, common::Path& path);
    bool forward(geometry::Pose2 const& pose, common::Path& path);
    bool backward(geometry::Pose2 const& pose, common::Path& path);

    void circlePathGenerator(geometry::Pose2 const& start, bool forward, float64_t steer_angle, float64_t delta_phi, common::Path& path);
    void zeroSpeedPathExtender(common::Path& path);

    bool selectTargetAndOutsidePoses(common::Path const& ref_path, geometry::Pose2 const& pose);

    void obstaclePreprocess(ObstacleListPtr const& origin, ObstacleListPtr& transformed, geometry::Pose2 pose);

private:
    /// park space obstacles
    std::vector<std::vector<Point3>> obstacles_;
    ObstacleListPtr                  inner_obstacles_;
    ObstacleListPtr                  total_obstacles_;
    geometry::Point2                           key_point_;

    /// perception obstacles
    bool            use_uss_;
    bool            use_detection_;
    bool            use_freespace_;
    ObstacleListPtr uss_fusioned_obstalces_;
    ObstacleListPtr detection_obstalces_;
    ObstacleListPtr free_spaces_fusioned_obstacles_;
    ObstacleListPtr non_free_spaces_obstacles_;
    geometry::Pose2           pose_free_spaces_;
    geometry::Pose2           pose_detection_;

    /// global state
    bool               right_side_ = true;
    geometry::Pose2              target_pose_;
    std::vector<geometry::Pose2> outside_poses_;
    State              state_ = State::PREPARE;

    /// hybrid a star state
    common::Path   ha_path_;
    size_t ha_current_index_ = 0;
    bool   ha_forward_       = true;

    /// planner param
    float64_t smooth_step_              = 0.025;
    float64_t max_speed_tolerance_      = 0.005;
    float64_t max_speed_                = 0.4;
    float64_t max_path_length_          = 5.0;
    float64_t max_end_distance_         = 0.3;  /// max distance check for ending
    float64_t max_path_size_tolerance_  = 10;  /// 10 * 0.025 = 0.25, max distance tolerance to the end of current phase
    float64_t max_angle_tolerance_      = 0.07;      /// angle difference between the value rad regard same
    float64_t min_key_point_distance_   = 0.05;      /// min distance to key point in turnin
    float64_t ideal_key_point_distance_ = 0.3;       /// ideal distance to key point in turnin
    float64_t min_delta_key_point_distance_ = 0.01;  /// min delta distance to key point for a better curve choice
    float64_t turn_in_stop_distance_ = 0.7;  /// min y value after turnin, keep this for y displacement in turninside
    float64_t turn_inside_stop_distance_ = 0.2;  /// min y distance after turninside, keep this for backward and forward
    float64_t prepare_side_distance_     = 0.8;  /// side distance to parking slot after prepare
    float64_t prepare_displace_          = 6.0;  /// displace along parking slot after prepare
    float64_t max_delta_front_wheel_angle_in_slot_ =
        0.05;  /// max delta front wheel angle from max value in backward and forward
    float64_t min_valid_obstacle_area_       = 0.04;  /// obstacle area filter
    float64_t collision_check_buffer_        = 0.1;   /// collision check buffer during parkin process
    float64_t ahead_distance_buffer_in_slot_ = 0.15;  /// buffer distance ahead in turninside, backward, forward
    bool      is_moved_ = false;  /// flag for change between forward and backward, change must with moved

    /// vehicle param
    float64_t vehicle_length_;
    float64_t vehicle_width_;
    float64_t imu_to_front_edge_;
    float64_t imu_to_back_edge_;
    float64_t wheelbase_             = 2.703;
    float64_t left_max_steer_angle_  = 0.51;
    float64_t right_max_steer_angle_ = 0.51;

    /// park space param
    float64_t park_width_             = 3.4;
    float64_t park_length_            = 7.0;
    float64_t park_side_extend_       = 2.0;
    float64_t park_opposide_distance_ = 5.0;

    TrapezoidVelocityPlanner velocity_planner_;
    CollisionChecker         collision_checker_;
};

}  // namespace planning
}  // namespace holo
#endif