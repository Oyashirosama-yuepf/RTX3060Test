/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file breaking_lane_scene_analyzer.h
 * @brief Scene analyzer for breaking lane
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-02-23
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_BREAKING_LANE_SCENE_ANALYZER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_BREAKING_LANE_SCENE_ANALYZER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_analysis/inner_scene_analyzer_base.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>

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
 * @brief Scene analyzer for breaksing lane
 *
 * @details Breaksing lane, generally with no successive lanes,
 *          would be extract here
 * 
 */
class BreakingLaneAnalyzer : public InnerSceneAnalyzerBase
{
public:
    BreakingLaneAnalyzer();
    virtual ~BreakingLaneAnalyzer()                       = default;
    BreakingLaneAnalyzer(BreakingLaneAnalyzer const&)     = delete;
    BreakingLaneAnalyzer(BreakingLaneAnalyzer&&)          = delete;
    BreakingLaneAnalyzer operator=(BreakingLaneAnalyzer const&) = delete;
    BreakingLaneAnalyzer operator=(BreakingLaneAnalyzer&&) = delete;

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
};
}  // namespace scene
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_BREAKING_LANE_SCENE_ANALYZER_H_ */