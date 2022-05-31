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

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_SPLIT_ANALYZER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_SPLIT_ANALYZER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator/scene_analyzer/scene_analyzer.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator/region_model/region_model_info.h>
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
class SplitAnalyzer : public SceneAnalyzer
{
public:
    SplitAnalyzer() = default;
    ~SplitAnalyzer() = default;
    SplitAnalyzer(SplitAnalyzer const&) = delete;
    SplitAnalyzer& operator=(SplitAnalyzer const&) = delete;
    SplitAnalyzer(SplitAnalyzer &&) = delete;
    SplitAnalyzer& operator=(SplitAnalyzer &&) = delete;

    virtual holo::bool_t Analyze(LanePathSPtrType path, std::vector<TargetRegion>& target_regions);
    virtual holo::bool_t Calculate(Input const& input, Output& output);
};


}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_SCENE_ANALYZER_H_ */