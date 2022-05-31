/*!
 * @file ubx_parse.c
 * @brief This source file defines ubx message parse functions
 * @author liuya@holomatic.com
 * @date 2019-09-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo_c/core/retcode.h>
#include <holo_c/sensors/ublox/ubx_parse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Ubx parse message state machine overflow handle
 *
 * @param parser Ubx message parse state machine pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t ubx_parser_handle_overflow(struct UbxParser* parser)
{
    parser->state = UBX_PARSE_OUTOFSYNC;

    return RC_UBX_RECV_BUFFER_OVERFLOW;
}

retcode_t ubx_parser_handle_outofsync(struct UbxParser* parser)
{
    parser->offset  = 0;
    parser->state   = UBX_PARSE_HEAD;
    parser->exp_len = 2;

    memset(parser->buf_base, 0, parser->buf_size);

    return RC_UBX_PARSER_OUTOFSYNC;
}

retcode_t ubx_parser_parse_head(struct UbxParser* parser, uint8_t** msg, uint32_t* len)
{
    retcode_t rc;

    if (*len < parser->exp_len)
    {
        if (parser->offset + *len > parser->buf_size)
        {
            rc = ubx_parser_handle_overflow(parser);
        }
        else
        {
            rc = RC_UBX_PARSE_HEAD_CONTINUE;
            memcpy(parser->buf_base + parser->offset, *msg, *len);

            parser->exp_len -= *len;
            parser->offset += *len;

            *msg += *len;
            *len -= *len;
        }
    }
    else
    {
        if (parser->offset + parser->exp_len > parser->buf_size)
        {
            rc = ubx_parser_handle_overflow(parser);
        }
        else
        {
            memcpy(parser->buf_base + parser->offset, *msg, parser->exp_len);
            *msg += parser->exp_len;
            *len -= parser->exp_len;
            parser->offset += parser->exp_len;
            parser->exp_len -= parser->exp_len;

            if (parser->buf_base[0] == 0xB5 && parser->buf_base[1] == 0x62)
            {
                rc              = RC_UBX_PARSE_HEAD_COMPLETE;
                parser->state   = UBX_PARSE_CLASS_ID;
                parser->exp_len = 2;
            }
            else
            {
                rc            = RC_UBX_PARSER_OUTOFSYNC;
                parser->state = UBX_PARSE_OUTOFSYNC;
            }
        }
    }
    return rc;
}

retcode_t ubx_parser_parse_class_id(struct UbxParser* parser, uint8_t** msg, uint32_t* len)
{
    retcode_t rc;

    if (*len < parser->exp_len)
    {
        if (parser->offset + *len > parser->buf_size)
        {
            rc = ubx_parser_handle_overflow(parser);
        }
        else
        {
            rc = RC_UBX_PARSE_ID_CONTINUE;
            memcpy(parser->buf_base + parser->offset, *msg, *len);

            parser->exp_len -= *len;
            parser->offset += *len;

            *msg += *len;
            *len -= *len;
        }
    }
    else
    {
        if (parser->offset + parser->exp_len > parser->buf_size)
        {
            rc = ubx_parser_handle_overflow(parser);
        }
        else
        {
            memcpy(parser->buf_base + parser->offset, *msg, parser->exp_len);
            *msg += parser->exp_len;
            *len -= parser->exp_len;
            parser->offset += parser->exp_len;
            parser->exp_len -= parser->exp_len;

            rc              = RC_UBX_PARSE_ID_COMPLETE;
            parser->state   = UBX_PARSE_LENGTH;
            parser->exp_len = 2;
        }
    }
    return rc;
}

retcode_t ubx_parser_parse_len(struct UbxParser* parser, uint8_t** msg, uint32_t* len)
{
    uint16_t msg_len;

    retcode_t rc;

    if (*len < parser->exp_len)
    {
        if (parser->offset + *len > parser->buf_size)
        {
            rc = ubx_parser_handle_overflow(parser);
        }
        else
        {
            rc = RC_UBX_PARSE_LEN_CONTINUE;
            memcpy(parser->buf_base + parser->offset, *msg, *len);

            parser->exp_len -= *len;
            parser->offset += *len;

            *msg += *len;
            *len -= *len;
        }
    }
    else
    {
        if (parser->offset + parser->exp_len > parser->buf_size)
        {
            rc = ubx_parser_handle_overflow(parser);
        }
        else
        {
            memcpy(parser->buf_base + parser->offset, *msg, parser->exp_len);
            *msg += parser->exp_len;
            *len -= parser->exp_len;

            rc            = RC_UBX_PARSE_LEN_COMPLETE;
            parser->state = UBX_PARSE_PAYLOAD;

            memcpy(&msg_len, parser->buf_base + parser->offset, parser->exp_len);
            parser->offset += parser->exp_len;
            parser->exp_len = msg_len;
        }
    }
    return rc;
}

retcode_t ubx_parser_parse_payload(struct UbxParser* parser, uint8_t** msg, uint32_t* len)
{
    retcode_t rc;

    if (*len < parser->exp_len)
    {
        if (parser->offset + *len > parser->buf_size)
        {
            rc = ubx_parser_handle_overflow(parser);
        }
        else
        {
            rc = RC_UBX_PARSE_PAYLOAD_CONTINUE;
            memcpy(parser->buf_base + parser->offset, *msg, *len);

            parser->exp_len -= *len;
            parser->offset += *len;

            *msg += *len;
            *len -= *len;
        }
    }
    else
    {
        if (parser->offset + parser->exp_len > parser->buf_size)
        {
            rc = ubx_parser_handle_overflow(parser);
        }
        else
        {
            memcpy(parser->buf_base + parser->offset, *msg, parser->exp_len);
            *msg += parser->exp_len;
            *len -= parser->exp_len;
            parser->offset += parser->exp_len;
            parser->exp_len -= parser->exp_len;

            rc              = RC_UBX_PARSE_PAYLOAD_COMPLETE;
            parser->state   = UBX_PARSE_CK;
            parser->exp_len = 2;
        }
    }
    return rc;
}

retcode_t ubx_parser_parse_ck(struct UbxParser* parser, uint8_t** msg, uint32_t* len)
{
    uint16_t msg_len;
    uint8_t  cal_ck_a, cal_ck_b;
    uint8_t  rcv_ck_a, rcv_ck_b;

    retcode_t rc;

    if (*len < parser->exp_len)
    {
        if (parser->offset + *len > parser->buf_size)
        {
            rc = ubx_parser_handle_overflow(parser);
        }
        else
        {
            rc = RC_UBX_PARSE_CRC_CONTINUE;
            memcpy(parser->buf_base + parser->offset, *msg, *len);

            parser->exp_len -= *len;
            parser->offset += *len;

            *msg += *len;
            *len -= *len;
        }
    }
    else
    {
        if (parser->offset + parser->exp_len > parser->buf_size)
        {
            rc = ubx_parser_handle_overflow(parser);
        }
        else
        {
            memcpy(parser->buf_base + parser->offset, *msg, parser->exp_len);
            *msg += parser->exp_len;
            *len -= parser->exp_len;
            parser->offset += parser->exp_len;
            parser->exp_len -= parser->exp_len;

            rcv_ck_a = *(parser->buf_base + parser->offset - 2);
            rcv_ck_b = *(parser->buf_base + parser->offset - 1);

            memcpy(&msg_len, parser->buf_base + 4, 2);
            msg_len += 4;

            ubx_calculate_ck(parser->buf_base + 2, msg_len, &cal_ck_a, &cal_ck_b);

            if (rcv_ck_a != cal_ck_a || rcv_ck_b != cal_ck_b)
            {
                rc = RC_UBX_PARSE_CRC_ERROR;
            }
            else
            {
                rc = RC_UBX_PARSE_CRC_OK;
            }

            parser->exp_len = 0;
        }
    }
    return rc;
}
