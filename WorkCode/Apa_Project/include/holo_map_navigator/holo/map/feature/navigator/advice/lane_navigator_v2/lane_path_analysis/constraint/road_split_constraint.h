/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_split_constraint.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-7
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_ROAD_SPLIT_CONSTRAINT_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_ROAD_SPLIT_CONSTRAINT_H_

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>
#include <holo/map/feature/navigator/router/route_info.h>

#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/constraint/constraint_base.h>

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
class RoadSplitConstraint : public ConstraintBase
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

public:
    /**
     * @brief Constrain items
     *
     * @param targets
     * @return holo::bool_t
     */
    virtual holo::bool_t Constrain(ConstrainedTarget& target) override;

private:
    holo::bool_t isRouteSplitRight(holo::bool_t& is_right_split);
    holo::bool_t isRouteSplitLeft(holo::bool_t& is_left_split);
    holo::bool_t isLaneSplit(LaneItemSPtrType const in_lane_item,
        holo::bool_t& is_left_split, holo::bool_t& is_right_split);
    holo::bool_t match(LaneItemSPtrType const& lane_item, 
        holo::bool_t& item_in_scope, holo::bool_t& in_route_branch, SceneSketchSPtrType& relate_scene);
    holo::bool_t check(LaneItemSPtrType const& lane_item_to_match, holo::bool_t& need_constrain);

};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_ROAD_SPLIT_CONSTRAINT_H_  */