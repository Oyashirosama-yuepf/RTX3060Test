/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file inner_scene_analyzer_base.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-3-7
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_INNER_SCENE_ANALYZER_BASE_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_INNER_SCENE_ANALYZER_BASE_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_analysis/scene_analyzer_base.h>
#include <holo/map/feature/navigator/router/route_info.h>
#include <holo/map/format/base/lane.h>

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
 * @brief Scene analyzer for route links
 *
 * @details The lane path would go by sereral scenes including
 *          down ramp, going up main road, spliting on ramp
 */
class InnerSceneAnalyzerBase : public SceneAnalyzerBase
{
public:
    InnerSceneAnalyzerBase();
    virtual ~InnerSceneAnalyzerBase()                     = default;
    InnerSceneAnalyzerBase(InnerSceneAnalyzerBase const&) = delete;
    InnerSceneAnalyzerBase(InnerSceneAnalyzerBase&&)      = delete;
    InnerSceneAnalyzerBase& operator=(InnerSceneAnalyzerBase const&) = delete;
    InnerSceneAnalyzerBase& operator=(InnerSceneAnalyzerBase&&) = delete;

    /**
     * @brief Analyze for road level scene
     *
     * @param input Input of scene analyzer
     * @param output Output of scnen anlyzer
     * @return holo::bool_t
     */
    virtual holo::bool_t Calculate(Input const& input, Output& output) override;

protected:
    /**
     * @brief make scene sketch using two links
     *
     * @param input lane instance
     * 
     * @return if true, input lane is breakup lane
     */
    virtual holo::bool_t makeSceneSketch(LaneGroupSPtrType entry_link, LaneGroupSPtrType exit_link, holo::bool_t& has_scene, SceneSketchSPtrType& scene) = 0;

protected:
    /**
     * @brief inner merge lane, left_boundary and right_boundary have same succeeding boundary 
     *
     * @param input lane instance
     * @return if true, input lane is inner merge lane
     */
    holo::bool_t isEndingLane(LaneSPtrType lane);
    /**
     * @brief inner split lane, left_boundary or right_boundary have >=2 succeeding boundary 
     *
     * @param input lane instance
     * @return if true, input lane is inner split lane
     */
    holo::bool_t isOpeningLane(LaneSPtrType lane);
    /**
     * @brief inner breakup lane, none succeeding lanes
     *
     * @param input lane instance
     * @return if true, input lane is breakup lane
     */
    holo::bool_t isBreakUpLane(LaneSPtrType lane);
    /**
     * @brief If find precedding lane in link
     *
     * @param input lane instance
     * @return if true, restricted
     */
    holo::bool_t isSuceedingLane(LaneGroupSPtrType entry_link, LaneSPtrType suc_lane);

    holo::bool_t isPrecedingLane(LaneGroupSPtrType exit_link, LaneSPtrType pre_lane);

};
}  // namespace scene
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_INNER_SCENE_ANALYZER_BASE_H_ */
