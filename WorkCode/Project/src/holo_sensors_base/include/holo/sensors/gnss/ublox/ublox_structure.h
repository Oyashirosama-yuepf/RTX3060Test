/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ublox_structure.h
 * @brief This structure file define the data of ublox ark
 * @author houyujian@holomatic.com
 * @date Dec 12, 2019
 */

#ifndef _HOLO_SENSORS_GNSS_UBLOX_UBLOX_STRUCTURE_H
#define _HOLO_SENSORS_GNSS_UBLOX_UBLOX_STRUCTURE_H

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/os/endian.h>
#include <holo_c/core/static_assert.h>
#include <string>

#ifndef HOLO_PLATFORM_LITTLE_ENDIAN
#error "Ublox structures are based on little-endian machines, please check it out."
#endif

namespace holo
{
namespace sensors
{
namespace ublox
{
static const uint32_t SEC_PER_WEEK     = 604800;  //! seconds per week
static const uint16_t GPS_WEEK_MINIMAL = 2010;    //! 2020-04-05 gps week is 2100

enum PvtFixType : uint8_t
{
    NO_FIX = 0x00,
    FIX_2D = 0x02,
    FIX_3D = 0x03
};

enum class UbxMessageType : uint8_t
{
    /* ubx */
    UBX_NAV = 0x01,
    UBX_RXM = 0x02,
    UBX_INF = 0x04,
    UBX_ACK = 0x05,
    UBX_CFG = 0x06,
    UBX_UPD = 0x09,
    UBX_MON = 0x0A,
    UBX_AID = 0x0B,
    UBX_TIM = 0x0D,
    UBX_ESF = 0x10,
    UBX_MGA = 0x13,
    UBX_LOG = 0x21,
    UBX_SEC = 0x27,
    UBX_HNR = 0x28,

    /* nmea */
    NMEA_STD  = 0xF0,
    NMEA_PUBX = 0xF1,
};

enum class UbxNmeaStdType : uint8_t
{
    NMEA_STD_GGA = 0x00,
    NMEA_STD_GLL = 0x01,
    NMEA_STD_GSA = 0x02,
    NMEA_STD_GSV = 0x03,
    NMEA_STD_RMC = 0x04,
    NMEA_STD_VTG = 0x05,
    NMEA_STD_GRS = 0x06,
    NMEA_STD_GST = 0x07,
    NMEA_STD_ZDA = 0x08,
    NMEA_STD_GBS = 0x09,
    NMEA_STD_DTM = 0x0A,
    NMEA_STD_GNS = 0x0D,
    NMEA_STD_THS = 0x0E,
    NMEA_STD_VLW = 0x0F,
    NMEA_STD_GPQ = 0x40,
    NMEA_STD_TXT = 0x41,
    NMEA_STD_GNQ = 0x42,
    NMEA_STD_GLQ = 0x43,
    NMEA_STD_GBQ = 0x44,
};

enum class UbxAckType : uint8_t
{
    ACK_NAK = 0x00,
    ACK_ACK = 0x01,
};

enum class UbxEsfType : uint8_t
{
    ESF_MEAS     = 0x02,
    ESF_RAW      = 0x03,
    ESF_STATUS   = 0x10,
    ESF_RESETALG = 0x13,
    ESF_ALG      = 0x14,
    ESF_INS      = 0x15,
};

enum class UbxHnrType : uint8_t
{
    HNR_PVT = 0x00
};

enum class UbxNavType : uint8_t
{
    NAV_AOPSTATUS = 0x60,
    NAV_ATT       = 0x05,
    NAV_CLOCK     = 0x22,
    NAV_DGPS      = 0x31,
    NAV_DOP       = 0x04,
    NAV_EOE       = 0x61,
    NAV_GEOFENCE  = 0x39,
    NAV_HPPOSECEF = 0x13,
    NAV_HPPOSLLH  = 0x14,
    NAV_ODO       = 0x09,
    NAV_ORB       = 0x34,
    NAV_POSECEF   = 0x01,
    NAV_POSLLH    = 0x02,
    NAV_PVT       = 0x07,
    NAV_RELPOSNED = 0x3C,
    NAV_RESETODO  = 0x10,
    NAV_SAT       = 0x35,
    NAV_SBAS      = 0x32,
    NAV_SOL       = 0x06,
    NAV_STATUS    = 0x03,
    NAV_SVINFO    = 0x30,
    NAV_SVIN      = 0x3B,
    NAV_TIMEBDS   = 0x24,
    NAV_TIMEGAL   = 0x25,
    NAV_TIMEGLO   = 0x23,
    NAV_TIMEGPS   = 0x20,
    NAV_TIMELS    = 0x26,
    NAV_TIMEUTC   = 0x21,
    NAV_VELECEF   = 0x11,
    NAV_VELNED    = 0x12,
};

enum class UbxRxmType : uint8_t
{
    RXM_IMES  = 0x61,
    RXM_MEASX = 0x14,
    RXM_PMREQ = 0x41,
    RXM_RAWX  = 0x15,
    RXM_RLM   = 0x59,
    RXM_RTCM  = 0x32,
    RXM_SFRBX = 0x13,
    RXM_SVSI  = 0x20,
};

struct UbxNavPvtMessage
{
    UbxNavPvtMessage()
      : itow()
      , year()
      , month()
      , day()
      , hour()
      , min()
      , sec()
      , valid()
      , tAcc()
      , nano()
      , fixType()
      , flags()
      , flags2()
      , numSV()
      , lon()
      , lat()
      , height()
      , hMSL()
      , hAcc()
      , vAcc()
      , velN()
      , velE()
      , velD()
      , gSpeed()
      , headMot()
      , sAcc()
      , headAcc()
      , pDop()
      , reserved1{}
      , headVeh()
      , magDec()
      , magAcc()
    {
    }

    uint32_t itow;          //! GPS time of week of the navigation epoch
    uint16_t year;          //! Year (UTC)
    uint8_t  month;         //! GMonth, range 1..12 (UTC)
    uint8_t  day;           //! Day of month, range 1..31 (UTC)
    uint8_t  hour;          //! Hour of day, range 0..23 (UTC)
    uint8_t  min;           //! Minute of hour, range 0..59 (UTC)
    uint8_t  sec;           //! Seconds of minute, range 0..60 (UTC)
    uint8_t  valid;         //! Validity flags
    uint32_t tAcc;          //! Time accuracy estimate (UTC)
    int32_t  nano;          //! Fraction of second, range -1e9 .. 1e9 (UTC)
    uint8_t  fixType;       //! GNSSfix Type: 0: no fix 1: dead reckoning only 2: 2D-fix 3: 3D-fix
                            //!               4: GNSS + dead reckoning combined 5: time only fix
    uint8_t  flags;         //! Fix status flags
    uint8_t  flags2;        //! Additional flags
    uint8_t  numSV;         //! Number of satellites used in Nav Solution
    int32_t  lon;           //! Longitude
    int32_t  lat;           //! Latitude
    int32_t  height;        //! Height above ellipsoid
    int32_t  hMSL;          //! Height above mean sea level
    uint32_t hAcc;          //! Horizontal accuracy estimate
    uint32_t vAcc;          //! Vertical accuracy estimate
    int32_t  velN;          //! NED north velocity
    int32_t  velE;          //! NED east velocity
    int32_t  velD;          //! NED down velocity
    int32_t  gSpeed;        //! Ground Speed (2-D)
    int32_t  headMot;       //! Heading of motion (2-D)
    uint32_t sAcc;          //! Speed accuracy estimate
    uint32_t headAcc;       //! Heading accuracy estimate (both motion and vehicle)
    uint16_t pDop;          //! Position Dop
    uint8_t  reserved1[6];  //! reserved
    int32_t  headVeh;       //! Heading of vehicle (2-D)
    int16_t  magDec;        //! Magnetic declination
    uint16_t magAcc;        //! Magnetic declination accuracy

    uint32_t Deserialize(const uint8_t* data, uint32_t size)
    {
        if (size < sizeof(struct UbxNavPvtMessage))
        {
            return 0;
        }
        (void)std::memcpy(this, data, sizeof(struct UbxNavPvtMessage));
        return sizeof(struct UbxNavPvtMessage);
    }
};
HOLO_STATIC_ASSERT(sizeof(struct UbxNavPvtMessage) == 92);

struct UbxRxmRawxMessageHeader
{
    UbxRxmRawxMessageHeader() : rcvTow(), week(), leapS(), numMeas(), recStat(), reserved1{}
    {
    }

    float64_t rcvTow;        //! Measurement time of week
    uint16_t  week;          //! GPS week number
    int8_t    leapS;         //! GPS leap seconds
    uint8_t   numMeas;       //! Number of measurements to follow
    uint8_t   recStat;       //! Receiver tracking status bitfield
    uint8_t   reserved1[3];  //! reserved

    uint32_t Deserialize(const uint8_t* data, uint32_t size)
    {
        if (size < sizeof(struct UbxRxmRawxMessageHeader))
        {
            return 0;
        }
        (void)std::memcpy(this, data, sizeof(struct UbxRxmRawxMessageHeader));
        return sizeof(struct UbxRxmRawxMessageHeader);
    }
};
HOLO_STATIC_ASSERT(sizeof(struct UbxRxmRawxMessageHeader) == 16);

struct UbxRxmRawxMessageBlock
{
    UbxRxmRawxMessageBlock()
      : pr_mes()
      , cp_mes()
      , do_mes()
      , gnss_id()
      , sv_id()
      , reserved2()
      , freq_id()
      , locktime()
      , cno()
      , pr_stdev()
      , cp_stdev()
      , do_stdev()
      , trk_stat()
      , reserved3()
    {
    }

    float64_t pr_mes;     //! Pseudorange measurement
    float64_t cp_mes;     //! Carrier phase measurement
    float32_t do_mes;     //! Doppler measurement
    uint8_t   gnss_id;    //! GNSS identifier
    uint8_t   sv_id;      //! Satellite identifier
    uint8_t   reserved2;  //! reserved
    uint8_t   freq_id;    //! Only used for GLONASS
    uint16_t  locktime;   //! Carrier phase locktime counter
    uint8_t   cno;        //! Carrier-to-noise density ratio
    uint8_t   pr_stdev;   //! Estimated pseudorange measurement standard deviation
    uint8_t   cp_stdev;   //! Estimated carrier phase measurement standard deviation
    uint8_t   do_stdev;   //! Estimated Doppler measurement standard deviation
    uint8_t   trk_stat;   //! Tracking status bitfield
    uint8_t   reserved3;  //! reserved

    uint32_t Deserialize(const uint8_t* data, uint32_t size)
    {
        if (size < sizeof(struct UbxRxmRawxMessageBlock))
        {
            return 0;
        }
        (void)std::memcpy(this, data, sizeof(struct UbxRxmRawxMessageBlock));
        return sizeof(struct UbxRxmRawxMessageBlock);
    }
};
HOLO_STATIC_ASSERT(sizeof(struct UbxRxmRawxMessageBlock) == 32);

}  // namespace ublox
}  // namespace sensors
}  // namespace holo

#endif
