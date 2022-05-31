/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file down_ramp_region_slider.h
 * @brief A sliding block for lane path to generate region model info
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-03-31
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_DOWN_RAMP_REGION_SLIDER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_DOWN_RAMP_REGION_SLIDER_H_

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
class DownRampRegionSlider : public RegionSliderBase
{
public:
    using DownRampSlidingStatus = SlidingStatus;

    DownRampRegionSlider()                      = default;
    DownRampRegionSlider(DownRampRegionSlider const&) = default;
    DownRampRegionSlider(DownRampRegionSlider&&)      = default;
    DownRampRegionSlider& operator=(DownRampRegionSlider const&) = default;
    DownRampRegionSlider& operator=(DownRampRegionSlider&&) = default;

    DownRampRegionSlider(holo::float64_t const down_ramp_search_distance, holo::float64_t const rate);

    holo::bool_t Active() override;

    holo::bool_t ResultValid() override;

    holo::bool_t Assemble() override;

protected:
    holo::bool_t doNextCheckNeedSliding() override;

    holo::bool_t doNextLoading() override;

    void doNextReset() override;

private:
    holo::bool_t assemblePathNotEnough();
    holo::bool_t assembleBoundaryNotMatched();
    holo::bool_t assembleRegionOutMaxLength();

private:
    holo::float64_t const down_ramp_search_distance_ = 0.0f;
    ///
    holo::float64_t const rate_risk_to_ultimate_ = 0.0f;
    ///
    holo::float64_t const CHANGE_LANE_REGION_MAX_LENGTH_ = 200.0f;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_MERGE_REGION_SLIDER_H_ */