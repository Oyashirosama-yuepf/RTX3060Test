/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#ifndef _HOLO_CMW_APPS_STARNETO_COMMON_APP_H
#define _HOLO_CMW_APPS_STARNETO_COMMON_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/os/time.h>
#include <holo/os/timer.h>
#include <holo/sensors/gnss/starneto/starneto.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_c/core/types.h>
#include <interface/interface_wrapper.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
#include <traits.h>
#else
#include <holo_base_msg/traits.h>
#endif

namespace holo_cmw
{
using holo::sensors::starneto::StarnetoDriver;

enum class StarnetoMsgType : int32_t
{
    ODOMETRY   = 0,
    ODOMETRY_T = 1,
    IMU        = 2,
    GNSS_PVT   = 3,
};

template <typename Td, typename Ti>
class StarnetoAppT
{
public:
    using GnssPvt          = holo::common::GnssPvt;
    using Imud             = holo::common::Imud;
    using Odometryd        = holo::common::OdometryT<float64_t>;
    using LiveCallbackType = std::function<void(uint32_t, uint32_t)>;

#if defined(CMW_WRAPPER_ENABLE_ROS)
    using OdometrydWriterType =
        cmw_wrapper::BusType::WriterType<Odometryd, ros_wrapper::DefaultConversionTraits<Odometryd>>;
    using ImudWriterType    = cmw_wrapper::BusType::WriterType<Imud, ros_wrapper::DefaultConversionTraits<Imud>>;
    using GnssPvtWriterType = cmw_wrapper::BusType::WriterType<GnssPvt, ros_wrapper::DefaultConversionTraits<GnssPvt>>;
#else
    using OdometrydWriterType = cmw_wrapper::BusType::WriterType<Odometryd>;
    using ImudWriterType      = cmw_wrapper::BusType::WriterType<Imud>;
    using GnssPvtWriterType   = cmw_wrapper::BusType::WriterType<GnssPvt>;
#endif

    StarnetoAppT(int32_t id, const std::string& ns)
      : thread_(nullptr)
      , running_(true)
      , frames_odometry_()
      , frames_odometry_t_()
      , frames_imu_()
      , frames_gnss_pvt_()
      , live_callback_(nullptr)
    {
        bus_ = std::make_shared<cmw_wrapper::BusType>(id, ns);
    }

    StarnetoAppT(std::shared_ptr<cmw_wrapper::BusType> bus)
      : bus_(bus)
      , thread_(nullptr)
      , running_(true)
      , frames_odometry_()
      , frames_odometry_t_()
      , frames_imu_()
      , frames_gnss_pvt_()
      , live_callback_(nullptr)
    {
    }

    ~StarnetoAppT()
    {
        running_ = false;
        if (thread_ && thread_->joinable())
        {
            thread_->join();
        }
    }

    void Setup(const std::string& config_file, bool_t blocking_mode = true);
    void InstallLiveCallback(const LiveCallbackType& handler) noexcept
    {
        live_callback_ = handler;
    }

private:
    bool_t GetParameters(const std::string& config_file);
    void   OdometryCallbackStarneto(const Odometryd& data, OdometrydWriterType& publisher);
    void   ImuCallbackStarneto(const Imud& data, ImudWriterType& publisher);
    void   PositionCallbackStarneto(const GnssPvt& data, GnssPvtWriterType& publisher);
    void   Background();

private:
    std::shared_ptr<cmw_wrapper::BusType> bus_;
    OdometrydWriterType                   pub_odometry_;
    OdometrydWriterType                   pub_translation_odometry_;
    ImudWriterType                        pub_imu_;
    GnssPvtWriterType                     pub_gnss_pvt_;
    std::shared_ptr<Td>                   driver_;
    std::shared_ptr<Ti>                   interface_;
    std::shared_ptr<std::thread>          thread_;

    bool_t      running_;
    std::string extrinsic_file_;
    std::string rtk_server_ip_;
    uint16_t    rtk_server_port_;
    bool_t      use_holo_basestation_;
    bool_t      use_gps_time_;

    std::string odometry_topic_;
    std::string odometry_translation_topic_;
    std::string imu_topic_;
    std::string gnss_pvt_topic_;

    std::atomic<uint32_t> frames_odometry_;
    std::atomic<uint32_t> frames_odometry_t_;
    std::atomic<uint32_t> frames_imu_;
    std::atomic<uint32_t> frames_gnss_pvt_;
    LiveCallbackType      live_callback_;
};
}  // namespace holo_cmw
#endif  // !_HOLO_CMW_APPS_STARNETO_COMMON_APP_H