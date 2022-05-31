/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file asensing_holocan.h
 * @brief This header file define the function of asening driver
 * @author zhangtongyang@holomatic.com
 * @date 2021-04-27
 */

#ifndef _HOLO_SENSORS_ASENSING_HOLOCAN_H
#define _HOLO_SENSORS_ASENSING_HOLOCAN_H

#include <holo/common/gnss_pvt.h>
#include <holo/common/gnss_raw_measurement.h>
#include <holo/common/odometry.h>
#include <holo/geometry/geographical_transformation.h>
#include <holo/sensors/common/device.h>
#include <holo/sensors/format/holocan.h>
#include <holo/sensors/format/rawbuf.h>
#include <holo/sensors/imu/imu.h>
#include <holo_c/core/static_assert.h>
#include <functional>

namespace holo
{
namespace sensors
{
namespace asensing
{
using holo::common::Extrinsicf;
using holo::common::GnssPvt;
using holo::common::GnssRawMeasurement;
using holo::sensors::ImuDriverT;
using holo::sensors::format::HoloCanPacket;
using Imud                       = holo::common::Imud;
using Odometryd                  = holo::common::Odometryd;
using Precision                  = holo::common::Odometryd::PrecisionValueType;
using GnssRawMeasurementCallback = std::function<void(const GnssRawMeasurement&)>;
using PositionCallback           = std::function<void(const GnssPvt&)>;
using OdometryCallbackType       = std::function<void(const Odometryd&)>;
using ImuCallbackType            = std::function<void(const Imud&)>;

static const uint8_t GNSS_HEIGHT_TIME_RECEIVED = (0x01 << 0);
static const uint8_t GNSS_LAT_LON_RECEIVED     = (0x01 << 1);
static const uint8_t GNSS_SPEED_RECEIVED       = (0x01 << 2);
static const uint8_t GNSS_DATAINFO_RECEIVED    = (0x01 << 3);
static const uint8_t GNSS_STD_RECEIVED         = (0x01 << 4);
static const uint8_t GNSS_GPS_WEEK_RECEIVED    = (0x01 << 5);
static const uint8_t GNSS_ALL_RECEIVED         = (0x3f);

static const uint32_t SEC_PER_WEEK     = 604800;  //! seconds per week
static const uint16_t GPS_WEEK_MINIMAL = 2010;    //! 2020-04-05 gps week is 2100

struct AsensingImuData
{
    holo::common::Timestamp timestamp;
    bool                    angle_rate_valid;
    float64_t               angle_rate[3];
    bool                    accel_valid;
    float64_t               accel[3];
};
HOLO_STATIC_ASSERT(sizeof(struct AsensingImuData) == 72);

enum class GpsFlag : uint8_t
{
    NONE             = 0,
    FIXEDPOS         = 1,
    FIXEDHEIGHT      = 2,
    DOPPLER_VELOCITY = 8,
    SINGLE           = 16,
    PSRDIFF          = 17,
    SBAS_SBAS        = 18,
    L1_FLOAT_L1      = 32,
    IONOFREE_FLOAT   = 33,
    NARROW_FLOAT     = 34,
    L1_INT_L1        = 48,
    WIDE_INT         = 49,
    NARROW           = 50,
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
enum class InitStatusAll : uint8_t
{
    NONE          = 0,
    ONLY_IMU_INIT = 1,
    ALL_INIT      = 2,
};

struct AsensingOdometryData
{
    uint32_t  gps_week;        //!< GPS week number
    float64_t gps_secs;        //!< Seconds into GPS week
    float64_t latitude;        //!< latitude - WGS84 (deg)
    float64_t longitude;       //!< longitude - WGS84 (deg)
    float64_t height;          //!< Ellipsoidal height - WGS84 (m)
    float64_t north_velocity;  //!< velocity in a northerly direction (m/s)
    float64_t east_velocity;   //!< velocity in an easterly direction (m/s)
    float64_t up_velocity;     //!< velocity in an up direction
    float64_t roll;            //!< right handed rotation around y-axis (degrees)
    float64_t pitch;           //!< right handed rotation aruond x-axis (degrees)
    float64_t azimuth;         //!< right handed rotation around z-axis (degrees)
    uint32_t  status;          //!< status of the INS system
};

struct AsenNavPvtMessage
{
    float64_t locatHeight;
    uint32_t  gpsWeek;  //! gps week
    uint32_t  time;     //! Seconds of week
    float64_t latitude;
    float64_t longitude;
    float64_t northSpd;
    float64_t eastSpd;
    float64_t toGroundSpd;
    uint8_t   gpsFlagPos;
    uint8_t   numSv;                //! Number of GPS received stars
    uint8_t   gpsFlagHeading;       //! GPS heading initialize flag
    uint8_t   gpsAge;               //! Differential delay
    uint8_t   carStatus;            //! Car status.bit0=1 means can received wheel speed
    uint8_t   status;               //! Asensing's overall status flag
    float64_t stdLat;               //! Latitude standard deviation
    float64_t stdLon;               //! Longitude standard deviation
    float64_t stdLocatHeight;       //! Height standard devision
    float64_t stdHeading;           //! Heading standard devision
    uint8_t   gnssDataReceivedFlg;  //! gnss data received flag
};

class AsensingDriver
{
public:
    AsensingDriver() : gnss_data_{}, asen_pos_callback_(nullptr), asen_pos_translation_callback_(nullptr)
    {
    }

    void ParseData(const HoloCanPacket& msg);
    void InstallPositionCallback(const PositionCallback& callback) noexcept;
    void InstallPositionTranslationCallback(const PositionCallback& callback) noexcept;
    void SetImuCallback(const ImuCallbackType& handler) noexcept;
    void SetOdometryCallback(const OdometryCallbackType& callback) noexcept;

private:
    void ImuPublish(const AsensingImuData& data) const;
    void ParseNavPvt(const AsenNavPvtMessage& data) const;
    void OdometryPublish(const AsensingOdometryData& odo_data, const AsenNavPvtMessage& gnss_data) const;

private:
    AsensingImuData      imu_data_;
    AsenNavPvtMessage    gnss_data_;
    AsensingOdometryData odometry_data_;
    GnssPvt              gnss_pvt_;
    ImuCallbackType      imu_callback_;
    OdometryCallbackType odometry_callback_;
    PositionCallback     asen_pos_callback_;
    PositionCallback     asen_pos_translation_callback_;

    static float64_t constexpr G_ACCEL = 9.80;
    static int32_t const NSEC_PER_MSEC = 1000000;
    static int32_t const MSEC_PER_SEC  = 1000;
};

}  // namespace asensing
}  // namespace sensors
}  // namespace holo

#endif
