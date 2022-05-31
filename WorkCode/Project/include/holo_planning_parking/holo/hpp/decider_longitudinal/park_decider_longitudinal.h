/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file decider_longitudinal_pullout.h
 * @brief the header of longitudinal decider for hpp scenario
 * @author huangnan(huangnan@holomatic.com)
 * @date 2022-01-14
 */

#ifndef _HOLO_PLANNING_PARKING_DECIDER_LONGITUDINAL_PARK_H_
#define _HOLO_PLANNING_PARKING_DECIDER_LONGITUDINAL_PARK_H_

#include <holo/hpp/decider_longitudinal/decider_longitudinal_base.h>
#include <holo/hpp/hpp_car_road_state.h>
#include <holo/hpp/obstacle_avoid/park_obstacle_detection_process.h>
#include <holo/hpp/scenario/scenario_hpp_struct.h>
#include <holo/planning/planner/velocity_planner/park_velocity_planner.h>

namespace holo
{
namespace planning
{
class ParkDeciderLongitudinal : public DeciderLongitudinalBase
{
public:
    /**
     * @brief   Constructor
     */
    ParkDeciderLongitudinal();

    /**
     * @brief   Destroy object
     */
    virtual ~ParkDeciderLongitudinal() = default;

    /**
     * @brief      longitudinal decision
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

    virtual bool_t PerformAVP(HppCarRoadState const& state,
                              RoadInfo const&        info,
                              BehaviorState&         behavior_state,
                              HppOutput&             output) override;

private:
    ParkVelocityPlanner          park_velocity_planner_;
    ParkObstacleDetectionProcess park_obstacle_detection_process_;

    bool_t use_freespace_     = true;
    bool_t use_avm_freespace_ = true;
    bool_t use_detection_     = true;

    float64_t forward_speed_pullout_ = 0.8;
    float64_t back_speed_pullout_    = 0.6;
    float64_t forward_speed_parkin_  = 0.4;
    float64_t back_speed_parkin_     = 0.3;
};

}  // namespace planning
}  // namespace holo

#endif