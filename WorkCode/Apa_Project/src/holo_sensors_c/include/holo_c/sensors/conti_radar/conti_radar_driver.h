/*!
 * @file conti_radar_driver.h
 * @brief This header file defines conti radar sensor driver functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_CONTI_RADAR_CONTI_RADAR_DRIVER_H_
#define HOLO_C_SENSORS_CONTI_RADAR_CONTI_RADAR_DRIVER_H_

#include <holo_c/sensors/conti_radar/structure/conti_radar_object.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 * @{
 *
 */

#define CONTI_RADAR_OBJECT_NUM 100

/**
 * @brief conti radar can data parse state
 *
 */
enum ContiRadarParseState
{
    CONTI_RADAR_PARSE_IDLE = 0,
    CONTI_RADAR_PARSE_OBJ_PART_0,
    CONTI_RADAR_PARSE_OBJ_PART_1,
    CONTI_RADAR_PARSE_OBJ_PART_2,
    CONTI_RADAR_PARSE_OBJ_PART_3,
    CONTI_RADAR_PARSE_STATE_ERROR,
};

/**
 * @brief conti radar driver struct
 *
 */
struct ContiRadarDriver
{
    enum ContiRadarParseState parse_state;

    struct ContiRadarObjectListRawData object_list;
};

/**
 * @brief init conti radar driver
 *
 * @param driver conti radar driver pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t conti_radar_driver_init(struct ContiRadarDriver* driver);

/**
 * @brief process conti radar can message
 *
 * @param driver conti radar driver pointer
 * @param timestamp system timestamp
 * @param msg_id can message id
 * @param msg can message content
 * @param len can message length
 * @return retcode_t RC_SUCCESS
 */
retcode_t conti_radar_driver_process_data(struct ContiRadarDriver* driver, const struct Timestamp timestamp,
                                          uint8_t index, uint32_t msg_id, const uint8_t* msg, uint8_t len);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_SENSORS_CONTI_RADAR_CONTI_RADAR_DRIVER_H_
