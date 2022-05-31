/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file scene_analyzer_manager.h
 * @brief Management of serveral scene analzyers
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-02-23
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_SCENE_ANALYZER_MANAGER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_SCENE_ANALYZER_MANAGER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_analysis/scene_analyzer_base.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_analysis/key_lane_tracker.h>

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
class SceneAnalyzerManager
{
public:
    using SceneSketchType          = holo::map::navigator::advice::scene::SceneSketch;
    using SceneSketchSPtrType      = std::shared_ptr<SceneSketchType>;
    using SceneSketchSPtrVecType   = std::vector<SceneSketchSPtrType>;
    using CompositeSceneSketchType          = holo::map::navigator::advice::scene::CompositeSceneSketch;
    using CompositeSceneSketchSPtrType      = std::shared_ptr<CompositeSceneSketchType>;
    using CompositeSceneSketchSPtrVecType   = std::vector<CompositeSceneSketchSPtrType>;
    using SceneAnalyzerSPtrType    = std::shared_ptr<SceneAnalyzerBase>;
    using SceneAnalyzerSPtrVecType = std::vector<SceneAnalyzerSPtrType>;
    using KeyLaneTrackerSPtrType   = std::shared_ptr<LaneTracker>;

    struct Input
    {
        /// Link ids passed by route info
        std::vector<holo::uint64_t> route_link_ids;
        /// Current matched link id
        holo::uint64_t current_matched_link_id = 0U;
        /// Distance to current link end; unit: meters
        holo::float64_t distance_to_link_end = 0.0f;
        /// Maximum distance for searching to extract scene
        holo::float64_t maximum_search_distance = 0.0f;
    };
    struct Output
    {
        SceneSketchSPtrVecType simple_scenes;
        /// All scene sketches extracted from link ids of route info
        SceneSketchSPtrVecType scene_sketchs;
    };

public:
    SceneAnalyzerManager()              = default;
    virtual ~SceneAnalyzerManager()     = default;
    SceneAnalyzerManager(SceneAnalyzerManager const&) = delete;
    SceneAnalyzerManager(SceneAnalyzerManager&&)      = delete;
    SceneAnalyzerManager operator=(SceneAnalyzerManager const&) = delete;
    SceneAnalyzerManager operator=(SceneAnalyzerManager&&) = delete;

    holo::bool_t Init();
    /**
     * @brief Analyze for road level scene
     *
     * @param input Input of scene analyzer
     * @param output Output of scnen anlyzer
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t Calculate(Input const& input, Output& output);

    holo::bool_t GetVerbose() const noexcept;
    void SetVerbose(holo::bool_t const v) noexcept;

private:
    holo::bool_t updateNearestCompositeScene(SceneSketchSPtrVecType const& simple_scenes);
    holo::bool_t updateNearestRoadMergeScene(SceneSketchSPtrVecType const& simple_scenes);
    holo::bool_t calculateSimpleScene(SceneAnalyzerBase::Input const& input, SceneSketchSPtrVecType& scenes);
    holo::bool_t calculateCompositeScene(SceneSketchSPtrVecType const& input, CompositeSceneSketchSPtrVecType& output);

private:
    SceneAnalyzerSPtrVecType scene_analyzers_;
    SceneAnalyzerSPtrVecType composite_analyzers_;
    KeyLaneTrackerSPtrType key_lane_tracker_ = nullptr;

    CompositeSceneSketchSPtrType nearest_composite_scene_ = nullptr;
    SceneSketchSPtrType nearest_road_merge_scene_         = nullptr;

    /// If true, print debugging messages to log.
    holo::bool_t verbose_ = true;

};
}  // namespace scene
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_SCENE_ANALYZER_MANAGER_H_ */