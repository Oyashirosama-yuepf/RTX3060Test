/*!
 * @file ublox_cfg.c
 * @brief This source file defines ublox m8t/m8l config functions
 * @author liuya@holomatic.com
 * @date 2019-09-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <string.h>

#include <holo_c/sensors/ublox/ublox_cfg.h>
#include <holo_c/sensors/ublox/ubx_parse.h>

retcode_t ublox_cfg_gnss(uint8_t* cfg_msg, uint8_t* len)
{
    uint8_t tdata[60];
    memset(tdata, 0, 60);

    memcpy(tdata, gnss_cfg_data, 58);

    ubx_calculate_ck(tdata + 2, 56, &tdata[58], &tdata[59]);

    memcpy(cfg_msg, tdata, 60);
    *len = 60;

    return RC_SUCCESS;
}

retcode_t ublox_cfg_nav5(uint8_t* cfg_msg, uint8_t* len)
{
    uint8_t tdata[44];
    memset(tdata, 0, 44);

    memcpy(tdata, nav5_cfg_data, 42);

    ubx_calculate_ck(tdata + 2, 40, &tdata[42], &tdata[43]);

    memcpy(cfg_msg, tdata, 44);
    *len = 44;

    return RC_SUCCESS;
}

retcode_t ublox_cfg_nmea(uint8_t* cfg_msg, uint8_t* len, uint8_t main_talker_id, uint8_t gsv_talker_id)
{
    uint8_t tdata[28];
    memset(tdata, 0, 28);

    memcpy(tdata, nmea_cfg_data, 26);
    tdata[15] = main_talker_id;
    tdata[16] = gsv_talker_id;

    ubx_calculate_ck(tdata + 2, 24, &tdata[26], &tdata[27]);

    memcpy(cfg_msg, tdata, 28);
    *len = 28;

    return RC_SUCCESS;
}

retcode_t ublox_cfg_msg_rate(uint8_t* cfg_msg, uint8_t* len, uint16_t meas_cyc, uint16_t nav_cyc)
{
    uint16_t tmp_meas_cyc;
    uint8_t  tdata[14];
    memset(tdata, 0, 14);

    memcpy(tdata, msg_rate_cfg_data, 12);
    if (meas_cyc < 100)
    {
        tmp_meas_cyc = 100;
    }
    else if (meas_cyc > 1000)
    {
        tmp_meas_cyc = 1000;
    }
    else
    {
        tmp_meas_cyc = meas_cyc;
    }

    tdata[6] = (tmp_meas_cyc & 0x00FF) >> 0;
    tdata[7] = (tmp_meas_cyc & 0xFF00) >> 8;
    tdata[8] = (nav_cyc & 0x7F) >> 0;

    ubx_calculate_ck(tdata + 2, 10, &tdata[12], &tdata[13]);

    memcpy(cfg_msg, tdata, 14);
    *len = 14;

    return RC_SUCCESS;
}

retcode_t ublox_cfg_tp5(uint8_t* cfg_msg, uint8_t* len, uint8_t enable_tp5)
{
    uint16_t tp5_flags;
    uint8_t  tdata[40];
    memset(tdata, 0, 40);

    memcpy(tdata, tp5_cfg_data, 38);
    tp5_flags = ((enable_tp5) ? (1 << 0) : (0 << 0)) + (1 << 1) + (1 << 2) + (1 << 4) + (1 << 5) + (1 << 6);

    tdata[34] = (tp5_flags & 0x00FF) >> 0;
    tdata[35] = (tp5_flags & 0xFF00) >> 8;

    ubx_calculate_ck(tdata + 2, 36, &tdata[38], &tdata[39]);

    memcpy(cfg_msg, tdata, 40);
    *len = 40;

    return RC_SUCCESS;
}

retcode_t ublox_cfg_msg_enable(uint8_t* cfg_msg, uint8_t* len, struct UbxMsgCfg* param)
{
    uint8_t tdata[11];
    memset(tdata, 0, 11);

    memcpy(tdata, msg_enable_cfg_data, 9);
    tdata[6] = param->classification;
    tdata[7] = param->id;
    tdata[8] = param->rate;

    ubx_calculate_ck(tdata + 2, 7, &tdata[9], &tdata[10]);

    memcpy(cfg_msg, tdata, 11);
    *len = 11;

    return RC_SUCCESS;
}

retcode_t ublox_cfg_save(uint8_t* cfg_msg, uint8_t* len)
{
    uint8_t tdata[21];
    memset(tdata, 0, 21);

    memcpy(tdata, cfg_save_data, 19);
    ubx_calculate_ck(tdata + 2, 17, &tdata[19], &tdata[20]);

    memcpy(cfg_msg, tdata, 21);
    *len = 21;

    return RC_SUCCESS;
}
