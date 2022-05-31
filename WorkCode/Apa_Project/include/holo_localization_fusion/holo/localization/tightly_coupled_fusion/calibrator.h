/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file calibrator.h
 * @brief This header file defines the class to do relative calibration in the fusion.
 * @author Lei Gehang(leigehang@holomatic.com)
 * @date Jul, 22, 2021
 */
#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_CALIBRATOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_CALIBRATOR_H_

#include <thread>

#include <holo/localization/common/localization_base.h>
#include <holo/localization/tightly_coupled_fusion/imu_stationary_calibrator.h>
#include <holo/localization/tightly_coupled_fusion/measurements_manager_fusion.h>
#include <holo/localization/tightly_coupled_fusion/vehicle_velocity_calibrator.h>

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
 * @brief The class is defined to run some kinds of the calibrations, such vehicle velocity calibrator and so on.
 *
 */
class Calibrator : public LocalizationBase
{
public:
    /**
     * @brief Handy typedefinitions
     */
    using Base = LocalizationBase;
    using Ptr  = std::shared_ptr<Calibrator>;
    using VehicleVelocityCorrectionCoefficientsCallback =
        std::function<void(VehicleVelocityCorrectionCoefficients const&)>;
    using MeasurementsManagerFusionPtr = MeasurementsManagerFusion::Ptr;
    using StampedImuStationaryResult   = ImuStationaryCalibrator::StampedImuStationaryResult;

    /**
     * @brief Define the parameters of this class.
     *
     */
    struct Parameters
    {
        Scalar                                frequency;  ///< Frequency to run the the core thread function[Unit: Hz]
        VehicleVelocityCalibrator::Parameters vehicle_velocity_calibrator_params;  ///< parameters of vehicle velocity
                                                                                   ///< calibrator
        bool_t enable_vehicle_velocity_calibrator;  ///< whether enable vehicle velocity calibrator

        /// Whether enable imu stationary calibrator.
        bool_t enable_imu_stationary_calibrator;

        /// Parameters used to construct ImuStationaryCalibrator obejct.
        ImuStationaryCalibrator::Parameters imu_stationary_calibrator_params;

        /// Whether enable lateral velocity correction.
        bool_t enable_lateral_velocity_correction;

        /// The max gyro standard deviation when we use the mean angular velocity as the gyro bias.
        Scalar max_gyro_std_for_bias_estimation;  ///< Unit: radian/s

        /**
         * @brief Construct a new Parameters
         *
         * @param[in] _frequency The running frequency of the calibration.
         * @param[in] _vehicle_velocity_calibrator_params The parameters of VehicleVelocityCalibrator.
         * @param[in] _enable_vehicle_velocity_calibrator Whether enable vehicle velocity calibrator
         * @param[in] _enable_imu_stationary_calibrator Whether enable imu stationary calibrator.
         * @param[in] _imu_stationary_calibrator_params The parameters of ImuStationaryCalibrator.
         * @param[in] _enable_lateral_velocity_correction whether enable lateral velocity correction.
         * @param[in] _max_gyro_std_for_bias_estimation The max gyro standard deviation.
         */
        Parameters(Scalar const                                 _frequency = Scalar(1.0),
                   VehicleVelocityCalibrator::Parameters const& _vehicle_velocity_calibrator_params =
                       VehicleVelocityCalibrator::Parameters::GenerateExample(),
                   bool_t const                               _enable_vehicle_velocity_calibrator = false,
                   bool_t const                               _enable_imu_stationary_calibrator   = true,
                   ImuStationaryCalibrator::Parameters const& _imu_stationary_calibrator_params =
                       ImuStationaryCalibrator::Parameters::GenerateExample(),
                   bool_t const _enable_lateral_velocity_correction = false,
                   Scalar const _max_gyro_std_for_bias_estimation   = Scalar(0.0015))
          : frequency(_frequency)
          , vehicle_velocity_calibrator_params(_vehicle_velocity_calibrator_params)
          , enable_vehicle_velocity_calibrator(_enable_vehicle_velocity_calibrator)
          , enable_imu_stationary_calibrator(_enable_imu_stationary_calibrator)
          , imu_stationary_calibrator_params(_imu_stationary_calibrator_params)
          , enable_lateral_velocity_correction(_enable_lateral_velocity_correction)
          , max_gyro_std_for_bias_estimation(_max_gyro_std_for_bias_estimation)
        {
        }

        /**
         * @brief Static method to generate example parameters for unit test.
         *
         * @return Parameters
         */
        static Parameters GenerateExample()
        {
            return Parameters();
        }

        /**
         * @brief Static method to load parameters from yaml.
         *
         * @param[in] node The yaml file node.
         * @return The loaded Parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief Operator overloading for "<<" to output the parameters to stream.
         *
         * @param[in] os std::ostream&
         * @param[in] parameters The Parameters to be outputed.
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters);
    };

    /**
     * @brief State of this calibrator to control operation process.
     *
     */
    struct CalibratorState
    {
        bool_t    is_vehicle_velocity_calibration_completed;  ///< Flag for whether the velocity calibration completed
        Timestamp last_gnss_pvt_timestamp_for_vehicle_velocity_calibration;  ///< The timestamp of the last gnss pvt
                                                                             ///< used for vehicle velocity calibration

        /**
         * @brief Construct a new Calibrator State object
         *
         * @param[in] _is_vehicle_velocity_calibration_completed ///< Flag for whether the velocity calibration
         * completed
         * @param[in] _last_gnss_pvt_timestamp_for_vehicle_velocity_calibration ///< The timestamp of the last gnss pvt
         * used for vehicle velocity calibration
         */
        CalibratorState(bool_t const     _is_vehicle_velocity_calibration_completed                = false,
                        Timestamp const& _last_gnss_pvt_timestamp_for_vehicle_velocity_calibration = Timestamp())
          : is_vehicle_velocity_calibration_completed(_is_vehicle_velocity_calibration_completed)
          , last_gnss_pvt_timestamp_for_vehicle_velocity_calibration(
                _last_gnss_pvt_timestamp_for_vehicle_velocity_calibration)
        {
        }
    };

    /**
     * @brief Construct a new Calibrator object
     *
     * @param[in] parameters The parameters
     * @param[in] measurement_manager_fusion_ptr The pointer of Measurement manager fusion.
     */
    Calibrator(Parameters const& parameters, MeasurementsManagerFusionPtr& measurement_manager_fusion_ptr);

    /**
     * @brief Destroy the Calibrator object
     *
     */
    virtual ~Calibrator();

    /**
     * @brief Overide the Stop function of base class to this calibration process.
     *
     */
    virtual void Stop() override;

    /**
     * @brief Set the vehicle velocity correction coefficients callback object
     *
     * @param[in] handler The velocity correction coefficients callback handler.
     */
    void SetVehicleVelocityCorrectionCoefficientsCallback(VehicleVelocityCorrectionCoefficientsCallback const& handler)
    {
        vehicle_velocity_correction_coefficients_callback_ = handler;
    }

protected:
    /**
     * @brief Override the run function of the base class.
     *
     */
    virtual void run() override;

    /**
     * @brief Get the Raw Measurement of Vehicle Velocity Calibration from Measurements manager
     *
     * @param[in] measurement_manager_fusion_ptr The pointer of the measurement manager
     * @param[in, out] old_gnss_pvt_timestamp Timestamp of the old gnss pvt used for calibration. It will be updated
     * after getting the new GnssPvt measurement.
     * @param[out] raw_velocity The raw velocity value to be calibrated.
     * @param[out] ground_truth The ground truth for reference.
     * @return It returns true if we can get the raw measurement successfully. Otherwise, it returns false.
     */
    bool_t getVehicleVelocityCalibrationRawMeasurement(MeasurementsManagerFusionPtr& measurement_manager_fusion_ptr,
                                                       Timestamp& old_gnss_pvt_timestamp, Scalar& raw_velocity,
                                                       Scalar& ground_truth) const;

    /**
     * @brief Run the vehicle velocity calibration process.
     *
     * @param[in] raw_velocity The raw velocity value to be calibrated.
     * @param[in] ground_truth The ground truth for reference.
     * @return It returns true if the vehicle velocity calibration is successful. Otherwise, it returns false.
     */
    bool_t runVehicleVelocityCalibration(Scalar const raw_velocity, Scalar const ground_truth);

    /**
     * @brief Get the vehicle velocity and imu data between last time and current .
     *
     * @param[out] corrected_vehicle_velocity_measurements The raw vehicle velocity data.
     * @param[out] imu_measurements The raw imu data.
     * @return It returns true if both vehicle velocity and imu data were gotten successfully. Otherwise, it returns
     * false.
     */
    bool_t
    getVelocityAndImuMeasurements(std::vector<StampedCorrectedVehicleVelocity>& corrected_vehicle_velocity_measurements,
                                  std::vector<ImuType>&                         imu_measurements);

    Parameters const             parameters_;                      ///< The parameters of this class.
    std::shared_ptr<std::thread> calibration_thread_ptr_;          ///< The main thread to run the calibration.
    MeasurementsManagerFusionPtr measurement_manager_fusion_ptr_;  /// Used to get the sensors data and fusion navstate.
    CalibratorState              calibrator_state_;  ///< The state to record calibration process variables.

    /**
     * @brief Variables relative to vehicle velocity calibrator.
     */
    VehicleVelocityCalibrator::Ptr vehicle_velocity_calibrator_ptr_;

    /// Output the calibrated correction coefficients
    VehicleVelocityCorrectionCoefficientsCallback vehicle_velocity_correction_coefficients_callback_;

    /// Used to accumulate and get imu stationary results.
    ImuStationaryCalibrator::Ptr imu_stationary_calibrator_ptr_;

    /// Last timestamp running calibrator thread, used to get imu and chassis data between last time and current.
    Timestamp last_calibrator_running_timestamp_;
};

/**
 * @}
 *
 */

}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  /// HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_CALIBRATOR_H_
