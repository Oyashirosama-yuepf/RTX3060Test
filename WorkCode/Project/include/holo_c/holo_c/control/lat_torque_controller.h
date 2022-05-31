/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lat_torque_controller.h
 * @brief the header of the lat torque controller
 * @author taobingbing(taobingbing@holomatic.com)
 * @date 2020-12-15
 */

#ifndef HOLO_C_CONTROL_LAT_TORQUE_CONTROLLER_H_
#define HOLO_C_CONTROL_LAT_TORQUE_CONTROLLER_H_

#include <holo_c/common/chassis_state.h>
#include <holo_c/common/odometry_float32.h>
#include <holo_c/control/segment_pid.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point2.h>
#include <holo_c/control/lat_torque_feedforward_controller.h>
#include <holo_c/control/filters/mean_filter.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LAT_TORQUE_CONTROLLER_CLAMP_NUM 6

/**
 * @brief LatTorqueController's parameter
 */
struct LatTorqueControllerParam
{
    struct SegmentPidParam lat_torque_pid_param;

    float32_t      step_torque;
    float32_t      lat_torque_value_dead_zone;
    struct Point2f lat_torque_clamp_table[LAT_TORQUE_CONTROLLER_CLAMP_NUM];
    uint32_t       lat_torque_clamp_table_size;
};

/**
 * @brief This structure represents the torque controller for lateral control
 */
struct LatTorqueController
{
    struct SegmentPid               lat_torque_pid_controller;
    struct LatTorqueControllerParam param;
    struct LatTorqueFeedforwardController lat_torque_ff_controller;
    struct MeanFilter               steer_angle_rate_error_filter;

    float32_t last_wheel_torque;
    float32_t last_steer_angle;
    float32_t last_exp_steer_angle;
};

/**
 * @brief Initialize the lat torque controller with input parameters
 *
 * @param controller Pointer to LatTorqueController structure
 * @param lat_torque_param The lat_torque_controller's parameter
 * @param lat_torque_ff_param Th lat_torque_feedforward_controller's parameter
 *
 * @return RC_SUCCESS init successfully
 * @return todo
 */
retcode_t lat_torque_controller_init(struct LatTorqueController*                       controller,
                                     const struct LatTorqueControllerParam*            lat_torque_param,
                                     const struct LatTorqueFeedforwardControllerParam* lat_torque_ff_param);

/**
 * @brief Calculate steering wheel torque after step limiting
 *
 * @param controller Pointer to LatTorqueController structure
 * @param torque steering wheel torque
 *
 * @return steering wheel torque after step limiting
 */
float32_t lat_controller_steer_wheel_torque_step_limit(struct LatTorqueController* controller, const float32_t torque);

/**
 * @brief Calculate steering wheel torque after output limiting
 *
 * @param controller Pointer to LatTorqueController structure
 * @param torque steering wheel torque
 * @param speed speed
 *
 * @return steering wheel torque after output limiting
 */
float32_t lat_controller_steer_wheel_torque_output_limit(struct LatTorqueController* controller,
                                                         const float32_t             torque,
                                                         const float32_t             speed);

/**
 * @brief Calculate the control_command in lat torque
 *
 * @param controller Pointer to LatTorqueController structure
 * @param chassis_state Pointer to ChassisState
 * @param odometry Pointer to Odometryf
 * @param exp_angle Expected front wheel angle
 *
 * @return the lateral torque controller's output
 */
float32_t lat_torque_controller_set_control(struct LatTorqueController*         controller,
                                            const struct ChassisState*          chassis_state,
                                            const struct Odometryf*             odometry,
                                            const float32_t                     exp_angle,
                                            struct LatTorqueControlDebugLogger* debug_logger);

/**
 * @brief Reset the lat torque controller
 *
 * @param controller Pointer to LatTorqueController structure
 */
void lat_torque_controller_reset(struct LatTorqueController* controller);

/**
 * @brief Smooth the steer angle rate by output limiting and filter
 *
 * @param filter Pointer to Meanfilter
 * 
 * @param steer_angle_rate the raw steer angle rate 
 * 
 * @return the smooth steer angle rate
 */
float32_t lat_torque_controller_steer_wheel_rate_smooth(struct MeanFilter* filter, float32_t steer_angle_rate);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_CONTROL_LAT_TORQUE_CONTROLLER_H_ */
