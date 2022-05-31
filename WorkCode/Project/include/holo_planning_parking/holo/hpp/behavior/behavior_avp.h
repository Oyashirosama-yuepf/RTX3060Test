/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file behavior_avp.h
 * @brief the header of behavior avp
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2021-09-07
 */

#ifndef _HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_AVP_H_
#define _HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_AVP_H_

#include <holo/core/types.h>

#include <holo/hpp/behavior/behavior.h>

namespace holo
{
namespace planning
{
class BehaviorAvp : public Behavior
{
public:
    /**
     * @brief Constructor
     */
    BehaviorAvp();

    /**
     * @brief Destroy object
     */
    virtual ~BehaviorAvp() = default;

    /**
     * @brief avp behavior execution
     *
     * @param[in] state  The car road state
     * @param[in] info The road info from loc and per
     * @param[out] output The output
     *
     * @return True if perform successfully, false otherwise.
     */
    virtual bool_t Perform(HppCarRoadState const& state, RoadInfo const& info, HppOutput& output);

private:
    float64_t dynamic_path_length_ = 15.0;  // path length for path follow
};
}  // namespace planning
}  // namespace holo

#endif  //_HOLO_PLANNING_PARKING_BEHAVIOR_BEHAVIOR_AVP_H_
