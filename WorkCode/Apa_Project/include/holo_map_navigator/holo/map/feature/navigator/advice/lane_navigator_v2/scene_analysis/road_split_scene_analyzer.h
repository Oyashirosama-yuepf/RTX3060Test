/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_split_scene_analzyer.h
 * @brief Calculating for road-level splitting scene
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-02-23
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_ROAD_SPLIT_SCENE_ANALYZER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_ROAD_SPLIT_SCENE_ANALYZER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>
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
class RoadSplitSceneAnalyzer : public SceneAnalyzerBase
{
public:
    RoadSplitSceneAnalyzer();
    virtual ~RoadSplitSceneAnalyzer()   = default;
    RoadSplitSceneAnalyzer(RoadSplitSceneAnalyzer const&) = delete;
    RoadSplitSceneAnalyzer(RoadSplitSceneAnalyzer&&)      = delete;
    RoadSplitSceneAnalyzer operator=(RoadSplitSceneAnalyzer const&) = delete;
    RoadSplitSceneAnalyzer operator=(RoadSplitSceneAnalyzer&&) = delete;

    /**
     * @brief Analyze for road level scene
     *
     * @param input Input of scene analyzer
     * @param output Output of scnen anlyzer
     * @return holo::bool_t
     */
    virtual holo::bool_t Calculate(Input const& input, Output& output) override;

private:
    holo::bool_t makeTargetRegion(FeatureIdType const lane_id, KeyLaneSectionType& lane_section);
    holo::bool_t makeSceneSketch(LaneGroupSPtrType scene_entry, LaneGroupSPtrType scene_exit, SceneSketchSPtrType& sketch);
    holo::bool_t isMainRoad(LaneGroupType const type);
    holo::bool_t isRamp(LaneGroupType const type);
    holo::bool_t getSceneType(LaneGroupSPtrType scene_entry, LaneGroupSPtrType scene_exit, SceneCategoryType& type);

};
}  // namespace scene
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_ROAD_SPLIT_SCENE_ANALYZER_H_ */