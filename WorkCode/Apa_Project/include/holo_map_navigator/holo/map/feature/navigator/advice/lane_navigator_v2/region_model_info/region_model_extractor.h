/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file region_model_seed.h
 * @brief A seed to calculate region model info
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-02-31
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_MODEL_EXTRACTOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_MODEL_EXTRACTOR_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator/region_model/region_model_info.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/region_model_info/region_slider/region_slider.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class RegionSlider;
class RegionModelExtractor
{
public:
    using LanePathSPtrType = std::shared_ptr<holo::map::navigator::advice::LanePath>;
    using LanePathSPtrVecType = std::vector<LanePathSPtrType>;

    using LaneChangeRegionType        = holo::map::navigator::advice::LaneChangeRegion;
    using LaneChangeRegionSPtrType    = std::shared_ptr<LaneChangeRegionType>;
    using LaneChangeRegionSPtrVecType = std::vector<LaneChangeRegionSPtrType>;
    using RegionSliderSPtrType        = std::shared_ptr<RegionSliderBase>;

    struct RegionModelSeed
    {
        /// Beginning lane id of target lane path; 
        /// target lane path is the lane which is changed to
        IdType              origin_lane_id     = 0U;
        /// Offset of beginning lane of target lane path
        holo::float64_t     origin_lane_offset = 0.0f;
        /// Target lane path that is changed to 
        LanePathSPtrType    origin             = nullptr;
        /// Candidates of lane paths which car is changing from
        LanePathSPtrVecType candidates;
        /// If true, there exists at least one lane path for changing
        /// from; false, there is no matched lane path
        bool_t matched = false;

        static std::string FormatToString(RegionModelSeed const& seed);
    };

    RegionModelExtractor()                       = default;
    RegionModelExtractor(RegionModelExtractor const&) = default;
    RegionModelExtractor(RegionModelExtractor&&)      = default;
    RegionModelExtractor& operator=(RegionModelExtractor const&) = default;
    RegionModelExtractor& operator=(RegionModelExtractor&&) = default;

    holo::bool_t Init();

    holo::bool_t Run(RegionModelSeed& seed);

private:
    holo::bool_t executeRegionSlider(LanePathSPtrType origin, LanePathSPtrType target);

private:
    /// Different region sliders to generate region model info
    std::vector<RegionSliderSPtrType> region_sliders_;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_MODEL_EXTRACTOR_H_ */