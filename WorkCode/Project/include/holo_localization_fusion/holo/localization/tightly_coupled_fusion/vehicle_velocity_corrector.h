/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vehicle_velocity_corrector.h
 * @brief this file defines function to correct and smooth imu data
 * @author Wenzhi Liu(liuwenzhi@holomatic.com)
 * @date  Feb 06, 2021
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_VEHICLE_VELOCITY_CORRECTOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_VEHICLE_VELOCITY_CORRECTOR_H_

#include <holo/localization/tightly_coupled_fusion/common_types.h>

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
 * @brief this class to correct wheel speed and vehicle velocity
 *
 */
class VehicleVelocityCorrector
{
public:
    /**
     * @brief Define common type
     *
     */
    using Ptr      = std::shared_ptr<VehicleVelocityCorrector>;
    using ConstPtr = std::shared_ptr<const VehicleVelocityCorrector>;

    /**
     * @brief parameters for corrector
     *
     */
    struct Parameters
    {
        // rear left wheel speed correction coefficient (a*x+b), default [a, b] = [1, 0]
        const Vector2Type rear_left_wheel_speed_correction_coeff;

        // rear right wheel speed correction coefficient (a*x+b), default [a, b] = [1, 0]
        const Vector2Type rear_right_wheel_speed_correction_coeff;

        // The mass at rear wheel is divided by the cornering stiffness of rear tire, default 0.0.
        // mr_divide_cr = (mr/Cr), mr is vehicle's mass at rear wheel, Cr is cornering stiffness of rear tire.
        const Scalar mr_divide_cr;

        /**
         * @brief constructor
         */
        Parameters(Vector2Type const& _rear_left_wheel_speed_correction_coeff  = Vector2Type(1.0, 0.0),
                   Vector2Type const& _rear_right_wheel_speed_correction_coeff = Vector2Type(1.0, 0.0),
                   Scalar const       _mr_divide_cr                            = 0.0)
          : rear_left_wheel_speed_correction_coeff(_rear_left_wheel_speed_correction_coeff)
          , rear_right_wheel_speed_correction_coeff(_rear_right_wheel_speed_correction_coeff)
          , mr_divide_cr(_mr_divide_cr)
        {
        }

        /**
         * @brief static method to load parameters from yaml
         *
         * @param node yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief static method to generate example parameters for unit test
         *
         * @return the generated parameters for unit test
         */
        static Parameters GenerateExample()
        {
            return Parameters();
        }

        /**
         * @brief output stream for vehicle velocity corrector parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters)
        {
            os << "VehicleVelocityCorrectorParameters: "
               << "\n rear_left_wheel_speed_correction_coeff = "
               << parameters.rear_left_wheel_speed_correction_coeff.Transpose()
               << "\n rear_right_wheel_speed_correction_coeff = "
               << parameters.rear_right_wheel_speed_correction_coeff.Transpose()
               << "\n mr_divide_cr = " << parameters.mr_divide_cr << std::endl;
            return os;
        }
    };

    /**
     * @brief Construct a new Velocity Corrector object
     *
     * @param parameters parameters for corrector
     */
    VehicleVelocityCorrector(Parameters const& parameters) : parameters_(parameters)
    {
    }

    /**
     * @brief Destroy the Velocity Corrector object
     *
     */
    ~VehicleVelocityCorrector()
    {
    }

    /**
     * @brief correct vehicle velocity with dynamics
     * @param multi_chassis_state Chassis State information in a period of time and timestamps are arranged in order
     * @param multi_imu IMU information in a period of time and timestamps are arranged in order.
     * @param multi_corrected_vehicle_velocity corrected vehicle velocitys
     * @note The timestamp of the first measurement of imus should not be greater than the timetstamp of the first
     * measurement of chassis_states.
     * The timestamp of the last measurement of imus should not be less than the timetstamp of the last
     * measurement of chassis_states.
     * @return bool_t false if the requirements in @note are not met.
     */
    bool_t Run(std::vector<ChassisState> const& multi_chassis_state, std::vector<ImuType> const& multi_imu,
               std::vector<StampedCorrectedVehicleVelocity>& multi_corrected_vehicle_velocity) const;

    /**
     * @brief correct vehicle velocity
     *
     * @param multi_chassis_state Chassis State information in a period of time and timestamps are arranged in order
     * @param multi_corrected_vehicle_velocity corrected vehicle velocitys
     */
    void Run(std::vector<ChassisState> const&              multi_chassis_state,
             std::vector<StampedCorrectedVehicleVelocity>& multi_corrected_vehicle_velocity) const;

    /**
     * @brief get parameters
     *
     * @return parameters
     */
    Parameters const& GetParameters() const
    {
        return parameters_;
    }

private:
    /**
     * @brief Compensate Wheel Speed object
     * @note We compensate the speed with the correction coefficients. But when the speed is less than the lower limit
     * (Here we set it to the 10 times of the bias of the correction coefficients), we don't correct it. Because the
     * correction will lead to errors. The calibrated parameters are not suitable for low speed case.
     *
     * @param chassis_state chassis state
     * @return Vector2Type Corrected left and right wheel speeds
     */
    inline Vector2Type compensateWheelSpeed(ChassisState const& chassis_state) const
    {
        auto const CompensateWheelSpeed = [&](Scalar const raw_speed, Scalar const lower_limit_of_corrected_speed,
                                              Vector2Type const& correction_coefficients) {
            return raw_speed > std::fabs(lower_limit_of_corrected_speed) ?
                       (correction_coefficients(0u) * raw_speed + correction_coefficients(1u)) :
                       raw_speed;
        };

        /// Here we set the lower limit of the corrected speed is 10 times of the bias of the correction coefficients.
        const Scalar rear_left_wheel_speed = CompensateWheelSpeed(
            chassis_state.GetRearLeftWheelSpeed(), parameters_.rear_left_wheel_speed_correction_coeff(1u) * 10.0,
            parameters_.rear_left_wheel_speed_correction_coeff);

        const Scalar rear_right_wheel_speed = CompensateWheelSpeed(
            chassis_state.GetRearRightWheelSpeed(), parameters_.rear_right_wheel_speed_correction_coeff(1u) * 10.0,
            parameters_.rear_right_wheel_speed_correction_coeff);

        return Vector2Type(rear_left_wheel_speed, rear_right_wheel_speed);
    }

    /**
     * @brief Correct Velocity With Dynamics object
     *
     * @param vx longitudinal velocity of vehicle
     * @param acc_y lateral acceleration at the center of the rear axle
     * @return Vector3Type Corrected vehicle velocity
     */
    inline Vector3Type correctLateralVelocity(Scalar const vx, Scalar const acc_y) const
    {
        const Scalar vy = vx * acc_y * parameters_.mr_divide_cr;
        return Vector3Type(vx, vy, static_cast<Scalar>(0.0));
    }

    /**
     * @brief interpolate acceleration
     *
     * @param chassis_state_timestamp timestamp of chassis state
     * @param imu_left_timestamp left timestamp of imu
     * @param imu_right_timestamp right timestamp of imu
     * @param imu_left_acc_y left lateral acceleration of imu
     * @param imu_right_acc_y right lateral acceleration of imu
     * @return Scalar interpolated lateral acceleration
     */
    inline Scalar interpolateAcceleration(Scalar const chassis_state_timestamp, Scalar const imu_left_timestamp,
                                          Scalar const imu_right_timestamp, Scalar const imu_left_acc_y,
                                          Scalar const imu_right_acc_y) const
    {
        return ((chassis_state_timestamp - imu_left_timestamp) * imu_right_acc_y +
                (imu_right_timestamp - chassis_state_timestamp) * imu_left_acc_y) /
               (imu_right_timestamp - imu_left_timestamp);
    }

private:
    Parameters parameters_;
};  // VehicleVelocityCorrector

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo
#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_VEHICLE_VELOCITY_CORRECTOR_H_
