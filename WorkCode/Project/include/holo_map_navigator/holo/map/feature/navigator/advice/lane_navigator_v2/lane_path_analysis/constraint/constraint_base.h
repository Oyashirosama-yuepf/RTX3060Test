/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file constraint_base.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-7
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_CONSTRAINT_BASE_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_CONSTRAINT_BASE_H_

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/key_lane_section.h>
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
class ConstraintBase
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

    using KeyLaneSectionType = holo::map::navigator::advice::scene::KeyLaneSection;
    using KeyLaneSectionSPtrType = std::shared_ptr<KeyLaneSectionType>;
    using KeyLaneSectionSPtrVecType = std::vector<KeyLaneSectionSPtrType>;

    struct ConstraintScene;
    using ConstraintSceneType    = ConstraintScene;
    using ConstraintSceneSPtrType = std::shared_ptr<ConstraintSceneType>;
    using ConstraintSceneSPtrVecType = std::vector<ConstraintSceneSPtrType>;

    struct ConstraintScene
    {
        SceneCategoryType main_category; ///< main scene category
        SceneSketchSPtrType main_scene;  ///< main scene instance
        RawFeatureIdVectorTypeV0 all_special_ids;
        RawFeatureIdVectorTypeV0 valid_special_ids;
        SceneSketchSPtrVecType related_scenes; ///< related inner split/merge scenes
    };

    struct ConstrainedTarget
    {
        LaneItemSPtrType newborn = nullptr;
        holo::bool_t     is_constrained = false;
    };

public:
    static std::string FormatToString(ConstraintScene const& contraint_scene);

public:
    ConstraintBase() = default;
    virtual ~ConstraintBase() = default;

public:
    virtual holo::bool_t Init();
    /**
     * @brief Constrain items
     * 
     * @param targets 
     * @return holo::bool_t 
     */
    virtual holo::bool_t Constrain(ConstrainedTarget& target) = 0;

    ConstraintSceneSPtrType const GetConstraintScene()  noexcept;
    ConstraintSceneSPtrType const GetConstraintScene() const  noexcept;
    void SetConstraintScene(ConstraintSceneSPtrType const& data) noexcept;

    holo::bool_t GetVerbose() const noexcept;
    void SetVerbose(holo::bool_t const v) noexcept;

protected:
    RawRetrieverSPtrType raw_retriever_ = nullptr;
    /// Scene analyzing results from scene analyzer
    SceneSketchSPtrVecType scene_sketchs_;

    ConstraintSceneSPtrType Constraint_scene_ = nullptr;

    /// If true, print debugging messages to log.
    holo::bool_t verbose_ = true;

};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_CONSTRAINT_BASE_H_ */