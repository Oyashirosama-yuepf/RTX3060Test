/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file behavior_path_follow_start.h
 * @brief the header of behavior of path follow start
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2021-04-08
 */

#ifndef _HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_PATH_FOLLOW_START_H_
#define _HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_PATH_FOLLOW_START_H_

#include <holo/hpp/behavior/behavior.h>

namespace holo
{
namespace planning
{
class BehaviorPathFollowStart : public Behavior
{
public:
    /**
     * @brief   Constructor
     */
    BehaviorPathFollowStart();

    /**
     * @brief   Destroy object
     */
    virtual ~BehaviorPathFollowStart() = default;

    /**
     * @brief      path follow start behavior execution
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
