/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file merge_region_slider.h
 * @brief A sliding block for lane path to generate region model info
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-03-31
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_ROAD_MERGE_REGION_SLIDER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_ROAD_MERGE_REGION_SLIDER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/region_model_info/region_slider/region_slider.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class RoadMergeRegionSlider : public RegionSliderBase
{
public:
    RoadMergeRegionSlider(holo::float64_t const search_distance, holo::float64_t const rate);
    RoadMergeRegionSlider(RoadMergeRegionSlider const&) = default;
    RoadMergeRegionSlider(RoadMergeRegionSlider&&)      = default;
    RoadMergeRegionSlider& operator=(RoadMergeRegionSlider const&) = default;
    RoadMergeRegionSlider& operator=(RoadMergeRegionSlider&&) = default;

    holo::bool_t Slide() override;

    holo::bool_t Active() override;

    holo::bool_t ResultValid() override;

    holo::bool_t Assemble() override;
protected:
    holo::bool_t doNextCheckNeedSliding() override;
    holo::bool_t doNextLoading() override;
    void         doNextReset() override;

private:
    holo::bool_t setRegionModel(std::shared_ptr<LaneChangeRegion> info);

private:
    /// Max search distance for merging
    holo::float64_t const merge_search_distance_ = 0U;
    /// Rate of (risk point to ultimate) / (ready point to ultimate)
    holo::float64_t const rate_risk_to_ultimate_ = 0.0f;
    ///
    holo::float64_t const CHANGE_LANE_REGION_MAX_LENGTH_ = 200;
    ///
    holo::float64_t distance_ready_to_base_line_ = 0.0f;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_ROAD_MERGE_REGION_SLIDER_H_ */