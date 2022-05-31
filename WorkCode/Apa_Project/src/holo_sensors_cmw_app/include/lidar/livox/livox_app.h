/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file livox_app.h
 * @brief This header file define the app of livox driver
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2021/04/20
 */

#ifndef HOLO_CMW_APPS_LIDAR_LIVOX_LIVOX_APP_H
#define HOLO_CMW_APPS_LIDAR_LIVOX_LIVOX_APP_H

#include <atomic>
#include <condition_variable>
#include <exception>
#include <mutex>

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/os/timer.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/format/holosync.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/livox/livox_converter.h>
#include <holo/sensors/lidar/livox/livox_driver.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <interface/interface_wrapper.h>
#include <utils/timediff_utils.h>
#include <cmw_wrapper/utils/cxxopts.hpp>

namespace holo_cmw
{
static constexpr size_t LIVOX_DATA_CAPACITY = 1024 * 1024 * 4;

template <typename LivoxPacketType>
class LivoxDriverApp : public TimediffBase
{
public:
    using HoloSyncPacket   = holo::sensors::format::HoloSyncPacket;
    using LivoxCmdPacket   = holo::sensors::format::LivoxCmdPacket;
    using LivoxScanType    = holo::sensors::livox::LivoxScan<LivoxPacketType>;
    using LivoxDriverType  = holo::sensors::livox::LivoxDriver<LivoxPacketType>;
    using SerializerType   = holo::serialization::Serializer<false, 4>;
    using LiveCallbackType = std::function<void(uint32_t, uint32_t)>;
    /* converter\ipc */
    using LivoxPcdConverter  = holo::sensors::livox::LivoxPcdConverter<LivoxPacketType>;
    using PointType          = holo::point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType     = holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(),
                                                          sizeof(PointType), holo::point_cloud::UnorganizedLayoutTag>;
    using PointCloudIpc      = holo::sensors::lidar::PointCloudIpc<PointCloudType>;
    using HoloSyncDiffPacket = holo::sensors::format::HoloSyncDiffPacket;
    using LidarScan          = holo::sensors::format::LidarScan<LIVOX_DATA_CAPACITY>;

    LivoxDriverApp(int32_t id, const std::string& ns)
      : TimediffBase()
      , scan_data_{new uint8_t[CAPACITY](), std::default_delete<uint8_t[]>()}
      , sensor_id_(0)
      , connected_(false)
      , start_sampling_(false)
      , frames_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
        bus_ = std::make_shared<cmw_wrapper::BusType>(id, ns);
    }

    LivoxDriverApp(std::shared_ptr<cmw_wrapper::BusType> bus)
      : TimediffBase()
      , bus_(bus)
      , scan_data_{new uint8_t[CAPACITY](), std::default_delete<uint8_t[]>()}
      , sensor_id_(0)
      , connected_(false)
      , start_sampling_(false)
      , frames_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
    }

    ~LivoxDriverApp()
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
    void CmdCallback(const LivoxCmdPacket& packet, void* args, struct sockaddr_in* dest);
    void MonCallback(const LivoxCmdPacket& packet, void* args, struct sockaddr_in* dest);
    void SyncCallback(const HoloSyncPacket& packet, holo::common::Timestamp& stamp);
    void ScanDataCallback(const LivoxScanType& msg);
    void SavePcdToShm(const LivoxScanType& scan);
    void Background(const std::string& config_file);

private:
    static constexpr size_t CAPACITY       = 1024 * 1024 * 4;
    static const int32_t    COMPRESS_ACCEL = 1;

private:
    std::string  device_ip_;
    uint16_t     broadcast_port_;
    holo::bool_t sync_available_;
    uint16_t     localhost_port_;
    uint32_t     coord_;
    uint32_t     packet_rate_;
    uint32_t     scan_rate_;
    std::string  scan_topic_;
    std::string  pcd_topic_;
    bool_t       time_check_;
    bool_t       use_compress_;
    // cmw_wrapper::BusType                       bus_;
    std::shared_ptr<cmw_wrapper::BusType>      bus_;
    cmw_wrapper::BusType::WriterType<uint8_t*> scan_pub_;
    cmw_wrapper::BusType::WriterType<uint64_t> pcd_pub_;
    bool_t                                     publish_scan_;
    std::shared_ptr<uint8_t>                   scan_data_;
    std::shared_ptr<LivoxDriverType>           driver_;
    std::string                                extrinsic_;
    holo::common::SensorId                     sensor_id_;
    std::shared_ptr<LivoxPcdConverter>         converter_;
    std::shared_ptr<PointCloudIpc>             pcd_ipc_;
    std::shared_ptr<LidarScan>                 lidar_scan_;
    holo::bool_t                               connected_;
    holo::bool_t                               start_sampling_;
    std::mutex                                 broadcast_mtx_;
    std::condition_variable                    broadcast_cv_;
    std::mutex                                 synchronization_mtx_;
    std::condition_variable                    synchronization_cv_;
    std::atomic<uint32_t>                      frames_;
    uint32_t                                   ns_per_scan_;
    std::shared_ptr<std::thread>               thread_;
    LiveCallbackType                           live_callback_;
};

}  // namespace holo_cmw

#endif
