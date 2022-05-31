/**
 * @file lon_feedforward_controller.h
 * @brief the header of longitudinal feedforward controller
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2019-09-25
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_CONTROL_LON_FEEDFORWARD_CONTROLLER_H_
#define HOLO_C_CONTROL_LON_FEEDFORWARD_CONTROLLER_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/control/util.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LON_FEEDFORWARD_CONTROLLER_PARAM_MAX_TABLE_SIZE 32  ///< maximum size of LonFeedforwardController's table
#define SEGMENT_RATIO_PARAM_MAX_DIMENSION 4    ///< maximum dimension of LonFeedforwardController param

/**
 * @brief LonFeedforwardController's parameter
 */
struct LonFeedforwardControllerParam
{
    uint32_t  table_size;     ///< size of LonFeedforwardControllerParam's table
    uint32_t  dimension;      ///< dimension of LonFeedforwardController params
    struct
    {
        float32_t plane[SEGMENT_RATIO_PARAM_MAX_DIMENSION];    
        float32_t ratio;                                        ///< Coefficient of feedforward
    } table[LON_FEEDFORWARD_CONTROLLER_PARAM_MAX_TABLE_SIZE];   ///< LonFeedforwardControllerParam's parameter table
};

/**
 * @brief This structure represents a feedforward controller, input value is a feedforward acceleration, output value is
 *        input value * coef(it is a function of ego speed).
 */
struct LonFeedforwardController
{
    struct LonFeedforwardControllerParam param;
};

/**
 * @brief Initialize feedforward controller by input parameters
 *
 * @param controller Pointer to LonFeedforwardController structure
 * @param param Input parameters
 *
 * @return RC_SUCCESS init successfully
 * @return RC_FEEDFORWARD_CONTROLLER_INVALID_MAXMIN_DEAD_ZONE the dead_zone parameter is invalid
 * @return RC_FEEDFORWARD_CONTROLLER_EMPTY_PARAM_TABLE the input parameters' table is empty
 * @return RC_FEEDFORWARD_CONTROLLER_SAME_ITEM the input parameters' table has the same item
 * @return RC_FEEDFORWARD_CONTROLLER_INVALID_ITEM_SPEED the later item's speed is less than former's
 */
retcode_t lon_feedforward_controller_init(struct LonFeedforwardController*            controller,
                                          const struct LonFeedforwardControllerParam* param);

/**
 * @brief Calculate the feedforward output based on input
 *
 * @param controller Pointer to LonFeedforwardController structure.
 * @param dimension  The dimension of params.
 * @param plane      The plane data.
 * @param input_feedforward The input feedforward.
 * @param interpolation_enable If enables the linear interpolation.
 *
 * @return the feedforward controller's output
 */
float32_t lon_feedforward_controller_set_control(struct LonFeedforwardController* controller,
                                                 uint32_t                         dimension,
                                                 float32_t*                       plane,
                                                 float32_t                        input_feedforward,
                                                 bool_t                           interpolation_enable);

/**
 * @brief Initialize feedforward parameters by default
 *
 * @param param The lon feedforward's parameter
 */
void feedforward_param_init_default(struct LonFeedforwardControllerParam* param);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_CONTROL_LON_FEEDFORWARD_CONTROLLER_H_ */
