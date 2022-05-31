/*!
 * @file ubx_msg.h
 * @brief This header file defines ubx message struct
 * @author liuya@holomatic.com
 * @date 2019-09-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_UBLOX_UBX_MSG_H_
#define HOLO_C_SENSORS_UBLOX_UBX_MSG_H_

#include <holo_c/common/timestamp.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RAWX_MAX_NUM 100
#define SFRBX_MAX_NUM 20

/**
 * @addtogroup sensors
 * @{
 *
 */

/**
 * @brief Define UBX message class
 *
 */
enum UbxMessageClass
{
    UBX_MSG_CLASS_NAV = 0x01,
    UBX_MSG_CLASS_RXM = 0x02,
    UBX_MSG_CLASS_INF = 0x04,
    UBX_MSG_CLASS_ACK = 0x05,
    UBX_MSG_CLASS_CFG = 0x06,
    UBX_MSG_CLASS_UPD = 0x09,
    UBX_MSG_CLASS_MON = 0x0A,
    UBX_MSG_CLASS_AID = 0x0B,
    UBX_MSG_CLASS_TIM = 0x0D,
    UBX_MSG_CLASS_ESF = 0x10,
    UBX_MSG_CLASS_MGA = 0x13,
    UBX_MSG_CLASS_LOG = 0x21,
    UBX_MSG_CLASS_SEC = 0x27,
    UBX_MSG_CLASS_HNR = 0x28

};

/**
 * @brief Define UBX message id
 *
 */
enum UbxMessageId
{
    UBX_MSG_ID_ACK_NAK      = 0x00,
    UBX_MSG_ID_ACK_ACK      = 0x01,
    UBX_MSG_ID_CFG_MSG      = 0x01,
    UBX_MSG_ID_CFG_RST      = 0x04,
    UBX_MSG_ID_CFG_RATE     = 0x08,
    UBX_MSG_ID_CFG_NMEA     = 0x17,
    UBX_MSG_ID_CFG_NAVX5    = 0x23,
    UBX_MSG_ID_CFG_NAV5     = 0x24,
    UBX_MSG_ID_CFG_ESFGAWT  = 0x2D,
    UBX_MSG_ID_CFG_ESFLA    = 0x2F,
    UBX_MSG_ID_CFG_ESFDWT   = 0x30,
    UBX_MSG_ID_CFG_TP5      = 0x31,
    UBX_MSG_ID_CFG_ESFTTAG  = 0x4B,
    UBX_MSG_ID_CFG_ESFA     = 0x4C,
    UBX_MSG_ID_CFG_ESFG     = 0x4D,
    UBX_MSG_ID_CFG_ESFALG   = 0x56,
    UBX_MSG_ID_CFG_HNR      = 0x5C,
    UBX_MSG_ID_CFG_ESFWT    = 0x82,
    UBX_MSG_ID_ESF_MEAS     = 0x02,
    UBX_MSG_ID_ESF_RAW      = 0x03,
    UBX_MSG_ID_ESF_STATUS   = 0x10,
    UBX_MSG_ID_ESF_RESETALG = 0x13,
    UBX_MSG_ID_ESF_ALG      = 0x14,
    UBX_MSG_ID_ESF_INS      = 0x15,
    UBX_MSG_ID_NAV_STATUS   = 0x03,
    UBX_MSG_ID_NAV_ATT      = 0x05,
    UBX_MSG_ID_NAV_SOL      = 0x06,
    UBX_MSG_ID_NAV_PVT      = 0x07,
    UBX_MSG_ID_NAV_VELNED   = 0x12,
    UBX_MSG_ID_NAV_TIMEGPS  = 0x20,
    UBX_MSG_ID_NAV_TIMEUTC  = 0x21,
    UBX_MSG_ID_NAV_SVINFO   = 0x30,
    UBX_MSG_ID_NAV_DGPS     = 0x31,
    UBX_MSG_ID_NAV_HNR      = 0x37,
    UBX_MSG_ID_HNR_PVT      = 0x00,
    UBX_MSG_ID_RXM_SFRBX    = 0x13,
    UBX_MSG_ID_RXM_RAWX     = 0x15
};

/**
 * @brief Sturct of configure ubx messages
 *
 */
struct UbxMsgCfg
{
    uint8_t classification;
    uint8_t id;
    uint8_t rate;
};
// HOLO_STATIC_ASSERT(sizeof(struct UbxMsgCfg) == 3);

/**
 * @brief Ubx message header
 *
 */
struct UbxMsgHeader
{
    uint8_t  msg_class;
    uint8_t  msg_id;
    uint16_t msg_length;
};
HOLO_STATIC_ASSERT(sizeof(struct UbxMsgHeader) == 4);

/**
 * @brief Ubx nav_pvt message struct
 *
 */
struct UbxNavPvtMsg
{
    struct UbxMsgHeader ubx_header;
    uint32_t            itow;   ///< GPS time of week of the navigation epoch
    uint16_t            year;   ///< Year (UTC)
    uint8_t             month;  ///< GMonth, range 1..12 (UTC)
    uint8_t             day;    ///< Day of month, range 1..31 (UTC)
    uint8_t             hour;   ///< Hour of day, range 0..23 (UTC)
    uint8_t             min;    ///< Minute of hour, range 0..59 (UTC)
    uint8_t             sec;    ///< Seconds of minute, range 0..60 (UTC)
    uint8_t             valid;  ///< Validity flags
    uint32_t            tAcc;   ///< Time accuracy estimate (UTC)
    int32_t             nano;   ///< Fraction of second, range -1e9 .. 1e9 (UTC)
    uint8_t fixType;   ///< GNSSfix Type:0: no fix 1: dead reckoning only 2: 2D-fix 3: 3D-fix 4: GNSS + dead reckoning
                       ///< combined 5: time only fix
    uint8_t  flags;    ///< Fix status flags
    uint8_t  flags2;   ///< Additional flags
    uint8_t  numSV;    ///< Number of satellites used in Nav Solution
    int32_t  lon;      ///< Longitude
    int32_t  lat;      ///< Latitude
    int32_t  height;   ///< Height above ellipsoid
    int32_t  hMSL;     ///< Height above mean sea level
    uint32_t hAcc;     ///< Horizontal accuracy estimate
    uint32_t vAcc;     ///< Vertical accuracy estimate
    int32_t  velN;     ///< NED north velocity
    int32_t  velE;     ///< NED east velocity
    int32_t  velD;     ///< NED down velocity
    int32_t  gSpeed;   ///< Ground Speed (2-D)
    int32_t  headMot;  ///< Heading of motion (2-D)
    uint32_t sAcc;     ///< Speed accuracy estimate
    uint32_t headAcc;  ///< Heading accuracy estimate (both motion and vehicle)
    uint16_t pDop;     ///< Position Dop
    uint8_t  reserved1[6];
    int32_t  headVeh;  ///< Heading of vehicle (2-D)
    int16_t  magDec;   ///< Magnetic declination
    uint16_t magAcc;   ///< Magnetic declination accuracy
};
HOLO_STATIC_ASSERT(sizeof(struct UbxNavPvtMsg) == 96);

/**
 * @brief Ubx rxm_rawx block message struct
 *
 */
struct RxmRawxBlock
{
    float64_t pr_mes;   ///< Pseudorange measurement
    float64_t cp_mes;   ///< Carrier phase measurement
    float32_t do_mes;   ///< Doppler measurement
    uint8_t   gnss_id;  ///< GNSS identifier
    uint8_t   sv_id;    ///< Satellite identifier
    uint8_t   reserved2;
    uint8_t   freq_id;   ///< Only used for GLONASS
    uint16_t  locktime;  ///< Carrier phase locktime counter
    uint8_t   cno;       ///< Carrier-to-noise density ratio
    uint8_t   pr_stdev;  ///< Estimated pseudorange measurement standard deviation
    uint8_t   cp_stdev;  ///< Estimated carrier phase measurement standard deviation
    uint8_t   do_stdev;  ///< Estimated Doppler measurement standard deviation
    uint8_t   trk_stat;  ///< Tracking status bitfield
    uint8_t   reserved3;
};
HOLO_STATIC_ASSERT(sizeof(struct RxmRawxBlock) == 32);

/**
 * @brief Ubx rxm_rawx message struct
 *
 */
struct UbxRxmRawxMsg
{
    struct UbxMsgHeader ubx_header;
    float64_t           rcvTow;   ///< Measurement time of week
    uint16_t            week;     ///< GPS week number
    int8_t              leapS;    ///< GPS leap seconds
    uint8_t             numMeas;  ///< Number of measurements to follow
    uint8_t             recStat;  ///< Receiver tracking status bitfield
    uint8_t             reserved1[3];
    struct RxmRawxBlock rxm_rawx_block[RAWX_MAX_NUM];
};
// HOLO_STATIC_ASSERT(sizeof(struct UbxRxmRawxMsg) == 3224);

/**
 * @brief Ubx rxm_sfrbx message struct
 *
 */
struct UbxRxmSfrbxMsg
{
    struct UbxMsgHeader ubx_header;
    uint8_t             gnssId;  ///< GNSS identifier
    uint8_t             svId;    ///< Satellite identifier
    uint8_t             reserved1;
    uint8_t             freqId;    ///< Only used for GLONASS: This is the frequency slot + 7
    uint8_t             numWords;  ///< The number of data words contained in this message
    uint8_t             reserved2;
    uint8_t             version;  ///< Message version
    uint8_t             reserved3;
    uint32_t            dwrd[SFRBX_MAX_NUM];  ///< The data words
};
HOLO_STATIC_ASSERT(sizeof(struct UbxRxmSfrbxMsg) == 92);

/**
 * @brief Ubx nav_pvt message + header
 *
 */
struct UbxNavPvtMessage
{
    struct Timestamp    timestamp;
    struct UbxNavPvtMsg message;
};

/**
 * @brief Ubx rxm_rawx message + header
 *
 */
struct UbxRxmRawxMessage
{
    struct Timestamp     timestamp;
    struct UbxRxmRawxMsg message;
};

/**
 * @brief Ubx rxm_sfrbx message + header
 *
 */
struct UbxRxmSfrbxMessage
{
    struct Timestamp      timestamp;
    struct UbxRxmSfrbxMsg message;
};

/**
 * @brief Construct rxm rawx message
 *
 * @param out Rxm rawx message
 * @param in Ubx message content
 */
void construct_rxm_rawx_msg(struct UbxRxmRawxMsg* out, uint8_t* in);

/**
 * @brief Construct rxm sfrbx message
 *
 * @param out Rxm sfrbx message
 * @param in Ubx message content
 */
void construct_rxm_sfrbx_msg(struct UbxRxmSfrbxMsg* out, uint8_t* in);

/**
 * @brief Construct nav pvt message
 *
 * @param out Nav pvt message
 * @param in Ubx message content buffer
 */
void construct_nav_pvt_msg(struct UbxNavPvtMsg* out, uint8_t* in);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_SENSORS_UBLOX_UBX_MSG_H_
