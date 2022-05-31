/**
 * @file kinematic_model.h
 * @brief kinematic_model
 * @author liuhuan (liuhuan@holomatic.com)
 * @date 2021.9.30
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef KINEMATIC_MODEL_H
#define KINEMATIC_MODEL_H

#include <holo_c/control/mpc_controller.h>
#include <holo_c/core/types.h>
#include <holo_c/numerics/matrix.h>

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#define KINEMATIC_MODEL_BASIC_STATE_SIZE 4       ///< state varibles:x_pos, y_pos, phi, angle_diff
#define KINEMATIC_MODEL_CONTROL_VARIABLES_NUM 2  ///< control varibles:linear_velocity,steering_wheel_angle
#define KINEMATIC_MODEL_MEASURED_VARIBLES_NUM 3  ///< measured varibles:x_pos, y_pos, phi

struct KinematicModelParam
{
    float32_t dt;  ///< period of calculating
    float32_t lf;  ///< distance from front wheel center to COM
    float32_t lr;  ///< distance from rear wheel center to COM
    float32_t k1;  /// < coefficient : k1  = lf / (lf + lr);
    float32_t steer_ratio;
};

struct KinematicModel
{
    float32_t x_pos;
    float32_t y_pos;
    float32_t phi;  ///< yaw angle
    float32_t angle_diff;
    float32_t x_pos_dot;
    float32_t y_pos_dot;
    float32_t phi_dot;  ///< yaw angle rates
    float32_t angle_diff_dot;
    float32_t beta;  ///< vehicle side slip angle;
    float32_t beta_dot_angle_diff;

    struct Vectorf X_status;  ///< state vector
    float32_t      X_status_buffer[VECTORF_MIN_BUF_SIZE(KINEMATIC_MODEL_BASIC_STATE_SIZE)];
    struct Vectorf X_status_dot;  ///< derivative of state vector
    float32_t      X_status_dot_buffer[VECTORF_MIN_BUF_SIZE(KINEMATIC_MODEL_BASIC_STATE_SIZE)];
    struct Matrixf H_mea;  /// measured matrix
    float32_t
        H_mea_buffer[MATRIXF_MIN_BUF_SIZE(KINEMATIC_MODEL_MEASURED_VARIBLES_NUM, KINEMATIC_MODEL_BASIC_STATE_SIZE)];
    struct Matrixf A_discrete;
    float32_t
        A_discrete_buffer[MATRIXF_MIN_BUF_SIZE(KINEMATIC_MODEL_BASIC_STATE_SIZE, KINEMATIC_MODEL_BASIC_STATE_SIZE)];
    struct Matrixf Q_discrete;
    float32_t
        Q_discrete_buffer[MATRIXF_MIN_BUF_SIZE(KINEMATIC_MODEL_BASIC_STATE_SIZE, KINEMATIC_MODEL_BASIC_STATE_SIZE)];
};

/**
 * @brief       Initialize the parameters of kinematic model
 *
 * @param       kin_model_param Parameters of kinmatic model.
 * @param       mpc_ctrl_param Parameters of mpc controller.
 *
 * @return      RC_SUCCESS
 */
retcode_t kinematic_model_param_init(struct KinematicModelParam*      kin_model_param,
                                     const struct MpcControllerParam* mpc_ctrl_param);

/**
 * @brief       Initialize the kinematic model
 *
 * @param       kin_model The pointer of KinematicModel.
 *
 * @return      RC_SUCCESS
 */
retcode_t kinematic_model_init(struct KinematicModel* kin_model);

/**
 * @brief       Get the kinematic model at each time point
 *
 * @param       steering_angle the angle of steering wheel, but not the tire.
 * @param       linear_velocity The  velocity of COM.
 * @param       kin_model The pointer of kinmatic model.
 * @param       kin_model_param The parameters of kinematic model.
 *
 * @return      RC_SUCCESS
 */
retcode_t get_kinematic_model(float32_t                   steering_angle,
                              float32_t                   linear_velocity,
                              struct KinematicModel*      kin_model,
                              struct KinematicModelParam* kin_model_param);

/**
 * @brief       Discrete and linearize kinematic model
 *
 * @param       steering_angle
 * @param       linear_velocity
 * @param       kin_model The pointer of kinmatic model.
 * @param       kin_model_param The parameters of kinematic model.
 *
 * @return      State Matrix A
 */
void discrete_and_linearize_kinematic_model(float32_t                   steering_angle,
                                            float32_t                   linear_velocity,
                                            struct KinematicModel*      kin_model,
                                            struct KinematicModelParam* kin_model_param);

/**
 * @brief       Get process noise matrix
 *
 * @param       linear_velocity
 * @param       kin_model The pointer of kinmatic model.
 * @param       kin_model_param The parameters of kinematic model.
 *
 * @return      Process noise  matrix Q
 */
void discrete_process_noise_model(float32_t                   linearVelocity,
                                  struct KinematicModel*      kin_model,
                                  struct KinematicModelParam* kin_model_param);

#ifdef __cplusplus
}
#endif

#endif  // KINEMATIC_MODEL_H
