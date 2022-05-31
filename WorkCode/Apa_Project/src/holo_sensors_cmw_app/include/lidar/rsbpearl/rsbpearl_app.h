/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsbpearl_app.h
 * @brief This header file define the app of rsbpearl driver
 * @author wujie<wujie@holomatic.com>
 * @date 2022/01/11
 */

#ifndef HOLO_CMW_APPS_LIDAR_RSBPEARL_APP_H
#define HOLO_CMW_APPS_LIDAR_RSBPEARL_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/os/time.h>
#include <holo/os/timer.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/lidar/rsbpearl/rsbpearl_converter.h>
#include <holo/sensors/lidar/rsbpearl/rsbpearl_driver.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <interface/interface_wrapper.h>
#include <utils/timediff_utils.h>
#include <atomic>
#include <cmw_wrapper/utils/cxxopts.hpp>

namespace holo_cmw
{
static constexpr size_t RSBP_DATA_CAPACITY = 1024 * 1024 * 4;

class RsbpearlDriverApp : public TimediffBase
{
public:
    using SerializerType      = holo::serialization::Serializer<false, 4>;
    using RsbpearlScanType    = holo::sensors::rsbpearl::RsbpearlScan;
    using RsbpearlPacket      = holo::sensors::rsbpearl::RsbpearlPacket;
    using RsbpearlDriver      = holo::sensors::rsbpearl::RsbpearlDriver;
    using RsbpearlPacketDIFOP = holo::sensors::format::RsbpearlPacketDIFOP;
    using RsbpearlPacketUCWP  = holo::sensors::format::RsbpearlPacketUCWP;
    using LidarScan           = holo::sensors::format::LidarScan<RSBP_DATA_CAPACITY>;
    using CompressUtils       = holo::sensors::CompressUtils;
    /* converter \ ipc */
    using RsbpearlConverter  = holo::sensors::rsbpearl::RsbpearlPcdConverter;
    using PointType          = holo::point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType     = holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(),
                                                          sizeof(PointType), holo::point_cloud::UnorganizedLayoutTag>;
    using PointCloudIpc      = holo::sensors::lidar::PointCloudIpc<PointCloudType>;
    using LiveCallbackType   = std::function<void(uint32_t, uint32_t)>;
    using HoloSyncDiffPacket = holo::sensors::format::HoloSyncDiffPacket;

    RsbpearlDriverApp(int32_t id, const std::string& ns)
      : TimediffBase()
      , coord_()
      , packet_rate_(0)
      , scan_rate_(0)
      , sensor_id_(0)
      , use_compress_(false)
      , time_check_(false)
      , publish_scan_(false)
      , scan_data_{new uint8_t[RSBP_DATA_CAPACITY](), std::default_delete<uint8_t[]>()}
      , frames_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
        bus_ = std::make_shared<cmw_wrapper::BusType>(id, ns);
    }

    RsbpearlDriverApp(std::shared_ptr<cmw_wrapper::BusType> bus)
      : TimediffBase()
      , coord_()
      , packet_rate_(0)
      , scan_rate_(0)
      , sensor_id_(0)
      , use_compress_(false)
      , time_check_(false)
      , publish_scan_(false)
      , bus_(bus)
      , scan_data_{new uint8_t[RSBP_DATA_CAPACITY](), std::default_delete<uint8_t[]>()}
      , frames_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
    }
    ~RsbpearlDriverApp()
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
    void ScanDataCallback(const RsbpearlScanType& scan);
    void DeviceInfoCallback(const RsbpearlPacketDIFOP& info_packet);
    void SavePcdToShm(const RsbpearlScanType& scan);
    void Background(const std::string& config_file);

private:
    uint32_t               coord_;
    uint32_t               packet_rate_;
    uint32_t               scan_rate_;
    std::string            extrinsic_;
    holo::common::SensorId sensor_id_;
    bool_t                 use_compress_;
    bool_t                 time_check_;
    bool_t                 publish_scan_;
    // cmw_wrapper::BusType                       bus_;
    std::shared_ptr<cmw_wrapper::BusType>      bus_;
    cmw_wrapper::BusType::WriterType<uint64_t> pcd_pub_;
    cmw_wrapper::BusType::WriterType<uint8_t*> scan_pub_;
    std::string                                scan_topic_;
    std::string                                pcd_topic_;
    std::shared_ptr<RsbpearlDriver>            driver_;
    std::shared_ptr<RsbpearlConverter>         converter_;
    std::shared_ptr<LidarScan>                 lidar_scan_;
    std::shared_ptr<PointCloudIpc>             pcd_ipc_;
    std::shared_ptr<uint8_t>                   scan_data_;
    std::atomic<uint32_t>                      frames_;
    std::shared_ptr<std::thread>               thread_;
    LiveCallbackType                           live_callback_;
};
}  // namespace holo_cmw

#endif