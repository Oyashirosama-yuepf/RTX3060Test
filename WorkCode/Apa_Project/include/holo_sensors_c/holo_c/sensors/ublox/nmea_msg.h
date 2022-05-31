/*!
 * @file nmea_msg.h
 * @brief This header file defines nmea message struct
 * @author liuya@holomatic.com
 * @date 2019-09-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_UBLOX_NMEA_MSG_H_
#define HOLO_C_SENSORS_UBLOX_NMEA_MSG_H_

#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 * @{
 *
 */

/**
 * @brief Define NMEA message class
 *
 */
enum NmeaMessageClass
{
    NMEA_MSG_CLASS_STD  = 0xF0,
    NMEA_MSG_CLASS_PUBX = 0xF1
};

/**
 * @brief Nmea message id
 *
 */
enum NmeaMessageId
{
    NMEA_MSG_ID_GGA = 0x00,
    NMEA_MSG_ID_GLL = 0x01,
    NMEA_MSG_ID_GSA = 0x02,
    NMEA_MSG_ID_GSV = 0x03,
    NMEA_MSG_ID_RMC = 0x04,
    NMEA_MSG_ID_VTG = 0x05,
    NMEA_MSG_ID_GRS = 0x06,
    NMEA_MSG_ID_GST = 0x07,
    NMEA_MSG_ID_ZDA = 0x08,
    NMEA_MSG_ID_GBS = 0x09,
    NMEA_MSG_ID_DTM = 0x0A,
    NMEA_MSG_ID_GNS = 0x0D,
    NMEA_MSG_ID_THS = 0x0E,
    NMEA_MSG_ID_VLW = 0x0F,
    NMEA_MSG_ID_GPQ = 0x40,
    NMEA_MSG_ID_TXT = 0x41,
    NMEA_MSG_ID_GNQ = 0x42,
    NMEA_MSG_ID_GLQ = 0x43,
    NMEA_MSG_ID_GBQ = 0x44,
};

#define NMEA_MAXSAT 12
#define NMEA_SATINPACK 4

/**
 * @brief Nmea satelite info
 *
 */
struct nmeaSATELLITE
{
    uint32_t id;       ///< Satellite PRN number
    uint32_t in_use;   ///< Used in position fix
    uint32_t elv;      ///< Elevation in degrees, 90 maximum
    uint32_t azimuth;  ///< Azimuth, degrees from true north, 000 to 359
    uint32_t sig;      ///< Signal, 00-99 dB
};
HOLO_STATIC_ASSERT(sizeof(struct nmeaSATELLITE) == 20);

/**
 * @brief Nmea time
 *
 */
struct nmeaTIME
{
    uint16_t year;  ///< Years since 1900
    uint8_t  mon;   ///< Months since January - [0,11]
    uint8_t  day;   ///< Day of the month - [1,31]
    uint8_t  hour;  ///< Hours since midnight - [0,23]
    uint8_t  min;   ///< Minutes after the hour - [0,59]
    uint8_t  sec;   ///< Seconds after the minute - [0,59]
    uint8_t  hsec;  ///< Hundredth part of second - [0,99]
};
HOLO_STATIC_ASSERT(sizeof(struct nmeaTIME) == 8);

/**
 * @brief Nmea gpgsa
 *
 */
struct GPGSAMsg
{
    uint8_t  fix_mode;              ///< Mode (M = Manual, forced to operate in 2D or 3D; A = Automatic, 3D/2D) */
    uint8_t  fix_type;              ///< Type, used for navigation (1 = Fix not available; 2 = 2D; 3 = 3D) */
    uint8_t  sat_prn[NMEA_MAXSAT];  ///< PRNs of satellites used in position fix (null for unused fields) */
    uint16_t reserved;

    float64_t PDOP;  ///< Dilution of precision */
    float64_t HDOP;  ///< Horizontal dilution of precision */
    float64_t VDOP;  ///< Vertical dilution of precision */
};
HOLO_STATIC_ASSERT(sizeof(struct GPGSAMsg) == 40);

/**
 * @brief Nmea gpgga
 *
 */
struct GPGGAMsg
{
    struct nmeaTIME utc;         ///< UTC of position (just time)
    uint8_t         ns;          ///< [N]orth or [S]outh
    uint8_t         ew;          ///< [E]ast or [W]est
    uint8_t         sig;         ///< GPS quality indicator (0 = Invalid; 1 = Fix; 2 = Differential, 3 = Sensitive)
    uint8_t         satinuse;    ///< Number of satellites in use (not those in view)
    uint8_t         elv_units;   ///< [M]eters (Antenna height unit)
    uint8_t         diff_units;  ///< [M]eters (Units of geoidal separation)
    uint8_t         dgps_sid;    ///< DGPS station ID number
    uint8_t         reserved;

    float64_t lat;   ///< Laitude in NDEG - [degree][min].[sec/60]
    float64_t lon;   ///< Longitude in NDEG - [degree][min].[sec/60]
    float64_t HDOP;  ///< Horizontal dilution of precision
    float64_t elv;   ///< Antenna altitude above/below mean sea level (geoid)
    float64_t diff;  ///< Geoidal separation (Diff. between WGS-84 earth ellipsoid and mean sea level. '-' = geoid is
                     ///< below WGS-84 ellipsoid)
    float64_t dgps_age;  ///< Time in seconds since last DGPS update
};
HOLO_STATIC_ASSERT(sizeof(struct GPGGAMsg) == 64);

/**
 * @brief Nmea gpgsv
 *
 */
struct GPGSVMsg
{
    uint8_t pack_count;  ///< Total number of messages of this type in this cycle
    uint8_t pack_index;  ///< Message number
    uint8_t sat_count;   ///< Total number of satellites in view
    uint8_t reserved;

    struct nmeaSATELLITE sat_data[NMEA_SATINPACK];
};
HOLO_STATIC_ASSERT(sizeof(struct GPGSVMsg) == 84);

/**
 * @brief Nme gprmc
 *
 */
struct GPRMCMsg
{
    struct nmeaTIME utc;

    uint8_t status;     ///< Status(A = active or V = void)
    uint8_t ns;         ///< [N]orth or [S]outh
    uint8_t ew;         ///< [E]ast or [W]est
    uint8_t declin_ew;  ///< [E]ast or [W]est
    uint8_t mode;  ///< (A = autonomous, D = differential, E = estimated, N = not valid, S = simulator)
    uint8_t reserved[3];  ///< For 4 bytes allign

    float64_t lat;          ///< Latitude in NDEG - [degree][min].[sec/60]
    float64_t lon;          ///< Longitude in NDEG - [degree][min].[sec/60]
    float64_t speed;        ///< Speed over the ground in knots
    float64_t direction;    ///< Track angle in degrees True
    float64_t declination;  ///< Magnetic variation degrees (Easterly var. subtracts from true course)
};
HOLO_STATIC_ASSERT(sizeof(struct GPRMCMsg) == 56);

/**
 * @brief Nmea gpvtg
 *
 */
struct GPVTGMsg
{
    uint8_t  dir_t; /**< Fixed text 'T' indicates that track made good is relative to true north */
    uint8_t  dec_m; /**< Fixed text 'M' */
    uint8_t  spn_n; /**< Fixed text 'N' indicates that speed over ground is in knots */
    uint8_t  spk_k; /**< Fixed text 'K' indicates that speed over ground is in kilometers/hour */
    uint32_t reserved;

    float64_t dir;  ///< True track made good (degrees)
    float64_t dec;  ///< Magnetic track made good
    float64_t spn;  ///< Ground speed, knots
    float64_t spk;  ///< Ground speed, kilometers per hour
};
HOLO_STATIC_ASSERT(sizeof(struct GPVTGMsg) == 40);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif  ///< HOLO_C_SENSORS_UBLOX_NMEA_MSG_H_
