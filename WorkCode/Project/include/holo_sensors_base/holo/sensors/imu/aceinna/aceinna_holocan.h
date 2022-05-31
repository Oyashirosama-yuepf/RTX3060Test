/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file aceinna_holocan.h
 * @brief This header file define the function of aceinna driver
 * @author guoguangchao@holomatic.com
 * @date 2020-08-21
 */

#ifndef _HOLO_SENSORS_IMU_ACEINNA_ACEINNA_HOLOCAN_H
#define _HOLO_SENSORS_IMU_ACEINNA_ACEINNA_HOLOCAN_H

#include <holo/sensors/format/holocan.h>
#include <holo/sensors/imu/aceinna/aceinna_base.h>
#include <holo/sensors/imu/imu.h>
#include <holo_c/core/static_assert.h>

namespace holo
{
namespace sensors
{
namespace aceinna
{
using holo::common::Extrinsicf;
using holo::sensors::ImuDriverT;
using holo::sensors::format::HoloCanPacket;
/* aceinna imu driver based on holocan message */
struct AceinnaImuData
{
    holo::common::Timestamp timestamp;
    bool                    angle_rate_valid;
    float64_t               angle_rate[3];
    bool                    accel_valid;
    float64_t               accel[3];
};
HOLO_STATIC_ASSERT(sizeof(struct AceinnaImuData) == 72);

template <>
class AceinnaDriverT<HoloCanPacket> : public ImuDriverT<HoloCanPacket>
{
public:
    AceinnaDriverT(const Extrinsicf& extrinsic) : ImuDriverT<HoloCanPacket>(extrinsic)
    {
    }

    void ParseData(const HoloCanPacket& msg);

private:
    void Publish(const AceinnaImuData& data) const;

private:
    AceinnaImuData imu_data_;
};

}  // namespace aceinna
}  // namespace sensors
}  // namespace holo

#endif
