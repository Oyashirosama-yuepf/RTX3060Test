/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file integrated_navigation_process2_float32.h
 * @brief This header file defines the process of 2D integrated navigation relative computation.
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Mar 21, 2020
 */

#ifndef HOLO_C_LOCALIZATION_FILTERING_INTEGRATED_NAVIGATION_PROCESS2_FLOAT32_H_
#define HOLO_C_LOCALIZATION_FILTERING_INTEGRATED_NAVIGATION_PROCESS2_FLOAT32_H_

#include <assert.h>
#include <holo_c/localization/filtering/imu_bias_estimator_float32.h>
#include <holo_c/localization/filtering/integrated_navstate2_float32.h>
#include <holo_c/localization/filtering/preprocessor.h>
#include <holo_c/localization/filtering/raw_measurement_float32.h>
#include <holo_c/localization/filtering/strapdown_inertial_navigation2_float32.h>
#include <holo_c/localization/filtering/wheel_odometry_estimator.h>
#include <holo_c/utils/geographical_transformation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup localization
 * @{
 *
 */

/**
 * @brief This struct defines the relative parameters of the 2D integrated navigation process
 *
 */
struct IntegratedNavigationProcess2fParameter
{
    /// The lowest speed threshold when we think the Gnss's yaw is accurate
    float32_t minimum_speed_for_believable_gnss_heading;  ///< Unit: m/s
    /// The threshold of yaw error between our system and Gnss when we wants to correct yaw based Gnss measurement
    float32_t yaw_error_needing_correction;  ///< Unit: Radian
    /** When the speed is lower than this threshold, we don't correct yaw in the kalman filter because of the low
     * observability*/
    float32_t low_speed_threshold_for_no_yaw_correction;  ///< Unit: m/s

    struct Matrixf process_noise_covariance;                                     ///< The Kalmanfilter process noise
    float32_t      process_noise_covariance_buff[MATRIXF_MIN_BUF_SIZE(8u, 8u)];  ///< The buffer of process noise

    struct Matrixf wheel_speed_noise_covariance;  ///< The wheel speed measurement noise
    /// The buffer of wheel speed measurement noise
    float32_t wheel_speed_noise_covariance_buff[MATRIXF_MIN_BUF_SIZE(2u, 2u)];

    struct Matrixf initial_priori_estimate_covariance;  ///< The initial priori covariance
    /// The buffer of initial priori covariance
    float32_t initial_priori_estimate_covariance_buff[MATRIXF_MIN_BUF_SIZE(8u, 8u)];

    float32_t imu_sample_time;               ///< The IMU sample time(Unit: second)
    float32_t wheel_speed_fuison_frequency;  ///< The fusion frequency of the wheel speed(Unit: Hz)

    struct Vectorf extrinsic_imu_to_antenna;                                 ///< The extrinsic from imu to antenna
    float32_t      extrinsic_imu_to_antenna_buff[VECTORF_MIN_BUF_SIZE(2u)];  ///< The buffer to keep extrinsic

    /// The following is the covariance thresholds
    /** The minimum covariance of yaw of the kalman filter. When the filter covariance is lower than it, we reset the
     * covariance to the minimum value.*/
    float32_t minimum_yaw_covariance;  ///< Unit: radian^2

    struct Vectorf maximum_position_covariance;  ///< The maximum value of the position covariance
    float32_t      maximum_position_covariance_buff[VECTORF_MIN_BUF_SIZE(2u)];

    struct Vectorf minimum_velocity_covariance;  ///< The minimum value of the velocity covariance
    float32_t      minimum_velocity_covariance_buff[VECTORF_MIN_BUF_SIZE(2u)];

    struct ImuBiasEstimatorfParameters imu_bias_estimator_param;  ///< IMU bias esimator parameters
    float32_t default_gyro_bias_z_axis;  ///< The default gyro bias for the dynamic initialization

    struct PreprocessorParameters preprocessor_param;  ///< The parameter of preprocessor

    struct DifferentialDriveModelParameter diff_drive_param;  ///< The parameter of the differential-drive model
};

/**
 * @brief This struct defines the state of the 2D integrated navigation process
 *
 */
struct IntegratedNavigationProcess2fState
{
    struct Timestamp last_velocity_fusion_timestamp;  ///< The timestamp of processing velocity fusion last time
    bool_t           is_initialized;                  ///< The flag which the integrated navigation is initialized
    struct ImuBiasEstimatorfState      imu_bias_estimator_state;  ///< IMU bias estimator state
    bool_t                             is_imu_bias_initialized;   /// The flag if IMU bias is initialized
    struct PreprocessorState           preprocessor_state;        ///< The state of preprocessor
    struct DifferentialDriveModelState diff_drive_state;          ///< The state of  differential-drive model
};

/**
 * @brief This struct defines the float32_t GNSS measurement in 2-dimension UTM coordinate.
 * @attention Please attention to the precision of float type. If the position value is over the range of the float
 * type, we must use the offset of the coordinate to reduce the value of position.
 *
 */
struct GnssMeasurementUtm2f
{
    Coordinate_t   gnss_coordinate;  ///< The corresponding coordinate
    struct Vectorf gnss_position;    ///< The GNSS east and north position measurement in UTM coordinate (Unit: m)
    float32_t      gnss_position_buff[VECTORF_MIN_BUF_SIZE(2u)];  ///< The buffer of GNSS position
    struct Vectorf gnss_velocity;  ///< The GNSS east and north velocity measurement (Unit: m/s)
    float32_t      gnss_velocity_buff[VECTORF_MIN_BUF_SIZE(2u)];          ///< The buffer of GNSS velocity
    struct Matrixf gnss_position_cov;                                     ///< The GNSS position covariance (Unit: m^2)
    float32_t      gnss_position_cov_buff[MATRIXF_MIN_BUF_SIZE(2u, 2u)];  ///< The buffer of GNSS position covariance
    struct Matrixf gnss_velocity_cov;  ///< The GNSS velocity covariance (Unit: (m/s)^2)
    float32_t      gnss_velocity_cov_buff[MATRIXF_MIN_BUF_SIZE(2u, 2u)];  ///< The buffer of GNSS velocity covariance
};

/**
 * @brief Initialize the state of the integrated navigation process from default
 *
 * @param[in] state The initialized state
 * @return The return code
 */
retcode_t integrated_navigation_process2f_init_state(struct IntegratedNavigationProcess2fState* state);

/**
 * @brief Initialize the parameter of the integrated navigation process from default
 *
 * @param[out] parameter The initialized parameter
 * @return The return code
 */
retcode_t integrated_navigation_process2f_init_parameter(struct IntegratedNavigationProcess2fParameter* parameter);

/**
 * @brief Initialize the gnss mesurement struct from default values.
 *
 * @param[in, out] gnss_measurement The initialized GNSS measurement struct
 * @return The return code
 */
retcode_t integrated_navigation_process2f_init_gnss_measurement_utm2f(struct GnssMeasurementUtm2f* gnss_measurement);

/**
 * @brief Run the initialization of the integrated navigation process
 * @details We will use the GNSS measurement in the raw measurements to initialize the position and heading of the
 * IntegratedNavstate. So we can initialize it successfully when there is avaiable GNSS measurement. Otherwise, we will
 * fail to initalize. If there is only the ChassisState measurements, we only update the timestamp of the
 * IntegratedNavstate.
 *
 * @param[in] raw_measurement The raw measurement
 * @param[in] parameter The parameter of the integrated navigation process
 * @param[out] integrated_navstate The initalized IntegratedNavstate
 * @return It returns ture when we initilize successfully. Otherwise, it will return false
 */
bool_t integrated_navigation_process2f_initialize(struct RawMeasurementf const*                        raw_measurement,
                                                  struct IntegratedNavigationProcess2fParameter const* parameter,
                                                  struct IntegratedNavstate2f* integrated_navstate);

/**
 * @brief The definition of main process used to realize the integrated navigation
 *
 * @param[in] raw_measurement The processed raw measurements
 * @param[in] parameter The parameter of the integrated navigation process
 * @param[in, out] integrated_navstate The last IntegratedNavstate which will be updated based on the RawMesurement.
 * @param[in, out] state The state of the integrated navigation process
 * @return The return code
 */
retcode_t integrated_navigation_process2f_run(struct RawMeasurementf*                              raw_measurement,
                                              struct IntegratedNavigationProcess2fParameter const* parameter,
                                              struct IntegratedNavstate2f*                         integrated_navstate,
                                              struct IntegratedNavigationProcess2fState*           state);

/**
 * @brief Predict the integrated navigation state by the imu measurement
 *
 * @param[in, out] integrated_navstate The last IntegratedNavstate which will be updated based on the imu
 * measurement.
 * @param[in] imu The IMU measurements
 * @param[in] parameter The parameter of the integrated navigation process
 * @return The return code
 */
retcode_t integrated_navigation_process2f_predict(struct IntegratedNavstate2f* integrated_navstate,
                                                  struct Imuf const*           imu,
                                                  struct IntegratedNavigationProcess2fParameter const* parameter);

/**
 * @brief Update the integrated navigation state when there is a new wheel speed measurement(ChassisState)
 *
 * @param[in, out] integrated_navstate The last IntegratedNavstate which will be updated based on the wheel speed
 * measurement.
 * @param[in] wheel_speed The wheel speed measurement
 * @param[in] parameter The parameter of the integrated navigation process
 * @param[in] is_vehicle_stationary The flag which the vehicle is stationary(true: stationary)
 * @return The return code
 */
retcode_t integrated_navigation_process2f_update_by_wheel_speed_measurement(
    struct IntegratedNavstate2f* integrated_navstate, float32_t wheel_speed,
    struct IntegratedNavigationProcess2fParameter const* parameter, bool_t is_vehicle_stationary);

/**
 * @brief Update the integrated navigation state when there is a new gnss measurement
 *
 * @param[in, out] integrated_navstate The last IntegratedNavstate which will be updated based on the gnss
 * measurement.
 * @param[in] gnss_measurement The GNSS speed measurement
 * @param[in] parameter The parameter of the integrated navigation process
 * @return The return code
 */
retcode_t integrated_navigation_process2f_update_by_gnss_measurement(
    struct IntegratedNavstate2f* integrated_navstate, struct GnssPvt const* gnss_measurement,
    struct IntegratedNavigationProcess2fParameter const* parameter);

/**
 * @brief Correct the navigation result with the Kalman filter's output
 *
 * @param[in] state_error The state error vector
 * @param[in, out] navstate The navstate which will be updated
 * @param[in, out] coordinate The system coordinate which will be updated
 * @return The return code
 */
retcode_t integrated_navigation_process2f_correct_navstate(struct Vectorf const* state_error,
                                                           struct Navstate2f* navstate, Coordinate_t* coordinate);

/**
 * @brief Compute state transision matrix of Kalman filter based on the current Navstate
 *
 * @param[in] navstate The current Navstate
 * @param[in] sample_time The sample time between two predictions. It is usually imu sample time.
 * @param[out] state_transition_matrix The current state transision matrix (8*8 matrix)
 * @return The return code
 */
retcode_t integrated_navigation_process2f_compute_state_transision_matrix(struct Navstate2f const* navstate,
                                                                          float32_t                sample_time,
                                                                          struct Matrixf* state_transition_matrix);

/**
 * @brief Compute observation matrix for only the velocity error observation
 *
 * @param[in] navstate The current Navstate
 * @param[in] is_zero_velocity_update If it is ZUPT
 * @param[out] observation_matrix The observation matrix for only the velocity error observation
 * @return The return code
 */
retcode_t integrated_navigation_process2f_compute_observation_matrix_for_velocity(struct Navstate2f const* navstate,
                                                                                  bool_t is_zero_velocity_update,
                                                                                  struct Matrixf* observation_matrix);

/**
 * @brief Compute observation matrix for the velocity error and position error observation
 *
 * @param[out] observation_matrix The observation matrix
 * @return The return code
 */
retcode_t
integrated_navigation_process2f_compute_observation_matrix_for_velocity_position(struct Matrixf* observation_matrix);

/**
 * @brief Set the yaw based on the GNSS measurement
 *
 * @param[in, out] navstate The Navstate which its yaw is updated with the GNSS measurement
 * @param[in] gnss_measurement The GNSS measurement
 * @param[in] minimum_gnss_velocity The lowest speed threshold when we think the Gnss's yaw is accurate
 * @param[in] minimum_heading_error The threshold of yaw error between our system and Gnss when we wants to correct yaw
 * based Gnss measurement
 * @return The return code
 */
retcode_t integrated_navigation_process2f_set_yaw_based_on_gnss(struct Navstate2f*    navstate,
                                                                struct GnssPvt const* gnss_measurement,
                                                                float32_t             minimum_gnss_velocity,
                                                                float32_t             minimum_heading_error);

/**
 * @brief Calculate the speed and position compensation due to the arm value of the GNSS antenna to the IMU
 *
 * @param[in] navstate The current Navstate
 * @param[in] lever_arm_value The lever arm value(Parent coord: IMU; Child coord: GNSS antenna or other sensor)
 * @param[out] velocity_compensation The velocity compensation
 * @param[out] position_compensation The position compensation
 * @return The return code
 */
retcode_t integrated_navigation_process2f_compute_level_arm_compensation(struct Navstate2f const* navstate,
                                                                         struct Vectorf const*    lever_arm_value,
                                                                         struct Vectorf*          velocity_compensation,
                                                                         struct Vectorf* position_compensation);

/**
 * @brief Get the navigation information in UTM coordinate from GNSS measurement
 * @details This function will convert the longitude and latitude of the GNSS to the UTM position, and compute the
 * corresponding Coordinate including ZoneId, offset_X and offset_Y. Besides that, it also can get the horizon velocity,
 * position covariance, velocity covariance from the input GNSS measurement.
 *
 * @param[in] gnss_measurement The GNSS measurement
 * @param[out] gnss_measurement_utm_2d The GNSS measurement in 2-dimension UTM coordinate
 * @return The return code
 */
retcode_t integrated_navigation_process2f_get_utm_navigation_information_from_gnss(
    struct GnssPvt const* gnss_measurement, struct GnssMeasurementUtm2f* gnss_measurement_utm_2d);

/**
 * @brief Update the covariance of Navstate with the Kalman fitler priori covariance, including pose covariance,
 * velocity covariance, acceleration bias covariance and gyro bias covariance
 *
 * @param[in] kalman_filter_covariance The kalaman filter priori covariance matrix(8*8 matrix)
 * @param[out] navstate The updated navstate
 * @return The return code
 */
retcode_t integrated_navigation_process2f_update_navstate_covariance(struct Matrixf const* kalman_filter_covariance,
                                                                     struct Navstate2f*    navstate);

/**
 * @brief Correct the kalman filter with velocity and position measurement
 *
 * @param[in] navstate The current navigation state
 * @param[in] gnss_measurement The GNSS measurement including position, velocity, coordinate and covariances
 * @param[in] param The parameter of the integrated navigation process
 * @param[in, out] kalman_filter The corrected kalman filter
 * @return The return code
 */
retcode_t integrated_navigation_process2f_run_kalmanfilter_correction_with_velocity_position(
    struct Navstate2f const* navstate, struct GnssMeasurementUtm2f const* gnss_measurement,
    struct IntegratedNavigationProcess2fParameter const* param, struct KalmanFilterf* kalman_filter);

/**
 * @brief Correct the Kalman filter only with velocity measurement
 *
 * @param[in] navstate The current navigation state
 * @param[in] velocity The velocity measurement (Ve, Vn)
 * @param[in] observation_noise_covariance The corresponding observation noise matrix
 * @param[in] is_vehicle_stationary The flag which the vehicle is stationary
 * @param[in, out] kalman_filter The corrected kalman filter
 * @return The return code
 */
retcode_t integrated_navigation_process2f_run_kalmanfilter_correction_with_velocity(
    struct Navstate2f const* navstate, struct Vectorf const* velocity,
    struct Matrixf const* observation_noise_covariance, bool_t is_vehicle_stationary,
    struct KalmanFilterf* kalman_filter);

/**
 * @brief Limit range of the covariance matrix according to the input parameter
 *
 * @param[in, out] covariance The covariance matrix wanted to be limited
 * @param[in] param The parameter including the thresholds
 * @return The return code
 */
retcode_t integrated_navigation_process2f_limit_covariance_range(
    struct Matrixf* covariance, struct IntegratedNavigationProcess2fParameter const* param);

/**
 * @brief Update timestamp of the integrated navstate with the input timestamp.
 * @details If the input timestamp is newer than the timestamp of intergated navstate, we will use it to set the
 * timestamp of integrated navstate. But if the input timestamp is older than or equal to the timestamp of integrated
 * navstate, there are two cases: 1) If the add_time_offset is true, we will add a litter time offset (such as 1e-6
 * second) to the timestamp of the integrated navigation to change it. 2) If the add_time_offset is false, we do
 * nothing.
 *
 * @param[in] input_time The input timestamp
 * @param[in] integrated_navstate The integrated navstate wanted to be updated
 * @param[in] add_time_offset The flag which to add time offset
 * @return The return code
 */
retcode_t integrated_navigation_process2f_update_navstate_timestamp(struct Timestamp const*      input_time,
                                                                    struct IntegratedNavstate2f* integrated_navstate,
                                                                    bool_t                       add_time_offset);

/**
 * @brief Run the IMU bias estimator
 * @details This function will do the following three things:
 * 1) Estimate the stationary IMU bias;
 * 2) If the vehicle is running but the IMU bias isn't initialized, initialize it by the default value;
 * 3) Judge the vehicle is running or stationary.
 *
 * @param[in] raw_measurement The raw measurements
 * @param[in] parameter The parameter of integrated navigation process
 * @param[in, out] integrated_navstate The integrated navstate, its IMU bias may be updated
 * @param[in, out] state The state of integrated navigation process
 * @return The return code
 */
retcode_t integrated_navigation_process2f_run_imu_bias_estimator(
    struct RawMeasurementf const* raw_measurement, struct IntegratedNavigationProcess2fParameter const* parameter,
    struct IntegratedNavstate2f* integrated_navstate, struct IntegratedNavigationProcess2fState* state);

/**
 * @brief The definition of main process used to realize the integrated navigation based on the differential-drive model
 *
 * @param[in] raw_measurement The processed raw measurements
 * @param[in] parameter The parameter of the integrated navigation process
 * @param[in, out] integrated_navstate The last IntegratedNavstate which will be updated based on the RawMesurement.
 * @param[in, out] state The state of the integrated navigation process
 * @return The return code
 */
retcode_t integrated_navigation_process2f_run_with_diff_drive_model(
    struct RawMeasurementf* raw_measurement, struct IntegratedNavigationProcess2fParameter const* parameter,
    struct IntegratedNavstate2f* integrated_navstate, struct IntegratedNavigationProcess2fState* state);

/**
 * @brief Switch the grid ID of the UTM coodinate if the current position is out of the range of the grid
 *
 * @param[in, out] current_pos_utm The current UTM position. It will be update if the position is out of the range of
 * the grid
 * @param[in, out] coordinate The current coordinate, It will be update if the current position is out of the range of
 * the current grid
 * @return If the grid has been switched and the coordinate has been update, it will return true. Otherwise, it return
 * false.
 */
bool_t integrated_navigation_process2f_switch_utm_grid(struct Point2f* current_pos_utm, Coordinate_t* coordinate);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_LOCALIZATION_FILTERING_INTEGRATED_NAVIGATION_PROCESS2_FLOAT32_H_
