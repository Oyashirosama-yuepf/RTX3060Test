/**
 * @file lat_torque_feedforward_controller.h
 * @brief the header of lateral torque feedforward controller
 * @author zhaoyifan(zhaoyifan@holomatic.com)
 * @date 2021-12-07
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_CONTROL_LAT_TORQUE_FEEDFORWARD_CONTROLLER_H_
#define HOLO_C_CONTROL_LAT_TORQUE_FEEDFORWARD_CONTROLLER_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/control/util.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LAT_TORQUE_FEEDFORWARD_CONTROLLER_PARAM_MAX_TABLE_SIZE 120  ///< maximum size of LatTorqueFeedforwardController's table
#define SEGMENT_TORQUE_PARAM_MAX_DIMENSION 4    ///< maximum dimension of LatTorqueFeedforwardController param
#define LAT_TORQUE_FEEDFORWARD_CONTROLLER_PARAM_TABLE_ROWS 15  ///< rows of LatTorqueFeedforwardController's table
#define LAT_TORQUE_FEEDFORWARD_CONTROLLER_PARAM_TABLE_COLS 8  ///< cols of LatTorqueFeedforwardController's table
/**
 * @brief LatTorqueFeedforwardController's parameter
 */
struct LatTorqueFeedforwardControllerParam
{
    uint32_t  table_size;     ///< size of LatTorqueFeedforwardControllerParam's table
    uint32_t  dimension;      ///< dimension of LatTorqueFeedforwardController params
    uint32_t  rows;           ///< rows of LatTorqueFeedforwardControllerParam's table
    uint32_t  cols;           ///< cols of LatTorqueFeedforwardControllerParam's table
    float32_t v_threshold;    ///< threshold of speed for the LatTorqueFeedforwardController
    struct
    {
        float32_t plane[SEGMENT_TORQUE_PARAM_MAX_DIMENSION];
        float32_t torque;                                              ///< Torque of lat feedforward
    } table[LAT_TORQUE_FEEDFORWARD_CONTROLLER_PARAM_MAX_TABLE_SIZE];   ///< LatTorqueFeedforwardControllerParam's parameter table
    struct Point3f table_2D[LAT_TORQUE_FEEDFORWARD_CONTROLLER_PARAM_TABLE_ROWS * LAT_TORQUE_FEEDFORWARD_CONTROLLER_PARAM_TABLE_COLS];
};

/**
 * @brief This structure represents a feedforward controller, input value is a feedforward acceleration, output value is
 *        input value * coef(it is a function of ego speed).
 */
struct LatTorqueFeedforwardController
{
    struct LatTorqueFeedforwardControllerParam param;
};

/**
 * @brief Initialize feedforward controller by input parameters
 *
 * @param controller Pointer to LatTorqueFeedforwardController structure
 * @param param Input parameters
 *
 * @return RC_SUCCESS init successfully
 * @return RC_FEEDFORWARD_CONTROLLER_INVALID_MAXMIN_DEAD_ZONE the dead_zone parameter is invalid
 * @return RC_FEEDFORWARD_CONTROLLER_EMPTY_PARAM_TABLE the input parameters' table is empty
 * @return RC_FEEDFORWARD_CONTROLLER_SAME_ITEM the input parameters' table has the same item
 * @return RC_FEEDFORWARD_CONTROLLER_INVALID_ITEM_SPEED the later item's speed is less than former's
 */
retcode_t lat_torque_feedforward_controller_init(struct LatTorqueFeedforwardController*            controller,
                                                 const struct LatTorqueFeedforwardControllerParam* param);

/**
 * @brief Calculate the feedforward output based on input
 *
 * @param controller Pointer to LatTorqueFeedforwardController structure.
 * @param dimension  The dimension of params.
 * @param plane      The plane data.
 * @param interpolation_enable If enables the linear interpolation.
 *
 * @return the feedforward controller's output
 */
float32_t lat_torque_feedforward_controller_set_control(struct LatTorqueFeedforwardController* controller,
                                                        uint32_t                         dimension,
                                                        float32_t*                       plane,
                                                        bool_t                           interpolation_enable);


/**
 * @brief Initialize feedforward parameters by default
 *
 * @param param The lat trq feedforward's parameter
 */
void lat_torque_feedforward_param_init_default(struct LatTorqueFeedforwardControllerParam* param);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_CONTROL_LAT_TORQUE_FEEDFORWARD_CONTROLLER_H_ */
