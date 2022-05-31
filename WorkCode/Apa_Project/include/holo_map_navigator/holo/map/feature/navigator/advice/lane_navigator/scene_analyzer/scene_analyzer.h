/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file scene_analyzer.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-04-27
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_SCENE_ANALYZER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_SCENE_ANALYZER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator/region_model/region_model_info.h>
#include <holo/map/feature/navigator/advice/lane_navigator/target_region.h>
#include <holo/map/format/base/lane.h>
#include <holo/map/feature/navigator/router/route_info.h>
#include <holo/map/feature/navigator/advice/lane_navigator/entity.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
/**
 * @brief Scene analyzer for lane path.
 * 
 * @details The lane path would go by sereral scenes including
 *          down ramp, going up main road, spliting on ramp
 */
class SceneAnalyzer
{
public:
    using Ptr = std::shared_ptr<SceneAnalyzer>;
    using LanePathSPtrType = std::shared_ptr<LanePath>;
    using RouteInfoType    = holo::map::RouteInfo2;
    using RouteInfoSPtrType = std::shared_ptr<RouteInfoType>;
    using TargetRegionType  = TargetRegion;
    using SceneCategory     = holo::map::navigator::advice::TargetRegion::SceneType;

    struct Input
    {
        std::vector<holo::uint64_t> route_link_ids;
        holo::float64_t             current_distance_to_end = 0.0f;
        holo::bool_t                has_complete_link_ids   = false;
    };
    struct Output
    {
        SceneSketch  scene_sketch;
        holo::bool_t has_scene = false;
    };

public:
    SceneAnalyzer()          = default;
    virtual ~SceneAnalyzer() = default;
    /**
     * @brief Initialize the scene analyzer
     *
     * @param ret
     * @return holo::bool_t
     */
    holo::bool_t Init(RetrieverSPType ret)
    {
        (void)ret;
        return true;
    }

    /**
     * @brief Analyze Scene of lane path
     *
     * @param path
     * @param target_regions
     * @return holo::bool_t
     */
    virtual holo::bool_t Analyze(LanePathSPtrType path, std::vector<TargetRegion>& target_regions) = 0;

    /**
     * @brief Analyze for road level scene
     * 
     * @param input Input of scene analyzer
     * @param output Output of scnen anlyzer
     * @return holo::bool_t 
     */
    virtual holo::bool_t Calculate(Input const& input, Output& output) = 0;

    /**
     * @brief Set the Max Search Distance 
     * 
     * @param dist 
     */
    void SetMaxSearchDistance(holo::float64_t const dist)
    {
        this->max_search_distance_ = dist;
    }

protected:
    /// Max search distance
    holo::float64_t max_search_distance_ = 1200;
};

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_SCENE_ANALYZER_H_ */