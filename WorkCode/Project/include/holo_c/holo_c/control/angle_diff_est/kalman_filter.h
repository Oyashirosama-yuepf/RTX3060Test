/**
 * @file kinematic_model.h
 * @brief kinematic_model
 * @author liuhuan (liuhuan@holomatic.com)
 * @date 2021.9.30
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

#include <holo_c/common/chassis_state.h>
#include <holo_c/common/odometry_float32.h>
#include <holo_c/control/angle_diff_est/kinematic_model.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#define counter_angle_diff_stop_times 500
#define angle_diff_vec_max_size 7

struct AngleDiffParam
{
    uint32_t  counter_angle_diff;                       ///< counter the times of runnin kalman filter
    float32_t angle_diff_est;                           ///< the estmated value of angle_diff
    float32_t angle_diff_vec[angle_diff_vec_max_size];  ///< the array for saving the estmated value at stop times
    uint32_t  angle_diff_vec_cur_size;                  ///< the cur number of  the arra
    bool_t    GET_ANGLE_DIFF_SUCCESS_FLAG; ///<finished flag of est angle diff
};

struct KalmanFilter
{
    struct Matrixf Q_init;  ///< process noise matrix at the first step
    float32_t Q_init_buffer[MATRIXF_MIN_BUF_SIZE(KINEMATIC_MODEL_BASIC_STATE_SIZE, KINEMATIC_MODEL_BASIC_STATE_SIZE)];
    struct Matrixf R_init;  ///< measurement noise matrix at the first step
    float32_t      R_init_buffer[MATRIXF_MIN_BUF_SIZE(KINEMATIC_MODEL_MEASURED_VARIBLES_NUM,
                                                 KINEMATIC_MODEL_MEASURED_VARIBLES_NUM)];
    struct Matrixf Q;  ///< time varying noise matrix when running kalman filter
    float32_t      Q_buffer[MATRIXF_MIN_BUF_SIZE(KINEMATIC_MODEL_BASIC_STATE_SIZE, KINEMATIC_MODEL_BASIC_STATE_SIZE)];
    struct Matrixf A;  /// discrete state matrix A
    float32_t      A_buffer[MATRIXF_MIN_BUF_SIZE(KINEMATIC_MODEL_BASIC_STATE_SIZE, KINEMATIC_MODEL_BASIC_STATE_SIZE)];

    struct Vectorf X_pre;  ///<  predicted value of vector status
    float32_t      X_pre_buffer[VECTORF_MIN_BUF_SIZE(KINEMATIC_MODEL_BASIC_STATE_SIZE)];
    struct Matrixf P_pre;  ///< predicted covariance matrix
    float32_t P_pre_buffer[MATRIXF_MIN_BUF_SIZE(KINEMATIC_MODEL_BASIC_STATE_SIZE, KINEMATIC_MODEL_BASIC_STATE_SIZE)];
    struct Vectorf Y_meas;  ///< measured varibles vector
    float32_t      Y_meas_buffer[VECTORF_MIN_BUF_SIZE(KINEMATIC_MODEL_MEASURED_VARIBLES_NUM)];
    struct Vectorf X_upd_last;  ///< last updatd value of vector status
    float32_t      X_upd_last_buffer[VECTORF_MIN_BUF_SIZE(KINEMATIC_MODEL_BASIC_STATE_SIZE)];
    struct Vectorf X_upd;  ///< cur updatd value of vector status
    float32_t      X_upd_buffer[VECTORF_MIN_BUF_SIZE(KINEMATIC_MODEL_BASIC_STATE_SIZE)];
    struct Matrixf P_upd_last;  ///< last updatd value of  convariance matrix
    float32_t
        P_upd_last_buffer[MATRIXF_MIN_BUF_SIZE(KINEMATIC_MODEL_BASIC_STATE_SIZE, KINEMATIC_MODEL_BASIC_STATE_SIZE)];
    struct Matrixf P_upd;  ///< cur updatd value of  convariance matrix
    float32_t P_upd_buffer[MATRIXF_MIN_BUF_SIZE(KINEMATIC_MODEL_BASIC_STATE_SIZE, KINEMATIC_MODEL_BASIC_STATE_SIZE)];
    struct Vectorf model_input;  ///< control varibles vector of  kinmatic model
    float32_t      model_input_buffer[VECTORF_MIN_BUF_SIZE(KINEMATIC_MODEL_CONTROL_VARIABLES_NUM)];
    struct Matrixf K;  ///< matrix gain of kalman filter
    float32_t K_buffer[MATRIXF_MIN_BUF_SIZE(KINEMATIC_MODEL_BASIC_STATE_SIZE, KINEMATIC_MODEL_MEASURED_VARIBLES_NUM)];

    float32_t roll_angle;
    float32_t pitch_angle;
    float32_t yaw_angle;

    bool_t                     INIT_KALMAN_SUCCESS;     ///< flag  for  judging init first step status
    bool_t                     Get_ANGLE_DIFF_SUCCESS;  ///< flag  for  judging the final estimation value
    struct KinematicModelParam kin_model_param;
    struct KinematicModel      kin_model;
};

/**
 * @brief       Init kalman filter
 *
 * @param       kal_filter The pointer of KalmanFilter.
 * @param       angle_diff_param The parameters of AngleDiff.
 *
 * @return      RC_SUCCESS
 */
retcode_t kalman_filter_init(struct KalmanFilter* kal_filter, struct AngleDiffParam* angle_diff_param);

/**
 * @brief       Get input and measurement information
 *
 * @param       odometry
 * @param       chassis_state
 * @param       kal_filter
 * @param       x_offset_in Compension the offset for x_pos
 * @param       y_offset_in Compension the offset for y_pos
 *
 * @return      RC_SUCCESS
 */
retcode_t get_kalman_input_and_meas_info(const struct Odometryf*    odometry,
                                         const struct ChassisState* chassis_state,
                                         struct KalmanFilter*       kal_filter,
                                         int32_t                    x_offset_in,
                                         int32_t                    y_offset_in);

/**
 * @brief       Init the first  step in kalman filter
 *
 * @param       kal_filter The pointer of KalmanFilter.
 * @param       mpc_ctrl_param The parameters of mpc controller
 *
 * @return      RC_SUCCESS
 */
retcode_t kalman_filter_init_first_step(struct KalmanFilter*             kal_filter,
                                        const struct MpcControllerParam* mpc_ctrl_param);

/**
 * @brief       Run the next steps in kalman filter
 *
 * @param       kal_filter The pointer of KalmanFilter.
 *
 * @return      RC_SUCCESS
 */
retcode_t kalman_filter_run_next_steps(struct KalmanFilter* kal_filter);

/**
 * @brief       Get the  weighted value of all estimated value
 *
 * @param       angle_diff_vec_input The pointer of the array
 *
 * @return      RC_SUCCESS
 */
float32_t get_weighted_average(float32_t angle_diff_vec_input[angle_diff_vec_max_size]);

/**
 * @brief       Reset kalman filter
 *
 * @param       kal_filter The pointer of KalmanFilter
 *
 * @return      RC_SUCCESS
 */
void kalman_filter_reset(struct KalmanFilter* kal_filter);

#ifdef __cplusplus
}
#endif

#endif  // KALMAN_FILTER_H
