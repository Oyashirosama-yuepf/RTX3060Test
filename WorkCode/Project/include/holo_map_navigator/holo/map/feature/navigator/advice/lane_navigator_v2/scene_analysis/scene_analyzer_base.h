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

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_SCENE_ANALYZER_BASE_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_SCENE_ANALYZER_BASE_H_

#include <vector>
#include <holo/map/common/common_define.h>
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
 * @brief Scene analyzer for route links
 * 
 * @details The lane path would go by sereral scenes including
 *          down ramp, going up main road, spliting on ramp and so on
 */
class SceneAnalyzerBase
{
public:
    using SectionFormType        = holo::map::navigator::advice::scene::KeyLaneSection::SectionForm;
    using KeyLaneSectionType    = holo::map::navigator::advice::scene::KeyLaneSection;
    using SceneSketchType        = holo::map::navigator::advice::scene::SceneSketch;
    using SceneSketchSPtrType    = std::shared_ptr<SceneSketchType>;
    using SceneSketchSPtrVecType = std::vector<SceneSketchSPtrType>;
    using CompositeSceneSketchType        = holo::map::navigator::advice::scene::CompositeSceneSketch;
    using CompositeSceneSketchSPtrType    = std::shared_ptr<CompositeSceneSketchType>;
    using CompositeSceneSketchSPtrVecType = std::vector<CompositeSceneSketchSPtrType>;
    using SceneCategoryType      = SceneSketchType::SceneCategory;
    using SceneGroupType         = SceneSketchType::SceneGroup;

    using MapErrorCodeType       = holo::map::MapErrorCode;

    using RetrieverType          = holo::map::service::client::engine::Retriever;
    using RetrieverSPtrType      = holo::map::service::client::engine::RetrieverSPtrType;
    using RawRetrieverType       = holo::map::service::client::engine::helper::raw::RawRetriever;
    using RawRetrieverSPtrType   = holo::map::service::client::engine::helper::raw::RawRetrieverSPtrType;

    using FeatureType            = holo::map::service::client::engine::helper::raw::RawFeatureTypeV0;
    using FeatureIdType          = holo::map::service::client::engine::helper::raw::RawFeatureIdTypeV0;
    using FeatureIdVectorType    = holo::map::service::client::engine::helper::raw::RawFeatureIdVectorTypeV0;
    using LaneGroupSPtrType      = holo::map::service::client::engine::helper::raw::RawLaneGroupSPtrTypeV0;
    using RawLaneGroupTypeV0          = holo::map::service::client::engine::helper::raw::RawLaneGroupTypeV0;
    using LaneGroupType          = holo::map::service::client::engine::helper::raw::RawLaneGroupTypeV0::LaneGroupType;
    using LaneType               = holo::map::service::client::engine::helper::raw::RawLaneTypeV0;
    using LaneSPtrType           = holo::map::service::client::engine::helper::raw::RawLaneSPtrTypeV0;
    using LaneBoundarySPtrType   = holo::map::service::client::engine::helper::raw::RawLaneBoundarySPtrTypeV0;
    using GeoPointType            = holo::map::service::client::engine::helper::raw::RawGeoPointTypeV0;
    using GeoPointVectorType      = holo::map::service::client::engine::helper::raw::RawGeometryTypeV0;

public:
    struct Input
    {
        /// Link ids passed by route info
        VecIdType route_link_ids;
        /// Distance to current link end; unit: meters
        Distance distance_current_link_end = 0.0f;
        /// Current matched link id
        IdType match_current_link_id = 0U;
        /// Maximum distance for searching to extract scene
        Distance maximum_search_distance = 0.0f;
    };
    struct Output
    {
        /// All scene sketches extracted from link ids of route info
        SceneSketchSPtrVecType scene_sketchs;
    };

    struct CompositeInput
    {
        SceneSketchSPtrVecType scenes;
    };
    struct CompositeOutput
    {
        CompositeSceneSketchSPtrVecType scenes;
    };

public:
    SceneAnalyzerBase()                 = default;
    virtual ~SceneAnalyzerBase()        = default;
    SceneAnalyzerBase(SceneAnalyzerBase const&) = delete;
    SceneAnalyzerBase(SceneAnalyzerBase&&)      = delete;
    SceneAnalyzerBase& operator=(SceneAnalyzerBase const&) = delete;
    SceneAnalyzerBase& operator=(SceneAnalyzerBase&&) = delete;

public:
    /**
     * @brief Initialize scene analyzer using mapengine's retriever
     *
     * @param retriever mapengine's retriever
     * @return holo::bool_t True, succeed; False retriver is nullptr
     */
    virtual holo::bool_t Init(RetrieverSPtrType retriever);

    /**
     * @brief Execute analyzing calculation for scene
     *
     * @param input Input of scene analyzer
     * @param output Output of scene anlyzer
     * @return holo::bool_t True, succeed; false otherwise
     */
    virtual holo::bool_t Calculate(Input const& input, Output& output);

    /**
     * @brief Composite simple scenes to composite scenes for special road situation
     *
     * @param input simple scenes
     * @param output composite scenes
     * @return holo::bool_t True, succeed; false otherwise
     */
    virtual holo::bool_t Composite(CompositeInput const& input, CompositeOutput& output);

    /**
     * @brief Get scene category type
     * 
     * @return Scene catetory type
     */
    SceneCategoryType GetSceneCategory();
    /**
     * @brief Get scene group type of analyzery 
     * 
     * @return Scene group type 
     */
    SceneGroupType GetSceneGroup();
    /**
     * @brief This analyzer can calcute a group of scenes?  
     * 
     * @return if true, this is a group analyzer 
     */
    holo::bool_t IsGroupAnalyzer();

    holo::bool_t GetVerbose() const noexcept;
    void SetVerbose(holo::bool_t const v) noexcept;

protected:
    /**
     * @brief Get lanegroup by feature identifier 
     * @param id lanegroup's identifier
     * @param lane_group lanegroup feature
     * 
     * @return if success, return true 
     */
    holo::bool_t GetLaneGroupById(FeatureIdType const& id, LaneGroupSPtrType& lane_group);
    /**
     * @brief Get lane by feature identifier  
     * @param id lane's identifier
     * @param lane_group lane feature
     * 
     * @return if success, return true 
     */
    holo::bool_t GetLaneById(FeatureIdType const& id, LaneSPtrType& lane);
    /**
     * @brief Get laneboundary by feature identifier  
     * @param id laneboundary's identifier
     * @param lane_group laneboundary feature
     * 
     * @return if success, return true 
     */
    holo::bool_t GetLaneBoundaryById(FeatureIdType const& id, LaneBoundarySPtrType& lane_boundary);

    holo::bool_t isGroupAnalyzer();
    /**
     * @brief restricted lane, none road pass right(now only emergency lane set restricted)
     *
     * @param input lane instance
     * @return if true, restricted
     */
    holo::bool_t isRestrictedLane(LaneSPtrType lane);
    /**
     * @brief Intersection lanegroup
     *
     * @param input lane group instance
     * @return if true, lanegroup is in intersection
     */
    holo::bool_t isIntersectionLaneGroup(RawLaneGroupTypeV0 const& lane_group);

protected:
    /// map engine's retriver instance
    RawRetrieverSPtrType raw_retriever_ = nullptr;
    holo::bool_t is_group_analyzer_ = false;
    SceneCategoryType scene_catagory_ = SceneCategoryType::UNDEFINED;
    SceneGroupType scene_group_ = SceneGroupType::UNDEFINED;

    /// If true, print debugging messages to log.
    holo::bool_t verbose_ = true;

};
}  // namespace scene
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_SCENE_ANALYZER_BASE_H_ */