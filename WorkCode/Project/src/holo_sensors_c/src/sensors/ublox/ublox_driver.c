/*!
 * @file ublox_driver.c
 * @brief This source file defines ublox driver functions
 * @author liuya@holomatic.com
 * @date 2019-09-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <assert.h>
#include <holo_c/geometry/geographical_transformation.h>
#include <holo_c/sensors/ublox/ublox_driver.h>
#include <holo_c/sensors/ublox/ubx_msg.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief Dispatch ubx message
 *
 * @param driver Ublox driver pointer
 * @return retcode_t RC_SUCCESS
 */
static retcode_t ubx_dispatch_message(struct UbloxDriver* driver, const struct Timestamp* timestamp)
{
    uint8_t   msg_class, msg_id;
    retcode_t rc = RC_SUCCESS;

    msg_class = *(driver->parser.buf_base + 2);
    msg_id    = *(driver->parser.buf_base + 3);

    switch (msg_class)
    {
        case UBX_MSG_CLASS_NAV:
            if (msg_id == UBX_MSG_ID_NAV_PVT)
            {
                driver->nav_pvt_msg.timestamp = *timestamp;

                construct_nav_pvt_msg(&driver->nav_pvt_msg.message, driver->rec_buf);

                memcpy(driver->nav_pvt_raw_data_buf, driver->rec_buf, 100);

                rc = RC_UBX_PARSE_NAV_PVT_SUCCESS;
            }
            else
            {
                rc = RC_UBX_PARSE_MSG_ERROR;
            }
            break;

        case UBX_MSG_CLASS_RXM:
            if (msg_id == UBX_MSG_ID_RXM_SFRBX)
            {
                driver->rxm_sfrbx_msg.timestamp = *timestamp;

                construct_rxm_sfrbx_msg(&driver->rxm_sfrbx_msg.message, driver->rec_buf);

                rc = RC_UBX_PARSE_RXM_SFRBX_SUCCESS;
            }
            else if (msg_id == UBX_MSG_ID_RXM_RAWX)
            {
                driver->rxm_rawx_msg.timestamp = *timestamp;

                construct_rxm_rawx_msg(&driver->rxm_rawx_msg.message, driver->rec_buf);
                memcpy(driver->rxm_rawx_data_buf, driver->rec_buf, sizeof(driver->rxm_rawx_data_buf));

                rc = RC_UBX_PARSE_RXM_RAWX_SUCCESS;
            }
            else
            {
                rc = RC_UBX_PARSE_MSG_ERROR;
            }
            break;

        default:
            rc = RC_UBX_PARSE_MSG_ERROR;
            break;
    }
    return rc;
}

void UbxParseCk(struct UbloxDriver* driver, const struct Timestamp* timestamp, retcode_t* rc)
{
    if (*rc == RC_UBX_PARSE_CRC_OK)
    {
        *rc = ubx_dispatch_message(driver, timestamp);
        switch (*rc)
        {
            case RC_UBX_PARSE_RXM_RAWX_SUCCESS:
                driver->rxm_rawx_callback(driver->rxm_rawx_data_buf);
                break;

            case RC_UBX_PARSE_NAV_PVT_SUCCESS:
                driver->nav_pvt_callback(driver->nav_pvt_raw_data_buf);
                break;

            case RC_UBX_PARSE_RXM_SFRBX_SUCCESS:
                // driver->rxm_sfrbx_callback(driver->rxm_sfrbx_data_buf);
                break;

            default:
                break;
        }
    }
}

retcode_t ublox_parse_message(struct UbloxDriver* driver, const struct Timestamp* timestamp, uint8_t* msg, uint32_t len)
{
    assert(driver != NULL);
    assert(msg != NULL);

    retcode_t rc = RC_FAIL;

    while (len > 0)
    {
        switch (driver->parser.state)
        {
            case UBX_PARSE_HEAD:
                rc = ubx_parser_parse_head(&(driver->parser), &msg, &len);
                break;

            case UBX_PARSE_CLASS_ID:
                rc = ubx_parser_parse_class_id(&(driver->parser), &msg, &len);
                break;

            case UBX_PARSE_LENGTH:
                rc = ubx_parser_parse_len(&(driver->parser), &msg, &len);
                break;

            case UBX_PARSE_PAYLOAD:
                rc = ubx_parser_parse_payload(&(driver->parser), &msg, &len);
                break;

            case UBX_PARSE_CK:
                rc = ubx_parser_parse_ck(&(driver->parser), &msg, &len);
                UbxParseCk(driver, timestamp, &rc);
                memset(driver->rec_buf, 0, UBLOX_RECV_BUFF_SIZE);
                driver->parser.exp_len = 2;
                driver->parser.offset  = 0;
                driver->parser.state   = UBX_PARSE_HEAD;
                break;

            case UBX_PARSE_OUTOFSYNC:
                len -= len;
                rc = ubx_parser_handle_outofsync(&(driver->parser));
                break;

            default:
                len -= len;
                rc = RC_FAIL;
                ubx_parser_handle_outofsync(&(driver->parser));
                break;
        }
    }

    return rc;
}

retcode_t ublox_driver_init(struct UbloxDriver* driver)
{
    assert(driver != NULL);

    memset(driver->rec_buf, 0, UBLOX_RECV_BUFF_SIZE);
    memset(driver->send_buf, 0, UBLOX_SEND_BUFF_SIZE);
    memset(driver->nav_pvt_raw_data_buf, 0, 100);
    memset(driver->rxm_rawx_data_buf, 0, 1024);

    driver->parser.exp_len  = 2;
    driver->parser.buf_base = driver->rec_buf;
    driver->parser.offset   = 0;
    driver->parser.buf_size = UBLOX_RECV_BUFF_SIZE;
    driver->parser.state    = UBX_PARSE_HEAD;

    driver->nav_pvt_callback  = NULL;
    driver->rxm_rawx_callback = NULL;

    return RC_SUCCESS;
}

retcode_t ublox_driver_get_nav_pvt_msg(const struct UbloxDriver* driver, struct UbxNavPvtMessage* msg)
{
    assert(driver != NULL);
    assert(msg != NULL);

    *msg = driver->nav_pvt_msg;

    return RC_SUCCESS;
}

retcode_t ublox_driver_get_rxm_rawx_msg(const struct UbloxDriver* driver, struct UbxRxmRawxMessage* msg)
{
    assert(driver != NULL);
    assert(msg != NULL);

    *msg = driver->rxm_rawx_msg;

    return RC_SUCCESS;
}

retcode_t ublox_driver_get_rxm_sfrbx_msg(const struct UbloxDriver* driver, struct UbxRxmSfrbxMessage* msg)
{
    assert(driver != NULL);
    assert(msg != NULL);

    *msg = driver->rxm_sfrbx_msg;

    return RC_SUCCESS;
}

retcode_t ublox_driver_install_nav_pvt_callback(struct UbloxDriver* driver, NavPvtHandle_t callback)
{
    assert(driver != NULL);
    assert(callback != NULL);

    driver->nav_pvt_callback = callback;

    return RC_SUCCESS;
}

retcode_t ublox_driver_install_rxm_rawx_callback(struct UbloxDriver* driver, RxmRawxHandle_t callback)
{
    assert(driver != NULL);
    assert(callback != NULL);

    driver->rxm_rawx_callback = callback;

    return RC_SUCCESS;
}
