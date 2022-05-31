/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file router.h
 * @brief router.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-26"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_ROUTER_ROUTER_H_
#define HOLO_MAP_SERVICE_CLIENT_ROUTER_ROUTER_H_

#include <memory>

#include <holo/common/odometry.h>
#include <holo/map/format/navigation/routing_path.h>
#include <holo/map/format/navigation/routing_path_element.h>
#include <holo/map/service/client/engine/retriever.h>
#include <holo/map/service/client/profile/base.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace router
{

/**
 * @addtogroup router
 * @{
 *
 */

class SegmentIterator;

class Router
{
public:
    using RetrieverSPtrType                 = holo::map::service::client::engine::RetrieverSPtrType;
    using LocalMapOdometryType              = holo::common::LocalMapOdometryd;
    using DistanceCMType                    = holo::uint32_t;
    using BidirectionalDistanceCmType       = holo::int32_t;

    /**
     * @brief Constructor.
     * 
     * @return Nothing.
     */
    Router();

    /**
     * @brief Destructor.
     * 
     * @return Nothing.
     */
    virtual ~Router();

    /**
     * @brief Access verbose message flag(Default: false).
     * 
     * @return true: Print debug message to log;
     *         false: Do not print debug message.
     */
    holo::bool_t GetVerbose() const noexcept;

    /**
     * @brief Assign verbose message flag.
     * 
     * @param[in] true: Open debug message.
     *            false: Close debug message.
     */
    void SetVerbose(holo::bool_t const v) const;

    /**
     * @brief Set the offset distance of explore road on the path.
     * 
     * @param[in] offset A offset distance, default is 1000*100, Unit:cm.
     */
    void SetOffset(DistanceCMType const offset);

    /**
     * @brief Init the router.
     * 
     * @param[in] ret A database engine.
     * @return true: Init successfully without any error;
     *         false: Otherwise.
     */
    holo::bool_t Init(RetrieverSPtrType ret);

    /**
     * @brief Find the first segment iterator by local odometry.
     * 
     * @param[in] odo A local map odometry.
     * @return A router segment iterator.
     */
    SegmentIterator find(LocalMapOdometryType const& odo);

    /**
     * @brief Get the end segment iterator.
     * 
     * @return A router segment iterator.
     */
    static SegmentIterator const& cend();

    /**
     * @brief Find the segment iterator by index.
     * 
     * @param[in] index A index of the segment on router.
     * @param[out] segment A router segment iterator.
     * @return true: find successfully without any error;
     *         false: Otherwise.
     */
    holo::bool_t find(std::size_t const index, SegmentIterator& segment);

    /**
     * @brief Print debug info.
     */
    void PrintStatus();

private:
    class RouterInner;
    std::unique_ptr<RouterInner> inner_;

    /// Unit: cm
    DistanceCMType required_remind_distance_ = 1000 * 100;
}; ///< End of class Router.

using RouterSPtrType = std::shared_ptr<Router>;
using RouterCSPtrType = std::shared_ptr<Router const>;

class SegmentIterator
{
public:
    using DistanceCMType                    = holo::uint32_t;
    using BidirectionalDistanceCmType       = holo::int32_t;
    using ProfileIdType                     = holo::map::service::client::profile::ProfileIdType;
    using ProfileIdVectorType               = holo::map::service::client::profile::ProfileIdVectorType;
    
    friend class Router;   
    
    /**
     * @brief Constructor.
     * 
     * @return Nothing.
     */
    SegmentIterator();

    /**
     * @brief Constructor.
     * 
     * @param[in] id: A group id.
     * @param[in] end: A end flag to record the iterator.
     *                 If true: end iterator; false: not end iterator.
     * 
     * @return Nothing.
     */
    SegmentIterator(ProfileIdType const id, holo::bool_t const end);

    /**
     * @brief Destructor.
     * 
     * @return Nothing.
     */
    virtual ~SegmentIterator() = default;

    SegmentIterator& GetNextByTargetId(ProfileIdType const id);

    /**
     * @brief  Increament operator.
     *
     * @return iterator pointing to current segment iterator.
     */
    SegmentIterator& operator ++ ();

    /**
     * @brief  Check if two iterators are equal.
     *
     * @tparam InputConst Whether input iterator is a const iterator.
     * @param other The input iterator.
     *
     * @return Whether the two iterators are pointing to the same segment iterator.
     */
    holo::bool_t operator == (SegmentIterator const& r) const;

    /**
     * @brief  Check if two iterators are not equal.
     *
     * @tparam InputConst Whether input iterator is a const iterator.
     * @param r The input iterator.
     *
     * @return Whether the two iterators are pointing to different segment iterator.
     */
    holo::bool_t operator != (SegmentIterator const& r) const;

    /**
     * @brief Dereferencing operator
     *
     * @return Reference to the segment iterator pointed by this iterator.
     */
    SegmentIterator& operator * ();

    /**
     * @brief Check segment is on main path or not on.
     *
     * @return true: on main path.
     *         false: not on main ptah. it on the branch path.
     */
    holo::bool_t IsOnManiPath() const;

    /**
     * @brief Access path id of the segment.
     *
     * @return Path id.
     *
     */
    ProfileIdType GetPathId() const;

    /**
     * @brief Access group id.
     *
     * @return Group id of segment.
     *
     */
    ProfileIdType GetGroupId() const;

    /**
     * @brief Access default next group id on the path.
     *
     * @return Next group id of segment.
     *
     */
    ProfileIdType GetDefaultNextGroupId() const;

    /**
     * @brief Access next group ids of segment.
     *
     * @return Group ids.
     *
     */
    ProfileIdVectorType const & GetNextGroupIds() const;

    /**
     * @brief Check current segment has branch path or not.
     *
     * @return true: has branch path.
     *         false: not has branch path.
     *
     */
    holo::bool_t HasBranchPath() const;

    /**
     * @brief Access the segment length, unit:cm.
     *
     * @return Length of segment.
     *
     */
    DistanceCMType GetLengthCm() const;
    
    /**
     * @brief Access distance from current segment to start pos, unit:cm.
     *
     * @return Distance from current segment to start pos.
     *
     */
    DistanceCMType GetDistanceToStartCm() const;

    /**
     * @brief Access Manhattan distance from current position to start point of this segment alone the path, unit:cm.
     *
     * @return A manhattan distance.
     *
     */
    BidirectionalDistanceCmType GetDistanceCmToSegmentStart() const;

    /**
     * @brief Access Manhattan distance from current position to end point of this segment alone the path, unit:cm.
     *
     * @return A manhattan distance.
     *
     */
    BidirectionalDistanceCmType GetDistanceCmToSegmentEnd() const;

    /**
     * @brief Judge current segment whether is on the navigation path.
     *
     * @return true: A navigation segment.
     *         false: Not a navigation segment.
     *
     */
    holo::bool_t IsNavigationSegment() const;

    /**
     * @brief Judge current segment whether is start of the navigation path.
     *
     * @return true: A start navigation segment.
     *         false: Not a start navigation segment.
     *
     */
    holo::bool_t IsStartNavigationSegment() const;

    /**
     * @brief Judge current segment whether is end of the navigation path.
     *
     * @return true: An end navigation segment.
     *         false: Not an end navigation segment.
     *
     */
    holo::bool_t IsEndNavigationSegment() const;

    /**
     * @brief Judge current segment whether is entry routing edge.
     *
     * @return true: An entry routing edge.
     *         false: Not an entry routing edge.
     *
     */
    holo::bool_t IsEntryRoutingEdgeSegment() const;
    
    /**
     * @brief Judge current segment whether is exit routing edge.
     *
     * @return true: An exit routing edge.
     *         false: Not an exit routing edge.
     *
     */
    holo::bool_t IsExitRoutingEdgeSegment() const;
private:
    using IndexType      = std::size_t;
    using RouterPtrType  = Router*;

    /// The index of the Route.
    IndexType index_ = 0;
    /// A point of Router for make data.
    RouterPtrType router_;
    /// A end flag to record the iterator.
    /// If true: end iterator; false: not end iterator.
    holo::bool_t end_flag_ = true; 

    /// A flag of group is on main path or not.
    /// If true: on main path, false: not on main path.
    holo::bool_t on_main_path_ = true;
    /// Routing path id.
    ProfileIdType routing_path_id_ = 0;
    /// Group Id.
    ProfileIdType group_id_ = 0;
    /// The default next id on path.
    ProfileIdType default_next_id_ = 0;
    /// Succedd ids
    ProfileIdVectorType next_ids_;
    /// A flag to record if has 
    holo::bool_t has_branch_path_ = false;
    /// Unit: cm.
    DistanceCMType length_cm_ = 0;
    /// Distance from the head of group to the odomenty along the shape point. Unit: cm.
    DistanceCMType distance_to_start_cm_ = 0;
    /// The index of path elements.
    ProfileIdType start_elemnet_index_ = 0;

    /// Distance from current position to the start point of this segment along routing path, uint: cm.
    BidirectionalDistanceCmType distance_to_segment_start_cm_ = 0;

    /// Distance from current position to the end point of this segment along routing path, uint: cm.
    BidirectionalDistanceCmType distance_to_segment_end_cm_ = 0;

    holo::bool_t is_navigation_segment_ = false;

    holo::bool_t is_start_navigation_segment_ = false;

    holo::bool_t is_end_navigation_segment_ = false;

    holo::bool_t is_entry_routing_edge_segment = false;

    holo::bool_t is_exit_routing_edge_segment = false;
};

/**
 * @}
 *
 */

} ///< namespace router
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_ROUTER_ROUTER_H_ */
