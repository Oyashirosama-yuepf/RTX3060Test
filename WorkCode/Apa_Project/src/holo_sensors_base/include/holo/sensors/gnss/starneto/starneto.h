/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file starneto.h
 * @brief A app for starneto messages output
 * @author wangzhaobing<wangzhaobing@holomatic.com>
 * @date 2022/1/28
 */

#ifndef _HOLO_SENSORS_STARNETO_STARNETO_H
#define _HOLO_SENSORS_STARNETO_STARNETO_H

#include <holo/common/extrinsic.h>
#include <holo/common/gnss_pvt.h>
#include <holo/common/imu.h>
#include <holo/common/odometry.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/geometry/geographical_transformation.h>
#include <holo/os/timer.h>
#include <holo/sensors/format/holocan.h>
#include <holo/sensors/format/rawbuf.h>
#include <holo/sensors/gnss/starneto/starneto_structure.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <functional>
#include <iostream>
#include <mutex>

namespace holo
{
namespace sensors
{
namespace starneto
{
using holo::common::Extrinsicf;
using holo::sensors::format::HoloCanPacket;

class StarnetoDriver
{
public:
    using Pose3d               = holo::geometry::Pose3d;
    using SensorId             = holo::common::SensorId;
    using VehicleLocation      = holo::common::VehicleLocation;
    using Odometryd            = holo::common::Odometryd;
    using Imud                 = holo::common::Imud;
    using GnssPvt              = holo::common::GnssPvt;
    using Precision            = holo::common::Odometryd::PrecisionValueType;
    using RawbufferType        = holo::sensors::format::Rawbuffer<8192>;
    using BufferCallbackType   = std::function<void(const uint8_t*, uint32_t)>;
    using OdometryCallbackType = std::function<void(const Odometryd&)>;
    using ImuCallbackType      = std::function<void(const Imud&)>;
    using PositionCallbackType = std::function<void(const GnssPvt&)>;

    StarnetoDriver(const Extrinsicf& extrinsic)
      : extrinsic_{std::make_shared<Extrinsicf>(extrinsic)}
      , odometry_callback_(nullptr)
      , odometry_translation_callback_(nullptr)
      , imu_callback_(nullptr)
      , position_callback_(nullptr)
      , gpfpd_bin_{}
      , gtimu_bin_{}
      , canodo_index_(0)
      , canimu_index_(0)
    {
    }

    void CANODO_INDEX_0()
    {
        canodo_index_ |= 0x01;
    }

    void CANIMU_INDEX_0()
    {
        canimu_index_ |= 0x01;
    }

    void CANODO_INDEX_1()
    {
        canodo_index_ |= 0x02;
    }

    void CANODO_INDEX_2()
    {
        canodo_index_ |= 0x04;
    }

    void CANODO_INDEX_3()
    {
        canodo_index_ |= 0x08;
    }

    void CANODO_INDEX_CLEAR()
    {
        canodo_index_ &= 0x00;
    }

    void CANIMU_INDEX_1()
    {
        canimu_index_ |= 0x02;
    }

    void CANIMU_INDEX_2()
    {
        canimu_index_ |= 0x04;
    }

    void CANIMU_INDEX_CLEAR()
    {
        canimu_index_ &= 0x00;
    }

    uint8_t GetCANOdoIndex() const noexcept
    {
        return canodo_index_;
    }

    uint8_t GetCANImuIndex() const noexcept
    {
        return canimu_index_;
    }

    void SetOdometryCallback(const OdometryCallbackType& handler) noexcept
    {
        odometry_callback_ = handler;
    }

    void SetOdometryTranslationCallback(const OdometryCallbackType& handler) noexcept
    {
        odometry_translation_callback_ = handler;
    }

    void SetImuCallback(const ImuCallbackType& handler) noexcept
    {
        imu_callback_ = handler;
    }

    void SetPositionCallback(const PositionCallbackType& handler) noexcept
    {
        position_callback_ = handler;
    }

    void ParseData(const HoloCanPacket& msg);

private:
    void Convert(uint32_t gps_week, float64_t week_secs, holo::common::Timestamp& timestamp);
    void Convert(const GPFPD_BIN& gpfpd_bin, Pose3d& pose);
    void Convert(const GPFPD_BIN& gpfpd_bin, Odometryd& odo);
    void Convert(const GTIMU_BIN& gtimu_bin, const GPFPD_BIN& gpfpd_bin, Imud& imu);
    void Convert(const GPFPD_BIN& gpfpd_bin, GnssPvt& position);

    void GpfpdBinLog();
    void GtimuBinLog();

    void ConstructOdoPart0(const HoloCanPacket& msg, GPFPD_BIN& gpfpd_bin);
    void ConstructOdoPart1(const HoloCanPacket& msg, GPFPD_BIN& gpfpd_bin);
    void ConstructOdoPart2(const HoloCanPacket& msg, GPFPD_BIN& gpfpd_bin);
    void ConstructOdoPart3(const HoloCanPacket& msg, GPFPD_BIN& gpfpd_bin);
    void ConstructOdoPart4(const HoloCanPacket& msg, GPFPD_BIN& gpfpd_bin);
    void ConstructImuPart0(const HoloCanPacket& msg, GTIMU_BIN& gtimu_bin);
    void ConstructImuPart1(const HoloCanPacket& msg, GTIMU_BIN& gtimu_bin);
    void ConstructImuPart2(const HoloCanPacket& msg, GTIMU_BIN& gtimu_bin);
    void ConstructTimPart0(const HoloCanPacket& msg, GTIMU_BIN& gtimu_bin, GPFPD_BIN& gpfpd_bin);

private:
    std::shared_ptr<Extrinsicf> extrinsic_;
    OdometryCallbackType        odometry_callback_;
    OdometryCallbackType        odometry_translation_callback_;
    ImuCallbackType             imu_callback_;
    PositionCallbackType        position_callback_;
    GPFPD_BIN                   gpfpd_bin_;
    GTIMU_BIN                   gtimu_bin_;
    uint8_t                     canodo_index_;
    uint8_t                     canimu_index_;
};

}  // namespace starneto
}  // namespace sensors
}  // namespace holo

#endif  // !_HOLO_SENSORS_STARNETO_STARNETO.H