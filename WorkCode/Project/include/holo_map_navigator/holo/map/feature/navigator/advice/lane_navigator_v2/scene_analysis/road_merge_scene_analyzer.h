/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_merge_scene_analyzer.h
 * @brief Generate road merging scene for road-level
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-02-23
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_ROAD_MERGE_SCENE_ANALYZER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_ROAD_MERGE_SCENE_ANALYZER_H_

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
 * @brief Scene analyzer for road-level scene
 *
 */
class RoadMergeSceneAnalyzer : public SceneAnalyzerBase
{
public:
    using SceneSketchType        = holo::map::navigator::advice::scene::SceneSketch;
    using SceneSketchSPtrType    = std::shared_ptr<SceneSketchType>;
    using SceneSketchSPtrVecType = std::vector<SceneSketchSPtrType>;

public:
    RoadMergeSceneAnalyzer();
    virtual ~RoadMergeSceneAnalyzer()                       = default;
    RoadMergeSceneAnalyzer(RoadMergeSceneAnalyzer const&)   = delete;
    RoadMergeSceneAnalyzer(RoadMergeSceneAnalyzer&&)        = delete;
    RoadMergeSceneAnalyzer operator=(RoadMergeSceneAnalyzer const&) = delete;
    RoadMergeSceneAnalyzer operator=(RoadMergeSceneAnalyzer&&) = delete;

    /**
     * @brief Analyze for road-level merging scene
     *
     * @param input Input of scene analyzer
     * @param output Output of scnen anlyzer
     * @return holo::bool_t True, succeed; fasle, othersie
     */
    virtual holo::bool_t Calculate(Input const& input, Output& output) override;

private:
    holo::bool_t isMainRoad(LaneGroupType const type);
    holo::bool_t isRamp(LaneGroupType const type);
    holo::bool_t getSceneType(LaneGroupSPtrType scene_entry, LaneGroupSPtrType scene_exit, SceneCategoryType& type);
    holo::bool_t makeSceneSketch(
        LaneGroupSPtrType scene_entry, LaneGroupSPtrType scene_exit,  SceneSketchSPtrType& scene);
};
}  // namespace scene
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_ROAD_MERGE_SCENE_ANALYZER_H_ */