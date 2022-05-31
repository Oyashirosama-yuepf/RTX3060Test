/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_path_attribute.h
 * @brief update lane path attributes
 * @author zhegnshulei (zhegnshulei@holomatic.com)
 * @date 2022-4-7
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_GRADING_GRADING_BASE_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_GRADING_GRADING_BASE_H_

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>

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
/**
 * @brief LanePath grading based the key scene before ego-car.
 * 
 */
class GradingBase
{
public:
    using LanePathSPtrType       = std::shared_ptr<LanePath>;
    using LanePathSPtrVecType    = std::vector<LanePathSPtrType>;
    using LaneItemSPtrType       = std::shared_ptr<LaneItem>;
    using LaneItemSPtrVecType    = std::vector<LaneItemSPtrType>;
    using SceneSketchType        = holo::map::navigator::advice::scene::SceneSketch;
    using SceneSketchSPtrType    = std::shared_ptr<SceneSketchType>;
    using SceneSketchSPtrVecType = std::vector<SceneSketchSPtrType>;

    enum class GradingMode : holo::uint8_t
    {
        UNDEFINED = 0U,
        ROAD_SPLIT_TWO_RAMP_BRANCH,
        ROAD_SPLIT_TWO_MAIN_BRANCH,
        ROAD_SPLIT_MAIN_DOWN_RAMP
    };

public:
    GradingBase() = default;
    virtual ~GradingBase() = default;

public:
    /**
     * @brief Update all lane path attribute, include level, candidate lane id, etc. 
     *
     * @param all_lane_paths all lane paths need update attribute
     * @return holo::bool_t True, succeed; false, otherwise
     */
    virtual holo::bool_t UpdateAllLanePath(LanePathSPtrVecType& all_lane_paths) = 0;

public:
    /**
     * @brief Get key scene used for lanepath grading
     * 
     */
    SceneSketchSPtrType GetKeyScene() const;
    /**
     * @brief Set key scene used for lanepath grading
     *
     * @param key_scene key scene, which is the first road split/merge or intersection scene.
     *
     */
    void SetKeyScene(SceneSketchSPtrType key_scene);
    /**
     * @brief Get key scene used for lanepath grading
     *
     */
    holo::bool_t GetVerbose() const;
    /**
     * @brief Set verbose
     *
     * @param v if true, print debug info log.
     *
     */
    void SetVerbose(holo::bool_t v);

protected:
    /// first key scene befor car
    SceneSketchSPtrType key_scene_ = nullptr;
    /// debug log
    holo::bool_t verbose_ = true;
    /// Grading mode
    GradingMode grading_mode_ = GradingMode::UNDEFINED;
};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_GRADING_GRADING_BASE_H_ */