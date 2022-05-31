/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file scenario_hpp.h
 * @brief the header of behavior selector for hpp scenario
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2021-04-08
 */

#ifndef _HOLO_PLANNING_PARKING_SCENARIO_SCENARIO_HPP_H_
#define _HOLO_PLANNING_PARKING_SCENARIO_SCENARIO_HPP_H_

#include <holo/hpp/behavior/behavior.h>
#include <holo/hpp/decider_longitudinal/decider_longitudinal_base.h>
#include <holo/hpp/hpp_car_road_state.h>
#include <holo/hpp/obstacle_avoid/avoid_obstacle_process.h>
#include <holo/hpp/scenario/scenario_hpp_struct.h>
#include <holo/hpp/scenario/scenario_parking_base.h>

namespace holo
{
namespace planning
{
/**
 * @brief      Class for behavior selection
 */
class ScenarioHpp : public ScenarioParkingBase
{
public:
    /**
     * @brief   Constructor
     */
    ScenarioHpp();

    /**
     * @brief   Destroy object
     */
    virtual ~ScenarioHpp() = default;

    /**
     * @brief      plan in hpp scenario
     *
     * @param[in]  state  The car road state
     * @param      output The output
     *
     * @return     True if no error occur, False otherwise.
     */
    bool_t Plan(HppCarRoadState const& state, HppOutput& output);

private:
    bool_t preProcess(HppCarRoadState const& state, HppOutput& output);
    bool_t selectBehavior(HppCarRoadState const& state, HppOutput& output);
    bool_t pathFollowStart(HppCarRoadState const& state);
    bool_t pathFollow(HppCarRoadState const& state, HppOutput& output);
    bool_t pathAvoidObstacle(HppCarRoadState const& state, HppOutput& output);
    bool_t pathPullOut();
    bool_t pathParkIn();
    bool_t pathPullOutToFollow(HppOutput& output);

    bool_t initPathInfo();
    size_t getNearestIndex(std::vector<CurvePoint> path, size_t min_index, size_t max_index);
    void   updatePiecewiseId();
    bool_t updatePathInfo();
    bool_t updateGripMap(std::vector<CurvePoint>                    refer_path,
                         std::vector<std::vector<geometry::Point2>> free_spaces,
                         std::vector<std::vector<geometry::Point2>> obstacle_spaces);
    bool_t transform2Sl(std::vector<CurvePoint>                     refer_path,
                        std::vector<std::vector<geometry::Point2>>  contour_point,
                        std::vector<std::vector<geometry::Point2>>& contour_sl,
                        float64_t&                                  s_min,
                        float64_t&                                  s_max);
    void   saveFirstPathSegment(std::vector<CurvePoint>& path);
    bool_t updatePulloutInfo();
    bool_t checkCurrentPosition();
    bool_t constraint4InitPose();

private:
    std::shared_ptr<DeciderLongitudinalBase> lon_decider_;
    std::shared_ptr<AvoidObstacleProcess>    avoid_obstacle_process_;

    std::vector<CurvePoint> ref_path_extend_last_;

    float64_t init_allow_lat_displace_ = 2.0;
    float64_t init_allow_lon_displace_ = 5.0;
    float64_t init_allow_heading_diff_ = 0.26;
    float32_t ref_lat_error_           = 0.0;
    float32_t ref_heading_error_       = 0.0;
    float64_t max_allow_distance_      = 50;
    float64_t max_allow_heading_diff_  = 1.74;
    float64_t min_allow_heading_diff_  = -0.17;  /// <-10~100°

    float64_t max_distance_tolerance_for_shift_gear_ = 0.3;
    float32_t max_position_change_                   = 5.0;
    float64_t max_speed_tolerance_                   = 0.005;
    float64_t min_valid_obstacle_area_               = 0.04;
    bool_t    save_first_segment_path_               = true;
    bool_t    use_control_output_                    = false;
    bool_t    control_end_ok_                        = false;

    float64_t grid_map_l_min_                = -3.5;
    float64_t grid_map_l_max_                = 3.5;
    float64_t grid_map_s_interval_           = 0.25;
    float64_t grid_map_l_interval_           = 0.05;
    float64_t avoid_path_max_l_              = 5.0;    // avoid obstacle l direction max distance
    float64_t avoid_path_recovery_max_l_     = 0.2;    // avoid obstacle recover to refer path l direction max distance
    bool_t    enable_avoid_obstacle_         = false;  // whether enable avoid obstacle
    bool_t    enable_pullout_                = false;
    bool_t    enable_constraint_4_init_pose_ = false;
    float64_t distance_not_to_pullout_       = 0.5;
    float64_t distance_to_parkin_            = 5.0;
    bool_t    enable_hpa2apa_                = false;
};

}  // namespace planning
}  // namespace holo

#endif
