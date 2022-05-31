/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file aceinna_holocan.hpp
 * @brief A class to receive and construct aceinna outputs in holocan format
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/03
 */

#include <holo/log/hololog.h>
#include <holo/core/types.h>
#include <holo/sensors/format/holocan.h>
#include <holo/sensors/imu/aceinna/aceinna_holocan.h>
#include <holo_c/sensors/dbc/aceinna_imu_dbc.h>

namespace holo
{
namespace sensors
{
namespace aceinna
{
void AceinnaDriverT<HoloCanPacket>::ParseData(const HoloCanPacket& msg)
{
    uint32_t raw_sigval;
    switch (msg.GetId())
    {
        case (ID_Aceinna_Accel):
            /* fetch values */
            raw_sigval            = GET_Aceinna_Accel_Aceinna_AccX(msg.GetData());
            imu_data_.accel[0]    = CALC_Aceinna_Accel_Aceinna_AccX(raw_sigval, 1.0);
            raw_sigval            = GET_Aceinna_Accel_Aceinna_AccY(msg.GetData());
            imu_data_.accel[1]    = CALC_Aceinna_Accel_Aceinna_AccY(raw_sigval, -1.0);
            raw_sigval            = GET_Aceinna_Accel_Aceinna_AccZ(msg.GetData());
            imu_data_.accel[2]    = CALC_Aceinna_Accel_Aceinna_AccZ(raw_sigval, -1.0);
            imu_data_.accel_valid = true;
            /* fetch timestamp */
            imu_data_.timestamp = holo::common::Timestamp(msg.GetSec(), msg.GetNsec());
            break;
        case (ID_Aceinna_AngleRate):
            /* fetch values */
            raw_sigval                 = GET_Aceinna_AngleRate_Aceinna_GyroX(msg.GetData());
            imu_data_.angle_rate[0]    = CALC_Aceinna_AngleRate_Aceinna_GyroX(raw_sigval, 1.0);
            raw_sigval                 = GET_Aceinna_AngleRate_Aceinna_GyroY(msg.GetData());
            imu_data_.angle_rate[1]    = CALC_Aceinna_AngleRate_Aceinna_GyroY(raw_sigval, -1.0);
            raw_sigval                 = GET_Aceinna_AngleRate_Aceinna_GyroZ(msg.GetData());
            imu_data_.angle_rate[2]    = CALC_Aceinna_AngleRate_Aceinna_GyroZ(raw_sigval, -1.0);
            imu_data_.angle_rate_valid = true;
            /* publish */
            Publish(imu_data_);
            /* clear */
            imu_data_.angle_rate_valid = false;
            imu_data_.accel_valid      = false;
            break;
        default:
            break;
    }
}

void AceinnaDriverT<HoloCanPacket>::Publish(const AceinnaImuData& data) const
{
    holo::common::Imud imu;
    Coordinate         coord = Coordinate::VehicleCoordinate(SensorId::Category::IMU, SensorId::Model::IMU_ACEINNA_305,
                                                     VehicleLocation::Plane::CHASSIS, VehicleLocation::Location::REAR,
                                                     VehicleLocation::Location::CENTER);
    imu.SetCoordinate(coord);
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

template class AceinnaDriverT<HoloCanPacket>;

}  // namespace aceinna
}  // namespace sensors
}  // namespace holo
