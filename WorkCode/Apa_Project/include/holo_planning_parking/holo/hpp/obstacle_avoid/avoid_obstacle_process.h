/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file avoid_obstacle_process.h
 * @brief the header of avoid obstacle process
 * @author lizhao(lizhao@holomatic.com)
 * @date 2021-06-8
 */

#ifndef _HOLO_HPP_AVOID_OBSTACLE_PROCESS_H_
#define _HOLO_HPP_AVOID_OBSTACLE_PROCESS_H_

#include <holo/hpp/hpp_car_road_state.h>
#include <holo/hpp/scenario/scenario_hpp_struct.h>
#include <holo/planning/common/curve_point.h>
#include <holo/planning/common/road_boundary.h>
#include <holo/planning/common/sl_path.h>
#include <holo/planning/util/collision_checker.h>

namespace holo
{
namespace planning
{
class AvoidObstacleProcess
{
public:
    /**
     * @brief Contructor
     */
    AvoidObstacleProcess(float64_t max_curvature, const bool_t use_detection, const bool_t use_freespace);

    /**
     * @brief Plan the avoid path
     *
     * @param[in] info  Road info
     * @param[in] grid_map  The available grid map
     * @param[in] path_step The step of refer path
     * @param[out] path The avoid path
     * @param[out] expand_length The lateral expand length
     * @param[out] recovery_flag (if true,recovery;false avoid obstacle)
     *
     * @return True if process successfully
     */
    bool Process(HppCarRoadState const&   state,
                 RoadInfo&                info,
                 float64_t const&         left_road_width,
                 float64_t const&         right_road_width,
                 std::vector<CurvePoint>& path,
                 bool                     recovery_flag);

    /**
     * @brief Judge whether avoiding obstacle
     *
     * @param[in] state  The car road state
     * @param[in] info  The RoadInfo
     * @param[in] obstacle_type  The obstacle type
     *
     * @return true if meeting avoid obstacle conditions,else return false.
     */
    bool HpaAvoidObstacleJudge(HppCarRoadState const& state, RoadInfo const& info, ObstacleType& obstacle_type);

    /**
     * @brief Judge whether avoiding obstacle
     *
     * @param[in] state  The car road state
     * @param[in] info  The RoadInfo
     * @param[in] obstacle_type  The obstacle type
     *
     * @return true if meeting avoid obstacle conditions,else return false.
     */
    bool AvpAvoidObstacleJudge(HppCarRoadState const& state, RoadInfo const& info, ObstacleType& obstacle_type);

    /**
     * @brief Judge whether recovering the origin refer path
     *
     * @param[in] info  The RoadInfo
     *
     * @return true if meeting recover to refer path conditions,else return false.
     */
    bool RecoveryJudge(HppCarRoadState const& state, RoadInfo const& info);

    /**
     * @brief Set avoid obstacle direction
     *
     * @param[in] direction  The direction
     *
     */
    void SetAvoidanceDirection(AvoidDirection direction);

private:
    /**
     * @brief Judge whether is valid path and has no obstacle
     *
     */
    bool_t IsValidAvoidPath(RoadInfo& info);

    /**
     * @brief Update avoid obstacle path by current pose
     *
     */
    void UpdateAvoidObstaclepath(const geometry::Pose2& pose);

    /**
     * @brief Generate the ahead path
     *
     * @param[in] info The RoadInfo
     */
    std::vector<CurvePoint> GetReferPathAhead(RoadInfo const& info);

    /**
     * @brief Check valid path no collision and curvature constraint
     *
     * @param[in] path_set The path set
     * @param[in] avoid_path The valid path
     */
    bool SearchValidPath(std::vector<std::vector<CurvePoint>>& path_set,
                         std::vector<float64_t>&               path_offset,
                         HppCarRoadState const&                state,
                         RoadInfo&                             info,
                         std::vector<CurvePoint>&              avoid_path);

private:
    /**
     * @brief The collision checker
     */
    CollisionChecker collision_checker_;

    /**
     * @brief The avoid obstacle min distance
     */
    float64_t min_avoid_obstacle_distance_ = 4.0;

    /**
     * @brief The avoid obstacle max distance
     */
    float64_t max_avoid_obstacle_distance_ = 8.0;

    /**
     * @brief The opposite car avoid obstacle min distance
     */
    float64_t min_vehicle_avoid_distance_ = 6.0;

    /**
     * @brief The opposite car avoid obstacle max distance
     */
    float64_t max_vehicle_avoid_distance_ = 9.0;

    /**
     * @brief Whether is on comming vehicle
     */
    bool_t is_on_comming_vehicle_ = false;

    /**
     * @brief Whether is dymatic obstacle
     */
    bool_t is_dymatic_obstacle_ = false;

    /**
     * @brief The vehicle width
     */
    float64_t vehicle_width_ = 1.8;

    /**
     * @brief The mirror width
     */
    float64_t mirror_width_ = 0.2;

    /**
     * @brief The check buffer width
     */
    float64_t check_buffer_ = 0.1;

    /**
     * @brief The check interval
     */
    float64_t check_interval_ = 1.0;

    /**
     * @brief The check length
     */
    float64_t check_length_ = 10.0;

    /**
     * @brief The max curvature threshold
     */
    float64_t max_curvature_threshold_ = 0.25;

    /**
     * @brief The avoidance direction
     */
    AvoidDirection avoid_direction_ = AvoidDirection::BI_DIRECTION;

    /**
     * @brief The expansion width
     */
    float64_t expansion_width_ = 0.3;  ///< 0.3 -> vehicle body expansion 0.5m

    /**
     * @brief Whether use detection
     */
    bool_t use_detection_ = true;

    /**
     * @brief Whether use freespace
     */
    bool_t use_freespace_ = true;

    /**
     * @brief The path generated by lattice
     */
    std::vector<CurvePoint> avoid_path_;
};
}  // namespace planning
}  // namespace holo

#endif