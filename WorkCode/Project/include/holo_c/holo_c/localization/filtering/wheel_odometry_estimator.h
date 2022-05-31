/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file wheel_odometry_estimator.h
 * @brief This header file defines structure related to the wheel odometry estimator and the related API.
 * @details Now we realize the wheel odometry estimator based on the differential-drive model. If it is necessary, we
 * can also add the realization of the bicycle model.
 *
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date July 6, 2020
 */

#ifndef HOLO_C_LOCALIZATION_FILTERING_WHEEL_ODOMETRY_ESTIMATOR_H_
#define HOLO_C_LOCALIZATION_FILTERING_WHEEL_ODOMETRY_ESTIMATOR_H_

#include <assert.h>

#include <holo_c/localization/common/navstate2_float32.h>
#include <holo_c/localization/filtering/raw_measurement_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup localization
 * @{
 *
 */

/**
 * @brief The type of the vehicle.
 *
 */
enum VehicleType
{
    VEHICLE_TYPE_MAGOTAN  = 0u,   ///< The FAW-Volkswagen Magotan
    VEHICLE_TYPE_ENVISION = 1u,   ///< The SAIC-GM ENVISION
    VEHICLE_TYPE_CHERY    = 3u,   ///< The Chery Little ant
    VEHICLE_TYPE_UNKNOWN  = 255u  ///< Unknown vehicle type
};

/**
 * @brief The struct to describe the vehicle specification such as the vehicle type, wheel base and track gauge.
 *
 */
struct VehicleSpecification
{
    enum VehicleType vehicle_type;  ///< The vehicle type
    /// The wheel base: the distance from the center of car's front axis to the rear axis.
    float32_t wheel_base;   ///< Unit: meter
    float32_t track_gauge;  ///< The distance between the left wheel and the right wheel. Unit: meter
};

/**
 * @brief The parameter of the differential-drive model
 *
 */
struct DifferentialDriveModelParameter
{
    struct VehicleSpecification vehicle_specification;          ///< The vehicle sepdification
    float32_t                   error_coefficient_left_wheel;   ///< The error constant coefficient of the left wheel
    float32_t                   error_coefficient_right_wheel;  ///< The error constant coefficient of the right wheel
    bool_t is_use_middle_point;            ///< The flag which use the mid point between the two near Chassistate or not
    bool_t is_update_navstate_covariance;  ///< The flag which update the covariance of the navstate or not
    bool_t is_use_yaw_rate;                ///< The flag which use the yawrate
};

/**
 * @brief The process state of the wheel odometry estimator based on the differential-drive model
 *
 */
struct DifferentialDriveModelState
{
    struct ChassisState last_chassis_state;  ///< The last chassis state
    /// The state transition jacobian of the state[x, y, vel_x, vel_y, omega_z] w.r.t previous state
    struct Matrixf state_transition_jacobian;
    /// The buffer of the state_transition_jacobian
    float32_t state_transition_jacobian_buff[MATRIXF_MIN_BUF_SIZE(5u, 5u)];
    /** The state transition jacobian of the state[x, y, vel_x, vel_y, omega_z] w.r.t the model variables
     * [wheel_speed_left, wheel_speed_rigth] */
    struct Matrixf noise_transition_jacobian;
    /// The buffer of the noise_transition_jacobian
    float32_t      noise_transition_jacobian_buff[MATRIXF_MIN_BUF_SIZE(5u, 2u)];
    struct Matrixf noise_covariance;  ///< The noise covariance of the model variables
    float32_t      noise_covariance_buff[MATRIXF_MIN_BUF_SIZE(2u, 2u)];  ///< The buffer of noise_covariance
};

/**
 * @brief Initialize the parameter of the differential-drive model
 *
 * @param[out] param The parameter of the differential-drive model
 * @return The return code
 */
retcode_t wheel_odometry_estimator_init_diff_drive_parameter(struct DifferentialDriveModelParameter* param);

/**
 * @brief Initialize the state of the differential-drive model
 *
 * @param[out] state The state of the differential-drive model
 * @return The return code
 */
retcode_t wheel_odometry_estimator_init_diff_drive_state(struct DifferentialDriveModelState* state);

/**
 * @brief The main pipeline to run the differential-drive model to update the
 *
 * @param[in] chassis_state The Chassisstate infomation from the bus
 * @param[in] parameter The parameter of the differential-drive model
 * @param[in, out] nav_state The updated navstate
 * @param[in,out] state The updated differential-drive model state
 * @return retcode_t
 */
retcode_t wheel_odometry_estimator_differential_drive_run(struct ChassisState const*                    chassis_state,
                                                          struct DifferentialDriveModelParameter const* parameter,
                                                          struct Navstate2f*                            nav_state,
                                                          struct DifferentialDriveModelState*           state);

/**
 * @brief We get the mean chassis state from the last and current input.
 *
 * @param[in] current_chassis_state The current ChassisState input
 * @param[in] last_chassis_state The last ChassisState input
 * @param[out] mean_chassis_state The mean ChassisState
 * @return The return code
 */
retcode_t wheel_odometry_estimator_get_mean_chassisstate(struct ChassisState const* current_chassis_state,
                                                         struct ChassisState const* last_chassis_state,
                                                         struct ChassisState*       mean_chassis_state);

/**
 * @brief We compute the forward kinematics based on the differential-drive model
 *
 * @param[in] chassis_state The Chassisstate infomation from the bus
 * @param[in] param The parameter of the differential-drive model
 * @param[out] velocity The velocity from the kinematics, it is 2-d vector:[longitude velocity, z-axis angular velocity]
 * @param[out] velocity_cov The noise covariance of the input variables
 * @return The return code
 */
retcode_t wheel_odometry_estimator_compute_diff_drive_kinematics(struct ChassisState const* chassis_state,
                                                                 struct DifferentialDriveModelParameter const* param,
                                                                 struct Vectorf*                               velocity,
                                                                 struct Matrixf* velocity_cov);

/**
 * @brief We update the navstate based on the differential-drive model and update its state.
 *
 * @param[in] chassis_state The Chassisstate infomation from the bus
 * @param[in] parameter The parameter of the differential-drive model
 * @param[in, out] nav_state The updated navstate
 * @param[in,out] state The updated differential-drive model state
 * @return retcode_t
 */
retcode_t wheel_odometry_estimator_update_navstate_with_diff_drive_model(
    struct ChassisState const* chassis_state, struct DifferentialDriveModelParameter const* parameter,
    struct Navstate2f* nav_state, struct DifferentialDriveModelState* state);

/**
 * @brief We compute the state transition jacobian matrix from the previous state to next state of
 * the f(x, y, omega_z, vel_x, vel_y)
 * @attention Here the axis x and axis y is the x and y directions of the UTM coordinate.
 *
 * @param[in] velocity The velocity from the kinematics, it is 2-d vector:[longitude velocity, z-axis angular velocity]
 * @param[in] previous_yaw The previous yaw value before update
 * @param[in] delta_time The delta time between the two updates
 * @param[out] state_transition_jacobian The state transition jacobian matrix
 * @return The return code
 */
retcode_t wheel_odometry_estimator_compute_state_transition_jacobian(struct Vectorf const* velocity,
                                                                     float32_t const       previous_yaw,
                                                                     float32_t const       delta_time,
                                                                     struct Matrixf*       state_transition_jacobian);
/**
 * @brief We compute the noise transition jacobian matrix  of the f(x, y, omega_z, vel_x, vel_y) w.r.t input variables
 * @attention Here the axis x and axis y is the x and y directions of the UTM coordinate.
 *
 * @param[in] velocity The velocity from the kinematics, it is 2-d vector:[longitude velocity, z-axis angular velocity]
 * @param[in] previous_yaw The previous yaw value before update
 * @param[in] delta_time The delta time between the two updates
 * @param[in] parameter The parameter of the differential-drive model
 * @param[out] noise_transition_jacobian The noise transition jacobian matrix
 * @return The return code
 */
retcode_t wheel_odometry_estimator_compute_noise_transition_jacobian(
    struct Vectorf const* velocity, float32_t const previous_yaw, float32_t const delta_time,
    struct DifferentialDriveModelParameter const* parameter, struct Matrixf* noise_transition_jacobian);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_LOCALIZATION_FILTERING_WHEEL_ODOMETRY_ESTIMATOR_H_
