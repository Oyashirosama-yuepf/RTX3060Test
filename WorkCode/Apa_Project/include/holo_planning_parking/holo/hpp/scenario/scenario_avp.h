/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file scenario_avp.h
 * @brief the header of scenario avp class
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2021-09-07
 */

#ifndef _HOLO_PLANNING_PARKING_SCENARIO_SCENARIO_AVP_H_
#define _HOLO_PLANNING_PARKING_SCENARIO_SCENARIO_AVP_H_

#include <holo/core/types.h>
#include <holo/hpp/decider_longitudinal/decider_longitudinal_base.h>
#include <holo/hpp/obstacle_avoid/avoid_obstacle_process.h>
#include <holo/hpp/scenario/scenario_parking_base.h>

namespace holo
{
namespace planning
{
/**
 * @brief The base class of scenario avp
 */
class ScenarioAvp : public ScenarioParkingBase
{
public:
    /**
     * @brief Constructor
     */
    ScenarioAvp(std::shared_ptr<MapNavigation> navigation_point);

    /**
     * @brief Destroy object
     */
    virtual ~ScenarioAvp() = default;

    /**
     * @brief plan in hpp scenario
     *
     * @param[in] state  The car road state
     * @param[out] output The output
     *
     * @return True if plan successfully, false otherwise.
     */
    virtual bool_t Plan(HppCarRoadState const& state, HppOutput& output);

protected:
    virtual bool_t selectBehavior(HppCarRoadState const& state, HppOutput& output);

    bool_t preProcess(HppCarRoadState const& state, HppOutput& output);

    bool_t pathFollowStart(HppCarRoadState const& state);
    bool_t pathFollow(HppCarRoadState const& state, HppOutput& output);
    bool_t pathPullOut(HppCarRoadState const& state);
    bool_t pathAvoidObstacle(HppCarRoadState const& state, HppOutput& output);

    bool_t initPathInfo();
    size_t getNearestIndex(std::vector<CurvePoint> path, size_t min_index, size_t max_index);
    void   updatePiecewiseId();
    bool_t updatePathInfo(HppOutput& output);
    bool_t updatePulloutInfo();
    bool_t checkCurrentPosition();
    bool_t constraint4InitPose();

protected:
    std::shared_ptr<DeciderLongitudinalBase> lon_decider_;
    std::shared_ptr<AvoidObstacleProcess>    avoid_obstacle_process_;

    float64_t extract_road_length_     = 50.0;
    float64_t distance_need_reextract_ = 20.0;

    float64_t init_allow_lon_displace_ = 5.0;
    float64_t init_allow_lat_displace_ = 2.0;
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
    bool_t    use_control_output_                    = false;
    bool_t    enable_pullout_                        = false;
    bool_t    enable_constraint_4_init_pose_         = false;
    bool_t    control_end_ok_                        = false;
    bool_t    get_the_end_of_path_                   = false;
    bool_t    need_extend_path_                      = false;
    float64_t distance_not_to_pullout_               = 0.5;

    float64_t grid_map_l_min_        = -3.5;
    float64_t grid_map_l_max_        = 3.5;
    bool_t    enable_avoid_obstacle_ = false;  // whether enable avoid obstacle
};

}  // namespace planning
}  // namespace holo

#endif  //_HOLO_PLANNING_PARKING_SCENARIO_SCENARIO_AVP_H_
