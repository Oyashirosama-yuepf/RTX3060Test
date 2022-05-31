/*!
 * @file mpc_driver.h
 * @brief This header file defines bosch mpc sensor driver functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_MPC_MPC_DRIVER_H_
#define HOLO_C_SENSORS_MPC_MPC_DRIVER_H_

#include <holo_c/common/timestamp.h>
#include <holo_c/core/types.h>
#include <holo_c/sensors/dbc/mpc_recv_dbc.h>
#include <holo_c/sensors/dbc/mpc_send_dbc.h>
#include <holo_c/sensors/mpc/structure/mpc_line.h>
#include <holo_c/sensors/mpc/structure/mpc_object.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 * @{
 */

/**
 * @brief only the can msg id in this table is useful for mpc driver
 *
 */
static const uint32_t mpc_msg_id_table[] = {
    ID_BV1_Lin_01_A, ID_BV1_Lin_01_B, ID_BV1_Lin_02_A, ID_BV1_Lin_02_B, ID_BV1_Lin_03_A, ID_BV1_Lin_03_B,
    ID_BV1_Lin_04_A, ID_BV1_Lin_04_B, ID_BV_Obj_01_A,  ID_BV_Obj_01_B,  ID_BV_Obj_01_C,  ID_BV_Obj_01_D,
    ID_BV_Obj_01_E,  ID_BV_Obj_02_A,  ID_BV_Obj_02_B,  ID_BV_Obj_02_C,  ID_BV_Obj_02_D,  ID_BV_Obj_02_E,
    ID_BV_Obj_03_A,  ID_BV_Obj_03_B,  ID_BV_Obj_03_C,  ID_BV_Obj_03_D,  ID_BV_Obj_03_E,  ID_BV_Obj_04_A,
    ID_BV_Obj_04_B,  ID_BV_Obj_04_C,  ID_BV_Obj_04_D,  ID_BV_Obj_04_E,  ID_BV_Obj_05_A,  ID_BV_Obj_05_B,
    ID_BV_Obj_05_C,  ID_BV_Obj_05_D,  ID_BV_Obj_05_E,  ID_BV_Obj_06_A,  ID_BV_Obj_06_B,  ID_BV_Obj_06_C,
    ID_BV_Obj_06_D,  ID_BV_Obj_06_E,  ID_BV_Obj_07_A,  ID_BV_Obj_07_B,  ID_BV_Obj_07_C,  ID_BV_Obj_07_D,
    ID_BV_Obj_07_E,  ID_BV_Obj_08_A,  ID_BV_Obj_08_B,  ID_BV_Obj_08_C,  ID_BV_Obj_08_D,  ID_BV_Obj_08_E,
    ID_BV_Obj_09_A,  ID_BV_Obj_09_B,  ID_BV_Obj_09_C,  ID_BV_Obj_09_D,  ID_BV_Obj_09_E,  ID_BV_Obj_10_A,
    ID_BV_Obj_10_B,  ID_BV_Obj_10_C,  ID_BV_Obj_10_D,  ID_BV_Obj_10_E,  ID_BV_Obj_11_A,  ID_BV_Obj_11_B,
    ID_BV_Obj_11_C,  ID_BV_Obj_11_D,  ID_BV_Obj_11_E,  ID_BV_Obj_12_A,  ID_BV_Obj_12_B,  ID_BV_Obj_12_C,
    ID_BV_Obj_12_D,  ID_BV_Obj_12_E,  ID_BV_Obj_13_A,  ID_BV_Obj_13_B,  ID_BV_Obj_13_C,  ID_BV_Obj_13_D,
    ID_BV_Obj_13_E,  ID_BV_Obj_14_A,  ID_BV_Obj_14_B,  ID_BV_Obj_14_C,  ID_BV_Obj_14_D,  ID_BV_Obj_14_E,
    ID_BV_Obj_15_A,  ID_BV_Obj_15_B,  ID_BV_Obj_15_C,  ID_BV_Obj_15_D,  ID_BV_Obj_15_E,  ID_BV_Obj_16_A,
    ID_BV_Obj_16_B,  ID_BV_Obj_16_C,  ID_BV_Obj_16_D,  ID_BV_Obj_16_E};

/**
 * @brief mpc can data process state
 *
 */
enum MpcParseState
{
    MPC_PARSE_IDLE = 0,
    MPC_PARSE_LINE,
    MPC_PARSE_OBJECT,
    MPC_PARSE_ERROR,
};

/**
 * @brief mpc driver struct
 *
 */
struct MpcDriver
{
    enum MpcParseState          parse_state;
    struct MpcLinesRawData      lines;
    struct MpcObjectListRawData objects;
};

/**
 * @brief whether the can msg id received in the valide table
 *
 * @param id can msg id
 * @return retcode_t RC_SUCCESS(valid), RC_FAIL(invalide)
 */
retcode_t mpc_msg_id_is_valid(uint32_t id);

/**
 * @brief Init mpc driver
 *
 * @param driver Mpc driver pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t mpc_driver_init(struct MpcDriver* driver);

/**
 * @brief Process mcp CAN bus data
 *
 * @param driver Mpc driver pointer
 * @param timestamp CAN data received timestamp
 * @param id CAN msg id
 * @param msg CAN msg content
 * @param len CAN msg length
 *
 * @return retcode_t RC_MPC_PARSE_LINE_CONTINUE Parse lane boundaries not complete yet.
 * @return retcode_t RC_MPC_PARSE_LINE_COMPLETE Parse lane boundaries complete.
 * @return retcode_t RC_MPC_PARSE_OBJ_CONTINUE Parse object not complete yet.
 * @return retcode_t RC_MPC_PARSE_OBJ_COMPLETE Parse object complete.
 * @return retcode_t RC_MPC_PARSE_ID_ERROR CAN id is not correct.
 * @return retcode_t RC_MPC_PARSE_DATA_ERROR CAN data is error.
 */
retcode_t mpc_driver_process_data(struct MpcDriver* driver, const struct Timestamp* timestamp, uint32_t id,
                                  const uint8_t* msg, uint8_t len);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif
