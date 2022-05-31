/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file novatel.cpp
 * @brief the novatel driver
 * @author houyujian@holomatic.com
 * @date 2019-12-09
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#include <holo/log/hololog.h>
#include <holo/sensors/novatel/novatel.h>

namespace holo
{
namespace sensors
{
namespace novatel
{
void NovatelDriver::InspvasLog(const uint8_t* msg, uint32_t len)
{
    if (ins_pva_s_callback_)
    {
        ins_pva_s_callback_(msg, len);
    }
    if (odometry_callback_ || odometry_translation_callback_)
    {
        Odometryd odometry;
        if (!ins_pva_.Deserialize(msg, len))
        {
            return;
        }
        if (odometry_callback_)
        {
            Convert(ins_pva_, odometry);
            Convert(covs_, odometry);
            odometry_callback_(odometry);
        }
        if (odometry_translation_callback_ && ConvertWgs84ToGcj02(ins_pva_.latitude, ins_pva_.longitude))
        {
            Convert(ins_pva_, odometry);
            odometry_translation_callback_(odometry);
        }
    }
}

void NovatelDriver::BestposeLog(const uint8_t* msg, uint32_t len)
{
    if (best_position_callback_)
    {
        best_position_callback_(msg, len);
    }
    if (position_callback_)
    {
        BestPosition best_position;
        if (best_position.Deserialize(msg, len))
        {
            Convert(best_position, ins_pva_, gnss_pvt_);
            position_callback_(gnss_pvt_);
        }
    }
}

void NovatelDriver::RawimusxLog(const uint8_t* msg, uint32_t len)
{
    if (raw_imu_s_x_callback_)
    {
        raw_imu_s_x_callback_(msg, len);
    }
    if (imu_callback_)
    {
        RawImuShortExtended raw_imuse;
        if (raw_imuse.Deserialize(msg, len))
        {
            Imud imu;
            Convert(raw_imuse, imu);
            imu_callback_(imu);
        }
    }
}

void NovatelDriver::InscovsLog(const uint8_t* msg, uint32_t len)
{
    if (ins_cov_s_callback_)
    {
        ins_cov_s_callback_(msg, len);
    }
    (void)covs_.Deserialize(msg, len);
}

void NovatelDriver::ParseData(const RawbufferType& data)
{
    const uint8_t* msg = data.data();
    uint32_t       len = data.size();
    if (len < sizeof(Oem6ShortHeader))
    {
        return;
    }
    if (msg[0] == SYNC_BYTE_1 && msg[1] == SYNC_BYTE_2 && (msg[2] == SYNC_BYTE_3 || msg[2] == SYNC_BYTE_3_SHORT))
    {
        uint32_t message_id = (static_cast<uint32_t>(msg[5]) << 8) + msg[4];
        switch (message_id)
        {
            case BinaryLogId::INSPVAS_LOG:
            {
                InspvasLog(msg, len);
                break;
            }
            case BinaryLogId::BESTPOSB_LOG:
            {
                BestposeLog(msg, len);
                break;
            }
            case BinaryLogId::RAWIMUSX_LOG:
            {
                RawimusxLog(msg, len);
                break;
            }
            case BinaryLogId::INSCOVS_LOG:
            {
                InscovsLog(msg, len);
                break;
            }
            default:
                break;
        }
    }
}

void NovatelDriver::Convert(uint32_t gps_week, float64_t week_secs, holo::common::Timestamp& timestamp)
{
    float64_t sec  = std::floor(week_secs);
    float64_t nsec = 1e9 * (week_secs - sec);
    sec            = sec + gps_week * 7 * 24 * 3600;
    (void)holo::common::Timestamp::GpsToUtc(holo::common::Timestamp(sec, nsec), timestamp);
}

void NovatelDriver::Convert(const InsPositionVelocityAttitudeShort& inspva, Pose3d& pose)
{
    // Calculation novatel to world
    holo::geometry::Point2d xy;
    (void)GeographicalTransformation::LL2UTM(inspva.longitude, inspva.latitude, xy);
    holo::geometry::Point3d p(xy.GetX(), xy.GetY(), inspva.height);
    holo::geometry::Rot3    Nov_World = holo::geometry::Rot3::Rz(holo::geometry::Radian<float64_t>(-inspva.azimuth)) *
                                     holo::geometry::Rot3::Rx(holo::geometry::Radian<float64_t>(inspva.pitch)) *
                                     holo::geometry::Rot3::Ry(holo::geometry::Radian<float64_t>(inspva.roll));
    pose             = Pose3d(Nov_World, p);
    Pose3d pose_body = extrinsic_->GetPose().template Cast<float64_t>().Inverse();
    pose             = pose * pose_body;
}

void NovatelDriver::Convert(const InsPositionVelocityAttitudeShort& inspva, Odometryd& odo)
{
    holo::common::Timestamp stamp;
    Convert(inspva.gps_week, inspva.gps_secs, stamp);
    odo.SetTimestamp(stamp);
    GeographicalTransformation::SetGlobalZoneIdByLatLon(inspva.longitude, inspva.latitude);
    uint32_t zone_id = GeographicalTransformation::GetZoneId();
    bool_t   south_flag(inspva.latitude < 0);
    odo.SetCoordinate(common::Coordinate::Utm6Coordinate(zone_id, south_flag, 0u, 0u));
    odo.SetChildCoordinate(common::Coordinate::VehicleCoordinate(
        SensorId::Category::GNSS, SensorId::Model::GNSS_NOVATEL, VehicleLocation::Plane::CHASSIS,
        VehicleLocation::Location::REAR, VehicleLocation::Location::CENTER));
    bool_t solution_good = static_cast<bool_t>(inspva.status == InspvaStatus::INS_SOLUTION_GOOD);
    odo.SetStatus(solution_good ? Odometryd::Status::ALLGOOD : Odometryd::Status::SOLUTIONNOGOOD);
    odo.SetSource(Odometryd::Source::GNSS);
    Pose3d pose;
    Convert(inspva, pose);
    odo.SetPose(pose);
    odo.SetPoseCovariance(numerics::Matrix6d::Identity());
    holo::numerics::Vector6 Velocity;
    Velocity(0) = inspva.east_velocity;
    Velocity(1) = inspva.north_velocity;
    Velocity(2) = inspva.up_velocity;
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
}

void NovatelDriver::Convert(const InsCovarianceShort& cov, Odometryd& odo)
{
    holo::numerics::Matrix6 pose_covariance;
    pose_covariance(0, 0) = cov.position_covariance[0];
    pose_covariance(0, 1) = cov.position_covariance[1];
    pose_covariance(0, 2) = cov.position_covariance[2];
    pose_covariance(1, 0) = cov.position_covariance[3];
    pose_covariance(1, 1) = cov.position_covariance[4];
    pose_covariance(1, 2) = cov.position_covariance[5];
    pose_covariance(2, 0) = cov.position_covariance[6];
    pose_covariance(2, 1) = cov.position_covariance[7];
    pose_covariance(2, 2) = cov.position_covariance[8];
    pose_covariance(3, 3) = holo::geometry::Radian<float64_t>(cov.attitude_covariance[0]);
    pose_covariance(3, 4) = holo::geometry::Radian<float64_t>(cov.attitude_covariance[1]);
    pose_covariance(3, 5) = holo::geometry::Radian<float64_t>(cov.attitude_covariance[2]);
    pose_covariance(4, 3) = holo::geometry::Radian<float64_t>(cov.attitude_covariance[3]);
    pose_covariance(4, 4) = holo::geometry::Radian<float64_t>(cov.attitude_covariance[4]);
    pose_covariance(4, 5) = holo::geometry::Radian<float64_t>(cov.attitude_covariance[5]);
    pose_covariance(5, 3) = holo::geometry::Radian<float64_t>(cov.attitude_covariance[6]);
    pose_covariance(5, 4) = holo::geometry::Radian<float64_t>(cov.attitude_covariance[7]);
    pose_covariance(5, 5) = holo::geometry::Radian<float64_t>(cov.attitude_covariance[8]);
    odo.SetPoseCovariance(pose_covariance);
    holo::numerics::Matrix6 velocity_covariance;
    velocity_covariance(0, 0) = cov.velocity_covariance[0];
    velocity_covariance(0, 1) = cov.velocity_covariance[1];
    velocity_covariance(0, 2) = cov.velocity_covariance[2];
    velocity_covariance(1, 0) = cov.velocity_covariance[3];
    velocity_covariance(1, 1) = cov.velocity_covariance[4];
    velocity_covariance(1, 2) = cov.velocity_covariance[5];
    velocity_covariance(2, 0) = cov.velocity_covariance[6];
    velocity_covariance(2, 1) = cov.velocity_covariance[7];
    velocity_covariance(2, 2) = cov.velocity_covariance[8];
    odo.SetVelocityCovariance(velocity_covariance);
}

void NovatelDriver::Convert(const RawImuShortExtended& raw_imu, Imud& imu)
{
    if (IMU_PARAMS_MAP.count(raw_imu.imu_type))
    {
        holo::common::Timestamp stamp;
        Convert(raw_imu.gps_week, raw_imu.gps_secs, stamp);
        imu.SetTimestamp(stamp);
        imu.SetCoordinate(common::Coordinate::BODY);
        imu.SetStatus(raw_imu.imu_flag ? holo::common::Imud::Status::UNDEFINEDERROR :
                                         holo::common::Imud::Status::ALLGOOD);
        holo::geometry::Point3d LinearAcceleration;
        LinearAcceleration[0] = -raw_imu.y_acceleration_neg * IMU_PARAMS_MAP.at(raw_imu.imu_type).accl_factor;
        LinearAcceleration[1] = -raw_imu.x_acceleration * IMU_PARAMS_MAP.at(raw_imu.imu_type).accl_factor;
        LinearAcceleration[2] = raw_imu.z_acceleration * IMU_PARAMS_MAP.at(raw_imu.imu_type).accl_factor;
        imu.SetLinearAcceleration(LinearAcceleration);
        holo::geometry::Point3d AngularVelocity;
        AngularVelocity[0] = -raw_imu.y_gyro_rate_neg * IMU_PARAMS_MAP.at(raw_imu.imu_type).gyro_factor;
        AngularVelocity[1] = -raw_imu.x_gyro_rate * IMU_PARAMS_MAP.at(raw_imu.imu_type).gyro_factor;
        AngularVelocity[2] = raw_imu.z_gyro_rate * IMU_PARAMS_MAP.at(raw_imu.imu_type).gyro_factor;
        imu.SetAngularVelocity(AngularVelocity);
    }
    imu = imu;
}

void NovatelDriver::Convert(const BestPosition& raw_position, const InsPositionVelocityAttitudeShort& ins_pva,
                            GnssPvt& position)
{
    holo::common::Timestamp stamp;
    Convert(raw_position.header.gps_week, raw_position.header.gps_millisecs / 1E3, stamp);
    position.SetTimestamp(stamp);
    position.SetCoordinate(common::Coordinate::WGS84);

    if ((raw_position.position_type == PositionType::SINGLE) || (raw_position.position_type == PositionType::INS_PSRSP))
    {
        position.SetMode(GnssPvt::Mode::SINGLE_FIX);
        position.SetValidFlags(true, true, true, true);
    }
    else if ((raw_position.position_type == PositionType::PSRDIFF) ||
             (raw_position.position_type == PositionType::L1_FLOAT) ||
             (raw_position.position_type == PositionType::NARROW_FLOAT) ||
             (raw_position.position_type == PositionType::INS_PSRDIFF))
    {
        position.SetMode(GnssPvt::Mode::DIFF_POSITION);
        position.SetValidFlags(true, true, true, true);
    }
    else if ((raw_position.position_type == PositionType::L1_INT) ||
             (raw_position.position_type == PositionType::WIDE_INT) ||
             (raw_position.position_type == PositionType::INS_RTKFLOAT) ||
             (raw_position.position_type == PositionType::INS_RTKFIXED))
    {
        position.SetMode(GnssPvt::Mode::RTK_FLOAT_FIX);
        position.SetValidFlags(true, true, true, true);
    }
    else if ((raw_position.position_type == PositionType::NARROW_INT) ||
             (raw_position.position_type == PositionType::INS_RTKFIXED))
    {
        position.SetMode(GnssPvt::Mode::RTK_INT_FIX);
        position.SetValidFlags(true, true, true, true);
    }
    else
    {
        position.SetMode(GnssPvt::Mode::NO_POSITION);
        position.SetValidFlags(false, false, false, false);
    }

    position.SetCoordinate(holo::common::Coordinate::Wgs84Coordinate());
    position.SetLatitude(raw_position.latitude);
    position.SetLongitude(raw_position.longitude);
    position.SetHeight(raw_position.altitude + raw_position.undulation);
    position.SetLatitudeCov(raw_position.latitude_std);
    position.SetLongitudeCov(raw_position.longitude_std);
    position.SetHeightCov(raw_position.altitude_std);
    position.SetVelocityEastCov(1);
    position.SetVelocityNorthCov(1);
    position.SetVelocityUpCov(1);

    position.SetVelocityEast(ins_pva.east_velocity);
    position.SetVelocityNorth(ins_pva.north_velocity);
    position.SetVelocityUp(ins_pva.up_velocity);
}

std::pair<uint8_t*, uint32_t> NovatelDriver::RecvData(uint8_t* rdata, uint32_t rbytes)
{
    uint32_t mesg_len = 0;

    using holo::sensors::novatel::BinaryLogId;
    if (rbytes > BinaryMesgLen::MESG_HEAD_LEN)
    {
        mesg_len            = 0;
        uint32_t message_id = (static_cast<uint32_t>(rdata[5]) << 8) + rdata[4];

        if (BinaryLogId::INSCOVS_LOG == message_id)
        {
            mesg_len = BinaryMesgLen::MESG_INSCOVS_LEN;
        }
        else if (BinaryLogId::RAWIMUSX_LOG == message_id)
        {
            mesg_len = BinaryMesgLen::MESG_RAWIMUSX_LEN;
        }
        else if ((BinaryLogId::BESTPOSB_LOG == message_id) || (BinaryLogId::INSPVAS_LOG == message_id))
        {
            mesg_len = BinaryMesgLen::MESG_BESTPOSB_OR_INSPVAS_LEN;
        }
        else
        {
            if (rbytes >= BinaryMesgLen::MESG_ERROR_226_LEN)
            {
                mesg_len = BinaryMesgLen::MESG_ERROR_226_LEN;
            }
            else if ((rbytes >= BinaryMesgLen::MESG_ERROR_219_LEN) && (rbytes < BinaryMesgLen::MESG_ERROR_226_LEN))
            {
                mesg_len = BinaryMesgLen::MESG_ERROR_219_LEN;
            }
            else if ((rbytes >= BinaryMesgLen::MESG_ERROR_7_LEN) && (rbytes < BinaryMesgLen::MESG_ERROR_219_LEN))
            {
                mesg_len = BinaryMesgLen::MESG_ERROR_7_LEN;
            }
        }
        if (rbytes >= mesg_len)
        {
            return std::pair<uint8_t*, uint32_t>(rdata, mesg_len);
        }
        else
        {
            return std::pair<uint8_t*, uint32_t>(nullptr, 0);
        }
    }

    return std::pair<uint8_t*, uint32_t>(nullptr, 0);
}

}  // namespace novatel
}  // namespace sensors
}  // namespace holo