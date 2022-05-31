/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fusion_estimator.h
 * @brief header file for fusion estimator
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-03-15"
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_FUSION_ESTIMATOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_FUSION_ESTIMATOR_H_

#include <holo/localization/tightly_coupled_fusion/common_types.h>
#include <holo/localization/tightly_coupled_fusion/ego_lane_determiner.h>
#include <holo/localization/tightly_coupled_fusion/fusion_initializer.h>
#include <holo/localization/tightly_coupled_fusion/graph_builder.h>
#include <holo/localization/tightly_coupled_fusion/lane/lane_processor.h>
#include <holo/localization/tightly_coupled_fusion/measurements_smoother.h>
#include <holo/localization/tightly_coupled_fusion/sign/visual_semantic_processor.h>

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
 * @brief this class aims to estimate fusion result from the given measurements
 * @details 0. do initialization with FusionInitializer first time and repeat 1-5
 *          1. determine link id and lane id by EgoLaneDeterminer
 *          2. do data association between hd map and smart camera
 *          3. prepare imu, gnss, wheel measurements
 *          4. create factor graph and initial values with GraphBuilder
 *          5. optimize the initial values to get fusion state
 */
class FusionEstimator
{
public:
    using Ptr                           = std::shared_ptr<FusionEstimator>;
    using MapServiceClientBase          = holo::localization::tightly_coupled_fusion::map::MapServiceClientBase;
    using MapServiceClientBasePtr       = EgoLaneDeterminer::MapServiceClientBasePtr;
    using LaneProcessor                 = holo::localization::tightly_coupled_fusion::lane::LaneProcessor;
    using VisualSemanticProcessor       = holo::localization::tightly_coupled_fusion::sign::VisualSemanticProcessor;
    using VisualSemanticCorrespondences = holo::localization::VisionSemanticCorrespondences;
    using MeasurementsSmoother          = holo::localization::tightly_coupled_fusion::MeasurementsSmoother;

    struct Parameters
    {
        Scalar                              lag_size;                        ///< size of fixed lag smoother
        GTISAM2Params                       isam2_parameters;                ///< parameters for optimizer
        FusionInitializer::Parameters       fusion_initializer_parameters;   ///< parameters for fusion initializer
        EgoLaneDeterminer::Parameters       ego_lane_determiner_parameters;  ///< parameters for ego lane estimator
        LaneProcessor::Parameters           lane_processor_parameters;       ///< parameters for lane processor
        VisualSemanticProcessor::Parameters visual_semantic_processor_parameters;  ///< parameters for visual semantic
                                                                                   ///< processor
        GraphBuilder::Parameters         graph_builder_parameters;                 ///< parameters for graph builder
        MeasurementsSmoother::Parameters measurements_smoother_parameters;  ///< parameters for measurements smoother

        /**
         * @brief parameters for factors
         */
        boost::shared_ptr<GTPreintegrationParams> pim_parameters;  ///< pim parameters including imu noise covariance,
                                                                   ///< gravity
        PreintegrationWheelParams pwm_parameters;                  ///< pwm parameters including velocity covariance
        GTVector3                 sigmas_for_velocity_factor;      ///< sigmas for velocity factor
        GTVector6 sigmas_for_pose_between_factor_when_zero_velocity;  ///< sigmas for pose between factor when velocity
                                                                      ///< is zero
        GTVector6 sigmas_for_imu_bias_between_factor;  ///< sigmas for bias between factor(random walk noise)
        GTVector6 sigmas_for_prior_pose;               ///< sigmas for prior pose factor
        GTVector3 sigmas_for_prior_velocity;           ///< sigmas for prior velocity factor
        GTVector6 sigmas_for_prior_imu_bias;           ///< sigmas for prior imu bias factor

        Scalar optimization_state_frequency;  ///< frequency of to add optimization state
        bool_t enable_compute_covariance;     ///< whether compute covariance of each variable

        ///@brief The local gravity calculation relative parameters
        Scalar local_gravity_update_interval = 3600;  ///< The time interval to update the local gravity. Unit: second.
        bool_t enable_local_gravity_update =
            true;  ///< Enable the local gravity update, which is based on the local position.

        /**
         * @brief constructor
         *
         * @param[in] _lag_size size of fixed lag smoother
         * @param[in] _isam2_parameters parameters for optimizer
         * @param[in] _fusion_initializer_parameters parameters for fusion initializer
         * @param[in] _ego_lane_determiner_parameters parameters for ego lane determiner
         * @param[in] _lane_processor_parameters parameters for lane processor
         * @param[in] _graph_builder_parameters parameters for graph builder
         * @param[in] _measurements_smoother_parameters parameters for measurements smoother
         * @param[in] _pim_parameters parameters for PIM
         * @param[in] _pwm_parameters parameters for PWM
         * @param[in] _sigmas_for_velocity_factor sigmas for velocity factor
         * @param[in] _sigmas_for_pose_between_factor_when_zero_velocity sigmas for between factor when velocity is zero
         * @param[in] _sigmas_for_imu_bias_between_factor sigmas for imu bias between factor
         * @param[in] _sigmas_for_prior_pose sigmas for prior pose
         * @param[in] _sigmas_for_prior_velocity sigmas for prior velocity
         * @param[in] _sigmas_for_prior_imu_bias sigmas for prior imu bias
         * @param[in] _optimization_state_frequency frequency for the optimization state
         * @param[in] _enable_compute_covariance whether compute covariance for each navstate
         * @param[in] _local_gravity_update_interval The time interval to update the local gravity. Unit: second.
         * @param[in] _enable_local_gravity_update The flag to enable the local gravity update
         */
        Parameters(Scalar _lag_size, GTISAM2Params const& _isam2_parameters,
                   FusionInitializer::Parameters const&             _fusion_initializer_parameters,
                   EgoLaneDeterminer::Parameters const&             _ego_lane_determiner_parameters,
                   LaneProcessor::Parameters const&                 _lane_processor_parameters,
                   VisualSemanticProcessor::Parameters const&       _visual_semantic_processor_parameters,
                   GraphBuilder::Parameters const&                  _graph_builder_parameters,
                   MeasurementsSmoother::Parameters const&          _measurements_smoother_parameters,
                   boost::shared_ptr<GTPreintegrationParams> const& _pim_parameters,
                   PreintegrationWheelParams const& _pwm_parameters, GTVector3 const& _sigmas_for_velocity_factor,
                   GTVector6 const& _sigmas_for_pose_between_factor_when_zero_velocity,
                   GTVector6 const& _sigmas_for_imu_bias_between_factor, GTVector6 const& _sigmas_for_prior_pose,
                   GTVector3 const& _sigmas_for_prior_velocity, GTVector6 const& _sigmas_for_prior_imu_bias,
                   Scalar const _optimization_state_frequency, bool_t const _enable_compute_covariance,
                   Scalar const _local_gravity_update_interval = Scalar(3600.0),
                   bool_t const _enable_local_gravity_update   = true)
          : lag_size(_lag_size)
          , isam2_parameters(_isam2_parameters)
          , fusion_initializer_parameters(_fusion_initializer_parameters)
          , ego_lane_determiner_parameters(_ego_lane_determiner_parameters)
          , lane_processor_parameters(_lane_processor_parameters)
          , visual_semantic_processor_parameters(_visual_semantic_processor_parameters)
          , graph_builder_parameters(_graph_builder_parameters)
          , measurements_smoother_parameters(_measurements_smoother_parameters)
          , pim_parameters(_pim_parameters)
          , pwm_parameters(_pwm_parameters)
          , sigmas_for_velocity_factor(_sigmas_for_velocity_factor)
          , sigmas_for_pose_between_factor_when_zero_velocity(_sigmas_for_pose_between_factor_when_zero_velocity)
          , sigmas_for_imu_bias_between_factor(_sigmas_for_imu_bias_between_factor)
          , sigmas_for_prior_pose(_sigmas_for_prior_pose)
          , sigmas_for_prior_velocity(_sigmas_for_prior_velocity)
          , sigmas_for_prior_imu_bias(_sigmas_for_prior_imu_bias)
          , optimization_state_frequency(_optimization_state_frequency)
          , enable_compute_covariance(_enable_compute_covariance)
          , local_gravity_update_interval(_local_gravity_update_interval)
          , enable_local_gravity_update(_enable_local_gravity_update)
        {
        }

        /**
         * @brief output stream for fusion parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters)
        {
            os << "FusionEstimator::Parameters :"
               << "\n lag_size = " << parameters.lag_size << std::endl;
            parameters.isam2_parameters.print("FusionEstimator::ISAM2");
            os << "\n"
               << parameters.fusion_initializer_parameters << "\n"
               << parameters.ego_lane_determiner_parameters << "\n"
               << parameters.lane_processor_parameters << "\n"
               << parameters.visual_semantic_processor_parameters << "\n"
               << parameters.graph_builder_parameters << "\n"
               << parameters.measurements_smoother_parameters << std::endl;
            parameters.pim_parameters->print("FusionEstimator::PIM");
            os << "\n pwm_parameters::VelocityCovariance = " << parameters.pwm_parameters.velocity_covariance
               << "\n sigmas_for_velocity_factor = " << parameters.sigmas_for_velocity_factor.transpose()
               << "\n sigmas_for_pose_between_factor_when_zero_velocity = "
               << parameters.sigmas_for_pose_between_factor_when_zero_velocity.transpose()
               << "\n sigmas_for_imu_bias_between_factor = "
               << parameters.sigmas_for_imu_bias_between_factor.transpose()
               << "\n sigmas_for_prior_pose = " << parameters.sigmas_for_prior_pose.transpose()
               << "\n sigmas_for_prior_velocity = " << parameters.sigmas_for_prior_velocity.transpose()
               << "\n sigmas_for_prior_imu_bias = " << parameters.sigmas_for_prior_imu_bias.transpose()
               << "\n optimization_state_frequency = " << parameters.optimization_state_frequency
               << "\n enable_compute_covariance = " << parameters.enable_compute_covariance
               << "\n local_gravity_update_interval = " << parameters.local_gravity_update_interval
               << "\n enable_local_gravity_update = " << parameters.enable_local_gravity_update << std::endl;
            return os;
        }

        /**
         * @brief static method to load parameters from yaml
         *
         * @param[in] node yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief static method to generate example parameters for unit test
         *
         * @return Parameters
         */
        static Parameters GenerateExample();
    };  // Parameters

    /**
     * @brief status of fusion estimator
     */
    enum class Status : uint32_t
    {
        ALLGOOD                            = 0x00000000,  ///< successfully return
        INITIALIZATION_FAILURE             = 0x00000001,  ///< failure due to initialization failure
        MAP_SERVICE_CONNECTION_FAILURE     = 0x00000002,  ///< can not connect to map service
        MAP_DATA_UNAVALIABLE               = 0x00000004,  ///< map data is not avaliable
        INVALID_INITIAL_LANE               = 0x00000008,  ///< initial lane is invalid
        NO_LANE_CORRESPONDENCES            = 0x00000010,  ///< no lane correspondences is created
        TRAJECTORY_JUMPING                 = 0x00000020,  ///< trajectory jumping occurs
        SMOOTHER_UPDATE_EXCEPTION          = 0x00000040,  ///< failure due to exception of smoother.update
        SMOOTHER_CALCULATE_EXCEPTION       = 0x00000080,  ///< failure due to exception of smoother.calculateEstimate
        SMOOTHER_MARGINAL_EXCEPTION        = 0x00000100,  ///< failure due to exception of smoother.MarginalCovariance
        NO_VISUAL_SEMANTIC_CORRESPONDENCES = 0x00000200,  ///< no visual semantic correspondences is created
        EGO_LANE_DETERMINER_ERROR          = 0x00000400,  ///< fatal due to ego lane determiner error.
    };

    /**
     * @brief constructor
     *
     * @param[in] parameters parameters for fusion estimator
     */
    FusionEstimator(Parameters const& parameters);

    /**
     * @brief destructor
     */
    ~FusionEstimator();

    /**
     * @brief do data association and optimization
     *
     * @param[in] fusion_raw_measurements measurements for fusion
     * @param[in] map_service_client_ptr the map service client smart pointer
     * @param[in][out] state optimized state for fusion
     * @param[in] optinal_initial_navstate_and_imu_bias optional navstate and imu bias used to provide initial state
     * @return Status status of fusion estimator
     */
    Status Run(FusionRawMeasurements const&   fusion_raw_measurements,
               MapServiceClientBasePtr const& map_service_client_ptr, FusionState& state,
               FusionInitializer::OptionalStampedGTNavStateAndImuBias const& optional_initial_navstate_and_imu_bias =
                   optional::none);

protected:
    /**
     * @brief add predicted navstate and imu bias into graph builder measurements
     * @note graph_builder_measurements will be changed
     *
     * @param[in] multi_stamped_gt_navstate_and_imu_bias predicted navstate and imu bias
     * @param[in][out] graph_builder_measurements graph builder measurements which wil be changed
     */
    void addNewPredictedNavStateAndImuBias(
        std::vector<StampedGTNavStateAndImuBias> const& multi_stamped_gt_navstate_and_imu_bias,
        GraphBuilder::Measurements&                     graph_builder_measurements) const;

    /**
     * @brief create a piror factor measurements and update graph builder measurements
     * @note graph_builder_measurements will be changed
     *
     * @param[in] multi_stamped_gt_navstate_and_imu_bias measurements for prior factor
     * @param[in] parameters parameters used to construct prior factor
     * @param[in][out] graph_builder_measurements graph builder measurements which wil be changed
     * @return GTFastMap<Timestamp, AdvancedNavstateType::Source> timestamp and source pair which indicate the
     * measurements at the give timestamp
     */
    GTFastMap<Timestamp, AdvancedNavstateType::Source> createPriorFactorMeasurements(
        std::vector<StampedGTNavStateAndImuBias> const& multi_stamped_gt_navstate_and_imu_bias,
        Parameters const& parameters, GraphBuilder::Measurements& graph_builder_measurements) const;

    /**
     * @brief create a prior pose factor measurement and update graph_builder_measurements
     * @note graph_builder_measurements will be changed
     *
     * @param[in] prior_pose measurement for prior pose factor
     * @param[in] sigmas noise sigma for the measurement
     * @param[in] timestamp timestamp of the measurement
     * @param[in][out] graph_builder_measurements graph builder measurements which wil be changed
     */
    void createPriorPoseFactorMeasurement(GTPose3 const& prior_pose, GTVector6 const& sigmas,
                                          Timestamp const&            timestamp,
                                          GraphBuilder::Measurements& graph_builder_measurements) const;

    /**
     * @brief create a prior velocity factor measurement and update graph_builder_measurements
     * @note graph_builder_measurements will be changed
     *
     * @param[in] prior_velocity measurement for prior velocity factor
     * @param[in] sigmas noise sigma for the measurement
     * @param[in] timestamp timestamp of the measurement
     * @param[in][out] graph_builder_measurements graph builder measurements which wil be changed
     */
    void createPriorVelocityFactorMeasurement(GTVector3 const& prior_velocity, GTVector3 const& sigmas,
                                              Timestamp const&            timestamp,
                                              GraphBuilder::Measurements& graph_builder_measurements) const;

    /**
     * @brief create a prior imu bias factor measurement and update graph_builder_measurements
     * @note graph_builder_measurements will be changed
     *
     * @param[in] prior_imu_bias measurement for prior imu bias factor
     * @param[in] sigmas noise sigma for the measurement
     * @param[in] timestamp timestamp of the measurement
     * @param[in][out] graph_builder_measurements graph builder measurements which wil be changed
     */
    void createPriorImuBiasFactorMesurement(GTConstantBias const& prior_imu_bias, GTVector6 const& sigmas,
                                            Timestamp const&            timestamp,
                                            GraphBuilder::Measurements& graph_builder_measurements) const;

    /**
     * @brief construct factor measurements and update graph builder measurements
     *
     * @param[in] fusion_raw_measurements raw measurements for fusion
     * @param[in] parent_coordinate parent coordinate of gnss pvt
     * @param[in] optional_multi_lane_correspondence optional lane correspondences from CameraLaneBoundaries and HD map data
     * association
     * @param[in] optional_multi_visual_semantic_correspondence optional visual semantic correspondences from keypoint
     * and HD map data association
     * @param[in] last_stamped_gt_navstate_and_imu_bias last stamped navstate and imu bias from previous optimization
     * @param[in] parameters parameters used to construct factor measurements
     * @param[in][out] graph_builder_measurements graph builder measurements which wil be changed
     * @return GTFastMap<Timestamp, AdvancedNavstateType::Source> timestamp and source pair which indicate the
     * measurements at the give timestamp
     */
    GTFastMap<Timestamp, AdvancedNavstateType::Source> updateGraphBuilderMeasurements(
        FusionRawMeasurements const& fusion_raw_measurements, CoordinateType const& parent_coordinate,
        OptionalT<std::vector<LaneCorrespondences>> const&           optional_multi_lane_correspondence,
        OptionalT<std::vector<VisualSemanticCorrespondences>> const& optional_multi_visual_semantic_correspondence,
        StampedGTNavStateAndImuBias const& last_stamped_gt_navstate_and_imu_bias, Parameters const& parameters,
        GraphBuilder::Measurements& graph_builder_measurements) const;

    /**
     * @brief create combined velocity measurement
     *
     * @param[in] multi_corrected_vehicle_velocity the input corrected vehicle velocity data
     * @param[in] pim preintegrated imu measurement whose time interval is aligned with multi_corrected_vehicle_velocity
     * @param[in] parameters fusion estimator parameters
     * @return StampedCombinedVelocityMeasurement stamped combined velocity measurement
     */
    StampedCombinedVelocityMeasurement createCombinedVelocityMeasurement(
        std::vector<StampedCorrectedVehicleVelocity> const& multi_corrected_vehicle_velocity,
        GTPreintegratedImuMeasurements const& pim, Parameters const& parameters) const;

    /**
     * @brief check zero velocity condition and add zero velocity factor
     *
     * @param[in] delta_translation the translation between two adjacent pose
     * @param[in] velocity velocity at {timestamp}
     * @param[in] timestamp timestamp of current pose
     * @param[in] parameters parameters used to construct factor measurements
     * @param[in][out] graph_builder_measurements graph builder measurements which wil be changed
     */
    void createZeroVelocityMeasurement(Scalar const delta_translation, Scalar const velocity,
                                       Timestamp const& timestamp, Parameters const& parameters,
                                       GraphBuilder::Measurements& graph_builder_measurements) const;

    /**
     * @brief update source object in timestamp_source_map at the given timestamp
     *
     * @param[in] timestamp the given timestamp, source at which will be updated
     * @param[in] new_source the given source used to update
     * @param[in][out] timestamp_source_map timestamp-source map which will be updated
     */
    void updateTimestampSourceMap(Timestamp const& timestamp, AdvancedNavstateType::Source const& new_source,
                                  GTFastMap<Timestamp, AdvancedNavstateType::Source>& timestamp_source_map) const;

    /**
     * @brief update source object timestamp and graph builder measurements
     *
     * @param[in] correspondences correspondences
     * @param[in] new_source the given new source
     * @param[in][out] multi_sensor_timestamp the given timestamp, source at which will be updated
     * @param[in][out] timestamp_source_map timestamp-source map which will be updated
     * @param[in][out] measurements graph builder measurements will be updated
     */
    template <typename T>
    void collectSensorTimestampAndUpdateGraphBuilderMeasurements(
        OptionalT<std::vector<T>> const& correspondences, AdvancedNavstateType::Source const& new_source,
        std::set<Timestamp>&                                multi_sensor_timestamp,
        GTFastMap<Timestamp, AdvancedNavstateType::Source>& timestamp_source_map, std::vector<T>& measurements) const;

    /**
     * @brief output fusion estimator status according to visual status
     *
     * @param[in] VisualSemanticProcessor::STATUS status of visual semantic processor
     * return FusionEstimator::Status status
     */
    FusionEstimator::Status
    convertVisualSemanticStatusToFusionEstimatorStatus(VisualSemanticProcessor::Status const& status) const;

    /**
     * @brief generate state timestamp with constant frequency and sensor timestamp
     * @note the user should gaurantee that ${right} is bigger than ${left}
     * @details let frequency = 10, left = Timestamp(1.0), right = Timestamp(2.0)
     *          multi_sensor_timestamp = Timestamp{0.1, 1.04, 1.24, 1.57, 1.97, 2.1}
     *  step1: generate uniform timestamp with the given frequency multi_state_timestamp =
     *         Timestamp{1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0}
     *  step2: loop timestamp in multi_sensor_timestamp and replace the nearest timestamp in multi_state_timestamp,
     * and drop it if it is not in interval [left, right] Timestamp(0.1) dropped Timestamp(1.04) added into
     * ${multi_state_timestamp}, Timestamp(1.24) replace Timestamp(1.2) in ${multi_state_timestamp} Timestamp(1.57)
     * replace Timestamp(1.6) in ${multi_state_timestamp} Timestamp(1.97) added into ${multi_state_timestamp}
     *         Timestamp(2.1) dropped
     *   step3: result = Timestamp{1.0, 1.04, 1.1, 1.24, 1.3, 1.4, 1.5, 1.57, 1.7, 1.8, 1.9, 1.97, 2.0}
     *
     * @param[in] frequency the give state frequency
     * @param[in] left left end of time interval
     * @param[in] right right end of time interval
     * @param[in] multi_sensor_timestamp timestamp of sensor measurements
     * @return std::set<Timestamp> state timestamp which insert sensor timestamp into the uniform state timestamp
     */
    std::set<Timestamp> generateStateTimestamp(Scalar const frequency, Timestamp const& left, Timestamp const& right,
                                               std::set<Timestamp> const& multi_sensor_timestamp) const;

    /**
     * @brief update fusion state with the optimzied values from new factor graph
     *
     * @param[in] graph_builder_measurements graph builder measurements which contain new factor measurements
     * @param[in] new_problem new problem with new sub factor graph, new values and key timestamp map
     * @param[in] timestamp_source_map timestamp and source pair which indicate the measurements at the give
     * timestamp
     * @param[in][out] state fusion state which will be updated
     * @return Status status of fusion estimator
     */
    Status updateFusionState(GraphBuilder::Measurements const&                         graph_builder_measurements,
                             GraphBuilder::Problem const&                              new_problem,
                             GTFastMap<Timestamp, AdvancedNavstateType::Source> const& timestamp_source_map,
                             FusionState&                                              state) const;

    /**
     * @brief construct advanced navstate with optimzied variables
     *
     * @param[in] optimized_pose optimized pose
     * @param[in] optimized_velocity optimized velocity
     * @param[in] optimized_bias optimized imu bias
     * @param[in] optimized_pose_covariance covariance of optimized pose
     * @param[in] optimized_velocity_covariance covariance of optimzed velocity
     * @param[in] optimized_bias_covariance covariance of optimized imu bias
     * @param[in] source source of the advanced navstate
     * @param[in] parent_coordinate parent coordinate of advanced navstate
     * @param[in][out] advanced_navstate advanced navstate which will be updated
     */
    void constructAdvancedNavstate(GTPose3 const& optimized_pose, GTVector3 const& optimized_velocity,
                                   GTConstantBias const& optimized_bias, GTMatrix6 const& optimized_pose_covariance,
                                   GTMatrix3 const&                    optimized_velocity_covariance,
                                   GTMatrix6 const&                    optimized_bias_covariance,
                                   AdvancedNavstateType::Source const& source, CoordinateType const& parent_coordinate,
                                   AdvancedNavstateType& advanced_navstate) const;

    /**
     * @brief Update the local gravity of the fusion state and the pim parameters based on the fusion_state's stamped
     * navstate. Only when the local gravity is calculated for the first time or the time from the last calculation
     * exceeds the threshold (parameters_.local_gravity_uptate_interval), the local gravity of the fusion state and the
     * pim parameters will be updated and return true.
     *
     * @param[in, out] fusion_state The fusion state. Its stamped navstates will be used to compute the local gravity.
     * And its local_gravity will be updated when the condition is met.
     * @param[out] pim_parameters The pim parameters, which's local gravity will be updated when the condition is met.
     * @return Whether the local gravity is calculated or not. True: have calculated. False: can't calculated.
     */
    bool_t updateLocalGravity(FusionState&                               fusion_state,
                              boost::shared_ptr<GTPreintegrationParams>& pim_parameters) const;

protected:
    Parameters              parameters_;                 ///< parameters for fusion estimator
    FusionInitializer       fusion_initializer_;         ///< initializer to prepare initial state for the estimator
    EgoLaneDeterminer       ego_lane_determiner_;        ///< ego lane determiner used to determine link id and lane id
    LaneProcessor           lane_processor_;             ///< lane processor used to do lane data association
    GraphBuilder            graph_builder_;              ///< graph builder used to create factor graph
    VisualSemanticProcessor visual_semantic_processor_;  ///< visual semantic processor used to create factor graph
    MeasurementsSmoother    measurements_smoother_;      ///< measurements smoother used to smooth measurements

};  // FusionEstimator

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_FUSION_ESTIMATOR_H_
