/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file matcher.h
 * @brief Definition for MapMatcher
 * @author wanghaiyang(wanghaiyang@holomaitc.com)
 * @date "2020-04-22"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_MATCHER_MATCHER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_MATCHER_MATCHER_H_

#include <memory>

#include <holo/map/service/client/matcher/results.h>
#include <holo/map/service/client/engine/retriever.h>

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
 * @brief A package used for calculating where is the target position on the HD map.
 */
class MapMatcher
{
public:
    using MatchingResultType = holo::map::service::client::matcher::MatchingResult;
    using MatchingResultVectorType = std::vector<MatchingResultType>;

    /// Redefine shared pointer for mutable MatchingResults.
    using SPtrMatchingResults = std::shared_ptr<MatchingResults>;
    /// Redefine shared pointer for immutable MatchingResults.
    using CSPtrMatchingResults = std::shared_ptr<MatchingResults const>;

    /// Redefine shared pointer for mutable MapMatcher.
    using SPtrType = std::shared_ptr<MapMatcher>;
    /// Redefine shared pointer for immutable MapMatcher.
    using CSPtrType =  std::shared_ptr<MapMatcher const>;

    /// Redefine position type from Odometry.
    using OdometryType = holo::common::Odometryd;

    /// Define a geographic point type with CRS(Coordinate Reference System).
    using GeoPointType      = MatchingResultType::GeoPointType;

    /// Redefine point type for inner members.
    using PointType         = GeoPointType::ParameterType;
    /// Redefine vector type for point.
    using PointVectorType   = std::vector<PointType>;
    /// Redefine CRS type for inner members.
    using CoordinateType    = GeoPointType::CoordinateType;

    using RetrieverType = holo::map::service::client::engine::Retriever;
    using RetrieverSPtrType = std::shared_ptr<RetrieverType>;

    using ProfileType           = RetrieverType::ProfileType;
    using ProfileIdType         = RetrieverType::ProfileIdType;
    using ProfileIdVectorType   = RetrieverType::ProfileIdVectorType;

    using ProfileBaseType       = RetrieverType::ProfileBaseType;
    using ProfileBaseSPtrType   = RetrieverType::ProfileSPtrType;
    using ProfileBaseCSPtrType  = RetrieverType::ProfileCSPtrType;

    /**
     * @brief The mode of map matching.
     */
    enum class MatchingMode : holo::uint8_t
    {
        MATCHING_MODE_CONTINUE, ///< The history will be used for verifying the current matching result.
        MATCHING_MODE_INTERVAL  ///< Map matching alone.
    };

    /**
     * @brief The level of map matching.
     */
    enum class MatchingLevel : holo::uint8_t
    {
        MATCHING_LEVEL_LINK,    ///< The matching result will be at link level.
        MATCHING_LEVEL_LANE     ///< The matching result will be at lane level.
    };

    /**
     * @brief Constructor.
     * 
     * @return Nothing.
     */
    MapMatcher() = default;

    /**
     * @brief Destructor.
     * 
     * @return Nothing.
     */
    ~MapMatcher() = default;

    MapMatcher(MapMatcher const&) = delete;
    MapMatcher(MapMatcher&&) = delete;

    MapMatcher& operator = (MapMatcher const&) = delete;
    MapMatcher& operator = (MapMatcher&&) = delete;

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
    void SetVerbose(holo::bool_t const b) noexcept;

#if 1 /* TEMPORARY_CODE_FOR_URBAN_PILOT */
    /**
     * @brief Access map matching degrading flag.
     * 
     * @return true: Enable degrading map matching when a feature(Lane/LaneGroup) without
     *               left or right boundary.
     *         false: Disable degrading map matching when a feature(Lane/LaneGroup) without
     *                left or right boundary.
     */
    holo::bool_t GetDegradingFlag() const noexcept;

    /**
     * @brief Assign map matchiing degrading flag.
     * 
     * @return true: true: Enable degrading map matching when a feature(Lane/LaneGroup) without
     *               left or right boundary.
     *         false: Disable degrading map matching when a feature(Lane/LaneGroup) without
     *                left or right boundary.
     */
    void SetDegradingFlag(holo::bool_t const f) noexcept;
#endif /* TEMPORARY_CODE_FOR_URBAN_PILOT */

    /**
     * @brief Init the map matcher.
     * 
     * @param[in] ret A database engine.
     * @return true: Init successfully without any error;
     *         false: Otherwise.
     */
    holo::bool_t Init(RetrieverSPtrType const ret);

    /**
     * @brief Access map engine handle.
     * 
     * @return Map engine handle.
     */
    RetrieverSPtrType GetRetriever() const
    {
        return this->retriever_;
    }

    /**
     * @brief Clear all the members of the current object.
     * 
     * @return Nothing.
     */
    void Clear();

    /**
     * @brief Access the current matching mode.
     * 
     * @return Current matching mode.
     */
    MatchingMode GetMatchingMode() const noexcept
    {
        return this->matching_mode_;
    }

    /**
     * @brief Assign a new matching mode.
     * 
     * @param[in] mode A new matching mode, if the mode doesn't equal to the
     *                 current mode, the matcher will be reset.
     * @return Nothing.
     */
    void SetMatchingMode(MatchingMode const mode) noexcept
    {
        if (this->matching_mode_ != mode)
        {
            this->matching_mode_ = mode;
            this->Clear();
        }
    }

    /**
     * @brief Access the current matching level.
     * 
     * @return Current matching level.
     */
    MatchingLevel GetMatchingLevel() const noexcept
    {
        return this->matching_level_;
    }

    /**
     * @brief Assign a new matching level.
     * 
     * @param[in] level A new matching level, if the level doesn't equal to the
     *                 current level, the matcher will be clear.
     * @return Nothing.
     */
    void SetMatchingLevel(MatchingLevel const level) noexcept
    {
        if (this->matching_level_ != level)
        {
            this->matching_level_ = level;
            this->Clear();
        }
    }

    /**
     * @brief Access the current matching results, if match failed, the
     *        current MatchingResults will be empty.
     * 
     * @return A shared pointer.
     */
    CSPtrMatchingResults GetMatchingResults() const noexcept
    {
        return this->current_matching_results_;
    }

    /**
     * @brief Make a real map matching.
     * 
     * @note If this function return true, the target point may be not on the
     *       map, so we should check the MatchingResults, if it is empty, the
     *       target point is not on the map..
     * @param[in] odo An odometry with position info and coordinate info.
     * @return true: Match successfully without an error;
     *         false: An error occurs in this function.
     */
    holo::bool_t Match(OdometryType const& odo);

    /**
     * @brief Check whether or not the matching result history is reliable.
     *
     * @details The interface 'IsHistoryReliable' will check history except
     *          the current matching result. This interface will check the
     *          latest matching result in history with current matching result.
     *
     * @return true: Reliable.
     *         false: Unreliable.
     */
    holo::bool_t IsReliable();

private:

    /**
     * @brief Whether or not the matching result history is reliable.
     * 
     * @return true: Reliable.
     *         false: Unreliable.
     */
    holo::bool_t IsHistoryReliable() const noexcept;

    /**
     * @brief Check the history before every matching.
     * 
     * @param[in] t The current target point.
     * @return Nothing.
     */
    void CheckHistory(MapPoint3 const& t);

    /**
     * @brief Update the history after every successful matching.
     * 
     * @param[in] results The current matching results.
     * @return Nothing.
     */
    void UpdateHistory(MatchingResults const& results);

    /**
     * @brief Update the matching history status to all matching result.
     * 
     * @detail After map matching, should udpate the history status for all
     *         the matching results.
     * @param[in] results All the current matching results.
     */
    void UpdateResultsHistoryStatus(MatchingResults& results);

    /**
     * @brief Judge whether there is a valid path from current link to target link
     *
     * @details When there are short links in map, the matching result will be un-reliable.
     *          We need to search target link previous than(or successive to) current link,
     *          and there are only short links between current link and target link.
     *
     *          ------------------ target link ------------ current link --------
     *          - link1  -  link2  -  link3    -    link4  -  link5  -  link6  -  link7 -----
     *
     *          The target link is at link3, the current link is at link5, so we need to
     *          find a path from link5 to link3 using deep-first method.
     * @param[in] _current_link_id Current link id
     * @param[in] _current_distance Distance from current point to top in positive direction
     *                              or current point to bottom for negative direction
     * @param[in] _target_link_id Target link id
     * @param[in] _distance The maximum distance to be searched by
     * @param[in] _is_positive_direction True for positive direction, false for negative direction
     * @return holo::bool_t True The links could connect at a certain distance
     *              False The links could not connect at a certain distance
     */
    holo::bool_t IsConnectedWithinDistance(MapFeatureIdType const& _current_link_id,
                                   Distance const& _current_distance,
                                   MapFeatureIdType const& _target_link_id,
                                   Distance const& _distance,
                                   holo::bool_t const succeeding_or_preceding,
                                   holo::bool_t& result);

    holo::bool_t IsRealInterruptedWithResults(MatchingResult const& current, MatchingResult const& last,
        holo::bool_t& result);

    /**
     * @brief Access the last matching link id if have an available history.
     * 
     * @return A link id, if the the history is invalid, will return 0.
     */
    MapFeatureIdType GetLastLinkIdFromHistory() const noexcept;

    /**
     * @brief Access the last matching lane id if have an available history.
     * 
     * @return A lane id, if the the history is invalid, will return 0.
     */
    MapFeatureIdType GetLastLaneIdFromHistory() const noexcept;

    /**
     * @brief An inner map matching package.
     * 
     * @param[in] target The current target point.
     * @param[in] coord Coordinate information about target point.
     * @param[out] results The matching results, if match failed, it will be empty.
     * @return true: No error, even though the target point is not on the map.
     *         false: An error occurs in this function.
     */
    holo::bool_t InnerMatch(format::GeoPoint const&  target,
                    holo::common::Coordinate const& coord,
                    MatchingResults&         results);

    /**
     * @brief Find all the available links in a special range of target point.
     *        The special is the matching_range_.
     * 
     * @param[in] target The target point.
     * @param[in] coord Coordinate information about target point.
     * @param[out] link_ids All the available link ids.
     * @return true: No error, even though link_ids is empty, means that the target
     *               point is not on the HD map.
     *         false: An error occurs in this function.
     */
    holo::bool_t RoughSearch(format::GeoPoint const&  target,
                     holo::common::Coordinate const& coord,
                     MapFeatureIdVectorType&             link_ids);

    /**
     * @brief Find all the closest links or lane.
     * 
     * @param[in] target The target point.
     * @param[in] link_ids The available link in the matching range.
     * @param[out] results The closest matching results.
     * @return true: No error.
     *         false: An error occurs in this function.
     */
    holo::bool_t FineSearch(format::GeoPoint const& target, 
                    MapFeatureIdVectorType const&       link_ids,
                    MatchingResults&         results);

    /**
     * @brief Make matching results by links.
     * 
     * @param[in] target The target point.
     * @param[in] link_ids The available link in the matching range.
     * @param[out] results The closest matching results.
     * @return true: No error.
     *         false: An error occurs in this function.
     */
    holo::bool_t MatchByLinks(format::GeoPoint const&   target, 
                      MapFeatureIdVectorType const&        link_ids,
                      MatchingResults&          results);

    /**
     * @brief Make matching results by lanes.
     * 
     * @param[in] target The target point.
     * @param[in] lane_ids The available link in the matching range.
     * @param[out] results The closest matching results.
     * @return true: No error.
     *         false: An error occurs in this function.
     */
    holo::bool_t MatchByLanes(format::GeoPoint const& target, 
                      MapFeatureIdVectorType const&       lane_ids, 
                      MatchingResults&         results);


    /**
     * @brief Calculate distance between target point and links or lanes.
     * 
     * @param [in] id Link or Lane id.
     * @param [in] lane_or_link If true: a lane id, if false: a link id,
     * @param [in] target Point on map.
     * @param [out] result @IndividualMatchResults.
     * @return true: No error.
     *         false: An error occurs in this function.
     */
    holo::bool_t MakeMatchResultByLaneOrLink(MapFeatureIdType const             id,
                                     holo::bool_t const                 lane_or_link,
                                     format::GeoPoint const&    target,
                                     MatchingResult&            result);

    /**
     * @brief Check the target between left and right mark.
     * 
     * @param [in] left_mark_id Left mark id of lane or link.
     * @param [in] right_mark_id Right mark id of lane or link.
     * @param [in] target Point on map.
     * @param [out] result @IndividualMatchResults.
     * @return true: No error.
     *         false: An error occurs in this function.
     */
    holo::bool_t MakeMatchResultByMark(MapFeatureIdType const            left_mark_id,
                               MapFeatureIdType const            right_mark_id,
                               format::GeoPoint const&   target,
                               MatchingResult&           result);

    /**
     * @brief Calculate matching result by ref points of a map feature(Lane/LaneGroup).
     *
     * @param[in] points Ref points of a map feature(Lane/LaneGroup).
     * @param[in] target Point on map.
     * @param[in] has_boundary If true:
     *                         do not calculate distance to middle_line\left_boundary\right_boundary;
     *                         if false:
     *                         calculate distance to middle_line\left_boundary\right_boundary.
     * @param[out] result @IndividualMatchResults.
     * @return true: No error.
     *         false: An error occurs in this function.
     */
    holo::bool_t makeMatchResultByRefPoints(std::vector<format::GeoPoint> const& points,
                                            format::GeoPoint const& target,
                                            holo::bool_t const has_boundary,
                                            MatchingResult&  result);

    /**
     * @brief Notify retriever that it should request profiles(aka map features) right now.
     * 
     * @detail Some profiles not exist in retriever, but they are used by matcher, so retriever
     *         should fetch those profiles from server right now.
     * @param[in] type Profile type, refer to holo::map::service::client::profile::ProfileType for
     *            more details.
     * @param[in] id Profile ids,(aka map feature ids).
     */
    void prepareProfiles(ProfileType const type, ProfileIdVectorType const& ids);

    /**
     * @brief Check if the target profile(map feature) is complete.
     * 
     * @detail If a lane group is complete, the lane group and it's left and right boundary are
     *         both exist in retriever.
     *         If a lane is complete, the lane and it's left and right boundary are both exist in
     *         retriever.
     * @note This function only support LANE and LANE_GROUP.
     * @param[in] type Profile type, refer to holo::map::service::client::profile::ProfileType for
     *            more details.
     * @param[in] id Profile id,(aka map feature id).
     * @param[out] result True: target profile does exist in retriever;
     *                    False: target profile does not exist in retriever.
     * @return True: No error;
     *         False: An error occurs in this function, refer to log for more details.
     */
    holo::bool_t isProfileReady(ProfileType const type, ProfileIdType const id, holo::bool_t& result);
#if 1 /* TEMPORARY_CODE_FOR_URBAN_PILOT */
    /**
     * @brief Check if the target profile is without left or right boundary.
     * 
     * @detail If a profile without left or right boundary, the result will be true.
     * @note This function only support LANE and LANE_GROUP.
     * @param[in] type refer to holo::map::service::client::profile::ProfileType for
     *            more details.
     * @param[in] id Profile id,(aka map feature id).
     * @param[out] result True: target profile without left or right boundary;
     *                    False: otherwise.
     * @return True: No error;
     *         False: An error occurs in this function, refer to log for more details.
     */
    holo::bool_t isProfileWithoutBoundary(ProfileType const type, ProfileIdType const id, holo::bool_t& result);
#endif /* TEMPORARY_CODE_FOR_URBAN_PILOT */
private:
    RetrieverSPtrType retriever_ = nullptr; ///< Database engine handle.

    /// Unit: meter, the tolerance for calculating the reliability of matching result.
    Distance matching_tolerance_ = 0.2;
    /// Unit: meter,the tolerance for fine searching.
    Distance search_tolerance_   = 10.0;
    /// Unit: meter, the range for rough searching.
    Distance search_range_       = 200.0;

    /// Unit: meter, the maximum distance for tracking back.
    /// There are two threads to update matching history:
    ///   1.replying thread to do with request,
    ///   2.callback thread to update matching history at real time.
    /// Callback thread may be blocked in a situation where replying thread is dealing
    /// with complex tasks in one interval.
    /// Because replaying thread accept odometry when car runs 50 meters, we need
    /// set distance for tracking back at least 50 meters. We scale it by 1.1 for the
    /// sake of safety.
    Distance track_back_distance_ = 50 * 1.1;

    /// Matching mode for map matching algorithm, If it is CONTINUE, the matching result
    /// history will affect the current matching result.
    MatchingMode       matching_mode_            = MatchingMode::MATCHING_MODE_CONTINUE;
    /// If it's LINK_LEVEL, the result will match on links;
    /// if it's LANE_LEVEL, the result will match on lanes.
    MatchingLevel      matching_level_           = MatchingLevel::MATCHING_LEVEL_LANE;

    /// Capacity for current matching results.
    std::size_t         current_results_capacity_ = 5;
    /// Matching result for current target point.
    SPtrMatchingResults current_matching_results_ = nullptr;

    /// Q: Why we need a history for matching results?
    /// A: 1. If a bridge on the HD map, the car is under the bridge, but the current
    ///       road of the car is not on the HD map, the targe point will be matched on
    ///       the HD map if we have only one point.
    ///    2. If there is a bridge on the HD map, roads under and over the bridge are
    ///       both on the HD map, the target point will be matched on the both of bridge
    ///       if we have only one point.
    ///    So we need a history of for double checking the current matching result.

    /// Whether or not the history is reliable.
    /// If false: the history is not reliable, so the current matching result is not
    ///           reliable.
    /// If true: the history is reliable, we can use it to double check the current
    ///          matching result whether or not reliable.
    holo::bool_t                is_history_reliable_      = false;
    /// Capacity for matching result history.
    std::size_t                 result_history_capacity_  = 20;    
    /// A deque buffer for matching result history.
    MatchingResult::DequeType   matching_result_history_;

    /// Current coordinate reference system from current position, used for calculating
    /// distance of two geopoints and updating map engine CRS. Note: it will be discarded
    /// when all the inner MapPoints have been repaced by geographic points.
    CoordinateType coordinate_;
    /// If true, print debug message to log.
    holo::bool_t verbose_ = false;

#if 1 /* TEMPORARY_CODE_FOR_URBAN_PILOT */
    /// If true, we can degrade map matching when a map feature(Lane/LaneGroup)
    /// without left or right boundary. we will use the reference points of map
    /// feature to make map matching.
    holo::bool_t matching_degrading_flag_ = false;
#endif /* TEMPORARY_CODE_FOR_URBAN_PILOT */
}; ///< End of class MapMatcher.

using MapMatcherSPtrType = std::shared_ptr<MapMatcher>;

/**
 * @}
 *
 */

} ///< namespace matcher
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_MATCHER_MATCHER_H_ */
