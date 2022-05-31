/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file decider_longitudinal_base.h
 * @brief the header of longitudinal decider base for hpp scenario
 * @author huangnan(huangnan@holomatic.com)
 * @date 2022-01-14
 */

#ifndef _HOLO_PLANNING_PARKING_DECIDER_LONGITUDINAL_BASE_H_
#define _HOLO_PLANNING_PARKING_DECIDER_LONGITUDINAL_BASE_H_

#include <holo/hpp/hpp_car_road_state.h>
#include <holo/hpp/scenario/scenario_hpp_struct.h>

namespace holo
{
namespace planning
{
class DeciderLongitudinalBase
{
public:
    /**
     * @brief   Constructor
     */
    DeciderLongitudinalBase(){};

    /**
     * @brief   Destroy object
     */
    virtual ~DeciderLongitudinalBase() = default;

    /**
     * @brief      longitudinal decision of HPP
     *
     * @param[in]  state  The car road state
     * @param[in]  info The road info from loc and per
     * @param[out] output The output
     *
     * @return     True if no error occur, False otherwise.
     */
    virtual bool_t
    PerformHPP(HppCarRoadState const& state, RoadInfo const& info, BehaviorState& behavior_state, HppOutput& output);

    /**
     * @brief      longitudinal decision of AVP
     *
     * @param[in]  state  The car road state
     * @param[in]  info The road info from loc and per
     * @param[out] output The output
     *
     * @return     True if no error occur, False otherwise.
     */
    virtual bool_t
    PerformAVP(HppCarRoadState const& state, RoadInfo const& info, BehaviorState& behavior_state, HppOutput& output);
};

}  // namespace planning
}  // namespace holo

#endif