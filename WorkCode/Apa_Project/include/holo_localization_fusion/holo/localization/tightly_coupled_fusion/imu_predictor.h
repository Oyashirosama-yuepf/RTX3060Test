/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu_predictor.h
 * @brief This header file defines the class to do imu prediction.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2021-02-19"
 */
#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_IMU_PREDICTOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_IMU_PREDICTOR_H_

#include <thread>

#include <holo/localization/common/localization_base.h>
#include <holo/localization/tightly_coupled_fusion/common_types.h>
#include <holo/localization/tightly_coupled_fusion/corrected_imu_filter.h>
#include <holo/localization/tightly_coupled_fusion/measurements_manager_fusion.h>
#include <holo/localization/tightly_coupled_fusion/utils/common_functions.h>

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
class ImuPredictor : public LocalizationBase
{
public:
    /**
     * @brief handy typedefs
     */
    using Base                   = LocalizationBase;
    using Ptr                    = std::shared_ptr<ImuPredictor>;
    using OdometryCallback       = std::function<int32_t(const OdometryType&)>;
    using ImuBiasCallback        = std::function<int32_t(const ImuBiasType&)>;
    using MeasurementsManagerPtr = holo::localization::tightly_coupled_fusion::MeasurementsManagerFusion::Ptr;
    /**
     * @brief Define predict source
     *
     */
    enum class PredictionSource : int32_t
    {
        DR     = 0,
        FUSION = 1,
    };

    /**
     * @brief Define precision
     *
     */
    enum class Precision : uint32_t
    {
        UNKNOWN       = 0u,
        HIGH          = 1u,
        MEDIUM        = 2u,
        LOW           = 3u,
        LATERNAL_HIGH = 4u,
    };

    /**
     * @brief Define the configuration of imu prediction
     *
     */
    struct Parameters
    {
        ImuPreintegration::Parameters  imu_preint_params;              ///< imu_preint params
        Scalar                         frequency;                      ///< frequency, unit, Hz
        PredictionSource               prediction_source;              ///< predict source
        Scalar                         accumulate_distance_threshold;  ///< accumulate distance threshold, unit, m
        CorrectedImuFilter::Parameters corrected_imu_filter_params;    ///< brief corrected imu filter parameters
        bool_t enable_differential_acceleration    = true;             ///< whether enable differential acceleration
        Scalar differential_velocity_time_interval = 0.01;             ///< differential velocity time interval
        Scalar max_time_imu_not_update;                                ///< max time that imu not update, unit, s
        Scalar max_time_optimize_state_not_update;  ///< max time that optimze state not update, unit, s
        bool_t enable_extrapolation_when_imu_not_updated =
            false;  ///< # true -> do extrapolation when imu is not updated, false -> do nothing when imu is not updated
        /**
         * @brief Construct a new Parameters object
         *
         * @param[in] _imu_preint_params imu prediction parameters
         * @param[in] _predict_frequency imu prediction frequency, unit, Hz
         * @param[in] _prediction_source imu prediction source
         * @param[in] _accumulate_distance_threshold accumulate distance threshold,unit, m
         * @param[in] _corrected_imu_filter_params corrected imu filter parameters
         * @param[in] _enable_differential_acceleration flag to enable differential acceleration
         * @param[in] _differential_velocity_time_interval time interval of differential velocity ,unit,s
         * @param[in] _max_time_imu_not_update _max time imu not update, unit,s
         * @param[in] _max_time_optimize_state_not_update max time optimize state not update, unit,s
         * @param[in] _enable_extrapolation_when_imu_not_updated switch to enable imu extrapolation
         */
        Parameters(ImuPreintegration::Parameters const& _imu_preint_params, Scalar const _predict_frequency,
                   PredictionSource const& _prediction_source, Scalar const _accumulate_distance_threshold,
                   CorrectedImuFilter::Parameters const& _corrected_imu_filter_params,
                   bool_t const _enable_differential_acceleration, Scalar const _differential_velocity_time_interval,
                   Scalar _max_time_imu_not_update, Scalar _max_time_optimize_state_not_update,
                   bool_t _enable_extrapolation_when_imu_not_updated)
          : imu_preint_params(_imu_preint_params)
          , frequency(_predict_frequency)
          , prediction_source(_prediction_source)
          , accumulate_distance_threshold(_accumulate_distance_threshold)
          , corrected_imu_filter_params(_corrected_imu_filter_params)
          , enable_differential_acceleration(_enable_differential_acceleration)
          , differential_velocity_time_interval(_differential_velocity_time_interval)
          , max_time_imu_not_update(_max_time_imu_not_update)
          , max_time_optimize_state_not_update(_max_time_optimize_state_not_update)
          , enable_extrapolation_when_imu_not_updated(_enable_extrapolation_when_imu_not_updated)
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
            os << "\n imu preintegration paramters : "
               << "\n acc noise sigma = " << parameters.imu_preint_params.GetAccNoiseSigmas().Transpose()
               << "\n gyro noise sigma = " << parameters.imu_preint_params.GetGyroNoiseSigmas().Transpose()
               << "\n imu frequency = " << parameters.imu_preint_params.GetFrequency()
               << "\n extrinsic imu in body frame bTi = " << parameters.imu_preint_params.GetExtrinsicBodyImu()
               << "\n integration uncertainty = " << parameters.imu_preint_params.GetIntegrationUncertainty()
               << "\n frequency = " << parameters.frequency
               << "\n prediction source = " << int32_t(parameters.prediction_source)
               << "\n accumulate distance threshold = " << parameters.accumulate_distance_threshold
               << "\n corrected imu filter paramters = " << parameters.corrected_imu_filter_params
               << "\n enable differential acceleration = " << parameters.enable_differential_acceleration
               << "\n differential_velocity_time_interval = " << parameters.differential_velocity_time_interval
               << "\n max time imu not update = " << parameters.max_time_imu_not_update
               << "\n max time optimize state not update = " << parameters.max_time_optimize_state_not_update
               << "\n enable_extrapolation_when_imu_not_updated = "
               << parameters.enable_extrapolation_when_imu_not_updated << std::endl;
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
    };

    /**
     * @brief Construct a new Imu Predictor object
     *
     * @param[in] params parameters needed in prediction
     * @param[in] measurements_manager_ptr measurements manager pointer
     */
    ImuPredictor(Parameters const& params, MeasurementsManagerPtr& measurements_manager_ptr);

    /**
     * @brief Destroy the Imu Predictor object
     *
     */
    virtual ~ImuPredictor();

    /**
     * @brief Stop imu prediction
     *
     */
    virtual void Stop() override;

    /**
     * @brief Set the odometry callback
     *
     * @param handler odometry callback handler
     */
    void SetOdometryCallback(OdometryCallback const& handler) noexcept
    {
        odometry_callback_ = handler;
    }

    /**
     * @brief Set the imu bias callback
     *
     * @param handler imu bias callback handler
     */
    void SetImuBiasCallback(ImuBiasCallback const& handler) noexcept
    {
        imu_bias_callback_ = handler;
    }

protected:
    /**
     * @brief accumulate distance from last navstate with high precision to latest input navstate
     *
     * @param[in] stamped_advanced_navstates_from_last_input_navstate stamped advanced navstates vector from last input
     * @param[in] last_input_stamped_advanced_navstate last input stamped advanced navstate
     * @param[in] has_high_precision_navstate flag used to judge whether has high precision navstate
     * @param[in] accumulated_distance_from_last_high_precision_navstate distance to last high precision navstate
     */
    void accumulateDistance(
        std::vector<StampedAdvancedNavstate> const& stamped_advanced_navstates_from_last_input_navstate,
        StampedAdvancedNavstate const& last_input_stamped_advanced_navstate, bool_t& has_high_precision_navstate,
        Scalar& accumulated_distance_from_last_high_precision_navstate) const;

    /**
     * @brief calculate longitudinal acceleration using two adjacent velocities
     *
     * @param[in] corrected_vehicle_velocities corrected vehicle velocities between last newest velocity and newest
     * @return Scalar returns longitudinal acceleration
     */
    Scalar calculateLongitudinalAcceleration(
        std::vector<StampedT<CorrectedVehicleVelocity>> const& corrected_vehicle_velocities);

    /**
     * @brief publish the stamped advanced navstate
     *
     * @param[in] stamped_advanced_navstate the predicted stamped advanced navstate
     * @param[in] source publish source of the predicted stamped advanced navstate
     * @param[in] precision publish precision of the predicted stamped advanced navstate
     */
    void publishPredictionResult(StampedAdvancedNavstate const& stamped_advanced_navstate,
                                 OdometryType::Source const& source, Precision const& precision);

    /**
     * @brief generate precision map
     *
     * @return std::map<Precision, uint32_t> generated precision map
     */
    std::map<Precision, uint32_t> generatePrecisionMap() const;

    /**
     * @brief generate odometry with given precision
     *
     * @param[in] precision given precision
     * @return OdometryType generated odometry
     */
    OdometryType generateOdometryWithGivenPrecision(OdometryType::PrecisionValueType const precision) const;

    /**
     * @brief determin DR source and precision
     *
     * @param[in] latest_input_stamped_advanced_navstate latest input stamped advanced navstate
     * @param[in] is_not_update_time_over_max flag to judge if the time imu/input optimized state have not updated over
     * max time threshold
     */
    void determineDRSourceAndPrecision(StampedAdvancedNavstate const& latest_input_stamped_advanced_navstate,
                                       bool_t const                   is_not_update_time_over_max);

    /**
     * @brief determin FUSION source and precision
     *
     * @param[in] last_input_stamped_advanced_navstate last input stamped advanced navstate
     * @param[in] stamped_advanced_navstates_from_last_input_navstate stamped advanced navstates vector from last input
     * @param[in] has_high_precision_navstate flag used to judge whether has high precision navstate
     * @param[in] accumulated_distance_from_last_high_precision_navstate distance from last high precision navstate
     * @param[in] is_not_update_time_over_max flag to judge if the time imu/input optimized state have not updated over
     */
    void determineFusionSourceAndPrecision(
        StampedAdvancedNavstate const&              last_input_stamped_advanced_navstate,
        std::vector<StampedAdvancedNavstate> const& stamped_advanced_navstates_from_last_input_navstate,
        bool_t& has_high_precision_navstate, Scalar& accumulated_distance_from_last_high_precision_navstate,
        bool_t const is_not_update_time_over_max);

    /**
     * @brief check how long have imu and input state not updated, if the time over threshold, set precision to unknown
     *
     * @param[in] newest_imu newest imu
     * @param[in] newest_input_state newest input state
     * @return bool_t return true if the time imu/input optimized state have not updated over
     * max time thredshold
     */
    bool_t processImuAndInputStateNotUpdate(ImuType const&                 newest_imu,
                                            StampedAdvancedNavstate const& newest_input_state);

    /**
     * @brief Run imu prediction
     *
     */
    virtual void run() override;

    /**
     * @brief Construct the ImuPreintegration parameters with the updated local gravity.
     *
     * @param[in] local_gravity The local gravity
     * @return ImuPreintegration::Parameters
     */
    ImuPreintegration::Parameters constructImuPreintegrationParameters(Scalar const local_gravity) const
    {
        ImuPreintegration::Parameters imu_preint_params = params_.imu_preint_params;
        imu_preint_params.SetGravity(local_gravity);
        return imu_preint_params;
    }

    std::shared_ptr<std::thread> prediction_thread_ptr_;                     ///< pointer to propagation thread
    OdometryCallback             odometry_callback_;                         ///< output odometry callback
    ImuBiasCallback              imu_bias_callback_;                         ///< output imu bias callback
    StampedAdvancedNavstate      last_input_stamped_advanced_navstate_;      ///< the last navstate from DR/FUSION
    StampedAdvancedNavstate      stamped_advanced_navstate_base_;            ///< navstate base of imu prediction
    StampedAdvancedNavstate      last_predicted_stamped_advanced_navstate_;  ///< the last navstate from imu propagate
    const Parameters             params_;                                    ///< parameters of imu prediction
    MeasurementsManagerPtr       measurements_manager_ptr_;                  ///< measurements manager pointer
    Scalar                       accumulated_distance_from_last_high_precision_navstate_ =
        DBL_MAX;                                          ///< distance between last navstate with
                                                          ///< high precision and current navstate (unit, m)
    bool_t has_high_precision_navstate_ = false;          ///< flag used to judge whether has high precision navstate
    OdometryType::Source          source_;                ///< publish source of predicted navstate
    Precision                     precision_;             ///< publish precision of predicted navstate
    std::map<Precision, uint32_t> precision_map_;         ///< precision enum to odometry precision flags
    AdvancedNavstateType::Source  navstate_source_;       ///< source of predicted navstate
    CorrectedImuFilter            corrected_imu_filter_;  ///< corrected imu filter
    uint64_t                      imu_not_update_count_;  ///< flag to record the number imu not updated
    uint64_t optimize_state_not_update_count_;            ///< flag to record the number optimize state not updated
};

/**
 * @}
 *
 */

}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo
#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_IMU_PREDICTOR_H_
