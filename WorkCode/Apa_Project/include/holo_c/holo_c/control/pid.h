/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pid.h
 * @brief the header of pid
 * @author sunlei(sunlei@holomatic.com)
 * @date 2020-09-04
 */

#ifndef HOLO_C_CONTROL_PID_H_
#define HOLO_C_CONTROL_PID_H_

#include <holo_c/control/debug.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct PidParam
{
    float32_t kp;                             ///< the proportion cofficient
    float32_t ki;                             ///< the integral cofficient
    float32_t kd;                             ///< the differential cofficent
    float32_t max_integral;                   ///< represents the maximum integral
    float32_t min_integral;                   ///< represents the minmum intergal
    float32_t max_output;                     ///< represents the maximum output
    float32_t min_output;                     ///< represents the minmum output
    float32_t integral_separation_threshold;  ///< represents the integral separation threshold 
    float32_t kp_max_output;                  ///< represents the kp maximum output
    float32_t kp_min_output;                  ///< represents the kp minmum output
};

struct Pid
{
    float32_t integral;    ///< represents the value of ki*sum(error)
    float32_t prev_error;  ///< represents the last error which is used to simplified the code
};

/**
 * @brief Initialize pid parameters by default
 *
 * @param pid Pointer to PidParam structure
 */
void pid_param_init_default(struct PidParam* param);

/**
 * @brief Initialize pid parameters
 *
 * @param param Pointer to PidParam structure.
 * @param kp Proportion cofficient.
 * @param ki Integral cofficent.
 * @param kd Differential cofficent.
 * @param max_integral Maximum integral.
 * @param min_integral Minimum intergal.
 * @param max_output Maximum output.
 * @param min_output Minimum output.
 * @param integral_separation_threshold integral separation threshold.
 * @param kp_max_output kp_max_output.
 * @param kp_min_output kp_min_output.

 * 
 * @return RC_SUCCESS init successfully
 * @return RC_PIDCONTROLLER_INVALID_PARAMETER max_integral < min_integral
 */
retcode_t pid_param_init(struct PidParam* param,
                         float32_t        kp,
                         float32_t        ki,
                         float32_t        kd,
                         float32_t        max_integral,
                         float32_t        min_integral,
                         float32_t        max_output,
                         float32_t        min_output,
                         float32_t        integral_separation_threshold,
                         float32_t        kp_max_output,
                         float32_t        kp_min_output);

/**
 * @brief Initialize pid by default parameters
 *
 * @param pid Pointer to Pid structure
 */
void pid_init_default(struct Pid* pid);

/**
 * @brief Calculate the pid output based on input error
 *
 * @param pid Pointer to Pid structure.
 * @param param Pointer to PidParam structure.
 * @param error The input error.
 *
 * @return the pid output
 */
float32_t
pid_set_control(struct Pid* pid, struct PidParam* param, float32_t error, struct PIDControlDebugLogger* debug_logger);

/**
 * @brief Reset the pid state, make previous error and integral as zero
 *
 * @param pid Pointer to Pid structure.
 */
void pid_reset(struct Pid* pid);

/**
 * @brief Reset the pid state, make integral as zero
 *
 * @param pid Pointer to Pid structure.
 */
void pid_reset_integral(struct Pid* pid);

/**
 * @brief Set the pid parameters
 *
 * @param param Pointer to PidParam structure.
 * @param input_kp The input kp.
 */
void pid_param_set_kp(struct PidParam* param, float32_t input_kp);

/**
 * @brief Set the pid parameters
 *
 * @param param Pointer to PidParam structure.
 * @param input_ki The input ki.
 */
void pid_param_set_ki(struct PidParam* param, float32_t input_ki);

/**
 * @brief Set the pid parameters
 *
 * @param param Pointer to PidParam structure.
 * @param input_kd The input kd.
 */
void pid_param_set_kd(struct PidParam* param, float32_t input_kd);

/**
 * @brief Set the pid parameters
 *
 * @param param Pointer to PidParam structure.
 * @param input_max_integral The input max_integral.
 */
void pid_param_set_max_integral(struct PidParam* param, float32_t input_max_integral);

/**
 * @brief Set the pid parameters
 *
 * @param param Pointer to PidParam structure.
 * @param input_min_integral The input min_integral.
 */
void pid_param_set_min_integral(struct PidParam* param, float32_t input_min_integral);

/**
 * @brief Set the pid parameters
 *
 * @param param Pointer to PidParam structure.
 * @param input_integral_separation_threshold The input integral_separation_threshold.
 */
void pid_param_set_integral_separation_threshold(struct PidParam* param, float32_t input_integral_separation_threshold);

/**
 * @brief Set the pid parameters
 *
 * @param param Pointer to PidParam structure.
 * @param kp_max_output The kp_max_output.
 */
void pid_param_set_kp_max_output(struct PidParam* param, float32_t kp_max_output);

/**
 * @brief Set the pid parameters
 *
 * @param param Pointer to PidParam structure.
 * @param kp_min_output The kp_min_output.
 */
void pid_param_set_kp_min_output(struct PidParam* param, float32_t kp_min_output);

/**
 * @brief Set the pid parameters
 *
 * @param param Pointer to PidParam structure.
 * @param max_output The max_output.
 */
void pid_param_set_max_output(struct PidParam* param, float32_t max_output);

/**
 * @brief Set the pid parameters
 *
 * @param param Pointer to PidParam structure.
 * @param min_output The min_output.
 */
void pid_param_set_min_output(struct PidParam* param, float32_t min_output);

/**
 * @brief Set the pid state
 *
 * @param pid Pointer to Pid structure.
 * @param input_integral The input integral.
 */
void pid_set_integral(struct Pid* pid, float32_t input_integral);

/**
 * @brief Set the pid state
 *
 * @param pid Pointer to Pid structure.
 * @param input_prev_error The input prev_error.
 */
void pid_set_prev_error(struct Pid* pid, float32_t input_prev_error);

#ifdef __cplusplus
}
#endif

#endif
