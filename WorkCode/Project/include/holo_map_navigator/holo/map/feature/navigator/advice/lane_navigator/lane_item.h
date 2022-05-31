/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_item2.h
 * @brief New Lane Item
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-10-08"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_LANE_ITEM_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_LANE_ITEM_H_

#include <memory>
#include <sstream>
#include <vector>

#include <holo/common/road_category.h>
#include <holo/core/types.h>

#include <holo/map/common/common_define.h>

#include <holo/map/format/base/lane.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
// class LanePath;
/**
 * @brief The basic element of lane path
 *
 */
class LaneItem
{
public:
    using LaneItemSPtrType = std::shared_ptr<LaneItem>;
    using LaneItemSPtrVecType  = std::vector<LaneItemSPtrType>;
    /**
     * @brief Status for intersecion
     *
     */
    enum class IntersectionStatus : holo::uint8_t
    {
        UNDEFINED = 0U,                         ///> Undefined
        NO_INTERSECTION,                   ///> There is no intersection
        INTERSECTION_NO_TRAFFIC,           ///> There is intersecton without traffic
        INTERSECTION_WITH_TRAFFIC,         ///> There is intersection with traffic
    };

public:
    /**
     * @brief Create a Lane Node
     *
     * @param ret Retriever for data engine
     * @param lane_id Lane id
     * @param node New lane node
     * @return holo::bool_t True, success; false, otherwise
     */
    static holo::bool_t CreateItem(RetrieverSPType ret, holo::uint64_t const lane_id, LaneItemSPtrType& item);

    /**
     * @brief Create a First Lane Item
     * 
     * @param ret 
     * @param lane_id 
     * @param item 
     * @param dist_to_end 
     * @return holo::bool_t 
     */
    static holo::bool_t CreateFirstItem(RetrieverSPType ret, holo::uint64_t const lane_id, LaneItemSPtrType& item,
                                        holo::float64_t dist_to_end);

    /**
     * @brief Create a vector of Successive Items
     *
     * @param ret Data retriveer
     * @param curr_item Current lane item
     * @param succ_items Succesive lane items
     * @return holo::bool_t True, success; false, otherwise
     */
    static holo::bool_t CreateSuccessiveItems(RetrieverSPType ret, LaneItemSPtrType curr_item,
                                              LaneItemSPtrVecType& succ_items);

    /**
     * @brief Create a Parallel Item
     * 
     * @param ret 
     * @param boundary_id 
     * @param side_left 
     * @param item 
     * @return holo::bool_t 
     */
    static holo::bool_t CreateParallelItem(RetrieverSPType ret, IdType const boundary_id,
                                           holo::bool_t const side_left, LaneItemSPtrType& item);

    /**
     * @brief Format to JSON String
     *
     * @param advice LaneItem2
     * @return std::string JOSN string
     */
    static std::string FormatToString(LaneItem const& item);

    /**
     * @brief Format to JSON String
     *
     * @param advice A vector of LaneItem2
     * @return std::string JOSN string
     */
    static std::string FormatToString(std::vector<LaneItemSPtrType> const& items);

    /**
     * @brief Whether or not be front of other lane item
     *
     * @param other
     * @return holo::bool_t
     */
    static holo::bool_t BeFrontOf(RetrieverSPType ret, LaneItemSPtrType front, LaneItemSPtrType after, holo::bool_t& is);

    /**
     * @brief Check two lane items is equql, we take lane id or
     *        entry/exit id in intersecion into consideration
     *
     * @param a One lane item
     * @param b Another lane item
     * @return holo::bool_t True, equal; false, not equal
     */
    static holo::bool_t RoughEqual(LaneItemSPtrType a, LaneItemSPtrType b);

    LaneItem()                = default;
    LaneItem(LaneItem&&)      = default;
    LaneItem& operator=(LaneItem&&) = default;

    LaneItem(LaneItem const&);
    LaneItem& operator=(LaneItem const&);

    virtual ~LaneItem()        = default;

    /**
     * @brief Get the Out Route Distance object
     *
     * @return holo::float64_t
     */
    holo::float64_t GetOutRouteDistance() const;

    /**
     * @brief
     *
     * @return std::size_t
     */
    std::size_t Index() const;

    /**
     * @brief
     *
     * @param ret
     * @param other
     * @param is_right
     * @return holo::bool_t
     */
    holo::bool_t NextTo(LaneItemSPtrType other, holo::bool_t const is_right);

    /**
     * @brief Set the Lane Id
     *
     * @param lane_id Lane id
     */
    void SetLaneId(holo::uint64_t const lane_id);

    /**
     * @brief Get lane id
     *
     * @return holo::uint64_t Lane id
     */
    holo::uint64_t GetLaneId() const;

    /**
     * @brief Set the Is In Intersection
     *
     * @param in Whether or not in intersection
     */
    void SetIntersectionStatus(IntersectionStatus const in);

    /**
     * @brief Whether or not in intersection
     *
     * @return holo::bool_t
     */
    IntersectionStatus GetIntersectionStatus() const;

    /**
     * @brief Set the Length
     *
     * @param len Length of lane
     */
    void SetLength(holo::float64_t const len);

    /**
     * @brief Get length of lane
     *
     * @return holo::float64_t Length of lane
     */
    holo::float64_t GetLength() const;

    /**
     * @brief Set the Road Type
     *
     * @param type Road type
     */
    void SetRoadCategory(holo::common::RoadCategory const category);

    /**
     * @brief Get road type
     *
     * @return holo::common::RoadType
     */
    holo::common::RoadCategory GetRoadCategory() const;

    /**
     * @brief Set the Parent Node
     *
     * @param node Parent lane node
     */
    void SetPreviousItem(LaneItemSPtrType item);

    /**
     * @brief Set the Parent Node
     *
     * @param node Parent lane node
     */
    void SetSimplePreviousItem(LaneItemSPtrType item);

    /**
     * @brief Get the Parent lane Node
     *
     * @return Parent lane node
     */
    LaneItemSPtrType GetPreviousItem() const;

    /**
     * @brief Set the Distance object
     * 
     * @param dist 
     */
    void SetDistance(holo::float64_t dist);
    /**
     *
     * @brief Get the distance from current position to end fo lane
     *
     * @return holo::float64_t Distance
     */
    holo::float64_t GetDistance() const;

    /**
     * @brief Set the Lane Group Id
     *
     * @param id Lane group id
     */
    void SetLaneGroupId(holo::uint64_t const id);

    /**
     * @brief Get the Lane Group Id
     *
     * @return holo::uint64_t Lane group id
     */
    holo::uint64_t GetLaneGroupId() const noexcept;

    /**
     * @brief Set the Ptr Lane
     *
     * @param lane
     */
    void SetPtrLane(format::PtrLane lane);

    /**
     * @brief Get the Ptr Lane
     *
     * @return format::PtrLane
     */
    format::PtrLane GetPtrLane();

    /**
     * @brief Set the Is On Route object
     *
     * @param is
     */
    void SetIsOnRoute(holo::bool_t const is);

    /**
     * @brief
     *
     * @return holo::bool_t
     */
    holo::bool_t IsOnRoute() const;

    /**
     * @brief Set the Left Lane Boundary Id object
     *
     * @param lane_id
     */
    void SetLeftLaneBoundaryId(holo::uint64_t const lane_id);

    /**
     * @brief
     *
     * @return holo::uint64_t
     */
    holo::uint64_t GetLeftLaneBoundaryId() const;

    /**
     * @brief Set the Right Lane Boundary Id object
     *
     * @param lane_id
     */
    void SetRightLaneBoundaryId(holo::uint64_t const lane_id);

    /**
     * @brief
     *
     * @return holo::uint64_t
     */
    holo::uint64_t GetRightLaneBoundaryId() const;

    /**
     * @brief Set the Forward Item
     * 
     * @param item 
     */
    void SetForwardItem(LaneItemSPtrType item);

    /**
     * @brief Get the Forward Item
     *
     * @return LaneItemSPtrType
     */
    LaneItemSPtrType GetForwardItem();

    /**
     * @brief Set the Is Predicted 
     * 
     * @param is Whether or not the lane item is predicted
     */
    void SetIsPredicted(holo::bool_t is);

    /**
     * @brief Whether or not the lane item is predicted
     * 
     * @return True, is predicted; false, not predicted
     */
    holo::bool_t GetIsPredicted() const;

    /**
     * @brief Whether or not is visual item
     */ 
    void SetIsVisualItem(holo::bool_t is_visual);

    /**
     * @brief Get whether or not is visual item
     */ 
    holo::bool_t GetIsVisualItem() const;

    /**
     * @brief Set whether or not has visual item ancestor
     */ 
    void SetHasVisualItemAncestor(holo::bool_t has);

    /**
     * @brief Get whether or not has visual item ancestor
     */
    holo::bool_t GetHasVisualItemAncestor() const;

    /**
     * @brief Get how many times passed intersection 
     */ 
    holo::uint8_t GetIntersectionPassedCount() const;

public:
    /// The unique id for lane item
    holo::uint64_t lane_id_ = 0U;
    /// Wheter or not is in intersection
    IntersectionStatus intersection_status_;
    /// The length of lane
    holo::float64_t length_ = std::numeric_limits<holo::float64_t>::max();
    /// Road type
    holo::common::RoadCategory road_category_;
    ///  lane group id
    holo::uint64_t  lane_group_id_  = 0U;       
    ///  Paretn node
    LaneItemSPtrType previous_item_ = nullptr;
    /// Left lane
    holo::uint64_t left_lane_boudanry_id_ = 0U;

    holo::uint64_t right_lane_boudnary_id_ = 0U;
    /// distance
    holo::float64_t distance_ = std::numeric_limits<holo::float64_t>::max();
    /// Wheter or not on route
    holo::bool_t    in_route_       = false;
    /// Distance out of route border
    holo::float64_t out_route_dist_ = std::numeric_limits<holo::float64_t>::max();
    /// lane
    format::PtrLane lane_           = nullptr; 
    /// Index in lane path
    std::size_t index_ = std::numeric_limits<std::size_t>::max();
    /// Successive lane items
    // std::vector<LaneItemSPtrType> successive_items_;
    /// Forward lane item ahead of current item
    LaneItemSPtrType forward_item_ = nullptr;
    /// Whether or not is prediction
    holo::bool_t is_predicted_ = false;
    /// Whether or not is visual lane item
    holo::bool_t is_visual_ = false;
    /// Whether or not has visual lane item in ancestors
    holo::bool_t has_visaul_ancestor_ = false;
    /// How many go through intersection
    holo::uint8_t intersection_though_count_ = 0U;
};

class VisualLaneItem : public LaneItem
{
public:
    using VisualLaneItemSPtrType    = std::shared_ptr<VisualLaneItem>;
    using VisualLaneItemSPtrVecType = std::vector<VisualLaneItemSPtrType>;
    using GeoPointType              = holo::map::format::GeoPoint;

public:
    VisualLaneItem()          = default;
    VisualLaneItem(VisualLaneItem const&) = default;
    VisualLaneItem(VisualLaneItem&&)      = default;
    VisualLaneItem& operator=(VisualLaneItem const&) = default;
    VisualLaneItem& operator=(VisualLaneItem&&) = default;

public:
    /**
     * @brief Create a Lane Node
     *
     * @param ret Retriever for data engine
     * @param lane_id Lane id
     * @param node New lane node
     * @return holo::bool_t True, success; false, otherwise
     */
    static holo::bool_t CreateVisualItem(RetrieverSPType ret, holo::uint64_t const entry_lane_id,
                                         holo::uint64_t const intersect_link_id, holo::uint64_t const exit_lane_id,
                                         VisualLaneItemSPtrType& item);

    /**
     * @brief Create current viausl item
     * 
     */
    static holo::bool_t CreateCurrentVisualItem(RetrieverSPType ret, holo::uint64_t const entry_lane_id,
                                                holo::uint64_t const intersect_link_id,
                                                holo::uint64_t const exit_lane_id, GeoPointType const& pos,
                                                VisualLaneItemSPtrType& item);

    /**
     * @brief Create successive visual items
     */
    static holo::bool_t CreateSuccessiveVisualItems(RetrieverSPType ret, LaneItemSPtrType front, IdType const intesect_link_id,
                                IdType const exit_link_id, VisualLaneItemSPtrVecType& succ_visaul_items);

public:
    void   SetEntryLaneId(IdType const id);

    IdType GetEntryLaneId() const;

    void   SetExitLaneId(IdType const id);

    IdType GetExitLaneId() const;

    void SetVisaulCompleteLength(holo::float64_t length);

    holo::float64_t GetVisualCompleteLength() const;

    holo::float64_t GetVisualSumCost() const;

private:
    holo::bool_t calculateSumInlucdedAngles();

private:
    /// Entry lane id
    IdType entry_lane_id = 0U;
    /// Exit lane id
    IdType exit_lane_id_ = 0U;
    /// Visual length
    holo::float64_t visual_length_ = 0.0f;
    /// Sum of included angles
    holo::float64_t sum_inlucded_angles_ =std::numeric_limits<holo::float64_t>::max();
};

using LaneItemSPtrType    = std::shared_ptr<LaneItem>;
using LaneItemSPtrVecType = std::vector<LaneItemSPtrType>;
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_LANE_ITEM_H_ */
