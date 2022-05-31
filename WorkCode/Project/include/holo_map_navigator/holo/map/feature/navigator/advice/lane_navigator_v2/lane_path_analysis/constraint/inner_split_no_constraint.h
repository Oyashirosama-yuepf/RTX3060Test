/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file inner_split_constraint.h
 * @brief Generate lane path for lane-level navigation
 * @author chanqiliang (chanqiliang@holomatic.com)
 * @date 2022-04-07
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_INNER_SPLIT_NO_CONSTRAINT_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_INNER_SPLIT_NO_CONSTRAINT_H_

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
class InnerSplitNoConstraint : public ConstraintBase
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

    DistanceTypeV0 GetActivateDistance() const;
    void           SetActivateDistance(DistanceTypeV0 dist);

private:
    holo::bool_t match(LaneItemSPtrType const& lane_item_to_match, holo::bool_t& in_scope);
    holo::bool_t isGoToTargetRoadSplitSceneThroughSpecialLanes(LaneItemSPtrType const& lane_item_to_match,
                                                               holo::bool_t&           is_pass,
                                                               holo::bool_t&           is_through_speial_lanes);
    holo::bool_t isCurrentLaneToTargetLink(::std::vector<RawFeatureIdTypeV0> const& current_lane_ids,
                                           RawFeatureIdTypeV0 const                 target_link_id,
                                           holo::map::VecLaneIdType const&          key_lanes,
                                           ::std::vector<RawFeatureIdTypeV0>&       target_lane_ids,
                                           holo::bool_t&                            is_through_speial_lanes);

private:
    DistanceTypeV0 MAX_DISTANCE_BETWEEN_CAR_AND_ROAD_SPLIT_SCENE = 500;
};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_INNER_SPLIT_NO_CONSTRAINT_H_