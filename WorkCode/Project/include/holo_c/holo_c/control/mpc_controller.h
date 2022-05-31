/**
 * @file mpc_controller.h
 * @brief mpc controller
 * @author lijiawen (lijiawen@holomatic.com)
 * @date 2019-08-21
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_CONTROL_MPC_CONTROLLER_H_
#define HOLO_C_CONTROL_MPC_CONTROLLER_H_

#include <holo_c/common/chassis_state.h>
#include <holo_c/common/odometry_float32.h>
#include <holo_c/common/path_float32.h>
#include <holo_c/control/filters/digital_filter.h>
#include <holo_c/control/filters/mean_filter.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point2.h>
#include <holo_c/numerics/cubic_spline.h>
#include <holo_c/numerics/matrix.h>
#include <holo_c/control/debug.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MPC_CONTROLLER_BASIC_STATE_SIZE 4  ///< lateral error, lateral error rate, heading error, heading error rate
#define MPC_CONTROLLER_CONTROL_VARIABLES_NUM 1  ///< numbers of control variables: wheel angle
#define MPC_CONTROLLER_MOVING_HORIZON 10        ///< size of moving horizon
#define MPC_CONTROLLER_GAIN_SCHEDULER_NUM 6     ///< numbers of points during generating spline
#define MPC_STEER_RATIO_TABLE_SIZE 11           ///< numbers of steer ratio table.
#define MPC_CONTROL_WEIGHT_RATIO_MAX_TABLE_SIZE 32  ///< maximum size of MpcController's control weight ratio param table
#define MPC_CONTROL_WEIGHT_RATIO_MAX_DIMENSION 4 ///< maximum dimension of MpcController's control weight ratio param table
#define MPC_CONTROL_WEIGHT_RATIO_TABLE_ROWS   3 ///< rows of MPCControlWeightRatio's table
#define MPC_CONTROL_WEIGHT_RATIO_TABLE_COLS   5 ///< cols of MPCControlWeightRatio's table
#define MPC_CONTROL_WEIGHT_RATIO_PLANE_SIZE   2 ///< size of MPCControlWeightPlane's size

struct MpcControllerParam
{
    float32_t hz;                              ///< control time interval
    float32_t matrix_q_00;
    float32_t matrix_q_11;
    float32_t matrix_q_22;
    float32_t matrix_q_33;
    float32_t matrix_r_00;

    bool_t    flag_enable_gain_scheduler;      ///< flag of enabling gain scheduler
    bool_t    flag_enable_preview_controller;  ///< flag of enabling preview controller 

    /* the following parameters are vehicle physics related. */
    float32_t wheel_base;                         ///< distance between front and rear wheel center
    float32_t mass_fl;
    float32_t mass_fr;
    float32_t mass_rl;
    float32_t mass_rr;
    float32_t max_wheel_angle;
    float32_t cf;                                 ///< corner stiffness; front
    float32_t cr;                                 ///< corner stiffness; rear
    float32_t steer_ratio;                        ///< steer ratio from steer wheel angel to front wheel angle
    float32_t mass;                               ///< mass of the vehicle
    float32_t lf;                                 ///< distance from front wheel center to COM
    float32_t lr;                                 ///< distance from rear wheel center to COM
    float32_t iz;                                 ///< rotational inertia

    float32_t abnormal_heading_error;       ///< parameters for mpc abnormal check: heading error
    float32_t abnormal_lateral_error;       ///< paramsters for mpc abnormal check: lateral error
    float32_t abnormal_step_heading_error;  ///< paramsters for mpc abnormal check: step heading error
    float32_t abnormal_step_lateral_error;  ///< paramsters for mpc abnormal check: step lateral error
    float32_t minimum_speed_protection;

    uint32_t mean_filter_window_size;         ///< mean filter window size
    uint32_t feedforward_filter_window_size;  ///< window size of feedforward's mean filter

    float32_t step_angle;                ///< safety parameters
    float32_t steer_wheel_angle_bias;

    float32_t path_segment_base_length;  ///< parameters for the base length of preview control

    struct Point2f  steer_ratio_table[MPC_STEER_RATIO_TABLE_SIZE];
    uint32_t        steer_ratio_table_size;

    struct Point2f lat_err_gain_scheduler_point_list[MPC_CONTROLLER_GAIN_SCHEDULER_NUM];
    uint32_t       lat_err_gain_scheduler_point_list_size;

    struct Point2f lat_err_gain_scheduler_by_curvature_point_list[MPC_CONTROLLER_GAIN_SCHEDULER_NUM];
    uint32_t       lat_err_gain_scheduler_by_curvature_point_list_size;

    struct Point2f heading_err_gain_scheduler_point_list[MPC_CONTROLLER_GAIN_SCHEDULER_NUM];
    uint32_t       heading_err_gain_scheduler_point_list_size;

    struct Point2f heading_err_gain_scheduler_by_curvature_point_list[MPC_CONTROLLER_GAIN_SCHEDULER_NUM];
    uint32_t       heading_err_gain_scheduler_by_curvature_point_list_size;

    struct
    {
        uint32_t  table_size;     ///< size of MPCControlWeightRatio's table
        uint32_t  dimension;      ///< dimension of MPCControlWeightRatio params
        uint32_t  rows;           ///< rows of MPCControlWeightRatio's table
        uint32_t  cols;           ///< cols of MPCControlWeightRatio's table
        struct
        {
            float32_t plane[MPC_CONTROL_WEIGHT_RATIO_MAX_DIMENSION];
            float32_t ratio;
        } table[MPC_CONTROL_WEIGHT_RATIO_MAX_TABLE_SIZE];
        struct Point3f table_2D[MPC_CONTROL_WEIGHT_RATIO_TABLE_ROWS * MPC_CONTROL_WEIGHT_RATIO_TABLE_COLS];
    }MPCControlWeightRatioTable;

    struct Point2f path_segment_velocity_ratio_table[MPC_CONTROLLER_GAIN_SCHEDULER_NUM];
    uint32_t       path_segment_velocity_ratio_table_size;

    struct Point2f path_segment_curvature_ratio_table[MPC_CONTROLLER_GAIN_SCHEDULER_NUM];
    uint32_t       path_segment_curvature_ratio_table_size;
};

struct MpcController
{
    bool_t    flag_former_loop_has_reset;      ///< flag to show whether former loop has reset*/
    float32_t curvature;                       ///< save closest point curvature value
    float32_t target_angular_speed;            ///< target angular speed

    float32_t current_wheel_angle;       ///< parameters for saving current wheel angle
    float32_t last_heading;              ///< parameters for saving last step heading info
    float32_t last_curvature;            ///< parameters for saving last step curvature info
    float32_t last_target_speed;         ///< parameters for saving last step target speed info
    float32_t last_target_theta;         ///< parameters for saving last step target theta info
    float32_t last_wheel_angle;          ///< parameters for saving last step output angle info

    struct MpcControllerParam param;

    float32_t last_heading_error;
    float32_t last_lateral_error;

    struct Matrixf matrix_a;  ///< vehicle system state matrix A
    float32_t matrix_a_buffer[MATRIXF_MIN_BUF_SIZE(MPC_CONTROLLER_BASIC_STATE_SIZE, MPC_CONTROLLER_BASIC_STATE_SIZE)];
    struct Matrixf matrix_ad;  ///< vehicle system state matrix A of discrete time
    float32_t matrix_ad_buffer[MATRIXF_MIN_BUF_SIZE(MPC_CONTROLLER_BASIC_STATE_SIZE, MPC_CONTROLLER_BASIC_STATE_SIZE)];

    struct Matrixf matrix_b;  ///< control matrix
    float32_t
        matrix_b_buffer[MATRIXF_MIN_BUF_SIZE(MPC_CONTROLLER_BASIC_STATE_SIZE, MPC_CONTROLLER_CONTROL_VARIABLES_NUM)];
    struct Matrixf matrix_bd;  ///< control matrix of discrete time
    float32_t
        matrix_bd_buffer[MATRIXF_MIN_BUF_SIZE(MPC_CONTROLLER_BASIC_STATE_SIZE, MPC_CONTROLLER_CONTROL_VARIABLES_NUM)];

    struct Matrixf matrix_c;  ///< offset matrix
    float32_t
        matrix_c_buffer[MATRIXF_MIN_BUF_SIZE(MPC_CONTROLLER_BASIC_STATE_SIZE, MPC_CONTROLLER_CONTROL_VARIABLES_NUM)];
    struct Matrixf matrix_cd;  ///< offset matrix of discrete time
    float32_t
        matrix_cd_buffer[MATRIXF_MIN_BUF_SIZE(MPC_CONTROLLER_BASIC_STATE_SIZE, MPC_CONTROLLER_CONTROL_VARIABLES_NUM)];

    struct Matrixf matrix_r;  ///< control authority weighting matrix
    float32_t      matrix_r_buffer[MATRIXF_MIN_BUF_SIZE(MPC_CONTROLLER_CONTROL_VARIABLES_NUM,
                                                   MPC_CONTROLLER_CONTROL_VARIABLES_NUM)];
    struct Matrixf matrix_r_updated;  ///< updated control authority weighting matrix
    float32_t      matrix_r_updated_buffer[MATRIXF_MIN_BUF_SIZE(MPC_CONTROLLER_CONTROL_VARIABLES_NUM,
                                                           MPC_CONTROLLER_CONTROL_VARIABLES_NUM)];
    struct Matrixf matrix_q;  ///< state weighting matrix
    float32_t matrix_q_buffer[MATRIXF_MIN_BUF_SIZE(MPC_CONTROLLER_BASIC_STATE_SIZE, MPC_CONTROLLER_BASIC_STATE_SIZE)];
    struct Matrixf matrix_q_updated;  ///< updated state weighting matrix
    float32_t
        matrix_q_updated_buffer[MATRIXF_MIN_BUF_SIZE(MPC_CONTROLLER_BASIC_STATE_SIZE, MPC_CONTROLLER_BASIC_STATE_SIZE)];
    struct Matrixf matrix_a_coeff;  ///< vehicle state matrix coefficients
    float32_t
        matrix_a_coeff_buffer[MATRIXF_MIN_BUF_SIZE(MPC_CONTROLLER_BASIC_STATE_SIZE, MPC_CONTROLLER_BASIC_STATE_SIZE)];
    struct Matrixf matrix_state;  ///< 4 by 1 matrix; state matrix
    float32_t      matrix_state_buffer[MATRIXF_MIN_BUF_SIZE(MPC_CONTROLLER_BASIC_STATE_SIZE,
                                                       MPC_CONTROLLER_CONTROL_VARIABLES_NUM)];

    struct MeanFilter lateral_error_filter;       ///< MeanFilter for lateral_error_filter;
    struct MeanFilter heading_error_filter;       ///< MeanFilter for heading_error_filter;
    struct MeanFilter heading_error_rate_filter;  ///< MeanFilter for heading_error_rate_filter;
    struct MeanFilter feed_forward_k_filter;      ///< MeanFilter for curvature
    struct MeanFilter centerforce_coef_filter;    ///< MeanFilter for centerforce k coeffiect
};

/**
 * @brief       Initialize the mpc controller
 *
 * @param       controller The pointer of MpcController.
 * @param       param The mpc's parameters.
 *
 * @return
 * @return      RC_SUCCESS
 */
retcode_t mpc_controller_init(struct MpcController* controller, const struct MpcControllerParam* param);

/**
 * @brief       compute output wheel angle
 *
 * @param       controller The pointer of MpcController.
 * @param       chassis_state
 * @param       odometry
 * @param       planning_path
 * @param       output
 *
 * @return      RC_MPC_CONTROLLER_SOLVE_FAILED
 * @return      RC_SUCCESS
 */
retcode_t mpc_controller_set_control(struct MpcController*         controller,
                                     const struct ChassisState*    chassis_state,
                                     const struct Odometryf*       odometry,
                                     const struct Pathf*           planning_path,
                                     float32_t*                    output,
                                     struct MpcControlDebugLogger* debug_logger);

/**
 * @brief       init the mpc control weight table by default
 * @param       param the mpc control weight ratio table (pointer)
 * 
 * @return      the  calculated control weight rate.
 */
void mpc_control_weight_ratio_table_init_default(struct MpcControllerParam* param);

/**
 * @brief       reset the mpc controller
 *
 * @param       controller The pointer of MpcController.
 */
void mpc_controller_reset(struct MpcController* controller);

#ifdef __cplusplus
}
#endif

#endif
