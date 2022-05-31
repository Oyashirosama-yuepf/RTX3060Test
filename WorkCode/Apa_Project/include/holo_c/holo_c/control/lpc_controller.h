/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lpc_controller.h
 * @brief the header of the longitudinal lpc controller, C version
 * @author zhaoyifan(zhaoyifan@holomatic.com), liuxiao (liuxiao@holomatic.com)
 * @date 2020-10-10
 */

#ifndef HOLO_C_CONTROL_LPC_CONTROLLER_H_
#define HOLO_C_CONTROL_LPC_CONTROLLER_H_

#include <holo_c/common/chassis_state.h>
#include <holo_c/common/control_command.h>
#include <holo_c/common/dequeue.h>
#include <holo_c/common/odometry_float32.h>
#include <holo_c/common/path_float32.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point2.h>
#include <holo_c/numerics/cubic_spline.h>
#include <holo_c/numerics/matrix.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif

#define LPC_CONTROLLER_GAIN_SCHEDULER_MAX_NUM 10   ///<numbers of gain scheduler size
#define LPC_CONTROLLER_AUG_MAX_NUM 30              ///<size of augmentation matirix

struct LPCControllerParam
{
    int32_t   pressurize_delay_;   ///<pressurize delay
    int32_t   pressurize_counter_; ///<counter for caculate delay distance
    float32_t safty_dist_;         ///<distance to exit stop at point
    float32_t weight_a_;           ///< weight of brake distance
    float32_t weight_b_;           ///<weight of acceleration difference
    float32_t weight_c_;           ///<weight of acceleration changing trend
    float32_t limit_acc_;          ///< limit of acceleration command
    uint32_t  acc_quantity_;       ///<quantity of acceleration command in scheduler
    uint32_t  A_size_;             ///< size of matrix A
    float32_t emergency_dist_;     ///< emergency brake distance

    struct Point2f  lpc_gain_scheduler_point_list[LPC_CONTROLLER_GAIN_SCHEDULER_MAX_NUM];
    uint32_t         lpc_gain_scheduler_point_list_size;
};

struct LPCController
{
    bool_t release_brake_;          ///<switch of release brake
    bool_t enter_braking_;          ///<brake status
    struct LPCControllerParam param;
    struct Matrixf  Matrix_A_;         ///<acc_quantity_ * (3*acc_quantity_) dimention matrix filled by jerk
    struct Matrixf  Matrix_B_;         ///<(3*acc_quantity_) * (3*acc_quantity_) dimention matrix filled by cur_speed and cur_acc
    struct Matrixf  Matrix_C_;         ///<(3*acc_quantity_) * acc_quantity_ dimention filled by delta_acc
    struct Matrixf  Matrix_d_;         ///<acc_quantity_ * 1 dimention matrix of acceleration command in scheduler
    struct Matrixf  Matrix_pre_dist_;  ///<acc_quantity_ * 1 dimention matrix of predictive brake distance
    struct Matrixf  Matrix_cost_;      ///< acc_quantity_ * 1 dimention matrix of cost

    float32_t  Matrix_A_buffer[MATRIXF_MIN_BUF_SIZE(LPC_CONTROLLER_GAIN_SCHEDULER_MAX_NUM, LPC_CONTROLLER_AUG_MAX_NUM)];
    float32_t  Matrix_B_buffer[MATRIXF_MIN_BUF_SIZE(LPC_CONTROLLER_AUG_MAX_NUM, LPC_CONTROLLER_AUG_MAX_NUM)];
    float32_t  Matrix_d_buffer[MATRIXF_MIN_BUF_SIZE(LPC_CONTROLLER_GAIN_SCHEDULER_MAX_NUM, 1)];   
    float32_t  Matrix_pre_dist_buffer[MATRIXF_MIN_BUF_SIZE(LPC_CONTROLLER_GAIN_SCHEDULER_MAX_NUM, 1)];
    float32_t  Matrix_cost_buffer[MATRIXF_MIN_BUF_SIZE(LPC_CONTROLLER_GAIN_SCHEDULER_MAX_NUM, 1)];         
    float32_t 
               Matrix_C_temp_buffer[MATRIXF_MIN_BUF_SIZE(LPC_CONTROLLER_AUG_MAX_NUM, LPC_CONTROLLER_GAIN_SCHEDULER_MAX_NUM)];    
};

/**
  * @brief  Initialize the lpc controller
  * 
  * @param  controller the lpc controller
  * @param  param the lpc's parameters
  * 
  * @return RC_SUCCESS init successfully
  * @return RC_FEEDFORWARD_CONTROLLER_EMPTY_PARAM_TABLE the input parameters' table is empty
  * @return RC_FEEDFORWARD_CONTROLLER_INVALID_MAXMIN_DEAD_ZONE the input parameters' table 
  *         size is bigger than LPC_CONTROLLER_GAIN_SCHEDULER_MAX_NUM
  */
retcode_t   lpc_controller_init(struct LPCController* controller, const struct LPCControllerParam* lpc_param);

/**
  * @brief  calculate acceleration command by lpc controller
  * 
  * @param  controller the lpc controller
  * @param  brake_dist brake distance
  * @param  curr_speed current speed
  * @param  curr_acc   current acceleration
  * @param  acc_cmd    accelration command
  * 
  * @return RC_SUCCESS enter the lpc control mode
  * @return RC_FAIL    can't enter the lpc control mode
  */
retcode_t  lpc_controller_set_control(struct LPCController* controller, 
                                     const  float32_t  brake_dist, 
                                     const  float32_t  curr_speed, 
                                     const  float32_t  curr_acc, 
                                     float32_t* acc_cmd);

/**
  * @brief determine whether enter precise brake 
  * 
  * @param enter_dist enter distance
  * @param brake_dist brake distance
  * @param curr_speed current speed
  */
void    UpdateEnterBraking(struct LPCController* controller, const float32_t enter_dist, const float32_t brake_dist, const float32_t curr_speed);

/**
  * @brief calculate predictive distance matrix
  * @param curr_acc current acceleration
  * @param curr_speed current speed
  */
void    CalcPreDistance(struct LPCController* controller, const float32_t curr_speed, const float32_t curr_acc);

/**
  * @brief  calculate acceleration command
  * @param  brake_dist brake distance
  * 
  * @return acceleration command
  */
float32_t CalcAccCmd(struct LPCController* controller, const float32_t brake_dist);

/**
  * @brief find the minimum coefficient of matrix
  * @param matrix matrix
  * @param min_row the row of minimum coefficient
  * @param min_col the col of minimum coefficient
  * @param min_value the value of minimum coefficient
  */
void find_matrix_minCoeff(struct Matrixf* matrix, uint32_t* min_row, uint32_t* min_col, float32_t* min_value);

/**
  * @brief find the maximum coefficient of matrix
  * @param matrix matrix
  * @param max_row the row of maximum coefficient
  * @param max_col the col of maximum coefficient
  * @param max_value the value of maximum coefficient
  */
void find_matrix_maxCoeff(struct Matrixf* matrix, uint32_t* max_row, uint32_t* max_col, float32_t* max_value);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_CONTROL_LPC_CONTROLLER_H_ */
