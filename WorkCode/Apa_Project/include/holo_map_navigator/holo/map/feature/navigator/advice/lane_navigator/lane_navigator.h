
/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_navigator.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-04-27
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_LANE_NAVIGATOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_LANE_NAVIGATOR_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/common/match_info.h>

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator/scene_analyzer/scene_analyzer_controller.h>
#include <holo/map/feature/navigator/navigator_config.h>
#include <holo/map/feature/navigator/router/route_info.h>
#include <holo/map/feature/navigator/advice/lane_navigator/region_model/region_model_generator.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/state_region_info/state_region_extractor.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/lane_path_manager.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
/**
 * @brief A Navigaor for calculating the lane level route
 *
 */
class LaneNavigator
{
public:
    using Ptr = std::shared_ptr<LaneNavigator>;
    using LanePathSPtrType = std::shared_ptr<LanePath>;
    using LanePathSPtrVecType = std::vector<LanePathSPtrType>;
    using LaneItemSPtrType    = std::shared_ptr<LaneItem>;
    using LaneItemSPtrVecType = std::vector<LaneItemSPtrType>;
    using TargetRegion               = holo::map::navigator::advice::TargetRegion;
    using RegionModelInfoSPtrType    = std::shared_ptr<RegionModelInfo>;
    using RegionModelInfoSPtrVecType = std::vector<RegionModelInfoSPtrType>;
    using SceneSketchSPtrType        = std::shared_ptr<scene::SceneSketch>;
    using SceneSketchSPtrVecType     = std::vector<SceneSketchSPtrType>;

    using MapMatchingInfoType = holo::map::MapMatchInfo;
public:
    /**
     * @brief Lane navigator input information.
     */
    struct Input
    {
        /// Route infomation calculated from router
        RouteInfo2::Ptr         route_info = nullptr;
        /// Match information calculated from Local Map Server 
        holo::map::MapMatchInfo matching_info;
        /// Scene sketch
        std::vector<SceneSketch> scene_sketchs;
        /// Scene sketch v2
        SceneSketchSPtrVecType scene_sketchs_v2;
    };

    /**
     * @brief Lane navigator output information.
     */
    struct Output
    {
        /// Several new lane path
        std::vector<LanePathSPtrType> paths;
    };

    struct VisualObjectId
    {
        VisualObjectId(holo::uint64_t const& en, holo::uint64_t const& ex)
        {
            this->entry_id = en;
            this->exit_id  = ex;
        }
        holo::uint64_t entry_id = 0U;
        holo::uint64_t exit_id = 0U;
        holo::bool_t operator < (const VisualObjectId &other) const
	    {
            return this->entry_id < other.entry_id ||
                   (this->entry_id == other.entry_id && this->exit_id < other.exit_id);
        }
        holo::bool_t operator == (const VisualObjectId &other) const
	    {
            return this->entry_id == other.entry_id && this->exit_id == other.exit_id;
        }
    };

public:
    /**
     * @brief Judge whther or not the lane is forward
     *
     * @param curr
     * @param next
     * @return holo::bool_t
     */
    static holo::bool_t GetForwardLaneItem(RetrieverSPType ret, std::vector<LanePathSPtrType> const& paths,
                                           LaneItemSPtrType current, LaneItemSPtrType forward);

    LaneNavigator();
    ~LaneNavigator();

    /**
     * @brief Initialize
     *
     * @param config Configuration which has read the yaml file
     * @param retriever A retriever for data engine
     * @return true: Success; false: otherwise
     */
    holo::bool_t Init( RetrieverSPType retriever);
    
    /**
     * @brief Assign verbose flag.
     *
     * @param[in] v: True: print detail debug logs.
     *            False: close detail debug logs(default value).
     */
    void SetVerbose(holo::bool_t const v);

    /**
     * @brief Calculate the all lane level routes
     *
     * @param input Road level route
     * @param output Map matching result which would provide the basic infomation such
     *                      as lane id, distance to the end of current link
     */
    holo::bool_t Run(LaneNavigator::Input const& input, LaneNavigator::Output& output);

    /**
     * @brief Calculate the all lane level routes
     *
     * @param input Road level route
     * @param output Map matching result which would provide the basic infomation such
     *                      as lane id, distance to the end of current link
     */
    holo::bool_t Run2(LaneNavigator::Input const& input, LaneNavigator::Output& output);

private:
    /**
     * @brief Run calculation of Lane Naviagtor
     *
     * @param route_info Route Info
     * @param matching_info Match info
     * @return holo::bool_t
     */
    holo::bool_t runLaneNavigator(RouteInfo2::Ptr route_info, std::vector<SceneSketch>const& scene_sketch, holo::map::MapMatchInfo const& matching_info);

    /**
     * @brief Run calculation of Lane Naviagtor
     *
     * @param route_info Route Info
     * @param matching_info Match info
     * @return holo::bool_t
     */
    holo::bool_t runLaneNavigator2(RouteInfo2::Ptr route_info, SceneSketchSPtrVecType const& scene_sketch,
                                   holo::map::MapMatchInfo const& matching_info);

    /**
     * @brief Check region on lane path
     *
     * @param lane_path LanePath to be matched
     * @param region Region to match
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t checkLanePathMatchRegion(LanePathSPtrType lane_path, TargetRegion const& origin, holo::bool_t& matched);

    /**
     * @brief Set visual items id
     */ 
    holo::bool_t assignLanePathsVisualIds();

    /**
     * @brief Assign lane path visual id
     * 
     * @param path 
     * @return holo::bool_t 
     */
    holo::bool_t assignLanePathVisualId(LanePathSPtrType path);

    holo::bool_t runStateRegionExtractor(holo::map::MapMatchInfo const& info,
        LanePathSPtrVecType& lane_paths);

private:
    /// verbose
    holo::bool_t                           verbose_          = false;
    navigator::config::NavigatorConfigSPtr navigator_config_ = nullptr;
    /// A retriever for data engine
    RetrieverSPType retriever_ = nullptr;

    using StateRegionExtractorType = holo::map::navigator::advice::StateRegionExtractor;
    using StateRegionExtractorUPtrType = std::unique_ptr<StateRegionExtractorType>;

    StateRegionExtractorUPtrType state_region_extractor_ = nullptr;
    /// Last lane queues for track history of lane queues, whcih would gurantee that
    /// the id of two same lane-routes is identical
    std::vector<LanePathSPtrType> last_lane_paths_;

private:
    class LanePathGenerator;
    std::unique_ptr<LanePathGenerator> lane_path_generator_;
    std::unique_ptr<lanepath::LanePathManager> lane_path_manager_         = nullptr;
    std::unique_ptr<SceneAnalyzerController>   scene_analyzer_controller_ = nullptr;
    std::unique_ptr<RegionModelGenerator>    region_model_generator_    = nullptr;
    std::map<VisualObjectId, holo::uint64_t> entry_exit_id_table_;
    holo::uint64_t                           max_visual_id_ = 0U;
};
}
}
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_LANE_NAVIGATOR_H_ */