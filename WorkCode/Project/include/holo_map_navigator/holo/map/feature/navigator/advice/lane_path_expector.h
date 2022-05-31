/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_path_expector.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-11-27
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_PATH_EXPECTOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_PATH_EXPECTOR_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/common/match_info.h>

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
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
 * @brief Expected lane paths calculation 
 *
 * @note We evaluate expected lane paths from Two big aspects.
 *       First, the length of lane path on route (especially on RouteInfo)
 *       is very important, whitch of great probablity decides where to go.
 *       Secode, the trouble defined as scene such as spliting, merging, 
 *       is so unpleasant that we would avoid the lane paths with many 
 *       troubles. 
 */
class LanePathExpector
{
public:
    using LanePathSPtrType = std::shared_ptr<LanePath>;
    using SceneSketch      = holo::map::navigator::advice::SceneSketch;

    struct Input
    {
        std::vector<LanePathSPtrType> lane_paths;
        std::vector<SceneSketch>      scene_sketchs;
    };

    struct Output
    {
        std::vector<holo::uint64_t> expected_lane_path_ids;
    };

    /**
     * @brief Score for chosing different la   ne paths
     *
     * @note We evaluate lane paths from Two big aspects.
     *       First, the length on route, the longer it is,
     *       the score would be higher;
     *       Second, many troubles cause less scores.
     *
     */
    class LanePathBehavior
    {
    public:
        
        static std::string FormatToString(LanePathBehavior const& behavior);

        static std::string FormatToString(std::vector<LanePathBehavior> const& behaviors);

    public:
        ///  Whether or not is same sequence
        holo::bool_t is_same_sequence = false;
        /// Length on route
        holo::float64_t on_route_length = 0.0f;
        /// Troubles for changing lane
        std::vector<holo::float64_t> troubles;
        /// Score for troubles
        holo::float64_t score_troubles = 0.0f;
        /// Score for same sequence
        holo::float64_t score_same_sequence = 0.0f;
        /// Score for length on route
        holo::float64_t score_on_route_length = 0.0f;
        /// Score for sum of all scores
        holo::float64_t score_total = 0.0f;
        /// Indentical to reprented lane path id
        holo::uint64_t     lane_path_id = 0;
        /// Score for visual item
        holo::float64_t score_visual_length = 0.0f;
        /// Score for scene
        holo::float64_t score_scene = 0.0f;
        /// Lane path
        LanePathSPtrType lane_path = nullptr;
    };

    /**
     * @brief Calcualte expected lane paths
     *
     * @param input The lane paths need to be evaludted
     * @param output The expected ids of lane paths
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t Calculate(LanePathExpector::Input const& input, LanePathExpector::Output& output);

private:
    /// The min distance for expected lane path, the lane path
    /// that length on route less than min length, woule be 
    /// not recommanded
    holo::float64_t expected_min_length_ = 600.0f;
    /// The max diantce for expected lane path, the lane path
    /// with length on route more than expected max length
    /// would be evaluated as full score 100
    holo::float64_t expected_max_length_ = 1200.0f;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_PATH_EXPECTOR_H_ */