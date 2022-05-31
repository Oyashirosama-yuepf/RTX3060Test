/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file composite_jct_scene_analyzer.h
 * @brief Scene Analyzer for composite jct scene, or a series scenes
 *        from down ramp to up main road
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-02-23
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_COMPOSITE_JCT_SCENE_ANALYZER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_COMPOSITE_JCT_SCENE_ANALYZER_H_

#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_analysis/scene_analyzer_base.h>

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
class CompositeJCTSceneAnalyzer : public SceneAnalyzerBase
{
public:
    CompositeJCTSceneAnalyzer();
    virtual ~CompositeJCTSceneAnalyzer()                                  = default;
    CompositeJCTSceneAnalyzer(CompositeJCTSceneAnalyzer const&)           = delete;
    CompositeJCTSceneAnalyzer(CompositeJCTSceneAnalyzer&&)                = delete;
    CompositeJCTSceneAnalyzer operator=(CompositeJCTSceneAnalyzer const&) = delete;
    CompositeJCTSceneAnalyzer operator=(CompositeJCTSceneAnalyzer&&) = delete;

    /**
     * @brief Analyze of composition from down ramp to up main road
     *
     * @param input Input of scene analyzer
     * @param output Output of scnen anlyzer
     * @return holo::bool_t True, succeed; false, otherwise
     */
    virtual holo::bool_t Composite(CompositeInput const& input, CompositeOutput& output) override;

};
}  // namespace scene
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_COMPOSITE_JCT_SCENE_ANALYZER_H_ */