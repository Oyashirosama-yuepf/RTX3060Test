/*!
 *  \brief interface of Data
 *  \author daizhen(daizhen@holomaitc.com)
 *  \date 2017-09-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */
#ifndef HOLO_MAP_RETRIEVER_RETRIEVER_H_
#define HOLO_MAP_RETRIEVER_RETRIEVER_H_

#include <holo/map/common/common_macro.h>
#include <holo/map/retriever/retbase.h>

namespace holo
{
namespace map
{
/**
 * @brief Fetch map data from database or memory.
 */
class Retriever : public RetBase
{
public:
    /// Prohibit default copy constructor and default constructor
    Retriever(const Retriever&) = delete;
    Retriever& operator=(const Retriever&) = delete;
    Retriever()                            = delete;

    /// Destructor
    virtual ~Retriever() = default;

    /**
     * @brief Constructor with database path.
     * 
     * @param[in] path If engine type is HOLO_NDS_DB, the path is the directory of Holo NDS datbase;
     *                 If engine type is NAVINFO_NDS_DB, the path is the config name of Navinfo SDK.
     * @param[in] et Database engine type.
     * 
     * @return Nothing.
     */
    Retriever(const char* path, const EngineType et = EngineType::ENGINE_TYPE_HOLO_NDS_DB);

    /// Clear cache
    void ClearCache();

    /**
     * @brief Get lane group and lanes by lane id at the same time.
     * 
     * @param[in] id A lane id.
     * @param[out] lane_group Lane group contained the target lane.
     * @param[out] lanes Lanes sorted by lane sequence in ascending order,
     *             if no lane in lane_group, it will be empty.
     * @return true: Success;
     *         false: An error occurs in this function.
     */
    bool GetLaneGroupAndLanesByLaneId(MapFeatureIdType const id, format::PtrLaneGroup& lane_group,
                                      std::vector<format::PtrLane>& lanes);
                                      
    /**
     * @brief Get lane group and lanes by lane group id at same time.
     * @param [in] _id lane group id.
     * @param [out] _lane_group Lane group with id is _id.
     * @param [out] _lanes Lanes of _lane_group are sorted by lane sequence in ascending order,
     *              if _lane_group hasn't lane, it will be empty.
     * @return true Success;
     *         false Failure.
     */
    bool GetLaneGroupAndLanesByLaneGroupID(const MapFeatureIdType _id, format::PtrLaneGroup& _lane_group,
                                           std::vector<format::PtrLane>& _lanes);

    /**
     * @brief Get lane, left boundary and right boundary by lane id at same time.
     * @param [in] _id Lane id.
     * @param [out] _lane Lane with id is _id.
     * @param [out] _left_boundary Left lane boundary object of _lane, if _lane hasn't left lane boundary,
     *                             it will be nullptr.
     * @param [out] _right_boundary Right lane boundary object of _lane, if _lane hasn't right lane boundary,
     *                              it will be nullptr.
     * @return true Success;
     *         false Failure.
     */
    bool GetLaneAndLaneBoundaryByLaneID(const MapFeatureIdType _id, format::PtrLane& _lane,
                                        format::PtrLaneBoundary& _left_boundary,
                                        format::PtrLaneBoundary& _right_boundary);

    /**
     * @brief Get lane group, lanes and lane boundaries by lane group id at same time.
     * @param [in] _id Lane group id.
     * @param [out] _lane_group Lane group with id is _id.
     * @param [out] _lanes Lanes of _lane_group are sorted by lane sequence in ascending order,
     *             if _lane_group hasn't lane, it will be empty.
     * @param [out] _boundaries LaneMarks of _lanes, they will sorted from left to right by lane sequence,
     *              if lane group hasn't lane, it will contain lane group left and right boundary,
     *              if lane group hasn't boundary, it will be empty.
     * @return true Success;
     *         false Failure.
     */
    bool GetLaneGroupAndLanesAndBoundariesByLaneGroupID(const MapFeatureIdType _id, format::PtrLaneGroup& _lane_group,
                                                        std::vector<format::PtrLane>&         _lanes,
                                                        std::vector<format::PtrLaneBoundary>& _boundaries);

    /**
     * @brief Get the Lane Boundary Ref Points object
     *
     * @param[in] _lane_boundary_id
     * @param[out] _ptr_ref_points
     * @return true
     * @return false
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetLaneBoundaryRefPoints(const MapFeatureIdType _lane_boundary_id, std::vector<format::GeoPoint>& _ptr_ref_points);

    /**
     * @brief Get reference points of a lane
     * @param[in] _lane_id id of the lane to be fetched
     * @param[out] _ptr_ref_points pointer of a reference point vector
     * @return true if operation succeeds.
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetLaneRefPoints(const MapFeatureIdType _lane_id, std::vector<format::GeoPoint>& _ptr_ref_points);

    /**
     * @brief get the lane boundary id included by adjacent lanes
     *
     * @param[in] _connected_lane_ids vector of adjacent lane ids
     * @param[out] _lane_boundary_id lane boundary between adjacent lanes
     * @return true: if lanes share a common lane boundary; false: otherwise
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetCommonLaneBoundary(const MapFeatureIdVectorType& _connected_lane_ids, MapFeatureIdType& _lane_boundary_id);
    /**
     * @brief get the side of lane boundary on the given lane
     *
     * @param[in] _current_lane_boundary_id lane boundary to be tested
     * @param[in] _current_lane_id current lane id
     * @param[out] _side the side of lane boundary w.r.t the lane,
     *       to be calculated inside the function
     * @return true: if lane boundary in on that lane and calculation succeeded;
     *        false: otherwise
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetSideOfLaneBoundary(const MapFeatureIdType _current_lane_boundary_id, const MapFeatureIdType _current_lane_id,
                               Direction& _side);

    // TODO(dingjing@holomatic.com): Cannot find this function in cpp.
    // /**
    //  * @brief get lane marks belonging to a set of lanes of a link
    //  *
    //  * @param[in] _link_id link id in which the parallel lane marks
    //  *       are to be retrieved
    //  * @param[out] _connected_lanemark_ids vector of lane mark id that
    //  *       belong to the lanes
    //  * @param[in] _sort_by_index whether to sort the lane marks by its
    //  *       associated index on link
    //  * @return true: if lane marks can be obtained; false: otherwise
    //  */
    // bool GetLaneMarksOnLink(const MapFeatureIdType _link_id,
    //                         MapFeatureIdVectorType& _connected_lanemark_ids,
    //                         const bool _sort_by_index = false);

    /**
     * @brief get lane mark index on link
     *
     * @param[in] _lane_boundary_id lane boundary id
     * @param[out] _index index of land boundary in the lane group
     * @return true: lane mark index id obtained; false: otherwise
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetLaneBoundaryIndexOnLaneGroup(const MapFeatureIdType _lane_boundary_id, MapFeatureIdType& _index);
    /**
     * @brief get the associated lane id of a lane boundary, given the side
     *
     * @param[in] _lane_boundary_id lane boundary id
     * @param[in] _side side of lane with respect to the lane boundary
     * @param[out] _lane_id lane id associated to the lane boundary
     * @return true: if the lane id is obtained; false: otherwise
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetLaneIdFromLaneBoundaryId(const MapFeatureIdType _lane_boundary_id, const Direction _side, MapFeatureIdType& _lane_id);
    /**
     * @brief get lanes associated to a given lane boundary
     *
     * @param[in] _lane_boundary_id lane boundary id
     * @param[out] _lanes all lanes (max. 2) that are associated
     *       to this lane boundary
     * @return true: if lanes can be found; false: otherwise
     */

    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetAdjacentLanes(const MapFeatureIdType _lane_boundary_id, std::vector<MapFeatureIdType>& _lanes);

    /**
     * @brief get the side of lane boundary on the given lane
     *
     * @param[in] _current_lane_boundary_id lane mark to be tested
     * @param[in] _current_lane current lane data
     * @param[out] _side the side of lane mark w.r.t the lane,
     *       to be calculated inside the function
     * @return true: if lanemark in on that lane and calculation succeeded;
     *        false: otherwise
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetSideOfLaneBoundary(const MapFeatureIdType _current_lane_boundary_id, const format::Lane& _current_lane,
                               Direction& _side);

    /**
     * @brief get the lane group id associated to a given lane boundary
     *
     * @param[in] _lane_boundary_id lane boundary id
     * @param[out] _lane_group_id lane group id of the lane group the lane mark belongs to
     * @return true: if lanes can be found; false: otherwise
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetLaneGroupIdFromLaneBoundaryId(const MapFeatureIdType _lane_boundary_id, MapFeatureIdType& _lane_group_id);

    /**
     * @brief Get reference points of a lane
     * @param[in] _lane_id id of the lane to be fetched
     * @param[out] _ptr_ref_points pointer of a reference point vector
     * @return true if operation succeeds.
     */

    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetRefPointsOnLane(const MapFeatureIdType _lane_id, const std::vector<format::GeoPoint>*& _ptr_ref_points);
    /**
     * @brief Get reference points of a lane boundary
     * @param[in] _lane_boundary_id id of the lane boundary to be fetched
     * @param[out] _ptr_ref_points pointer of a reference point vector
     * @return true if operation succeeds.
     */

    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetRefPointsOnLaneBoundary(const MapFeatureIdType _lane_boundary_id,
                                    const std::vector<format::GeoPoint>*& _ptr_ref_points);
    /**
     * @brief get connected lanes of a lane in an expected direction
     *
     * @param[in] _current_lane_id current lane id. We want to get its lane
     * connection.
     * @param[in] _dir the direction of the connected lanes w.r.t to the current
     * lane
     * @param[out] _connected_lane_ids connected lanes, if any
     * @return true: if the connected lanes are obtained; false: otherwise
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetConnectedLanes(const MapFeatureIdType _current_lane_id, const Direction _dir, MapFeatureIdVectorType& _connected_lane_ids);

    /**
     * @brief Get connected lanes of a lane in an expected direction.
     *
     * @details If input lane have no connected lane in expected direction and there is no other situation, return true.
     *
     * @param[in]  current_lane_id    Current lane id we want to get its lane's connection.
     * @param[in]  dir                The direction of the connected lanes w.r.t to the current lane.
     * @param[out] connected_lane_ids Connected lane ids. Empty result is normal.
     * 
     * @return true: if the connected lanes are obtained; false: otherwise
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetConnectedLanesV2(MapFeatureIdType const current_lane_id, Direction const dir, MapFeatureIdVectorType& connected_lane_ids);

    /**
     * @brief get connected lanes of some lanes in an expected direction
     *
     * @param[in] lane_ids lane ids. We want to get their lane connections.
     * @param[in] _dir the direction of the connected lanes w.r.t to the current
     * lane
     * @param[out] _connected_lane_ids connected lanes, if any
     * @return true: if the connected lanes are obtained; false: otherwise
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetConnectedLanes(const std::vector<MapFeatureIdType>& _lane_ids, const Direction _dir,
                           MapFeatureIdVectorType& _connected_lane_ids);

    /**
     * @brief Get connected lanes by lane group id. A lane group may be composed of multiple
     * lanes and each lane may have multiple connected lanes
     * @param[in] _current_lane_group_id current lane group id
     * @param[in] _dir the direction of the connected lanes w.r.t to the current
     * lane group
     * @param[out] _connected_lane_ids connected lanes, if any
     * @return true if the connected lanes are obtained; false: otherwise
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetConnectedLanesByLaneGroupId(const MapFeatureIdType _current_lane_group_id, const Direction _dir,
                                        MapFeatureIdVectorType& _connected_lane_ids);

    /**
     * @brief Access lane group ids connected with the target lane.
     * 
     * @param[in] id A target lane.
     * @param[out] preceding_ids Preceding lane groups connected with the target lane, if without preceding
     *                           lane group, the result will be empty.
     * @param[out] succeeding_ids Succeeding lane group connected with the target lane, if without succeeding
     *                            lane group, the result will be empty.
     * @return true: No error, even though preceding_ids and succeeding_ids are both empty;
     *         false: An error occurs in this function.
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetConnectedLaneGroupByLaneId(MapFeatureIdType const id, MapFeatureIdVectorType& preceding_ids, MapFeatureIdVectorType& succeeding_ids);

    /**
     * @brief Access lane group ids connected with the target lane group.
     * 
     * @param[in] id A target lane group.
     * @param[out] preceding_ids Preceding lane groups connected with the target lane group, if without preceding
     *                           lane group, the result will be empty.
     * @param[out] succeeding_ids Succeeding lane groups connected with the target lane group, if without succeeding
     *                            lane group, the result will be empty.
     * @return true: No error, even though preceding_ids and succeeding_ids are both empty;
     *         false: An error occurs in this function.
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetConnectedLaneGroupByLaneGroupId(MapFeatureIdType const id, MapFeatureIdVectorType& preceding_ids, MapFeatureIdVectorType& succeeding_ids);

    /**
     * @brief get parallel lanes on lane group
     *
     * @param[in] _lane_group_id
     * @param[out] _parallel_lane_data
     * @return true: get parallel lanes successfully; false: otherwise
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetParallelLanesOnLaneGroup(const MapFeatureIdType _lane_group_id, MapFeatureIdVectorType& _parallel_lane_data);

    /**
     * @brief Get lane group id from lane id
     *
     * @param [in] _lane_id lane id
     * @param [out] _lane_group_id lane group id
     * @return true
     * @return false
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetLaneGroupIdFromLaneId(const MapFeatureIdType _lane_id, MapFeatureIdType& _lane_group_id);

    /**
     * @brief If two lanes are in the same link
     *
     * @param [in] _lane_id1
     * @param [in] _lane_id2
     * @param [out] _if_same_lane_group
     * @return true
     * @return false
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") AreBothLanesInSameLaneGroup(const MapFeatureIdType _lane_id1, const MapFeatureIdType _lane_id2, bool& _if_same_lane_group);

    /**
     * @brief get lane marks belonging to a set of lanes
     *
     * @param[in] _lane_ids vector of lane id
     * @param[out] _connected_lane_boundary_ids vector of lane mark id that belong to
     * the lanes
     * @return true: if lane marks can be obtained; false: otherwise
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetLaneBoundariesFromLanes(const MapFeatureIdVectorType& _lane_ids, MapFeatureIdVectorType& _connected_lane_boundary_ids);
    /**
     * @brief get lane marks belonging to a set of lanes of a lane group
     *
     * @param[in] _lane_group_id lane group id in which the parallel lane marks
     *       are to be retrieved
     * @param[out] _connected_lane_boundary_ids vector of lane mark id that
     *       belong to the lanes
     * @param[in] _sort_by_index whether to sort the lane marks by its
     *       associated index on lane group
     * @return true: if lane marks can be obtained; false: otherwise
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetParallelLaneBoundariesOnLaneGroup(const MapFeatureIdType _lane_group_id, MapFeatureIdVectorType& _connected_lane_boundary_ids,
                                              const bool _sort_by_index = false);

    // /**
    //  * @brief Get ramp type in link from lane id
    //  *
    //  * @param [in] _lane_id lane id
    //  * @param [out] _ramp_type ramp type
    //  * @return true
    //  * @return false
    //  */
    // bool GetRampTypeByLaneId(const MapFeatureIdType _lane_id, Char2& _ramp_type);

    /**
     * @brief Whether a link has lanes or not
     *
     * @param [in] _link_id link id
     * @return true
     * @return false
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") HasLanes(const MapFeatureIdType _link_id);

    /**
     * @brief Check if lane is of specific type
     * @param[in] _lane_id lane id
     * @param[in] _lane_type lane type to be checked
     * @return true if this lane is of this type
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") IsLaneOfType(const MapFeatureIdType _lane_id, const format::Lane::LaneType _lane_type);

    /**
     * @brief Get lane length
     * @param[in] _lane_id lane id
     * @param[out] _length length of lane (unit: meter)
     * @return true if operation succeeded
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetLaneLength(const MapFeatureIdType _lane_id, Distance& _length);

    /**
     * @brief Get lane sequence
     *
     * @param [in] _lane_id lane id
     * @param [out] _seq lane sequence
     * @return true
     * @return false
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetLaneSeq(const MapFeatureIdType _lane_id, SeqValue& _seq);

    /**
     * @brief Get the Road Length object
     *
     * @param[in] _road_id
     * @param[out] _length
     * @return true
     * @return false
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetRoadLength(const MapFeatureIdType _road_id, Distance& _length);

    /**
     * @brief Get the lane group Length directly
     *
     * @param [in] _lane_group_id lane group id
     * @param [out] _length lane group length
     * @return true
     * @return false
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetLaneGroupLength(const MapFeatureIdType _lane_group_id, Distance& _length);

    /*
     * @brief Get the Link Length directly
     *
     * @param [in] _link_id link id
     * @param [out] _length link length
     * @return true
     * @return false
     */
    // bool GetLinkLength(const MapFeatureIdType _link_id, Distance& _length);

    /**
     * @brief Get number of lanes in lane group
     *
     * @param [in] _lane_group_id lane group id
     * @param [out] _num_lanes number of lanes
     * @return true
     * @return false
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetNumLanes(const MapFeatureIdType _lane_group_id, Size& _num_lanes);

    /**
     * @brief if trajectory existed in link
     *
     * @param[in] _link_id
     * @return true
     * @return false
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") HasTrajectory(const MapFeatureIdType _link_id);

    /**
     * @brief get position list by road id
     *
     * @param[in] _road_id road id
     * @param[out] positions vector of position which on the given road
     *
     * @return true: find success; false: otherwise
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetPositionsByRoadID(const MapFeatureIdType _road_id, ::std::vector<format::Position>& positions);

    /**
     * @brief Get connected lane groups w.r.t current lane group
     * @param[in] _current_lane_group_id current lane group id
     * @param[in] _dir direction w.r.t current lane group
     * @param[out] _connected_lane_group_ids connected lane groups to expected direction
     * to current lane group
     * @return true if we have connected lane group
     */
    bool HOLO_MAP_DEPRECATED("Has been deprecated") GetConnectedLaneGroups(const MapFeatureIdType _current_lane_group_id, const Direction _dir,
                                MapFeatureIdVectorType& _connected_lane_group_ids);

    /**
     * @brief Get the Header object
     *
     * @param[in] _header_ptr header pointer
     * @return true
     * @return false
     */
    bool GetHeader(format::PtrHeader& _header_ptr);

private:
    /**
     * @brief get the lane group id associated to a given lane mark
     *
     * @param[in] _lanemark lane mark data
     * @param[out] _lane_group_id lane group id of the lane group the lane mark belongs to
     * @return true: if lanes can be found; false: otherwise
     */
    bool Private_GetLaneGroupIdFromLaneBoundaryId(const format::LaneBoundary& _lane_boundary, MapFeatureIdType& _lane_group_id);

    void SortPairVec(std::vector<PairKeyAndInt>& _vec_of_pair);
};

typedef std::shared_ptr<Retriever> PtrRetriever;

}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_RETRIEVER_RETRIEVER_H_ */
