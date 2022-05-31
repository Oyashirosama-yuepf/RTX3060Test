/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file aceinna_someip.cpp
 * @brief A class to receive and construct aceinna outputs in someip format
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/03
 */

#include <holo/log/hololog.h>
#include <holo/core/types.h>
#include <holo/sensors/format/someip.h>
#include <holo/sensors/imu/aceinna/aceinna_someip.h>

namespace holo
{
namespace sensors
{
namespace aceinna
{
void AceinnaDriverT<SomeipPacketType>::ParseData(const SomeipPacketType& data)
{
    ::Imuf             output_Imu_f;
    holo::common::Imud imu;
    uint32_t           payload_length = data.GetMsgLength() - 8;
    data.GetPayload(0, imu_data_, payload_length);

    imuf_init(&output_Imu_f);
    imuf_deserialize(&output_Imu_f, &imu_data_[4], payload_length - 4);

    Coordinate coord = imuf_get_coordinate(&output_Imu_f);
    imu.SetCoordinate(coord);
    holo::common::Timestamp stamp;
    stamp.SetSec(timestamp_get_sec(imuf_get_timestamp(&output_Imu_f)));
    stamp.SetNsec(timestamp_get_nsec(imuf_get_timestamp(&output_Imu_f)));
    imu.SetTimestamp(stamp);
    holo::common::Imud::Status status = static_cast<holo::common::Imud::Status>(imuf_get_status(&output_Imu_f));
    imu.SetStatus(status);

    float32_t angle_rate_x, angle_rate_y, angle_rate_z;
    imuf_get_angular_velocity_value(&output_Imu_f, &angle_rate_x, &angle_rate_y, &angle_rate_z);
    imu.SetAngularVelocity(angle_rate_x, angle_rate_y, angle_rate_z);

    float32_t acc_x, acc_y, acc_z;
    imuf_get_linear_acceleration_value(&output_Imu_f, &acc_x, &acc_y, &acc_z);
    imu.SetLinearAcceleration(acc_x, acc_y, acc_z);

    /* callback */
    if (imu_callback_)
    {
        imu_callback_(imu);
    }
}

template class AceinnaDriverT<SomeipPacketType>;

}  // namespace aceinna
}  // namespace sensors
}  // namespace holo
