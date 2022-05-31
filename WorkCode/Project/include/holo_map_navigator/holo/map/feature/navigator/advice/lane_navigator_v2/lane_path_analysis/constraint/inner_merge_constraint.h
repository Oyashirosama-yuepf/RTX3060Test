/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file inner_merge_constraint.h
 * @brief Default constraint based on lane boundary line type(solid/dashed) to fix topo error
 * @author zhengshulei(zhengshulei@holomatic.com)
 * @date 2022-3-7
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_INNER_MAERGE_CONSTRAINT_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_INNER_MAERGE_CONSTRAINT_H_

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
class InnerMergeConstraint : public ConstraintBase
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
    virtual holo::bool_t Constrain(ConstrainedTarget& target) override;

private:
    holo::bool_t getMergeDirection(LaneItemSPtrType const in_lane_item,
                                   holo::bool_t& is_left_merge, 
                                   holo::bool_t& is_right_merge);

    holo::bool_t constrainMergeRight(ConstrainedTarget& target);

private:
    /// TODO: FIX MERGE RIGHT FOR EHP MAP
    holo::bool_t constrain_merge_right_ = true;

};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_INNER_MAERGE_CONSTRAINT_H_ */