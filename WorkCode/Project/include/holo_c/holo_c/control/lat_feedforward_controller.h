/**
 * @file lat_feedforward_controller.h
 * @brief the header of lateral feedforward controller
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2020-12-05
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_CONTROL_LAT_FEEDFORWARD_CONTROLLER_H_
#define HOLO_C_CONTROL_LAT_FEEDFORWARD_CONTROLLER_H_

#include <holo_c/common/chassis_state.h>
#include <holo_c/common/odometry_float32.h>
#include <holo_c/common/path_float32.h>
#include <holo_c/control/debug.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/numerics/cubic_spline.h>

#include <holo_c/control/filters/mean_filter.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LAT_FEEDFORWARD_CONTROLLER_GAIN_SCHEDULER_NUM 15  ///< numbers of points during generating spline
#define FF_ARKERMANN_RATIO_MAX_TABLE_SIZE 225
#define FF_ARKERMANN_RATIO_MAX_DIMENSION 2
#define FF_ARKERMANN_RATIO_TABLE_ROWS 15
#define FF_ARKERMANN_RATIO_TABLE_COLS 15

/**
 * @brief LatFeedforwardController's parameter
 */
struct LatFeedforwardControllerParam
{
    float32_t feedforward_arkermann_model_coef;
    float32_t feedforward_kinetic_model_coef;
    float32_t wheelbase;
    float32_t v_threshold;
    float32_t preview_v_threshold;
    float32_t preview_distance_forward_1;
    float32_t preview_distance_forward_2;
    float32_t preview_distance_backward_1;
    float32_t preview_distance_backward_2;
    float32_t abnormal_step_target_curvature;
    float32_t abnormal_target_curvature;

    uint32_t feedforward_filter_window_size;  ///< window size of feedforward's mean filter



    struct
    {
        uint32_t  table_size;     ///< size of FFArkermannRatioTable's table
        uint32_t  dimension;      ///< dimension of FFArkermannRatioTable params
        uint32_t  rows;           ///< rows of FFArkermannRatioTable's table
        uint32_t  cols;           ///< cols of FFArkermannRatioTable's table
        struct
        {
            float32_t plane[FF_ARKERMANN_RATIO_MAX_DIMENSION];
            float32_t ratio;
        } table[FF_ARKERMANN_RATIO_MAX_TABLE_SIZE];
        struct Point3f table_2D[FF_ARKERMANN_RATIO_TABLE_ROWS * FF_ARKERMANN_RATIO_TABLE_COLS];
    } FFArkermannRatioTable; 

    struct Point2f feedforward_kinetic_coef_velocity_ratio_table[LAT_FEEDFORWARD_CONTROLLER_GAIN_SCHEDULER_NUM];
    uint32_t       feedforward_kinetic_coef_velocity_ratio_table_size;

    struct Point2f feedforward_kinetic_coef_curvature_ratio_table[LAT_FEEDFORWARD_CONTROLLER_GAIN_SCHEDULER_NUM];
    uint32_t       feedforward_kinetic_coef_curvature_ratio_table_size;
};

/**
 * @brief This structure represents the feedforward controller for lateral control
 */
struct LatFeedforwardController
{
    struct LatFeedforwardControllerParam param;
    struct MeanFilter                    feed_forward_k_filter;  ///< MeanFilter for curvature
    float32_t                            last_target_curvature;
    bool_t                               flag_former_loop_has_reset;
};

/**
 * @brief Initialize lateral feedforward controller by input parameters
 *
 * @param controller Pointer to LatFeedforwardController structure
 * @param param Input parameters
 *
 * @return RC_SUCCESS init successfully
 * @return todo
 */
retcode_t lat_feedforward_controller_init(struct LatFeedforwardController*            controller,
                                          const struct LatFeedforwardControllerParam* param);

/**
 * @brief Update target curvature for lateral feedforward controller
 *
 * @param controller Pointer to LatFeedforwardController structure
 * @param path Pointer to Pathf
 * @param odometry Pointer to Odometryf
 *
 * @return target_curvature
 * @return todo
 */
float32_t lat_feedforward_controller_update_target_curvature(struct LatFeedforwardController* controller,
                                                             const struct Pathf*              path,
                                                             const struct Odometryf*          odometry,
                                                             const struct ChassisState*       chassis_state);

/**
 * @brief Check target curvature for lateral feedforward controller
 *
 * @param target_curvature Pointer to LatFeedforwardController structure
 *
 * @return RC_SUCCESS
 * @return todo
 */
retcode_t lat_feedforward_controller_abnormal_input_check(struct LatFeedforwardController* controller,
                                                          float32_t                        target_curvature);

/**
 * @brief Calculate lateral feedforward controller's output
 *
 * @param controller Pointer to LatFeedforwardController structure.
 * @param path Pointer to Pathf
 * @param odometry Pointer to Odometryf
 *
 * @return the lateral feedforward controller's output
 */
retcode_t lat_feedforward_controller_set_control(struct LatFeedforwardController*         controller,
                                                 const struct Pathf*                      path,
                                                 const struct Odometryf*                  odometry,
                                                 const struct ChassisState*               chassis_state,
                                                 float32_t*                               ff_output,
                                                 struct LatFeedforwardControlDebugLogger* lat_ff_debug_log);

/**
 * @brief reset the lateral feedforward controller
 *
 * @param controller The pointer of LatFeedforwardController.
 */
void lat_feedforward_controller_reset(struct LatFeedforwardController* controller);

/**
 * @brief   init the lat feedforward corf tatio table by default
 * @param controller the lat feedforward controller parameter pointer
 */
void feedforward_arkermann_corf_ratio_table_init_default(struct LatFeedforwardControllerParam* controller);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_CONTROL_LAT_FEEDFORWARD_CONTROLLER_H_ */
