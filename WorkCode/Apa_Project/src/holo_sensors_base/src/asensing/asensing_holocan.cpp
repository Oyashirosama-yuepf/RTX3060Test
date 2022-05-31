/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file asensing_holocan.cpp
 * @brief A class to receive and construct asensing outputs in holocan format
 * @author zhangtongyang@holomatic.com
 * @date 2021-04-27
 */

#include <holo/core/types.h>
#include <holo/log/hololog.h>
#include <holo/sensors/asensing/asensing_holocan.h>
#include <holo/sensors/format/holocan.h>
#include <holo_c/sensors/dbc/asensing_dbc.h>

namespace holo
{
namespace sensors
{
namespace asensing
{
void AsensingDriver::ParseData(const HoloCanPacket& msg)
{
    uint32_t raw_sigval;
    switch (msg.GetId())
    {
        case ID_INS_Acc:
            raw_sigval            = GET_INS_Acc_ACC_X(msg.GetData());
            imu_data_.accel[0]    = CALC_INS_Acc_ACC_X(raw_sigval, G_ACCEL);
            raw_sigval            = GET_INS_Acc_ACC_Y(msg.GetData());
            imu_data_.accel[1]    = CALC_INS_Acc_ACC_Y(raw_sigval, -G_ACCEL);
            raw_sigval            = GET_INS_Acc_ACC_Z(msg.GetData());
            imu_data_.accel[2]    = CALC_INS_Acc_ACC_Z(raw_sigval, -G_ACCEL);
            imu_data_.accel_valid = true;

            imu_data_.timestamp = holo::common::Timestamp(msg.GetSec(), msg.GetNsec());
            break;
        case ID_INS_GYRO:
            raw_sigval                 = GET_INS_GYRO_GYRO_X(msg.GetData());
            imu_data_.angle_rate[0]    = CALC_INS_GYRO_GYRO_X(raw_sigval, 1.0);
            raw_sigval                 = GET_INS_GYRO_GYRO_Y(msg.GetData());
            imu_data_.angle_rate[1]    = CALC_INS_GYRO_GYRO_Y(raw_sigval, -1.0);
            raw_sigval                 = GET_INS_GYRO_GYRO_Z(msg.GetData());
            imu_data_.angle_rate[2]    = CALC_INS_GYRO_GYRO_Z(raw_sigval, -1.0);
            imu_data_.angle_rate_valid = true;

            ImuPublish(imu_data_);
            /* clear */
            imu_data_.angle_rate_valid     = false;
            imu_data_.accel_valid          = false;
            gnss_data_.gnssDataReceivedFlg = 0;
            break;
        case ID_INS_HeadingPitchRoll:
            break;
        case ID_INS_HeightTime:
            raw_sigval             = GET_INS_HeightTime_INS_LocatHeight(msg.GetData());
            gnss_data_.locatHeight = CALC_INS_HeightTime_INS_LocatHeight(raw_sigval, 1.0);
            raw_sigval             = GET_INS_HeightTime_INS_Time(msg.GetData());
            gnss_data_.time        = CALC_INS_HeightTime_INS_Time(raw_sigval, 1.0);
            gnss_data_.gnssDataReceivedFlg |= GNSS_HEIGHT_TIME_RECEIVED;
            break;
        case ID_INS_LatitudeLongitude:
            raw_sigval           = GET_INS_LatitudeLongitude_INS_Latitude(msg.GetData());
            gnss_data_.latitude  = CALC_INS_LatitudeLongitude_INS_Latitude(raw_sigval, 1.0);
            raw_sigval           = GET_INS_LatitudeLongitude_INS_Longitude(msg.GetData());
            gnss_data_.longitude = CALC_INS_LatitudeLongitude_INS_Longitude(raw_sigval, 1.0);
            gnss_data_.gnssDataReceivedFlg |= GNSS_LAT_LON_RECEIVED;
            break;
        case ID_INS_Speed:
            raw_sigval             = GET_INS_Speed_INS_NorthSpd(msg.GetData());
            gnss_data_.northSpd    = CALC_INS_Speed_INS_NorthSpd(raw_sigval, 1.0);
            raw_sigval             = GET_INS_Speed_INS_EastSpd(msg.GetData());
            gnss_data_.eastSpd     = CALC_INS_Speed_INS_EastSpd(raw_sigval, 1.0);
            raw_sigval             = GET_INS_Speed_INS_ToGroundSpd(msg.GetData());
            gnss_data_.toGroundSpd = CALC_INS_Speed_INS_ToGroundSpd(raw_sigval, -1.0);
            gnss_data_.gnssDataReceivedFlg |= GNSS_SPEED_RECEIVED;
            break;
        case ID_INS_DataInfo:
            gnss_data_.gpsFlagPos     = GET_INS_DataInfo_INS_GpsFlag_Pos(msg.GetData());
            gnss_data_.numSv          = GET_INS_DataInfo_INS_NumSV(msg.GetData());
            gnss_data_.gpsFlagHeading = GET_INS_DataInfo_INS_GpsFlag_Heading(msg.GetData());
            gnss_data_.gpsAge         = GET_INS_DataInfo_INS_Gps_Age(msg.GetData());
            gnss_data_.carStatus      = GET_INS_DataInfo_INS_Car_Status(msg.GetData());
            gnss_data_.status         = GET_INS_DataInfo_INS_Status(msg.GetData());
            gnss_data_.gnssDataReceivedFlg |= GNSS_DATAINFO_RECEIVED;
            break;
        case ID_INS_Std:
            raw_sigval                = GET_INS_Std_INS_Std_Lat(msg.GetData());
            gnss_data_.stdLat         = CALC_INS_Std_INS_Std_Lat(raw_sigval, 1.0);
            raw_sigval                = GET_INS_Std_INS_Std_Lon(msg.GetData());
            gnss_data_.stdLon         = CALC_INS_Std_INS_Std_Lon(raw_sigval, 1.0);
            raw_sigval                = GET_INS_Std_INS_Std_LocatHeight(msg.GetData());
            gnss_data_.stdLocatHeight = CALC_INS_Std_INS_Std_LocatHeight(raw_sigval, 1.0);
            raw_sigval                = GET_INS_Std_INS_Std_Heading(msg.GetData());
            gnss_data_.stdHeading     = CALC_INS_Std_INS_Std_Heading(raw_sigval, 1.0);
            gnss_data_.gnssDataReceivedFlg |= GNSS_STD_RECEIVED;
            OdometryPublish(odometry_data_, gnss_data_);
            break;
        case ID_GPS_HeightAndWeek:
            gnss_data_.gpsWeek = GET_GPS_HeightAndWeek_GPS_Week(msg.GetData());
            gnss_data_.gnssDataReceivedFlg |= GNSS_GPS_WEEK_RECEIVED;

            /* parse and publish gnss data of asensing*/
            ParseNavPvt(gnss_data_);
            gnss_data_.gnssDataReceivedFlg = 0;
            break;
        default:
            break;
    }
}
void AsensingDriver::SetOdometryCallback(const OdometryCallbackType& callback) noexcept
{
    odometry_callback_ = callback;
}
void AsensingDriver::SetImuCallback(const ImuCallbackType& handler) noexcept
{
    imu_callback_ = handler;
}
void AsensingDriver::InstallPositionCallback(const PositionCallback& callback) noexcept
{
    asen_pos_callback_ = callback;
}

void AsensingDriver::InstallPositionTranslationCallback(const PositionCallback& callback) noexcept
{
    asen_pos_translation_callback_ = callback;
}

void AsensingDriver::ImuPublish(const AsensingImuData& data) const
{
    holo::common::Imud imu;

    imu.SetCoordinate(Coordinate::BODY);
    imu.SetTimestamp(data.timestamp);
    uint32_t imu_status = static_cast<uint32_t>(holo::common::Imud::Status::ALLGOOD);
    imu_status |= data.angle_rate_valid ? 0 : static_cast<uint32_t>(holo::common::Imud::Status::GYROXERROR);
    imu_status |= data.angle_rate_valid ? 0 : static_cast<uint32_t>(holo::common::Imud::Status::GYROYERROR);
    imu_status |= data.angle_rate_valid ? 0 : static_cast<uint32_t>(holo::common::Imud::Status::GYROZERROR);
    imu_status |= data.accel_valid ? 0 : static_cast<uint32_t>(holo::common::Imud::Status::ACCLXERROR);
    imu_status |= data.accel_valid ? 0 : static_cast<uint32_t>(holo::common::Imud::Status::ACCLYERROR);
    imu_status |= data.accel_valid ? 0 : static_cast<uint32_t>(holo::common::Imud::Status::ACCLZERROR);
    imu.SetStatus(static_cast<holo::common::Imud::Status>(imu_status));

    imu.SetAngularVelocity(holo::geometry::Radian<float64_t>(data.angle_rate[0]),
                           holo::geometry::Radian<float64_t>(data.angle_rate[1]),
                           holo::geometry::Radian<float64_t>(data.angle_rate[2]));
    imu.SetLinearAcceleration(data.accel[0], data.accel[1], data.accel[2]);

    /* callback */
    if (imu_callback_)
    {
        imu_callback_(imu);
    }
}

void AsensingDriver::OdometryPublish(const AsensingOdometryData& odo_data, const AsenNavPvtMessage& gnss_data) const
{
    holo::common::Odometryd odo;

    holo::common::Timestamp timestamp;
    float64_t               sec  = std::floor(gnss_data.time);
    float64_t               nsec = 1e9 * (gnss_data.time - sec);
    float64_t               yaw_temp;
    sec = sec + gnss_data.gpsWeek * 7 * 24 * 3600;
    holo::common::Timestamp::GpsToUtc(holo::common::Timestamp(sec, nsec), timestamp);
    odo.SetTimestamp(timestamp);

    GeographicalTransformation::SetGlobalZoneIdByLatLon(gnss_data.longitude, gnss_data.latitude);
    uint32_t zone_id = GeographicalTransformation::GetZoneId();
    bool_t   south_flag(gnss_data.latitude < 0);
    odo.SetCoordinate(holo::common::Coordinate::Utm6Coordinate(zone_id, south_flag, 0u, 0u));
    odo.SetChildCoordinate(holo::common::Coordinate::VehicleCoordinate(
        SensorId::Category::GNSS, SensorId::Model::GNSS_NOVATEL, VehicleLocation::Plane::CHASSIS,
        VehicleLocation::Location::REAR, VehicleLocation::Location::CENTER));
    bool_t solution_good = static_cast<bool_t>(odo_data.status == InspvaStatus::INS_SOLUTION_GOOD);
    odo.SetStatus(solution_good ? Odometryd::Status::ALLGOOD : Odometryd::Status::SOLUTIONNOGOOD);
    odo.SetSource(Odometryd::Source::GNSS);

    holo::geometry::Point2d xy;
    GeographicalTransformation::LL2UTM(gnss_data.longitude, gnss_data.latitude, xy);
    holo::geometry::Point3d p(xy.GetX(), xy.GetY(), gnss_data.locatHeight);
    yaw_temp = -odo_data.azimuth + 90;
    if (yaw_temp > 180)
        yaw_temp = yaw_temp - 360;
    holo::geometry::Rot3 Nov_World = holo::geometry::Rot3::Rz(holo::geometry::Radian<float64_t>(yaw_temp)) *
                                     holo::geometry::Rot3::Ry(holo::geometry::Radian<float64_t>(-odo_data.pitch)) *
                                     holo::geometry::Rot3::Rx(holo::geometry::Radian<float64_t>(odo_data.roll));
    Pose3d pose = Pose3d(Nov_World, p);
    odo.SetPose(pose);

    odo.SetPoseCovariance(numerics::Matrix6d::Identity());
    holo::numerics::Vector6 Velocity;
    Velocity(0) = gnss_data.eastSpd;
    Velocity(1) = gnss_data.northSpd;
    Velocity(2) = gnss_data.toGroundSpd;
    odo.SetVelocity(Velocity);
    odo.SetVelocityCovariance(numerics::Matrix6d::Identity());
    if (gnss_pvt_.GetMode() == GnssPvt::Mode::SINGLE_FIX)
    {
        odo.SetPosePrecision(Precision::LOW);
        odo.SetVelocityPrecision(Precision::LOW);
    }
    else if ((gnss_pvt_.GetMode() == GnssPvt::Mode::DIFF_POSITION) ||
             (gnss_pvt_.GetMode() == GnssPvt::Mode::RTK_FLOAT_FIX) ||
             (gnss_pvt_.GetMode() == GnssPvt::Mode::RTK_INT_FIX))
    {
        odo.SetPosePrecision(Precision::HIGH);
        odo.SetVelocityPrecision(Precision::HIGH);
    }
    else
    {
        odo.SetPosePrecision(Precision::UNKNOWN);
        odo.SetVelocityPrecision(Precision::UNKNOWN);
    }

    /* callback */
    if (odometry_callback_)
    {
        odometry_callback_(odo);
    }
}

void AsensingDriver::ParseNavPvt(const AsenNavPvtMessage& data) const
{
    GnssPvt                 pos;
    holo::common::Timestamp gps_stamp(SEC_PER_WEEK * data.gpsWeek + data.time / MSEC_PER_SEC,
                                      (data.time % MSEC_PER_SEC) * NSEC_PER_MSEC);
    holo::common::Timestamp utc_stamp;
    holo::common::Timestamp::GpsToUtc(gps_stamp, utc_stamp);
    pos.SetTimestamp(utc_stamp);

    bool_t        position_valid_flag      = false;
    bool_t        velocity_valid_flag      = false;
    bool_t        position_cov_valid_flag  = false;
    bool_t        velocity__cov_valid_flag = false;
    GnssPvt::Mode position_mode            = GnssPvt::Mode::NO_POSITION;

    /* if initialize success */
    if ((static_cast<InitStatusAll>(data.status) == InitStatusAll::ALL_INIT) &&
        (data.gnssDataReceivedFlg == GNSS_ALL_RECEIVED))
    {
        if ((static_cast<GpsFlag>(data.gpsFlagPos) < GpsFlag::DOPPLER_VELOCITY) ||
            (static_cast<GpsFlag>(data.gpsFlagHeading) < GpsFlag::DOPPLER_VELOCITY))
        {
            position_mode            = GnssPvt::Mode::NO_POSITION;
            position_valid_flag      = false;
            velocity_valid_flag      = false;
            position_cov_valid_flag  = false;
            velocity__cov_valid_flag = false;
        }
        else if ((static_cast<GpsFlag>(data.gpsFlagPos) == GpsFlag::DOPPLER_VELOCITY) ||
                 (static_cast<GpsFlag>(data.gpsFlagHeading) == GpsFlag::DOPPLER_VELOCITY))
        {
            position_mode            = GnssPvt::Mode::TIMING_ONLY;
            position_valid_flag      = true;
            velocity_valid_flag      = true;
            position_cov_valid_flag  = true;
            velocity__cov_valid_flag = true;
        }
        else if ((static_cast<GpsFlag>(data.gpsFlagPos) == GpsFlag::SINGLE) ||
                 (static_cast<GpsFlag>(data.gpsFlagHeading) == GpsFlag::SINGLE))
        {
            position_mode            = GnssPvt::Mode::SINGLE_FIX;
            position_valid_flag      = true;
            velocity_valid_flag      = true;
            position_cov_valid_flag  = true;
            velocity__cov_valid_flag = true;
        }
        else if ((static_cast<GpsFlag>(data.gpsFlagPos) == GpsFlag::PSRDIFF) ||
                 (static_cast<GpsFlag>(data.gpsFlagHeading) == GpsFlag::PSRDIFF))
        {
            position_mode            = GnssPvt::Mode::DIFF_POSITION;
            position_valid_flag      = true;
            velocity_valid_flag      = true;
            position_cov_valid_flag  = true;
            velocity__cov_valid_flag = true;
        }
        else if ((static_cast<GpsFlag>(data.gpsFlagPos) < GpsFlag::L1_INT_L1) ||
                 (static_cast<GpsFlag>(data.gpsFlagHeading) < GpsFlag::L1_INT_L1))
        {
            position_mode            = GnssPvt::Mode::RTK_FLOAT_FIX;
            position_valid_flag      = true;
            velocity_valid_flag      = true;
            position_cov_valid_flag  = true;
            velocity__cov_valid_flag = true;
        }
        else
        {
            position_mode            = GnssPvt::Mode::RTK_INT_FIX;
            position_valid_flag      = true;
            velocity_valid_flag      = true;
            position_cov_valid_flag  = true;
            velocity__cov_valid_flag = true;
        }
    }
    else
    {
        position_mode            = GnssPvt::Mode::NO_POSITION;
        position_valid_flag      = false;
        velocity_valid_flag      = false;
        position_cov_valid_flag  = false;
        velocity__cov_valid_flag = false;
    }
    pos.SetMode(position_mode);
    pos.SetValidFlags(position_valid_flag, velocity_valid_flag, position_cov_valid_flag, velocity__cov_valid_flag);

    float64_t lat = data.latitude;
    float64_t lon = data.longitude;
    pos.SetCoordinate(holo::common::Coordinate::Wgs84Coordinate());
    pos.SetLatitude(lat);
    pos.SetLongitude(lon);
    pos.SetHeight(data.locatHeight);
    pos.SetVelocityEast(data.eastSpd);
    pos.SetVelocityNorth(data.northSpd);
    pos.SetVelocityUp(data.toGroundSpd);
    pos.SetLatitudeCov(data.stdLat);
    pos.SetLongitudeCov(data.stdLon);
    pos.SetHeightCov(data.stdLocatHeight);
    // pos.SetVelocityEastCov(0);
    // pos.SetVelocityNorthCov(0);
    // pos.SetVelocityUpCov(0);

    /* callback */
    if (asen_pos_callback_)
    {
        asen_pos_callback_(pos);
    }

    if (asen_pos_translation_callback_)
    {
        if (ConvertWgs84ToGcj02(lat, lon))
        {
            pos.SetCoordinate(holo::common::Coordinate::Gcj02Coordinate());
            pos.SetLatitude(lat);
            pos.SetLongitude(lon);
            asen_pos_translation_callback_(pos);
        }
    }
}

}  // namespace asensing
}  // namespace sensors
}  // namespace holo