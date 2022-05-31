/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file region_slider.h
 * @brief A sliding block for lane path to generate region model info
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-03-31
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_MAIN_ROAD_REGION_SLIDER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_MAIN_ROAD_REGION_SLIDER_H_

#include <vector>

#include <holo/map/feature/navigator/advice/lane_navigator_v2/region_model_info/region_slider/region_slider.h>
#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class MainRoadRegionSlider : public RegionSliderBase
{
public:
    MainRoadRegionSlider()                            = delete;
    MainRoadRegionSlider(MainRoadRegionSlider const&) = default;
    MainRoadRegionSlider(MainRoadRegionSlider&&)      = default;
    MainRoadRegionSlider& operator=(MainRoadRegionSlider const&) = default;
    MainRoadRegionSlider& operator=(MainRoadRegionSlider&&) = default;

    MainRoadRegionSlider(holo::float64_t risk_point_to_baseline, holo::float64_t offset_ready_to_risk);

    holo::bool_t Active() override;

    holo::bool_t ResultValid() override;

    holo::bool_t Assemble() override;

protected:
    holo::bool_t doNextCheckNeedSliding() override;

    holo::bool_t doNextLoading() override;

    void doNextReset() override;

private:
    holo::bool_t assembleCompleted();

    holo::bool_t assemblePathNotEnough();

    holo::bool_t assembleBoundaryNotMatched();

private:
    /// Distance risk point to baseline, Unit: meters
    holo::float64_t const unit_distance_risk_to_baseline_;
    /// offset ready point to risk point, Unit: meters
    holo::float64_t const offset_ready_to_risk_;
    ///
    holo::float64_t distance_ready_to_base_line_ = 0.0f;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_MAIN_ROAD_REGION_SLIDER_H_ */