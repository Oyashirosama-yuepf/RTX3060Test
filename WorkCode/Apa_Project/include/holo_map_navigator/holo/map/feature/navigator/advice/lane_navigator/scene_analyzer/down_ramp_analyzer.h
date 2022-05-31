/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file down_ramp_analyzer.h
 * @brief Scene analyzer for drive dwon to ramp road
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-11-27
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_DOWN_RAMP_ANALYZER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_DOWN_RAMP_ANALYZER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator/entity.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator/region_model/region_model_info.h>
#include <holo/map/feature/navigator/advice/lane_navigator/target_region.h>
#include <holo/map/feature/navigator/router/route_info.h>
#include <holo/map/format/base/lane.h>
#include <holo/map/feature/navigator/advice/lane_navigator/scene_analyzer/split_analyzer.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
/**
 * @brief Down ramp scene analyzer
 *
 */
class DownRampAnalyzer : public SplitAnalyzer
{
public:
    /**
     * @brief Scene anaylizer for down ramp
     *
     * @param path
     * @param target_regions
     * @return holo::bool_t
     */
    holo::bool_t Analyze(LanePathSPtrType path, std::vector<TargetRegion>& target_regions);

    holo::bool_t Calculate(Input const& input, Output& output);

private:
    /**
     * @brief
     *
     * @param path
     * @param target_regions
     * @return holo::bool_t
     */
    holo::bool_t analyzeDirectDownRamp(LanePathSPtrType path, std::size_t const splited_idx,
                                       std::size_t const shift_idx, std::vector<TargetRegion>& target_regions);

    /**
     * @brief
     *
     * @param path
     * @return holo::bool_t
     */
    holo::bool_t checkDirectDownRamp(LanePathSPtrType path, holo::bool_t& has_scene, std::size_t& splited_idx,
                                     std::size_t& shift_idx);

    /**
     * @brief
     *
     * @param path
     * @param target_regions
     * @return holo::bool_t
     */
    holo::bool_t analyzeCorrespondDownRamp(LanePathSPtrType path, std::size_t const shift_idx,
                                           std::vector<TargetRegion>& target_regions);
};

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_DOWN_RAMP_ANALYZER_H_ */