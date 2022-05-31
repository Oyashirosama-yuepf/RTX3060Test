/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file scene_analyzer.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-04-27
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_INNER_SPLIT_SCENE_ANALYZER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_INNER_SPLIT_SCENE_ANALYZER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_analysis/inner_scene_analyzer_base.h>
#include <holo/map/feature/navigator/router/route_info.h>
#include <holo/map/format/base/lane.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
namespace scene
{
/**
 * @brief Scene analyzer for route links
 *
 * @details The lane path would go by sereral scenes including
 *          down ramp, going up main road, spliting on ramp
 */
class InnerSplitSceneAnalyzer : public InnerSceneAnalyzerBase
{
public:
    InnerSplitSceneAnalyzer();
    virtual ~InnerSplitSceneAnalyzer()                    = default;
    InnerSplitSceneAnalyzer(InnerSplitSceneAnalyzer const&) = delete;
    InnerSplitSceneAnalyzer(InnerSplitSceneAnalyzer&&)      = delete;
    InnerSplitSceneAnalyzer operator=(InnerSplitSceneAnalyzer const&) = delete;
    InnerSplitSceneAnalyzer operator=(InnerSplitSceneAnalyzer&&) = delete;

protected:
    /**
     * @brief make scene sketch using two links
     *
     * @param input lane instance
     * 
     * @return if true, input lane is breakup lane
     */
    virtual holo::bool_t makeSceneSketch(LaneGroupSPtrType entry_link, LaneGroupSPtrType exit_link,
                                         holo::bool_t& has_scene, SceneSketchSPtrType& scene) override;

private:
    holo::bool_t isLaneBoundaryHeadCrossed(LaneSPtrType lane);

};
}  // namespace scene
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_INNER_SPLIT_SCENE_ANALYZER_H_ */