/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file novatel_common_app.h
 * @brief This header file define the app of novatel in common
 * @author houyujian@holomatic.com
 * @date Dec 24, 2019
 */

#ifndef _HOLO_CMW_APPS_NOVATEL_COMMON_APP_H
#define _HOLO_CMW_APPS_NOVATEL_COMMON_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/os/time.h>
#include <holo/os/timer.h>
#include <holo/sensors/novatel/novatel.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_c/core/types.h>
#include <interface/interface_wrapper.h>
#include <utils/timediff_utils.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
#include <traits.h>
#else
#include <holo_base_msg/traits.h>
#endif

namespace holo_cmw
{
using holo::sensors::novatel::NovatelDriver;
enum class NovatelMsgType : uint32_t
{
    ODOMETRY   = 0,
    ODOMETRY_T = 1,
    IMU        = 2,
    GNSS_PVT   = 3,
};

class NovatelDriverApp : public TimediffBase
{
public:
    using HoloSyncDiffPacket = holo::sensors::format::HoloSyncDiffPacket;
    using GnssPvt            = holo::common::GnssPvt;
    using Imud               = holo::common::Imud;
    using Odometryd          = holo::common::OdometryT<float64_t>;
    using LiveCallbackType   = std::function<void(uint32_t, uint32_t)>;

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    using OdometrydWriterType =
        cmw_wrapper::BusType::WriterType<Odometryd, mdc_cm_wrapper::VSOdometryWgs84SITraits<Odometryd>>;
    using ImudWriterType = cmw_wrapper::BusType::WriterType<Imud, mdc_cm_wrapper::VSImuSITraits<Imud>>;
    using GnssPvtWriterType =
        cmw_wrapper::BusType::WriterType<GnssPvt, mdc_cm_wrapper::VSGnssPvtWgs84SITraits<GnssPvt>>;
#elif defined(CMW_WRAPPER_ENABLE_ROS)
    using OdometrydWriterType =
        cmw_wrapper::BusType::WriterType<Odometryd, ros_wrapper::DefaultConversionTraits<Odometryd>>;
    using ImudWriterType    = cmw_wrapper::BusType::WriterType<Imud, ros_wrapper::DefaultConversionTraits<Imud>>;
    using GnssPvtWriterType = cmw_wrapper::BusType::WriterType<GnssPvt, ros_wrapper::DefaultConversionTraits<GnssPvt>>;
#else
    using OdometrydWriterType = cmw_wrapper::BusType::WriterType<Odometryd>;
    using ImudWriterType      = cmw_wrapper::BusType::WriterType<Imud>;
    using GnssPvtWriterType   = cmw_wrapper::BusType::WriterType<GnssPvt>;
#endif

    NovatelDriverApp(int32_t id, const std::string& ns)
      : TimediffBase()
      , thread_(nullptr)
      , running_(true)
      , frames_odometry_()
      , frames_odometry_t_()
      , frames_imu_()
      , frames_gnss_pvt_()
      , live_callback_(nullptr)
      , init_diff_(std::numeric_limits<int64_t>::min())
    {
        bus_ = std::make_shared<cmw_wrapper::BusType>(id, ns);
    }

    NovatelDriverApp(std::shared_ptr<cmw_wrapper::BusType> bus)
      : TimediffBase()
      , bus_(bus)
      , thread_(nullptr)
      , running_(true)
      , frames_odometry_()
      , frames_odometry_t_()
      , frames_imu_()
      , frames_gnss_pvt_()
      , live_callback_(nullptr)
      , init_diff_(std::numeric_limits<int64_t>::min())
    {
    }

    ~NovatelDriverApp()
    {
        running_ = false;
        if (thread_ && thread_->joinable())
        {
            thread_->join();
        }
    }

    void Setup(const std::string& config_file, bool_t blocking_mode = true);

    void InstallCallback(const LiveCallbackType& handler) noexcept
    {
        live_callback_ = handler;
    }

private:
    bool_t GetParameters(const std::string& config_file);
    void   TimediffCallback(const HoloSyncDiffPacket& packet);
    void   OdometryCallback(const Odometryd& data, OdometrydWriterType& publisher, std::atomic<uint32_t>& frames);
    void   ImuCallback(const Imud& data, ImudWriterType& publisher);
    void   PositionCallback(const GnssPvt& data, GnssPvtWriterType& publisher);
    void   Background(const std::string& config_file);

    template <typename T>
    bool AdjustTimestamp(T& msg)
    {
        /* if NOT use gps timestamp */
        if (!use_gps_time_)
        {
            if (init_diff_ == std::numeric_limits<int64_t>::min())
            {
                uint32_t sec  = 0u;
                uint32_t nsec = 0u;
                if (!holo::os::GetSystemTime(sec, nsec))
                {
                    LOG(ERROR) << "failed to get system timestamp, will try next time";
                    return false;
                }
                uint64_t init_sys = holo::common::Timestamp(sec, nsec).ToNsec();
                uint64_t init_msg = msg.GetTimestamp().ToNsec();
                init_diff_        = init_sys - init_msg;
            }
            msg.SetTimestamp(msg.GetTimestamp() + holo::common::Duration(init_diff_));
        }
        /* if use external time compensation */
        if (TimediffBase::IsEnabled())
        {
            if (!TimediffBase::IsInitialized())
            {
                LOG(ERROR) << "timestamp compensation is not initialized";
                return false;
            }
            msg.SetTimestamp(msg.GetTimestamp() + holo::common::Duration(time_diff_));
        }
        return true;
    }

    // static void TransformToBody(Imud& imu, const holo::geometry::Pose3d& bTi)
    // {
    //     // const Pose3 bTi = extrinsic.GetPose();
    //     holo::numerics::Matrix3d const bRi = bTi.GetRotation().ToMatrix();
    //     holo::numerics::Vector3d const av = bRi * imu.GetAngularVelocity<holo::numerics::Vector3d>();
    //     holo::numerics::Vector3d       la = bRi * imu.GetLinearAcceleration<holo::numerics::Vector3d>();
    //     // Centrifugal acceleration
    //     holo::geometry::Point3d const  t = bTi.GetTranslation();
    //     holo::numerics::Vector3d const bti(t[0], t[1], t[2]);
    //     if (!bti.IsZero())
    //     {
    //         // Subtract out the the centripetal acceleration from the unbiased one
    //         // to get linear acceleration vector in the imu frame:
    //         holo::numerics::Matrix3d const body_Omega_body = av.ToSkewSymmetric();
    //         holo::numerics::Vector3d const b_velocity_bs   = body_Omega_body * bti;  // magnitude: omega * arm
    //         la -= body_Omega_body * b_velocity_bs;
    //     }
    //     imu.SetAngularVelocity(av.At(0), av.At(1), av.At(2));
    //     imu.SetLinearAcceleration(la.At(0), la.At(1), la.At(2));
    // }

private:
    std::shared_ptr<cmw_wrapper::BusType> bus_;
    OdometrydWriterType                   pub_odometry_;
    OdometrydWriterType                   pub_translation_odometry_;
    ImudWriterType                        pub_imu_;
    GnssPvtWriterType                     pub_gnss_pvt_;
    holo::common::Extrinsicf              extrinsic_;
    std::shared_ptr<NovatelDriver>        driver_;
    std::shared_ptr<std::thread>          thread_;

    bool_t      running_;
    std::string extrinsic_file_;
    std::string rtk_server_ip_;
    uint16_t    rtk_server_port_;
    bool_t      use_holo_basestation_;
    bool_t      use_gps_time_;
    // bool_t      imu_to_body_;

    std::string odometry_topic_;
    std::string odometry_translation_topic_;
    std::string imu_topic_;
    std::string gnss_pvt_topic_;
    std::string command_;

    std::atomic<uint32_t> frames_odometry_;
    std::atomic<uint32_t> frames_odometry_t_;
    std::atomic<uint32_t> frames_imu_;
    std::atomic<uint32_t> frames_gnss_pvt_;
    LiveCallbackType      live_callback_;
    int64_t               init_diff_;
};

}  // namespace holo_cmw

#endif
