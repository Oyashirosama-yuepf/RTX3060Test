/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lat_alignment_controller.h
 * @brief the header of the latitudinal alignment controller
 * @author wangmengyue(wangmengyue@holomatic.com)
 * @date 2021-09-10
 */

#ifndef HOLO_C_CONTROL_LAT_ALIGNMENT_CONTROLLER_H_
#define HOLO_C_CONTROL_LAT_ALIGNMENT_CONTROLLER_H_

#include <holo_c/common/chassis_state.h>
#include <holo_c/common/control_command.h>
#include <holo_c/common/dequeue.h>
#include <holo_c/common/odometry_float32.h>
#include <holo_c/common/path_float32.h>
#include <holo_c/control/debug.h>
#include <holo_c/control/filters/digital_filter.h>
#include <holo_c/control/lat_controller.h>
#include <holo_c/control/lat_torque_controller.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief latitudinal controller
 */
struct LatAlignmentController
{
    struct DigitalFilter       digital_filter;  ///< digital filter for output
    struct LatVehicleParam     param;
    struct LatTorqueController lat_torque_controller;

    float32_t last_wheel_angle;  ///< parameters for saving last step output angle info
};

/**
 * @brief Initialize the lat controller with input parameters
 *
 * @param controller Pointer to LatAlignmentController structure
 * @param lat_param The parameter of vehicle in latitudinal
 * @param lat_torque_param The parameter of vehicle in lat torque
 *
 * @return RC_SUCCESS init successfully
 * @return RC_lat_alignment_controller_INVALID_PARAM lat_param is invalid
 */
retcode_t lat_alignment_controller_init(struct LatAlignmentController*                    controller,
                                        const struct LatVehicleParam*                     lat_param,
                                        const struct LatTorqueControllerParam*            lat_torque_param,
                                        const struct LatTorqueFeedforwardControllerParam* lat_torque_feedforward_param);

/**
 * @brief Calculate the control_command in latitudinal
 *
 * @param controller Pointer to LatAlignmentController structure
 * @param odometry Pointer to Odometryf
 * @param chassis_state Pointer to ChassisState
 * @param control_command The output parameter
 *
 * @return RC_SUCCESS calculate the control command successfully
 */
retcode_t lat_alignment_controller_set_control(struct LatAlignmentController* controller,
                                               const struct Odometryf*        odometry,
                                               const struct ChassisState*     chassis_state,
                                               struct ControlCommand*         control_command,
                                               struct DebugLogger*            debug_logger);

/**
 * @brief Reset the lat alignment controller
 *
 * @param controller Pointer to LatAlignmentController structure
 * @param chassis_state Pointer to ChassisState
 */
void lat_alignment_controller_reset(struct LatAlignmentController* controller,
                                    const struct ChassisState*     chassis_state);

/**
 * @brief Calculate steering wheel angle after limiting
 *
 * @param controller Pointer to LatAlignmentController structure
 * @param wheel_angle steering wheel angle
 * @param front_wheel_bias the bias of front wheel
 *
 * @return steering wheel angle after limiting
 */
float32_t lat_alignment_controller_steer_wheel_angle_limit(struct LatAlignmentController* controller,
                                                           const float32_t                wheel_angle,
                                                           const float32_t                front_wheel_bias);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_CONTROL_LAT_ALIGNMENT_CONTROLLER_H_ */
