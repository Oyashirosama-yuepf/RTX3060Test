/*!
 * @file vehicle_can_driver.h
 * @brief This header file defines vehicle can driver functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */
#ifndef HOLO_C_SENSORS_CAN_VEHICLE_CAN_DRIVER_H_
#define HOLO_C_SENSORS_CAN_VEHICLE_CAN_DRIVER_H_

#include <holo_c/common/chassis_state.h>
#include <holo_c/common/imu_float32.h>
#include <holo_c/common/timestamp.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/sensors/dbc/vehicle_can_dbc.h>
#include <holo_c/sensors/dbc/vehicle_body_dbc.h>
#include <holo_c/sensors/vehicle_body_state/vehicle_body_state.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 * @{
 */

/**
 * @brief process vehicle can data and construct raw data struct
 *
 * @param raw_data vehicle can raw data pointer
 * @param timestamp system timestamp
 * @param id can message id
 * @param data can message content
 * @param len can message length
 * @return retcode_t RC_SUCCESS
 */
retcode_t vehicle_can_driver_process_data(struct ChassisState* chassis_state, struct VehicleBodyState* body_state,
                                          const struct Timestamp* timestamp, uint32_t id, uint8_t* data, uint32_t len);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif
