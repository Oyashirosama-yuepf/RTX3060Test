/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_path_manager.h
 * @brief Generate lane path for lane-level navigation base on given combined rules
 * @author chanqiliang (chanqiliang@holomatic.com)
 * @date 2022-04-06
 */
#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_MANAGER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_MANAGER_H_

#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/lane_path_generator/lane_path_generator_default.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/lane_path_generator/lane_path_generator_split.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/lane_path_generator/lane_path_generator_merge.h>

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
class LanePathManager
{
    using LanePathSPtrType                  = std::shared_ptr<LanePath>;
    using LanePathSPtrVecType               = std::vector<LanePathSPtrType>;
    using LaneItemSPtrType                  = std::shared_ptr<LaneItem>;
    using LaneItemSPtrVecType               = std::vector<LaneItemSPtrType>;
    using GeneratorSPtrType                 = std::shared_ptr<holo::map::navigator::advice::lanepath::LaneItemGeneratorBase>;
    using SceneSketchType                   = holo::map::navigator::advice::scene::SceneSketch;
    using SceneCategoryType      = SceneSketchType::SceneCategory;
    using CompositeSceneSketchType          = holo::map::navigator::advice::scene::CompositeSceneSketch;
    using SceneSketchSPtrType               = std::shared_ptr<SceneSketchType>;
    using CompositeSceneSketchSPtrType      = std::shared_ptr<CompositeSceneSketchType>;
    using SceneSketchSPtrVecType            = std::vector<SceneSketchSPtrType>;
    using GeneratorModeType                 = LaneItemGeneratorBase::GeneratorMode;
    using LanePathGeneratorBaseType     = holo::map::navigator::advice::lanepath::LanePathGeneratorBase;
    using LanePathGeneratorBaseSPtrType = std::shared_ptr<LanePathGeneratorBaseType>;
    using LanePathGeneratorBaseVecSPtrType = std::vector<LanePathGeneratorBaseSPtrType>;
    using LanePathGeneratorDefalutType     = holo::map::navigator::advice::lanepath::LanePathGeneratorDefault;
    using LanePathGeneratorDefaultSPtrType = std::shared_ptr<LanePathGeneratorDefalutType>;
    using LanePathGeneratorSplitType      = holo::map::navigator::advice::lanepath::LanePathGeneratorSplit;
    using LanePathGeneratorSplitSPtrType  = std::shared_ptr<LanePathGeneratorSplitType>;
    using LanePathGeneratorMergeType      = holo::map::navigator::advice::lanepath::LanePathGeneratorMerge;
    using LanePathGeneratorMergeSPtrType  = std::shared_ptr<LanePathGeneratorMergeType>;
    using MapMatchingInfoType             = holo::map::MapMatchInfo;

public:
    LanePathManager() = default;
    ~LanePathManager() = default;

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
    
    struct Output
    {
        /// Several new lane path
        std::vector<LanePathSPtrType> paths;
    };

    /**
     * @brief Caculate the lane-level path depends on different lane path generator
     *
     * @param input Input of lane-path generator
     * @param output Output of lane-path generator
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t Run(Input const& input, Output& output);

    holo::bool_t Init();

private:
    holo::bool_t setLanePathId(LanePathSPtrVecType& lane_paths);

    holo::bool_t setGrading(LanePathSPtrVecType& lane_paths, SceneSketchSPtrVecType const& scenes);

private:
    LanePathGeneratorBaseVecSPtrType lane_path_genetators_;
    LanePathSPtrVecType last_lane_paths_;
};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif