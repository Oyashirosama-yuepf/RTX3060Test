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

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_SCENE_ANALYZER_CONTROLLER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_SCENE_ANALYZER_CONTROLLER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator/region_model/region_model_info.h>
#include <holo/map/feature/navigator/advice/lane_navigator/target_region.h>
#include <holo/map/format/base/lane.h>
#include <holo/map/feature/navigator/advice/lane_navigator/scene_analyzer/scene_analyzer.h>
#include <holo/map/feature/navigator/advice/lane_navigator/entity.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
/**
 * @brief Scene analyzer for lane path.
 *
 * @details The lane path would go by sereral scenes including
 *          down ramp, going up main road, spliting on ramp
 */
class SceneAnalyzerController
{
public:
    using SceneSketch = holo::map::navigator::advice::SceneSketch;

   struct Input
    {
        std::vector<holo::uint64_t> route_link_ids;
        holo::float64_t current_distance_to_end = 0.0f;
    };
    struct Output
    {
        std::vector<SceneSketch> scene_sketchs;
        holo::bool_t has_scene = false;
        holo::bool_t             error_exitsed = false;
    };

public:
    SceneAnalyzerController();
    ~SceneAnalyzerController() = default;

    /**
     * @brief Analyze sc            ene and target region from lane path
     *
     * @param path Lane path
     * @param target_regions Target regions calculated from lane path
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t Analyze(SceneAnalyzer::LanePathSPtrType path, std::vector<TargetRegion>& target_regions);

    /**
     * @brief 
     * 
     * @param input 
     * @param output 
     * @return holo::bool_t 
     */
    holo::bool_t Analyze(Input const& input, Output& output);

    /**
     * @brief 
     * 
     * @param input 
     * @param output 
     * @return holo::bool_t 
     */
    holo::bool_t Calculate(Input const& input, Output& output);
    
    /**
     * @brief Initialze controller
     *
     * @param ret Retriever for data engine
     * @return holo::bool_t True, success; false, otherwise
     */
    holo::bool_t Init(RetrieverSPType ret);

private:
    /// All scene analzyers
    std::vector<SceneAnalyzer::Ptr> scene_analyzers_;
    /// All scene analyzers
    std::vector<SceneAnalyzer::Ptr> all_scene_analzyers_;
};

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_ANALYZER_SCENE_ANALYZER_H_ */