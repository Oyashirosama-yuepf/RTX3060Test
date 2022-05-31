/*!
 * @file ublox_parse.h
 * @brief This header file defines ubx message parse functions
 * @author liuya@holomatic.com
 * @date 2019-09-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_UBLOX_UBX_PARSE_H_
#define HOLO_C_SENSORS_UBLOX_UBX_PARSE_H_

#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
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
 * @brief State machine states for parsing ubx message
 *
 */
enum UbxParserState
{
    UBX_PARSE_HEAD,
    UBX_PARSE_CLASS_ID,
    UBX_PARSE_LENGTH,
    UBX_PARSE_PAYLOAD,
    UBX_PARSE_CK,
    UBX_PARSE_OUTOFSYNC,
};

/**
 * @brief State machine for ubx message parsing
 *
 */
struct UbxParser
{
    uint8_t* buf_base;

    uint16_t            exp_len;
    uint16_t            buf_size;
    uint16_t            offset;
    enum UbxParserState state;
};

/**
 * @brief Calculate crc of sending messages
 *
 * @param data Message content
 * @param data_length Message length
 * @param ck_a CRC part a
 * @param ck_b CRC part b
 */
void ubx_calculate_ck(const uint8_t* data, uint32_t data_length, uint8_t* ck_a, uint8_t* ck_b);

/**
 * @brief Ubx parse message state machine overflow handle
 *
 * @param parser Ubx message parse state machine pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t ubx_parser_handle_overflow(struct UbxParser* parser);

/**
 * @brief Ubx parse message state machine out of sync handle
 *
 * @param parser Ubx message parse state machine pointer
 * @return retcode_t RC_UBX_PARSER_OUTOFSYNC
 */
retcode_t ubx_parser_handle_outofsync(struct UbxParser* parser);

/**
 * @brief Parse ubx message header
 *
 * @param parser Ubx message parse state machine pointer
 * @param msg Ubx message content
 * @param len Ubx message length
 * @return retcode_t Parse status
 */
retcode_t ubx_parser_parse_head(struct UbxParser* parser, uint8_t** msg, uint32_t* len);

/**
 * @brief Parse ubx message class id
 *
 * @param parser Ubx message parse state machine pointer
 * @param msg Ubx message content
 * @param len Ubx message length
 * @return retcode_t Parse status
 */
retcode_t ubx_parser_parse_class_id(struct UbxParser* parser, uint8_t** msg, uint32_t* len);

/**
 * @brief Ubx message parse length
 *
 * @param parser Ubx message parse state machine pointer
 * @param msg Ubx message content
 * @param len Ubx message length
 * @return retcode_t Parse status
 */
retcode_t ubx_parser_parse_len(struct UbxParser* parser, uint8_t** msg, uint32_t* len);

/**
 * @brief Ubx message parse payload
 *
 * @param parser Ubx message parse state machine pointer
 * @param msg Ubx message content
 * @param len Ubx message length
 * @return retcode_t Parse status
 */
retcode_t ubx_parser_parse_payload(struct UbxParser* parser, uint8_t** msg, uint32_t* len);

/**
 * @brief Ubx message parse ck
 *
 * @param parser Ubx message parse state machine pointer
 * @param msg Ubx message content
 * @param len Ubx message length
 * @return retcode_t Parse status
 */
retcode_t ubx_parser_parse_ck(struct UbxParser* parser, uint8_t** msg, uint32_t* len);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_SENSORS_UBLOX_UBX_PARSE_H_
