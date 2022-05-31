/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file region_model_manager.h
 * @brief A seed to calculate region model info
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-04-02
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_MODEL_MANAGER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_MODEL_MANAGER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator/region_model/region_model_info.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/region_model_info/region_model_extractor.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class RegionModelManager
{
public:
    using LanePathSPtrType       = std::shared_ptr<holo::map::navigator::advice::LanePath>;
    using LanePathSPtrVecType    = std::vector<LanePathSPtrType>;
    using SceneSketchType        = holo::map::navigator::advice::scene::SceneSketch;
    using SceneSketchSPtrType    = std::shared_ptr<SceneSketchType>;
    using SceneSketchSPtrVecType = std::vector<SceneSketchSPtrType>;

    RegionModelManager()                              = default;
    RegionModelManager(RegionModelManager const&)     = default;
    RegionModelManager(RegionModelManager&&)          = default;
    RegionModelManager&   operator=(RegionModelManager const&) = default;
    RegionModelManager&   operator=(RegionModelManager&&) = default;

    struct Input
    {
        LanePathSPtrVecType lane_paths;
        SceneSketchSPtrVecType scene_sketchs;
    };

    struct Output
    {
        // Nothing to define
    };

    holo::bool_t Run(Input const& input, Output& output);

    holo::bool_t Init();

private:
    /**
     * @brief Caclculate region model slider
     *
     * @param source
     * @param target
     * @return holo::bool_t
     */
    holo::bool_t doMakeRegionModels(LanePathSPtrVecType const& lane_paths, SceneSketchSPtrVecType const& scenes);

private:
    ///
    holo::float64_t max_region_distance_ = 2000.0f;
    ///
    RegionModelExtractor region_model_extractor_;
    ///

};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_MODEL_SEED_H_ */