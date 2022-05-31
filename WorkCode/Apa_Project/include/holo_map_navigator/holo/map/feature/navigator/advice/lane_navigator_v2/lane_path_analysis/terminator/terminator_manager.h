/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file terminator_manager.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-23
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_TERMINATOR_MANAGER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_TERMINATOR_MANAGER_H_

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/terminator/terminator_base.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>
#include <holo/map/feature/navigator/router/route_info.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_analysis/key_lane_tracker.h>

#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/terminator/no_succeed_terminator.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/terminator/merge_terminator.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/terminator/intersection_terminator.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/terminator/jct_terminator.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/terminator/down_ramp_termiantor.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/terminator/default_merge_terminator.h>

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
class TerminatorManager
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
    using TerminatorBaseType     = holo::map::navigator::advice::lanepath::TerminatorBase;
    using TerminatorSPtrType     = std::shared_ptr<TerminatorBaseType>;
    using TerminatorSPtrVecType  = std::vector<TerminatorSPtrType>;

public:
    TerminatorManager()  = default;
    ~TerminatorManager() = default;

public:
    /**
     * @brief Add a new termiator
     *
     * @param terminator new added terminator
     * @return
     */
    void Add(TerminatorSPtrType const& terminator);

    /**
     * @brief Delete a terminator by given mode
     *
     * @param mode terminator mode
     * @return
     */
    void Remove(TerminatorBaseType::TerminatorCategory const& mode);

    /**
     * @brief Delete all terminators
     *
     * @param
     * @return
     */
    void Clear();

    /**
     * @brief Update contraints using all simple scenes on route of current frame
     *
     * @param scenes all simple scenes
     * @return holo::bool_t
     */
    holo::bool_t Update(SceneSketchSPtrVecType const& scenes);

    /**
     * @brief Update route info
     *
     * @param route_info
     * @return holo::bool_t
     */
    holo::bool_t Update(RouteInfo2::Ptr route_info);

    /**
     * @brief Constrain items
     *
     * @param targets
     * @return holo::bool_t
     */
    holo::bool_t Check(TerminatorBase::TerminatorTarget& target);

    /**
     * @brief Set the max distance for terminate for the lane
     */
    holo::bool_t SetSearchDistance(holo::float64_t const dist);
    

protected:
    /// Terminators for lane path generator
    TerminatorSPtrVecType terminators_;
};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_TERMINATOR_MANAGER_H_ */