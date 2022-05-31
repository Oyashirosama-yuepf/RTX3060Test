/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file composite_intersection_scene_analzyer.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-02-23
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_COMPOSITE_INTERSECTION_SCENE_ANALYZER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_COMPOSITE_INTERSECTION_SCENE_ANALYZER_H_

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
 * @brief Scene analyzer for composite intersection scenes
 *
 * @details The analyzer would extract composition of serveral
 *         intersection scenes
 */
class CompositeIntersectionSceneAnalyzer : public SceneAnalyzerBase
{
public:
    CompositeIntersectionSceneAnalyzer();
    virtual ~CompositeIntersectionSceneAnalyzer()                         = default;
    CompositeIntersectionSceneAnalyzer(CompositeIntersectionSceneAnalyzer const&) = delete;
    CompositeIntersectionSceneAnalyzer(CompositeIntersectionSceneAnalyzer&&)  = delete;
    CompositeIntersectionSceneAnalyzer operator=(CompositeIntersectionSceneAnalyzer const&) = delete;
    CompositeIntersectionSceneAnalyzer operator=(CompositeIntersectionSceneAnalyzer&&) = delete;

    virtual holo::bool_t Composite(CompositeInput const& input, CompositeOutput& output) override;

};
}  // namespace scene
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_COMPOSITE_INTERSECTION_SCENE_ANALYZER_H_*/