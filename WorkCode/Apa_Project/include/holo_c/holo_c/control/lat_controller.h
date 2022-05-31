/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lat_controller.h
 * @brief the header of the latitudinal controller
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2019-10-11
 */

#ifndef HOLO_C_CONTROL_LAT_CONTROLLER_H_
#define HOLO_C_CONTROL_LAT_CONTROLLER_H_

#include <holo_c/common/chassis_state.h>
#include <holo_c/common/control_command.h>
#include <holo_c/common/dequeue.h>
#include <holo_c/common/odometry_float32.h>
#include <holo_c/common/path_float32.h>
#include <holo_c/control/debug.h>
#include <holo_c/control/lat_feedforward_controller.h>
#include <holo_c/control/lat_torque_controller.h>
#include <holo_c/control/mpc_controller.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>

#define LAST_WHEEL_ANGLE_DEQUE_SIZE 5

#ifdef __cplusplus
extern "C" {
#endif

#define STEER_RATIO_TABLE_SIZE 11    ///< numbers of steer ratio table.

struct LatVehicleParam
{
    float32_t steer_ratio;
    float32_t hz;
    float32_t dead_zone;
    float32_t clamp_angle;
    float32_t step_angle;
    float32_t step_n_angle;
    float32_t cutoff_freq;
    float32_t steer_wheel_bias;
    
    struct Point2f  steer_ratio_table[STEER_RATIO_TABLE_SIZE];
    uint32_t        steer_ratio_table_size;

    struct Point2f  front_wheel_steer_ratio_table[STEER_RATIO_TABLE_SIZE];
    uint32_t        front_wheel_steer_ratio_table_size;

    bool_t enable_lat_angle_control;
    bool_t enable_lat_torque_control;
};

/**
 * @brief latitudinal controller
 */
struct LatController
{
    struct MpcController            mpc_controller;
    struct LatFeedforwardController lat_ff_controller;
    struct DigitalFilter            digital_filter;  ///< digital filter for output
    struct LatVehicleParam          param;
    struct LatTorqueController      lat_torque_controller;

    float32_t last_wheel_angle;            ///< parameters for saving last step output angle info

    float32_t       last_wheel_angle_buffer[LAST_WHEEL_ANGLE_DEQUE_SIZE];
    struct Dequeuef last_wheel_angle_deque;  ///< deque for saving last several step output angle info
};

/**
 * @brief Initialize the lat controller with input parameters
 *
 * @param controller Pointer to LatController structure
 * @param mpc_param The mpc_controller's parameter
 * @param lat_ff_param The lateral feed forward param
 * @param lat_param The parameter of vehicle in latitudinal
 * @param lat_torque_param The parameter of vehicle in lat torque
 * @param lat_torque_ff_param The parameter of vehicle in lat torque feedforward controller
 *
 * @return RC_SUCCESS init successfully
 * @return RC_LAT_CONTROLLER_INVALID_PARAM lat_param is invalid
 */
retcode_t lat_controller_init(struct LatController*                             controller,
                              const struct MpcControllerParam*                  mpc_param,
                              const struct LatFeedforwardControllerParam*       lat_ff_param,
                              const struct LatVehicleParam*                     lat_param,
                              const struct LatTorqueControllerParam*            lat_torque_param,
                              const struct LatTorqueFeedforwardControllerParam* lat_torque_ff_param);

/**
 * @brief Calculate the control_command in latitudinal
 *
 * @param controller Pointer to LatController structure
 * @param path The path
 * @param odometry Pointer to Odometryf
 * @param chassis_state Pointer to ChassisState
 * @param control_command The output parameter
 *
 * @return RC_SUCCESS calculate the control command successfully
 */
retcode_t lat_controller_set_control(struct LatController*         controller,
                                     const struct Pathf*           path,
                                     const struct Odometryf*       odometry,
                                     const struct ChassisState*    chassis_state,
                                     struct ControlCommand*        control_command,
                                     struct LatControlDebugLogger* debug_logger);

/**
 * @brief Reset the lat controller
 *
 * @param controller Pointer to LatController structure
 */
void lat_controller_reset(struct LatController* controller, const struct ChassisState* chassis_state);

/**
 * @brief Calculate steering wheel angle after limiting
 *
 * @param controller Pointer to LatController structure
 * @param wheel_angle steering wheel angle
 * @param front_wheel_bias the bias of front wheel
 *
 * @return steering wheel angle after limiting
 */
float32_t lat_controller_steer_wheel_angle_limit(struct LatController* controller, const float32_t wheel_angle, const float32_t front_wheel_bias);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_CONTROL_LAT_CONTROLLER_H_ */
