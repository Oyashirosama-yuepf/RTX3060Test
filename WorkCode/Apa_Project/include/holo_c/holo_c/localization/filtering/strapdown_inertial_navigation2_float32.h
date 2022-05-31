/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file strapdown_inertial_navigation2_float32.h
 * @brief This header file defines 2-D strapdown inertial navigation struct and relative functions.
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Feb 28, 2020
 */

#ifndef HOLO_C_LOCALIZATION_STRAPDOWN_INERTIAL_NAVIGATION2_FLOAT32_H_
#define HOLO_C_LOCALIZATION_STRAPDOWN_INERTIAL_NAVIGATION2_FLOAT32_H_

#include <assert.h>

#include <holo_c/common/imu_bias_float32.h>
#include <holo_c/common/imu_float32.h>
#include <holo_c/localization/common/navstate2_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup localization
 * @{
 *
 */

/**
 * @brief Update strapdown inertial navigation state based on the new IMU measurement
 * @todo  When the Imu2f is constructed, use Imu2f instead of the argument Imuf
 *
 * @param[in,out] navstate The navstate which will be updated
 * @param[in] imu The imu measurement
 * @param[in] imu_sample_time The imu sample time
 * @return The returned code
 */
retcode_t strapdown_inertial_navigation2f_update(struct Navstate2f* navstate, struct Imuf const* imu,
                                                 float32_t const imu_sample_time);

/**
 * @brief Update the attitude based on the new imu measurement
 *
 * @param[in,out] rot2 The 2-dimension rotation
 * @param[in] z_axis_angular_velocity The z axis angular velocity measurement
 * @param[in] z_axis_angular_velocity_bias The z axis angular velocity bias value
 * @param[in] imu_sample_time The imu sample time
 * @return The returned code
 */
retcode_t strapdown_inertial_navigation2f_update_attitude(struct Rot2f*   rotation,
                                                          float32_t const z_axis_angular_velocity,
                                                          float32_t const z_axis_angular_velocity_bias,
                                                          float32_t const imu_sample_time);

/**
 * @brief Update the velocity in navigation coordinate based on the new imu measurement
 *
 * @param[in,out] velocity The velocity in navigation coordinate (2*1 Vector, Unit: m/s)
 * @param[in] rotation The current attitude
 * @param[in] xy_axis_acceleration The acceleration measurement of x axis and y axis in body coordinate
 * @param[in] xy_axis_acceleration_bias The acceleration bias of x axis and y axis in body coordinate
 * @param[in] imu_sample_time The imu sample time
 * @return The returned code
 */
retcode_t strapdown_inertial_navigation2f_update_velocity(struct Vectorf* velocity, struct Rot2f const* rotation,
                                                          struct Vectorf const* xy_axis_acceleration,
                                                          struct Vectorf const* xy_axis_acceleration_bias,
                                                          float32_t const       imu_sample_time);

/**
 * @brief Update the position in navigation coordinate
 *
 * @param[in, out] position The position will be updated (east, north)
 * @param[in] last_velocity The last velocity in navigation coordinate (2D vector: east, north)
 * @param[in] current_velocity The current velocity in navigation coordinate (2D vector: east, north)
 * @return The returned code
 */
retcode_t strapdown_inertial_navigation2f_update_position(struct Vectorf* position, struct Vectorf const* last_velocity,
                                                          struct Vectorf const* current_velocity,
                                                          float32_t const       imu_sample_time);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_LOCALIZATION_STRAPDOWN_INERTIAL_NAVIGATION2_FLOAT32_H_
