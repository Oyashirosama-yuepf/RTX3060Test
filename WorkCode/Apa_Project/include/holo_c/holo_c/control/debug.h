#ifndef HOLO_C_CONTROL_DEBUG_H_
#define HOLO_C_CONTROL_DEBUG_H_

#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct PIDControlDebugLogger
{
    float32_t error;
    float32_t error_rate;
    float32_t kp;
    float32_t ki;
    float32_t kd;
    float32_t output_kp;
    float32_t output_ki;
    float32_t output_kd;
};

struct MpcControlDebugLogger
{
    float32_t odometry_x;
    float32_t odometry_y;
    float32_t odometry_theta;
    float32_t target_x;
    float32_t target_y;
    float32_t target_theta;

    float32_t lateral_error;
    float32_t lateral_error_rate;
    float32_t heading_error;
    float32_t heading_error_rate;

    float32_t vx;
    float32_t vy;
    float32_t target_curvature;
    float32_t target_angular_speed;

    float32_t matrix_q1_updated;
    float32_t matrix_q2_updated;
    float32_t matrix_q3_updated;
    float32_t matrix_q4_updated;
    float32_t matrix_r_updated;
    float32_t mpc_result;
};

struct LatFeedforwardControlDebugLogger
{
    float32_t target_curvature;
    float32_t arkermann_coef;
    float32_t kinetic_coef;
    float32_t lat_ff_result;
};

struct LatDegreeControlDebugLogger
{
    float32_t lat_ff_output;
    float32_t lat_fb_output;
    float32_t lat_bias_output;
    float32_t lat_degree_output;
    float32_t lat_exp_angle;
    float32_t lat_cur_angle;
};

struct LatTorqueControlDebugLogger
{
    float32_t                    exp_angle;
    float32_t                    cur_angle;
    float32_t                    damping_torque;
    float32_t                    torque_output;
    float32_t                    ego_speed;
    float32_t                    torque_ff;
    struct PIDControlDebugLogger pid_logger;
};

struct LonControlDebugLogger
{
    float32_t                    acc_output;
    float32_t                    acc_launch;
    float32_t                    acc_feedforward_output;
    float32_t                    acc_feedback_output;
    float32_t                    torque_output;
    float32_t                    time_matched_speed;
    float32_t                    target_speed;
    float32_t                    ego_speed;
    float32_t                    time_matched_acc;
    float32_t                    target_acc;
    float32_t                    ego_acc;
    float32_t                    target_distance;
    float32_t                    torque_output_feedback;
    float32_t                    torque_output_feedforward;
    float32_t                    acc_assist;
    float32_t                    slope_ave;
    float32_t                    acceleration_mode_enable;
    float32_t                    target_speed_compensated;
    struct PIDControlDebugLogger acc_pid_logger;
    struct PIDControlDebugLogger torque_pid_logger;
};

struct ControlStatusDebugLogger
{
    uint32_t path_size;
    uint32_t path_state;
    uint32_t path_validvalue;
    uint32_t run_control_status;
    uint32_t check_control_mode;
};

struct LatControlDebugLogger
{
    struct MpcControlDebugLogger            mpc_control_debug_log;
    struct LatFeedforwardControlDebugLogger lat_ff_debug_log;
    struct LatDegreeControlDebugLogger      lat_degree_debug_log;
    struct LatTorqueControlDebugLogger      lat_torque_debug_log;
};

struct DebugLogger
{
    struct LatControlDebugLogger    lat_control_debug_log;
    struct LonControlDebugLogger    lon_control_debug_log;
    struct ControlStatusDebugLogger control_status_debug;
};

void pid_logger_init(struct PIDControlDebugLogger* pid_controller_logger);

void control_debug_log_init(struct DebugLogger* control_debug_log);

#ifdef __cplusplus
}
#endif

#endif