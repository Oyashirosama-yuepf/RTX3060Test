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

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_UP_MAIN_ANALYZER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_UP_MAIN_ANALYZER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator/entity.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator/region_model/region_model_info.h>
#include <holo/map/feature/navigator/advice/lane_navigator/target_region.h>
#include <holo/map/feature/navigator/router/route_info.h>
#include <holo/map/format/base/lane.h>
#include <holo/map/feature/navigator/advice/lane_navigator/scene_analyzer/merge_analyzer.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
/**
 * @brief Up to main road scene analyzer
 *
 */
class UpMainRoadAnalyzer : public MergeAnalyzer
{
public:
    /**
     * @brief Analyzing for up main road
     *
     * @param path Lane path
     * @param target_regions Target regions calculated from lane path
     * @return holo::bool_t
     */
    holo::bool_t Analyze(LanePathSPtrType path, std::vector<TargetRegion>& target_regions);

    holo::bool_t Calculate(Input const& input, Output& output)
    {
        (void)input;
        (void)output;
        return true;
    }
};

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_SCENE_ANALYZER_H_ */