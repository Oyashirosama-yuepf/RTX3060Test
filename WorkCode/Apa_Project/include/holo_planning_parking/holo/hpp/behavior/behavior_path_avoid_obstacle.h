/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file behavior_path_avoid_obstacle.h
 * @brief the header of behavior of avoid obstacle
 * @author lizhao(lizhao@holomatic.com)
 * @date 2021-06-07
 */

#ifndef _HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_PATH_AVOID_PATH_H_
#define _HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_PATH_AVOID_PATH_H_

#include <holo/hpp/behavior/behavior.h>

namespace holo
{
namespace planning
{
class BehaviorPathAvoidObstacle : public Behavior
{
public:
    /**
     * @brief   Constructor
     */
    BehaviorPathAvoidObstacle();

    /**
     * @brief   Destroy object
     */
    virtual ~BehaviorPathAvoidObstacle() = default;

    /**
     * @brief      path avoid obstacle  behavior execution
     *
     * @param[in]  state  The car road state
     * @param[in]  info The road info from loc and per
     * @param[out] output The output
     *
     * @return     True if no error occur, False otherwise.
     */
    virtual bool_t Perform(HppCarRoadState const& state, RoadInfo const& info, HppOutput& output);

private:
    size_t FindNearestPathIndex(std::vector<CurvePoint> path, float64_t x, float64_t y);

private:
    float64_t dynamic_path_length_ = 15.0;  /// path length for path follow
};
}  // namespace planning
}  // namespace holo

#endif
