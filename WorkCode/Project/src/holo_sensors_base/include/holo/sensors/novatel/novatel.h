/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file novatel.h
 * @brief This header file define the function of novatel
 * @author houyujian@holomatic.com
 * @date Dec 02, 2019
 */

#ifndef _HOLO_SENSORS_NOVATEL_NOVATEL_H
#define _HOLO_SENSORS_NOVATEL_NOVATEL_H

#include <functional>
#include <iostream>
#include <mutex>

#include <holo/common/extrinsic.h>
#include <holo/common/gnss_pvt.h>
#include <holo/common/imu.h>
#include <holo/common/odometry.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/geometry/geographical_transformation.h>
#include <holo/os/timer.h>
#include <holo/sensors/format/rawbuf.h>
#include <holo/sensors/novatel/novatel_structure.h>
#include <holo/sensors/utils/sensors_utils.h>

namespace holo
{
namespace sensors
{
namespace novatel
{
using holo::common::Extrinsicf;
class NovatelDriver
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

    NovatelDriver(const Extrinsicf& extrinsic)
      : extrinsic_{std::make_shared<Extrinsicf>(extrinsic)}
      , ins_pva_s_callback_(nullptr)
      , best_position_callback_(nullptr)
      , raw_imu_s_x_callback_(nullptr)
      , ins_cov_s_callback_(nullptr)
      , odometry_callback_(nullptr)
      , odometry_translation_callback_(nullptr)
      , imu_callback_(nullptr)
      , position_callback_(nullptr)
      , covs_{}
      , ins_pva_{}
    {
    }

    void SetInsPvaSCallback(const BufferCallbackType& handler) noexcept
    {
        ins_pva_s_callback_ = handler;
    }

    void SetBestPositionCallback(const BufferCallbackType& handler) noexcept
    {
        best_position_callback_ = handler;
    }

    void SetInsCovSCallback(const BufferCallbackType& handler) noexcept
    {
        ins_cov_s_callback_ = handler;
    }

    void SetRawImuSXCallback(const BufferCallbackType& handler) noexcept
    {
        raw_imu_s_x_callback_ = handler;
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

    void ParseData(const RawbufferType& data);

    std::pair<uint8_t*, uint32_t> RecvData(uint8_t* rdata, uint32_t rbytes);

private:
    bool_t InitImuParams(uint8_t imu_type);
    void   Convert(uint32_t gps_week, float64_t week_secs, holo::common::Timestamp& timestamp);
    void   Convert(const InsPositionVelocityAttitudeShort& inspva, Pose3d& pose);
    void   Convert(const InsPositionVelocityAttitudeShort& inspva, Odometryd& odo);
    void   Convert(const InsCovarianceShort& cov, Odometryd& odo);
    void   Convert(const RawImuShortExtended& raw_imu, Imud& imu);
    void   Convert(const BestPosition& raw_position, const InsPositionVelocityAttitudeShort& inspva, GnssPvt& position);

    void InspvasLog(const uint8_t* msg, uint32_t len);
    void BestposeLog(const uint8_t* msg, uint32_t len);
    void RawimusxLog(const uint8_t* msg, uint32_t len);
    void InscovsLog(const uint8_t* msg, uint32_t len);

private:
    std::shared_ptr<Extrinsicf>      extrinsic_;
    BufferCallbackType               ins_pva_s_callback_;
    BufferCallbackType               best_position_callback_;
    BufferCallbackType               raw_imu_s_x_callback_;
    BufferCallbackType               ins_cov_s_callback_;
    OdometryCallbackType             odometry_callback_;
    OdometryCallbackType             odometry_translation_callback_;
    ImuCallbackType                  imu_callback_;
    PositionCallbackType             position_callback_;
    InsCovarianceShort               covs_;
    InsPositionVelocityAttitudeShort ins_pva_;
    GnssPvt                          gnss_pvt_;
};

}  // namespace novatel
}  // namespace sensors
}  // namespace holo
#endif