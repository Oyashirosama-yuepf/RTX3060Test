/*!
 * @file ublox_cfg.h
 * @brief This header file defines ublox m8t/m8l config messages
 * @author liuya@holomatic.com
 * @date 2019-09-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_UBLOX_UBLOX_CFG_H_
#define HOLO_C_SENSORS_UBLOX_UBLOX_CFG_H_

#include <holo_c/core/types.h>
#include <holo_c/sensors/ublox/nmea_msg.h>
#include <holo_c/sensors/ublox/ubx_msg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 * @{
 *
 */

/**
 * @brief Gnss class message config content
 *
 */
static const uint8_t gnss_cfg_data[58] = {
    0xB5, 0x62, 0x06, 0x3E, 0x34, 0x00, 0x00, 0x00, 0x20, 0x06, 0x00, 0x08, 0x10, 0x00, 0x01,
    0x00, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x08, 0x10, 0x00,
    0x01, 0x00, 0x01, 0x01, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x01, 0x05, 0x00, 0x03,
    0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x08, 0x0E, 0x00, 0x00, 0x00, 0x01, 0x01,
    // 0x14,   0xE1
};

/**
 * @brief Nav5 class message config content
 *
 */
static const uint8_t nav5_cfg_data[42] = {
    0xB5,
    0x62,
    UBX_MSG_CLASS_CFG,
    UBX_MSG_ID_CFG_NAV5,
    0x24,
    0x00,
    0xFF,
    0xFF,
    0x04,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x10,
    0x27,
    0x00,
    0x00,
    0x05,
    0x00,
    0xFA,
    0x00,
    0xFA,
    0x00,
    0x64,
    0x00,
    0x2C,
    0x01,
    0x00,
    0x00,
    0x00,
    0x00,
    0x10,
    0x27,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};

/**
 * @brief Nmea class message config content
 *
 */
static const uint8_t nmea_cfg_data[26] = {
    0xB5,
    0x62,
    UBX_MSG_CLASS_CFG,
    UBX_MSG_ID_CFG_NMEA,
    0x14,
    0x00,
    0x00,
    0x41,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x01,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};

/**
 * @brief Message rate config content
 *
 */
static const uint8_t msg_rate_cfg_data[12] = {
    0xB5, 0x62, UBX_MSG_CLASS_CFG, UBX_MSG_ID_CFG_RATE, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
};

/**
 * @brief Tp5 class message config content
 *
 */
static const uint8_t tp5_cfg_data[38] = {
    0xB5,
    0x62,
    UBX_MSG_CLASS_CFG,
    UBX_MSG_ID_CFG_TP5,
    0x20,
    0x00,
    0x01,
    0x01,
    0x00,
    0x00,
    0x32,
    0x00,
    0x00,
    0x00,
    0x40,
    0x42,
    0x0F,
    0x00,
    0x40,
    0x42,
    0x0F,
    0x00,
    0xA0,
    0x86,
    0x01,
    0x00,
    0xA0,
    0x86,
    0x01,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};

/**
 * @brief Enable message config content
 *
 */
static const uint8_t msg_enable_cfg_data[9] = {
    0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00,
};

/**
 * @brief Save config content
 *
 */
static const uint8_t cfg_save_data[19] = {
    0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
    // 0x1D, 0xAB
};

/**
 * @brief Config gnss message
 *
 * @param driver Ublox driver pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t ublox_cfg_gnss(uint8_t* cfg_msg, uint8_t* len);

/**
 * @brief Config nav5 message
 *
 * @param driver Ublox driver pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t ublox_cfg_nav5(uint8_t* cfg_msg, uint8_t* len);

/**
 * @brief Config nmea message
 *
 * @param driver Ublox driver pointer
 * @param main_talker_id Nmea main talker id
 * @param gsv_talker_id Nmea gsv talker id
 * @return retcode_t RC_SUCCESS
 */
retcode_t ublox_cfg_nmea(uint8_t* cfg_msg, uint8_t* len, uint8_t main_talker_id, uint8_t gsv_talker_id);

/**
 * @brief Config message rate
 *
 * @param driver Ublox driver pointer
 * @param meas_cyc Nmea meas cyc
 * @param nav_cyc Nmea nav cyc
 * @return retcode_t RC_SUCCESS
 */
retcode_t ublox_cfg_msg_rate(uint8_t* cfg_msg, uint8_t* len, uint16_t meas_cyc, uint16_t nav_cyc);

/**
 * @brief Config tp5 message enable/disable
 *
 * @param driver Ublox driver pointer
 * @param enable_tp5 Enable/disable tp5 message
 * @return retcode_t RC_SUCCESS
 */
retcode_t ublox_cfg_tp5(uint8_t* cfg_msg, uint8_t* len, uint8_t enable_tp5);

/**
 * @brief Enalbe/disable ublox message
 *
 * @param driver Ublox driver pointer
 * @param param Config content
 * @return retcode_t RC_SUCCESS
 */
retcode_t ublox_cfg_msg_enable(uint8_t* cfg_msg, uint8_t* len, struct UbxMsgCfg* param);

/**
 * @brief Save ublox config
 *
 * @param driver Ublox driver pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t ublox_cfg_save(uint8_t* cfg_msg, uint8_t* len);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_SENSORS_UBLOX_UBLOX_CFG_H_
