/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file starneto.cpp
 * @brief A app for starneto messages output
 * @author wangzhaobing<wangzhaobing@holomatic.com>
 * @date 2022/1/28
 */

#include <holo/log/hololog.h>
#include <holo/sensors/gnss/starneto/starneto.h>
#include <holo_c/sensors/dbc/XW-GI5651V2.0_dbc.h>

namespace holo
{
namespace sensors
{
namespace starneto
{
void StarnetoDriver::GpfpdBinLog()
{
    if (odometry_callback_ || odometry_translation_callback_)
    {
        Odometryd odometry;

        if (odometry_callback_)
        {
            Convert(gpfpd_bin_, odometry);
            odometry_callback_(odometry);
        }
        if (odometry_translation_callback_ && ConvertWgs84ToGcj02(gpfpd_bin_.latitude, gpfpd_bin_.longitude))
        {
            Convert(gpfpd_bin_, odometry);
            odometry_translation_callback_(odometry);
        }
    }
    if (position_callback_)
    {
        GnssPvt gnss_pvt_;
        Convert(gpfpd_bin_, gnss_pvt_);
        position_callback_(gnss_pvt_);
    }
}

void StarnetoDriver::GtimuBinLog()
{
    if (imu_callback_)
    {
        Imud imu;
        Convert(gtimu_bin_, gpfpd_bin_, imu);
        imu_callback_(imu);
    }
}

void StarnetoDriver::ConstructOdoPart1(const HoloCanPacket& msg, GPFPD_BIN& gpfpd_bin)
{
    uint16_t u16val;
    int16_t  s16val;
    u16val            = GET_NAV_ATTI_NAV_ATTI_Heading(msg.GetData());
    gpfpd_bin.azimuth = CALC_NAV_ATTI_NAV_ATTI_Heading(u16val, 1.0f);
    s16val            = GET_NAV_ATTI_NAV_ATTI_Pitch(msg.GetData());
    gpfpd_bin.pitch   = CALC_NAV_ATTI_NAV_ATTI_Pitch(s16val, 1.0f);
    s16val            = GET_NAV_ATTI_NAV_ATTI_Roll(msg.GetData());
    gpfpd_bin.roll    = CALC_NAV_ATTI_NAV_ATTI_Roll(s16val, 1.0f);
}

void StarnetoDriver::ConstructOdoPart2(const HoloCanPacket& msg, GPFPD_BIN& gpfpd_bin)
{
    int32_t s32val;
    s32val              = GET_NAV_POS_LatLon_NAV_POS_Latitude(msg.GetData());
    gpfpd_bin.latitude  = CALC_NAV_POS_LatLon_NAV_POS_Latitude(s32val, 1.0f);
    s32val              = GET_NAV_POS_LatLon_NAV_POS_Longitude(msg.GetData());
    gpfpd_bin.longitude = CALC_NAV_POS_LatLon_NAV_POS_Longitude(s32val, 1.0f);
}

void StarnetoDriver::ConstructOdoPart3(const HoloCanPacket& msg, GPFPD_BIN& gpfpd_bin)
{
    int32_t s32val;
    s32val           = GET_NAV_POS_AltFlag_NAV_POS_Altitude(msg.GetData());
    gpfpd_bin.height = CALC_NAV_POS_AltFlag_NAV_POS_Altitude(s32val, 1.0f);
    gpfpd_bin.status = GET_NAV_POS_AltFlag_NAV_Flag(msg.GetData());
}

void StarnetoDriver::ConstructOdoPart4(const HoloCanPacket& msg, GPFPD_BIN& gpfpd_bin)
{
    int16_t s16val;
    s16val                   = GET_NAV_Speed_NAV_Speed_Ve(msg.GetData());
    gpfpd_bin.east_velocity  = CALC_NAV_Speed_NAV_Speed_Ve(s16val, 1.0f);
    s16val                   = GET_NAV_Speed_NAV_Speed_Vn(msg.GetData());
    gpfpd_bin.north_velocity = CALC_NAV_Speed_NAV_Speed_Vn(s16val, 1.0f);
    s16val                   = GET_NAV_Speed_NAV_Speed_Vu(msg.GetData());
    gpfpd_bin.up_velocity    = CALC_NAV_Speed_NAV_Speed_Vu(s16val, 1.0f);
}

void StarnetoDriver::ConstructImuPart0(const HoloCanPacket& msg, GTIMU_BIN& gtimu_bin)
{
    int32_t s32val;
    s32val                   = GET_IMU_ACCE_XY_IMU_AcceX(msg.GetData());
    gtimu_bin.x_acceleration = CALC_IMU_ACCE_XY_IMU_AcceX(s32val, 1.0f);
    s32val                   = GET_IMU_ACCE_XY_IMU_AcceY(msg.GetData());
    gtimu_bin.y_acceleration = CALC_IMU_ACCE_XY_IMU_AcceY(s32val, 1.0f);
}

void StarnetoDriver::ConstructImuPart1(const HoloCanPacket& msg, GTIMU_BIN& gtimu_bin)
{
    int32_t s32val;
    s32val                = GET_IMU_GYRO_XY_IMU_GyroX(msg.GetData());
    gtimu_bin.x_gyro_rate = CALC_IMU_GYRO_XY_IMU_GyroX(s32val, 1.0f);
    s32val                = GET_IMU_GYRO_XY_IMU_GyroY(msg.GetData());
    gtimu_bin.y_gyro_rate = CALC_IMU_GYRO_XY_IMU_GyroY(s32val, 1.0f);
}

void StarnetoDriver::ConstructImuPart2(const HoloCanPacket& msg, GTIMU_BIN& gtimu_bin)
{
    int32_t s32val;
    s32val                   = GET_IMU_AcceGyro_Z_IMU_AcceZ(msg.GetData());
    gtimu_bin.z_acceleration = CALC_IMU_AcceGyro_Z_IMU_AcceZ(s32val, 1.0f);
    s32val                   = GET_IMU_AcceGyro_Z_IMU_GyroZ(msg.GetData());
    gtimu_bin.z_gyro_rate    = CALC_IMU_AcceGyro_Z_IMU_GyroZ(s32val, 1.0f);
}

void StarnetoDriver::ConstructTimPart0(const HoloCanPacket& msg, GTIMU_BIN& gtimu_bin, GPFPD_BIN& gpfpd_bin)
{
    uint16_t u16val;
    uint32_t u32val;
    u16val             = GET_GPS_Time_GPS_Time_Week(msg.GetData());
    gpfpd_bin.gps_week = CALC_GPS_Time_GPS_Time_Week(u16val, 1);
    gtimu_bin.gps_week = CALC_GPS_Time_GPS_Time_Week(u16val, 1);
    u32val             = GET_GPS_Time_GPS_Time_Second(msg.GetData());
    gpfpd_bin.gps_secs = CALC_GPS_Time_GPS_Time_Second(u32val, 1.0f);
    gtimu_bin.gps_secs = CALC_GPS_Time_GPS_Time_Second(u32val, 1.0f);
}

void StarnetoDriver::ParseData(const HoloCanPacket& msg)
{
    switch (msg.GetId())
    {
        case ID_GPS_Time:
            ConstructTimPart0(msg, gtimu_bin_, gpfpd_bin_);
            CANODO_INDEX_0();
            CANIMU_INDEX_0();
            break;
        case ID_NAV_ATTI:
            /* parsing message */
            ConstructOdoPart1(msg, gpfpd_bin_);
            CANODO_INDEX_1();
            break;
        case ID_NAV_POS_LatLon:
            ConstructOdoPart2(msg, gpfpd_bin_);
            CANODO_INDEX_2();
            break;
        case ID_NAV_POS_AltFlag:
            ConstructOdoPart3(msg, gpfpd_bin_);
            CANODO_INDEX_3();
            break;
        case ID_NAV_Speed:
            ConstructOdoPart4(msg, gpfpd_bin_);
            if (GetCANOdoIndex() == 0x0F)
            {
                CANODO_INDEX_CLEAR();
                GpfpdBinLog();
            }
            break;
        case ID_IMU_ACCE_XY:
            ConstructImuPart0(msg, gtimu_bin_);
            CANIMU_INDEX_1();
            break;
        case ID_IMU_GYRO_XY:
            ConstructImuPart1(msg, gtimu_bin_);
            CANIMU_INDEX_2();
            break;
        case ID_IMU_AcceGyro_Z:
            ConstructImuPart2(msg, gtimu_bin_);
            if (GetCANImuIndex() == 0x07)
            {
                CANIMU_INDEX_CLEAR();
                GtimuBinLog();
            }
            break;
        default:
            break;
    }
}

void StarnetoDriver::Convert(uint32_t gps_week, float64_t week_secs, holo::common::Timestamp& timestamp)
{
    float64_t sec  = std::floor(week_secs);
    float64_t nsec = 1e9 * (week_secs - sec);
    sec            = sec + gps_week * 7 * 24 * 3600;
    (void)holo::common::Timestamp::GpsToUtc(holo::common::Timestamp(sec, nsec), timestamp);
}

void StarnetoDriver::Convert(const GPFPD_BIN& gpfpd_bin, Pose3d& pose)
{
    // Calculation novatel to world
    holo::geometry::Point2d xy;
    (void)GeographicalTransformation::LL2UTM(gpfpd_bin.longitude, gpfpd_bin.latitude, xy);
    holo::geometry::Point3d p(xy.GetX(), xy.GetY(), gpfpd_bin.height);
    holo::geometry::Rot3 Nov_World = holo::geometry::Rot3::Rz(holo::geometry::Radian<float64_t>(-gpfpd_bin.azimuth)) *
                                     holo::geometry::Rot3::Rx(holo::geometry::Radian<float64_t>(gpfpd_bin.pitch)) *
                                     holo::geometry::Rot3::Ry(holo::geometry::Radian<float64_t>(gpfpd_bin.roll));
    pose             = Pose3d(Nov_World, p);
    Pose3d pose_body = extrinsic_->GetPose().template Cast<float64_t>().Inverse();
    pose             = pose * pose_body;
}

void StarnetoDriver::Convert(const GPFPD_BIN& gpfpd_bin, Odometryd& odo)
{
    holo::common::Timestamp stamp;
    Convert(gpfpd_bin.gps_week, gpfpd_bin.gps_secs, stamp);
    odo.SetTimestamp(stamp);
    GeographicalTransformation::SetGlobalZoneIdByLatLon(gpfpd_bin.longitude, gpfpd_bin.latitude);
    uint32_t zone_id = GeographicalTransformation::GetZoneId();
    bool_t   south_flag(gpfpd_bin.latitude < 0);
    odo.SetCoordinate(common::Coordinate::Utm6Coordinate(zone_id, south_flag, 0u, 0u));
    odo.SetChildCoordinate(common::Coordinate::VehicleCoordinate(
        SensorId::Category::GNSS, SensorId::Model::GNSS_NOVATEL, VehicleLocation::Plane::CHASSIS,
        VehicleLocation::Location::REAR, VehicleLocation::Location::CENTER));
    bool_t solution_good =
        static_cast<bool_t>((gpfpd_bin.status == Gpfpdstatus::GPSDIRETION) ||
                            (gpfpd_bin.status == Gpfpdstatus::RTKFIXED) || (gpfpd_bin.status == Gpfpdstatus::RTKFLOAT));
    odo.SetStatus(solution_good ? Odometryd::Status::ALLGOOD :
                                  Odometryd::Status::SOLUTIONNOGOOD); /*ALLGOOD: topic status == 0 */
    odo.SetSource(Odometryd::Source::GNSS);
    Pose3d pose;
    Convert(gpfpd_bin, pose);
    odo.SetPose(pose);
    odo.SetPoseCovariance(numerics::Matrix6d::Identity());
    holo::numerics::Vector6 Velocity;
    Velocity(0) = gpfpd_bin.east_velocity;
    Velocity(1) = gpfpd_bin.north_velocity;
    Velocity(2) = gpfpd_bin.up_velocity;
    odo.SetVelocity(Velocity);
    odo.SetVelocityCovariance(numerics::Matrix6d::Identity());
    if (gpfpd_bin.status == Gpfpdstatus::GPSDIRETION)
    {
        odo.SetPosePrecision(Precision::LOW);
        odo.SetVelocityPrecision(Precision::LOW);
    }
    else if ((gpfpd_bin.status == Gpfpdstatus::RTKFIXED) || (gpfpd_bin.status == Gpfpdstatus::RTKFLOAT))
    {
        odo.SetPosePrecision(Precision::HIGH);
        odo.SetVelocityPrecision(Precision::HIGH);
    }
    else
    {
        odo.SetPosePrecision(Precision::UNKNOWN);
        odo.SetVelocityPrecision(Precision::UNKNOWN);
    }
}

void StarnetoDriver::Convert(const GTIMU_BIN& gtimu_bin, const GPFPD_BIN& gpfpd_bin, Imud& imu)
{
    holo::common::Timestamp stamp;
    Convert(gtimu_bin.gps_week, gtimu_bin.gps_secs, stamp);
    imu.SetTimestamp(stamp);
    imu.SetCoordinate(common::Coordinate::BODY);
    bool_t imu_solution =
        static_cast<bool_t>((gpfpd_bin.status == Gpfpdstatus::GPSDIRETION) ||
                            (gpfpd_bin.status == Gpfpdstatus::RTKFIXED) || (gpfpd_bin.status == Gpfpdstatus::RTKFLOAT));
    imu.SetStatus(imu_solution ? holo::common::Imud::Status::ALLGOOD : holo::common::Imud::Status::UNDEFINEDERROR);
    holo::geometry::Point3d LinearAcceleration;
    LinearAcceleration[0] = gtimu_bin.y_acceleration;  /*x axes in BOOY*/
    LinearAcceleration[1] = -gtimu_bin.x_acceleration; /*y axes in BOOY*/
    LinearAcceleration[2] = gtimu_bin.z_acceleration;  /*z axes in BOOY*/
    imu.SetLinearAcceleration(LinearAcceleration);
    holo::geometry::Point3d AngularVelocity;
    AngularVelocity[0] = gtimu_bin.y_gyro_rate;
    AngularVelocity[1] = -gtimu_bin.x_gyro_rate;
    AngularVelocity[2] = gtimu_bin.z_gyro_rate;
    imu.SetAngularVelocity(AngularVelocity);
}

void StarnetoDriver::Convert(const GPFPD_BIN& gpfpd_bin, GnssPvt& gnss_pvt)
{
    holo::common::Timestamp stamp;
    Convert(gpfpd_bin.gps_week, gpfpd_bin.gps_secs, stamp);
    gnss_pvt.SetTimestamp(stamp);
    gnss_pvt.SetCoordinate(common::Coordinate::WGS84);

    if (gpfpd_bin.status == Gpfpdstatus::GPSDIRETION)
    {
        gnss_pvt.SetMode(GnssPvt::Mode::SINGLE_FIX);
        gnss_pvt.SetValidFlags(true, true, true, true);
    }
    else if ((gpfpd_bin.status == Gpfpdstatus::RTKFIXED) || (gpfpd_bin.status == Gpfpdstatus::RTKFLOAT))
    {
        gnss_pvt.SetMode(GnssPvt::Mode::RTK_FLOAT_FIX);
        gnss_pvt.SetValidFlags(true, true, true, true);
    }
    else
    {
        gnss_pvt.SetMode(GnssPvt::Mode::NO_POSITION);
        gnss_pvt.SetValidFlags(false, false, false, false);
    }

    gnss_pvt.SetCoordinate(holo::common::Coordinate::Wgs84Coordinate());
    gnss_pvt.SetLatitude(gpfpd_bin.latitude);
    gnss_pvt.SetLongitude(gpfpd_bin.longitude);
    gnss_pvt.SetHeight(gpfpd_bin.height);
    gnss_pvt.SetLatitudeCov(1);
    gnss_pvt.SetLongitudeCov(1);
    gnss_pvt.SetHeightCov(1);
    gnss_pvt.SetVelocityEastCov(1);
    gnss_pvt.SetVelocityNorthCov(1);
    gnss_pvt.SetVelocityUpCov(1);

    gnss_pvt.SetVelocityEast(gpfpd_bin.east_velocity);
    gnss_pvt.SetVelocityNorth(gpfpd_bin.north_velocity);
    gnss_pvt.SetVelocityUp(gpfpd_bin.up_velocity);
}

}  // namespace starneto
}  // namespace sensors
}  // namespace holo