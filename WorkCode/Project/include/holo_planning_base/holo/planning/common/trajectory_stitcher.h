/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file trajectory_stitcher.h
 * @brief the header of the trajectory_stitcher
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2020-11-09
 */

#ifndef _HOLO_PLANNING_COMMON_TRAJECTORY_STITCHER_H_
#define _HOLO_PLANNING_COMMON_TRAJECTORY_STITCHER_H_

#include <memory>
#include <vector>

#include <holo/common/chassis_state.h>
#include <holo/common/odometry.h>
#include <holo/common/path.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>

#include <holo/planning/common/published_path.h>

namespace holo
{
namespace planning
{
/**
 * @brief The trajectory stitcher
 */
class TrajectoryStitcher
{
public:
    /**
     * @brief TrajectoryStitcher's mode
     */
    enum class Mode : uint8_t
    {
        NORMAL                = 0,  ///< normal mode
        LATERAL_OVERRIDE      = 1,  ///< lateral override mode
        LONGITUDINAL_OVERRIDE = 2,  ///< longitudinal override mode
        REINIT                = 3,  ///< reinit mode
    };

public:
    /*
     * @brief Default Constructor
     */
    TrajectoryStitcher() = delete;

    /*
     * @brief compute the stitching_trajectory
     *
     * @param odometry The odometry
     * @param chassis_state The chassis_state
     * @param wheel_base The wheel_base of ego car
     * @param current_timestamp The current timestamp in format of double
     * @param forward_points_num The num of match-point-newer-points to preserve in stitching_trajectory
     * @param time_between_path_point The time between 2 path_point
     * @param preserved_points_num The num of match-point-older-points to preserve in stitching_trajectory
     * @param prev_trajectory The previous planning path
     * @param flags_replan_lateral_distance_threshold The lat_distance_threshold of replan check
     * @param flags_replan_longitudinal_distance_threshold The lon_distance_threshold of replan check
     * @param mode The mode of TrajectoryStitcher
     *
     * @return The stitching_trajectory
     */
    static PublishedPath ComputeStitchingTrajectory(std::shared_ptr<common::Odometryd>    odometry,
                                                    std::shared_ptr<common::ChassisState> chassis_state,
                                                    float64_t                             wheel_base,
                                                    float64_t                             current_timestamp,
                                                    uint32_t                              forward_points_num,
                                                    float64_t                             time_between_path_point,
                                                    uint32_t                              preserved_points_num,
                                                    PublishedPath const&                  prev_trajectory,
                                                    float64_t flags_replan_lateral_distance_threshold,
                                                    float64_t flags_replan_longitudinal_distance_threshold,
                                                    Mode      mode);

    /*
     * @brief compute the stitching_trajectory
     *
     * @param odometry The odometry
     * @param chassis_state The chassis_state
     * @param wheel_base The wheel_base of ego car
     * @param current_timestamp The current timestamp in format of double
     * @param forward_points_num The num of match-point-newer-points to preserve in stitching_trajectory
     * @param time_between_path_point The time between 2 path_point
     * @param preserved_points_num The num of match-point-older-points to preserve in stitching_trajectory
     * @param prev_trajectory The previous planning path
     * @param flags_replan_lateral_distance_threshold The lat_distance_threshold of replan check
     * @param flags_replan_longitudinal_distance_threshold The lon_distance_threshold of replan check
     * @param mode The mode of TrajectoryStitcher
     * @param[out] is_trajectory_stitching True if the trajectory is stitching, false otherwise
     *
     * @return The stitching_trajectory
     */
    static common::Path ComputeStitchingTrajectory(std::shared_ptr<common::Odometryd>    odometry,
                                                   std::shared_ptr<common::ChassisState> chassis_state,
                                                   float64_t                             wheel_base,
                                                   common::Timestamp                     current_timestamp,
                                                   uint32_t                              forward_points_num,
                                                   float64_t                             time_between_path_point,
                                                   uint32_t                              preserved_points_num,
                                                   common::Path const&                   prev_trajectory,
                                                   float64_t flags_replan_lateral_distance_threshold,
                                                   float64_t flags_replan_longitudinal_distance_threshold,
                                                   Mode      mode,
                                                   bool_t&   is_trajectory_stitching);

private:
    static std::pair<float64_t, float64_t> ComputePositionProjection(float64_t                x,
                                                                     float64_t                y,
                                                                     common::PathPoint const& p);

    static common::PathPoint ComputeTrajectoryPointFromEgoState(std::shared_ptr<common::Odometryd>    odometry,
                                                                std::shared_ptr<common::ChassisState> chassis_state,
                                                                float64_t                             wheel_base);

    static PublishedPath ComputeNormalStitchingTrajectory(std::shared_ptr<common::Odometryd>    odometry,
                                                          std::shared_ptr<common::ChassisState> chassis_state,
                                                          float64_t                             wheel_base,
                                                          float64_t                             current_timestamp,
                                                          uint32_t                              forward_points_num,
                                                          float64_t                             time_between_path_point,
                                                          uint32_t                              preserved_points_num,
                                                          PublishedPath const&                  prev_trajectory,
                                                          float64_t flags_replan_lateral_distance_threshold,
                                                          float64_t flags_replan_longitudinal_distance_threshold);

    static common::Path ComputeNormalStitchingTrajectory(std::shared_ptr<common::Odometryd>    odometry,
                                                         std::shared_ptr<common::ChassisState> chassis_state,
                                                         float64_t                             wheel_base,
                                                         common::Timestamp                     current_timestamp,
                                                         uint32_t                              forward_points_num,
                                                         uint32_t                              preserved_points_num,
                                                         common::Path const&                   prev_trajectory,
                                                         float64_t flags_replan_lateral_distance_threshold,
                                                         float64_t flags_replan_longitudinal_distance_threshold,
                                                         bool_t&   is_trajectory_stitching);

    static PublishedPath
    ComputeLongitudinalOverrideStitchingTrajectory(std::shared_ptr<common::Odometryd>    odometry,
                                                   std::shared_ptr<common::ChassisState> chassis_state,
                                                   float64_t                             wheel_base,
                                                   float64_t                             current_timestamp,
                                                   uint32_t                              forward_points_num,
                                                   float64_t                             time_between_path_point,
                                                   uint32_t                              preserved_points_num,
                                                   PublishedPath const&                  prev_trajectory,
                                                   float64_t flags_replan_lateral_distance_threshold);

    static common::Path
    ComputeLongitudinalOverrideStitchingTrajectory(std::shared_ptr<common::Odometryd>    odometry,
                                                   std::shared_ptr<common::ChassisState> chassis_state,
                                                   float64_t                             wheel_base,
                                                   common::Timestamp                     current_timestamp,
                                                   uint32_t                              forward_points_num,
                                                   float64_t                             time_between_path_point,
                                                   uint32_t                              preserved_points_num,
                                                   common::Path const&                   prev_trajectory,
                                                   float64_t flags_replan_lateral_distance_threshold,
                                                   bool_t&   is_trajectory_stitching);

    /*
     * @brief compute the stitching_trajectory when need to reinit
     *
     * @param odometry The odometry
     * @param chassis_state The chassis_state
     * @param wheel_base The wheel_base of ego car
     * @param[out] is_trajectory_stitching True if the trajectory is stitching, false otherwise
     *
     * @return The reinit stitching_trajectory
     */
    static common::Path ComputeReinitStitchingTrajectory(std::shared_ptr<common::Odometryd>    odometry,
                                                         std::shared_ptr<common::ChassisState> chassis_state,
                                                         float64_t                             wheel_base,
                                                         bool_t&                               is_trajectory_stitching);

    /*
     * @brief compute the stitching_trajectory when need to reinit in PublishedPath form
     *
     * @param odometry The odometry
     * @param chassis_state The chassis_state
     * @param wheel_base The wheel_base of ego car
     *
     * @return The reinit stitching_trajectory
     */
    static PublishedPath ComputeReinitStitchingPublishedPath(std::shared_ptr<common::Odometryd>    odometry,
                                                             std::shared_ptr<common::ChassisState> chassis_state,
                                                             float64_t                             wheel_base);
};

}  // namespace planning
}  // namespace holo

#endif  //_HOLO_PLANNING_COMMON_TRAJECTORY_STITCHER_H_
