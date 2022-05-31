/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_processor.h
 * @brief the definition of lane_processor class
 * @author Zhang Yelin(zhangyelin@holomatic.com)
 * @date 2019-12-03
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_PROCESSOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_PROCESSOR_H_

#include <atomic>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <holo/common/optional.h>
#include <holo/geometry/polyfit2.h>
#include <holo/localization/tightly_coupled_fusion/lane/common.h>
#include <holo/localization/tightly_coupled_fusion/lane/curve_fitter.h>
#include <holo/localization/tightly_coupled_fusion/lane/lane_boundary_matcher.h>
#include <holo/localization/tightly_coupled_fusion/lane/map_points_interpolator.h>
#include <holo/localization/tightly_coupled_fusion/lane/types.h>
#include <holo/localization/tightly_coupled_fusion/map/map_service_client_base.h>
#include <holo/localization/tools/source_checker.h>
#include <holo/os/timer.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
namespace lane
{
/**
 * @addtogroup lane
 * @{
 *
 */

/**
 * @brief This class defines lane processor for get correspondences after preprocessing
 *
 */
class LaneProcessor
{
public:
    /**
     * @brief define shared pointer type name
     *
     */
    using Ptr                 = std::shared_ptr<LaneProcessor>;
    using ConstPtr            = std::shared_ptr<const LaneProcessor>;
    using OdometryInfo        = holo::localization::tightly_coupled_fusion::OdometryInfo;
    using EgoLaneInformation  = holo::localization::tightly_coupled_fusion::EgoLaneInformation;
    using LaneRawMeasurement  = holo::localization::tightly_coupled_fusion::LaneRawMeasurement;
    using LaneRawMeasurements = holo::localization::tightly_coupled_fusion::LaneRawMeasurements;

    using Odometries               = std::vector<OdometryType>;
    using MapPointsInterpolatorPtr = holo::localization::tightly_coupled_fusion::lane::MapPointsInterpolator::Ptr;
    using MapServiceClientBasePtr  = holo::localization::tightly_coupled_fusion::map::MapServiceClientBase::Ptr;
    using LinkId                   = holo::localization::tightly_coupled_fusion::map::MapServiceClientBase::LinkId;
    using MatchingAttribute = holo::localization::tightly_coupled_fusion::map::MapServiceClientBase::MatchingAttribute;

    /**
     * @brief define buffer size
     *
     */
    const static std::size_t kLaneCorrespondenceSize = 25u;  ///< total lane correspondence size

    /**
     * @brief define parameters
     *
     */
    struct Parameters
    {
        /* @brief enable highway switch assist function, If this parameter be set to true, lane localization can still
         * be used when not on main road and vaild lane length will be shorter because of poor detected lane.
         */
        bool_t enable_highway_switch_assist = false;

        /// @brief threshold to determine if the detected lane were confident.
        Scalar min_confidence = Scalar(0.5);

        /// @brief threshold to determine if the detected lane were too wide, unit(m)
        Scalar max_detected_lane_width = Scalar(5.0);

        /// @brief threshold to determine if vehicle were leaving current lane.
        Scalar min_center_ratio = Scalar(0.2);

        /// @brief threshold to determine if all input measurements were acceptable, unit(second)
        Scalar max_measurement_time = Scalar(0.2);

        /// @brief threshold to determine if map points were enough.
        uint64_t min_map_points = 4u;

        /// @brief threshold to determine if map point were in valid range, unit(m)
        Scalar max_lane_length = Scalar(20.0);

        /// @brief threshold to determine if map point were in valid range for poor detection, unit(m)
        Scalar max_lane_length_for_poor_detection = Scalar(2.0);

        /// @brief threshold to determine if two lane boudaries were parallel, unit(degree)
        Scalar min_parallel_error = Scalar(0.2);

        /// @brief threshold to determine if the detected lane were too narrow, unit(m)
        Scalar min_detected_lane_width = Scalar(3.0);

        /// @brief max threshold to determine if the car will change lane, unit(m)
        Scalar max_boundary_lane_width = Scalar(3.7);

        /// @brief min threshold to determine if the car will change lane, unit(m)
        Scalar min_boundary_lane_width = Scalar(0.8);

        /// @brief min threshold to determine if we use the land id, unit(m)
        Scalar min_lane_distance = Scalar(0.15);

        /// @brief min lane segment number
        uint64_t min_lane_segment_number = 5u;

        /// @brief max lane segment number
        uint64_t max_lane_segment_number = 10u;

        /// @brief sample length of detected lane, unit(m)
        Scalar detect_lane_sample_length = Scalar(1.0);

        /// @brief sample length of detected lane for get point in lane boundary, unit(m)
        Scalar sample_length_for_sample_detected_lane = Scalar(3.5);

        /// @brief distance in the front direction for check if lane boundary if forked, unit(m)
        Scalar front_distance_for_forked_laneboundary_check = Scalar(60.0);

        /// @brief distance in the rear direction for check if lane boundary if forked, unit(m)
        Scalar rear_distance_for_forked_laneboundary_check = Scalar(5.0);
        /// @brief extended length before start point and after end point of detected lane for get more map
        /// because map points are sparse, unit(m)
        Scalar extended_length_near_detected_lane = Scalar(10.0);

        /// @brief control parameter of log info
        bool_t verbose = false;

        /// @brief interpolator map points or not
        bool_t enable_interpolate_map_points = true;

        /// @brief control use spline or line to interpolate map points
        bool_t enable_line_interpolate_map_points = true;

        /// @brief control enable input abs odometry as init lane or not
        bool_t enable_abs_odo_as_init_lane = false;

        /// @brief map points interpolator interval, unit(m)
        Scalar map_point_interval = Scalar(0.5);

        /// @brief curverate threshold to judge curve road, unit(1/m)
        Scalar curvature_threshold = Scalar(0.0025);

        /// @brief lane factor noise sigma, unit(m)
        Scalar lane_factor_noise_sigma = Scalar(0.1);

        /// @brief lane noise coefficient, for changable sigma of lane factor
        Scalar lane_noise_coefficient = Scalar(0.008);

        /// @brief minimum longitudinal position for get curvature, unit(m)
        Scalar min_longitudinal_position = Scalar(8.0);

        /// @brief threshold to check if the lane match valid, unit(m)
        Scalar max_lane_match_lane_width = Scalar(4.2);

        /// @brief threshold to check if detected lane diff with lane match distance exceed a certain range, unit(m)
        /// if fabs(left decteted distance - left lane match distance) > detected_with_map_diff, we think is error
        Scalar detected_with_map_diff = Scalar(2.0);

        /// @brief threshold to check if detected lane diff with lane match distance ratio too large, definition is
        /// detected ratio = left detect distance/(detect lane width), lane match ratio = left lane match distance/(map
        /// lane width), if (detected ratio/lane match ratio) > detected_with_map_ratio or (lane match ratio/ detected
        /// ratio) > detected_with_map_ratio. we think it is error
        Scalar detected_with_map_ratio = Scalar(3.5);

        /// @brief where is the map lane boundary extracted in the longitudinal direction of the vehicle. unit(m)
        Scalar map_lane_boundary_extraction_location_longitudinal_offset = Scalar(-8.0);

        /// @brief piecewise value of lateral distance variance scale calculation function, this value is a segmented
        /// value that sets the variance scale for the distance from the detected lane boundary to the body.
        /// eg. piecewise_value_of_lateral_distance_variance_scale_calculation_function = 1.5, then the variance scale
        /// of distance within 1.5 is 1. if distance = 3, the scale = (3/1.5)^2 = 4.
        Scalar piecewise_value_of_lateral_distance_variance_scale_calculation_function = Scalar(1.5);

        ///@brief control algorithm use new mechanism or not.
        bool_t enable_new_association_mechanism = true;

        ///@brief switch of lane factor optimization rotation
        bool_t disable_lane_factor_optimization_rotation = false;

        ///@brief minimum association probability of lane boundary, If the lane line association probability is less
        /// than this value, we do not create lane factor.
        Scalar min_association_probability_of_lane_boundary = 0.1;

        /// @brief param of map points interpolator
        MapPointsInterpolator::Parameters map_points_interpolator_param;

        /// @brief param of lane boundary matcher
        LaneBoundaryMatcher::Parameters lane_boundary_matcher_param;

        /**
         * @brief generate example parameters
         *
         * @return Parameters example parameters
         */
        static Parameters GenerateExample();

        /**
         * @brief output stream for lane processor parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters);

        /**
         * @brief Static method to load parameters from yaml
         *
         * @param[in] node Yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);
    };

    /**
     * @brief define validity of current lane's two laneboundaries
     *
     */
    struct LaneValidity
    {
        /// @brief validity of left laneboundary
        bool_t is_left_lane_boundary_valid = false;

        /// @brief validity of right laneboundary
        bool_t is_right_lane_boundary_valid = false;

        /// @brief validity of this CameraLaneBoundaries
        bool_t is_camera_lane_boundaries_valid = false;
    };

    /**
     * @brief define matching result
     *
     */
    struct MatchingResult
    {
        /// @brief raw measurements of lane preprocessor
        LaneRawMeasurement lane_raw_measurement;

        /// @brief left laneboundary lines
        std::vector<MapPointsType> left_route_lines;

        /// @brief right laneboundary lines
        std::vector<MapPointsType> right_route_lines;

        /// @brief validity of current lane
        LaneValidity lane_validity;

        /// @brief valid lane length, unit(m)
        Scalar valid_lane_length = Scalar(20.0);
    };

    /**
     * @brief define lane boundary association pair struct
     *
     */
    struct LaneBoundaryAssociationPair
    {
        /// @brief detected lane boundary
        CameraLaneBoundaryType detected_lane_boundary;
        /// @brief map lane boundary
        MapPointsType map_lane_boundary;
        /// @brief association probability
        Scalar association_probability;

        /**
         * @brief Construct a new Lane Boundary Association Pair object
         */
        LaneBoundaryAssociationPair(CameraLaneBoundaryType const& _detected_lane_boundary,
                                    MapPointsType const&    _map_lane_boundary,
                                    Scalar const            _association_probability = 1.0)
          : detected_lane_boundary(_detected_lane_boundary)
          , map_lane_boundary(_map_lane_boundary)
          , association_probability(_association_probability)
        {
        }
    };

    /**
     * @brief disable default constructor
     */
    LaneProcessor() = delete;

    /**
     * @brief constructor
     * @param[in] parameters input parameters
     */
    LaneProcessor(const Parameters& parameters) : parameters_(parameters)
    {
        map_interpolator_          = std::make_shared<MapPointsInterpolator>(parameters_.map_points_interpolator_param);
        lane_boundary_matcher_ptr_ = std::make_shared<LaneBoundaryMatcher>(parameters_.lane_boundary_matcher_param);
    }

    /**
     * @brief destructor
     */
    virtual ~LaneProcessor()
    {
    }

    /**
     * @brief Get the Lane Correspondences
     *
     * @param lane_raw_measurements input lane raw measurements
     * @param map_service_client_ptr the map service client smart pointer
     * @return OptionalT<std::vector<LaneCorrespondences>> lane correspondences
     */
    OptionalT<std::vector<LaneCorrespondences>> Run(const LaneRawMeasurements&     lane_raw_measurements,
                                                    const MapServiceClientBasePtr& map_service_client_ptr) const;

    /**
     * @brief get parameters;
     */
    const Parameters& GetParameters() const
    {
        return parameters_;
    }

protected:
    /**
     * @brief run with old association scheme
     *
     * @param lane_raw_measurements lane raw measurements
     * @param map_service_client_ptr the map service client smart pointer
     * @return OptionalT<std::vector<LaneCorrespondences>> lane correspondences
     */
    OptionalT<std::vector<LaneCorrespondences>> runWithOldAssociationScheme(
        const LaneRawMeasurements& lane_raw_measurements, const MapServiceClientBasePtr& map_service_client_ptr) const;

    /**
     * @brief run with new association scheme
     *
     * @param lane_raw_measurements lane raw measurements
     * @param map_service_client_ptr the map service client smart pointer
     * @return OptionalT<std::vector<LaneCorrespondences>> lane correspondences
     */
    OptionalT<std::vector<LaneCorrespondences>> runWithNewAssociationScheme(
        const LaneRawMeasurements& lane_raw_measurements, const MapServiceClientBasePtr& map_service_client_ptr) const;

    /**
     * @brief compute lane boundary association
     *
     * @param lane_raw_measurement last frame of lane raw measurements
     * @param map_service_client_ptr the map service client smart pointer
     * @param lane_boundary_association the result of lane boundary association
     * @param is_on_main_road the flag of whether the vehicle is on the main road
     * @return bool_t return false if can not be computed
     */
    bool_t computeAssociation(LaneRawMeasurement const&                 lane_raw_measurement,
                              MapServiceClientBasePtr const&            map_service_client_ptr,
                              std::vector<LaneBoundaryAssociationPair>& lane_boundary_association,
                              bool_t&                                   is_on_main_road) const;

    /**
     * @brief processing map lane boundary
     *
     *
     * @param origin_points origin points
     * @param processed_points processed points
     * @param lane_segment_number number of lane segment
     * @return bool_t return false if the size of origin_points is too small
     */
    bool_t processingMapLaneBoundary(AdvancedNavstateType const& navstate, MapPointsType const& origin_points,
                                     MapPointsType& processed_points, uint64_t& lane_segment_number) const;

    /**
     * @brief compute lane correspondences
     *
     * @param lane_raw_measurement last frame of lane raw measurements
     * @param lane_boundary_association_vector lane boundary association vector
     * @param is_on_main_road the flag of whether the vehicle is on the main road
     * @param all_lanecorres all lane correspondences
     * @return bool_t return false if can not be computed
     */
    bool_t computeLaneCorrespondences(LaneRawMeasurement const&                       lane_raw_measurement,
                                      std::vector<LaneBoundaryAssociationPair> const& lane_boundary_association_vector,
                                      bool_t const                                    is_on_main_road,
                                      std::vector<LaneCorrespondences>&               all_lanecorres) const;

    /**
     * @brief compute lane boundary association with old method
     *
     * @param lane_raw_measurement last frame of lane raw measurements
     * @param map_service_client_ptr the map service client smart pointer
     * @param lane_boundary_association the result of lane boundary association
     * @param is_on_main_road the flag of whether the vehicle is on the main road
     * @return bool_t return false if can not be computed
     */
    bool_t computeAssociationWithOldMethod(LaneRawMeasurement const&                 lane_raw_measurement,
                                           MapServiceClientBasePtr const&            map_service_client_ptr,
                                           std::vector<LaneBoundaryAssociationPair>& lane_boundary_association,
                                           bool_t&                                   is_on_main_road) const;

    /**
     * @brief compute lane boundary association with new method
     *
     * @param lane_raw_measurement last frame of lane raw measurements
     * @param map_service_client_ptr the map service client smart pointer
     * @param lane_boundary_association the result of lane boundary association
     * @param is_on_main_road the flag of whether the vehicle is on the main road
     * @return bool_t return false if can not be computed
     */
    bool_t computeAssociationWithNewMethod(LaneRawMeasurement const&                 lane_raw_measurement,
                                           MapServiceClientBasePtr const&            map_service_client_ptr,
                                           std::vector<LaneBoundaryAssociationPair>& lane_boundary_association,
                                           bool_t&                                   is_on_main_road) const;

private:
    /**
     * @brief compute the best match result
     *
     * @param lane_raw_measurements vector of lane raw measurements
     * @param map_service_client_ptr the map service client smart pointer
     * @param best_matching_result the best match result
     * @return bool_t true if there is the best match
     */
    bool_t computeBestMatchingResult(const LaneRawMeasurements&     lane_raw_measurements,
                                     const MapServiceClientBasePtr& map_service_client_ptr,
                                     MatchingResult&                best_matching_result) const;

    /**
     * @brief compute matching result
     *
     * @param lane_raw_measurement lane raw measurement
     * @param map_service_client_ptr the map service client smart pointer
     * @param matching_result matching result
     * @return bool_t true if the matching result can used
     */
    bool_t computeMatchingResult(const LaneRawMeasurement&      lane_raw_measurement,
                                 const MapServiceClientBasePtr& map_service_client_ptr,
                                 MatchingResult&                matching_result) const;

    /**
     * @brief up sample map points which are surround of vehicle
     *
     * @param origin_left_points original left lane line points
     * @param origin_right_points original right lane line points
     * @param left_points left lane line points after upsampling
     * @param right_points right lane line points after upsampling
     * @return bool_t true if up sampling possible
     */
    bool_t upSampleMapPoints(const MapPointsType& origin_left_points, const MapPointsType& origin_right_points,
                             MapPointsType& left_points, MapPointsType& right_points) const;

    /**
     * @brief compute number of lane segment
     *
     * @param navstate navstate of vehilce
     * @param origin_left_points original left lane line points
     * @param origin_right_points original right lane line points
     * @param lane_segment_number number of lane segment
     * @return bool_t true if it can be computed
     */
    bool_t computeLaneSegmentNumber(const AdvancedNavstateType& navstate, const MapPointsType& origin_left_points,
                                    const MapPointsType& origin_right_points, uint64_t& lane_segment_number) const;

    /**
     * @brief compute lane correspondences
     *
     * @param matching_result matching result
     * @param map_left_points left lane line points of map after upsampling
     * @param map_right_points right lane line points of map after upsampling
     * @param lane_segment_number number of lane segment
     * @return std::vector<LaneCorrespondences> lane correspondences
     */
    std::vector<LaneCorrespondences> computeLaneCorrespondences(const MatchingResult& matching_result,
                                                                const MapPointsType&  map_left_points,
                                                                const MapPointsType&  map_right_points,
                                                                const uint64_t        lane_segment_number) const;

    /**
     * @brief check input CameraLaneBoundaries is valid or not
     *
     * @param[in] detect_frame input data of detect frame
     * @return LaneValidity contain validity of CameraLaneBoundaries, left lane boundary and right lane boundary
     */
    LaneValidity checkCameraLaneBoundaries(const CameraLaneBoundariesType& detect_frame) const;

    /**
     * @brief fit map points in body
     * @param[in] points_3d_in_world input point in world frame
     * @param[in] odometry input odometry
     * @param[out] coefficients are organized as [c0, c1, c2, c3]T
     * @param[out] points_in_body_plane map points in body plane
     * @return true if succeed estimate lane boundary coeffients.
     * @return false if fail to estimate lane boundary coeffients.
     */
    bool_t fitMapPointInBody(const MapPointsType& points_3d_in_world, const OdometryType& odometry,
                             VectorXType& coefficients, std::vector<Point2Type>& points_in_body_plane) const;

    /**
     * @brief fitting line using fitting lane
     *
     * @param[in] points input points
     * @return holo::OptionalT<Line2Type>
     */
    holo::OptionalT<Line2Type> fittingLine(const std::vector<Point2Type>& points) const;

    /**
     * @brief fitting points group to get line segment group
     *
     * @param[in] points_2d_group input points 2d group
     * @return std::vector<holo::OptionalT<Line2Type>>
     */
    std::vector<holo::OptionalT<Line2Type>>
    fittingLineGroup(const std::vector<std::vector<Point2Type>>& points_2d_group) const;

    /**
     * @brief check if mappoint is valid by prior pose
     *
     * @param[in] map_point input mappoint
     * @param[in] prior_pose prior pose
     * @param[in] region_start start point of detect lane
     * @param[in] region_end end point of detect lane
     * @param[in] valid_range valid range of testing
     * @return true if valid
     * @return false if invalid
     */
    bool_t isPointInValidRange(const Point3Type& map_point, const Pose3Type& prior_pose, Scalar region_start,
                               Scalar region_end, Scalar valid_range) const;

    /**
     * @brief get the map points which are in the projected range of detect lane
     *
     * @param[in] map_points input map points
     * @param[in] prior_pose prior pose
     * @param[in] region_start start point of detect lane
     * @param[in] region_end end point of detect lane
     * @param[in] valid_range input range of detect length which we think is valid
     * @return valid map points which are in the range of detect lane
     */
    std::vector<Point3Type> getPointsInValidRange(const std::vector<Point3Type>& map_points,
                                                  const Pose3Type& prior_pose, Scalar region_start, Scalar region_end,
                                                  const Scalar valid_range) const;

    /**
     * @brief check the vehicle is keep on currenct by single detect lane boundary
     * @param[in] lb lane boundary
     * @return true is keeping on current lane or false if driving out of current lane
     */
    bool_t isKeepingOnSingleLane(const CameraLaneBoundaryType& lb) const;

    /**
     * @brief get curve rate of map points
     * @param[in] coefficients coefficients of fitting map line
     * @param[in] points_in_body map points in body frame
     * @return curve rate of map points
     */
    Scalar getMapCurverate(const VectorXType& coefficients, const std::vector<Point2Type>& points_in_body) const;

    /**
     * @brief check if we reject detected line
     * @param[in] detect_frame detect frame from smart camera
     * @param[in] lane_validity validity of detected lane
     * @param[in] left_lane_match_distance left lane match distance
     * @param[in] right_lane_match_distance right lane match distance
     * @return true if we reject detected line or false if we accept it
     */
    bool_t rejectDetectedLine(const CameraLaneBoundariesType& detect_frame, const LaneValidity& lane_validity,
                              const Scalar left_lane_match_distance, const Scalar right_lane_match_distance) const;

    /**
     * @brief check if we reject single detected lane boundary, if is single lane boundary, we must make sure
     * it is the same lane boundary, we just use it to do lane localization
     * @param detect_lane_validitys vector of detected lane validity
     * @param detect_lane_validity validity of detected lane
     * @return bool_t true if is not same lane boundary
     */
    bool_t rejectSingleLaneBoundary(const std::vector<LaneValidity>& detect_lane_validitys,
                                    const LaneValidity&              detect_lane_validity) const;

    /**
     * @brief get available lane boundary combined detected lane and lane boundary from map data
     * @param[in] is_left_boundary_forked left lane boundary is forked or not, come from map data
     * @param[in] is_right_boundary_forked right lane boundary is forked or not, come from map data
     * @param[in] detect_lane_validity validity of detected lane, which checks detected lane
     */
    void rejectForkedLaneBoundary(const bool_t is_left_boundary_forked, const bool_t is_right_boundary_forked,
                                  LaneValidity& detect_lane_validity) const;

    /**
     * @brief get lane correspondences according to detected lane and map points, using sampled points from detected
     * lane and line fitted by interpolationed map points
     *
     * @param[in] lane_boundary detected lane boundary
     * @param[in] map_points input map points
     * @param[in] prior_pose prior pose
     * @param[in] valid_range input range of detect length which we think is valid
     * @param[in] timestamp timestamp from CameraLaneBoundaries
     * @param[in] lane_segment_number number of lane segment
     * @param[in] detected_lane_length the max selected length of detected lane boundary
     * @param[out] lanecorres lane correspondences from detected lane and map points, in world coordinate frame
     * @param[in] reciprocal_of_association_probability reciprocal of lane boundary association probability
     */
    void getLaneCorrespondencesWorld(const CameraLaneBoundaryType& lane_boundary, const std::vector<Point3Type>& map_points,
                                     const Pose3Type& prior_pose, const Scalar valid_range, const Timestamp& timestamp,
                                     const uint64_t lane_segment_number, const Scalar detected_lane_length,
                                     std::vector<LaneCorrespondences>& lanecorres,
                                     Scalar const reciprocal_of_association_probability = 1.0) const;

    /**
     * @get grouped map points
     * @param[in] map_points input map points from map server
     * @param[in] lane_segment_number segment number of laneboundary
     * @return grouped map points
     */
    std::vector<std::vector<Point3Type>> getGroupMapPoints(const std::vector<Point3Type>& map_points,
                                                           const uint64_t                 lane_segment_number) const;

    /**
     * @brief convert points from 3d to 2d, which means drop z directly
     * @param[in] points_3d 3d points
     * @return 2d points
     */
    std::vector<Point2Type> convert3dto2d(const std::vector<Point3Type>& points_3d) const;

    /**
     * @brief convert points from 3d to 2d, which means drop z directly
     * @param[in] points_3d_group 3d points group
     * @return 2d points group
     */
    std::vector<std::vector<Point2Type>>
    convert3dto2dgroup(const std::vector<std::vector<Point3Type>>& points_3d_group) const;

    /**
     * @brief check if the input point is in the range of grouped map points, all points are in world frame
     * if in range, return the corresponding group of map points
     * @param[in] map_points_group map points group in world frame
     * @param[in] pt input point, which to be checked
     * @return OptionalT<uint64_t>, the index of corresponding group of map points, if fail, return none
     */
    OptionalT<uint64_t> getPointsInRange(const std::vector<std::vector<Point3Type>>& map_points_group,
                                         const Point2Type&                           pt) const;

    /**
     * @brief check if the input point in the range of fitted map line
     * @tparam PointXd the Point type
     * @param[in] pt, input point
     * @param[in] map_points input map points, maybe 2D or 3D
     * @return true if point in the range of fitted map line
     */
    template <typename PointXd>
    bool_t isPointInTheFittedMapLine(const Point2Type& pt, const std::vector<PointXd>& map_points) const;

    /**
     * @brief convert AdvancedNavstate to Odometry
     *
     * @param navstate navstate of vehicle
     * @return OdometryType converted odometry
     */
    OdometryType convertAdvancedNavstateToOdometry(const AdvancedNavstateType& navstate) const;

    /**
     * @brief Set the Z value for Multi Point 3 Type object
     *
     * @param[in] z_value The target z value
     * @param[in, out] multi_point3 The multi points for being setting z value.
     */
    void setZforMultiPoint3Type(Scalar const z_value, std::vector<Point3Type>& multi_point3) const
    {
        for (auto& point : multi_point3)
        {
            point.SetZ(z_value);
        }
    }

private:
    /// define parameter
    Parameters parameters_;

    /// map points interpolator pointer
    MapPointsInterpolatorPtr map_interpolator_;

    /// lane boundary matcher pointer
    LaneBoundaryMatcher::Ptr lane_boundary_matcher_ptr_;

};  // class LaneProcessor

/**
 * @}
 *
 */
}  // namespace lane
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_PROCESSOR_H_