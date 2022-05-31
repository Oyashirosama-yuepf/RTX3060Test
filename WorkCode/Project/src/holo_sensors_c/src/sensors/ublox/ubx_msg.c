/*!
 * @file ubx_msg.c
 * @brief This source file defines ubx message construct functions
 * @author liuya@holomatic.com
 * @date 2019-09-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo_c/sensors/ublox/ublox_driver.h>

void ubx_calculate_ck(const uint8_t* data, uint32_t data_length, uint8_t* ck_a, uint8_t* ck_b)
{
    uint32_t i;

    *ck_a = 0;
    *ck_b = 0;

    for (i = 0; i < data_length; ++i)
    {
        *ck_a = *ck_a + data[i];
        *ck_b = *ck_b + *ck_a;
    }
}

void construct_nav_pvt_msg(struct UbxNavPvtMsg* out, uint8_t* in)
{
    uint8_t* head_p = in;
    uint8_t* msg_p  = in + 2 + sizeof(struct UbxMsgHeader);

    out->ubx_header.msg_class  = *((uint8_t*)(head_p + 2));
    out->ubx_header.msg_id     = *((uint8_t*)(head_p + 3));
    out->ubx_header.msg_length = *((uint16_t*)(head_p + 4));

    out->itow    = *((uint32_t*)(msg_p + 0));
    out->year    = *((uint16_t*)(msg_p + 4));
    out->month   = *((uint8_t*)(msg_p + 6));
    out->day     = *((uint8_t*)(msg_p + 7));
    out->hour    = *((uint8_t*)(msg_p + 8));
    out->min     = *((uint8_t*)(msg_p + 9));
    out->sec     = *((uint8_t*)(msg_p + 10));
    out->valid   = *((uint8_t*)(msg_p + 11));
    out->tAcc    = *((uint32_t*)(msg_p + 12));
    out->nano    = *((int32_t*)(msg_p + 16));
    out->fixType = *((uint8_t*)(msg_p + 20));
    out->flags   = *((uint8_t*)(msg_p + 21));
    out->flags2  = *((uint8_t*)(msg_p + 22));
    out->numSV   = *((uint8_t*)(msg_p + 23));
    out->lon     = *((int32_t*)(msg_p + 24));
    out->lat     = *((int32_t*)(msg_p + 28));
    out->height  = *((int32_t*)(msg_p + 32));
    out->hMSL    = *((int32_t*)(msg_p + 36));
    out->hAcc    = *((uint32_t*)(msg_p + 40));
    out->vAcc    = *((uint32_t*)(msg_p + 44));
    out->velN    = *((int32_t*)(msg_p + 48));
    out->velE    = *((int32_t*)(msg_p + 52));
    out->velD    = *((int32_t*)(msg_p + 56));
    out->gSpeed  = *((int32_t*)(msg_p + 60));
    out->headMot = *((int32_t*)(msg_p + 64));
    out->sAcc    = *((uint32_t*)(msg_p + 68));
    out->headAcc = *((uint32_t*)(msg_p + 72));
    out->pDop    = *((int32_t*)(msg_p + 76));
    out->headVeh = *((int32_t*)(msg_p + 84));
    out->magDec  = *((int16_t*)(msg_p + 88));
    out->magAcc  = *((uint16_t*)(msg_p + 90));
}

void construct_rxm_sfrbx_msg(struct UbxRxmSfrbxMsg* out, uint8_t* in)
{
    uint8_t  i;
    uint8_t* head_p = in;
    uint8_t* msg_p  = in + 2 + sizeof(struct UbxMsgHeader);

    out->ubx_header.msg_class  = *((uint8_t*)(head_p + 2));
    out->ubx_header.msg_id     = *((uint8_t*)(head_p + 3));
    out->ubx_header.msg_length = *((uint16_t*)(head_p + 4));

    out->gnssId    = *((uint8_t*)(msg_p + 0));
    out->svId      = *((uint8_t*)(msg_p + 1));
    out->reserved1 = *((uint8_t*)(msg_p + 2));
    out->freqId    = *((uint8_t*)(msg_p + 3));
    out->numWords  = *((uint8_t*)(msg_p + 4));
    out->reserved2 = *((uint8_t*)(msg_p + 5));
    out->version   = *((uint8_t*)(msg_p + 6));
    out->reserved3 = *((uint8_t*)(msg_p + 7));

    for (i = 0; i < out->numWords; i++)
    {
        out->dwrd[i] = *((uint32_t*)(msg_p + 8 + i * 4));
    }
}

/**
 * @brief Construct rxm rawx block message
 *
 * @param out Rxm rawx block message
 * @param in Ubx message content
 */
static void construct_rxm_rawx_block(struct RxmRawxBlock* out, uint8_t* in)
{
    out->pr_mes    = *((float64_t*)(in + 0));
    out->cp_mes    = *((float64_t*)(in + 8));
    out->do_mes    = *((float32_t*)(in + 16));
    out->gnss_id   = *((uint8_t*)(in + 20));
    out->sv_id     = *((uint8_t*)(in + 21));
    out->reserved2 = *((uint8_t*)(in + 22));
    out->freq_id   = *((uint8_t*)(in + 23));
    out->locktime  = *((uint16_t*)(in + 24));
    out->cno       = *((uint8_t*)(in + 26));
    out->pr_stdev  = *((uint8_t*)(in + 27));
    out->cp_stdev  = *((uint8_t*)(in + 28));
    out->do_stdev  = *((uint8_t*)(in + 29));
    out->trk_stat  = *((uint8_t*)(in + 30));
    out->reserved3 = *((uint8_t*)(in + 31));
}

void construct_rxm_rawx_msg(struct UbxRxmRawxMsg* out, uint8_t* in)
{
    uint8_t  i;
    uint8_t* head_p = in;
    uint8_t* msg_p  = in + 2 + sizeof(struct UbxMsgHeader);
    uint8_t* tmp_p  = msg_p;

    out->ubx_header.msg_class  = *((uint8_t*)(head_p + 2));
    out->ubx_header.msg_id     = *((uint8_t*)(head_p + 3));
    out->ubx_header.msg_length = *((uint16_t*)(head_p + 4));

    out->rcvTow       = *((float64_t*)(msg_p + 0));
    out->week         = *((uint16_t*)(msg_p + 8));
    out->leapS        = *((int8_t*)(msg_p + 10));
    out->numMeas      = *((uint8_t*)(msg_p + 11));
    out->recStat      = *((uint8_t*)(msg_p + 12));
    out->reserved1[0] = *((uint8_t*)(msg_p + 13));
    out->reserved1[1] = *((uint8_t*)(msg_p + 14));
    out->reserved1[2] = *((uint8_t*)(msg_p + 15));

    tmp_p = msg_p + 16;
    for (i = 0; i < out->numMeas; i++)
    {
        construct_rxm_rawx_block(&out->rxm_rawx_block[i], tmp_p);
        tmp_p += 32;
    }
}
