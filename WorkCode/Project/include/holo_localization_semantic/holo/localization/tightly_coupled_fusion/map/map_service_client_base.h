/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_service_client_base.h
 * @brief The definition of map_service_client_base abstract class
 * @attention It is a abstract class, we must inherit and implement its member functions.
 * @author Lei Gehang(leigehang@holomatic.com)
 * @date Oct 29, 2020
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPPLE_FUSION_MAP_MAP_SERVICE_CLIENT_BASE_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPPLE_FUSION_MAP_MAP_SERVICE_CLIENT_BASE_H_

#include <holo/localization/common/types.h>
#include <holo/log/hololog.h>

#include <iostream>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
namespace map
{
/**
 * @addtogroup map
 * @{
 *
 */

/**
 * @brief This class is a abstract class for declare the interfaces of the map service client.
 * @attention It is a abstract class, we must inherit and implement its member functions.
 *
 */
class MapServiceClientBase
{
public:
    using Ptr            = std::shared_ptr<MapServiceClientBase>;
    using ConstaPtr      = std::shared_ptr<const MapServiceClientBase>;
    using CoordinateType = holo::localization::CoordinateType;
    using LinkId         = holo::uint64_t;
    using LaneId         = holo::uint64_t;

    /**
     * @brief The parameters for judging the road structure attribute
     *
     */
    struct JudgingRoadAttributeParameters
    {
        /// The front and rear distance determining the range to judge whether the vehicle in the main road
        Scalar front_distance_to_judge_single_road = Scalar(80.0);
        Scalar rear_distance_to_judge_single_road  = Scalar(20.0);
        /// The front and rear distance determining the range to judge whether the lane number changed
        Scalar front_distance_to_judge_lane_number_changed = Scalar(80.0);
        Scalar rear_distance_to_judge_lane_number_changed  = Scalar(20.0);
        /// The front and rear distance determining the range to judge whether the laneboundary type changed
        Scalar front_distance_to_judge_laneboundary_type_changed = Scalar(80.0);
        Scalar rear_distance_to_judge_laneboundary_type_changed  = Scalar(20.0);
        /// The front and rear distance determining the range to judge whether the lane is parallel
        Scalar front_distance_to_judge_lane_parallel = Scalar(80.0);
        Scalar rear_distance_to_judge_lane_parallel  = Scalar(20.0);
    };

    /**
     * @brief The parameters for map mathcing when we call the map service client and get the matching result
     *
     */
    struct MatchingParameters
    {
        JudgingRoadAttributeParameters judge_road_attribute_params;
    };

    /**
     * @brief The road structure attribute that we can get from the map
     *
     */
    struct RoadAttribute
    {
        bool_t is_in_single_road             = true;   ///< The flag whether the vehicle is in the single road
        bool_t is_lane_number_changed        = false;  ///< The flag whether the surrounding lane number changes
        bool_t is_lane_boundary_type_changed = false;  ///< The flag whether the surrounding lind type changes
        bool_t is_lane_parallel              = true;   ///< The flag whether the surrounding lane is parallel
        /// The width of each lane. It's arranged from the inside to the outside
        std::vector<Scalar> lane_width_vector;
    };

    /**
     * @brief The matching attribute that we can get from the map after we matched a position with the HD map
     *
     */
    struct MatchingAttribute
    {
        LinkId link_id                   = 0u;           ///< The matching link Id
        LaneId lane_id                   = 0u;           ///< The matching lane Id
        Scalar distance_to_middle_line   = Scalar(0.0);  ///< The distance from the target position to the middle line
        Scalar distance_to_left_boundary = Scalar(0.0);  ///< The distance from the target position to the left boundary
        Scalar distance_to_right_boundary =
            Scalar(0.0);                           ///< The distance from the target position to the right boundary
        Scalar  distance_to_bottom = Scalar(0.0);  ///< The distance from the target position to the link head
        Scalar  distance_to_top    = Scalar(0.0);  ///< The distance from the target position to the link tail
        uint8_t confidence         = 0u;           ///< The matching result confidence; From 0 to 100
        bool_t  is_on_main_road    = true;         ///< is matching results on main road or not
    };

    /**
     * @brief The definition of matching attribute and lane boundaries
     *
     */
    struct MatchingAttributeAndLaneBoundaries
    {
        MatchingAttribute                    matching_attribute;     ///< The matching attribute
        std::vector<std::vector<Point3Type>> left_lane_boundaries;   ///< The left lane boundaries
        std::vector<std::vector<Point3Type>> right_lane_boundaries;  ///< The right lane boundaries
    };

    /**
     * @brief The type of the lane boundary in the map
     *
     */
    enum class BoundaryType : uint8_t
    {
        BOUNDARY_TYPE_UNKNOWN = 0u,
        BOUNDARY_TYPE_REGULAR,  ///< Lane boundary painted on the ground
        BOUNDARY_TYPE_BARRIER,  ///< Guardrail both side of road
        BOUNDARY_TYPE_CURB,     ///< Curb both side of road, lower than barrier usually
    };

    /**
     * @brief The style of the lane boundarty in the map
     *
     */
    enum class BoundaryStyle : uint8_t
    {
        BOUNDARY_STYLE_UNKNOWN = 0u,
        BOUNDARY_STYLE_SINGLE_SOLID_LINE,
        BOUNDARY_STYLE_DOUBLE_SOLID_LINE,
        BOUNDARY_STYLE_SINGLE_DASHED_LINE,
        BOUNDARY_STYLE_DOUBLE_DASHED_LINE,
        BOUNDARY_STYLE_OTHER,
    };

    /**
     * @brief The color of the lane boundarty in the map
     *
     */
    enum class BoundaryColor : uint8_t
    {
        BOUNDARY_COLOR_UNKNOWN = 0u,
        BOUNDARY_COLOR_YELLOW,
        BOUNDARY_COLOR_WHITE,
    };

    /**
     * @brief The type of the lane in the map
     *
     */
    enum class LaneType : uint8_t
    {
        LANE_TYPE_UNKNOWN = 0u,
        LANE_TYPE_EXPRESS,     ///< Express lane
        LANE_TYPE_EMERGENCY,   ///< Emergency lane which adjacent to the right road carriageway, including hard shoulder
        LANE_TYPE_ENTRY,       ///< The lane entering the main highway ,is usually followed by an acceleration lane
        LANE_TYPE_EXIT,        ///< The lane leaving the express way, usually followed by the deceleration lane
        LANE_TYPE_ACCELERATE,  ///< The lane used for vehicle acceleration when merging from ramp into main highway
        LANE_TYPE_DECELERATE,  ///< The lane used to slow down vehicles when driving off the ramp from the main highway
        LANE_TYPE_HARD_SHOULDER,  ///< Distance from the outer edge of carriageway to the edge of Subgrade
        LANE_TYPE_RAMP,           ///< A road on the right side of an expressway exit or entrance
        LANE_TYPE_OTHER           ///< Other lane
    };

    /**
     * @brief The type of the mapobject including the type and a vector of map object outline points
     *
     */
    struct MapObject
    {
        /**
         * @brief The classification of map object
         *
         */
        enum class Classification : uint8_t
        {
            SIGN = 0,
            POLE,
        };

        Classification          classification;  ///< classification of map object
        std::vector<Point3Type> outline;         ///< vector of map outline's contour points
    };

    /**
     * @brief The line boundary attribute including the type, color, line width
     *
     */
    struct BoundaryAttribute
    {
        BoundaryStyle style = BoundaryStyle::BOUNDARY_STYLE_UNKNOWN;
        BoundaryColor color = BoundaryColor::BOUNDARY_COLOR_UNKNOWN;
        Scalar        width = Scalar(0.0);  ///< The line width
        Scalar        start = Scalar(0.0);  ///< The start of this line segment of the boundary
        Scalar        end   = Scalar(0.0);  ///< The end of this line segment of the boundary
    };

    /**
     * @brief The definition of the lane boundary
     *
     */
    struct LaneBoundary
    {
        std::vector<BoundaryAttribute> boundary_attributes;
        BoundaryType                   boundary_type   = BoundaryType::BOUNDARY_TYPE_UNKNOWN;
        Scalar                         length          = Scalar(0.0);  ///< The length of this laneboundary
        LaneType                       left_lane_type  = LaneType::LANE_TYPE_UNKNOWN;
        LaneId                         left_lane_id    = 0u;
        LaneType                       right_lane_type = LaneType::LANE_TYPE_UNKNOWN;
        LaneId                         right_lane_id   = 0u;

        ///< The geometry points to express the lane boundary
        std::shared_ptr<std::vector<Point3Type>> lane_geometry_points_ptr = nullptr;
    };

    /**
     * @brief The lane boundaries in the target road that we can get from the map after we matched a position with the
     * HD map
     */
    struct RoadBoundary
    {
        uint8_t                   number_boundary = 0u;  ///< The number of the lane
        std::vector<LaneBoundary> lane_boundaries;       ///< All lane boundary in current route
    };

    /**
     * @brief The matching result including the matching attribute, road attribute and lane attribute
     *
     */
    struct MatchingResult
    {
        MatchingAttribute matching_attribute;
        RoadAttribute     road_attribute;
        RoadBoundary      road_boundary;
    };

    /**
     * @brief The parameters for request the road bounadary from the HD map. The special road boundary type includes the
     * road barrier and curb.
     *
     */
    struct SpecialRoadBoundaryTypeRequestParameters
    {
        BoundaryType boundary_type = BoundaryType::BOUNDARY_TYPE_UNKNOWN;

        Scalar front_detection_distance = 0.0;  ///< Front distance of the target point. Unit: meter.
        Scalar rear_detection_distance  = 0.0;  ///< Rear distanc of the target point. Unit: meter.
    };

    /**
     * @brief The special road boundary type definition.
     *
     */
    struct SpecialRoadBoundaryType
    {
        std::vector<Point3Type> boundary_points;  ///< The range points of the special boundary.
        ///< The different boundary point index ranger. The pair is <start_index, end_index> for one boundary
        std::vector<std::pair<uint16_t, uint16_t>> boundary_index_ranges;
    };

    /**
     * @brief The result for the special road boundary requestion.
     *
     */
    struct SpecialRoadBoundaryResult
    {
        /// Left special road boundary, if no special type road boundary, it should be nullptr(Notice).
        std::shared_ptr<SpecialRoadBoundaryType> left_road_boundary = nullptr;

        /// Right special road boundary, if no special type road boundary, it should be nullptr(Notice).
        std::shared_ptr<SpecialRoadBoundaryType> right_road_boundary = nullptr;
    };

    /**
     * @brief Enable the default constructor
     *
     */
    MapServiceClientBase() = default;

    /**
     * @brief Enable the default destructor
     *
     */
    virtual ~MapServiceClientBase() = default;

    /**
     * @brief Update the Map Engine and match the map to get the results based on the input position.
     * @attention We only do the map matching in link level
     *
     * @param[in] odometry The position of the matching point
     * @return It returns true if we can update and match successfully. Otherwise, we return false.
     */
    virtual bool_t UpdateAndMatchingMap(const OdometryType& odometry) = 0;

    /**
     * @brief Get the matching link Id sequence
     *
     * @param[out] link_ids The matching link Id sequence
     * @return It returns true if we can get the link Id successfully. Otherwise, it returns false.
     */
    virtual bool_t GetMatchingLinkIds(std::vector<LinkId>& link_ids) = 0;

    /**
     * @brief Get the matching Link Id sequence
     *
     * @param[in] odometry The odometry to request the HDmap for matching
     * @param[out] link_ids The returned matching link Id sequence
     * @return It returns true when we request the HDmap successfully. Otherwise, it returns false.
     */
    virtual bool_t GetMatchingLinkIds(const OdometryType& odometry, std::vector<LinkId>& link_ids) = 0;

    /**
     * @brief Get the road attribute based on the target link Id
     *
     * @param[in] link_id The target link Id
     * @param[in] param The parameters for judging the road structure attribute
     * @param[out] road_attribute The road attribute in current link Id
     * @return It returns true if we can get the road attribute successfully. Otherwise, it returns false.
     */
    virtual bool_t GetRoadAttribute(const LinkId& link_id, const JudgingRoadAttributeParameters& param,
                                    RoadAttribute& road_attribute) = 0;

    /**
     * @brief Get the matching attribute based on the target link Id
     *
     * @param[in] link_id The target link Id
     * @param[out] matching_attribute The matching attribute in current link Id
     * @return It returns true if we can get the matching attribute successfully. Otherwise, it returns false.
     */
    virtual bool_t GetMatchingAttribute(const LinkId& link_id, MatchingAttribute& matching_attribute) = 0;

    /**
     * @brief Get the road boundary based on the target link Id
     *
     * @param[in] link_id The target link Id
     * @param[out] road_boundary The road boundary information in current link Id
     * @return It returns true if we can get the lane attribute successfully. Otherwise, it returns false.
     */
    virtual bool_t GetRoadBoundary(const LinkId& link_id, RoadBoundary& road_boundary) = 0;

    /**
     * @brief Get the matching result based on the target link Id
     *
     * @param[in] link_id The target link Id
     * @param[in] param The parameters for map matching
     * @param[out] result The matching result in current link Id
     * @return It returns true if we can get the corresponding matching result successfully. Otherwise, it returns
     * false.
     */
    virtual bool_t GetMatchingResult(const LinkId& link_id, const MatchingParameters& param,
                                     MatchingResult& result) = 0;

    /**
     * @brief Get all matching results after we mathced a position with the HD map
     * @attention We must match the map with a position before we call this function. Otherwise, it can't get any
     result
     * and will return fasle.
     *
     * @param[in] param The parameters for map matching
     * @param[out] result_sequence The sequence of the current mathcing results
     * @return It returns true if we can get matching results successfully. Otherwise, it returns false.
     */
    virtual bool_t GetMatchingResults(const MatchingParameters&    param,
                                      std::vector<MatchingResult>& result_sequence) = 0;

    /**
     * @brief Get all matching results based on the target odometry.
     *
     * @param[in] odometry The target odoemtry
     * @param[in] param The matching parameters
     * @param[out] result_sequence The sequence of the current mathcing results
     * @return It returns true if we can get matching results successfully. Otherwise, it returns false.
     */
    virtual bool_t GetMatchingResults(const OdometryType& odometry, const MatchingParameters& param,
                                      std::vector<MatchingResult>& result_sequence) = 0;

    /**
     * @brief Get the line boundaries of the target lane. The target lane is determined by the input link Id and lane
     * Id. And the lane boundaries including the left laneboundary and the right laneboundary of the target lane. The
     * odometry is used as a projection point to obtain laneboundary points.
     *
     * @param[in] odometry The projection point to obtain laneboundary points
     * @param[in] link_id The link Id of the target lane
     * @param[in] lane_id The lane Id of the target lane
     * @param[out] left_boundary_points The left boundary points of the lane
     * @param[out] right_boundary_points The right boundary points of the lane
     * @return It returns true if we can get the result successfully; Otherwise, it returns false.
     */
    virtual bool_t GetTargetLineBoundaries(const OdometryType& odometry, const LinkId& link_id, const LaneId& lane_id,
                                           std::vector<std::vector<Point3Type>>& left_boundary_points,
                                           std::vector<std::vector<Point3Type>>& right_boundary_points) = 0;

    /**
     * @brief Get the forked property of the lane boundaries of current lane.
     *
     * @param[in] position The position to obtain laneboundary
     * @param[in] lane_id The lane Id of the target lane
     * @param[in] front_distance Required distance in the front direction
     * @param[in] rear_distance Required distance in the rear direction
     * @param[out] is_left_lane_boundary_forked Is left lane boundary forked or not
     * @param[out] is_right_lane_boundary_forked Is right lane boundary forked or not
     * @return It returns true if we can get the result successfully; Otherwise, it returns false.
     */
    virtual bool_t GetLaneBoundariesForkProperty(const Point3Type& position, const LaneId& lane_id,
                                                 const Scalar front_distance, const Scalar rear_distance,
                                                 bool_t& is_left_lane_boundary_forked,
                                                 bool_t& is_right_lane_boundary_forked) = 0;

    /**
     * @brief Get the left and right lineboundaries based on the input odometry position.
     * @details We firstly match the map with the input position, then if it can match successfully, we will assume
     * the left and right boundaries.
     *
     * @param[in] odometry The matching position with the map
     * @param[out] left_boundary_points The left boundary points of the lane of the matching position
     * @param[out] right_boundary_points The right boundary points of the lane of the matching position
     * @return It returns true if the matching is successfully and we can get the laneboundaries successfully.
     * Otherwise, it returns false.
     */
    virtual bool_t GetTargetLineBoundaries(const OdometryType&                   odometry,
                                           std::vector<std::vector<Point3Type>>& left_boundary_points,
                                           std::vector<std::vector<Point3Type>>& right_boundary_points,
                                           MatchingAttribute&                    matching_attribute) = 0;

    /**
     * @brief Get the multiple matching attribute and lane boundaries based on the input odometry position.
     *
     * @param[in] odometry The matching position with the map
     * @param[out] multi_matching_attribute_and_lane_boundaries The mutiple matching attribute and lane boundaries
     * @return It returns true if get the multiple matching attribute and lane boundaries successfully.
     * Otherwise, it returns false.
     */
    virtual bool_t GetTargetMultiMatchingAttributeAndLaneBoundaries(
        OdometryType const&                              odometry,
        std::vector<MatchingAttributeAndLaneBoundaries>& multi_matching_attribute_and_lane_boundaries) = 0;

    /**
     * @brief Get the special road boundares from the HD map.
     *
     * @param[in] target_position The target position for the requestion.
     * @param[in] coordinate The coordinate.
     * @param[in] parameters The parameters for the reqeustion.
     * @param[out] special_roadboundary_result The result.
     * @return It returns true if we can get the result successfully. Otherwise, it returns false.
     */
    virtual bool_t GetSpecialRoadBoundaries(Point3Type const& target_position, CoordinateType const& coordinate,
                                            SpecialRoadBoundaryTypeRequestParameters const& parameters,
                                            SpecialRoadBoundaryResult& special_roadboundary_result) = 0;

    /**
     * @brief Get the target map feature from HD map.
     *
     * @param [in] odometry The matching position with the map.
     * @param [out] map_objects The object near matching position.
     * @return It returns true if we can get the result successfully. Otherwise, it returns false.
     */
    virtual bool_t GetTargetObjects(OdometryType const& odometry, std::vector<MapObject>& map_objects) = 0;

    /**
     * @brief Judge whether it is the single road around the vehicle. The range of judgement is determined by the
     * distance between "front_distance" and "rear_distance".
     *
     * @param[in] link_id The target link Id
     * @param[in] front_distance The ditance in front of the vehicle
     * @param[in] rear_distance The distance behind the vehicle
     * @param[out] result True: it's in single road. False: not in the main road
     * @return It returns true if we can get the judgement successfully. Otherwise, it returns false.
     */
    virtual bool_t IsWithInSingleRoad(const LinkId& link_id, const Scalar front_distance, const Scalar rear_distance,
                                      bool_t& result) = 0;

    /**
     * @brief Judge whether the lane nubmer changes around the vehicle. The range of judgement is determined by the
     * distance between "front_distance" and "rear_distance".
     *
     * @param[in] link_id The target link Id
     * @param[in] front_distance The ditance in front of the vehicle
     * @param[in] rear_distance The distance behind the vehicle
     * @param[out] result True: it is changed. False: not changed.
     * @return It returns true if we can get the judgement successfully. Otherwise, it returns false.
     */
    virtual bool_t IsLaneNumberChanged(const LinkId& link_id, const Scalar front_distance, const Scalar rear_distance,
                                       bool_t& result) = 0;

    /**
     * @brief Judge whether the type of lane boundary changes around the vehicle. The range of judgement is determined
     * by the distance between "front_distance" and "rear_distance".
     *
     * @param[in] link_id The target link Id
     * @param[in] front_distance The ditance in front of the vehicle
     * @param[in] rear_distance The distance behind the vehicle
     * @param[out] result True: it is changed. False: not changed.
     * @return It returns true if we can get the judgement successfully. Otherwise, it returns false.
     */
    virtual bool_t IsLaneBoundaryTypeChanged(const LinkId& link_id, const Scalar front_distance,
                                             const Scalar rear_distance, bool_t& result) = 0;

    /**
     * @brief Judge whether the lane around the vehicle is parallel. The range of judgement is determined by the
     * distance between "front_distance" and "rear_distance".
     *
     * @param[in] link_id The target link Id
     * @param[in] front_distance The ditance in front of the vehicle
     * @param[in] rear_distance The distance behind the vehicle
     * @param[out] result True: it is parallel. False: not parallel.
     * @return It returns true if we can get the judgement successfully. Otherwise, it returns false.
     */
    virtual bool_t IsLaneParallel(const LinkId& link_id, const Scalar front_distance, const Scalar rear_distance,
                                  bool_t& result) = 0;

    /**
     * @brief Get the lane width in the target link Id. The reference position is the location, which is determined by
     * the odometry requesting the HD map.
     *
     * @param[in] link_id The target link Id
     * @param[out] lane_width_vector The width sequence of the lane in the road. It is arranged from the inside to the
     * outsize of the road
     * @return It returns true if we can get the width successfully. Otherwise, it returns false.
     */
    virtual bool_t GetLaneWidth(const LinkId& link_id, std::vector<Scalar>& lane_width_vector) = 0;

    /**
     * @brief Judge whether two lane Ids are the connected lanes. In other words, they represent the same lane or not.
     *
     * @param[in] lane_id_1 The one Lane Id
     * @param[in] lane_id_2 The another Lane Id
     * @param[in] distance Valid distance between two lanes. If they are too far away from each other, we think they are
     * not connected
     * @param[out] result True means connected; False means Not connected
     * @return It returns true if we can get the judgement successfully. Otherwise, it returns false.
     */
    virtual bool_t AreLanesConnectedDirectly(const LaneId& lane_id_1, const LaneId& lane_id_2, const Scalar& distance,
                                             bool_t& result) = 0;

    /**
     * @brief Judge whether two Link Ids are the connected links. In other words, they represent the same road or not.
     *
     * @param[in] link_id_1 The one Link Id
     * @param[in] link_id_2 The another Link Id
     * @param[in] distance Valid distance between two links. If they are too far away from each other, we think they are
     * not connected
     * @param[in] result True means connected; False means Not connected
     * @return It returns true if we can get the judgement successfully. Otherwise, it returns false.
     */
    virtual bool_t AreLaneGroupsConnectedDirectly(const LinkId& link_id_1, const LinkId& link_id_2,
                                                  const Scalar& distance, bool_t& result) = 0;

    /**
     * @brief Judge whether two Lane Ids are adjacent.
     *
     * @param[in] lane_id_1 The one Lane Id
     * @param[in] lane_id_2 The another Lane Id
     * @param[in] result True means adjacent; False means Not adjacent
     * @return It returns true if we can get the judgement successfully. Otherwise, it returns false.
     */
    virtual bool_t AreLanesAdjacent(const LaneId& lane_id_1, const LaneId& lane_id_2, bool_t& result) = 0;

    /**
     * @brief Override the operator << to realize the format ouput of the matching result struct.
     *
     * @param[in] os The ostream
     * @param[in] result The matching result structure
     * @return The reference of the ostream
     */
    friend std::ostream& operator<<(std::ostream& os, const MatchingResult& result);
};

/**
 * @}
 *
 */

}  // namespace map
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPPLE_FUSION_MAP_MAP_SERVICE_CLIENT_BASE_H_
