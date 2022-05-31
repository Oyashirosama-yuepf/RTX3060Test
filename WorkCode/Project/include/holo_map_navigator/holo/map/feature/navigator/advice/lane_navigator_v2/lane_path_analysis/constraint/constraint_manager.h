/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file constraint_manager.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-7
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_CONSTRAINT_MANAGER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_CONSTRAINT_MANAGER_H_

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/constraint/constraint_base.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>
#include <holo/map/feature/navigator/router/route_info.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_analysis/key_lane_tracker.h>

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
class ConstraintManager
{
public:
    using LaneItemSPtrType       = std::shared_ptr<LaneItem>;
    using LaneItemSPtrVecType    = std::vector<LaneItemSPtrType>;
    using LanePathSPtrType       = std::shared_ptr<LanePath>;
    using LanePathSPtrVecType    = std::vector<LanePathSPtrType>;
    using SceneSketchType        = holo::map::navigator::advice::scene::SceneSketch;
    using SceneCategoryType      = SceneSketchType::SceneCategory;
    using SceneSketchSPtrType    = std::shared_ptr<SceneSketchType>;
    using SceneSketchSPtrVecType = std::vector<SceneSketchSPtrType>;
    using ConstraintBaseType     = holo::map::navigator::advice::lanepath::ConstraintBase;
    using ConstraintSPtrType     = std::shared_ptr<ConstraintBaseType>;
    using ConstraintSPtrVecType  = std::vector<ConstraintSPtrType>;

    using ConstraintTargetType     = ConstraintBaseType::ConstrainedTarget;

    using ConstraintSceneType    = ConstraintBaseType::ConstraintScene;
    using ConstraintSceneSPtrType = std::shared_ptr<ConstraintSceneType>;
    using ConstraintSceneSPtrVecType = std::vector<ConstraintSceneSPtrType>;
    using KeyLaneTrackerType   = holo::map::navigator::advice::scene::LaneTracker;
    using KeyLaneTrackerSPtrType   = std::shared_ptr<KeyLaneTrackerType>;

public:
    ConstraintManager() = default;
    ~ConstraintManager() = default;

public:
    holo::bool_t Init();
    /**
     * @brief Update contraints using all simple scenes on route of current frame in generator of default
     *
     * @param scenes all simple scenes
     * @return holo::bool_t
     */
    holo::bool_t UpdateDefaultGenerator(SceneSketchSPtrVecType const& scenes);

    /**
     * @brief Update contraints using all simple scenes on route of current frame in generator of split
     *
     * @param scenes all simple scenes
     * @return holo::bool_t
     */
    holo::bool_t UpdateSplitGenerator(SceneSketchSPtrVecType const& scenes);

    /**
     * @brief Constrain items
     *
     * @param targets
     * @return holo::bool_t
     */
    holo::bool_t Constrain(ConstraintTargetType& target);

protected:
    /// Constraints for lane path generator
    ConstraintSPtrVecType constraints_;

private:
    const DistanceTypeV0 MAX_DISTANCE_BETWEEN_INNER_SPLIT_SCENE_AND_ROAD_SPLIT_SCENE = 200;

private:
    holo::bool_t isInnerSplitType(SceneCategoryType const& category);
    holo::bool_t isInnerMergeType(SceneCategoryType const& category);
    holo::bool_t isRoadSplitType(SceneCategoryType const& category);
    holo::bool_t isRoadMergeType(SceneCategoryType const& category);
    holo::bool_t getAllInnerSplitScene(SceneSketchSPtrVecType const& input, SceneSketchSPtrVecType& output);
    holo::bool_t getAllInnerMergeScene(SceneSketchSPtrVecType const& input, SceneSketchSPtrVecType& output);
    holo::bool_t getAllRoadSplitScene(SceneSketchSPtrVecType const& input, SceneSketchSPtrVecType& output);
    holo::bool_t getAllRoadMergeScene(SceneSketchSPtrVecType const& input, SceneSketchSPtrVecType& output);
    holo::bool_t makeContrantData(SceneSketchSPtrType const& input, SceneSketchSPtrVecType const& sub_scenes, ConstraintSceneSPtrType& constraint_scene);
    holo::bool_t makeConstraint(ConstraintSceneSPtrType const& constraint_scene, ConstraintSPtrType& constraint);
    holo::bool_t makeNoConstraint(ConstraintSceneSPtrType const& constraint_scene, ConstraintSPtrType& constraint);
    IdType       makeInnerContrantData(SceneSketchSPtrType const& input, SceneSketchSPtrVecType const& sub_scenes,
                                       IdType const target_split_road_id, ConstraintSceneSPtrType& constraint_scene);
    holo::bool_t GetVerbose() const noexcept;
    void SetVerbose(holo::bool_t const v) noexcept;

private:
    KeyLaneTrackerSPtrType lane_tracker_ = nullptr;

    /// If true, print debugging messages to log.
    holo::bool_t verbose_ = true;
    
};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_CONSTRAINT_BASE_H_ */