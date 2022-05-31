/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_path.h
 * @brief New Lane Path
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-10-08"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_LANE_PATH_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_LANE_PATH_H_

#include <queue>
#include <sstream>
#include <vector>

#include <holo/common/road_type.h>
#include <holo/core/types.h>

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/state_region_info/state_region.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/region_model_info/lane_change_region.h>
#define LANE_PATH_ON_ROUTE 0x01
#define LANE_PATH_LANE_LEVEL 0X02

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class RegionModelInfo;
/**
 * @brief New lane path, which describe one lane-level navigation route
 * @note Member varibale description defaut value is zero; in other words,
 *       as defalut, the lane path is not lane-level route and not towards
 *       to destination.
 */
class LanePath
{
public:
    using LanePathSPtrType       = std::shared_ptr<LanePath>;
    using LanePathSPtrVectorType = std::vector<LanePathSPtrType>;
    using RegionModelInfoSPtrType = std::shared_ptr<RegionModelInfo>;
    using RegiionModelInfoSPtrVecType = std::vector<RegionModelInfoSPtrType>;

    using StateRegionType       = holo::map::navigator::advice::StateRegion;
    using StateRegionVectorType = std::vector<StateRegionType>;

    using LaneChangeRegionType = holo::map::navigator::advice::LaneChangeRegion;
    using LaneChangeRegionSPtrType = std::shared_ptr<LaneChangeRegionType>;
    using LaneChangeRegionSPtrVecType = std::vector<LaneChangeRegionSPtrType>;

    enum class AccessibilityCategory : holo::uint8_t
    {
        UNDEFINED = 0U,
        ACCESSED,
        NO_ACCESSED,
        OHTERS
    };

    enum class InclusiveRelation : holo::uint8_t
    {
        INCLUSIVE_RELATION_UNDEFINED    = 1U,
        INCLUSIVE_RELATION_IDENTICAL    = 2U,
        INCLUSIVE_RELATION_CONTAINING   = 3U,
        INCLUSIVE_RELATION_BE_CONTAINED = 4U,
        INCLUSIVE_RELATION_NO_RELATION  = 5U
    };

    struct RelateEndpoint
    {
        holo::bool_t is_valid = false;
        holo::bool_t is_relate_lane_path_id = false;
        IdType relate_lane_path_id = 0;
        MapFeatureIdType from_lane_id = 0;
        MapFeatureIdVectorType to_lane_ids;
    };

    struct Grading
    {
        enum class GradingMode : holo::uint8_t
        {
            NONE              = 0,
            ROAD_SPLIT        = 1,  /// support split_main_branch and dowm-ramp
            ROAD_MERGE        = 2,  /// support ramp-merge-main
            INNER_BREAKING_UP = 3,
            ROAD_SPLIT_TWO_RAMP,
            ROAD_SPLIT_TWO_MAIN,
            ROAD_SPLIT_MAIN_DOWN_RAMP
        };
        static const holo::uint64_t INVALID_LANE_ID = 0;
        /// the id of candinate lane that's in from link of first key scene
        holo::uint64_t candidate_lane_id = INVALID_LANE_ID;
        /// lane path level depends on level of the candidate lane
        holo::uint8_t level = 255;
        /// is lane path pass through a target lane?
        holo::bool_t is_go_through_target_lane = false;
        /// Whether or not has graded
        holo::bool_t is_grading = false;
        /// Grading mode
        GradingMode mode = GradingMode::NONE;

        static std::string FormatToString(Grading const& grading)
        {
            std::stringstream ss;
            ss << "{";
            ss << "\"candidate_lane_id\": \"" << grading.candidate_lane_id;
            ss << "\", \"level\": \"" << static_cast<holo::int32_t>(grading.level);
            ss << "\", \"is_go_through_target_lane\": " << grading.is_go_through_target_lane;
            ss << ", \"is_grading\": " << grading.is_grading;
            ss << ", \"mode\": " << static_cast<holo::int32_t>(grading.mode);
            ss << "\"}";
            return ss.str();
        }
    };

    using RelateEndpointType = RelateEndpoint;
    using RelateEndpointSPtrType = std::shared_ptr<RelateEndpointType>;

public:
    /**
     * @brief Format to JSON String
     *
     * @param advice LanePath2
     * @return std::string JOSN string
     */
    static std::string FormatToString(LanePath const& path);

    /**
     * @brief Format to JSON String
     *
     * @param advice A vector of LanePath2
     * @return std::string JOSN string
     */
    static std::string FormatToString(std::vector<LanePathSPtrType> const& paths);

    /**
     * @brief Match the curretn lane queue and last lane queue; if the back section
     *        of last queue and front section of current lane queue is identical, then
     *        we regard it matched
     *
     * @param lane_queues Several candidate lane queues to be checked to match
     * @param lane_queue Current lane queue
     * @param has_matched Whether or not there is a lane queue which is matched to current lane queue
     * @param matched_id The matched id
     * @return holo::bool_t True,succes; false, otherwise
     */
    static holo::bool_t MatchAndTruck(std::vector<LanePathSPtrType> const& lane_queues, LanePathSPtrType& lane_queue,
                                         holo::bool_t& has_matched, holo::uint64_t& matched_id);

    /**
     * @brief Track all lane paths
     *
     * @param last_paths Last lane paths
     * @param current_paths Current lane paths
     * @return holo::bool_t True, succeed; false, otherwise
     */
    static holo::bool_t TrackAllPaths(std::vector<LanePathSPtrType> const& last_paths,
                                      std::vector<LanePathSPtrType>&       current_paths,
                                      std::map<std::size_t, std::size_t>& lookup);
    /**
     * @brief Split the lane queue from start position in any length
     *
     * @param queue The queue need to be splited
     * @param start Start positon to be splited
     * @param count The size of queue which has been splited, but start + count <= size of queue
     * @return LaneQueue The queue that is splited from queue
     */
    static LanePath Split(LanePath const& path, holo::uint64_t start, holo::uint64_t count);

    /**
     * @brief Calculate state region for lane path
     *
     * @param path LanePath
     * @return holo::bool_t True, success; false, otherwise
     */
    static holo::bool_t CalcuateStateRegion(LanePathSPtrType path);

    /**
     * @brief Extract unique lane path
     *
     * @param paths LanePath
     * @return holo::bool_t True, success; false, otherwise
     */
    static holo::bool_t ExtractUniquePaths(LanePathSPtrVectorType& paths);

    /**
     * @brief Unique push lane path
     *
     * @param paths lane paths for push 
     * @param other lane path to push
     * @return holo::bool_t True, success; false, otherwise
     */
    static holo::bool_t UniquePushPaths(LanePathSPtrVectorType& paths, LanePathSPtrType const& other);

public:
    LanePath()                = default;
    LanePath(LanePath&&)      = default;
    LanePath& operator=(LanePath&&) = default;

    LanePath(LanePath const&);
    LanePath& operator=(LanePath const&);

    ~LanePath()                     = default;

    /**
     * @brief Set the Id
     *
     * @param id
     */
    void SetId(holo::uint64_t id);

    /**
     * @brief Get the Id
     *
     * @return holo::uint64_t Unique id for lane path
     */
    holo::uint64_t GetId() const;

    /**
     * @brief Set the Sequence Number
     *
     * @param seq Sequence number
     */
    void SetSequenceNumber(holo::int32_t const seq);

    /**
     * @brief Get the Sequnce Number
     *
     * @return holo::int32_t Sequence number
     */
    holo::int32_t GetSequnceNumber() const;

    /**
     * @brief Get the Lane Items
     *
     * @return std::vector<LaneItem> const& Get all ane items in lane path
     */
    LaneItemSPtrVecType const GetLaneItems() const;

    /**
     * @brief Get the Region Model Infos
     *
     * @return All region model infos
     */
    RegiionModelInfoSPtrVecType const& GetRegionModelInfos() const;

    /**
     * @brief Get the Region Model Infos
     * 
     * @return std::vector<RegionModelInfo>const& 
     */
    RegiionModelInfoSPtrVecType& GetRegionModelInfos();

    /**
     * @brief Set the Is Road Level
     *
     * @param is_lane_level Whther or not is road level;
     *                      bit 1 stands for lane level; 0 for road level
     */
    void SetIsLaneLevel(holo::bool_t is_lane_level);

    /**
     * @brief Whether or not is lane level
     *
     * @note bit 1 stands for lane level; 0 for road level
     *
     * @return true It is lane level
     * @return false Not lane level
     */
    holo::bool_t IsLaneLevel() const;

    /**
     * @brief Set the state for whether or not on route
     *
     * @param on_route Whether or not on route; bit 1 stands for on route;
     *                 0 for not on route
     */
    void SetIsOnRoute(holo::bool_t on_route);

    /**
     * @brief Whether or not on route
     *
     * @return true On route
     * @return false Not on route
     */
    holo::bool_t IsOnRoute() const;

    /**
     * @brief Get the Tracked Ids
     *
     * @return Tracked ids of lane paths in previous frame
     */
    std::vector<holo::uint64_t> const GetTrackedIds() const;

    /**
     * @brief Calculate inclusive relation with another
     */
    InclusiveRelation InclusiveRelates(LanePath const& path) const;

    /**
     * @brief Split the lane queue from start position
     *
     * @param start The start position
     * @param count The size of splited queue
     * @return PathQueue Splited queue
     */
    LanePath Split(holo::uint64_t start, holo::uint64_t count) const;

    /**
     * @brief Set the Visited 
     * 
     * @param visited Whether or not the lane path has been calculated
     */
    void SetVisited(holo::bool_t const visited);

    /**
     * @brief Get the Visited object
     * 
     * @return holo::bool_t 
     */
    holo::bool_t Visited() const;

    /**
     * @brief Get the Item Idx By Distance
     *
     * @param dist
     * @return LaneItemSPtrType
     */
    LaneItemSPtrType GetItemByDistance(holo::float64_t const dist) const;

    /**
     * @brief Update for lane path 
     *
     * @return holo::bool_t
     */
    holo::bool_t Update();

    /**
     * @brief Get the Description
     * 
     * @return holo::uint16_t 
     */
    holo::uint16_t GetDescription() const;

    /**
     * @brief Is lane id existed in lane path
     *
     * @param id Lane id
     * @return holo::bool_t True, existed; false, not existed
     */
    holo::bool_t IsLaneIdExisted(IdType const id);

    /**
     * @brief Is link id existed in lane path
     *
     * @param id Link id
     * @return holo::bool_t True, existed; false, not existed
     */
    holo::bool_t IsPassedCertainLink(IdType const id);

    /**
     * @brief Whether or not has region lane ids
     * 
     * @param lane_ids 
     * @return holo::bool_t 
     */
    holo::bool_t HasRegionLaneIds(std::vector<holo::uint64_t> const& lane_ids) const;

    /**
     * @brief Update back item
     * 
     * @return holo::bool_t 
     */
    holo::bool_t UpdateTrackedItem(LaneItemSPtrType item);

    /**
     * @brief Get the On Route Length 
     * 
     * @return holo::float64_t Length on route
     */
    holo::float64_t GetOnRouteLength() const;

    /**
     * @brief Push front queue
     *
     * @param item Pointer to lane node
     */
    void PushFront(LaneItemSPtrType item);

    /**
     * @brief Push back queue
     *
     * @param item Pointer to lane ndoe
     */
    void PushBack(LaneItemSPtrType item);

    /**
     * @brief Get the Index By Lane Id object
     *
     * @param lane_id Lane id
     * @return holo::uint64_t Index of lane by its id
     */
    holo::uint64_t GetItemIndexByLaneId(holo::uint64_t const lane_id) const;

    /**
     * @brief Get the Index By Lane item
     *
     * @param lane_id Lane id
     * @return holo::uint64_t Index of lane by its id
     */
    holo::bool_t GetItemIndexByItem(LaneItemSPtrType item, holo::uint64_t& index) const;

    /**
     * @brief Get visual length of lane path
     */
    holo::float64_t GetLanePathVisualLength() const;

    /**
     * @brief Get the Visual Sum Angles Cost
     * 
     * @return holo::float64_t 
     */
    holo::float64_t GetVisualSumAnglesCost() const;

    /**
     * @brief Overload operator [] to get lane node from queue
     *
     * @param idx Index of lane node
     * @return LaneNodeSPtr Pointer of certain lane node
     */
    LaneItemSPtrType operator[](std::size_t idx) const;

    /**
     * @brief Get size of lane queue
     *
     * @return std::size_t
     */
    std::size_t Size() const;

    /**
     * @brief Judege whether or not the queue is empty
     *
     * @return holo::bool_t
     */
    holo::bool_t Empty() const;

    /**
     * @brief Clear items
     */
    void Clear();

    /**
     * @brief Get the front lane node of queue
     */
    LaneItemSPtrType Front() const;

    /**
     * @brief Get the back lane node of queue
     */
    LaneItemSPtrType Back() const;

    /**
     * @brief Get the State Regions 
     * 
     * @return State regions 
     */
    std::vector<StateRegion>& GetStateRegions();

    /**
     * @brief Get the State Regions 
     * 
     * @return State regions 
     */
    std::vector<StateRegion> const& GetStateRegions() const;


    void SetStateRegions(StateRegionVectorType const& regions);

    void SetStateRegions(StateRegionVectorType&& regions);

    holo::bool_t HasLeftLaneBoundaryIds(std::vector<IdType> const& ids, holo::bool_t const strict);
    holo::bool_t HasRightLaneBoundaryIds(std::vector<IdType> const& ids, holo::bool_t const strict);

    RelateEndpointType const GetRelateEndpoint();
    void SetRelateEndpoint(RelateEndpointType const& endpoint);

    holo::bool_t ClearHistoryTrace();

    /**
     * @brief Set level of the candidate lane 
     */
    void SetLevel(holo::uint8_t const level);
    /**
     * @brief Get level of the candidate lane 
     * @return lane path level
     */
    holo::uint8_t GetLevel();
    /**
     * @brief Set candidate lane id
     */
    void SetCandidateLaneId(holo::uint64_t const candidate_lane_id, holo::bool_t const is_target_lane);
    /**
     * @brief Get candidate lane id
     * @return candidate lane id
     */
    holo::uint64_t GetCandidateLaneId();
    /**
     * @brief Candinate is a target lane?
     * @return if true, the candidate lane is target lane
     */
    holo::bool_t IsGoThroughTargetLane();

    Grading const& GetGrading() const;

    void SetGrading(Grading const grading);

    LaneChangeRegionSPtrVecType const& GetLaneChangeRegions() const;

    LaneChangeRegionSPtrVecType& GetLaneChangeRegions();

    void SetAccessibilityCategory(AccessibilityCategory const category);

    AccessibilityCategory GetAccessibilityCategory() const;

private:
    /// Unique id for lane path
    holo::uint64_t id_ = 0U;
    /// Sequence number of lane; current lane's sequence is 0.
    /// And left lane next current lane is -1; right lane next
    /// to current lane is +1;
    holo::int32_t sequence_number_ = 0U;
    /// Basic elements for lane path;
    std::deque<LaneItemSPtrType> lane_items_;
    /// A vector of Region Model Info about changing, mergin and
    /// spliting， which represents procedure for changing lane
    RegiionModelInfoSPtrVecType region_model_infos_;
    /// Lane-chagne regions
    LaneChangeRegionSPtrVecType lane_change_regions_;
    /// LANE_PATH_LANE_LEVEL -> whether or not on route; LANE_PATH_ON_ROUTE -> 
    /// whether or not is lane level
    holo::uint16_t description_ = 0;
    /// Whether or not is on route
    holo::bool_t   is_on_route_ = false;
    /// Whether or not the lane path has been visited, more details:
    /// The lane path would be calculated region model info from one
    /// to another lane path.In order to avoid double calculation,
    /// we need set a flag to represent that the lane path has been
    /// calculated
    holo::bool_t visited_ = false;
    /// State regions
    std::vector<StateRegion> state_regions_;

    RelateEndpointType relate_endpoint_;

    /// Grading lane path
    Grading      grading_;

    /// Accessibility
    AccessibilityCategory accesibility_category_ = AccessibilityCategory::UNDEFINED;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_LANE_PATH_H_ */
