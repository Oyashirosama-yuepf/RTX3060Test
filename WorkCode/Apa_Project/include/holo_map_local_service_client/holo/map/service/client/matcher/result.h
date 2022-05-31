/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file result.h
 * @brief Definition for matching result.
 * @author wanghaiyang(wanghaiyang@holomaitc.com)
 * @date "2020-04-22"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_MATCHER_RESULT_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_MATCHER_RESULT_H_

#include <holo/map/common/common_type_define.h>
#include <holo/map/common/preprocess.h>
#include <holo/map/common/utility.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace matcher
{

/**
 * @addtogroup matcher
 * @{
 *
 */

/**
 * @brief Define the matching result for map matcher.
 */
class MatchingResult
{
public:
    /// Redefine type for vector.
    using VectorType = std::vector<MatchingResult>;
    /// Redefine type for deque.
    using DequeType  = std::deque<MatchingResult>;
    /// Redefine type for confidence type.
    using ConfidenceType = holo::uint8_t;

    /// Define a geographic point type with CRS(Coordinate Reference System).
    using GeoPointType      = holo::map::format::geometry::GeographicParameterType<MapPoint3>;
    /// Redefine point type for inner members.
    using PointType         = GeoPointType::ParameterType;
    /// Redefine CRS type for inner members.
    using CoordinateType    = GeoPointType::CoordinateType;

    /// Confidence value with fully confident.
    static ConfidenceType const FULL_CONFIDENCE;
    /// Define invalid confidece value.
    static ConfidenceType const INVALID_CONFIDECE;
    /// Default tolerance for checking if the result is fully confident. (Unit: meter)
    static Distance const       DEFAULT_TOLERANCE;
    /// Invalid distance value.
    static Distance const       INVALID_DISTANCE;
    /// Valid distance value.
    static Distance const       VALID_DISTANCE;

    /**
     * @brief Format a MatchingResult to a JSON string.
     * 
     * @param[in] r An object of MatchingResult.
     * @return A JSON string.
     */
    static std::string FormatToString(MatchingResult const & r);

    /**
     * @brief Format an array of MatchingResult to a JSON string.
     * 
     * @param[in] r An array of MatchingResult.
     * @return A JSON string.
     */
    static std::string FormatToString(MatchingResult::VectorType const& r);

    /**
     * @brief Define the result type for map matcher.
     */
    enum class ResultType : holo::uint8_t
    {
        RESULT_TYPE_UNKNOWN         = 0, ///< Place holder.
        RESULT_TYPE_LINK_MATCHING,       ///< Matching result at link level.
        RESULT_TYPE_LANE_MATCHING        ///< Matching result at lane level.
    };

    /**
     * @brief Constructor.
     */
    MatchingResult();

    /**
     * @brief Destructor.
     */
    ~MatchingResult() = default;

    /**
     * @brief Reset all the members in MatchingResult.
     * 
     * @return Nothing.
     */
    void Reset();

    /**
     * @brief Whether or not current result is more confident than
     *        another result.
     * 
     * @param[in] r Another MatchingResult object;
     * @return true: if this result is more reliable than r;
     *         false: otherwise.
     */
    bool operator > (MatchingResult const & r) const;

    /**
     * @brief Whether or not current result is less confident than
     *        another result.
     * 
     * @param[in] r Another MatchingResult object;
     * @return true: if this result is less reliable than r;
     *         false: otherwise.
     */
    bool operator < (MatchingResult const & r) const;

    /**
     * @brief Whether or not equal with another object.
     * 
     * @param[in] r Another MatchingResult object;
     * @return true: Equal;
     *         false: otherwise.
     */
    bool operator == (MatchingResult const & r) const;

    /**
     * @brief Whether or not unequal with another object.
     * 
     * @param[in] r Another MatchingResult object;
     * @return true: Unequal.
     *         false: otherwise.
     */
    bool operator != (MatchingResult const & r) const;

    /**
     * @brief Access confidence value of current matching result.
     * 
     * @return A confidence value, range:[0, 100], if it equals 100,
     *         the result is absolutely reliable.
     */
    ConfidenceType GetConfidence() const;

    /**
     * @brief Check if the result is valid.
     * 
     * @return true: the result is valid;
     *         false: the result is invalid.
     */
    bool IsValid() const noexcept;

    /**
     * @brief Check if the result is matched.
     * 
     * @return true: the result is matched;
     *         false: the result is not matched.
     */
    bool IsMatched() const;

    /**
     * @brief Check if the result is reliable.
     * 
     * @return true: the result is reliable;
     *         false: the result is not reliable.
     */
    bool IsReliable() const
    {
        return FULL_CONFIDENCE == this->GetConfidence();
    }

    /**
     * @brief Check if the result is base on a reliable history.
     * 
     * @return true: the result is reliable;
     *         false: the result is not reliable.
     */
    bool IsHistoryReliable() const noexcept
    {
        return this->is_history_reliable_;
    }

    /**
     * @brief Assign history status.
     * 
     * @param[in] r true: The matching history is reliable;
     *              false: The matching history is non-reliable.
     */
    holo::bool_t SetHistoryStatus(holo::bool_t const r) noexcept
    {
        return this->is_history_reliable_ = r;
    }

    /**
     * @brief Check if target link is main road.
     * 
     * @return true: Is a main road;
     *         false: Not a main road.
     */
    holo::bool_t IsMotorwayMainRoad() const noexcept
    {
        return this->motorway_main_road_flag_;
    }

    /**
     * @brief Assign main road flag.
     * 
     * @param[in] flag true: Target link is main road;
     *                 false: Target link is not main road.
     */
    void SetMotorwayMainRoadFlag(holo::bool_t const flag) noexcept
    {
        this->motorway_main_road_flag_ = flag;
    }

    /**
     * @brief Check if target link is connected with current matching result.
     * 
     * @param[in] id Target link id.
     * @return true Target link is connected with current matching result;
     *         false Otherwise.
     */
    bool IsLinkConnected(MapFeatureIdType const id) const
    {
         return (utility::InsideVector(this->link_preceding_ids_, id) ||
                 utility::InsideVector(this->link_succeeding_ids_, id));
    }

    /**
     * @brief Check if target lane is connected with current matching result.
     * 
     * @param [in] id Target lane id.
     * @return true Target lane is connected with current matching result;
     *         false Otherwise.
     */
    bool IsLaneConnected(MapFeatureIdType const id) const
    {
        return (utility::InsideVector(this->lane_preceding_ids_, id) ||
                utility::InsideVector(this->lane_succeeding_ids_, id));
    }

    /**
     * @brief Access target point.
     * 
     * @return A point.
     */
    PointType const & GetTargetPoint() const noexcept
    {
        return this->target_point_.parameter;
    }

    /**
     * @brief Assign a target point.
     * 
     * @param[in] p A point.
     * @return Nothing.
     */
    void SetTargetPoint(PointType const & p)
    {
        this->target_point_.parameter = p;
    }

    /**
     * @brief Access coordinate info from inner geographic point.
     *
     * @return Coordiante reference system of inner geographic point.
     */
    CoordinateType const& GetCoordinate() const noexcept
    {
        return this->target_point_.coordinate;
    }

    /**
     * @brief Assign coordinate to the geographic point.
     *
     * @param [in] c Coordinate info.
     */
    void SetCoordinate(CoordinateType const& c) noexcept
    {
        this->target_point_.coordinate = c;
    }

    /**
     * @brief Access geographic point.
     *
     * @return A geographic point contained a point and a coordinate info.
     */
    GeoPointType const& GetGeoPoint() const noexcept
    {
        return this->target_point_;
    }

    /**
     * @brief Assign a new geographic point.
     *
     * @param[in] p A new geographic point, the point must be with a valid
     *            CRS(Coordinate Reference System) info.
     */
    void SetGeoPoint(GeoPointType const& p) noexcept
    {
        this->target_point_ = p;
    }

    /**
     * @brief Access matching result with link id.
     * 
     * @return A link id.
     */
    MapFeatureIdType GetMatchingLinkId() const noexcept
    {
        return this->link_id_;
    }

    /**
     * @brief Assign  a link id to the matching result.
     * 
     * @param[in] A link id.
     * @return Nothing.
     */
    void SetMatchingLinkId(MapFeatureIdType const id) noexcept
    {
        this->link_id_ = id;
    }

    /**
     * @brief Access matching result with lane id.
     * 
     * @return A lane id.
     */
    MapFeatureIdType GetMatchingLaneId() const noexcept
    {
        return this->lane_id_;
    }

    /**
     * @brief Assign a lane id to matching result.
     * 
     * @param[in] id A lane id.
     * @return Nothing.
     */
    void SetMatchingLaneId(MapFeatureIdType const id) noexcept
    {
        this->lane_id_ = id;
    }

    /**
     * @brief Access the link id of last matching result.
     * 
     * @return A link id.
     */
    MapFeatureIdType GetLastMatchingLinkId() const noexcept
    {
        return this->last_link_id_;
    }

    /**
     * @brief Assign a link id to the last matching result.
     * 
     * @param[in] A link id.
     * @return Nothing.
     */
    void SetLastMatchingLinkId(MapFeatureIdType const id) noexcept
    {
        this->last_link_id_ = id;
    }

    /**
     * @brief Access the link id of last matching result.
     * 
     * @return A link id.
     */
    MapFeatureIdType GetLastMatchingLaneId() const noexcept
    {
        return this->last_lane_id_;
    }

    /**
     * @brief Assign a link id to the last matching result.
     * 
     * @param[in] A link id.
     * @return Nothing.
     */
    void SetLastMatchingLaneId(MapFeatureIdType const id) noexcept
    {
        this->last_lane_id_ = id;
    }

    /**
     * @brief Access the tolerance of map matching.
     * 
     * @return A tolerance value.
     */
    Distance GetTolerance() const noexcept
    {
        return this->tolerance_;
    }

    /**
     * @brief Assign the tolerance for map matching.
     * 
     * @param[in] A tolerance value.
     * @return Nothing.
     */
    void SetTolerance(Distance const d) noexcept
    {
        this->tolerance_ = d;
    }

    /**
     * @brief Access the distance between current car position and the middle line.
     * 
     * @return A distance between current car position and the middle line of a link or lane.
     */
    Distance GetDistanceToMiddleLine() const noexcept
    {
        return this->distance_to_middle_line_;
    }

    /**
     * @brief Assign the distance between current car position and the middle line.
     * 
     * @param[in] d A distance between current car position and the middle line of a link or lane.
     * @return Nothing.
     */
    void SetDistanceToMiddleLine(Distance const d) noexcept
    {
        this->distance_to_middle_line_ = d;
    }

    /**
     * @brief Access the distance between current car position and left boundary.
     * 
     * @return The distance between current car position and left boundary.
     */
    Distance GetDistanceToLeftBoundary() const noexcept
    {
        return this->distance_to_left_boundary_;
    }

    /**
     * @brief Assign a distance between current car position and left boundary.
     * 
     * @param[in] d A distance between current car position and left boundary.
     * @return Nothing.
     */
    void SetDistanceToLeftBoundary(Distance const d) noexcept
    {
        this->distance_to_left_boundary_ = d;
    }

    /**
     * @brief Access a distance between current car position and right boundary.
     * 
     * @return A distance between current car position and left boundary.
     */
    Distance GetDistanceToRightBoundary() const noexcept
    {
        return this->distance_to_right_boundary_;
    }

    /**
     * @brief Assign a distance between current car position and right boundary.
     * 
     * @param[in] d A distance between current car position and right boundary.
     * @return Nothing.
     */
    void SetDistanceToRightBoundary(Distance const d) noexcept
    {
        this->distance_to_right_boundary_ = d;
    }

    /**
     * @brief Access a distance between current car position and link head.
     * 
     * @return If it equals to INVALID_DISTANCE, means that the current car position
     *         is too far to the link head and the link tail is at the back of the
     *         current car position.
     *         If it equals to VALID_DISTANCE, means that the current car position is
     *         to far to the link tail and the link tail is at the front of the current
     *         car position.
     */
    Distance GetDistanceToBottom() const noexcept
    {
        return this->distance_to_bottom_;
    }

    /**
     * @brief Assign a new distance between current car position and link head.
     * 
     * @param[in] A distance to the road head.
     * @return Nothing.
     */
    void SetDistanceToBottom(Distance const d) noexcept
    {
        this->distance_to_bottom_ = d;
    }

    /**
     * @brief Access a distance between current car position and link tail.
     * 
     * @return If it equals to INVALID_DISTANCE, means that the current car position
     *         is too far to the link tail and the link tail is at the front of the
     *         current car position.
     *         If it equals to VALID_DISTANCE, means that the current car position is
     *         to far to the link tail and the link tail is at the back of the current
     *         car position.
     */
    Distance GetDistanceToTop() const noexcept
    {
        return this->distance_to_top_;
    }

    /**
     * @brief Assign a new distance between current car position and link tail.
     * 
     * @param[in] A distance to the road tail.
     * @return Nothing.
     */
    void SetDistanceToTop(Distance const d) noexcept
    {
        this->distance_to_top_ = d;
    }

    /**
     * @brief Access result type of current matching result.
     * 
     * @return Current result type.
     */
    ResultType GetResultType() const noexcept
    {
        return this->matching_type_;
    }

    /**
     * @brief Assign matching result type.
     * 
     * @param[in] t Matching result type.
     * @return Nothing.
     */
    void SetResultType(const ResultType t) noexcept
    {
        this->matching_type_ = t;
    }

    /**
     * @brief Access succeeding link ids of current matching link.
     * 
     * @return Succeeding link ids.
     */
    MapFeatureIdVectorType const & GetMatchingLinkSucceedingIds() const noexcept
    {
        return this->link_succeeding_ids_;
    }

    /**
     * @brief Assign succeeding links to the matching result link.
     * 
     * @param[in] ids Succeeding link ids.
     * @return Nothing.
     */
    void SetMatchingLinkSucceedingIds(MapFeatureIdVectorType const & ids)
    {
        this->link_succeeding_ids_ = ids;
    }

    /**
     * @brief Assign succeeding links to the matching result link.
     * 
     * @param[in] ids Succeeding link ids.
     * @return Nothing.
     */
    void SetMatchingLinkSucceedingIds(MapFeatureIdVectorType&& ids)
    {
        this->link_succeeding_ids_ = std::move(ids);
    }

    /**
     * @brief Access preceding link ids of current matching result link.
     * 
     * @return Preceding link ids.
     */
    MapFeatureIdVectorType const & GetMatchingLinkPrecedingIds() const
    {
        return this->link_preceding_ids_;
    }

    /**
     * @brief Assign preceding links to the matching result link.
     * 
     * @param[in] ids Preceding link ids.
     * @return Nothing.
     */
    void SetMatchingLinkPrecedingIds(MapFeatureIdVectorType const & ids)
    {
        this->link_preceding_ids_ = ids;
    }

    /**
     * @brief Assign preceding links to the matching result link.
     * 
     * @param[in] ids Preceding link ids.
     * @return Nothing.
     */
    void SetMatchingLinkPrecedingIds(MapFeatureIdVectorType&& ids)
    {
        this->link_preceding_ids_ = std::move(ids);
    }

    /**
     * @brief Access preceding lane ids of current matching result lane.
     * 
     * @return Preceding lane ids.
     */
    MapFeatureIdVectorType const & GetMatchingLanePrecedingIds() const noexcept
    {
        return this->lane_preceding_ids_;
    }

    /**
     * @brief Assign preceding lanes to the matching result lane.
     * 
     * @param[in] ids Preceding lane ids.
     * @return Nothing.
     */
    void SetMatchingLanePrecedingIds(MapFeatureIdVectorType const & ids)
    {
        this->lane_preceding_ids_ = ids;
    }

    /**
     * @brief Assign preceding lanes to the matching result lane.
     * 
     * @param[in] ids Preceding lane ids.
     * @return Nothing.
     */
    void SetMatchingLanePrecedingIds(MapFeatureIdVectorType&& ids)
    {
        this->lane_preceding_ids_ = std::move(ids);
    }

    /**
     * @brief Access succeeding lane ids of current matching result lane.
     * 
     * @return Succeeding lane ids.
     */
    MapFeatureIdVectorType const & GetMatchingLaneSucceedingIds() const noexcept
    {
        return this->lane_succeeding_ids_;
    }

    /**
     * @brief Assign succeeding lanes to the matching result lane.
     * 
     * @param[in] ids Succeeding lane ids.
     * @return Nothing.
     */
    void SetMatchingLaneSucceedingIds(MapFeatureIdVectorType const & ids)
    {
        this->lane_succeeding_ids_ = ids;
    }

    /**
     * @brief Assign succeeding lanes to the matching result lane.
     * 
     * @param[in] ids Succeeding lane ids.
     * @return Nothing.
     */
    void SetMatchingLaneSucceedingIds(MapFeatureIdVectorType&& ids)
    {
        this->lane_succeeding_ids_ = std::move(ids);
    }

private:

    MapFeatureIdType link_id_ = 0; ///< Target link matched with target point.
    MapFeatureIdType lane_id_ = 0; ///< Target lane matched with target point.

    /// The last matched link id, if match at first time or the matching history
    /// is not continued, the last link id is 0.
    MapFeatureIdType last_link_id_ = 0;
    /// The last matched lane id, if match at first time or the matching history
    /// is not continued, the last lane id is 0.
    MapFeatureIdType last_lane_id_ = 0;

    MapFeatureIdVectorType link_preceding_ids_;  ///< Preceding link ids of matched link.
    MapFeatureIdVectorType link_succeeding_ids_; ///< Succeeding link ids of matched link.
    MapFeatureIdVectorType lane_preceding_ids_;  ///< Preceding lane ids of matched lane.
    MapFeatureIdVectorType lane_succeeding_ids_; ///< Succeeding lane ids of matched lane.

    /// This parameter will be set at outside of the this class, if the matching
    /// result history is reliable, this parameter will be true, otherwise will be
    /// false.
    holo::bool_t is_history_reliable_ = false;

    /// If current matching result is main road, the flag will be true, if is ramp,
    /// it will be false.
    holo::bool_t motorway_main_road_flag_ = false;

    /// If a distance of parameters is less than the tolerance, the matching
    /// result will be non-fully-confident.
    /// Parameters: distance_to_left_boundary_, distance_to_right_boundary_
    ///             distance_to_top_, distance_to_bottom_.
    /// Unit: meter.
    Distance tolerance_ = DEFAULT_TOLERANCE; 

    /// Thumbnail of a lane or link.
    /// Preceding. |>>>>>>>> Driving direction >>>>>>>>>| Succeeding.
    ///                      Left boundary.
    ///            |------------------------------------|
    ///     Bottom |         Lane/Link                  | Top.
    ///            |------------------------------------|
    ///                  Right boundary.
    /// Note: if all the parameters are greater than 0, the target point is matched
    ///       on the current lane or link.
    ///       Parameters: distance_to_left_boundary_, distance_to_right_boundary_,
    ///                   distance_to_top_, distance_to_bottom_.

    /// Distance(Unit: meter) between target point and middle line of current link or lane.
    /// If target point is outside of middle line, the distance is the length
    /// of target point and bottom or top point of middle line of a link/lane.
    Distance distance_to_middle_line_ = INVALID_DISTANCE;

    /// Distance(Unit: meter) of perpendicular between target point and left boundary line segment.
    /// If it is less than 0, the target point is on the left side of left boundary.
    /// If it is greater than 0, the target point is on the right side of left boundary.
    Distance distance_to_left_boundary_ = INVALID_DISTANCE;

    /// Distance(Unit: meter) of perpendicular between target point and right boundary line segment.
    /// If it is less than 0, the target point is on the right side of right boundary.
    /// If it is greater than 0, the target point is on the left side of right boundary.
    Distance distance_to_right_boundary_ = INVALID_DISTANCE;

    /// Distance(Unit: meter) between target point and bottom line of current lane or link.
    /// If it's left than 0, the target point is one the left side of bottom line.
    /// If it's greater than 0, the target point is on the right side of bottom line.
    Distance distance_to_top_ = VALID_DISTANCE;

    /// Distance(Unit: meter) between target point and top line of current lane of link.
    /// If it's left than 0, the target point is one the right side of top line.
    /// If it's greater than 0, the target point is one the left side of top line.
    Distance distance_to_bottom_ = VALID_DISTANCE;

    /// If matched link without lanes, matching type will be set up MATCHING_TYPE_LINK_MATCHING.
    /// If the matching type is RESULT_TYPE_LINK_MATCHING, all the lane information will be un-available,
    /// like @lane_id_ @last_lane_id_ @lane_preceding_ids_ @lane_succeeding_ids_.
    ResultType matching_type_ = ResultType::RESULT_TYPE_UNKNOWN;

    /// Target point from fused odometry.
    GeoPointType target_point_;
}; ///< End of class MatchingResult.

/**
 * @}
 *
 */

} ///< namespace matcher
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_MATCHER_RESULT_H_ */
