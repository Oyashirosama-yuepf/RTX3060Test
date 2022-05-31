/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file toll_area_analzyer.h
 * @brief Toll area scene analzyer
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-02-23
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_TOLL_AREA_ANALYZER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_TOLL_AREA_ANALYZER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_analysis/scene_analyzer_base.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
namespace scene
{
/**
 * @brief Scene analyzer for toll area
 */
class TollAreaAnalyzer : public SceneAnalyzerBase
{
public:
    TollAreaAnalyzer();
    virtual ~TollAreaAnalyzer()                       = default;
    TollAreaAnalyzer(TollAreaAnalyzer const&)         = delete;
    TollAreaAnalyzer(TollAreaAnalyzer&&)              = delete;
    TollAreaAnalyzer     operator=(TollAreaAnalyzer const&) = delete;
    TollAreaAnalyzer     operator=(TollAreaAnalyzer&&) = delete;

    /**
     * @brief Analyze for road level scene
     *
     * @param input Input of scene analyzer
     * @param output Output of scnen anlyzer
     * @return holo::bool_t
     */
    virtual holo::bool_t Calculate(Input const& input, Output& output) override;

};
}  // namespace scene
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_TOLL_AREA_ANALYZER_H_ */