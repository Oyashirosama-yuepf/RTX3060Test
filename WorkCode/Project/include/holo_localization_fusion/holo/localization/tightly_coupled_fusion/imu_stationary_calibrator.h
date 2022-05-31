/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu_stationary_calibrator.h
 * @brief This header file is used to define the imu stationary calibrator class.
 * @author Gan di (gandi@holomatic.com)
 * @date Apr. 8, 2022
 */
#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_IMU_STATIONARY_CALIBRATOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_IMU_STATIONARY_CALIBRATOR_H_

#include <holo/localization/tightly_coupled_fusion/common_types.h>
#include <holo/localization/tightly_coupled_fusion/utils/imu_accumulator.h>
#include <holo/localization/tightly_coupled_fusion/utils/vehicle_motion_state_detector.h>

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
 * @brief This class is used to get IMU measurements when vehicle is  stationary or uniform linear motion.
 *
 */
class ImuStationaryCalibrator
{
public:
    /// The fixed size for the Imu accumualor. The 200 is hard code. And It can be adjusted.
    static uint16_t constexpr kFixedImuAccumulatorBufferSize = 200u;

    /**
     * @brief Define common type
     *
     */
    using ImuAccumulatorType = ImuAccumulator<kFixedImuAccumulatorBufferSize>;
    using Ptr                = std::shared_ptr<ImuStationaryCalibrator>;
    using ConstPtr           = std::shared_ptr<const ImuStationaryCalibrator>;
    using StampedVector6Type = StampedT<Vector6Type>;

    /**
     * @brief The relative data type of this class.
     *
     */
    struct ImuStationaryResult
    {
        /// Acceleration mean of imu stationary measurements.
        Vector3Type acceleration_mean;
        /// Acceleration standard deviation of imu stationary measurements.
        Vector3Type acceleration_std;
        /// Angular velocity mean of imu stationary measurements.
        Vector3Type angular_velocity_mean;
        /// Angular velocity mean  standard deviation of imu stationary measurements.
        Vector3Type angular_velocity_std;
    };
    using StampedImuStationaryResult = StampedT<ImuStationaryResult>;

    /**
     * @brief The relative parameters of this class.
     *
     */
    struct Parameters
    {
        VehicleMotionStateDetector::Parameters vehicle_motion_state_detector_params;
        ImuAccumulatorParameters               imu_accumulator_params;

        /**
         * @brief The operator overloading for <<.
         *
         * @param[in] os The std ostream.
         * @param[in] params The parameters object.
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters)
        {
            os << "ImuStationaryCalibratorParameters: \n"
               << parameters.vehicle_motion_state_detector_params << parameters.imu_accumulator_params << std::endl;
            return os;
        }

        /**
         * @brief Construct a new Parameters struct
         *
         * @param[in] _vehicle_motion_state_detector_params Parameters for detecting vehicle motion state.
         * @param[in] _imu_accumulator_params Parameters for judging whether imu measurements are normal.
         */
        Parameters(VehicleMotionStateDetector::Parameters _vehicle_motion_state_detector_params =
                       VehicleMotionStateDetector::Parameters(),
                   ImuAccumulatorParameters _imu_accumulator_params = ImuAccumulatorParameters())
          : vehicle_motion_state_detector_params(_vehicle_motion_state_detector_params)
          , imu_accumulator_params(_imu_accumulator_params)
        {
        }

        /**
         * @brief Static method to load parameters from yaml node.
         *
         * @param[in] node The yaml node.
         * @return The loaded parameters.
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief static method to generate example parameters for unit test
         *
         * @return The generated parameters for unit test
         */
        static Parameters GenerateExample()
        {
            return Parameters();
        }
    };

    /**
     * @brief Construct a new Imu Stationary Calibrator object
     *
     * @param[in] parameters The initial parameters.
     */
    explicit ImuStationaryCalibrator(Parameters const& parameters);

    /**
     * @brief Run the imu stationary  calibrator. Imu values will be added to accumulator buffer, if vehicle is
     * stationary.
     *
     * @param[in] corrected_vehicle_velocity_measurements The aligned and corrected vehicle velocity, which are used to
     * judge the motion state of the vehicle.
     * @param[in] imu_measurements The aligned imu values.
     * @param[out] vehicle_motion_state The move station of vehicle.
     * @param[out] imu_stationary_result The calculated mean of imu stationary measurements.
     * @return It returns true we can get the imu stationary measurements.(The buffer size of ImuAccumulator is enough).
     * Otherwise, it returns false.
     */
    bool_t Run(std::vector<StampedCorrectedVehicleVelocity> const& corrected_vehicle_velocity_measurements,
               std::vector<ImuType> const& imu_measurements, VehicleMotionState& vehicle_motion_state,
               StampedImuStationaryResult& imu_stationary_result);

    /**
     * @brief Reset the vehicle velocity and imu accumulator.
     *
     */
    void Reset()
    {
        vehicle_motion_state_detector_.Reset();
        imu_accumulator_.Reset();
    }

    /**
     * @brief Get the valid Imu mean and standard deviation.
     *
     * @param[out] m The acceleration mean,  acceleration standard deviation, angular velocity mean and angular velocity
     * standard deviation.
     * @return It returns true we can get the data.(The buffer size of ImuAccumulator is enough). Otherwise, it
     * returns false.
     */
    bool_t GetImuStationaryResult(StampedImuStationaryResult& m) const;

private:
    Parameters const parameters_;

    /// To judge the motion state of the vehicle
    VehicleMotionStateDetector vehicle_motion_state_detector_;

    /// To accumulate the Imu values in stationary or uniform linear motion
    ImuAccumulatorType imu_accumulator_;
};

}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif
