/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fusion_initializer.h
 * @brief This file is used to define the FusionInitializer class which is to run the initialization of the localization
 * fusion.
 * @author Lei Gehang(leigehang@holomatic.com)
 * @date Feb 19, 2021
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_FUSION_INITIALIZER_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_FUSION_INITIALIZER_H_

#include <holo/localization/tightly_coupled_fusion/common_types.h>
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

/**
 * @brief This class is used to realize the initialization of the localization fusion. It will provide the prior pose,
 * the prior velocity and the prior IMU bias for the initialization process.
 *
 */
class FusionInitializer
{
public:
    /// The fixed size for the Imu accumualor. The 100 is hard code. And It can be adjusted.
    static uint16_t constexpr kFixedSizeOfImuAccumulator = 100u;

    /// The handy types definition
    using OptionalStampedGTNavStateAndImuBias = holo::OptionalT<StampedGTNavStateAndImuBias>;
    using FixedSizeImuAccumulator             = ImuAccumulator<kFixedSizeOfImuAccumulator>;
    using OptionalTimestamp                   = holo::OptionalT<holo::common::Timestamp>;
    using OptionalScalar                      = holo::OptionalT<Scalar>;
    using OptionalStampedVector3Type          = holo::OptionalT<StampedT<Vector3Type>>;
    using StampedVector3Type                  = StampedT<Vector3Type>;
    using StampedVector6Type                  = StampedT<Vector6Type>;
    using StampedImuStationaryResult          = ImuStationaryCalibrator::StampedImuStationaryResult;

protected:
    /**
     * @brief This class is used to output a accumulated odometry based on the vehicle speed.
     * @details It is used to roughly accumulate the distance traveled by the vehicle. Users who call it should not
     * require it for high precision.
     *
     */
    class VehicleSpeedOdometry
    {
    public:
        /**
         * @brief The parameters of the VehicleSpeedOdometry class
         *
         */
        struct Parameters
        {
            /// To judge the delay or loss of the input measurements. Unit: s.
            Scalar max_delay_time_for_input = Scalar(0.1);
        };

        /**
         * @brief Construct a new Vehicle Speed Odometry object
         *
         * @param[in] max_delay_time_for_input The acceptable max delay time for the input. If the time between current
         * input and last input is over the threshold. We will reset this class.
         */
        VehicleSpeedOdometry(Parameters const& parameters)
          : parameters_(parameters)
          , last_vehicle_velocity_timestamp_(optional::none)
          , last_wheel_speed_(optional::none)
          , accumulated_distance_(optional::none)
          , enable_flag_(false)
        {
        }

        /**
         * @brief To accumulate the vehicle speed to get the accumulated distance traveled by the vehicle.
         *
         * @param[in] vehicle_velocity_measurements The stamped vehicle velocity measurements.
         * @return  (1) OptionalT<Distance>. If the input measurements are not delayed or lost. It can return the rough
         * accumulated distance. (Unit: meter)
         * (2) optional::none. If there is delay or loss of the input measurements occurred, and the delay time is over
         * the threshold, it will return the optional::none.
         */
        OptionalScalar Run(std::vector<StampedCorrectedVehicleVelocity> const& vehicle_velocity_measurements);

        /**
         * @brief Reset the vehicle velocity odoemtry class.
         *
         */
        void Reset()
        {
            last_vehicle_velocity_timestamp_ = optional::none;
            last_wheel_speed_                = optional::none;
            accumulated_distance_            = optional::none;
            enable_flag_                     = false;
        }

        /**
         * @brief Get the enabled flag.
         *
         * @return The enable flag.
         */
        bool_t IsEnabled()
        {
            return enable_flag_;
        }

        /**
         * @brief Enable the velocity speed odoemtry.
         *
         */
        void Enable()
        {
            enable_flag_ = true;
        }

        /**
         * @brief Disable the velocity speed odoemtry.
         *
         */
        void Disable()
        {
            enable_flag_ = false;
        }

    private:
        /**
         * @brief To detect whether the vehicle velocity is lost or delayed.
         *
         * @param[in] vehicle_velocity The vehicle velocity
         * @return It returns false if the vehicle velocity is lost. Otherwise, it returns true.
         */
        bool_t isMeasurementLost(StampedCorrectedVehicleVelocity const& vehicle_velocity) const;

        /**
         * @brief To accumulate the distance traveled by the vehicle.
         *
         */
        void accumulateDistance(StampedCorrectedVehicleVelocity const& vehicle_velocity);

        Parameters const parameters_;  ///< The vehicle speed odoemtry parameters

        OptionalTimestamp last_vehicle_velocity_timestamp_;  ///< To record the last input timestamp
        OptionalScalar    last_wheel_speed_;                 ///< To record the last wheel speed. Unit: m/s
        OptionalScalar    accumulated_distance_;  ///< The accumualted distance traveled by the vehicle. Unit: m.

        bool_t enable_flag_ = false;  ///< The flag to enable the distance accumulation.
    };

public:
    /**
     * @brief The parameters of the fsion initializer.
     *
     */
    struct Parameters
    {
        /// Parameters used to construct ImuStationaryCalibrator obejct.
        ImuStationaryCalibrator::Parameters imu_stationary_calibrator_params;
        VehicleSpeedOdometry::Parameters       vehicle_speed_odometry_params;
        ImuBiasType default_imu_bias;  ///< The default IMU bias will be used when can't estimate the current Bias.

        /// The max acceleration standard deviation when we use the acceleration to estimate the roll and pitch.
        Scalar max_acc_std_for_rotation_estimation = Scalar(0.01);  ///< Unit: m/s^2

        /// The max gyro standard deviation when we use the mean angular velocity as the gyro bias.
        Scalar max_gyro_std_for_bias_estimation = Scalar(0.001);  ///< Unit: radian/s

        /// The min speed when we estimater from gnss with its velocity. If the speed is lower, the yaw is not
        /// trusted.
        Scalar min_speed_for_estimating_yaw_from_gnss = Scalar(5.0);  ///< Unit: m/s.

        /**
         * The traveled distance is accumulated from the start position of the vehicle is stationary or at the
         * uniform speed linear motion.
         */
        Scalar max_traveled_distance_for_rotation_estimation = Scalar(5.0);  ///< Unit: m.

        /**
         * @brief Output stream overloading for FusionInitializer's parameter
         *
         * @param[in] os std::ostream&
         * @param[in] parameters Parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters)
        {
            os << "FusionInitializerParameters: \n"
               << parameters.imu_stationary_calibrator_params
               << "VehicleSpeedOdometry Parameter: max_delay_time_for_input = "
               << parameters.vehicle_speed_odometry_params.max_delay_time_for_input
               << "\nDefaultImuBias: \nDefault AccelerationBias = "
               << parameters.default_imu_bias.GetLinearAccelerationBias<Vector3Type>().Transpose()
               << "\nDefault AngularVelocityBias = "
               << parameters.default_imu_bias.GetAngularVelocityBias<Vector3Type>().Transpose()
               << "\nmax_acc_std_for_rotation_estimation = " << parameters.max_acc_std_for_rotation_estimation
               << "\nmax_gyro_std_for_bias_estimation = " << parameters.max_gyro_std_for_bias_estimation
               << "\nmin_speed_for_estimating_yaw_from_gnss = " << parameters.min_speed_for_estimating_yaw_from_gnss
               << "\nmax_traveled_distance_for_rotation_estimation = "
               << parameters.max_traveled_distance_for_rotation_estimation << std::endl;
            return os;
        }

        /**
         * @brief Static method to load parameters from yaml
         *
         * @param[in] node Yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);
    };

    /**
     * @brief Construct a new Fusion Initializer object
     *
     * @param[in] parameters The input parameters
     */
    FusionInitializer(Parameters const& parameters);

    /**
     * @brief Run the initializer to get the prior Advanced NavState, which includes the prior pose, prior
     * velocity, prior IMU bias.
     *
     * @param[in] raw_measurements The raw measurements of localization fusion.
     * @return Optional stamped GTNavState type and GTImuBias. If Its initialization failures, it will return
     * optional::none.
     */
    OptionalStampedGTNavStateAndImuBias Run(FusionRawMeasurements const& raw_measurements);

    /**
     * @brief Reset the fusion initializer to the default.
     *
     */
    void Reset()
    {
        imu_stationary_calibrator_.Reset();
        vehicle_speed_odometry_.Reset();
        acceleration_mean_     = optional::none;
        acceleration_std_      = optional::none;
        angular_velocity_mean_ = optional::none;
        angular_velocity_std_  = optional::none;
    }

protected:
    /**
     * @brief Estimate the roll and pitch value of the vehicle based on the acceleration.
     * @note In this method, the roll and pitch are estimated by the component of gravity on each axis of the
     * accelerometer, so it is necessary to ensure that the input acceleration is the measured value when the
     * vehicle is stationary or moving in a uniform straight line
     *
     * @param[in] acceleration_mean The 3-axis acceleration mean value. Unit: m/s^2
     * @param[in] acceleration_std The 3-axis acceleration standard deviation. Unit: m/s^2
     * @return std::pair<Roll, Pitch>. Unit: radian
     */
    std::pair<Scalar, Scalar> estimateRollPitchWithAcceleration(Vector3Type const& acceleration_mean,
                                                                Vector3Type const& acceleration_std) const;

    /**
     * @brief Estimate the yaw value of the vehicle based on the GNSS velocity.
     *
     * @param[in] gnss_pvts The GNSS measurements
     * @return The yaw value. Unit: radian. If we can't get the yaw, for example when the velocity is too slow, it
     * will return optional::none.
     */
    OptionalScalar estimateYawWithGnssVelocity(std::vector<GnssPvtType> const& gnss_pvts) const;

    /**
     * @brief Unpack the imu stationary result.
     *
     * @param[in] imu_stationary_result The imu mean and standard deviation in stationary.
     * @param[out] acceleration_mean The acceleration mean.
     * @param[out] acceleration_std The acceleration standard deviation.
     * @param[out] angular_velocity_mean The angular velocity mean.
     * @param[out] angular_velocity_std The angular velocity standard deviation.
     */
    void unpackImuStationaryResult(StampedImuStationaryResult const& imu_stationary_result,
                                   OptionalStampedVector3Type&       acceleration_mean,
                                   OptionalStampedVector3Type&       acceleration_std,
                                   OptionalStampedVector3Type&       angular_velocity_mean,
                                   OptionalStampedVector3Type&       angular_velocity_std) const;

    /**
     * @brief Create a Prior Imu Bias.
     * @details (1) Acceleration bias: The prior acceleration bias is equal to the input default bias.
     *          (2) Angular velocity bias: When the angular velocity mean is valid and its standard deviation is
     * lower than the threshold, the prior angular velocity bias is set to the angular velocity mean. Otherwise, it
     * is equal to the default bias.
     *
     * @param[in] angular_velocity_mean The optional angular velocity mean. [x,y,z]. Unit: radian/s.
     * @param[in] angular_velocity_std The optional angular velocity stdandard deviation. [x,y,z]. Unit:
     * radian/s.
     * @return The prior ImuBias
     */
    ImuBiasType createPriorImuBias(OptionalStampedVector3Type const& angular_velocity_mean,
                                   OptionalStampedVector3Type const& angular_velocity_std,
                                   ImuBiasType const&                default_imu_bias) const;

    /**
     * @brief Create a Prior Stamped GTNavStateAndImuBias.
     *
     * @param[in] roll_pitch_yaw The prior roll pitch and yaw Euler angle.
     * @param[in] vehicle_velocity_measurements The vehicle velocity measurements.
     * @param[in] gnss_pvt_measurements The gnss pvt measurements.
     * @param[in] prior_imu_bias The prior Imu Bias
     * @return The prior stamped GTNavStateAndImuBias
     */
    StampedGTNavStateAndImuBias createPriorStampedGTNavStateAndImuBias(
        Vector3Type const&                                  roll_pitch_yaw,
        std::vector<StampedCorrectedVehicleVelocity> const& vehicle_velocity_measurements,
        std::vector<GnssPvtType> const& gnss_pvt_measurements, ImuBiasType const& prior_imu_bias) const;

    /**
     * @brief Get the Nearest Measurement T from the std::vector<T>
     * @note The buffer must be in chronological order from small to large.
     *
     * @tparam T The target type
     * @param target_timestamp The target timestamp
     * @param buffer The buffer of the T object.
     * @return It returns Optional<T> if we can find the neareset measurement. Otherwise, it returns optional::none.
     */
    template <typename T>
    holo::OptionalT<T> getNearestMeasurementT(const Timestamp& target_timestamp, const std::vector<T>& buffer) const;

private:
    Parameters const parameters_;

    /// To judge motion state of the vehicle and accumulate  imu stationary measurements.
    ImuStationaryCalibrator imu_stationary_calibrator_;

    VehicleSpeedOdometry vehicle_speed_odometry_;  ///< To compute the travel distance of the vehicle with the
                                                   ///< speed.

    /// The acceleration mean. It is used for estimating roll and pitch. Unit: m/s^2.
    OptionalStampedVector3Type acceleration_mean_;

    /// The acceleration standard deviation. It is used for estimating roll and pitch. Unit: m/s^2.
    OptionalStampedVector3Type acceleration_std_;

    /// The angular velocity mean. It is used for estimating the gyroscope bias. Unit: radian/s.
    OptionalStampedVector3Type angular_velocity_mean_;

    /// The angular velocity standard deviation. It is used for estimating the gyroscope bias. Unit: radian/s.
    OptionalStampedVector3Type angular_velocity_std_;

};  // namespace tightly_coupled_fusion

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_FUSION_INITIALIZER_H_
