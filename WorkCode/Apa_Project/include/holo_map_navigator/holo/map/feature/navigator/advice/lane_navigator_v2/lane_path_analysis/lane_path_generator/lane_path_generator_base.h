/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_path_combination_base.h
 * @brief Generate lane path for lane-level navigation base on given generator,constraint and terminator
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-7
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_GENERATOR_BASE_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_GENERATOR_BASE_H_

#include <queue>

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/constraint/constraint_manager.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/lane_item_generator/lane_item_generator_manager.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>
#include <holo/map/feature/navigator/router/route_info.h>

#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/terminator/terminator_manager.h>
#include <queue>

#include <holo/map/feature/navigator/advice/lane_navigator/scene_analyzer/scene_analyzer_controller.h>
#include <holo/map/common/match_info.h>
#include <holo/map/feature/navigator/router/route_info.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
namespace lanepath
{

class LanePathGeneratorBase
{
public:
    using LanePathSPtrType             = std::shared_ptr<LanePath>;
    using LanePathSPtrVecType          = std::vector<LanePathSPtrType>;
    using LaneItemSPtrType             = std::shared_ptr<LaneItem>;
    using LaneItemSPtrVecType          = std::vector<LaneItemSPtrType>;
    using GeneratorSPtrType            = std::shared_ptr<holo::map::navigator::advice::lanepath::LaneItemGeneratorBase>;
    using SceneSketchType              = holo::map::navigator::advice::scene::SceneSketch;
    using SceneCategoryType      = SceneSketchType::SceneCategory;
    using CompositeSceneSketchType     = holo::map::navigator::advice::scene::CompositeSceneSketch;
    using SceneSketchSPtrType          = std::shared_ptr<SceneSketchType>;
    using CompositeSceneSketchSPtrType = std::shared_ptr<CompositeSceneSketchType>;
    using SceneSketchSPtrVecType       = std::vector<SceneSketchSPtrType>;
    using GeneratorModeType            = LaneItemGeneratorBase::GeneratorMode;
    using MapMatchingInfoType             = holo::map::MapMatchInfo;

public:
    struct Input
    {
        /// Route infomation calculated from router
        RouteInfo2::Ptr         route_info = nullptr;
        /// Match information calculated from Local Map Server 
        MapMatchingInfoType matching_info;
        /// Scene sketch
        std::vector<SceneSketch> scene_sketchs;
        /// Scene sketch v2
        SceneSketchSPtrVecType scene_sketchs_v2;
    };

    // The context would be used to be analysed for 
    // Whether or not to use the CURRENT GNERATOR
    using GeneratorContext = Input;

    struct Output
    {
        /// Several new lane path
        std::vector<LanePathSPtrType> paths;
    };

    enum class LanePathGeneratorMode : holo::uint8_t
    {
        UNDEFINED = 0,
        DEFAULT,
        SPLIT,
        MERGE
    };

protected:
    struct LanePathGeneratorSeed
    {
        holo::uint64_t                   lane_id    = 0U;       ///> lane id for starting calculation
        holo::uint64_t                   link_id    = 0U;       ///> link id for starting calculation
        RouteInfo2::Ptr                  route_info = nullptr;  ///> a vector of link ids for road-level
        holo::float64_t                  offset   = 0.0;  ///> the distance from current position to end of current link
        holo::int32_t                    sequence = 0;    ///> the sequence of lane
        holo::map::format::GeoPoint      position;        ///> current position
        std::vector<SceneSketchSPtrType> scene_sketchs;   ///> scene sketchs
    };

public:
    LanePathGeneratorBase() = default;

    virtual ~LanePathGeneratorBase() = default;

    /**
     * @brief Initialize
     */
    holo::bool_t Init(RetrieverSPType ret);

    /**
     * @brief Set the distance for searching for the lane
     */
    void SetSearchDistance(holo::float64_t const dist);

    /**
     * @brief Caculate the lane-level path
     */
    holo::bool_t Run(LanePathGeneratorBase::Input const& input, LanePathGeneratorBase::Output& output);

    /**
     * @brief Construct constraints and terminators by scene
     */
    virtual holo::bool_t UpdateScenes(std::vector<SceneSketchSPtrType> const& scenes);

    /**
     * @brief Check if this lane path generator is enable
     */
    virtual holo::bool_t IsEnable(GeneratorContext const& input) = 0;

    /**
     * @brief Get the Mode 
     * 
     * @return lane pant generator's Mode 
     */
    virtual LanePathGeneratorMode GetMode() const = 0;

protected:
    /**
     * @brief Initialize other params
     */
    virtual holo::bool_t DoInit(); 

    /**
     * @brief Get the LanePathGenerator's all first seeds
     * 
     * @return 
     */
    virtual holo::bool_t GetAllFirstSeeds(LanePathGeneratorBase::Input const& input, std::vector<LanePathGeneratorSeed>& first_seeds);

    /**
     * @brief Do some work after lane paths have been generated
     *
     * @param paths The lane path should be dealed
     * @return holo::bool_t True, succeed; false, otherwise
     */
    virtual holo::bool_t PostProcessing(LanePathSPtrVecType& paths);

    /**
     * @brief Caculate the lane-level path
     */
    holo::bool_t GenerateLanePathBySeed(LanePathGeneratorSeed const& first_seed, LanePathSPtrVecType& lane_paths);

private:
    holo::bool_t updateRouteInfo(RouteInfo2::Ptr route_info);
    holo::bool_t trackBackItemsToLanePath(holo::int32_t const& seq, std::vector<std::shared_ptr<LaneItem>> const& v,
                                      std::vector<std::shared_ptr<LanePath>>& lane_paths);
    holo::bool_t CheckLaneValid(format::PtrLane lane);

public:
    /// handle to obtain map data
    RetrieverSPType retriever_ = nullptr;
    /// Debug infomation
    holo::bool_t verbose_ = false;

    holo::float64_t max_search_distance_ = 2200.0f;
    /// Generators for lane path
    LaneItemGeneratorManager lane_item_generator_manager_;
    /// Manager for constraint to ban some lane path generating
    ConstraintManager constraint_manager_;
    /// Terminator management
    TerminatorManager terminator_manager_;
};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_GENERATOR_BASE_H_ */