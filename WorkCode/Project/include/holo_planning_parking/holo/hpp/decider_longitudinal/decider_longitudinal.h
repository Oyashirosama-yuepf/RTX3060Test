/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file decider_longitudinal.h
 * @brief the header of longitudinal decider for hpp scenario
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2021-04-26
 */

#ifndef _HOLO_PLANNING_PARKING_DECIDER_LONGITUDINAL_H_
#define _HOLO_PLANNING_PARKING_DECIDER_LONGITUDINAL_H_

#include <holo/hpp/decider_longitudinal/decider_longitudinal_base.h>
#include <holo/hpp/hpp_car_road_state.h>
#include <holo/hpp/obstacle_avoid/obstacle_detection_process.h>
#include <holo/hpp/scenario/scenario_hpp_struct.h>
#include <holo/planning/planner/velocity_planner/trapezoid_velocity_planner.h>

namespace holo
{
namespace planning
{
class DeciderLongitudinal : public DeciderLongitudinalBase
{
public:
    /**
     * @brief   Constructor
     */
    DeciderLongitudinal();

    /**
     * @brief   Destroy object
     */
    virtual ~DeciderLongitudinal() = default;

    /**
     * @brief      longitudinal decision of HPP
     *
     * @param[in]  state  The car road state
     * @param[in]  info The road info from loc and per
     * @param[out] output The output
     *
     * @return     True if no error occur, False otherwise.
     */
    virtual bool_t PerformHPP(HppCarRoadState const& state,
                              RoadInfo const&        info,
                              BehaviorState&         behavior_state,
                              HppOutput&             output) override;

    /**
     * @brief      longitudinal decision of AVP
     *
     * @param[in]  state  The car road state
     * @param[in]  info The road info from loc and per
     * @param[out] output The output
     *
     * @return     True if no error occur, False otherwise.
     */
    virtual bool_t PerformAVP(HppCarRoadState const& state,
                              RoadInfo const&        info,
                              BehaviorState&         behavior_state,
                              HppOutput&             output) override;

private:
    /**
     * @brief      safety monitor
     *
     * @param[in]  state  The car road state
     * @param[in]  cur_scene  0 : backward, 1 : Straight Line, 2 : Turnning
     * @param[out] output The output
     *
     * @return     True if no fault occur, False otherwise.
     */
    bool_t safetyMonitor(HppCarRoadState const& state, int32_t cur_scene, HppOutput& output);

    /**
     * @brief      Assign the velocity in speed_plan_list to path
     *
     * @param[in]  speed_plan_list  The planned velocity vector
     * @param[out]  path Path to be traited
     * @param[in] current_idx The starting point index of path
     *
     * @return     True if no error occur, False otherwise.
     */
    bool_t pathPointVelocityAssign(std::vector<float64_t> const& speed_plan_list,
                                   common::Path&                 path,
                                   size_t                        current_idx);

    /**
     * @brief Calculate vehicle drive distance by wheel pulse
     *
     * @param[in] state  The car road state
     * @param[in] start_left_pulse  The start left wheel pulse
     * @param[in] start_right_pulse  The start right wheel pulse
     *
     * @return The vehicle driving distance
     */
    float64_t CalcuDrivingDistanceByWheelPulse(HppCarRoadState const& state,
                                               uint32_t const&        start_left_pulse,
                                               uint32_t const&        start_right_pulse);

private:
    TrapezoidVelocityPlanner velocity_planner_;
    ObstacleDetectionProcess obstacle_detection_process_;

    bool_t use_avm_freespace_ = true;
    bool_t use_detection_     = true;

    float64_t follow_path_speed_ = 1.1;
    float64_t back_speed_        = 0.6;
    float64_t turn_speed_        = 0.8;
    float64_t laterror_speed_    = 0.83;

    float64_t avp_max_speed_            = 2.78;
    float64_t avp_obstacle_avoid_speed_ = 0.56;
    float64_t avp_turn_speed_           = 1.39;
    float64_t avp_crossroad_speed_      = 1.39;
    float64_t avp_slope_speed_          = 1.94;

    float64_t over_speed_time_threshold_ = 3.0;
    bool      enable_safety_monitor_     = false;

    float64_t              max_speed_ = 0.0;
    std::vector<float64_t> velocity_plan_list_;
    common::Timestamp      last_update_speed_timestamp_;
    common::Timestamp      last_speed_large_deviation_timestamp_;
    common::Timestamp      start_running_timestamp_;

    uint32_t  max_wheel_pulse_num_              = 4096;
    float64_t wheel_pulse_per_cycle_            = 86.0f;
    float64_t wheel_diameter_                   = 0.65f;
    uint32_t  laterror_start_left_wheel_pulse_  = 0;
    uint32_t  laterror_start_right_wheel_pulse_ = 0;
};

}  // namespace planning
}  // namespace holo

#endif
