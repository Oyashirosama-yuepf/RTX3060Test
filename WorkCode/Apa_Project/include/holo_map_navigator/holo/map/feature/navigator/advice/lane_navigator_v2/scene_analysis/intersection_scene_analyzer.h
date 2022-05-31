/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file intersection_scene_analyzer.h
 * @brief Scene analzyer for intersection
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-02-23
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_INTERSECTION_SCENE_ANALYZER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_INTERSECTION_SCENE_ANALYZER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_analysis/scene_analyzer_base.h>
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
 * @brief Scene analyzer for intersection
 *
 */
class IntersectionSceneAnalyzer : public SceneAnalyzerBase
{
public:
    using SceneSketchType        = holo::map::navigator::advice::scene::SceneSketch;
    using SceneSketchSPtrType    = std::shared_ptr<SceneSketchType>;
    using SceneSketchSPtrVecType = std::vector<SceneSketchSPtrType>;

public:
    IntersectionSceneAnalyzer();
    virtual ~IntersectionSceneAnalyzer()                  = default;
    IntersectionSceneAnalyzer(IntersectionSceneAnalyzer const&) = delete;
    IntersectionSceneAnalyzer(IntersectionSceneAnalyzer&&)      = delete;
    IntersectionSceneAnalyzer operator=(IntersectionSceneAnalyzer const&) = delete;
    IntersectionSceneAnalyzer operator=(IntersectionSceneAnalyzer&&) = delete;

    /**
     * @brief Analyze for road level scene
     *
     * @param input Input of scene analyzer
     * @param output Output of scnen anlyzer
     * @return holo::bool_t True, succeed; false, otherwise
     */
    virtual holo::bool_t Calculate(Input const& input, Output& output) override;

private:
    holo::bool_t getSceneType(LaneGroupSPtrType intersection, SceneCategoryType& type);
    holo::bool_t makeSceneSketch(
        LaneGroupSPtrType scene_entry, LaneGroupSPtrType intersection, LaneGroupSPtrType scene_exit, 
        Distance distance_to_car, SceneSketchSPtrType& scene);

};
}  // namespace scene
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_INTERSECTION_SCENE_ANALYZER_H_ */