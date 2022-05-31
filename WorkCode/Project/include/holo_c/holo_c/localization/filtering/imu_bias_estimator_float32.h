/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu_bias_estimator_float32.h
 * @brief This header file defines float32 structure related to the IMU bias estimation and the related API.
 * @attention In current version, we only support to estimate z-axis bis of the gyroscope because we only use the the
 * three axis IMU and have a plane assumption without the roll and pitch.
 *
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date May 12, 2020
 */

#ifndef HOLO_C_LOCALIZATION_FILTERING_IMU_BIAS_ESTIMATOR_FLOAT32_H_
#define HOLO_C_LOCALIZATION_FILTERING_IMU_BIAS_ESTIMATOR_FLOAT32_H_

#include <assert.h>

#include <holo_c/common/chassis_state.h>
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
 * @brief The enum is used to describe the vehicle movement status, such as stationary, run, uncertain
 */
enum VehicleMovementStatus
{
    VEHICLE_MOVEMENT_STATUS_UNCERTAIN  = 0u,  ///< The vehicle movement is uncertain
    VEHICLE_MOVEMENT_STATUS_STATIONARY = 1u,  ///< The vehicle is running
    VEHICLE_MOVEMENT_STATUS_RUN        = 2u   ///< The vehicle is stationary
};

/**
 * @brief This struct defines the related parameter of the IMU bias estimator
 *
 */
struct ImuBiasEstimatorfParameters
{
    uint32_t minimum_imu_size;  ///< The minimum size of static imu sequence for compute the bias
    /// The maximum angular velocity for the static IMU measurement. It is for the outlier rejection.
    float32_t maximum_static_angular_velocity;
    float32_t speed_threshold_for_stationary_vehicle;  /// Threshold of judge if the vehicle is stationary (Unit: m/s)
    /// the minimum number of continuous zero speed measurements for judging the car is stationary
    uint32_t continuous_zero_speed_number_for_stationary;
};

/**
 * @brief This struct is used to define the relative state of the IMU bias estimator.
 * @details This struct serves as the input and output of the static IMU bias estimator API.
 */
struct ImuBiasEstimatorfState
{
    /// The accumulation counter to record how many Imu have been used to get the imu bias
    uint64_t                   accumulation_counter;
    float32_t                  gyro_bias_z_axis;     ///< The z-axis gyroscope bias, unit: radian/s.
    bool_t                     is_imu_bias_updated;  ///< The flag of if the imu bias is valid or trusted
    enum VehicleMovementStatus car_movement_status;  ///< The movement status of the car
    uint32_t continuous_zero_speed_counter;          ///< The counter of how much continuous zero speed measurements
};

/**
 * @brief Initialize the parameter of IMU bias estimator by default values.
 *
 * @param[in, out] param The intialized parameter
 * @return The return code
 */
retcode_t imu_bias_estimatorf_init_parameter(struct ImuBiasEstimatorfParameters* param);

/**
 * @brief Initialize the state of IMU bias estimator by default values.
 *
 * @param[in, out] state The intialized state
 * @return The return code
 */
retcode_t imu_bias_estimatorf_init_state(struct ImuBiasEstimatorfState* state);

/**
 * @brief Input the raw measurement and compute its bias based on the average value.
 * @details In this function, we will judge the vehicle's movement status. If it is stationary, we will estimate the
 * z-axis gyroscope bias because we only have the three axis IMU.
 * @attention The state including the z-axis gyro bias will be updated when the API is called if the vehicle is
 * stationary. Only when the flag "is_imu_bias_updated" is true, the gyro bias in the state is valid and can be used.
 *
 * @param[in] raw_measurement The raw measurement with the chassis state
 * @param[in, out] state The updated state of imu bias estimator
 * @return The return code
 */
retcode_t imu_bias_estimatorf_run(struct RawMeasurementf const*             raw_measurement,
                                  struct ImuBiasEstimatorfParameters const* parameter,
                                  struct ImuBiasEstimatorfState*            state);

/**
 * @brief Judge if the car is stationary based on the chassisstate's vehicle speed
 *
 * @param[in] chassis_state_measurements The chassisstate measurements.
 * @param[in] chassis_state_size The size of the input chassisstate measurements
 * @param[in] parameter The parameter of the integrated navigation process
 * @param[in, out] system_state The system state which will be updated
 * @return The return code
 */
retcode_t imu_bias_estimatorf_is_car_stationary(struct ChassisState const*                chassis_state_measurements,
                                                uint32_t                                  chassis_state_size,
                                                struct ImuBiasEstimatorfParameters const* parameter,
                                                struct ImuBiasEstimatorfState*            state);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_LOCALIZATION_FILTERING_IMU_BIAS_ESTIMATOR_FLOAT32_H_
