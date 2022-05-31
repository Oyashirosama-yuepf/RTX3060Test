/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file down_ramp_terminator.h
 * @brief Terminator is used to stop extending of lane path
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-23
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_DOWN_RAMP_TERMINATOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_DOWN_RAMP_TERMINATOR_H_

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/terminator/terminator_base.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>
#include <holo/map/feature/navigator/router/route_info.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
namespace lanepath
{
class DownRampTerminator : public TerminatorBase
{
public:
    /**
     * @brief Whethor or not the terminator take effect
     *
     * @return holo::bool_t True, take effect; false, no effect
     */
    virtual holo::bool_t Enable() override;

    /**
     * @brief Compared with another terminator
     *
     * @param terminator Another terminator
     * @return holo::bool_t True, take priority over another; false, not prior, may equally
     */
    virtual holo::bool_t HavePriorityOver(TerminatorSPtrType terminator) override;

    /**
     * @brief Get the Category
     *
     * @return TerminatorCategory
     */
    virtual TerminatorCategory GetCategory() override;

protected:
    /**
     * @brief Check the whether or not the target should be stop to extend
     *
     * @param targets Targets that should be checked
     * @return holo::bool_t True, succeed; false, otherwise
     */
    virtual holo::bool_t doCheck(TerminatorTarget& target) override;

private:
    holo::bool_t checkHaltLanePathBeforeJCT(TerminatorTarget& target);
};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_DOWN_RAMP_TERMINATOR_H_ */