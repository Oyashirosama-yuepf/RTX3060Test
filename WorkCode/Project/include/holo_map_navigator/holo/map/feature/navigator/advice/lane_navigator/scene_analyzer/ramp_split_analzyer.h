/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ramp_split_analyzer.h
 * @brief Analyzer for ramp road spliting
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-11-27
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_RAMP_SPLIT_ANALYZER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_RAMP_SPLIT_ANALYZER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator/region_model/region_model_info.h>
#include <holo/map/feature/navigator/advice/lane_navigator/scene_analyzer/scene_analyzer.h>
#include <holo/map/feature/navigator/advice/lane_navigator/scene_analyzer/split_analyzer.h>
#include <holo/map/feature/navigator/advice/lane_navigator/target_region.h>
#include <holo/map/format/base/lane.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
/**
 * @brief Road split Analyzer.
 *
 * @details The lane path would go by sereral scenes including
 *          down ramp, going up main road, spliting on ramp
 */
class RampSplitAnalyzer : public SplitAnalyzer
{
public:
    RampSplitAnalyzer()                 = default;
    ~RampSplitAnalyzer()                = default;
    RampSplitAnalyzer(RampSplitAnalyzer const&) = delete;
    RampSplitAnalyzer& operator=(RampSplitAnalyzer const&) = delete;
    RampSplitAnalyzer(RampSplitAnalyzer&&)                 = delete;
    RampSplitAnalyzer& operator=(RampSplitAnalyzer&&) = delete;

    virtual holo::bool_t Calculate(Input const& input, Output& output);
};

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_RAMP_SPLIT_ANALYZER_H_ */