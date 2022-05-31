/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file behavior.h
 * @brief the header of behavior base class
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2021-04-08
 */

#ifndef _HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_H_
#define _HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_H_

#include <holo/hpp/hpp_car_road_state.h>
#include <holo/hpp/scenario/scenario_hpp_struct.h>

namespace holo
{
namespace planning
{
class Behavior
{
public:
    /**
     * @brief   Constructor
     */
    Behavior() = default;

    /**
     * @brief   Destroy object
     */
    virtual ~Behavior() = default;

    /**
     * @brief      behavior execution
     *
     * @param[in]  state  The car road state
     * @param[in]  info The road info from loc and per
     * @param[out] output The output
     *
     * @return     True if no error occur, False otherwise.
     */
    virtual bool_t Perform(HppCarRoadState const& state, RoadInfo const& info, HppOutput& output) = 0;

    /**
     * @brief judge if behavior is preemptible
     *
     * @return true if preemptible
     */
    virtual bool_t IsPreemptible()
    {
        return preemptible_;
    }

protected:
    bool_t    preemptible_             = false;
};
}  // namespace planning
}  // namespace holo

#endif
