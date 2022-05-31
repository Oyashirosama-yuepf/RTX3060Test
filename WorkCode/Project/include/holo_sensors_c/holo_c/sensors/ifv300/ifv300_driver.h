/*!
 * @file ifv300_driver.h
 * @brief This header file defines ifv300 sensor driver functions
 * @author liuya@holomatic.com
 * @date 2020-04-15
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_IFV300_IFV300_DRIVER_H_
#define HOLO_C_SENSORS_IFV300_IFV300_DRIVER_H_

#include <holo_c/common/timestamp.h>
#include <holo_c/core/types.h>
#include <holo_c/sensors/ifv300/structure/ifv300_line.h>
#include <holo_c/sensors/ifv300/structure/ifv300_object.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 * @{
 */

#define RC_IFV_PARSE_LINE_CONTINUE -1001
#define RC_IFV_PARSE_LINE_COMPLETE -1002
#define RC_IFV_PARSE_OBJ_CONTINUE -1011
#define RC_IFV_PARSE_OBJ_COMPLETE -1012
#define RC_IFV_PARSE_ID_ERROR -1021
#define RC_IFV_PARSE_DATA_ERROR -1031

/**
 * @brief ifv can data process state
 *
 */
enum IfvParseState
{
    IFV_PARSE_IDLE = 0,
    IFV_PARSE_LINE_HEAD,
    IFV_PARSE_LINE_NEAR_LEFT,
    IFV_PARSE_LINE_NEAR_RIGHT,
    IFV_PARSE_LINE_NEIGHBOR_RIGHT,
    IFV_PARSE_LINE_NEIGHBOR_LEFT,
    IFV_PARSE_OBJECT_PART1,
    IFV_PARSE_OBJECT_PART2,
    IFV_PARSE_OBJECT_PART3,
    IFV_PARSE_ERROR,
};

/**
 * @brief ifv driver struct
 *
 */
struct IfvDriver
{
    enum IfvParseState          parse_state;
    struct IfvLinesRawData      lines;
    struct IfvObjectListRawData objects;
};

/**
 * @brief whether the can msg id received in the valide table
 *
 * @param id can msg id
 * @return retcode_t RC_SUCCESS(valid), RC_FAIL(invalide)
 */
retcode_t ifv_msg_id_is_valid(uint32_t id);

/**
 * @brief Init ifv driver
 *
 * @param driver Ifv driver pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t ifv_driver_init(struct IfvDriver* driver);

/**
 * @brief Process ifv CAN bus data
 *
 * @param driver Ifv driver pointer
 * @param timestamp CAN data received timestamp
 * @param id CAN msg id
 * @param msg CAN msg content
 * @param len CAN msg length
 *
 * @return retcode_t RC_IFV_PARSE_LINE_CONTINUE Parse lane boundaries not complete yet.
 * @return retcode_t RC_IFV_PARSE_LINE_COMPLETE Parse lane boundaries complete.
 * @return retcode_t RC_IFV_PARSE_OBJ_CONTINUE Parse object not complete yet.
 * @return retcode_t RC_IFV_PARSE_OBJ_COMPLETE Parse object complete.
 * @return retcode_t RC_IFV_PARSE_ID_ERROR CAN id is not correct.
 * @return retcode_t RC_IFV_PARSE_DATA_ERROR CAN data is error.
 */
retcode_t ifv_driver_process_data(struct IfvDriver* driver, const struct Timestamp* timestamp, uint32_t id,
                                  const uint8_t* msg, uint8_t len);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif
