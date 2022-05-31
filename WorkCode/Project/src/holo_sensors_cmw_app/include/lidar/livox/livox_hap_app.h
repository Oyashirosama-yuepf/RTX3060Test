/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file livox_hap_app.h
 * @brief This header file define the app of livox hap driver
 * @author wujie<wujie@holomatic.com>
 * @date 2021/08/19
 */

#ifndef HOLO_CMW_APPS_LIDAR_LIVOX_HAP_APP_H
#define HOLO_CMW_APPS_LIDAR_LIVOX_HAP_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/os/timer.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/format/holosync.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/livox/livox_converter.h>
#include <holo/sensors/lidar/livox/livox_hap_driver.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <interface/interface_wrapper.h>
#include <utils/timediff_utils.h>
#include <atomic>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>

#if defined(MDC_PRODUCTION_MDC610)
#include <holo/sensors/utils/mdc610_utils.h>
#endif

namespace holo_cmw
{
static constexpr size_t HAP_DATA_CAPACITY = 1024 * 1024 * 4;

template <typename LivoxPacketType>
class LivoxHapDriverApp : public TimediffBase
{
public:
    using Timestamp           = holo::common::Timestamp;
    using LivoxHapCmdPacket   = holo::sensors::format::LivoxHapCmdPacket;
    using LivoxScanType       = holo::sensors::livox::LivoxScan<LivoxPacketType>;
    using LivoxDriverType     = holo::sensors::livox::LivoxHapDriver<LivoxPacketType>;
    using SerializerType      = holo::serialization::Serializer<false, 4>;
    using LivoxHapControlInfo = holo::sensors::livox::LivoxHapControlInfo;
    using LiveCallbackType    = std::function<void(uint32_t, uint32_t)>;
    /* converter\ipc */
    using LivoxPcdConverter  = holo::sensors::livox::LivoxPcdConverter<LivoxPacketType>;
    using PointType          = holo::point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType     = holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(),
                                                          sizeof(PointType), holo::point_cloud::UnorganizedLayoutTag>;
    using PointCloudIpc      = holo::sensors::lidar::PointCloudIpc<PointCloudType>;
    using HoloSyncDiffPacket = holo::sensors::format::HoloSyncDiffPacket;
    using LidarScan          = holo::sensors::format::LidarScan<HAP_DATA_CAPACITY>;

    LivoxHapDriverApp(int32_t id, const std::string& ns)
      : TimediffBase()
      , scan_data_{new uint8_t[CAPACITY](), std::default_delete<uint8_t[]>()}
      , connected_(false)
      , start_sampling_(false)
      , frames_(0)
      , sensor_id_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
        bus_ = std::make_shared<cmw_wrapper::BusType>(id, ns);
    }
    LivoxHapDriverApp(std::shared_ptr<cmw_wrapper::BusType> bus)
      : TimediffBase()
      , bus_(bus)
      , scan_data_{new uint8_t[CAPACITY](), std::default_delete<uint8_t[]>()}
      , connected_(false)
      , start_sampling_(false)
      , frames_(0)
      , sensor_id_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
    }

    ~LivoxHapDriverApp()
    {
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
    bool GetParameters(const std::string& config_file);
    void CmdCallback(const LivoxHapCmdPacket& packet);
    void ScanDataCallback(const LivoxScanType& scan);
    void SavePcdToShm(const LivoxScanType& scan);
    void Background(const std::string& config_file);

private:
    static constexpr size_t CAPACITY       = 1024 * 1024 * 4;
    static const int32_t    COMPRESS_ACCEL = 1;

private:
    std::string device_ip_;
    uint16_t    broadcast_port_;
    uint16_t    localhost_port_;
    uint32_t    coord_;
    uint32_t    packet_rate_;
    uint32_t    scan_rate_;
    bool_t      time_check_;
    bool_t      use_compress_;
    // cmw_wrapper::BusType                       bus_;
    std::shared_ptr<cmw_wrapper::BusType>      bus_;
    cmw_wrapper::BusType::WriterType<uint8_t*> scan_pub_;
    cmw_wrapper::BusType::WriterType<uint64_t> pcd_pub_;
    std::string                                scan_topic_;
    std::string                                pcd_topic_;
    std::shared_ptr<LivoxDriverType>           driver_;
    bool_t                                     publish_scan_;
    std::shared_ptr<uint8_t>                   scan_data_;
    holo::bool_t                               connected_;
    holo::bool_t                               start_sampling_;
    std::atomic<uint32_t>                      frames_;
    std::string                                extrinsic_;
    holo::common::SensorId                     sensor_id_;
    std::shared_ptr<LivoxPcdConverter>         converter_;
    std::shared_ptr<PointCloudIpc>             pcd_ipc_;
    std::shared_ptr<LidarScan>                 lidar_scan_;
    uint32_t                                   ns_per_scan_;
    std::shared_ptr<std::thread>               thread_;
    LiveCallbackType                           live_callback_;
#if defined(MDC_PRODUCTION_MDC610)
    holo::common::Duration timediff_;
#endif
};
}  // namespace holo_cmw

#endif
