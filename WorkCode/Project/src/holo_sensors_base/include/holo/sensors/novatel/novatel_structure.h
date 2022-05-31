/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file novatel_structure.h
 * @brief This structure file define the data of novatel
 * @author houyujian@holomatic.com
 * @date Dec 03, 2019
 */

#ifndef _HOLO_SENSORS_NOVATEL_NOVATEL_STRUCTURE_H
#define _HOLO_SENSORS_NOVATEL_NOVATEL_STRUCTURE_H

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/os/endian.h>
#include <holo_c/core/static_assert.h>

#include <map>
#include <string>

#ifndef HOLO_PLATFORM_LITTLE_ENDIAN
#error "novatel structures are based on little-endian machines, fix it if the target machine is big-endian."
#endif

namespace holo
{
namespace sensors
{
namespace novatel
{
static const uint8_t SYNC_BYTE_1       = 0xAA;
static const uint8_t SYNC_BYTE_2       = 0x44;
static const uint8_t SYNC_BYTE_3       = 0x12;
static const uint8_t SYNC_BYTE_3_SHORT = 0x13;

static const uint8_t IMU_TYPE_FSAS     = 13;
static const uint8_t IMU_TYPE_CPT      = 16;
static const uint8_t IMU_TYPE_A1       = 31;
static const uint8_t IMU_TYPE_S1       = 32;
static const uint8_t IMU_TYPE_EPSON370 = 61;

static const float64_t FSAS_GYROSCOPE_SCALE_FACTOR      = 3.7876E-7;
static const float64_t FSAS_GYROSCOPE_BIAS_STABILITY    = 3.634E-6;
static const float64_t FSAS_ACCELERATION_SCALE_FACTOR   = 3.0518E-4;
static const float64_t FSAS_ACCELERATION_BIAS_STABILITY = 1E-3;

static const float64_t CPT_GYROSCOPE_SCALE_FACTOR      = 1.0851E-5;
static const float64_t CPT_GYROSCOPE_BIAS_STABILITY    = 4.864E-6;
static const float64_t CPT_ACCELERATION_SCALE_FACTOR   = 1.52588E-4;
static const float64_t CPT_ACCELERATION_BIAS_STABILITY = 7.5E-3;

static const float64_t STIM_GYROSCOPE_SCALE_FACTOR      = 1.0403E-6;
static const float64_t STIM_GYROSCOPE_BIAS_STABILITY    = 2.432E-6;
static const float64_t STIM_ACCELERATION_SCALE_FACTOR   = 2.9802E-5;
static const float64_t STIM_ACCELERATION_BIAS_STABILITY = 1E-3;

static const float64_t A1_GYROSCOPE_SCALE_FACTOR      = 1.17033E-6;
static const float64_t A1_GYROSCOPE_BIAS_STABILITY    = 2.432E-6;
static const float64_t A1_ACCELERATION_SCALE_FACTOR   = 1.862645E-5;
static const float64_t A1_ACCELERATION_BIAS_STABILITY = 1E-3;

static const float64_t EPSON370_GYROSCOPE_SCALE_FACTOR      = 4.0348E-9;
static const float64_t EPSON370_GYROSCOPE_BIAS_STABILITY    = 3.878E-6;
static const float64_t EPSON370_ACCELERATION_SCALE_FACTOR   = 5.9875E-8;
static const float64_t EPSON370_ACCELERATION_BIAS_STABILITY = 9.8E-5;

struct NovatelImuParameters
{
    float64_t gyro_factor;
    float64_t gyro_noise_density;
    float64_t accl_factor;
    float64_t accl_noise_density;
};

static const std::map<uint8_t, NovatelImuParameters> IMU_PARAMS_MAP{
    {IMU_TYPE_FSAS,
     {FSAS_GYROSCOPE_SCALE_FACTOR, FSAS_GYROSCOPE_BIAS_STABILITY, FSAS_ACCELERATION_SCALE_FACTOR,
      FSAS_ACCELERATION_BIAS_STABILITY}},
    {IMU_TYPE_CPT,
     {CPT_GYROSCOPE_SCALE_FACTOR, CPT_GYROSCOPE_BIAS_STABILITY, CPT_ACCELERATION_SCALE_FACTOR,
      CPT_ACCELERATION_BIAS_STABILITY}},
    {IMU_TYPE_A1,
     {A1_GYROSCOPE_SCALE_FACTOR, A1_GYROSCOPE_BIAS_STABILITY, A1_ACCELERATION_SCALE_FACTOR,
      A1_ACCELERATION_BIAS_STABILITY}},
    {IMU_TYPE_S1,
     {STIM_GYROSCOPE_SCALE_FACTOR, STIM_GYROSCOPE_BIAS_STABILITY, STIM_ACCELERATION_SCALE_FACTOR,
      STIM_ACCELERATION_BIAS_STABILITY}},
    {IMU_TYPE_EPSON370,
     {EPSON370_GYROSCOPE_SCALE_FACTOR, EPSON370_GYROSCOPE_BIAS_STABILITY, EPSON370_ACCELERATION_SCALE_FACTOR,
      EPSON370_ACCELERATION_BIAS_STABILITY}}};

enum BinaryLogId : uint32_t
{
    // GNSS RECEIVER
    BESTPOSB_LOG = 42, /* GNSS position */
    // SPAN - INS specific logs
    CORRIMU_LOG  = 812,  /* IMU corrected data */
    INSCOVS_LOG  = 320,  /* INSCOV with short header */
    INSPVAS_LOG  = 508,  /* INS POSITION, VELOCITY, AND ATTITUDE short header */
    RAWIMUSX_LOG = 1462, /* RAWIMUS, but with extended status */
};

enum BinaryMesgLen : uint32_t
{
    MESG_HEAD_LEN                = 6,
    MESG_INSCOVS_LEN             = 244,
    MESG_RAWIMUSX_LEN            = 56,
    MESG_BESTPOSB_OR_INSPVAS_LEN = 104,
    MESG_ERROR_226_LEN           = 226,
    MESG_ERROR_219_LEN           = 219,
    MESG_ERROR_7_LEN             = 7,
};

enum InspvaStatus : uint32_t
{
    INS_INACTIVE            = 0, /* INS is inactive. */
    INS_ALIGNING            = 1, /* INS is in alignment mode */
    INS_HIGH_VARIANCE       = 2, /* The INS solution is in navigation mode */
    INS_SOLUTION_GOOD       = 3, /* INS solution is good */
    INS_SOLUTION_FREE       = 6, /* GNSS solution is suspected to be in error */
    INS_ALIGNMENT_COMPLETE  = 7, /* The INS filter is in navigation mode */
    DETERMINING_ORIENTATION = 8, /* INS is determining the IMU axis aligned with gravity */
    WAITING_INITIALPOS      = 9, /* The INS filter has determined the IMU orientation */
};

enum PositionType : uint32_t
{
    SINGLE     = 16, /* Single point position */
    PSRDIFF    = 17, /* Pseudorange differential solution */
    WAAS       = 18, /* Solution calculated using corrections from an SBAS */
    PROPAGATED = 19, /* Propagated by a Kalman filter without new observations */

    L1_FLOAT       = 32, /* Floating L1 ambiguity solution */
    IONOFREE_FLOAT = 33, /* Floating ionospheric-free ambiguity solution */
    NARROW_FLOAT   = 34, /* Floating narrow-lane ambiguity solution */

    L1_INT         = 48, /* Integer L1 ambiguity solution */
    WIDE_INT       = 49, /* Integer wide-lane ambiguity solution */
    NARROW_INT     = 50, /* Integer narrow-lane ambiguity solution */
    RTK_DIRECT_INS = 51, /* RTK status where the RTK filter is directly initialized from the INS filter */
    INS_SBAS       = 52, /* INS calculated position corrected for the antenna */
    INS_PSRSP      = 53, /* INS pseudorange single point solution – no DGPS corrections */
    INS_PSRDIFF    = 54, /* INS pseudorange differential solution */
    INS_RTKFLOAT   = 55, /* INS RTK floating point ambiguities solution */
    INS_RTKFIXED   = 56, /* INS RTK fixed ambiguities solution */
};

struct Oem6Header
{
    Oem6Header()
      : sync1()
      , sync2()
      , sync3()
      , header_length()
      , message_id()
      , message_type()
      , port_address()
      , message_length()
      , sequence()
      , idle_time()
      , time_status()
      , gps_week()
      , gps_millisecs()
      , receiver_status()
      , reserved()
      , software_version()
    {
    }

    uint8_t  sync1;             //!< start of packet first byte (0xAA)
    uint8_t  sync2;             //!< start of packet second byte (0x44)
    uint8_t  sync3;             //!< start of packet third  byte (0x12)
    uint8_t  header_length;     //!< Length of the header in bytes ( From start of packet )
    uint16_t message_id;        //!< Message ID number
    uint8_t  message_type;      //!< Message type - binary, ascii, nmea, etc...
    uint8_t  port_address;      //!< Address of the data port the log was received on
    uint16_t message_length;    //!< Message length (Not including header or CRC)
    uint16_t sequence;          //!< Counts down from N-1 to 0 for multiple related logs
    uint8_t  idle_time;         //!< Time the processor was idle in last sec between logs with same ID
    uint8_t  time_status;       //!< Indicates the quality of the GPS time (check TIME_STATUS for detail)
    uint16_t gps_week;          //!< GPS Week number
    uint32_t gps_millisecs;     //!< Milliseconds into week
    uint32_t receiver_status;   //!< Receiver status word
    uint16_t reserved;          //!< Reserved for internal use
    uint16_t software_version;  //!< Receiver software build number (0-65535)
};
HOLO_STATIC_ASSERT(sizeof(struct Oem6Header) == 28);

struct Oem6ShortHeader
{
    Oem6ShortHeader() : sync1(), sync2(), sync3(), message_length(), message_id(), gps_week(), gps_millisecs()
    {
    }

    uint8_t  sync1;           //!< start of packet first byte (0xAA)
    uint8_t  sync2;           //!< start of packet second byte (0x44)
    uint8_t  sync3;           //!< start of packet third  byte (0x13)
    uint8_t  message_length;  //!< Message length (Not including header or CRC)
    uint16_t message_id;      //!< Message ID number
    uint16_t gps_week;        //!< GPS Week number
    uint32_t gps_millisecs;   //!< Milliseconds into week
};
HOLO_STATIC_ASSERT(sizeof(struct Oem6ShortHeader) == 12);

struct InsPositionVelocityAttitudeShort
{
    InsPositionVelocityAttitudeShort()
      : header{}
      , gps_week()
      , gps_secs()
      , latitude()
      , longitude()
      , height()
      , north_velocity()
      , east_velocity()
      , up_velocity()
      , roll()
      , pitch()
      , azimuth()
      , status()
      , crc{}
    {
    }

    Oem6ShortHeader header;
    uint32_t        gps_week;        //!< GPS week number
    float64_t       gps_secs;        //!< Seconds into GPS week
    float64_t       latitude;        //!< latitude - WGS84 (deg)
    float64_t       longitude;       //!< longitude - WGS84 (deg)
    float64_t       height;          //!< Ellipsoidal height - WGS84 (m)
    float64_t       north_velocity;  //!< velocity in a northerly direction (m/s)
    float64_t       east_velocity;   //!< velocity in an easterly direction (m/s)
    float64_t       up_velocity;     //!< velocity in an up direction
    float64_t       roll;            //!< right handed rotation around y-axis (degrees)
    float64_t       pitch;           //!< right handed rotation aruond x-axis (degrees)
    float64_t       azimuth;         //!< right handed rotation around z-axis (degrees)
    uint32_t        status;          //!< status of the INS system
    int8_t          crc[4];

    uint32_t GetSerializedSize() const noexcept
    {
        return sizeof(struct InsPositionVelocityAttitudeShort);
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t size) noexcept
    {
        if (size < GetSerializedSize())
        {
            return 0;
        }
        (void)std::memcpy(this, data, GetSerializedSize());
        return GetSerializedSize();
    }
};
HOLO_STATIC_ASSERT(sizeof(struct InsPositionVelocityAttitudeShort) == 104);

struct RawImuShortExtended
{
    RawImuShortExtended()
      : header{}
      , imu_flag()
      , imu_type()
      , gps_week()
      , gps_secs()
      , imu_status()
      , z_acceleration()
      , y_acceleration_neg()
      , x_acceleration()
      , z_gyro_rate()
      , y_gyro_rate_neg()
      , x_gyro_rate()
      , crc{}
    {
    }

    Oem6ShortHeader header;              //!< Message header
    uint8_t         imu_flag;            //!< flag of the imu measurement: 0 is okay, 1 is error
    uint8_t         imu_type;            //!< imu type
    uint16_t        gps_week;            //!< GPS week number
    float64_t       gps_secs;            //!< Seconds into GPS week
    uint32_t        imu_status;          //!< Status of the IMU
    int32_t         z_acceleration;      //!< change in velocity along z axis in scaled m/s
    int32_t         y_acceleration_neg;  //!< -change in velocity along y axis in scaled m/s
    int32_t         x_acceleration;      //!< change in velocity along x axis in scaled m/s
    int32_t         z_gyro_rate;         //!< change in angle around z axis in radians
    int32_t         y_gyro_rate_neg;     //!< -(change in angle around y axis) in radians
    int32_t         x_gyro_rate;         //!< change in angle around x axis in radians
    int8_t          crc[4];

    uint32_t GetSerializedSize() const noexcept
    {
        return sizeof(struct RawImuShortExtended);
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t size) noexcept
    {
        if (size < GetSerializedSize())
        {
            return 0;
        }
        (void)std::memcpy(this, data, GetSerializedSize());
        return GetSerializedSize();
    }
};
HOLO_STATIC_ASSERT(sizeof(struct RawImuShortExtended) == 56);

struct InsCovarianceShort
{
    InsCovarianceShort()
      : header{}, gps_week(), gps_secs(), position_covariance{}, attitude_covariance{}, velocity_covariance{}, crc{}
    {
    }

    Oem6ShortHeader header;                  //!< Message header
    uint32_t        gps_week;                //!< GPS week number
    float64_t       gps_secs;                //!< Seconds into GPS week
    float64_t       position_covariance[9];  //!< Position covariance matrix [m^2] (xx,xy,xz,yz,yy,...)
    float64_t       attitude_covariance[9];  //!< Attitude covariance matrix [deg^2] (xx,xy,xz,yz,yy,...)
    float64_t       velocity_covariance[9];  //!< Velocity covariance matrix [(m/s)^2] (xx,xy,xz,yz,yy,...)
    int8_t          crc[4];

    uint32_t GetSerializedSize() const noexcept
    {
        return sizeof(struct InsCovarianceShort) - 4;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t size) noexcept
    {
        if (size < GetSerializedSize())
        {
            return 0;
        }
        (void)std::memcpy(this, data, GetSerializedSize());
        return GetSerializedSize();
    }
};
HOLO_STATIC_ASSERT(sizeof(struct InsCovarianceShort) == 248);

struct BestPosition
{
    BestPosition()
      : header{}
      , solution_status()
      , position_type()
      , latitude()
      , longitude()
      , altitude()
      , undulation()
      , datum_id()
      , latitude_std()
      , longitude_std()
      , altitude_std()
      , stn_id{}
      , diff_age()
      , sol_age()
      , svs()
      , sol_svs()
      , l1_svs()
      , mult_svs()
      , reserved()
      , extsolstat()
      , gal_sig_mask()
      , sig_mask()
      , crc{}
    {
    }

    Oem6Header header;           //!< Message header
    uint32_t   solution_status;  //!< Solution status
    uint32_t   position_type;    //!< Position type
    float64_t  latitude;         //!< latitude (deg)
    float64_t  longitude;        //!< longitude (deg)
    float64_t  altitude;         //!< height above mean sea level (m)
    float32_t  undulation;       //!< Undulation - the relationship between the geoid and the ellipsoid (m)
    uint32_t   datum_id;         //!< datum id number
    float32_t  latitude_std;     //!< latitude standard deviation (m)
    float32_t  longitude_std;    //!< longitude standard deviation (m)
    float32_t  altitude_std;     //!< height standard deviation (m)
    char       stn_id[4];        //!< base station id
    float32_t  diff_age;         //!< differential position age (sec)
    float32_t  sol_age;          //!< solution age (sec)
    uint8_t    svs;              //!< number of satellites tracked
    uint8_t    sol_svs;          //!< number of satellites used in solution
    uint8_t    l1_svs;           //!< number of GPS plus GLONASS L1 satellites used in solution
    uint8_t    mult_svs;         //!< number of GPS plus GLONASS L2 satellites used in solution
    uint8_t    reserved;         //!< reserved
    uint8_t    extsolstat;       //!< extended solution status - OEMV and greater only
    uint8_t    gal_sig_mask;     //!< reserved
    uint8_t    sig_mask;         //!< signals used mask - OEMV and greater only
    uint8_t    crc[4];           //!< 32-bit cyclic redundancy check (CRC)

    uint32_t GetSerializedSize() const noexcept
    {
        return sizeof(struct BestPosition) - 8;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t size) noexcept
    {
        if (size < GetSerializedSize())
        {
            return 0;
        }
        (void)std::memcpy(this, data, sizeof(header) + 8);
        (void)std::memcpy(&latitude, data + sizeof(header) + 8, GetSerializedSize() - sizeof(header) - 8);
        return GetSerializedSize();
    }
};
HOLO_STATIC_ASSERT(sizeof(struct BestPosition) == 112);

}  // namespace novatel
}  // namespace sensors
}  // namespace holo

#endif
