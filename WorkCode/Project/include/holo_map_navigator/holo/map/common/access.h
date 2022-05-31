/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file access.h
 * @brief Direct access map elements based on retriever.
 * @author daizhen(daizhen@holomaitc.com)
 * @date "2018-03-06"
 */

#ifndef _HOLO_MAP_COMMON_ACCESS_H_
#define _HOLO_MAP_COMMON_ACCESS_H_

#include <bitset>
#include <functional>

#include <holo/common/coordinate.h>
#include <holo/map/common/geometry.h>
#include <holo/map/common/common_define.h>
#include <holo/map/common/math.h>
#include <holo/map/map_enum.h>
#include <holo/map/retriever/retriever.h>
#include <holo/map/road_speed_limits.h>
/**
 * @addtogroup holo
 *
 * @{
 */
namespace holo
{
/**
 * @addtogroup map
 *
 * @{
 */
namespace map
{
/**
 * @addtogroup access
 *
 * @{
 */
namespace access
{
class AngleInfo
{
public:
    AngleInfo()
    {
        clear();
    }
    ~AngleInfo() = default;
    void clear()
    {
        is_accurate_     = false;
        height_cm_       = 0;
        slope_           = 0;
        super_elevation_ = 0;
        heading_         = 0U;
        curvature_       = 0;
    }
    void operator=(const AngleInfo& _obj)
    {
        this->is_accurate_     = _obj.is_accurate_;
        this->height_cm_       = _obj.height_cm_;
        this->slope_           = _obj.slope_;
        this->super_elevation_ = _obj.super_elevation_;
        this->heading_         = _obj.heading_;
        this->curvature_       = _obj.curvature_;
    }
    void SetDataFromPosition(const format::Position& _position, bool _is_accurate)
    {
        this->is_accurate_ = _is_accurate;
        this->height_cm_   = _position.GetHeightCm();
        this->slope_       = _position.GetSlope();
        // this->super_elevation_ = _position.GetSuperElevation();
        // this->heading_         = _position.GetHeading();
        this->curvature_ = _position.GetCurvature();
    }

public:
    bool            is_accurate_;  // whether the angle information is accurate
    ::std::int64_t  height_cm_;
    ::std::int64_t  slope_;
    ::std::int64_t  super_elevation_;
    ::std::uint64_t heading_;
    ::std::int64_t  curvature_;
};

/**
 * @brief Find the closest point on input lane around input position.
 *
 * @details The closest point is on lane's reference points.
 *
 * @param[in]  _ret         Pointer of retriever
 * @param[in]  _ori_pos     Current position
 * @param[in]  _lane_id     Lane id
 * @param[out] _closest_pos Closest point
 *
 * @return true  Operation successful.
 * @return false Otherwise.
 */
template <typename T>
bool FindClosestRefPointOnLane(const RetrieverSPType _ret, const T& _ori_pos, const IdType _lane_id,
                               format::GeoPoint& _closest_pos);

/**
 * @brief Find Z value on input lane around input position.
 *
 * @details The Z value is the closest point's Z value on lane's reference points.
 *
 * @param[in]  _ret     Pointer of retriever
 * @param[in]  _pos     Current position
 * @param[in]  _lane_id Lane id
 * @param[out] _z       Z value, unit: meter
 *
 * @return true  Operation successful.
 * @return false Otherwise.
 */
template <typename T>
bool FindClosestZ(const RetrieverSPType _ret, const T& _pos, const IdType _lane_id, double& _z);

/**
 * @brief whether the end of current lane is join
 *
 * @param[in] _lane_id current lane id
 * @param[out] _is_join wether the end of this lane is join or not
 * @return true
 * @return false
 */
bool IsLaneEndWithJoin(const RetrieverSPType _ret, const IdType _lane_id, bool& _is_join);

/**
 * @brief Check if the end of input lane is forked.
 *
 * @details "forked lane" means there are more than one connected lanes at the end of current lane
 *
 * @param[in]  _ret      Pointer of retriever
 * @param[in]  _lane_id  Lane id
 * @param[out] _is_fork  If the end of lane is forked
 *
 * @return true  Operation successful.
 * @return false Otherwise.
 */
bool IsLaneEndWithFork(const RetrieverSPType _ret, const IdType _lane_id, bool& _is_fork);

/**
 * @brief Check if the start of input lane is joined.
 *
 * @details "joined lane" means there are more than one connected lanes at the beginning of current lane
 *
 * @param[in]  _ret      Pointer of retriever
 * @param[in]  _lane_id  Lane id
 * @param[out] _is_join  If the end of lane is joined
 *
 * @return true  Operation successful.
 * @return false Otherwise.
 */
bool IsLaneStartWithJoin(const RetrieverSPType _ret, const IdType _lane_id, bool& _is_join);

/**
 * @brief Check if a lane boundary shared by two neighboring lanes
 *
 * @details Judge the lane boundary if it has both left and right lane.
 *
 * @param[in] _ret              Pointer of retriever
 * @param[in] _lane_boundary_id Lane boundary id
 *
 * @return true:  The lane boundary is shared by two lanes.
 * @return false: Otherwise.
 */
bool IsCommonLaneBoundary(const RetrieverSPType _ret, const IdType _lane_boundary_id);

/**
 * @brief Check if two lanes are connected in expected direction
 *
 * @param[in] _ret                          Pointer of retriever
 * @param[in] _lane_data_1                  One lane id
 * @param[in] _lane_data_2                  Another lane id
 * @param[in] _expected_dir_lane1_wrt_lane2 Direction of lane1 with respect to lane2, either preceding or succeeding.
 *
 * @return true:  Both lanes are connected in expected direction.
 * @return false: Otherwise.
 */
bool AreConnectedLanes(const RetrieverSPType _ret, const IdType _lane_id_1, const IdType _lane_id_2,
                       const Direction _expected_dir_lane1_wrt_lane2);

/**
 * @brief Check if two lanes are connected regardless of direction
 *
 * @param[in] _ret       Pointer of retriever
 * @param[in] _lane_id_1 One lane id
 * @param[in] _lane_id_2 Another lane id
 *
 * @return true:  Both lanes are connected.
 * @return false: Otherwise.
 */
bool AreConnectedLanes(const RetrieverSPType _ret, const IdType _lane_id_1, const IdType _lane_id_2);

/**
 * @brief Check if two lanes are connected in expected direction
 *
 * @param[in] _ret pointer of retriever
 * @param[in] _lane_data_1                  One lane
 * @param[in] _lane_data_2                  Another lane
 * @param[in] _expected_dir_lane1_wrt_lane2 Direction of lane1 with respect to lane2, either preceding or succeeding.
 *
 * @return true:  Both lanes are connected in expected direction
 * @return false: Otherwise
 */
bool AreLanesParallelInSpecificDirection(const format::Lane& _lane_data_1, const format::Lane& _lane_data_2,
                                         const Direction _expected_dir_lane1_wrt_lane2);

/**
 * @brief Check if two lane boundaries on the same side of associated lanes, respectively.
 *
 * @details Check if side of lane boundary 1 w.r.t lane 1 is same as lane boundary 2 w.r.t lane 2.
 *
 * @param[in] _ret               Pointer of retriever
 * @param[in] _lane_boundary_id1 A lane boundary id
 * @param[in] _lane_id_1         Lane data associated to lane boundary 1
 * @param[in] _lane_boundary_id2 A lane boundary id
 * @param[in] _lane_id_2         Lane data associated to lane boundary 2
 *
 * @return true:  If lane association is correct and both sides are same;
 * @return false: Otherwise
 */

// bool AreBothLaneBoundariesOnSameSide(const RetrieverSPType _ret, const IdType _lane_boundary_id1,
//                                      const IdType _lane_id1, const IdType _lane_boundary_id2,
//                                      const IdType _lane_id2);
/**
 * @brief Get left and right boundary information of a lane group.
 *
 * @details (1) Get positions of four corner points
 *          (2) Get reference points of left-most and right-most boundaries.
 *
 * @param[in]  _ret                    Pointer of retriever
 * @param[in]  _current_lanegroup_id   Lane Group id
 * @param[out] _corner_points_pos      Corner point position
 * @param[out] _left_boundary          Ref points of leftmost boundary
 * @param[out] _right_boundary         Ref points of rightmost boundary
 *
 * @return true:  Get the result successfully;
 * @return false: Otherwise
 */
bool GetLaneGroupBoundingInfo(const RetrieverSPType _ret, const IdType _current_lanegroup_id,
                              std::vector<format::GeoPoint>&          _corner_points_pos,
                              const ::std::vector<format::GeoPoint>*& _left_boundary,
                              const ::std::vector<format::GeoPoint>*& _right_boundary);

/**
 * @brief Get lane boundary information.
 *
 * @details (1) Get positions of four corner points.
 *          (2) Get contour line of current lane (composed of left and right lane boundary refpoints).
 *
 * @param[in]  _ret     Pointer of retriever
 * @param[in]  lane_id  Lane id
 * @param[out] _contour Contour line
 * @param[out] _corners Four corners of this lane
 *
 * @return true:  Get the result successfully;
 * @return false: Otherwise
 */
bool GetLaneBoundingInfo(const RetrieverSPType _ret, const IdType lane_id, VecXYH& _contour, VecXYH& _corners);

/**
 * @brief Get the connected lane boundary
 *
 * @details (1) Get connected lane boundary(boundaries) in specified direction.
 *          (2) Get the most straight one in these boundaries
 *
 * @param[in]  _ret                                 Pointer of retriever
 * @param[in]  _current_lane_boundary_id            Lane boundary id
 * @param[in]  _direction                           Direction of the lane boundary to be calculated
 *                                                  with respect to the current lane boundary
 * @param[out] _connected_lane_boundary_ids         Connected lane boundaries in specified direction
 * @param[out] _straight_connected_lane_boundary_id Straightly connected lane boundary in specified direction,
 *                                                  as to Roadmap requirement
 *
 * @return true:  Get the result successfully;
 * @return false: Otherwise
 */
bool FindConnectedLaneBoundaries(const RetrieverSPType _ret, const IdType _current_lane_boundary_id,
                                 const Direction _direction, VecIdType& _connected_lane_boundary_ids,
                                 IdType& _straight_connected_lane_boundary_id);

/**
 * @brief Get all the lanes with same lane group id by a lane id.
 *
 * @detail All the lanes will be sorted by lane sequence by increasing order.
 * @param[in] ret A handle of database engine.
 * @param[in] id The target lane id.
 * @param[out] lanes All the lanes are adjacent to the target lane in the
 *                   horizontal direction.
 * @param[in] enable_empty true: if the lanes is empty, the return is true;
 *                          false: if the lanes is empty, the return is false.
 * @return true: No error.
 *         false: An error occurs in this function.
 */
bool GetSortedLanesByLaneId(RetrieverSPType const ret, IdType const id, std::vector<format::PtrLane>& lanes,
                            bool const enable_empty = false);

/**
 * @brief Get all the lanes with same lane group id by a lane id.
 *
 * @detail All the lanes will be sorted by lane sequence by increasing order and
 *         return the target lane index in the output container.
 * @param[in] ret A handle of database engine.
 * @param[in] id The target lane id.
 * @param[out] lanes All the lanes are adjacent to the target lane in the
 *                   horizontal direction.
 * @param[out] index The index of target lane in the output container.
 * @param[in] enable_empty true: if the lanes is empty, the return is true;
 *                         false: if the lanes is empty, the return is false;
 * @return true: No error.
 *         false: An error occurs in this function.
 */
bool GetSortedLanesByLaneIdWithIndex(RetrieverSPType const ret, IdType const id, std::vector<format::PtrLane>& lanes,
                                     std::size_t& index, bool const enable_empty = false);

/**
 * @brief Get all the lanes with same lane group id.
 *
 * @detail All the lanes will be sorted by lane sequence by increasing order.
 * @param[in] ret A handle of database engine.
 * @param[in] id The group lane id.
 * @param[out] lanes All the lanes in the target lane group.
 * @param[in] enable_empty true: if the lanes is empty, the return is true;
 *                         false: if the lanes is empty, the return is false;
 * @return true: No error.
 *         false: An error occurs in this function.
 */
bool GetSortedLanesByLaneGroupId(RetrieverSPType const ret, IdType const id, std::vector<format::PtrLane>& lanes,
                                 bool const enable_empty = false);

/**
 * @brief Get succeeding lane sequence
 *
 * @details Get sequence of current lane's succeeding lanes.
 *
 * @param[in]  _ret          Pointer of retriever
 * @param[in]  _lane_id      Lane id
 * @param[in]  _succ_lane_id Succeeding lane id
 * @param[out] _seq          Succeeding lane's sequence for this lane
 *
 * @return true:  Get the result successfully;
 * @return false: Otherwise
 */
bool GetSuccLaneSeq(const RetrieverSPType _ret, const IdType _lane_id, const IdType _succ_lane_id,
                    ::std::int32_t& _seq);

/**
 * @brief Get preceeding lane sequence
 *
 * @details Get sequence of current lane's preceeding lanes.
 *
 * @param[in]  _ret         Pointer of retriever
 * @param[in]  _lane_id     Lane id
 * @param[in]  _pre_lane_id Preceeding lane id
 * @param[out] _seq         Preceeding lane's sequence
 *
 * @return true:  Get the result successfully
 * @return false: Otherwise
 */
bool GetPreLaneSeq(const RetrieverSPType _ret, const IdType _lane_id, const IdType _pre_lane_id,
                   ::std::int32_t& _seq);

/**
 * @brief Check if two lane groups are fully connected.
 *
 * @details It means all lanes of first lane group have connections to the lanes of second lane group.
 *
 * @param[in]  _ret                 Pointer of retriever
 * @param[in]  _lanegroup_id1       First lane group id
 * @param[in]  _lanegroup_id2       Second lane group id
 * @param[out] _are_fully_connected true: Fully connected
 *                                  false: Otherwise
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool AreTwoLaneGroupsFullyConnected(const RetrieverSPType _ret, const IdType _lanegroup_id1,
                                    const IdType _lanegroup_id2, bool& _are_fully_connected);

/**
 * @brief Whether or not the current lane is an emergency lane.
 *
 * @param[in] ret The handle of database engine.
 * @param[in] id Target lane id.
 * @param[out] result If true, the current lane is an emergency lane;
 *                    If false, otherwise.
 * @return true: No error.
 *         false: An error occurs in this function.
 */
bool IsEmergencyLane(RetrieverSPType const ret, IdType const id, bool& result);

/**
 * @brief Whether or not the current lane is a hard shoulder.
 *
 * @note The hard shoulder lane is the leftmost lane in a lane group, the width
 *       is less than 2.0 meters in general(Just in china).
 * @param[in] ret The handle of database engine.
 * @param[in] id Target lane id.
 * @param[out] result If true, the current lane is a hardshoulder lane;
 *                    If false, otherwise.
 * @return true: No error.
 *         false: An error occurs in this function.
 */
bool IsHardShoulderLane(RetrieverSPType const ret, IdType const id, bool& result);

/**
 * @brief Check if the current lane group's type is ramp type.
 *
 * @param[in]  _ret          Pointer of retriever
 * @param[in]  _lanegroup_id Lane group id
 * @param[out] _is_ramp      true: Current lane group's type is ramp;
 *                           false: Current lane group's type is not ramp;
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool IsLaneRamp(const RetrieverSPType _ret, const IdType _lanegroup_id, bool& _is_ramp);

/**
 * @brief Check if the current lane group is high way.
 *
 * @param[in]  _ret          Pointer of retriever
 * @param[in]  _lanegroup_id Lane group id
 * @param[out] _is_highway   true: Current lane group is highway;
 *                           false: Current lane group is not highway;
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool IsHighWay(const RetrieverSPType _ret, const IdType _lanegroup_id, bool& _is_highway);

/**
 * @brief Check if the current lane group is a toll booth.
 *
 * @param[in]  ret           Pointer of retriever
 * @param[in]  lane_group_id A lane group id.
 * @param[out] result If true, the road is a toll booth;
 *                    If false, the road is not a toll booth.
 *
 * @return true: No error.
 *         false: An error occurs in this function and the result is invalid.
 */
bool IsTollBoothByLaneGroupId(RetrieverSPType const ret, IdType const lane_group_id, bool& result);

/**
 * @brief Check if the current lane group is a toll booth.
 *
 * @param[in] ret The handle of database engine.
 * @param[in] lane_group A lane group object.
 * @param[out] result If true, the road is a toll booth;
 *                    If false, the road is not a toll booth.
 *
 * @return true: No error.
 *         false: An error occurs in this function and the result is invalid.
 */
bool IsTollBoothByLaneGroup(RetrieverSPType const ret, format::PtrLaneGroup const lane_group, bool& result);

/**
 * @brief Whether or not the target road is a toll booth.
 *
 * @param[in] ret The handle of database engine.
 * @param[in] road_t A road id.
 * @param[out] result If true, the road is a toll booth;
 *                    If false, the road is not a toll booth.
 *
 * @return true: No error.
 *         false: An error occurs in this function and the result is invalid.
 */
bool IsTollBoothByRoadId(RetrieverSPType const ret, IdType const road_id, bool& result);

/**
 * @brief Whether or not the target road is a toll booth.
 *
 * @param[in] road A road object from database engine.
 * @param[out] result If true, the road is a toll booth;
 *                    If false, the road is not a toll booth.
 *
 * @return true: No error.
 *         false: An error occurs in this function and the result is invalid.
 */
bool IsTollBoothByRoad(format::PtrRoad const road, bool& result);

// /**
//  * @brief Check if current lane has virtual lane boundary.
//  *
//  * @details (1) Only left lane boundary is virtual;
//  *          (2) Only right lane boundary is virtual;
//  *          (3) Both left and right lane boundaries are virtual.
//  *
//  * @param[in]  _ret             Pointer of retriever
//  * @param[in]  _lane_id         Lane id
//  * @param[out] _are_virtual_lbs true: The current lane has virtual lane boundary
//  *                              false: Otherwise
//  *
//  * @return true:  Operation successful
//  * @return false: Otherwise
//  */
// bool AreVirtualLaneboundaries(const RetrieverSPType _ret, const IdType _lane_id, bool& _are_virtual_lbs);

/**
 * @brief Get the right-most lane
 *
 * @details (1) The right-most lane is in current lane's lane group.
 *          (2) The right-most lane is not emergency stop lane
 *
 * @param[in]  _ret                Pointer of retriever
 * @param[in]  _current_lane_id    Current lane id
 * @param[out] _right_most_lane_id Rightmost lane id
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool GetRightMostLaneByLaneId(const RetrieverSPType _ret, const IdType _current_lane_id,
                              IdType& _right_most_lane_id);

/**
 * @brief Get a parallel lane in same lane group by horizontal shift
 *
 * @details _shift value: 0 -- keep current lane;
 *                        -1, -2... : shift to left,
 *                        +1, +2... : shift to right
 *
 * @param[in]  _ret              Pointer of retriever
 * @param[in]  _current_lane_id  Current lane id
 * @param[in]  _shift            Parallel lane shift
 * @param[out] _resulted_lane_id Lane id with given shift at the same lane group
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool GetParallelLaneByShift(const RetrieverSPType _ret, const IdType _current_lane_id, const int _shift,
                            IdType& _resulted_lane_id);

/**
 * @brief Get all parallel lanes of current lane's lane group (include current lane)
 *
 * @param[in]  _ret                Pointer of retriever
 * @param[in]  _current_lane_id    Current lane id
 * @param[out] _parallel_lane_data All parallel lanes' id including input lane id
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool GetLanesOnSameLaneGroup(const RetrieverSPType _ret, const IdType _current_lane_id,
                             VecIdType& _parallel_lane_data);

/**
 * @brief Get right-most or left-most lane of specific type.
 *
 * @param[in]  _ret                   Pointer of retriever
 * @param[in]  _current_lanegroup_id  Current lane group id
 * @param[in]  _right_most            True is for right-most one;
 *                                    Flase is for left-most one;
 * @param[in]  _lane_type             Expected lane type
 * @param[out] _expected_lane_id      Lane id to be fetched
 *
 * @return Feedback::OK : Operation successful
 *         Others:        Otherwise
 */
Feedback GetSpecificLaneOnLaneGroup(const RetrieverSPType _ret, const IdType _current_lanegroup_id,
                                    const bool _right_most, const format::Lane::LaneType _lane_type,
                                    IdType& _expected_lane_id);
/**
 * @brief Get a point on lane's reference points by specific index
 *
 * @param[in]  _ret     Pointer of retriever
 * @param[in]  _lane_id Lane id
 * @param[in]  _idx     Index of reference point
 * @param[out] _pos     The reference point
 *
 * @return Feedback::OK : Operation successful
 *         Others:        Otherwise
 */
Feedback GetRefPointOfLaneByIndex(const RetrieverSPType _ret, const IdType _lane_id, const long long _idx,
                                  MapPoint3& _pos);

/**
 * @brief Get a point on a lane by distance from lane head
 *
 * @details (1) If distance is longer than lane's length, the output point is lane's last point,
 *          remaining distance is over the length of this lane;
 *          (2) If distance is shorter than lane's length, the output point is on the lane,
 *          remaining distance is to the end of the lane.
 *
 *
 * @param[in]  _ret                      Pointer of retriever
 * @param[in]  _lane_id                  Lane id
 * @param[in]  _dist_from_lane_beginning Distance of point from lane head
 * @param[out] _pos                      Calculated position associated to the distance
 * @param[out] _remaining_distance       Remaining distance
 *
 * @return Feedback::OK : Operation successful
 *         Others:        Otherwise
 */
Feedback GetPointOnLaneByDistance(const RetrieverSPType _ret, const IdType _lane_id,
                                  const Distance _dist_from_lane_beginning, MapPoint3& _pos,
                                  Distance& _remaining_distance);

/**
 * @brief Get the most straight connected lane boundary in specified direction.
 *
 * @param[in]  _ret                       Pointer of retriever
 * @param[in]  _lane_boundary_id          Lane boundary id
 * @param[out] _straight_lane_boundary_id The most straight lane boundary
 * @param[in]  preceding                  true: Preceding;
 *                                        false: Succeeding;
 * @param[in]  index
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool GetStraightLaneBoundaryId(const RetrieverSPType _ret, const IdType _lane_boundary_id,
                               IdType& _straight_boundary_id, const bool preceding = true, const int index = 2);

/**
 * @brief Get lane group reference points.
 *
 * @details Lane group's reference points is its middle line or one lane's reference points in this lane group.
 *          Calculate its middle line by the leftmost and rightmost laneboundaries.
 *
 * @param[in]  _ret           Pointer of retriever
 * @param[in]  _lane_group_id Lane group id
 * @param[out] _ref_points    Vector of reference points
 * @param[in]  _on_middle     true: Get middle line.
 *                            false: Get a lane's reference points in this lane group.
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool GetLaneGroupRefPoints(const RetrieverSPType _ret, const IdType _lanegroup_id,
                           std::vector<format::GeoPoint>& _ref_points, const bool _on_middle = true);

/**
 * @brief Get lane group reference points.
 *
 * @details Lane group's reference points is its middle line or one lane's reference points in this lane group.
 *          Calculate its middle line by the leftmost and rightmost laneboundaries.
 *
 * @param[in]  _ret           Pointer of retriever
 * @param[in]  _lane_group_id Lane group id
 * @param[out] _ref_points    Vector of reference points
 * @param[in]  _on_middle     true: Get middle line.
 *                            false: Get a lane's reference points in this lane group.
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool GetLaneRefPoints(const RetrieverSPType _ret, const IdType lane_id,
                      std::vector<format::GeoPoint>& _ref_points);

/**
 * @brief Get middle line of current lane
 *
 * @param[in]  _ret        Pointer of retriever
 * @param[in]  _lane_id    Lane id
 * @param[out] _ref_points Vector of middle line's points
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool GetMiddleLineByLaneId(const RetrieverSPType _ret, const IdType _lane_id,
                           std::vector<format::GeoPoint>& _ref_points);

/**
 * @brief Get lane group width
 *
 * @param[in]  _ret     Pointer of retriever
 * @param[in]  _lane_group_id Lane group id
 * @param[out] _width   Lane group width(Unit: meters)
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool GetLaneGroupWidth(const RetrieverSPType _ret, const IdType _lanegroup_id, Distance& _width);

/**
 * @brief Access lane width by lane id.
 *
 * @param[in]  _ret Map database engine.
 * @param[in]  _lane_id Lane id.
 * @param[out] _width Unit: meters, If width value is invalid(<=0), this function will return false.
 *
 * @return true: Operation successful.
 * @return false: An error occors in this function.
 */
bool GetLaneWidth(const RetrieverSPType _ret, const IdType _lane_id, Distance& _width);

/**
 * @brief Get road ref points
 *
 * @details (1) If current id is lane id; Get this lane's reference points;
 *          (2) If lane has no reference points, get points as middle line of lane;
 *          (3) If current id is lane group id, get points as middle line of lane group.
 *
 * @param[in]  _ret        Pointer of retriever
 * @param[in]  _id         Lane or lane group id
 * @param[in]  _is_lane_id true: lane id
 *                         false: lane group id
 * @param[out] _points     Expected refpoints
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool GetRoadRefPoints(const RetrieverSPType _ret, const IdType _id, const bool _is_lane_id,
                      std::vector<format::GeoPoint>& _points);

/**
 * @brief Check if two lane groups are connected
 *
 * @details (1) If the direction is DIR_SUCCEEDING, lane group id2 is the succeeding lane group of lane group id1;
 *          (2) If the direction is DIR_PRECEEDING, lane group id2 is the preceeding lane group of lane group id2;
 *          (3) Otherwise, check connectivity regardless of direction
 *
 * @param[in] _lane_group_id1 lane group id1
 * @param[in] _lane_group_id2 lane group id2
 * @param[in] _dir            Direction
 *
 * @return true:  Two lane group are connected in specified direction.
 * @return false: Two lane group are not connected in specified direction.
 */
bool AreConnectedLaneGroups(const RetrieverSPType _ret, const IdType _lanegroup_id1, const IdType _lanegroup_id2,
                            const Direction _dir = Direction::UNKNOWN);

/**
 * @brief Get direct connected lane groups (stop searching if furcation occurs) by
 *        look ahead distance
 *
 * @details (1) If the direction is DIR_SUCCEEDING, search in succeeding direction
 *          (2) If the direction is DIR_PRECEDING, search in preceeding direction
 *
 * @param[in] _ret           Pointer of retriever
 * @param[in] _lane_group_id Start lane group id
 * @param[in] _min_length    Look ahead distance
 * @param[in] _dir           Direction
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool GetDirectConnectedLaneGroupsByLength(const RetrieverSPType _ret, const IdType _lanegroup_id,
                                          const Distance _min_length, std::vector<IdType>& _vec_lanegroup_ids,
                                          const Direction _dir = Direction::DIR_SUCCEEDING);

/**
 * @brief Get lane groups between start id and end id
 *
 * @param[in]  _ptr_ret        Pointer of retriever
 * @param[in]  _start_id       Start lane group id
 * @param[in]  _end_id         End lane group id
 * @param[out] _lane_group_ids Lane group ids between start lane group id and end lane group id
 * @param[in]  max_search_num  Max search number of lane group ids
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool GetLaneGroupsInBetween(const RetrieverSPType _ptr_ret, const IdType _start_id, const IdType _end_id,
                            std::vector<IdType>& _lanegroups_ids, const int max_search_num = 10);

// /**
//  * @brief Get the angle information of the given point
//  *
//  * @param [in] _lane_group_id lane group id
//  * @param [in] _target the given point
//  * @param [out] _angle_info the angle info of the given point
//  * @return true find success
//  * @return false no angle information
//  */
// template <typename T>
// bool GetAngleInformation2D(const RetrieverSPType _ptr_ret, const IdType _lane_group_id, const T& _target,
//                            AngleInfo& _angle_info);

/**
 * @brief Get speed limit for lane group
 *
 * @details The maximum speed limit is the lanes' maximum speed limit in current lane group
 *          The minimum speed limit is the lanes' minimum speed limit in current lane group
 *
 * @param[in] _ptr_ret         Pointer of retriever
 * @param[in] _lane_group_id   Lane group id
 * @param[in] _max_speed_limit Max speed limit for lane group
 * @param[in] _min_speed_limit Min speed limit for lane group
 *
 * @return true:  Operation successful
 * @return false: Otherwise
 */
bool GetLaneGroupSpeedLimit(const RetrieverSPType _ptr_ret, const IdType _lanegroup_id, double& _max_speed_limit,
                            double& _min_speed_limit);

/**
 * @brief Get trajectory by lane or lane group id
 *
 * @param[in]  _ptr_ret Pointer of retriever
 * @param[in]  _id      Lane or lane group id
 * @param[in]  _is_lane true: lane id
 *                      false: lane group id
 * @param[out] _points  Corresponding trajectory points
 *
 * @return true:  Operation successful
 * @return false: Otherwise. Maybe the number of trajectory is not 1 in lane/lane group.
 */
// bool GetTrajectoryById(const RetrieverSPType _ptr_ret, const IdType _id, const bool _is_lane,
//                        std::vector<MapPoint3>& _points);

/**
 * @brief Describe the space attribute of a lane in a lane group.
 */
enum class LaneAdjacentType : uint8_t
{
    LAT_NONE                    = 0x00,       ///< Placeholder.
    LAT_LEFT_MOST_LANE          = 0x01 << 0,  ///< The leftmost lane in a lane group.
    LAT_RIGHT_MOST_LANE         = 0x01 << 1,  ///< The rightmost lane in a lane group.
    LAT_MIDDLE_NON_DRIVING_LANE = 0x01 << 2,  ///< The middle lane which disable driving.
    LAT_MIDDLE_DRIVING_LANE     = 0X01 << 3,  ///< The middle lane which enable driving.
    LAT_LEFT_MOST_DRIVING_LANE  = 0X01 << 4,  ///< The leftmost driving lane.
    LAT_RIGHT_MOST_DRIVING_LANE = 0X01 << 5,  ///< The rightmost driving lane.
};

/**
 * @brief Get the adjacent type from a target lane.
 *
 * @param[in] ret The handle of database engine.
 * @param[in] id Target lane id.
 * @param[out] type The space attribute of the target lane.
 * @return true: No error.
 *         false: An error occurs in this function.
 */
bool GetLaneAdjacentType(RetrieverSPType const ret, IdType const id, LaneAdjacentType& type);

/**
 * @brief Whether or not the target lane is an auto driving lane.
 *
 * @param[in] lane A lane object.
 * @return true: Enable auto driving;
 *         false: otherwise.
 */
bool IsAutoDrivingLane(format::PtrLane const lane);

/**
 * @brief Whether or not the target lane ia an auto driving lane.
 *
 * @param[in] ret A handle of map database engine.
 * @param[in] id Target lane id.
 * @param[out] result true: Target lane is an auto driving lane.
 *                    false: Otherwise.
 * @return true: No error;
 *         false: An error occurs in this function.
 */
bool IsAutoDrivingLane(RetrieverSPType const ret, IdType const id, bool& result);

/**
 * @brief Get Auto-Driving Lanes In a LaneGroup
 *
 * @param[in] ret           Pointer of retriever
 * @param[in] lane_group_id Lane Group id.
 * @param[out] lane_ids     Auto-Driving Lanes
 * @param[in] with_emergency_lane If has emergency lane
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
bool GetDrivingLanes(RetrieverSPType const ret, IdType const lane_group_id, VecIdType& lane_ids,
                     bool const with_emergency_lane = true);

/**
 * @brief Get Auto-Driving Lanes In a LaneGroup
 *
 * @param[in] ret           Pointer of retriever
 * @param[in] lane_group_id Lane Group id.
 * @param[out] ptr_lanes    Auto-Driving Lanes pointers.
 * @param[in] with_emergency_lane If has emergency lane
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
bool GetDrivingLanes(RetrieverSPType const ret, IdType const lane_group_id, std::vector<format::PtrLane>& ptr_lanes,
                     bool const with_emergency_lane = true);

/**
 * @brief Whether or not the target lane is the leftmost lane in a lane group.
 *
 * @param[in] ret The handle of database engine.
 * @param[in] id Target lane id.
 * @param[out] result true: Target lane is the leftmost lane.
 *                    false: Ohterwise.
 * @return true: No error;
 *         false: An error occurs in this function.
 */
bool IsLeftMostLane(RetrieverSPType const ret, IdType const id, bool& result);

/**
 * @brief Whether or not the target lane is the rightmost lane in a lane group.
 *
 * @param[in] ret The handle of database engine.
 * @param[in] id Target lane id.
 * @param[out] result true: Target lane is the rightmost lane.
 *                    false: Ohterwise.
 * @return true: No error;
 *         false: An error occurs in this function.
 */
bool IsRightMostLane(RetrieverSPType const ret, IdType const id, bool& result);

/**
 * @brief Whether or not the target lane is the leftmost driving lane in a lane group.
 *
 * @param[in] ret The handle of database engine.
 * @param[in] id Target lane id.
 * @param[out] result true: Target lane is the leftmost driving lane.
 *                    false: Ohterwise.
 * @return true: No error;
 *         false: An error occurs in this function.
 */
bool IsLeftMostDrivingLane(RetrieverSPType const ret, IdType const id, bool& result);

/**
 * @brief Whether or not the target lane is the rightmost lane in a lane group.
 *
 * @param[in] ret The handle of database engine.
 * @param[in] id Target lane id.
 * @param[out] result true: Target lane is the rightmost driving lane.
 *                    false: Ohterwise.
 * @return true: No error;
 *         false: An error occurs in this function.
 */
bool IsRightMostDrivingLane(RetrieverSPType const ret, IdType const id, bool& result);

/**
 * @brief Get specific line length.
 *
 * @details Input line's id and type to get length.
 *
 * @param[in]  _ptr_ret Pointer of retriever
 * @param[in]  _id      Line id
 * @param[in]  _type    Line type 0->lane;
 *                                1->lane boundary;
 *                                2->lane group.
 * @param[out] _length  Line length
 *
 * @return true:  Operation successful
 * @return false: Otherwise.
 */
bool GetLineLengthByIdAndType(const RetrieverSPType _ptr_ret, const IdType _id, const int _type, Distance& _length);

/**
 * @brief Calculate distance from specific line head.
 *
 * @tparam MapPoint, MapPoint3, GeoPoint
 *
 * @param[in]  _ret       Pointer of retriever
 * @param[in]  _line_id   Line id
 * @param[in]  _line_type Line type 0->lane;
 *                                  1->lane boundary;
 *                                  2->lane group.
 * @param[in]  _pos       Current position
 * @param[out] _dist      Distance
 *
 * @return Feedback::OK : Operation successful
 *         Others:        Otherwise
 */
template <typename T>
map::Feedback CalculateDistanceToLineHeadById(const RetrieverSPType _ret, const IdType _line_id, const int _line_type,
                                              const T& _pos, Distance& _dist);

/**
 * @brief Get specific point on lane group by given distance from lane group head
 *
 * @details If this lane group cannot cover the expected position, position is the last point on current lane group,
 *          remaining distance = _dist_from_lane_beginning - current lane group length
 *
 * @param[in]  _ret                      Pointer of retriever
 * @param[in]  _lane_group_id                  Current lane group id
 * @param[in]  _dist_from_lane_beginning Expcted distance from lane group head
 * @param[out] _pos                      Resulted position
 * @param[out] _remaining_distance       Remaining distance
 *
 * @return Feedback::OK : Operation successful
 *         Others:        Otherwise
 */
template <typename T>
map::Feedback GetPointOnLaneGroupByDistance(const RetrieverSPType _ret, const IdType _lanegroup_id,
                                            const Distance _dist_from_lane_beginning, T& _pos,
                                            Distance& _remaining_distance);

/// TODO:jiangdianqin@holomatic.com 
/// remove all tile related and object releated functions
/// related function all moved to map local service module
/**
 * @brief Inquiry objects by geo info robustly;
 *
 * @details Get all objects in tile of inputing point.
 *
 * @param[in]  _ret     Pointer of retriever
 * @param[in]  _point   GeoPoint
 * @param[out] _objects Objects
 *
 * @return true:  Operation successful, if no object in GeoCircle, _objects will be empty.
 * @return false: An error occors in this function.
 */
// bool InquiryObjectGeoRobust(const RetrieverSPType _ptr_ret, const format::GeoPoint& _point,
//                             ::std::vector<format::ObjectInfo>& _objects);

/**
 * @brief Inquiry objects in specific 2D area
 *
 * @tparam T GeoCircle
 *
 * @param[in] _ptr_ret Pointer of retriever
 * @param[in] _scale   GeoCircle, extent of the inquiry
 * @param[in] _objects Objects
 *
 * @return true:  Operation successful, if no object in GeoCircle, _objects will be empty.
 * @return false: An error occors in this function.
 */
// template <typename T>
// bool InquiryObjectGeoExact2D(const RetrieverSPType _ptr_ret, const T& _geo_extent,
//                              ::std::vector<format::ObjectInfo>& _objects);

/**
 * @brief Fetch objects from map database engine by a specific 2D scope.
 *
 * @tparam T GeoCircle.
 *
 * @param[in] ret A handle of map database engine.
 * @param[in] extent A specific area used to filter object.
 * @param[in] coord Coordinate reference system of the specific 'extent'.
 * @param[out] objects Objects falling in the specific area.
 * @return true: No error even though the output is emtpy;
 *      false: An error occurs in this function.
 */
// template <typename T>
// bool InquiryObjectGeoExact2DV2(RetrieverSPType const ret, T const& extent, holo::common::Coordinate const& coord,
//                                std::vector<format::ObjectInfo>& objects);

/**
 * @brief Inquiry objects in specific 3D area
 *
 * @tparam T GeoCircle
 *
 * @param[in]  _ptr_ret    Pointer of retriever
 * @param[in]  _geo_extent GeoCircle, query scope.
 * @param[out] _objects    Objects
 * @param[in]  _min_height Minimum height to filter, unit cm
 * @param[in]  _max_height Maximum height to filter, unit cm
 *
 * @return true:  Operation successful, if no object in GeoCircle, _objects will be empty
 * @return false: An error occurs in this function.
 */
// template <typename T>
// bool InquiryObjectGeoExact3D(const RetrieverSPType _ptr_ret, const T& _geo_extent,
//                              ::std::vector<format::ObjectInfo>& _objects, const double _min_height,
//                              const double _max_height);

/**
 * @brief Fetch objects from map database engine by a specific 3D area.
 *
 * @tparam T GeoCircle.
 *
 * @param[in] ret A handle of map database engin.
 * @param[in] extent A specific area used to filter object.
 * @param[in] coord Coordinate reference system of the specific 'extent'.
 * @param[out] objects Objects falling in the specific area.
 * @param[in] min_height The minimum height filter(Unit: centermeter).
 * @param[in] max_height The maximum height filter(Unit: centermeter).
 * @return true: No error even though the output is empty;
 *         false: An error occurs in this function.
 */
// template <typename T>
// bool InquiryObjectGeoExact3DV2(RetrieverSPType const ret, T const& extent, holo::common::Coordinate const& coord,
//                                std::vector<format::ObjectInfo>& objects, double const min_height,
//                                double const max_height);

/**
 * @brief Check if an object is in specified circle
 *
 * @param[in] _object Object
 * @param[in] _circle Specified scope
 *
 * @return true:  The object is in this scope.
 * @return false: The object is not in this scope.
 */
// bool IsObjectInScale2D(const format::ObjectInfo& _object, const format::GeoCircle& _circle);

// /**
//  * @brief check if the object is covered by the box
//  *
//  * @param[in] _object object
//  * @param[in] _box box, extent of the judgement
//  * @return true
//  * @return false
//  */
// bool IsObjectInScale2D(const format::Object& _object,
// 							  const format::GeoBox& _box);

/**
 * @brief Check if the object is in this height scope.
 *
 * @param[in] _object     Object
 * @param[in] _min_height Minimum height to filter object,unit cm
 * @param[in] _max_height Maximum height to filter object,unit cm
 *
 * @return true  The object is in this scope.
 * @return false The object is not in this scope.
 */
// bool FilterObjectByHeight(const format::ObjectInfo& _object, const double _min_height, const double _max_height);

/**
 * @brief Get all tile ids on map
 *
 * @param[in]  _ret      Pointer of retriever
 * @param[out] _tile_ids All tile ids
 *
 * @return true:  Operation successful.
 * @return false: Otherwise
 */
// bool GetAllTileIdsOnMap(const RetrieverSPType _ret, std::vector<IdType>& _tile_ids);

/**
 * @brief Get all road ids on map
 *
 * @param[in]  _ret      Pointer of retriever
 * @param[out] _road_ids All road ids
 *
 * @return true:  Operation successful.
 * @return false: Otherwise
 */
//bool GetAllRoadIdsOnMap(const RetrieverSPType _ret, std::vector<IdType>& _road_ids);

/**
 * @brief Get all lane group ids on map
 *
 * @param[in]  _ret      Pointer of retriever
 * @param[out] _lane_group_ids All lane group ids
 *
 * @return true:  Operation successful.
 * @return false: Otherwise
 */
//bool GetAllLaneGroupIdsOnMap(const RetrieverSPType _ret, std::vector<IdType>& _lanegroup_ids);

/**
 * @brief Get all lane ids on map
 *
 * @param[in]  _ret      Pointer of retriever
 * @param[out] _lane_ids All lane ids
 *
 * @return true:  Operation successful.
 * @return false: Otherwise
 */
//bool GetAllLaneIdsOnMap(const RetrieverSPType _ret, std::vector<IdType>& _lane_ids);

/**
 * @brief Get all object ids on map
 *
 * @param[in]  _ret        Pointer of retriever
 * @param[out] _object_ids All object ids
 *
 * @return true:  Operation successful.
 * @return false: Otherwise
 */
//bool GetAllObjectIdsOnMap(const RetrieverSPType _ret, std::vector<IdType>& _object_ids);

/**
 * @brief Get all trajectory ids on map
 *
 * @param[in]  _ret            Pointer of retriever
 * @param[out] _trajectory_ids All trajectory ids
 *
 * @return true:  Operation successful.
 * @return false: Otherwise
 */
//bool GetAllTrajectoryIdsOnMap(const RetrieverSPType _ret, std::vector<IdType>& _trajectory_ids);

/**
 * @brief Get all Lane boundary ids on map
 *
 * @param[in]  _ret               Pointer of retriever
 * @param[out] _lane_boundary_ids Lane boundary ids
 *
 * @return true:  Operation successful.
 * @return false: Otherwise
 */
//bool GetAllLaneBoundaryIdsOnMap(const RetrieverSPType _ret, std::vector<IdType>& _lane_boundary_ids);

/**
 * @brief Get lane group ids in specified scope
 *
 * @details If tile cross through the scope, all lane groups of this tile will be added
 *
 * @tparam T GeoCircle/GeoBox/GeoPoint
 *
 * @param[in]  _ret        Pointer of retriever
 * @param[in]  _geo_extent Specified scope
 * @param[out] _lane_group_ids   lane group ids
 *
 * @return true:  Operation successful.
 * @return false: Otherwise
 */
// template <typename T>
// bool GetLaneGroupIdsInScope(const RetrieverSPType _ret, const T& _geo_extent, std::vector<IdType>& _lanegroup_ids);

/**
 * @brief Get lane groups in specified scope.
 *
 * @details If a lane group cross through the scope, it will be added.
 * @note If no lane group in tile, this function will return false.
 *
 * @tparam T GeoPoint/MapPoint3/MapPoint
 *
 * @param[in]  ret      Pointer of retriever.
 * @param[in]  tile_id  Target tile id.
 * @param[in]  point    Center point of target scope.
 * @param[in]  range    Range of target scope from center point.
 * @param[out] lane_group_ids Output lane groups in the target scope, if no lane group in
 *                            target tile, it's invalid.
 *
 * @return true:  Target tile has lane groups in target scope;
 *         false: Target tile doesn't has lane group in target scope.
 */
// template <typename T>
// bool GetLaneGroupIdsInScope(RetrieverSPType const ret, IdType const tile_id, T const& _point, Distance const range,
//                             std::vector<IdType>& lanegroup_ids);

/**
 * @brief Get lane groups in specified scope.
 *
 * @details If a lane group cross through the scope, it will be added.
 * @note If no lane group in tile, this function will return true.
 *
 * @tparam T GeoPoint/MapPoint3/MapPoint
 *
 * @param[in]  ret      Pointer of retriever.
 * @param[in]  tile_id  Target tile id.
 * @param[in]  point    Center point of target scope.
 * @param[in]  range    Range of target scope from center point.
 * @param[out] lane_group_ids Output lane groups in the target scope, if no lane group in
 *                            target tile, it will be empty.
 *
 * @return true:  No error, even though no lane group in target tile;
 *         false: An error occurs in this function.
 */
// template <typename T>
// bool GetLaneGroupIdsInScopeV2(RetrieverSPType const ret, IdType const tile_id, T const& point, Distance const range,
//                               std::vector<IdType>& lanegroup_ids);

/**
 * @brief Get tile ids in specified scope(with WGS84-UTM Zone 50N).
 *
 * @details If tile cross through the scope, this tile will be added
 *
 * @tparam T GeoCircle/GeoBox/GeoPoint
 *
 * @param[in]  _ret        Pointer of retriever
 * @param[in]  _geo_extent Specified scope
 * @param[out] _tile_ids   Tile ids
 *
 * @return true:  There are tiles in target scope.
 * @return false: Otherwise
 */
// template <typename T>
// bool GetTileIdsInScope(const RetrieverSPType _ret, const T& _geo_extent, std::vector<IdType>& _tile_ids);

/**
 * @brief GetCalculate tile ids by a special scope(with WGS84)
 *
 * @details If tile cross through the scope, this tile will be added
 *
 * @tparam T GeoCircle/GeoBox/GeoPoint
 *
 * @param[in]  ret Handle of database engine.
 * @param[in]  geo_extent Specified scope with coordinate reference system of WGS84.
 * @param[out] tile_ids Tile covered by the special spope.
 * @return true: No error.
 *         false: An error occors in this function.
 */
// template <typename T>
// bool GetTileIdsInScopeByLonLat(RetrieverSPType const ret, T const& geo_extent, std::vector<IdType>& tile_ids);

/**
 * @brief Calculate tile ids by a special scope(within UTM).
 *
 * @details If a tile cross through the scope, this tile will be added.
 *
 * @tparam T GeoCircle/GeoBox/GeoPoint
 *
 * @param[in] ret Handle of database engine.*
 * @param[in] geo_extent Specified scope with coordinate reference system of UTM.
 * @param[in] zone_id A zone id within UTM.
 * @param[in] south_flag true: in the southern hemispherr, false: in the northern hemispherr.
 * @param[out] tile_ids Tile covered by the special spope.
 * @return true: No error.
 *         false: An error occors in this function.
 */
// template <typename T>
// bool GetTileIdsInScopeByUTM(RetrieverSPType const ret, T const& geo_extent, CoordinateUtmZoneType const zone_id,
//                             holo::bool_t const south_flag, std::vector<IdType>& tile_ids);

/**
 * @brief Get lane ids in specified scope
 *
 * @details If tile cross through the scope, all lanes of this tile will be added
 *
 * @tparam T GeoCircle/GeoBox/GeoPoint
 *
 * @param[in]  _ret        Pointer of retriever
 * @param[in]  _geo_extent Specified scope
 * @param[out] _lane_ids   Lane ids
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
// template <typename T>
// bool GetLaneIdsInScope(const RetrieverSPType _ret, const T& _geo_extent, std::vector<IdType>& _lane_ids);

/**
 * @brief Get lane groups in a circled scope
 *
 * @param[in]  _ret        Pointer of retriever
 * @param[in]  _cp         Center of circle
 * @param[in]  _radius     Radius, unit: meter
 * @param[out] _lanegroups Lane group ids around the given point
 *
 * @return true:  Operation successful. There are lane groups in this scope.
 * @return false: Otherwise.
 */
// template <typename T>
// bool GetLaneGroupsAroundPoint(const RetrieverSPType _ret, const T& _cp, const Distance _radius,
//                               VecIdType& _lanegroups);

/**
 * @brief Get closest lane group to a given point
 *
 * @param[in]  _ret          Pointer of retriever
 * @param[in]  _cp           Center of circle
 * @param[in]  _max_radius   Radius, unit: meter
 * @param[out] _lanegroup_id Closest lane group id
 *
 * @return true:  Found a valid lane group;
 * @return false: Otherwise.
 */
// template <typename T>
// bool GetClosestLaneGroup(const RetrieverSPType _ret, const T& _cp, const Distance _max_radius, IdType& _lanegroup_id);

/**
 * @brief Get all lane group ids of all input lanes
 *
 * @param[in]  _ret           Pointer of retriever
 * @param[in]  _lane_ids      Lane ids
 * @param[out] _lanegroup_ids Lane group ids
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
bool GetLaneGroupIdsByLaneIds(const RetrieverSPType _ret, const VecIdType& _lane_ids, VecIdType& _lanegroup_ids);

/**
 * @brief Get the n-th lowest index-on-lane group lane boundary from given lane boundary ids
 *
 * @param[in]  _ret               Pointer of retriever
 * @param[in]  _lane_boundary_ids Lane boundary ids
 * @param[in]  _n                 N-th lowest index-on-lane group lane boundary, n begins with 0
 * @param[out] _lane_boundary_id  N-th lane boundary.
 *
 * @return true:  Found a valid lane boundary id
 * @return false: Otherwise.
 */
bool GetNthLowestIndexLaneBoundary(const RetrieverSPType _ret, const ::holo::map::VecIdType& _lane_boundary_ids,
                                   const ::holo::map::IdType _n, const bool _invert,
                                   ::holo::map::IdType& _lane_boundary_id);

/**
 * @brief Get the minimum index-on-lane group lane boundary from given lane boundary ids
 *
 * @param[in] _ret               Pointer of retriever
 * @param[in] _lane_boundary_ids Lane boundary ids
 * @param[out] _lane_boundary_id Minimum index-on-lane group lane boundary
 *
 * @return true:  Found a valid lane boundary id
 * @return false: Otherwise.
 */
bool GetMinIndexLaneBoundary(const RetrieverSPType _ret, const ::holo::map::VecIdType& _lane_boundary_ids,
                             ::holo::map::IdType& _lane_boundary_id);

/**
 * @brief Get the maximum index-on-lane group lane boundary from given lane boundary ids
 *
 * @param[in]  _ret               Pointer of retriever
 * @param[in]  _lane_boundary_ids Lane boundary ids
 * @param[out] _lane_boundary_id  Maximum index-on-lane group lane boundary
 *
 * @return true:  Found a valid lane boundary id
 * @return false: Otherwise.
 */
bool GetMaxIndexLaneBoundary(const RetrieverSPType _ret, const ::holo::map::VecIdType& _lane_boundary_ids,
                             ::holo::map::IdType& _lane_boundary_id);

/**
 * @brief Get minimum/maximum index-on-lane group lane boundary from succeeding lane boundaries.
 *
 * @param[in]  _ptr_ret              Pointer of retriever
 * @param[in]  _lane_ids             Lane ids
 * @param[in]  _current_lane_boundary_id Current lane boundary
 * @param[in]  _invert               True means get succeeding maximum index-on-lane group, vice versa
 * @param[out] _succ_lane_boundary_id    Succeeding minimum/maximum index-on-lane group lane boundary.
 *
 * @return true:  Found a valid lane boundary id
 * @return false: Otherwise.
 */
bool GetSuccMinIndexLaneBoundary(const RetrieverSPType _ptr_ret, const ::holo::map::VecIdType& _lane_ids,
                                 const ::holo::map::IdType _current_lane_boundary_id, const bool _invert,
                                 ::holo::map::IdType& _succ_lane_boundary_id);

/**
 * @brief Get a lane group by a specified height
 *
 * @details The input lane groups have different heights(e.g. overpasses).
 *          Function choose a lane group containing current height.
 *
 * @param[in]  _ptr_ret  Pointer of retriever
 * @param[in]  _height   Height of current location, unit: cm
 * @param[in]  _lanegroup_ids Vector of lane group ids
 * @param[out] _lanegroup_id  Current lane group id.
 *
 * @return true:  Found a valid lane group id
 * @return false: Otherwise.
 */
bool GetLaneGroupIDByHeight(const RetrieverSPType _ptr_ret, const ::holo::int64_t _height,
                            const ::holo::map::VecIdType& _lanegroup_ids, ::holo::map::IdType& _lanegroup_id);

/// TODO:jiangdianqin@holomatic.com 
/// remove all tile related and object releated functions
/// related function all moved to map local service module
/**
 * @brief Filter objects by types
 *
 * @param[in]  _objects        All objects that need to be filtered
 * @param[in]  _object_types   Keep objects belonging to these types
 * @param[out] _filter_objects Objects after filtering
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
// bool GetObjectsByObjectType(const std::vector<format::ObjectInfo>&      _objects,
//                             const std::vector<::holo::map::ObjectType>& _object_types,
//                             std::vector<format::ObjectInfo>&            _filter_objects);

/**
 * @brief Get objects from many objects by object marking type
 *
 * @param[in]  _objects        All objects that need to be filtered
 * @param[in]  _object_type    Keep objects belonging to these types
 * @param[out] _filter_objects Objects after filtering
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
#if 0  // TODO: Closed by wanghaiyang 2020/03/09, because holo_base/map will be redesigned
       // adn new types of Data has not been merged.
bool GetObjectsByMarkingType(const std::vector<format::ObjectInfo>&             objects,
                             const std::vector<::holo::map::ObjectMarkingType>& marking_types,
                             std::vector<format::ObjectInfo>&                   filter_objects);
#endif
/**
 * @brief Filter out objects not belonging to current lane group
 *
 * @param[in]  _objects        All objects that need to be filtered
 * @param[in]  _road_id        Current road id
 * @param[out] _output_objects Objects after filtering
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
// bool GetObjectsByRoadId(const std::vector<format::ObjectInfo>& _objects, const holo::map::IdType _road_id,
//                         std::vector<format::ObjectInfo>& _output_objects);

/**
 * @brief Translate a enum from holo::map to holo::base
 *
 * @param[in] _type Lane type
 *
 * @return Translated enum
 */
holo::map::CommonLaneType ConvertLaneType(const format::Lane::LaneType _type);
/**
 * @brief Translate a enum from holo::map to holo::base
 *
 * @param[in] _type Mark type
 *
 * @return Translated enum
 */
holo::map::CommonMarkType ConvertMarkType(const format::LaneBoundaryElement::BoundaryType _type);
/**
 * @brief Translate a enum from holo::map to holo::base
 *
 * @param[in] _color Mark color
 *
 * @return Translated enum
 */
holo::map::CommonMarkColor ConvertMarkColor(const format::LaneBoundaryElement::BoundaryColor _color);
/**
 * @brief Translate a enum from holo::map to holo::base
 *
 * @param[in] _material Mark material
 *
 * @return Translated enum
 */
holo::map::CommonMarkMaterial ConvertMarMaterial(const format::LaneBoundaryElement::BoundaryMaterial _material);

// /**
//  * @brief Translate a enum from holo::map to holo::base
//  *
//  * @param[in] _rdm Common Rhombus Deceleration Marking
//  *
//  * @return Translated enum
//  */
// holo::map::CommonRhombusDecelerationMarking ConvertRDMarking(const format::LaneMark::RhombusDecelerationMarking
// _rdm);

/**
 * @brief Get the list of a parking space convex in clockwise (or anti-clockwise)
 *
 * @details Result points be sorted by angle w.r.t the centroid(anticlockwise)
 *          [0]  entrance   [3]
 *           |               |
 *           |       P       |
 *           |               |
 *          [1]_____________[2]
 *
 * @param[in]  _ptr_ret    Pointer of retriever
 * @param[in]  _ps_id      Parking space id
 * @param[out] _vec_points List of convex
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
template <typename T>
bool GetVertexListByParkingSpaceId(const RetrieverSPType _ptr_ret, const IdType _ps_id,
                                   ::std::vector<T>& _vec_points);

/**
 * @brief Get the Tiles cover the specified range
 *
 * @tparam T GeoBox/GeoCircle/GeoPoint
 *
 * @param[in]  _geo_extent The specified range
 * @param[out] _tile_ids   Tile ids
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
// template <typename T>
// bool GetTiles(const T& _geo_extent, ::std::vector<IdType>& _tile_ids);

/// TODO:jiangdianqin@holomatic.com 
/// remove all parking related functions
/// related function all moved to map local service module

/**
 * @brief Get the list of a parking space convex and accessible line.
 *
 * @details Given a parking space id, get the list of convex in clockwise (or
 *          anti-clockwise). Also, output the indices of accessible line terminals in
 *          this list. For example, a parking space is composed of 4 terminals.
 *          Output can be 1, 2, which means that point 1 and 2 are terminals of
 *          accessible parking space mark
 *
 * @tparam T MapPoint/MapPoint3/GeoPoint
 *
 * @param[in]  _ptr_ret    Pointer of retriever
 * @param[in]  _ps_id      Parking space id
 * @param[out] _vec_points List of parking space convex
 * @param[out] _index_p0   A terminal of accessible line
 * @param[out] _index_p1   The other terminal of accessible line
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
// template <typename T>
// bool GetParkingSpaceAccessDirectionById(const RetrieverSPType _ptr_ret, const IdType _ps_id,
//                                         ::std::vector<T>& _vec_points, Size& _index_p0, Size& _index_p1);

/**
 * @brief Get lane boundary length
 *
 * @param[in]  _lane_boundary_id Lane boundary id
 * @param[out] _length           Length of lane boundary, unit: meter
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
bool GetLaneBoundaryLength(const RetrieverSPType _ptr_ret, const IdType _lane_boundary_id, Distance& _length);

/// TODO:jiangdianqin@holomatic.com 
/// remove all parking related functions
/// related function all moved to map local service module

/**
 * @brief Calculate surface parameters according to points of ground
 *
 * @details Formula: @f$a0+ a1x + a2x^2 + a3xy + a4y + a5y^2 = z@f$.
 *
 * @param[in]  _points             All ground points
 * @param[out] _surface_parameters 6 parameters for surface
 * @param[out] result_mean         All z - z' mean
 * @param[out] result_variance     All z - z' variance
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
// bool CalculateSurface(const VecXYH& _points, std::vector<holo::float64_t>& _surface_parameters, float64_t& _result_mean,
//                       float64_t& _result_variance);

/**
 * @brief Calculate surface parameters according to points of ground
 *
 * @details Choose some points randomly many times and calculate parameters.
 *          Choose the best result.
 *
 * @details Formula: @f$a0+ a1x + a2x^2 + a3xy + a4y + a5y^2 = z@f$.
 *
 * @param[in]  _points             All ground points
 * @param[out] _surface_parameters 6 parameters for surface
 * @param[out] _result_mean        All z - z' mean
 * @param[out] _result_variance    All z - z' variance
 * @param[in]  _run_num            Random number of calculations
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
// bool CalculateSurfaceByNum(const VecXYH& _points, std::vector<holo::float64_t>& _surface_parameters,
//                           float64_t& _result_mean, float64_t& _result_variance, const Size _run_num = 5);

/// TODO:jiangdianqin@holomatic.com 
/// remove all parking related functions
/// related function all moved to map local service module

/**
 * @brief Get all ground points
 *
 * @param[in]  _ret           Pointer of retriever
 * @param[out] _ground_points All ground points
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
// bool GetAllGroundPoints(const RetrieverSPType _ret, VecXYH& _ground_points);

enum class AccessedLinkTypes : ::holo::uint8_t
{
    kError = 0,
    kRamp,
    kRoundaboutRoad,
    kParallel,
    KServiceRoad,
    KMainRoad,
    KSquare,
    KPedestrianZone,
    KPedestrian,
    KRoundaboutInterior,
    KSlipRoad,
    KSpecialTraficFigure,
    KBoundary,
    kFuncClass1,
    kFuncClass2,
    kFuncClass3,
    kFuncClass4,
    kFuncClass5,
    kFuncClass11,
    kLast
};

static const std::size_t NumAccessedLinkTypes = static_cast<std::size_t>(AccessedLinkTypes::kLast);

/// TODO:jiangdianqin@holomatic.com 
/// remove all tile related and object releated functions
/// related function all moved to map local service module
/**
 * @brief Get all lane groups with specific type from given tiles
 *
 * @param[in]  _ret           Pointer of retriever
 * @param[in]  _tile_ids      Vector of tile id
 * @param[in]  _type          AccessedLinkTypes
 * @param[out] _lanegroup_ids Vector of lane group of specified type
 *
 * @return true:  Operation successful. The result is not empty.
 * @return false: Otherwise.
 */
// bool GetAllLaneGroupsByType(const RetrieverSPType _ret, const VecIdType& _tile_ids, const AccessedLinkTypes _type,
//                             VecIdType& _lanegroup_ids);

/**
 * @brief Check if the lane group is a specific type.
 *
 * @param[in] _ret  Pointer of retriever
 * @param[in] _id   Lane group id
 * @param[in] _type Expected lane group type
 *
 * @return true:  This lane group is specified type.
 * @return false: Otherwise.
 */
bool IsLaneGroupOfType(const RetrieverSPType _ret, const IdType _id, const AccessedLinkTypes _type);

/**
 * @brief Get properties of given lane group
 *
 * @param[in] _ret Pointer of retriever
 * @param[in] _id  Lane group id
 *
 * @return A bitset with each bit index associated with AccessedLinkTypes
 */
std::bitset<NumAccessedLinkTypes> GetLaneGroupPropertiesAsBitset(const RetrieverSPType _ret, const IdType _id);

/**
 * @brief Definitions for ramp type.
 */
enum class AccessRampType : ::holo::uint8_t
{
    RAMP_TYPE_NOT_ATTRIBUTED = 0,  ///< If a road with type of motorway, it shounld be without ramp type.
    RAMP_TYPE_JCT            = 1,  ///< A road connected with motorway and motorway.
    RAMP_TYPE_ENTRANCE_RAMP  = 2,  ///< A road connected from a ramp to a motorway.
    RAMP_TYPE_EXIT_RAMP      = 3,  ///< A road connected fromt a motorway to a ramp.
    RAMP_TYPE_SPLITED_RAMP   = 4,  ///< A ramp raod splited to two ramp roads.
    RAMP_TYPE_MERGED_RAMP    = 5,  ///< A ramp raod merged from two ramp raods.
    RAMP_TYPE_UNDEFINED      = 6   ///< Placeholder.
};

/**
 * @brief Get ramp type from given lane group.
 *
 * @param[in] _ret Database engine.
 * @param[in] _lane_group A lane group object.
 * @param[out] type The ramp type of target lane group.
 *
 * @return true: No error.
 *         false: An error occurs in this function.
 */
bool GetLaneGroupRampType(RetrieverSPType const _ret, format::PtrLaneGroup const _lane_group, AccessRampType& type);

/**
 * @brief Get speed limit of lane by current position
 *
 * @param[in] ptr_lane   Input lane.
 * @param[in] point      Current position
 * @param[out] min_speed Pointer of retriever
 * @param[out] max_speed Lane id
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
bool GetLaneSpeedLimitByPosition(const format::PtrLane& ptr_lane, const format::GeoPoint& point,
                                 std::uint32_t& min_speed, std::uint32_t& max_speed);

/**
 * @brief Get Boundary element geometry points
 *
 * @param[in] ptr_ret      Pointer of retriever
 * @param[in] boundary_ele Laneboundary element
 * @param[out] geo_points  Boundary element geometry points
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
bool GetBoundaryElementGeometryPoints(const RetrieverSPType ptr_ret, const format::LaneBoundaryElement& boundary_ele,
                                      std::vector<format::GeoPoint>& geo_points);

/**
 * @brief Get approximate lane boundary info index from a complex lane boundary object for a Road, LaneGroup or Lane.
 *
 * @detail Reference: https://wiki.holomatic.cn/pages/viewpage.action?pageId=56757646
 *
 * @param[in] lb A laneBoundary object.
 * @param[out] info_index Index of LaneBoundaryInfo in LaneBoudary, ref points are calculated from this
 * LaneBoundaryInfo.
 * @param[out] has_lane_boundary If no lane boundary in LaneBoundary, it will be false and this function returns ture,
 *                               otherwise will be true.
 * @param[in] lane_boundary_direction A LaneBoundary with several sorted LaneBoundaryInfos(Sorted from right to left in
 * China), lane_boundary_direction is used to find the real lane boundary info. if the LaneBoundary on the left of
 * target road/lane/lanegroup, the direction is DIR_LEFT, if the LaneBoundary on the right of target
 * road/lane/lanegroup, the direction is DIR_RIGHT.
 * @param[in] driving_direction Driving direction.
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
bool GetApproximateLaneBoundaryInfoIndex(
    const format::LaneBoundary& lb, std::size_t& info_index, bool& has_lane_boundary,
    const Direction        lane_boundary_direction,
    const DrivingDirection driving_direction = DrivingDirection::DRIVING_DIR_RIGHT_HAND);
/**
 * @brief Check if a lane boundary element has an actual sign on the ground.
 * @details If the type of given lane boundary element belong to the following types, this function will retrun true:
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_LONG_DASHED_LINE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_DOUBLE_SOLID_LINE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_SINGLE_SOLID_LINE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_SOLID_LINE_DASHED_LINE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_DASHED_LINE_SOLID_LINE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_SHORT_DASHED_LINE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_SHADED_AREA_MARKING
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_DASHED_BLOCKS
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_DOUBLE_DASHED_LINE
 *
 * @param[in] element Given lane boundary element.
 * @return True if given lane boundary element has an actual sign on the ground,
 *         False if not.
 */
bool IsRealLaneBoundaryElement(format::LaneBoundaryElement const& element);

/**
 * @brief Check if a lane boundary element is general lane boundary element.
 * @details If the type of given lane boundary element belong to the following types, this function will retrun true:
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_LONG_DASHED_LINE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_DOUBLE_SOLID_LINE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_SINGLE_SOLID_LINE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_SOLID_LINE_DASHED_LINE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_DASHED_LINE_SOLID_LINE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_SHORT_DASHED_LINE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_SHADED_AREA_MARKING
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_DASHED_BLOCKS
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_DOUBLE_DASHED_LINE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_CROSSING_ALERT
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_CURB
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_WALL_FLAT
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_WALL_TUNNEL
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_BARRIER_JERSEY
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_BARRIER_SOUND
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_BARRIER_CABLE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_GUARDRAIL
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_FENCE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_CURB_TRAVERSABLE
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_END_OF_ROAD
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_CLIFF
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_DITCH
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_GORE
 *
 *
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_OTHER_BARRIER
 *              format::LaneBoundaryElement::BoundaryType::BOUNDARY_TYPE_NO_MARKING
 *
 * @param[in] element Given lane boundary element.
 * @return True if given lane boundary element is general lane boundary element,
 *         False if not.
 */
bool IsGeneralLaneBoundaryElement(format::LaneBoundaryElement const& element);

/**
 * @brief Find closest specific lane boundary info identified by its lane boundary elements.
 *
 * @param[in] infos Given lane boundary info vector to get result lane boundary info from.
 * @param[out] index Index of result lane boundary info in given lane boundary info vector.
 *                   If not found, this 'index' will be std::numeric_limits<std::size_t>::max() and is_get_result will
 * be False.
 * @param[out] is_get_result If result lane boundary info found, it will be True, else it will be false.
 * @param[in] lane_boundary_side A LaneBoundary with several sorted LaneBoundaryInfos(Sorted from right to left in
 * China), if the LaneBoundary on the left of target road/lane/lanegroup, the direction is DIR_LEFT, if the LaneBoundary
 * on the right of target road/lane/lanegroup, the direction is DIR_RIGHT.
 * @param[in] driving_direction Driving direction.
 * @param[in] is_specific Function pointer provided by user to identify the specific lane boundary info by useing its
 * input parameter.
 *
 * @return true:  Operation successful. index will be valid value, is_get_result will be true.
 * @return false: If error occurred, index will be std::numeric_limits<std::size_t>::max(), is_get_result will be false.
 */
bool FindSpecificClosestLaneBoundaryInfo(
    std::vector<format::LaneBoundaryInfo> const& infos, std::size_t& index, bool& is_get_result,
    Direction const lane_boundary_side, DrivingDirection const driving_direction,
    std::function<bool(format::LaneBoundaryElement const&)> const& is_specific = IsRealLaneBoundaryElement);

/**
 * @brief Get approximate ref points from a complex lane boundary object for a Road, LaneGroup or Lane.
 *
 * @detail Reference: https://wiki.holomatic.cn/pages/viewpage.action?pageId=56757646
 *
 * @param[in] lb A laneBoundary object.
 * @param[out] points Ref points in a lane boundary of Road, LaneGroup, Lane.
 * @param[out] info_index Index of LaneBoundaryInfo in LaneBoudary, ref points are calculated from this
 LaneBoundaryInfo.
 * @param[out] has_lane_boundary If no lane boundary in LaneBoundary, it will be false and this function returns ture,
 *                               otherwise will be true.
 * @param[in] lane_boundary_direction A LaneBoundary with several sorted LaneBoundaryInfos(Sorted from right to left in
 China),
 *                                    lane_boundary_direction is used to find the real lane boundary info.
 *                                    if the LaneBoundary on the left of target road/lane/lanegroup, the direction is
 DIR_LEFT,
 *                                    if the LaneBoundary on the right of target road/lane/lanegroup, the direction is
 DIR_RIGHT.
 *
 * @param[in] is_specific Function pointer provided by user to identify the specific lane boundary info
 *                        (use this lane boundary info to calculate ref points what we want) by useing its input
 parameter.
 * @param[in] driving_direction Driving direction.

 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
bool GetApproximateLaneBoundaryGeometryPoints(
    const format::LaneBoundary& lb, std::vector<format::GeoPoint>& points, std::size_t& info_index,
    bool& has_lane_boundary, const Direction lane_boundary_direction,
    const std::function<bool(const format::LaneBoundaryElement&)>& is_specific = IsRealLaneBoundaryElement,
    const DrivingDirection driving_direction = DrivingDirection::DRIVING_DIR_RIGHT_HAND);
};  // namespace access
/**
 * @}
 */
}  // namespace map
/**
 * @}
 */
}  // namespace holo
/**
 * @}
 */

#endif /* HOLO_MAP_COMMON_GEOMETRY_H_ */
