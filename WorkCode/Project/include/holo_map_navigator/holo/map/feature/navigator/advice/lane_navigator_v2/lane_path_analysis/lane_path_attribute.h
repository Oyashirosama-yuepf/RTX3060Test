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

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_ATTRIBUTE_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_ATTRIBUTE_H_

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/map_types.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/lane_path_grading/grading_base.h>

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

class LanePathAttribute
{
public:
    using LanePathSPtrType       = std::shared_ptr<LanePath>;
    using LanePathSPtrVecType    = std::vector<LanePathSPtrType>;
    using LaneItemSPtrType       = std::shared_ptr<LaneItem>;
    using LaneItemSPtrVecType    = std::vector<LaneItemSPtrType>;

    using RouteSceneType         = scene::RouteScene;
    using RouteSceneSPtrType     = std::shared_ptr<RouteSceneType>;

    using GradingBaseSPtrType = std::shared_ptr<GradingBase>;

public:
    LanePathAttribute() = default;
    ~LanePathAttribute() = default;

public:
    /**
     * @brief Initialize using route scene
     *
     * @param route_scene all scene on route before car
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t Initialize(RouteSceneSPtrType route_scene);
    /**
     * @brief Update all lane path attribute, include level, candidate lane id, etc. 
     *
     * @param all_lane_paths all lane paths need update attribute
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t SetGrading(LanePathSPtrVecType& all_lane_paths);

private:
    /// lane path grading builder
    GradingBaseSPtrType grading_ = nullptr;
    /// debug log
    holo::bool_t verbose_ = true;

};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_ATTRIBUTE_H_ */