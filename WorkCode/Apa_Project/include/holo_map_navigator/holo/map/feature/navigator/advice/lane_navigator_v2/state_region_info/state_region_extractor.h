/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file state_region_extractor.h
 * @brief Extract state region form lane path.
 * @author wanghaiyang@holomatic.com
 * @date "2022-01-19"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_STATE_REGION_EXTRACTOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_STATE_REGION_EXTRACTOR_H_

#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_analysis/scene_analyzer_manager.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>

#include <holo/map/common/match_info.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{

class StateRegionExtractor
{
public:
    using LanePathType              = holo::map::navigator::advice::LanePath;
    using LanePathSPtrType          = std::shared_ptr<LanePathType>;
    using LanePathSPtrVectorType    = std::vector<LanePathSPtrType>;

    using LaneItemType              = holo::map::navigator::advice::LaneItem;
    using LaneItemSPtrType          = std::shared_ptr<LaneItemType>;
    using LaneItemSPtrVectorType    = std::vector<LaneItemSPtrType>;

    using StateRegionType           = holo::map::navigator::advice::StateRegion;
    using StateRegionVectorType     = std::vector<StateRegionType>;

    using FeatureIdType         = MapFeatureIdType;
    using FeatureIdVectorType   = MapFeatureIdVectorType;

    using DistanceWithMeterType = holo::float64_t;
    
    using SceneSketchType = scene::SceneSketch;
    using SceneSketchSPtrType    = std::shared_ptr<scene::SceneSketch>;
    using SceneSketchSPtrVecType = std::vector<SceneSketchSPtrType>;

    using MapMatchingInfoType = holo::map::MapMatchInfo;

    StateRegionExtractor();
    virtual ~StateRegionExtractor();

    holo::bool_t GetVerbose() const noexcept;

    void SetVerboase(holo::bool_t const v);

    holo::bool_t Init(RetrieverSPType ret);

    holo::bool_t Process(MapMatchingInfoType const& match_info, SceneSketchSPtrVecType const& scene_sketchs, 
                                                LanePathSPtrVectorType& lane_paths);

private:
    enum class FlowingType : holo::uint8_t
    {
        FT_UNKNOWN = 0,
        FT_MERGING = 1,
        FT_SPLITING = 2,
        FT_MERGING_AND_SPLITING = 3,
        FT_SPLITING_AND_MERGING = 4,
        FT_BREAKUP = 5,
        FT_MERGE_PASS_BY_LEFT = 6,
        FT_MERGE_PASS_BY_RIGHT = 7,
        FT_SPLIT_PASS_BY_LEFT = 8,
        FT_SPLIT_PASS_BY_RIGHT = 9,
        FT_INTERSECTION = 10,
    };

    enum class FlowingDirection : holo::uint8_t
    {
        FD_UNKNOWN = 0,
        FD_LEFT = 1,
        FD_RIGHT = 2,
        FD_AROUND_LEFT = 3,
        FD_AROUND_RIGHT = 4,
        FD_AREA_LEFT = 5,
        FD_AREA_RIGHT = 6,
    };

    enum class FlowingLaneType : holo::uint8_t
    {
        FLT_UNKNOWN = 0,
        FLT_ACCELERATION = 1,
        FLT_DECELERATION = 2,
    };

    struct FlowingRegion
    {
        FlowingType type = FlowingType::FT_UNKNOWN;
        FlowingDirection direction = FlowingDirection::FD_UNKNOWN;
        FlowingLaneType lane_type = FlowingLaneType::FLT_UNKNOWN;

        FeatureIdVectorType lane_ids;
        FeatureIdType id = 0;

        DistanceWithMeterType offset_to_start   = 0.0;
        DistanceWithMeterType offset_to_stop    = 0.0;
        DistanceWithMeterType length            = 0.0;
    };

    using FlowingRegionType = struct FlowingRegion;
    using FlowingRegionVectorType = std::vector<FlowingRegionType>;

    enum class JunctureAlignmentType : holo::uint8_t
    {
        JAT_UNKNOWN = 0,
        JAT_PARALLEL = 1,
        JAT_DOUBLE_STRAIGHT = 2,
        JAT_SINGLE_LEFT_TO_DOUBLE_POINT = 3,
        JAT_SINGLE_RIGHT_TO_DOUBLE_POINT = 4,
        JAT_DOUBLE_POINT_TO_SINGLE_LEFT = 5,
        JAT_DOUBLE_POINT_TO_SINGLE_RIGHT = 6,
        JAT_SINGLE_LEFT_TO_SINGLE_RIGHT = 7,
        JAT_SINGLE_RIGHT_TO_SINGLE_LEFT = 8,
        JAT_RESERVE_0 = 200,
        JAT_RESERVE_1 = 201,
        JAT_RESERVE_2 = 202,
        JAT_RESERVE_3 = 203,
        JAT_RESERVE_4 = 204,
        JAT_OTHERS = 255
    };

    struct FlowingItem
    {
        using IndexType = std::size_t;

        FlowingType main_type       = FlowingType::FT_UNKNOWN;
        FlowingType secondary_type  = FlowingType::FT_UNKNOWN;
        FlowingLaneType lane_type = FlowingLaneType::FLT_UNKNOWN;

        FeatureIdType id = 0;

        IndexType item_index    = 0;
        IndexType start_index   = 0;
        IndexType stop_index    = 0;

        FeatureIdType item_lane_id      = 0;
        FeatureIdType start_lane_id     = 0;
        FeatureIdType stop_lane_id      = 0;
    };

    using FlowingItemType = struct FlowingItem;
    using FlowingItemVectorType = std::vector<FlowingItemType>;

    static std::string FormatToString(FlowingRegionType const& region);

    static std::string FormatToString(FlowingItemType const& item);

    holo::bool_t process(MapMatchingInfoType const& match_info, LanePathSPtrType& lane_path);

    holo::bool_t extractFlowingRegions(MapMatchingInfoType const& match_info, LanePathSPtrType lane_path,
        FlowingRegionVectorType& flowing_regions);

    holo::bool_t updateLanePath(FlowingRegionVectorType const& flowing_regions,
        LanePathSPtrType& lane_path);

    holo::bool_t extractFlowingeItems(MapMatchingInfoType const& match_info, LanePathSPtrType lane_path,
        FlowingItemVectorType& flowing_items);

    holo::bool_t findFlowingeItems(MapMatchingInfoType const& match_info, LanePathSPtrType lane_path,
        FlowingItemVectorType& flowing_items);

    holo::bool_t updateFlowingeItemRanges(LanePathSPtrType lane_path,
        FlowingItemVectorType& flowing_items);

    holo::bool_t findFlowingItemRange(LanePathSPtrType lane_path,
        FlowingType const type,  FlowingItemType::IndexType const index,
        FlowingItemType::IndexType& start_index,
        FlowingItemType::IndexType& stop_index);

    holo::bool_t findStartAndEndIndex(LanePathSPtrType lane_path,
        std::size_t const index, std::size_t& start_index, std::size_t& stop_index);

    holo::bool_t extractFlowingRegionsFromFlowingItems(MapMatchingInfoType const& match_info, LanePathSPtrType lane_path,
        FlowingItemVectorType const& items, FlowingRegionVectorType& regions);

    holo::bool_t extractFlowingRegionFromFlowingItem(MapMatchingInfoType const& match_info, LanePathSPtrType lane_path,
        FlowingItemType const& item, FlowingRegionType& regions);

    holo::bool_t extractFlowingRegionByRangeForFlowMerging(MapMatchingInfoType const& match_info, LanePathSPtrType lane_path,
        FlowingItemType const& item, FlowingRegionType& region);

    holo::bool_t extractFlowingRegionByRangeForFlowSpliting(MapMatchingInfoType const& match_info, LanePathSPtrType lane_path,
        FlowingItemType const& item, FlowingRegionType& region);

    holo::bool_t extractFlowingRegionByRangeForIntersection(MapMatchingInfoType const& match_info, LanePathSPtrType lane_path,
        FlowingItemType const& item, FlowingRegionType& region);
        
    holo::bool_t extractFlowingRegionByRangeForBreakUp(LanePathSPtrType lane_path, FlowingItemType const& item, FlowingRegionType& region);

    holo::bool_t extractFlowingRegionByRangeForPassBy(LanePathSPtrType lane_path, FlowingItemType const& item, FlowingRegionType& region);

    holo::bool_t extractFlowingItemForPassBy(LaneItemSPtrType curr_item, LaneItemSPtrType succ_item, FlowingType& fl_item_main_type);

    holo::bool_t getFlowingDirectionFromTopologyLanes(
        format::PtrLane preceding_lane, format::PtrLane succeeding_lane, FlowingDirection& direction);

    holo::bool_t getFlowingDirectionFromRoadNetwork(
        format::PtrLane lane, FlowingDirection& direction);

    holo::bool_t getJunctureAlignmentTypeFromTopologyLanes(format::PtrLane preceding_lane,
        format::PtrLane succeeding_lane, JunctureAlignmentType& type);

    holo::bool_t findKlsByLaneId(FeatureIdType const lane_id, SceneSketchSPtrType & target_scene, std::vector<FeatureIdType>& key_lanes);

    holo::bool_t findPassByStartAndStopIndex(LanePathSPtrType lane_path,
        std::size_t const index, holo::bool_t const is_merge, holo::bool_t const is_left,
        std::size_t& start_index, std::size_t& stop_index);

    holo::bool_t findStateRegionLaneIds(FeatureIdType const seed_lane_id, holo::bool_t const is_merge, 
        holo::bool_t const is_left, std::vector<FeatureIdType>& state_region_ids);
    
    holo::bool_t getLeftAndRightLaneId(FeatureIdType current_lane_id, FeatureIdType& left_lane_id, 
        FeatureIdType& right_lane_id);
    
    holo::bool_t getBreakUpStartAndStopIndex(LanePathSPtrType lane_path, std::size_t const index,
                                              std::size_t& start_index, std::size_t& stop_index);

    holo::bool_t getIntersectionStartAndStopIndex(LanePathSPtrType lane_path, std::size_t const index,
                                              std::size_t& start_index, std::size_t& stop_index);
    
    holo::bool_t caculateFlowingDirectionByTopology(LanePathSPtrType lane_path, FlowingItemType const& item, FlowingDirection& fl_direction);
    
    holo::bool_t caculateFlowingDirectionByTurnType(LanePathSPtrType lane_path, FlowingItemType const& item, FlowingDirection& fl_direction);

private:
    RetrieverSPType retriever_ = nullptr;
    SceneSketchSPtrVecType  scene_sketchs_;
    //unit: meter
    const Distance MAX_BREAK_UP_PRE_SEARCH_DIATANCE = 200.0;
    holo::bool_t verbose_ = false;
};

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_STATE_REGION_EXTRACTOR_H_ */