/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file action_verticle_parkin.h
 * @brief the header of action verticle parkin
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2020-07-29
 */

#ifndef _HOLO_PLANNING_PARKING_ACTION_VERTICLE_PARKIN_H_
#define _HOLO_PLANNING_PARKING_ACTION_VERTICLE_PARKIN_H_

#include <holo/hpp/action/action.h>
#include <holo/planning/planner/hybrid_astar/hybrid_a_star.h>
#include <holo/planning/planner/trapezoid_velocity_planner.h>
#include <holo/planning/util/collision_checker.h>

namespace holo
{
namespace planning
{
/**
 * @brief Class for action verticle parkin.
 *
 * @details ActionVerticleParkin is used to descirbe vehicle verticle parkin
 */
class ActionVerticleParkin : public Action
{
public:
    enum class State : uint8_t
    {
        PREPARE,  ///< PREPARE
        OUTSIDE,  ///< OUTSIDE
        MOVEIN,   ///< MOVEIN
        FORWARD,  ///< FORWARD
        INSIDE,   ///< INSIDE
    };

public:
    /**
     * @brief Constructor.
     */
    ActionVerticleParkin();

    /**
     * @brief Check the action status.
     *
     * @param hpp_car_road_state The car road state
     * @param route The plan route
     *
     * @return True if action is changed in check(), False otherwise.
     */
    virtual bool Check(const HppCarRoadState& hpp_car_road_state, PlanRoute& route);

    /**
     * @brief Perform the action.
     *
     * @param[in]  hpp_car_road_state The car road state
     * @param[out] route The route
     *
     * @return True if action is executed successfully. False otherwise.
     */
    virtual bool Perform(const HppCarRoadState& hpp_car_road_state, PlanRoute& route);

    /**
     * @brief Reset the action state.
     */
    virtual void Reset();

private:
    bool moveInStandard(geometry::Pose2 const& pose, std::vector<CurvePoint>& path, float64_t& target_steer_angle);
    bool moveInBackup(geometry::Pose2 const& pose, std::vector<CurvePoint>& path, float64_t& target_steer_angle);
    bool hybridAStar(geometry::Pose2 const&             start,
                     geometry::Pose2 const&             end,
                     float64_t                speed,
                     std::vector<CurvePoint>& path,
                     bool_t&                  direction);

    void
         circlePathGenerator(geometry::Pose2 const& start, float64_t steer_angle, float64_t delta_phi, std::vector<CurvePoint>& path);
    void insidePathGenerator(geometry::Pose2 const& start, std::vector<CurvePoint>& path);
    void zeroSpeedPathExtender(std::vector<CurvePoint>& path, bool_t direction);

    void SelectTargetAndOutsidePoses(std::vector<CurvePoint> const& ref_path, float64_t heading);

private:
    /// park space obstacles
    std::vector<std::vector<geometry::Point2>> obstacles_;
    std::vector<std::vector<geometry::Point2>> inner_obstacles_;
    geometry::Point2                           key_point_;

    /// perception obstacles
    bool                             use_detection_;
    bool                             use_freespace_;
    std::vector<std::vector<geometry::Point2>> detection_obstalces_;
    std::vector<std::vector<geometry::Point2>> free_spaces_fusioned_obstacles_;
    std::vector<std::vector<geometry::Point2>> non_free_spaces_obstacles_;
    geometry::Pose2                            pose_free_spaces_;
    geometry::Pose2                            pose_detection_;

    /// global state
    bool               right_side_ = true;
    geometry::Pose2              target_pose_;
    std::vector<geometry::Pose2> outside_poses_;
    State              state_ = State::PREPARE;

    /// hybrid a star state
    std::vector<std::vector<CurvePoint>> ha_paths_;
    std::vector<bool>                    ha_directions_;
    size_t                               ha_current_index_;

    /// planner param
    float64_t smooth_step_              = 0.025;
    float64_t max_speed_tolerance_      = 0.005;
    float64_t max_speed_                = 0.4;
    float64_t max_path_length_          = 5.0;
    float64_t max_end_distance_         = 0.3;  /// max distance check for ending
    float64_t max_path_size_tolerance_  = 10;  /// 10 * 0.025 = 0.25, max distance tolerance to the end of current phase
    float64_t max_angle_tolerance_      = 0.07;       /// angle difference between the value rad regard same
    float64_t min_key_point_distance_   = 0.01;       /// min distance to key point in movein
    float64_t ideal_key_point_distance_ = 0.3;        /// ideal distance to key point in movein
    float64_t min_delta_key_point_distance_ = 0.025;  /// min delta distance to key point for a better curve choice
    float64_t min_valid_obstacle_area_      = 0.04;   /// obstacle area filter
    float64_t collision_check_buffer_       = 0.01;   /// collision check buffer during parkin process
    float64_t prepare_side_distance_        = 1.5;    /// side distance to parking slot after prepare
    float64_t prepare_displace_             = 4.0;    /// displace along parking slot after prepare
    bool      is_moved_                 = false;  /// flag for change between forward and movein, change must with moved
    float64_t max_delta_heading_        = 2.1;    /// max allowable delta heading change in movein, 2.1 rad = 120 degree
    float64_t overside_distance_        = 0.1;    /// max allowable overside distance in movein
    float64_t max_lateral_end_distance_ = 0.1;    /// max allowable lateral difference in the end
    float64_t stop_distance_buffer_     = 0.4;    /// buffer distance in movein and forward

    /// vehicle param
    float64_t left_max_steer_angle_  = 0.51;
    float64_t right_max_steer_angle_ = 0.51;

    /// park space param
    float64_t park_width_             = 2.6;
    float64_t park_length_            = 5.5;
    float64_t park_side_extend_       = 3.0;
    float64_t park_opposide_distance_ = 5.3;

    TrapezoidVelocityPlanner velocity_planner_;
    CollisionChecker         collision_checker_;

    config::VehicleConfig const&     vehicle_cfg_;
    config::HybridAstarConfig const& hybrid_astar_cfg_;
};

}  // namespace planning
}  // namespace holo
#endif