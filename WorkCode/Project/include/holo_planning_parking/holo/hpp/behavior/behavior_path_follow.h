/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file behavior_path_follow.h
 * @brief the header of behavior of path follow
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2021-04-08
 */

#ifndef _HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_PATH_FOLLOW_H_
#define _HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_PATH_FOLLOW_H_

#include <holo/hpp/behavior/behavior.h>

namespace holo
{
namespace planning
{
class BehaviorPathFollow : public Behavior
{
public:
    /**
     * @brief   Constructor
     */
    BehaviorPathFollow();

    /**
     * @brief   Destroy object
     */
    virtual ~BehaviorPathFollow() = default;

    /**
     * @brief      path follow behavior execution
     *
     * @param[in]  state  The car road state
     * @param[in]  info The road info from loc and per
     * @param[out] output The output
     *
     * @return     True if no error occur, False otherwise.
     */
    virtual bool_t Perform(HppCarRoadState const& state, RoadInfo const& info, HppOutput& output);

private:
    float64_t dynamic_path_length_ = 15.0;  /// path length for path follow
};
}  // namespace planning
}  // namespace holo

#endif
