/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file segment_pid.h
 * @brief header of the segment pid
 * @author sunlei(sunlei@holomatic.com)
 * @date 2020-09-04
 */

#ifndef HOLO_C_CONTROL_SEGMENT_PID_H_
#define HOLO_C_CONTROL_SEGMENT_PID_H_

#include <holo_c/control/pid.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/control/debug.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SEGMENT_PID_PARAM_MAX_TABLE_SIZE 128  ///< maximum size of SegmentPid's table
#define SEGMENT_PID_PARAM_MAX_DIMENSION 4    ///< maximum dimention of SegmentPid

/**
 * @brief SegmentPid's parameter
 */
struct SegmentPidParam
{
    uint16_t table_size;  ///< size of SegmentPid's table
    uint16_t dimension;   ///< dimention of SegmentPid
    struct
    {
        float32_t       plane[SEGMENT_PID_PARAM_MAX_DIMENSION];
        struct PidParam param;
    } table[SEGMENT_PID_PARAM_MAX_TABLE_SIZE];  ///< SegmentPid's parameter table
};

/**
 * @brief an assemble of Pid with different parameters
 *
 * @details The structure representing segment pid parameters, it has several segments. The segments are
 *          divided by different hyperplane. Each segment has its own kp, ki and kd which are
 *          different from other segments.
 */
struct SegmentPid
{
    struct Pid             pid;    ///< SegmentPid's pid
    struct SegmentPidParam param;  ///< SegmentPid's parameters
};

/**
 * @brief an comparator of hyperplane
 *
 * @param plane_l hyperplane
 * @param plane_r hyperplane
 *
 * @return RC_FAIL plane_l is greater than or equal to plane_r
 * @return RC_SUCCESS plane_l is less than plane_r in every dimension
 */
retcode_t plane_cmp_lt(uint16_t dimension, const float32_t* plane_l, const float32_t* plane_r);

/**
 * @brief an comparator of hyperplane
 *
 * @param plane_l hyperplane
 * @param plane_r hyperplane
 *
 * @return RC_FAIL
 * @return RC_SUCCESS plane_l is less than or equal to plane_r in higher dimension
 */
retcode_t plane_cmp_higher_dimension_lt(uint16_t dimension, const float32_t* plane_l, const float32_t* plane_r);

/**
 * @brief Initialize segment pid parameters by default
 *
 * @param param The SegmentPid's parameter
 *
 * @return RC_SECTIONAL_PID_CONTROLLER_EMPTY_PARAM_TABLE the input parameter table is empty
 * @return RC_SECTIONAL_PID_CONTROLLER_INVALID_ITEM_ERROR input item's error is less than back item from table
 * @return RC_FAIL init failed
 * @return RC_SUCCESS
 */
void segment_param_init_default(struct SegmentPidParam* param);

/**
 * @brief Initialize segment pid with input parameters
 *
 * @param controller Pointer to SegmentPid structure
 * @param param The SegmentPid's parameter
 *
 * @return RC_SECTIONAL_PID_CONTROLLER_EMPTY_PARAM_TABLE the input parameter table is empty
 * @return RC_SECTIONAL_PID_CONTROLLER_INVALID_ITEM_ERROR input item's error is less than back item from table
 * @return RC_FAIL init failed
 * @return RC_SUCCESS
 */
retcode_t segment_pid_init(struct SegmentPid* controller, const struct SegmentPidParam* param);

/**
 * @brief Calculate the segment pid output based on input
 *
 * @param controller Pointer to SegmentPid structure
 * @param dimension The dimension of params
 * @param plane The hyperplane of SegmentPid
 * @param error  The error between ego_speed and target_speed
 * @param interpolation_enable  Enable linear interpolation of tables
 *
 * @return the segment pid's output
 */
float32_t segment_pid_set_control(struct SegmentPid*            controller,
                                  int16_t                       dimension,
                                  float32_t*                    plane,
                                  float32_t                     error,
                                  bool_t                        interpolation_enable,
                                  struct PIDControlDebugLogger* debug_logger);

/**
 * @brief Reset the segment pid parameters make previous error and integral as zero
 *
 * @param controller Pointer to SegmentPid structure
 */
void segment_pid_reset(struct SegmentPid* controller);

/**
 * @brief Reset the segment pid parameters make integral as zero
 *
 * @param controller Pointer to SegmentPid structure
 */
void segment_pid_reset_integral(struct SegmentPid* controller);

/**
 * @brief  Linear interpolation of adjacent struct PidParam
 *
 * @param param_statrt Pointer to PidParam structure
 * @param param_end Pointer to PidParam structure
 * @param ratio interpolation coef
 *
 * @return  struct PidParam after linear interpolation
 */
struct PidParam segment_param_linear_interpolation(const struct PidParam* param_start,
                                                   const struct PidParam* param_end,
                                                   const float32_t        ratio);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_CONTROL_SECTIONAL_PID_CONTROLLER_H_ */
