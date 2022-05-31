/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file region_model_generator.h
 * @brief Generate region model info for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-12-23
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_REGION_MODEL_GENERATOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_REGION_MODEL_GENERATOR_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/common/match_info.h>

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator/scene_analyzer/scene_analyzer_controller.h>
#include <holo/map/feature/navigator/navigator_config.h>
#include <holo/map/feature/navigator/router/route_info.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
/**
 * @brief The generator for region model info
 *
 */
class RegionModelGenerator
{
public:
    using LanePathSPtrType           = std::shared_ptr<LanePath>;
    using LanePathSPtrVecType        = std::vector<LanePathSPtrType>;
    using LaneItemSPtrType           = std::shared_ptr<LaneItem>;
    using LaneItemSPtrVecType        = std::vector<LaneItemSPtrType>;
    using TargetRegion               = holo::map::navigator::advice::TargetRegion;
    using RegionModelInfoSPtrType    = std::shared_ptr<RegionModelInfo>;
    using RegionModelInfoSPtrVecType = std::vector<RegionModelInfoSPtrType>;
    using SceneSketchType            = holo::map::navigator::advice::SceneSketch;

public:
    /**
     * @brief Lane navigator input information.
     */
    struct Input
    {
        /// Some LanePaths  to be calcualted region model info
        LanePathSPtrVecType all_paths;
        /// Scene sketch for calculating region model info
        SceneSketchType scene_sketch;
    };

    /**
     * @brief Lane navigator output information.
     */
    struct Output
    {
        /// The lane paths has been calcuated region model info
        LanePathSPtrVecType paths;
    };

public:
    holo::bool_t Run(Input const& input, Output& output);

private:
    /**
     * @brief Make or create region model info
     * 
     * @param prepared_paths 
     * @param target_path 
     * @param target_region 
     * @param matched 
     * @return holo::bool_t 
     */
    holo::bool_t makeOrCreateRegionModelInfo(LanePathSPtrVecType& prepared_paths, LanePathSPtrType target_path,
                                TargetRegion const& target_region, holo::bool_t& matched);

    holo::bool_t checkLanePathMatchRegion(LanePathSPtrType lane_path, TargetRegion const& region, holo::bool_t& matched);

    holo::bool_t matchOrCreateRegionModelInfo(LanePathSPtrType target_path, TargetRegion const& target_region,
                                              LanePathSPtrType origin_path, holo::bool_t& matched);
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_REGION_MODEL_GENERATOR_H_ */