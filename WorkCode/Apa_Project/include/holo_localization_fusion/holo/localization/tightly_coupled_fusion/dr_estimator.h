/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file dr_estimator.h
 * @brief this file defines DrEstimator
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @author MaYufei(mayufei@holomatic.com)
 * @date 2021-02-08
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_DR_ESTIMATOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_DR_ESTIMATOR_H_

#include <thread>

#include <holo/localization/common/localization_base.h>
#include <holo/localization/sam/factors/prior_rpy_factor.h>
#include <holo/localization/sam/factors/wheel_speed_factor.h>
#include <holo/localization/sam/sam.h>
#include <holo/localization/sam/type_converter.h>
#include <holo/localization/tightly_coupled_fusion/common_types.h>
#include <holo/localization/tightly_coupled_fusion/dr_integrator.h>
#include <holo/localization/tightly_coupled_fusion/failure_detector.h>
#include <holo/localization/tightly_coupled_fusion/graph_builder.h>
#include <holo/localization/tightly_coupled_fusion/imu_stationary_calibrator.h>
#include <holo/localization/tightly_coupled_fusion/measurements_manager_fusion.h>
#include <holo/localization/tightly_coupled_fusion/utils/common_functions.h>
#include <holo/localization/tightly_coupled_fusion/vehicle_velocity_corrector.h>

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
 * @brief DrEstimator provides dead reckoning functionality
 *
 * @details The core algorithm fuses imu and wheel speed measurements and outputs a continuous smoothing local odometry
 *
 */
class DrEstimator : public LocalizationBase
{
public:
    using Base                             = LocalizationBase;
    using MeasurementsManagerFusionPtr     = MeasurementsManagerFusion::Ptr;
    using StampedPim                       = MeasurementsManagerFusion::StampedGTPreintegratedImuMeasurements;
    using StampedCvm                       = StampedCombinedVelocityMeasurement;
    using VehicleVelocityCorrectorConstPtr = VehicleVelocityCorrector::ConstPtr;
    using StampedImuStationaryResult       = ImuStationaryCalibrator::StampedImuStationaryResult;

    // gtsam related types, can be moved to sam.h
    using GTKeyTimestampMap      = GTFixedLagSmoother::KeyTimestampMap;
    using GTPriorPose3Factor     = GTPriorFactor<GTPose3>;
    using GTPriorVelocity3Factor = GTPriorFactor<GTVelocity3>;
    using GTPriorBiasFactor      = GTPriorFactor<GTConstantBias>;
    using GTBiasBetweenFactor    = GTBetweenFactor<GTConstantBias>;
    using GTPimParamsPtr         = boost::shared_ptr<GTPreintegrationParams>;

    // callback function to output error code
    using ErrorCodeCallback = std::function<void(uint8_t const, bool_t const)>;

    /**
     * @brief define parameters
     *
     */
    struct Parameters
    {
        Scalar frequency;
        bool_t enable_estimator;  ///< parameters to enable or disable dr estimator thread
        bool_t enable_integrator;
        bool_t enable_medium_before_fusion_is_high_precision;  ///< parameters for switch to dr estimator in advance
                                                               ///< without waiting fusion is  high precision
        DrIntegrator::Parameters integrator_parameters;        ///< dr integrator parameters

        Scalar        lag_size;          ///< size of fixed lag smoother
        GTISAM2Params isam2_parameters;  ///< parameters for optimizer

        GraphBuilder::Parameters graph_builder_parameters;  ///< parameters for graph builder

        GTPimParamsPtr pim_parameters;  ///< pim parameters including imu noise covariance, gravity
        GTVector6 sigmas_for_pose_between_factor_when_zero_velocity;  ///< sigmas for pose between factor when velocity
                                                                      ///< is zero
        GTVector6 sigmas_for_imu_bias_between_factor;  ///< sigmas for bias between factor(random walk noise)
        GTVector6 sigmas_for_prior_pose;               ///< sigmas for prior pose factor
        GTVector3 sigmas_for_prior_velocity;           ///< sigmas for prior velocity factor
        GTVector6 sigmas_for_prior_imu_bias;           ///< sigmas for prior imu bias factor
        GTVector3 sigmas_for_prior_rpy;                ///< sigmas for prior rpy factor

        bool_t                      enable_compute_covariance;  ///< whether compute covariance of each variable
        FailureDetector::Parameters failure_detector_params;    ///< failure detector paremeters

        /**
         * minimum number to confirm the navstate is high navstate,i.e.when the number of high precision navstate
         * is larger than the threshold, the navstate is valid high precision
         */
        uint8_t min_num_for_valid_high_precision;

        /**
         * minimum number to confirm the navstate is low navstate,i.e. when the number of low precision navstate is
         * larger than the threshold, the navstate is valid low precision
         */
        uint8_t min_num_for_valid_low_precision;

        /**
         * angle trust region near pi which is used to judge the difference between this two values, unit, rad
         * this param is used because the rpy is decomposed by atan2, which is easy to jump to -pi when the value is
         * near pi
         */
        Scalar angle_trust_region_near_pi;

        /**
         * parameter to judge whether the delta_fusion_yaw change more than threshold, which is defined by the ratio
         * between std::abs(predicted_delta_dr_yaw) - std::abs(delta_fusion_yaw) and std::abs(predicted_delta_dr_yaw).
         * When the change ratio is larger than this threshold, the yaw constrain will not be added
         */
        Scalar yaw_angle_change_ratio;
        bool_t enable_yaw_constraint;  ///< parameter to enable yaw constraint

        /**
         * @brief
         *
         * @param os
         * @param params
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& params)
        {
            os << "DrEstimator::Parameters : \n"
               << "frequency = " << params.frequency << "\n"
               << "enable_estimator = " << params.enable_estimator << "\n"
               << "enable_integrator = " << params.enable_integrator << "\n"
               << "enable_medium_before_fusion_is_high_precision = "
               << params.enable_medium_before_fusion_is_high_precision << "\n"
               << params.integrator_parameters << "lag_size = " << params.lag_size << "\n";
            params.isam2_parameters.print("DrEstimator");
            os << "\n";
            os << params.graph_builder_parameters;
            params.pim_parameters->print("DrEstimator");
            os << "sigmas_for_pose_between_factor_when_zero_velocity = "
               << params.sigmas_for_pose_between_factor_when_zero_velocity.transpose() << "\n"
               << "sigmas_for_imu_bias_between_factor = " << params.sigmas_for_imu_bias_between_factor.transpose()
               << "\n"
               << "sigmas_for_prior_pose = " << params.sigmas_for_prior_pose.transpose() << "\n"
               << "sigmas_for_prior_velocity = " << params.sigmas_for_prior_velocity.transpose() << "\n"
               << "sigmas_for_prior_imu_bias = " << params.sigmas_for_prior_imu_bias.transpose() << "\n"
               << "sigmas_for_prior_rpy = " << params.sigmas_for_prior_rpy.transpose() << "\n"
               << "enable_compute_covariance = " << params.enable_compute_covariance << "\n "
               << "failure detector parameters = " << params.failure_detector_params << "\n"
               << "min_num_for_valid_high_precision = " << params.min_num_for_valid_high_precision << "\n"
               << "min_num_for_valid_low_precision = " << params.min_num_for_valid_low_precision << "\n"
               << "angle_trust_region_near_pi = " << params.angle_trust_region_near_pi << "\n"
               << "yaw_angle_change_ratio = " << params.yaw_angle_change_ratio << "\n"
               << "enable_yaw_constraint = " << params.enable_yaw_constraint << "\n"
               << std::endl;
            return os;
        }

        /**
         * @brief load parameters from yaml
         *
         * @param node
         * @return Parameters
         */
        static Parameters LoadFromYaml(yaml::Node const& node);

        /**
         * @brief generate example
         *
         * @return Parameters
         */
        static Parameters GenerateExample();

    private:
        /**
         * @brief
         *
         * @param node
         * @param params
         */
        static void LoadFactorSigmas(yaml::Node const& node, Parameters& params);
    };

    /**
     * @brief define factor measurements
     *
     */
    struct RawMeasurements
    {
        std::vector<StampedPim>                  multi_pim;           ///< imu factor
        std::vector<StampedCvm>                  multi_cvm;           ///< velocity constraints
        std::vector<StampedAdvancedNavstateType> multi_fusion_state;  ///< prior rpy factor
        StampedAdvancedNavstateType              state;               ///< navstate at left boundary
        bool_t                                   needs_prior_factor     = false;
        bool_t                                   add_extra_prior_factor = false;

        /**
         * @brief check if the measurements are valid
         *
         * @return bool_t
         */
        bool_t IsValid() const
        {
            // size check
            bool_t const size_flag =
                (multi_pim.size() == multi_cvm.size()) && (multi_pim.size() == multi_fusion_state.size());
            if (!size_flag)
            {
                return false;
            }

            // prior factor check
            if (!needs_prior_factor && multi_pim.empty())
            {
                return false;
            }

            // other factor check
            if (!multi_pim.empty())
            {
                // start timestamp check
                bool_t time_flag = (multi_pim.front().GetTimestamp() == multi_cvm.front().GetTimestamp()) &&
                                   (multi_cvm.front().GetTimestamp() == multi_fusion_state.front().GetTimestamp());

                // end timestamp check
                time_flag &= (multi_pim.back().GetTimestamp() == multi_cvm.back().GetTimestamp()) &&
                             (multi_cvm.back().GetTimestamp() == multi_fusion_state.back().GetTimestamp());

                if (!time_flag)
                {
                    return false;
                }
            }

            return true;
        }
    };

    /**
     * @brief conditions for judging whether fix yaw
     *
     */
    struct FixYawCondition
    {
        uint8_t count_for_high_precision;  ///< high precision number of the navstate
        uint8_t count_for_low_precision;   ///< low precision number of the navstate

        FixYawCondition(uint8_t _count_for_high_precision = 0, uint8_t _count_for_low_precision = 0)
          : count_for_high_precision(_count_for_high_precision), count_for_low_precision(_count_for_low_precision)
        {
        }
    };

    /**
     * @brief Construct a new Dr Estimator object
     *
     * @param parameters dr estimator parameters
     * @param mmf measurements manager
     * @param vvc vehicle velocity corrector
     */
    DrEstimator(Parameters const& parameters, MeasurementsManagerFusionPtr mmf, VehicleVelocityCorrectorConstPtr vvc);

    /**
     * @brief Destroy the Dr Estimator object
     *
     */
    virtual ~DrEstimator();

    /**
     * @brief get parameters
     *
     * @return parameters
     */
    Parameters const& GetParameters() const
    {
        return parameters_;
    }

    /**
     * @brief stop dr thread
     */
    virtual void Stop() override;

    /**
     * @brief reset system (non-FP)
     *
     */
    void Reset();

    /**
     * @brief set error code callback
     *
     * @param[in] handler the pointer of callback function
     */
    void SetErrorCodeCallback(ErrorCodeCallback const& handler);

protected:
    /**
     * @brief initialize dr state (non-FP)
     */
    void initializeState();

    /**
     * @brief core algorithm happens here (non-FP)
     *
     */
    virtual void run() override;

    /**
     * @brief check if switch to integration mode (non-FP)
     *
     * @return bool_t
     */
    bool_t switchToIntegrator();

    /**
     * @brief check if system has initialized
     *
     * @return bool_t
     */
    bool_t isInitialized() const;

    /**
     * @brief process data with factor graph (non-FP)
     *
     * @return bool_t
     */
    bool_t process();

    /**
     * @brief initialize
     *
     * @param fusion_state fusion state
     * @param state dr state
     * @return bool_t
     */
    bool_t initialize(StampedAdvancedNavstateType const& fusion_state, StampedAdvancedNavstateType* state);

    /**
     * @brief construct initial state
     * @param fusion_state fusion state
     * @param state dr state
     */
    void constructInitialState(StampedAdvancedNavstateType const& fusion_state,
                               StampedAdvancedNavstateType*       state) const;

    /**
     * @brief detect failure in dr estimator
     * @note current_index should be larger than 0u
     * @param[in] current_index current optimized index
     * @param[in] values optimized values
     * @return FailureDetector::Status
     */
    FailureDetector::Status detectFailure(uint64_t const current_index, GTValues const& values) const;

    /**
     * @brief optimize
     *
     * @param fusion_state fusion state
     * @param state dr state
     * @param needs_prior_factor if needs prior factor
     * @return bool_t
     */
    bool_t optimize(StampedAdvancedNavstateType const& fusion_state, StampedAdvancedNavstateType* state,
                    bool_t const needs_prior_factor = false);

    /**
     * @brief construct raw measurements
     *
     * @param left_state state at left boundary
     * @param right_state state at right boundary
     * @param needs_prior_factor if needs prior factor
     * @return holo::OptionalT<RawMeasurements>
     */
    holo::OptionalT<RawMeasurements> constructRawMeasurements(StampedAdvancedNavstateType const& left_state,
                                                              StampedAdvancedNavstateType const& right_state,
                                                              bool_t const needs_prior_factor) const;

    /**
     * @brief Create a Prior R P Y Factor Measurement object
     * @details 1. count_for_high_precision is used to record high precision number of the navstate,if this value is
     *          larger than min_num_for_valid_high_precision, the navstate is on valid high precision.
     *          count_for_low_precision is similar.
     *          2. Only when the precision is valid high,the yaw constrain will be added.
     *          3. When the fusion yaw is near pi, which is judged by angle_trust_region_near_pi, the
     *          yaw constrain will not be added. Because the rpy is decomposed through atan2, which is easy to jump to
     * -pi when the value is near pi.
     * @param[in] left_dr_stamped_advanced_navstate left dr stamped advanced navstate
     * @param[in] right_fusion_stamped_advanced_navstate right fusion stamped advanced navstate
     * @param[in] fix_yaw_condition fix yaw condition
     * @return StampedT<GraphBuilder::PriorRPYFactorMeasurement>
     */
    StampedT<GraphBuilder::PriorRPYFactorMeasurement>
    createPriorRPYFactorMeasurement(StampedAdvancedNavstate const& left_dr_stamped_advanced_navstate,
                                    StampedAdvancedNavstate const& right_fusion_stamped_advanced_navstate,
                                    FixYawCondition&               fix_yaw_condition) const;

    /**
     * @brief construct graph builder measurements
     *
     * @param rm raw measurements
     * @return Measurements
     */
    GraphBuilder::Measurements constructGraphBuilderMeasurements(RawMeasurements const& rm,
                                                                 FixYawCondition&       fix_yaw_condition) const;

    /**
     * @brief check zero velocity condition and add zero velocity factor
     *
     * @param[in] delta_translation the translation between two adjacent pose
     * @param[in] velocity velocity at {timestamp}
     * @param[in] timestamp timestamp of current pose
     * @param[in] parameters parameters used to construct factor measurements
     * @param[in][out] graph_builder_measurements graph builder measurements which wil be changed
     */
    void constructZeroVelocityMeasurement(Scalar const delta_translation, Scalar const velocity,
                                          Timestamp const& timestamp, Parameters const& parameters,
                                          GraphBuilder::Measurements& graph_builder_measurements) const;

    /**
     * @brief add prior factor measurements
     *
     * @param[in] gt_navstate prior navstate measurement
     * @param[in] gt_bias prior imu bias measurement
     * @param[in] timestamp timestamp of the prior state
     * @param[in] measurements graph builder measurements with prior facotr measurements
     */
    void constructPriorFactorMeasurements(GTNavState const& gt_navstate, GTConstantBias const& gt_bias,
                                          Timestamp const& timestamp, GraphBuilder::Measurements& measurements) const;

    /**
     * @brief construct state from values
     *
     * @param timestamp dr state timestamp
     * @param index dr state index
     * @param values optimized values from gtsam
     * @param state constructed dr state
     */
    void constructState(Timestamp const& timestamp, uint64_t const index, GTValues const& values,
                        StampedAdvancedNavstateType* state) const;

    /**
     * @brief construct state covariance
     *
     * @param smoother smoother
     * @param index index
     * @param values optimized values
     * @param state constructed dr state
     */
    void constructStateCovariance(GTIncrementalFixedLagSmoother const& smoother, uint64_t const index,
                                  GTValues const& values, StampedAdvancedNavstateType* state) const;

    /**
     * @brief Get the Dr Estimator Source object
     *
     * @return AdvancedNavstateType::Source
     */
    AdvancedNavstateType::Source getSource() const
    {
        return static_cast<AdvancedNavstateType::Source>(static_cast<uint32_t>(AdvancedNavstateType::Source::IMU) |
                                                         static_cast<uint32_t>(AdvancedNavstateType::Source::WHEEL));
    }

    /**
     * @brief output error code
     *
     * @param[in] error_code error code which should be published
     * @param[in] is_error_code_exist whether this error code occurs
     */
    void outputErrorCode(ErrorCode const error_code, bool_t const is_error_code_exist) const;

    Parameters const              parameters_;        ///< parameters
    MeasurementsManagerFusionPtr  mmf_;               ///< measurements manager
    GraphBuilder                  graph_builder_;     ///< graph builder
    GTIncrementalFixedLagSmoother smoother_;          ///< smoother
    StampedAdvancedNavstateType   state_;             ///< latest dr state
    std::shared_ptr<DrIntegrator> integrator_;        ///< dr integrator
    std::shared_ptr<std::thread>  estimator_thread_;  ///< estimation thread
    uint16_t counter_to_add_prior_factor_;   ///< when the counter is larger than a threshold prior factor will be added
    FailureDetector   failure_detector_;     ///< failure detector
    ErrorCodeCallback error_code_callback_;  ///< error code callback used to output error code
    FixYawCondition   fix_yaw_condition_;    ///< conditions to judge whether fix yaw
};

/**
 * @brief using gtsam key
 *
 */
using symbol_shorthand::B;
using symbol_shorthand::V;
using symbol_shorthand::X;

/**
 * @}
 *
 */

}  // namespace tightly_coupled_fusion

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_DR_ESTIMATOR_H_
