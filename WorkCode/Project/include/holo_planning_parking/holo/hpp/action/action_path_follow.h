/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file action_path_follow.h
 * @brief the header of action path follow
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2019-09-20
 */

#ifndef _HOLO_PLANNING_ACTION_PATH_FOLLOW_H_
#define _HOLO_PLANNING_ACTION_PATH_FOLLOW_H_

#include <holo/hpp/action/action.h>
#include <holo/hpp/path_provider.h>
// #include <holo/planning/common/grid_map_frenet.h>
#include <holo/planning/planner/trapezoid_velocity_planner.h>
#include <holo/planning/util/collision_checker.h>

namespace holo
{
namespace planning
{
/**
 * @brief Class for action path follow.
 *
 * @details ActionPathFollow is used to descirbe vehicle in path follow state for hpp.
 */
class ActionPathFollow : public Action
{
public:
    /**
     * @brief State class enum
     */
    enum class State : uint8_t
    {
        NORMAL,  ///< Normal
        SLOW,    ///< Slow
        AVOID,   ///< Avoid
        STOP,    ///< Stop
    };

public:
    /**
     * @brief Constructor.
     */
    ActionPathFollow();

    /**
     * @brief Destroys the object.
     */
    virtual ~ActionPathFollow();

    /**
     * @brief Check the action status.
     *
     * @param car_road_state The car road state
     * @param route The plan route
     *
     * @return True if action is changed in check(), False otherwise.
     */
    virtual bool Check(const HppCarRoadState& hpp_car_road_state, PlanRoute& route);

    /**
     * @brief Perform the action.
     *
     * @param[in]  car_road_state The car road state
     * @param[out] route The route
     *
     * @return True if action is executed successfully. False otherwise.
     */
    virtual bool Perform(const HppCarRoadState& hpp_car_road_state, PlanRoute& route);

    /**
     * @brief Reset the action state.
     */
    virtual void Reset();

    /**
     * @brief Set path provider
     *
     * @param path_provider common::Path provider to be seted
     */
    void SetPathProvider(const std::shared_ptr<PathProvider>& path_provider);

    /**
     * @brief Reset grid map to current first piecewise reference path in path_provider_
     */
    // bool ResetGridMap();

private:
    /**
     * @brief Update Current Section By Clear Passed Points
     *
     * @param cur_vx Current longitudinal speed
     * @param odo_speed speed calc from odometry
     */
    void CheckAndUpdatePassedSectionOfRoad(float32_t cur_vx, float32_t odo_speed);

    /**
     * @brief Update Current Section Points By Start Points
     *
     * @param pose Current 2d pose
     * @param height Current height
     * @param ref_path Ref path
     * @param ref_path_extend Extend ref path
     *
     * @return True if find current index approximated
     */
    bool RefPathGenerate(const geometry::Pose2&             pose,
                         float64_t                height,
                         std::vector<CurvePoint>& ref_path,
                         std::vector<CurvePoint>& ref_path_extend);

    /**
     * @brief Get progress.
     *
     * @param min_distance_index Current index approximated
     *
     * @return The progress
     */
    uint32_t GetProgress(size_t min_distance_index);

private:
    std::shared_ptr<PathProvider> path_provider_;
    TrapezoidVelocityPlanner      velocity_planner_;
    CollisionChecker              collision_checker_;
    // std::shared_ptr<GridMapFrenet> grid_map_;
    bool     in_avoid_;
    uint32_t exit_avoid_wait_frame_;
    size_t   current_path_index_;

    std::vector<std::vector<geometry::Point2>> detection_obstalces_;
    std::vector<std::vector<geometry::Point2>> free_spaces_fusioned_obstacles_;
    std::vector<std::vector<geometry::Point2>> non_free_spaces_obstacles_;
    std::vector<std::vector<geometry::Point2>> uss_fusioned_obstalces_;
    geometry::Pose2                            pose_free_spaces_;
    geometry::Pose2                            pose_detection_;

    bool use_freespace_;
    bool use_detection_;
    bool use_uss_;
    bool use_avoid_;
    bool use_parkin_;

    float64_t follow_path_speed_;
    float64_t back_speed_;
    float64_t turn_speed_;
    float64_t warning_speed_;

    float64_t end_zero_speed_path_length_;
    float64_t start_zero_speed_path_length_;
    float64_t dynamic_path_length_;
    float64_t smooth_step_;
    float64_t uss_stop_distance_;
    float64_t uss_check_buffer_distance_;
    float64_t min_valid_obstacle_area_;
    float64_t check_width_;
    float64_t soa_check_width_;
    float64_t mirror_width_;
    float64_t straight_dead_distance_;
    float64_t turn_dead_distance_;
    float64_t back_dead_distance_;

    float64_t max_distance_tolerance_for_shift_gear_;
    float64_t max_distance_tolerance_for_start_;
    float64_t max_heading_tolerance_;
    float64_t max_speed_tolerance_;
};

}  // namespace planning
}  // namespace holo

#endif
