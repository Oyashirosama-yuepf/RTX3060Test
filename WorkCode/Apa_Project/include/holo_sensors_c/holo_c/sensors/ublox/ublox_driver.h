/*!
 * @file ublox_driver.h
 * @brief This header file defines ublox m8t/m8l driver functions
 * @author liuya@holomatic.com
 * @date 2019-09-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_UBLOX_UBLOX_DRIVER_H_
#define HOLO_C_SENSORS_UBLOX_UBLOX_DRIVER_H_

#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/sensors/ublox/ubx_msg.h>
#include <holo_c/sensors/ublox/ubx_parse.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 * @{
 *
 */

#define RC_UBX_PARSE_NAV_PVT_SUCCESS -7022
#define RC_UBX_PARSE_RXM_RAWX_SUCCESS -7023
#define RC_UBX_PARSE_RXM_SFRBX_SUCCESS -7024

#define UBLOX_RECV_BUFF_SIZE 2048
#define UBLOX_SEND_BUFF_SIZE 64

typedef void (*NavPvtHandle_t)(uint8_t*);
typedef void (*RxmRawxHandle_t)(uint8_t*);

/**
 * @brief Ublox driver struct
 *
 */
struct UbloxDriver
{
    struct UbxNavPvtMessage   nav_pvt_msg;
    struct UbxRxmRawxMessage  rxm_rawx_msg;
    struct UbxRxmSfrbxMessage rxm_sfrbx_msg;

    uint8_t nav_pvt_raw_data_buf[100];
    uint8_t rxm_rawx_data_buf[1024];

    uint8_t rec_buf[UBLOX_RECV_BUFF_SIZE];
    uint8_t send_buf[UBLOX_SEND_BUFF_SIZE];

    struct UbxParser parser;

    NavPvtHandle_t  nav_pvt_callback;
    RxmRawxHandle_t rxm_rawx_callback;
};

/**
 * @brief Init ublox driver
 *
 * @param driver Ublox driver pointer
 * @param send Send message to ublox function handle
 * @param recv Receive message from ublox function handle
 * @param get_sys_time Get system time function handle
 * @return retcode_t RC_SUCCESS
 */
retcode_t ublox_driver_init(struct UbloxDriver* driver);

/**
 * @brief Parse ublox message
 *
 * @param driver Ublox driver poniter
 * @param timestamp Message recive time
 * @param msg Ublox raw message buffer
 * @param len Ublox raw message length
 * @return retcode_t RC_SUCCESS
 */
retcode_t ublox_parse_message(struct UbloxDriver* driver, const struct Timestamp* timestamp, uint8_t* msg,
                              uint32_t len);

/**
 * @brief Get nav pvt message
 *
 * @param driver Ublox driver pointer
 * @param msg Nav pvt message pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t ublox_driver_get_nav_pvt_msg(const struct UbloxDriver* driver, struct UbxNavPvtMessage* msg);

/**
 * @brief Get rxm rawx message
 *
 * @param driver Ublox driver pointer
 * @param msg Rxm rawx message pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t ublox_driver_get_rxm_rawx_msg(const struct UbloxDriver* driver, struct UbxRxmRawxMessage* msg);

/**
 * @brief Get rxm sfrbx message
 *
 * @param driver Ublox driver pointer
 * @param msg Rxm sfrbx message pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t ublox_driver_get_rxm_sfrbx_msg(const struct UbloxDriver* driver, struct UbxRxmSfrbxMessage* msg);

/**
 * @brief Install nav pvt message callback function
 *
 * @param driver Ublox driver pointer
 * @param callback NavPvt callback function pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t ublox_driver_install_nav_pvt_callback(struct UbloxDriver* driver, NavPvtHandle_t callback);

/**
 * @brief Install rxm rawx message callback function
 *
 * @param driver Ublox driver pointer
 * @param callback RxmRawx callback function pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t ublox_driver_install_rxm_rawx_callback(struct UbloxDriver* driver, RxmRawxHandle_t callback);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_SENSORS_UBLOX_UBLOX_DRIVER_H_
