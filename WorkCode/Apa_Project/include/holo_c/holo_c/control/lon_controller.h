/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lon_controller.h
 * @brief the header of the lonitudinal controller
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2019-10-11
 */

#ifndef HOLO_C_CONTROL_LON_CONTROLLER_H_
#define HOLO_C_CONTROL_LON_CONTROLLER_H_

#include <holo_c/common/chassis_state.h>
#include <holo_c/common/control_command.h>
#include <holo_c/common/odometry_float32.h>
#include <holo_c/common/path_float32.h>
#include <holo_c/control/debug.h>
#include <holo_c/control/filters/mean_filter.h>
#include <holo_c/control/lon_feedforward_controller.h>
#include <holo_c/control/lpc_controller.h>
#include <holo_c/control/segment_pid.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CYCLE_TIME 0.02                               ///< Control pariod time
#define MIN_TORQUE_GRADIENT 10.0                      ///< Min torque gradient
#define ACC_TO_DEC_TIME 0.2                           ///< Time from toeque to deceleration
#define ROAD_SLOPE_FILTER_SIZE 5                      ///< Road slope filter save size
#define UPHILL_ASSIST_SLOPE_LIMIT 1.5                 ///< Uphill assist slope minimum limit
#define DOWNHILL_ASSIST_SLOPE_LIMIT -1                ///< Downhill assist slope minimum limit
#define UPHILL_ASSIST_START_SPEED_LIMIT 0.27          ///< Uphill assis start speed limit
#define ROAD_SLOPE_MAXIMUM_LIMIT 20.0                 ///< Maximum road slope limit
#define DOWNHILL_CLICK_BRAKE_ASSIST_SPEED_LIMIT 2.78  ///< Downhill click brake assist speed limit
#define NEUTRAL_GEAR_BRAKE_SWICTH_LIMIT -0.3          ///< the speed error limit between neutral gear and brake
#define LON_CONTROLLER_GAIN_SCHEDULER_NUM 6           ///< numbers of points for look-up table

struct LonVehicleParam
{
    float32_t max_acc;                  ///< Maximum acceleration every loop
    float32_t min_acc;                  ///< Minimum acceleration every loop
    float32_t step_lon_acc;             ///< limit lon acceleration every step
    float32_t step_lon_torque;          ///< limit lon torque every step
    float32_t clamp_lon_torque;         ///< limit lon torque output
    float32_t start_lon_torque_stage1;  ///< start lon torque
    float32_t start_lon_torque_stage2;
    float32_t start_acc_threshold;
    float32_t start_acc_error;

    bool_t    enable_lon_torque_control;           ///< Switch for torque control
    bool_t    enable_odometry_slope;               ///< Switch for slope mode
    bool_t    slope_assist_switch;                 ///< Switch for using slope assist 
    bool_t    chassis_acc_switch;                  ///< Switch for using chassis acc
    float32_t torque_acc_threshold;                ///< The threshold between torque command and deceleration command
    float32_t speed_error_threshold;               ///< The threshold between target speed and current speed
    float32_t deceleration_threshold;              ///< The threshold of deceleration
    float32_t min_preview_dist;                    ///< The minimum value of preview distance;
    float32_t max_preview_dist;                    ///< The maximum value of preview distance;
    float32_t accelerate_to_decelerate_threshold;  ///< Threshold value of torque switching to deceleration;
    float32_t decelerate_to_accelerate_threshold;  ///< decelerate to accelerate threshold
    float32_t position_compensation_threshold;     ///< Switching threshold of speed compensation
    float32_t kp_position_control_high_speed;      ///< Speed compensation coefficient of high speed
    float32_t kp_position_control_city;            ///< Speed compensation coefficient of urban area
    float32_t target_distance_threshold;           ///< Upper bound of distance compensation
    float32_t control_exit_time;                   ///<Control the recovery time after exit
    float32_t target_speed_max;                    ///<Maximum speed limit
};

/**
 * @brief longitudinal controller
 */
struct LonController
{
    struct SegmentPid               acc_controller;
    struct SegmentPid               torq_controller;
    struct LonFeedforwardController lon_acc_ff_controller;
    struct LonFeedforwardController lon_torque_ff_controller;
    struct LPCController            lpc_controller;

    struct LonVehicleParam param;

    struct MeanFilter torque_filter;
    struct MeanFilter slope_filter;
    struct MeanFilter target_distance_filter;

    float32_t last_lon_acc;
    float32_t last_lon_torque;
    float32_t last_target_speed;
    float32_t last_target_acc;
    bool_t    flag_former_loop_has_reset;
    bool_t    acceleration_mode_enable;

    struct Point2f preview_time_table[LON_CONTROLLER_GAIN_SCHEDULER_NUM];
    uint32_t       preview_time_table_size;
};

/**
 * @brief Initialize the lon controller with input parameters
 *
 * @param controller Pointer to LonController structure
 * @param acc_pid_param The SegmentPid of acceleration's parameter
 * @param torque_pid_param The SegmentPid of acceleration's parameter
 * @param lon_acc_feedforward_param The feedforward controller parameter
 * @param lon_torque_feedforward_param The feedforward controller parameter
 * @param lon_param The parameter of vehicle in longitudinal
 * @param lpc_param The parameter of lpc controller
 *
 * @return RC_SUCCESS init successfully
 * @return RC_SECTIONAL_PID_CONTROLLER_EMPTY_PARAM_TABLE the input parameter table is empty
 * @return RC_SECTIONAL_PID_CONTROLLER_INVALID_ITEM_ERROR input item's error is less than back item from table
 * @return RC_FAIL init failed
 * @return RC_FEEDFORWARD_CONTROLLER_INVALID_MAXMIN_DEAD_ZONE the dead_zone parameter is invalid
 * @return RC_FEEDFORWARD_CONTROLLER_EMPTY_PARAM_TABLE the input parameters' table is empty
 * @return RC_FEEDFORWARD_CONTROLLER_SAME_ITEM the input parameters' table has the same item
 * @return RC_FEEDFORWARD_CONTROLLER_INVALID_ITEM_SPEED the later item's speed is less than former's
 * @return RC_LON_CONTROLLER_INVALID_PARAM lon_param is invalid
 */
retcode_t lon_controller_init(struct LonController*                       controller,
                              const struct SegmentPidParam*               acc_pid_param,
                              const struct SegmentPidParam*               torque_pid_param,
                              const struct LonFeedforwardControllerParam* lon_acc_feedforward_param,
                              const struct LonFeedforwardControllerParam* lon_torque_feedforward_param,
                              const struct LonVehicleParam*               lon_param,
                              const struct LPCControllerParam*            lpc_param);

/**
 * @brief Check target speed and target acceleration for longitudinal controller
 *
 * @param controller Pointer to LonController structure
 * @param target_speed target speed according to planning path
 * @param target_acc target acceleration according to planning path
 * @param ego_speed current vehicle speed
 *
 * @return RC_SUCCESS
 * @return todo
 */
retcode_t lon_controller_abnormal_input_check(struct LonController* controller,
                                              const float32_t       target_speed,
                                              const float32_t       target_acc,
                                              const float32_t       ego_speed);

/**
 * @brief Calculate the control_command in lonitudinal
 *
 * @param controller Pointer to LonController structure
 * @param path The path
 * @param odometry Pointer to Odometryf
 * @param chassis_state Pointer to ChassisState
 * @param control_command The output parameter
 *
 * @return RC_SUCCESS calculate the control command successfully
 * @return RC_PATH_IS_EMPTY path is empty
 * @return RC_PATH_INVALID_START_INDEX start_idx is too large
 */
retcode_t lon_controller_set_control(struct LonController*         controller,
                                     const struct Pathf*           path,
                                     const struct Odometryf*       odometry,
                                     const struct ChassisState*    chassis_state,
                                     struct ControlCommand*        control_command,
                                     struct LonControlDebugLogger* debug_logger);

/**
 * @brief Reset the lon controller
 *
 * @param controller Pointer to LonController structure
 */
void lon_controller_reset(struct LonController* controller);

/**
 * @brief Calculate lon acc after step limiting
 *
 * @param controller Pointer to LonController structure
 * @param acc acc
 *
 * @return lon acc after step limiting
 */
float32_t lon_controller_acc_step_limit(struct LonController* controller, const float32_t acc);

/**
 * @brief Calculate lon acc after output limiting
 *
 * @param controller Pointer to LonController structure
 * @param acc acc
 *
 * @return lon acc after output limiting
 */
float32_t lon_controller_acc_output_limit(struct LonController* controller, const float32_t acc);

/**
 * @brief Calculate lon torque after step limiting
 *
 * @param controller Pointer to LonController structure
 * @param torque torque
 *
 * @return lon torque after step limiting
 */
float32_t lon_controller_torque_step_limit(struct LonController* controller, const float32_t torque);

/**
 * @brief Calculate lon torque after output limiting
 *
 * @param controller Pointer to LonController structure
 * @param torque torque
 *
 * @return lon torque after output limiting
 */
float32_t lon_controller_torque_output_limit(struct LonController* controller, const float32_t torque);

/**
 * @brief Calculate brake distance.
 *
 * @param car_position vehicle's current position
 * @param plan_path planning path
 *
 * @return brake_distance
 */
float32_t cal_brake_distance(const struct Point3f* car_position, const struct Pathf* plan_path);

/**
 * @brief Get brake distance from path.
 *
 * @param path planning path
 * @param path_brak_dist brake distance on path
 *
 */
void path_get_brk_dist(const struct Pathf* path, float32_t* path_brak_dist);

/**
 * @brief Cal and output the control command when vehicle starts
 *
 * @param controller  Pointer to LonController structure
 * @param ego_speed   vehicle's speed
 * @param speed_error the error between target speed and ego speed
 * @param tar_acc     target acceleration
 * @param ego_acc     vehicle's acceleration
 * @param trq_output  Pointer to torque output
 *
 */
void lon_controller_in_start_status(struct LonController* controller,
                                    const struct Pathf*   path,
                                    float32_t             ego_speed,
                                    float32_t             speed_error,
                                    float32_t             tar_acc,
                                    float32_t             ego_acc,
                                    float32_t*            trq_output);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_CONTROL_LON_CONTROLLER_H_ */
