/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file behavior_pullout.h
 * @brief the header of behavior of pullout
 * @author yansenwei(yansenwei@holomatic.com)
 * @date 2021-05-14
 */

#ifndef _HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_PULLOUT_H_
#define _HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_PULLOUT_H_

#include <holo/hpp/behavior/behavior.h>
#include <holo/hpp/parkingplan/parkingplan.h>

namespace holo
{
namespace planning
{
class BehaviorPullout : public Behavior
{
public:
    /**
     * @brief   Constructor
     */
    BehaviorPullout();

    /**
     * @brief   Destroy object
     */
    virtual ~BehaviorPullout() = default;

    /**
     * @brief      pullout behavior execution
     *
     * @param[in]  state  The car road state
     * @param[in]  info The road info from loc and per
     * @param[out] output The output
     *
     * @return     True if no error occur, False otherwise.
     */
    virtual bool_t Perform(HppCarRoadState const& state, RoadInfo const& info, HppOutput& output);
};
}  // namespace planning
}  // namespace holo

#endif
