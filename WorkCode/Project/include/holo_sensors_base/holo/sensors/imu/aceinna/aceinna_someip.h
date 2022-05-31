/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file aceinna.h
 * @brief This header file define the function of aceinna driver
 * @author guoguangchao@holomatic.com
 * @date 2020-08-21
 */

#ifndef _HOLO_SENSORS_ACEINNA_ACEINNA_H
#define _HOLO_SENSORS_ACEINNA_ACEINNA_H

#include <holo/sensors/format/holocan.h>
#include <holo/sensors/imu/aceinna/aceinna_base.h>
#include <holo_c/common/imu_float32.h>
#include <holo_c/numerics/vector_float32.h>
#include <holo_c/sensors/dbc/aceinna_imu_dbc.h>

namespace holo
{
namespace sensors
{
namespace aceinna
{
using SomeipPacketType = holo::sensors::format::SomeipPacket<64>;

/* aceinna imu driver based on someip packet */
template <>
class AceinnaDriverT<SomeipPacketType> : public ImuDriverT<SomeipPacketType>
{
public:
    AceinnaDriverT(const Extrinsicf& extrinsic) : ImuDriverT<SomeipPacketType>(extrinsic), imu_data_{}
    {
    }

    void ParseData(const SomeipPacketType& data);

private:
    uint8_t imu_data_[256];
};

}  // namespace aceinna
}  // namespace sensors
}  // namespace holo

#endif
