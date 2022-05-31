/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file scenario_parking_base.h
 * @brief the header of scenario parking base class
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2021-09-03
 */

#ifndef _HOLO_PLANNING_PARKING_SCENARIO_SCENARIO_PARKING_BASE_H_
#define _HOLO_PLANNING_PARKING_SCENARIO_SCENARIO_PARKING_BASE_H_

#include <memory>

#include <holo/core/types.h>

#include <holo/hpp/behavior/behavior.h>
#include <holo/hpp/hpp_car_road_state.h>
#include <holo/hpp/scenario/scenario_hpp_struct.h>

namespace holo
{
namespace planning
{
/**
 * @brief The base class of scenario in parking
 */
class ScenarioParkingBase
{
public:
    /**
     * @brief Constructor
     */
    ScenarioParkingBase();

    /**
     * @brief Destroy object
     */
    virtual ~ScenarioParkingBase() = default;

    /**
     * @brief plan in hpp scenario
     *
     * @param[in] state  The car road state
     * @param[out] output The output
     *
     * @return True if plan successfully, false otherwise.
     */
    virtual bool_t Plan(HppCarRoadState const& state, HppOutput& output);

    /**
     * @brief check path curvature
     *
     * @param[out] output The output
     *
     * @return True if path curvature over threshold, false otherwise.
     */
    void CurvatureCheck(HppCarRoadState const& state, HppOutput& output);

protected:
    virtual bool_t selectBehavior(HppCarRoadState const& state, HppOutput& output) = 0;

protected:
    BehaviorState             behavior_state_;
    std::shared_ptr<Behavior> behavior_;
    RoadInfo                  info_;

    float64_t max_curvature_threshold_ = 0.2;
    float64_t need_reextract_distance_ = 20.0;
};

}  // namespace planning
}  // namespace holo

#endif  //_HOLO_PLANNING_PARKING_SCENARIO_SCENARIO_PARKING_BASE_H_
