/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ego_lane_estimator.h
 * @brief the definition of lane level localization class
 * @author jiaxing.zhao(zhaojiaxing@holomatic.com)
 * @date 2020-05-19
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_EGO_LANE_ESTIMATOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_EGO_LANE_ESTIMATOR_H_

#include <holo/localization/tightly_coupled_fusion/common_types.h>
#include <holo/localization/tightly_coupled_fusion/lane/common.h>
#include <holo/localization/tightly_coupled_fusion/lane/types.h>
#include <holo/localization/tightly_coupled_fusion/map/map_service_client_base.h>
#include <holo/os/tictoc_timer.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @addtogroup tightly_coupled_fusion
 * @{
 *
 */

/**
 * @brief We design a probabilistic ego-lane estimation algorithm for highway-like scenarios
 *        that is designed to increase the accuracy of the ego-lane estimate, which can be obtained
 *        relying only on a noisy line detector and tracker.
 *
 * @ref Vehicle Ego-Lane Estimation with Sensor Failure Modeling
 */
class EgoLaneEstimator
{
public:
    using MapServiceClientBase              = holo::localization::tightly_coupled_fusion::map::MapServiceClientBase;
    using MapJudgingRoadAttributeParameters = MapServiceClientBase::JudgingRoadAttributeParameters;
    using MapLinkId                         = MapServiceClientBase::LinkId;
    using MapLaneId                         = MapServiceClientBase::LaneId;
    using MapMatchingAttribute              = MapServiceClientBase::MatchingAttribute;
    using MapBoundaryType                   = MapServiceClientBase::BoundaryType;
    using MapBoundaryStyle                  = MapServiceClientBase::BoundaryStyle;
    using MapBoundaryColor                  = MapServiceClientBase::BoundaryColor;
    using MapBoundaryAttribute              = MapServiceClientBase::BoundaryAttribute;
    using MapLaneType                       = MapServiceClientBase::LaneType;
    using MapLaneBoundary                   = MapServiceClientBase::LaneBoundary;
    using MapRoadBoundary                   = MapServiceClientBase::RoadBoundary;
    using MapMatchingResult                 = MapServiceClientBase::MatchingResult;
    using MapServiceClientBasePtr           = MapServiceClientBase::Ptr;
    using MapRoadAttribute                  = MapServiceClientBase::RoadAttribute;
    using MatchingParameters                = MapServiceClientBase::MatchingParameters;

    using OdometryCallback = std::function<int32_t(const OdometryType&)>;
    using Ptr              = std::shared_ptr<EgoLaneEstimator>;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /**
     * @brief  The parameters used to the preprocess of the ego lane estimator
     */
    struct PreprocessParameters
    {
        /// The min distance between the target position and the matching link bottom (head) (Unit: m)
        Scalar min_distance_to_link_bottom = Scalar(100.0);
        /// The min distance between the target position and the matching link top (tail) (Unit: m)
        Scalar   min_distance_to_link_top = Scalar(100.0);
        uint16_t min_matching_confidence  = 90u;          ///< The min confidenc of the matching result
        Scalar   min_valid_lane_width     = Scalar(1.5);  ///< The min width of the valid and believable lane (Unit: m)
        /// The minimum length of all the laneboundaries under the current line type (Unit: m)
        Scalar min_length_of_same_lane_type = Scalar(80.0);
    };

    /**
     * @brief The sensors state parameters which constrains the maximum, minimum and increment of sensor transition
     * state
     *
     */
    struct SensorTransitionStateParameters
    {
        /// The maximum probability of the sensor transition state from ok to ok
        Scalar max_sensor_state_ok_to_ok = Scalar(0.7);
        /// The minimum probability of the sensor transition state from ok to ok
        Scalar min_sensor_state_ok_to_ok = Scalar(0.1);
        /// The step increment value of the probability of the sensor transition state from ok to ok
        Scalar step_increment = Scalar(0.05);
    };

    /**
     * @brief Define parameters of ego lane estimator
     */
    struct Parameters
    {
        MatchingParameters   map_matching_parameter;  ///< The parameters to matching map
        PreprocessParameters preprocess_parameter;    ///< The preprocess relative parameters

        Scalar detect_lane_sample_valid_range = Scalar(50.0);  ///< Sample valid range of detected lane (Unit: meter)
        Scalar detect_lane_sample_length      = Scalar(0.5);   ///< Sample length of detected lane (Unit: meter)
        Scalar threshold_tracker_mean         = Scalar(0.1);   ///< Threshold mean value of tracker (Unit: meter)
        Scalar threshold_tracker_stdev        = Scalar(0.1);   ///< Threshold stdev value of tracker (Unit: meter)
        /// The minimum time difference between the DR odometry and CameraLaneBoundaries to find the nearest DR odometry
        Scalar   min_time_diff_between_dr_and_camera_lane_boundaries = Scalar(0.04);  ///< Unit: second
        uint16_t max_line_reliability_index   = 30u;           ///< The max LRI value when track the lines
        uint16_t min_line_reliability_index   = 15u;           ///< The min LRI to judge the line is valid

        /** If the line has the continuous flag set, an additional Bonus Value (BV) is added to the tentative vector
         * position */
        uint16_t bonus_value               = 1u;
        Scalar   normal_distribution_sigma = Scalar(0.6);  ///< Normal distribution sigma
        Scalar   min_confidence = Scalar(0.5);  ///< Threshold to determine smart line if the detected lane were confident
        /// The min probability gap of the first and second largest state values.
        Scalar min_probability_gap = Scalar(0.15);
        /// The max distance threshold used for judging the adjacent links or lanes
        Scalar max_adjacent_lane_or_link_distance = Scalar(200.0);  ///< Unit: meters
        /// The min value of the counter of the output continuous same lane
        uint16_t min_output_consistency_counter = 5u;

        /// The duration to recovery the lane changing flag to false
        Scalar lane_changing_flag_recoverying_duration = Scalar(3.0);
        /// The percentage of the lane width to judge the vehicle is changing lane
        Scalar                          width_percentage_to_judge_lane_changing = Scalar(0.1);
        SensorTransitionStateParameters sensor_transition_state_param;  ///< The sensors state parameter

        bool_t enable_bonus_value   = false;  ///< The switch to enable the bonus value
        bool_t enable_visualization = true;   ///< Enable the visualization of the estimated ego lane
        bool_t verbose              = false;  ///< Enable the verbose output of log information
        /// Enable the output consitency check. Only continuous N outputs are same, we return
        bool_t enable_output_consistency_check = false;

        /**
         * @brief Static method to load parameters from yaml
         *
         * @param[in] node Yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief Output stream overloading for EgoLaneEstimator's parameter
         *
         * @param[in] os std::ostream&
         * @param[in] parameters Parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const parameters);
    };

    /**
     * @brief Line property
     */
    struct LineProperties
    {
        bool_t         is_valid;                ///< valid or invalid
        bool_t         is_continuous;           ///< detected line is continuous or not
        LaneBoundaryId line_id;                 ///< line id
        Scalar         line_reliability_index;  ///< line reliability index
        Scalar         lateral_offset;          ///< lateral offset
    };

    /**
     * @brief Frame property which converted from the smart camera data
     */
    struct FrameProperties
    {
        /// The detected lines properties, they are sorted by the order: left_2, left_1, right_1, right_2
        std::vector<LineProperties> detected_lines_properties;
        Timestamp                   timestamp;  ///< The frame timestamp
    };

    /**
     * @brief The lane property from the map matching results. It contails all the map lane information needed for our
     * ego-lane estimator.
     */
    struct MapLaneProperty
    {
        MapLaneId            lane_id              = 0u;  /// The default lane id is 0, means invalid.
        MapLaneType          lane_type            = MapLaneType::LANE_TYPE_UNKNOWN;
        Scalar               width                = Scalar(0.0);  ///< The lane width (Unit: meter)
        Scalar               left_boundary_length = Scalar(0.0);  ///< The left lane boundary length (Unit: meter)
        MapBoundaryType      left_boundary_type   = MapBoundaryType::BOUNDARY_TYPE_UNKNOWN;
        MapBoundaryAttribute left_boundary_attribute;              ///< The left laneboundary attribute
        Scalar               right_boundary_length = Scalar(0.0);  ///< The left lane boundary length (Unit: meter)
        MapBoundaryType      right_boundary_type   = MapBoundaryType::BOUNDARY_TYPE_UNKNOWN;
        MapBoundaryAttribute right_boundary_attribute;  ///< The right laneboundary attribute
    };

    /**
     * @brief The structure to keep the Line Tracker state
     *
     */
    struct LineTrackerState
    {
        bool_t    is_initialized = false;                     ///< The flag of initialization
        CameraLaneBoundariesType last_camera_lane_boundaries; ///< The last CameraLaneBoundaries measurement
        /// The last DR navstate measurement which is corresponding to the timestamp of the last CameraLaneBoundaries
        StampedAdvancedNavstate last_dr_navstate;
        /// The line realiability index of each detected line (From Left2nd to Right2nd, totally 4 lines)
        std::array<uint16_t, 4u> line_reliability_indices = {{0u, 0u, 0u, 0u}};
    };

    /**
     * @brief This enum defines the status of the Result to diagnose what happens for current result.
     *
     */
    enum class DiagnosisStatus : uint16_t
    {
        ALL_GOOD                     = 0x0000,
        INVALID_RAW_MEASUREMENTS     = 0x0001,
        REQUESTING_MAP_FAILURE       = 0x0002,  ///< Can get the map responsed result.
        INVALID_MAP_MATCHING_RESULTS = 0x0004,  ///< Map data failed validity check.
        LINE_TRACKER_FAILURE         = 0x0008,
        EMPTY_VALID_DETECTED_LINES   = 0x0010,  ///< Can get the invalid line properties from detected lines.
        LANE_MAP_MATCHING_FAILURE    = 0x0020,  ///< Can match the map lines and detected lines.
        UNCERTAIN_HMM_STATE          = 0x0040,  ///< Can get clear lane ID from the HMM state.
        POST_CHECK_FAILURE           = 0x0080,  ///< Failed in post check for illegal lane changing.
        CONSISTENCY_CHECK_FAILURE    = 0x0100,  ///< Result consistency can't meet the requirements.
        UNKNOWN                      = 0xFFFF,  ///< Unknown status. Except for the above status.
    };

    /**
     * @brief Define the ego-lane estimator output result.
     *
     */
    struct Result
    {
        Timestamp                     timestamp = Timestamp();
        DiagnosisStatus               status;
        OptionalT<EgoLaneInformation> ego_lane_information;

        /**
         * @brief Construct a new Ego Lane Result object
         *
         * @param _timestamp The current timestamp
         * @param _status The EgoLane diagnosis status
         * @param _ego_lane_information The EgoLaneInformation
         */
        Result(Timestamp const& _timestamp = Timestamp(), DiagnosisStatus const& _status = DiagnosisStatus::UNKNOWN,
               OptionalT<EgoLaneInformation> const& _ego_lane_information = optional::none)
          : timestamp(_timestamp), status(_status), ego_lane_information(_ego_lane_information)
        {
        }
    };
    using Results = std::vector<Result>;

    /**
     * @brief The state of the post process of the ego lane estimator
     *
     */
    struct PostProcessState
    {
        VectorXType        last_hmm_state;                         ///< The HMM state of last iteration
        EgoLaneInformation last_lane_inforamtion;                  ///< The EgoLane information of last iteration
        uint16_t           counter_for_continuous_same_lane = 0u;  ///< The output counter for the continuous same lane
    };

    /**
     * @brief The class to describe the vehicle is in the process of the lane change or not.
     * @attention It is a pre declaration, and the specific implementation is at the end.
     *
     */
    class LaneChangingFlag;

    /**
     * @brief The class to describe the Sensor transition state including 'state_from_ok_to_ok',
     * 'state_from_ok_to_bad', 'state_from_bad_to_ok' and 'state_from_bad_to_bad'.
     * @attention It is a pre declaration, and the specific implementation is at the end.
     *
     */
    class SensorTransitionState;

    /**
     * @brief Delete default constructor
     *
     */
    EgoLaneEstimator() = delete;

    /**
     * @brief Default constructor
     *
     * @param[in] params The parameter of ego lane estimator
     */
    EgoLaneEstimator(const Parameters& params) noexcept;

    /**
     * @brief Destructor
     */
    ~EgoLaneEstimator() noexcept;

    /**
     * @brief Run the ego lane estimator to estimate which lane the vehicle is in
     *
     * @param[in] raw_measurement The raw measurements we need to estimate the ego lane
     * @param[in] map_service_client_ptr The map service client smart pointer
     * @return The egolane results for the each CameraLaneBoundaries input.
     */
    Results Run(const EgoLaneRawMeasurements& raw_measurement, const MapServiceClientBasePtr& map_service_client_ptr);

    /**
     * @brief Set the odometry callback for visualization
     *
     * @param[in] handler Odometry callback handler
     */
    void SetLaneIdOdometryCallback(const OdometryCallback& handler) noexcept
    {
        odometry_lane_id_cb_ = handler;
    }

protected:
    /**
     * @brief Initialize HMM state at time t
     *
     * @param[in] num_lanes The number of lanes got from HDMap
     * @return The HMM state
     */
    VectorXType initializeHMMStateXt(uint8_t const& num_lanes) const noexcept;

    /**
     * @brief Compute the normal distribution value
     *
     * @param[in] x The target point
     * @param[in] mu The mean of the normal distribution
     * @param[in] sigma The covariance of the normal distribution
     * @return Normal distribution variable
     */
    Scalar computePdfOfNormalDistribution(Scalar const x, Scalar const mu, Scalar const sigma) const;

    /**
     * @brief Compute basic transition Matrix
     *
     * @param[in] num_lanes The number of the lanes
     * @param[in] sigma The covariance of the normal distribution
     * @return The basic transition matrix
     */
    MatrixXType computeBasicTransitionMatrix(uint8_t const num_lanes, Scalar const sigma) const;

    /**
     * @brief Compute transition state Matrix
     *
     * @param[in] basic_transition_matrix The basic transition matrix
     * @return The transition state matrix
     */
    MatrixXType computeTransitionStateMatrix(MatrixXType const& basic_transition_matrix) const;

    /**
     * @brief Compute tentative vector
     *
     * @param[in] frame_properties The input frames properties
     * @param[in] map_lines_arrangement The lines arrangement known from the HDmap. The true means continuous line,
     * The false means dashed line
     * @param[in] valid_nums_lane The number of valid lanes. The 'valid lanes' is the lane where the vehicle may
     * travel
     * @param[in] enable_bonus_value The switch whether we enable the bonus value when we detect the continuous
     * line. True: enable, False, disable
     * @param[in, out] tentative_vector The computed tentative vector
     * @return It return true we compute successfully. Otherwise, we return false
     */
    bool_t computeTentativeVector(FrameProperties const&     frame_properties,
                                  std::vector<bool_t> const& map_lines_arrangement, uint8_t valid_nums_lane,
                                  bool_t enable_bonus_value, VectorXType& tentative_vector) const;

    /**
     * @brief Get the line properties from the input laneboundary
     *
     * @param[in] lb The laneboundary
     * @param[in] lb_id The corresponding laneboundary ID
     * @return OptionalT<LineProperties>. It return optional::none if the input laneboundary is invalid
     */
    OptionalT<LineProperties> computeLineProperty(const CameraLaneBoundaryType& lb, LaneBoundaryId lb_id) const;

    /**
     * @brief Get the frame properties from the input CameraLaneBoundaries
     *
     * @param[in] detect_frame The detected CameraLaneBoundaries
     * @param[in] line_tracker_state The line tracker state for all detected line
     * @return Optional<FrameProperties>. It return optional::none if we don't detect valid laneboundary
     */
    OptionalT<FrameProperties> computeCameraLaneProperties(const CameraLaneBoundariesType& detect_frame,
                                                      const LineTrackerState& line_tracker_state) const;

    /**
     * @brief Update the HMM state vector
     *
     * @param[in] tentative_vector The tentative vector
     * @param[in] valid_lane_num The number of current valid lanes
     * @param[in] sensor_score_ok The sensor score which represents the sensor is ok
     * @param[in, out] hmm_state The updated HMM state
     * @return It returns true if it sucesses, otherwise, it return false.
     */
    bool_t updateHmmState(const VectorXType& tentative_vector, const uint16_t& valid_lane_num,
                          const Scalar sensor_score_ok, VectorXType& hmm_state) const;

    /**
     * @brief Get the ego lane result from the current HMM state and find the corresponding lane ID from the
     * map lane properties.
     *
     * @param[in] hmm_state The HMM state
     * @param[in] map_lane_properties The map lane properties
     * @param[in] min_probability_gap The min probability gap of the first and second largest state values. If it is
     * less than the gap, we assume we don't find the valid lane Id result.
     * @param[out] lane_id The estimated lane id
     * @return It returns true if it can find the result. Otherwise, it returns false.
     */
    bool_t getEgoLaneResult(const VectorXType& hmm_state, const std::vector<MapLaneProperty>& map_lane_properties,
                            const Scalar min_probability_gap, MapLaneId& lane_id) const;

    /**
     * @brief Compute the sensor score that represents OK
     *
     * @param[in] frame_properties The properties of the detected CameraLaneBoundaries
     * @return The score of the sensor is OK
     */
    Scalar computeSensorScoreOK(const FrameProperties& frame_properties) const;

    /**
     * @brief Compute sensor score that represents Bad
     *
     * @param[in] sensor_score_ok The score of the sensor is OK
     * @return The score of the sensor is bad
     */
    Scalar computeSensorScoreBad(const Scalar& sensor_score_ok) const;

    /**
     * @brief Line Tracker
     *
     * @param[in] last_line_time The timestamp of last line
     * @param[in] current_line_time The timestamp of current line
     * @param[in] last_navstate The last navstate of the vehicle
     * @param[in] current_navstate The current navstate of the vehicle
     * @param[in] detected_last_lane_boundary The last detected laneboundary
     * @param[in] detected_current_lane_boundary The current detected laneboundary
     * @return It return false if the last or current laneboundary is valid, or if the line tracker fails.
     * Otherwise, we return true
     *
     * @todo Make this function as an independent class for future expansion.
     */
    bool_t lineTracker(Timestamp const& last_line_time, Timestamp const& current_line_time,
                       StampedAdvancedNavstate const& last_navstate, StampedAdvancedNavstate const& current_navstate,
                       CameraLaneBoundaryType const& detected_last_lane_boundary,
                       CameraLaneBoundaryType const& detected_current_lane_boundary) const;

    /**
     * @brief Compute distance from point to laneboundary
     *
     * @param[in] detected_lane The detected laneboundary
     * @param[in] point The 2D point in the plane of the laneboundary
     * @param[in] check_range The flag to check the lane boundary valid range or not.
     * @return The distance from point to laneboundary. If the point is over the range of the laneboundary when we
     * enbale the switch of checking range, it returns optional::none.
     */
    OptionalT<Scalar> computeDistanceFromPointToLane(CameraLaneBoundaryType const& detected_lane, Point2Type const& point,
                                                     bool_t const check_range = true) const;

    /**
     * @brief compute lateral offset between the vehicle and the laneboundary
     *
     * @param[in] lb The laneboundary
     * @return The lateral offset
     */
    Scalar computeLateralOffset(CameraLaneBoundaryType const& lb) const;

    /**
     * @brief Judge whether the line is solid or dashed
     *
     * @param[in] lb The laneboundary
     * @return OptionalT<It returns true if it is continuous>. It returns optional::none if we can't judge it is
     * solid or dashed.
     */
    OptionalT<bool_t> isSolidLine(const CameraLaneBoundaryType& lb) const;

    /**
     * @brief Judge whether the raw measurement meets the requirements to estimate ego lane
     *
     * @param[in] raw_measurement The raw measurement
     * @return It returns true if it is valid and meets the requirements
     */
    bool_t isRawMeasurementValid(const EgoLaneRawMeasurements& raw_measurement) const;

    /**
     * @brief Get the line type arrangement from the detected line properties.
     * @details For example, if the detected line is (LEFT_1ST: continuous, RIGHT_1ST: dashed).
     * The arrangement is (continuous, none, dashed). We will set the line type of the missing line in the middle to
     * optional::none
     *
     * @param[in] frame_properties The detected line properties
     * @return The line type arrangement. It is arranged from left to right. And the True means continuous line, and
     * the False means dashed line. The optional::none means there is a missing line but we can't know what type it
     * is.
     */
    std::vector<OptionalT<bool_t>> getLineTypeArrangement(const FrameProperties& frame_properties) const;

    /**
     * @brief We resize the state vector with the target size.
     * @details If the size of the input state vector is not equal to the target size, we will resize it.
     * (1) If the size of the vector is larger than the set value, the redundant part is deleted;
     * (2) If the size of the vector is less than the set value, the original vector is expanded and the newly added
     * part is set to 0;
     * @throw std::runtime_error If the target size is not even or the size of state vector is not even
     *
     * @param[in] size The target size
     * @param[in, out] state_vector The updated state vector
     */
    void resizeStateVector(const std::size_t size, VectorXType& state_vector) const;

    /**
     * @brief Run the publisher and visualization for the estimated lane Id.
     * @details  We use target lane midpoint and reference attitude of the coarse odometry to
     * construct an odoemtry and output it, so that it can be visualized on the simulator.
     *
     * @param[in] coarse_navstate The reference pose for getting its rotation as the output rotation
     * @param[in] link_id The estimated link Id
     * @param[in] lane_id The estimated lane Id
     * @param[in] map_service_client_ptr The map service client result
     */
    void runPublisherAndVisualization(const StampedAdvancedNavstate& coarse_navstate, const MapLinkId& link_id,
                                      const MapLaneId&               lane_id,
                                      const MapServiceClientBasePtr& map_service_client_ptr) const;
    /**
     * @brief Check whether the matching road is the complex road.
     * @details The complex road means: 1. the vehicle isn't in the single road.
     * 2. the surrounding lane number changes.
     * 3. the surrounding lind type changes.
     * 4. the surrounding lane is not parallel.
     *
     * @param[in] matching_result The map matching result
     * @return It returns true if it is in complex road. Otherwise, it returns false.
     */
    bool_t isComplexRoads(const MapMatchingResult& matching_result) const;

    /**
     * @brief Check whether the matching result is trusted.
     * @details We have the following assumptions: (1) The matching confidence is too low to be trusted;
     * (2) Close to the top and bottom of the link is not trusted. Because we think the borderline of the link is
     * changeable and complex, the smart camera and the map date have high probability of error.
     *
     * @param[in] matching_result The map matching result
     * @return It returns true if it is trusted. Otherwise, it returns false.
     */
    bool_t isTrustedMatch(const MapMatchingResult& matching_result) const;

    /**
     * @brief Check the boundaries distribution rationality.
     * @details We think that for two adjacent laneboundaries, the lane Id and type on the right side of the left
     * laneboundary should be equal to the lane Id and type on the left side of the right laneboundary.
     *
     * @param[in] road_boundaries The road boundaries getted from the map client
     * @return It returns true if it is rational. Otherwise, it returns false.
     */
    bool_t checkBoundariesDistributionRationality(const MapRoadBoundary& road_boundaries) const;

    /**
     * @brief Convert the road boundary to the map lane preperties.
     * @attention Please check the connection validity of the boundaries distribution before call this function.
     *
     * @param[in] road_boundaries The road boundaries getted from the map client
     * @param[out] lane_properties The lane properties based on the road boundary information
     * @return It returns true if it converts successfully. Otherwise, it returns false.
     */
    bool_t convertRoadBoundaryToMapLaneProperties(const MapRoadBoundary&        road_boundaries,
                                                  std::vector<MapLaneProperty>& lane_properties) const;

    /**
     * @brief Because the lane width information is existed in the road attribute result, we need get the lane
     * widths from it and assign them to each lane one by one.
     *
     * @param[in] road_attribute The road attribute getted from the map client
     * @param[out] lane_properties The lane properties which have been set the lane width
     * @return It returns true if we assign successfully. Otherwise, it returns false.
     */
    bool_t assignLaneWidthFromRoadAttributeToLaneProperties(const MapRoadAttribute&       road_attribute,
                                                            std::vector<MapLaneProperty>& lane_properties) const;

    /**
     * @brief Remove non-driving lane on the current road and check the rest whether is valid or believable
     * @details Case 1: In fact, the lanes in the map data include the hard shoulder type and the narrow emergency
     * lane. It will be not detected by the smart and can't drive. So we need to reject it. Case 2: If the
     * non-driving lane exists on the middle of the road, not on both sides, it means the map data is wrong or the
     * road is complex. We will return false.
     *
     * @param[in, out] lane_properties The lane properties removed the non-driving lanes
     * @return It returns true if it rejects successfull. Otherwise, it returns false when the rest is valid because
     * the data is wrong or is complex.
     */
    bool_t removeNonDrivingLaneAndCheckRest(std::vector<MapLaneProperty>& lane_properties) const;

    /**
     * @brief Confirm the lane properties whether meets the ego-lane positioning requirements
     * @details The requirements includes: (1) The leftmost lane must have a left laneboundary;
     * (2) The length of all the laneboundaries under the current line type should not be less than the threshold.
     * (3) The all laneboundaries has the clear line type (dashed or continous), rather than the unknown.
     *
     * @param[in] lane_properties The lane properties
     * @return It returns true if it meets the requirements. Otherwise, it returns false.
     */
    bool_t confirmLanePropertiesMeetsPositioningRequirement(const std::vector<MapLaneProperty>& lane_properties) const;

    /**
     * @brief Get the line type arrangement of the map laneboundaries and get the number of the valid lane.
     * @details The lines arrangement is from the left to right. The true means continuous line, The false means
     * dashed line. The 'valid lanes' is the lane where the vehicle may travel.
     *
     * @param[in] lane_properties The lane properties after preprocess
     * @param[out] line_arrangement The map line type arrangement
     * @param[out] valid_lane_num The number of the valid lane
     * @return It returns true if we can get successfully. Otherwise, it returns false.
     */
    bool_t getMapLineTypeArrangement(const std::vector<MapLaneProperty>& lane_properties,
                                     std::vector<bool_t>& line_arrangement, uint16_t& valid_lane_num) const;

    /**
     * @brief Preprocess the map matching result and convert it to the lane properties. It will return false if the
     * preprocess fails. There are the following cases:
     * (1) Is in a complex road; (2) Matching result isn't trusted; (3) The map lane boundaries are wrong;
     * (4) The map line arrangement is not meet the ego-lane positioning requirements.
     *
     * @param[in] map_matching_result The map matching result
     * @param[out] lane_properties The lane properties converted from the matching result
     * @return It returns true if it convert successfully. Othewise, it returns false.
     */
    bool_t preprocessMapMatchingResult(const MapMatchingResult&      map_matching_result,
                                       std::vector<MapLaneProperty>& lane_properties) const;

    /**
     * @brief Run the Line Tracker to check the CameraLaneBoundaries and update the LRI for each laneboundary
     *
     * @param[in] camera_lane_boundaries The current CameraLaneBoundaries measurement
     * @param[in] dr_navstates The DR navstate sequence including the relative pose corresponding to the
     * timestamp of the input CameraLaneBoundaries
     * @param[in, out] line_tracker_state The line tracker state which will be updated
     * @return It returns true if it processes the tracker normally. Otherwise, It returns false.
     *        False case: 1) There is no DR odometry which its timestamp is closed to the CameraLaneBoundaries
     *                    2) The LineTracker is not intialized.
     */
    bool_t runLineTracking(const CameraLaneBoundariesType& camera_lane_boundaries, 
                           const std::vector<StampedAdvancedNavstate>& dr_navstates,
                           LineTrackerState& line_tracker_state) const;

    /**
     * @brief Get the Nearest Measurement from the vector sequence
     *
     * @tparam T The vector type
     * @param[in] timestamp The target timestamp
     * @param[in] measurements The measurements vector sequence
     * @param[out] target The return value
     * @return It returns true if it can get successfully. Otherwise, it returns false.
     */
    template <typename T>
    bool_t getNearestMeasurement(const Timestamp& timestamp, const std::vector<T>& measurements, T& target) const;

    /**
     * @brief Reject the invalid line properties from the FrameProperties
     *
     * @param[in, out] frame_properties The FrameProperties structure
     * @return It returns true if it is successful. Otherwise, it returns false.
     */
    bool_t rejectInvalidDetectedLineProperties(FrameProperties& frame_properties) const;

    /**
     * @brief Get the main road lane width from the map lane properties
     *
     * @param[in] map_lane_property The map lane properties
     * @return It returns the width if the optional is valid. Otherwise, it returns none.
     */
    OptionalT<Scalar> getMainRoadLaneWidth(const std::vector<MapLaneProperty>& map_lane_property) const;

    /**
     * @brief Judge whether the vehicle is changing lane
     * @details We think that when the vehicle approaches the lane line on both sides, the vehicle is in lane
     * changing state. Therefore, we use the distance between the vehicle and the left or right lane lines to judge
     *
     * @param[in] detected_frame_properties The detected frame properties
     * @param[in] lane_width The lane width for one lane
     * @return It returns true if the vehicle is changing lane. Otherwise, it returns false.
     */
    bool_t isVehicleChangingLane(const FrameProperties&   detected_frame_properties,
                                 const OptionalT<Scalar>& lane_width) const;

    /**
     * @brief Run the post process to check whether current ego lane result is valid or not
     * @details We use the following rules to judge: (1) It is impossible for a vehicle to change two lanes
     * instantaneously; (2) The vehicle did not change lanes, but the lane ID changed.
     *
     * @param[in] map_service_client_ptr The map service client smart pointer
     * @param[in, out] current_hmm_state The current hmm state. If the current result is invalid, it will recovry
     * the last state.
     * @param[in, out] current_result The current egolane result. If it is invalid, it will recovery the last
     * result.
     * @param[in, out] post_process_state The post process state. If the current result is invalid, it will be reset
     * to none.
     * @param[in, out] sensor_state The sensor transition state. If the current result is invalid, it will be reset.
     * @return It returns true if the input ego lane result has passed athe validity check. Otherwise, it returns
     * false.
     */
    bool_t runPostProcess(const MapServiceClientBasePtr& map_service_client_ptr, VectorXType& current_hmm_state,
                          EgoLaneInformation& current_result, OptionalT<PostProcessState>& post_process_state,
                          std::shared_ptr<SensorTransitionState>& sensor_state) const;

    /**
     * @brief To check whether all the timestamps of the source measurements exist in the timestamp sets.
     *
     * @tparam T The type of the source measurements.
     * @param[in] timestamp_sets The timestamp sets waiting for being checked.
     * @param[in] source_measurements The source measurements with the timestamps.
     *
     * @return It returns true if all the timestamps of the source measurements exist in the timestamp sets.
     * Otherwise, it returns false.
     */
    template <typename T>
    bool_t checkAllTimestampExist(std::set<Timestamp> const& timestamp_sets,
                                  std::vector<T> const&      source_measurements) const
    {
        for (T const& m : source_measurements)
        {
            if (timestamp_sets.find(m.GetTimestamp()) == timestamp_sets.end())
            {
                LOG(WARNING) << "EgoLane->RawMeasurements: we can't find the time in DR: " << std::setprecision(15)
                             << m.GetTimestamp().ToSec();
                return false;
            }
        }
        return true;
    }

    /**
     * @brief To construct the Result according to the  timestamp of the input sequences.
     * @note The input type of the sequences must have the interface "GetTimestamp" to get its timestamp.
     *
     * @tparam T The template type.
     * @param[in] sequences_with_timestamps The sequence datas with the corresponding timestamp.
     * @param[in] status The diagnosis status of the Result.
     * @param[in] ego_lane_information The ego lane information.
     * @return Results
     */
    template <typename T>
    Results
    constructEgoLaneResultsBasedOnSequenceTimestamp(T const& sequences_with_timestamps, DiagnosisStatus const& status,
                                                    OptionalT<EgoLaneInformation> const& ego_lane_information) const
    {
        Results ego_lane_results;

        for (auto iter = std::begin(sequences_with_timestamps); iter != std::end(sequences_with_timestamps); ++iter)
        {
            ego_lane_results.emplace_back(Result(iter->GetTimestamp(), status, ego_lane_information));
        }

        return ego_lane_results;
    }

    /**
     * @brief Override the operator << to realize the format output of the MapLaneProperty structure
     *
     * @param[in] os The ostream
     * @param[in] lane_property The map lane property
     * @return The ostream
     */
    friend std::ostream& operator<<(std::ostream& os, const MapLaneProperty& lane_property);

    /**
     * @brief Override the operator << to realize the format output of the sequence of the MapLaneProperty structure
     *
     * @param[in] os The ostream
     * @param[in] lane_properties The sequence of map lane property
     * @return The ostream
     */
    friend std::ostream& operator<<(std::ostream& os, const std::vector<MapLaneProperty>& lane_properties);

    /**
     * @brief Override the operator << to realize the format output of the FrameProperties
     *
     * @param[in] os The ostream
     * @param[in] frame_properties The frame properties
     * @return The ostream
     */
    friend std::ostream& operator<<(std::ostream& os, const FrameProperties& frame_properties);

private:
    const Parameters params_;                ///< Parameters
    VectorXType      hmm_state_;             ///< Current HMM state
    bool_t           is_initialized_;        ///< The flag of which the estimator has been intialized
    int8_t           est_lane_id_;           ///< The estimated lane ID
    bool_t           is_first_est_lane_id_;  ///< Judge whether it is the first estimation of lane ID

    /// The odometry with the estimated lane ID information for visualization
    OdometryCallback odometry_lane_id_cb_;

    int8_t   last_lane_id_;     ///< Last estimated lane ID
    uint32_t lane_id_counter_;  ///< Lane id counter which used to judge whether the consecutive lane IDs are same

    LineTrackerState                       line_tracker_state_;       ///< The state of line tracker
    std::shared_ptr<LaneChangingFlag>      lane_changing_flag_ptr_;   ///< The lane changing flag
    std::shared_ptr<SensorTransitionState> sensor_transition_state_;  ///< The sensors transition state for prediction
    OptionalT<PostProcessState>            post_process_state_;  ///< The post process state (none means uninitialized)

};  // namespace EgoLaneEstimator

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief This function is used to realize the format output of the line arrangament result.
 *
 * @param[in] os The ostream
 * @param[in] line_arrangement The line arrangement
 * @return The ostream
 */
std::ostream& operator<<(std::ostream& os, const std::vector<bool_t>& line_arrangement);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief The class to describe the vehicle is in the process of the lane change or not.
 *
 */
class EgoLaneEstimator::LaneChangingFlag
{
public:
    /**
     * @brief Disable the default constructor.
     *
     */
    LaneChangingFlag() = delete;

    /**
     * @brief Construct a new Lane Changing flag object
     *
     * @param[in] duration The recoverying duration of the changing lane state
     */
    LaneChangingFlag(const Scalar duration) : recoverying_duration_(duration), tictoc_timer_(), is_changing_lane_(false)
    {
    }

    /**
     * @brief Set the changing lane flag
     *
     * @param[in] flag The updated changing lane flag
     */
    void SetFlag(const bool_t flag)
    {
        is_changing_lane_ = flag;
        tictoc_timer_.Tic();
    }

    /**
     * @brief Get the changing lane flag
     *
     * @return True: means that the vehicle is changing state
     *         False: means that the vehicle is not changing state
     */
    bool_t GetFlag()
    {
        /// Recovery the flag if a duration has passed since the last setting
        if (is_changing_lane_ && (tictoc_timer_.Elapsed() > recoverying_duration_))
        {
            is_changing_lane_ = false;
        }
        return is_changing_lane_;
    }

private:
    const Scalar      recoverying_duration_;  ///< The recovering duration of the is changing lane flag(Unit: second)
    holo::TicTocTimer tictoc_timer_;          ///< The tictor timer for recoverying the is_changing_lane flag
    bool_t            is_changing_lane_;      ///< The flag of the vehicle is changing lane or not
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief The class to describe the Sensor transition state including 'state_from_ok_to_ok', 'state_from_ok_to_bad',
 * 'state_from_bad_to_ok' and 'state_from_bad_to_bad'.
 *
 */
class EgoLaneEstimator::SensorTransitionState
{
public:
    /**
     * @brief Construct a new Sensor Transition State
     *
     * @param[in] sensor_ok_to_ok The probability of the sensor state from ok to ok
     */
    SensorTransitionState(const SensorTransitionStateParameters& param = SensorTransitionStateParameters())
      : parameter_(param), sensor_ok_to_ok_(Scalar(0.5))
    {
    }

    /**
     * @brief Reset the sensor transition state
     *
     * @param[in] sensor_ok_to_ok he probability of the sensor state from ok to ok
     */
    void Reset(const Scalar& sensor_ok_to_ok)
    {
        sensor_ok_to_ok_ = sensor_ok_to_ok;
    }

    /**
     * @brief Reset the sensor transition state
     *
     * @param[in] sensor_ok_to_ok The probability of the sensor state from ok to ok
     */
    void Reset()
    {
        sensor_ok_to_ok_ = parameter_.min_sensor_state_ok_to_ok;
    }

    /**
     * @brief Increase the sensor transition state by one step increment
     *
     */
    void IncreaseSensorTransitionState()
    {
        sensor_ok_to_ok_ = std::min(sensor_ok_to_ok_ + parameter_.step_increment, parameter_.max_sensor_state_ok_to_ok);
    }

    /**
     * @brief Get the probability of the sensor state from ok to ok
     *
     * @return The probability of the sensor state from ok to ok
     */
    Scalar GetOKToOkProbability()
    {
        return sensor_ok_to_ok_;
    }

    /**
     * @brief Get the probability of the sensor state from ok to bad
     *
     * @return The probability of the sensor state from ok to bad
     */
    Scalar GetOKToBadProbability()
    {
        return 1.0 - sensor_ok_to_ok_;
    }
    /**
     * @brief Get the probability of the sensor state from bad to ok
     *
     * @return The probability of the sensor state from bad to ok
     */
    Scalar GetBadToOkProbability()
    {
        return sensor_ok_to_ok_;
    }

    /**
     * @brief Get the probability of the sensor state from bad to bad
     *
     * @return The probability of the sensor state from bad to bad
     */
    Scalar GetBadToBadProbability()
    {
        return 1.0 - sensor_ok_to_ok_;
    }

private:
    const SensorTransitionStateParameters parameter_;
    Scalar                                sensor_ok_to_ok_;  ///< The probability of the sensor state from ok to ok
};

/**
 * @}
 *
 */

}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_EGO_LANE_ESTIMATOR_H_
