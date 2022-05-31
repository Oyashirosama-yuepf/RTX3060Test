/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsruby_app.h
 * @brief This header file define the app of rsruby driver
 * @author wujie<wujie@holomatic.com>
 * @date 2021/10/25
 */

#ifndef HOLO_CMW_APPS_LIDAR_RSRUBY_RSRUBY_APP_H
#define HOLO_CMW_APPS_LIDAR_RSRUBY_RSRUBY_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/os/time.h>
#include <holo/os/timer.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/lidar/rsruby/rsruby_converter.h>
#include <holo/sensors/lidar/rsruby/rsruby_driver.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/thread/thread_pool.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <interface/interface_wrapper.h>
#include <atomic>
#include <cmw_wrapper/utils/cxxopts.hpp>

namespace holo_cmw
{
static constexpr size_t RSRUBY_CAPACITY = 1024 * 1024 * 4;

class RsrubyDriverApp
{
public:
    using SerializerType         = holo::serialization::Serializer<false, 4>;
    using RsrubyScanType         = holo::sensors::rsruby::RsrubyScan;
    using RsrubyPacket           = holo::sensors::rsruby::RsrubyPacket;
    using RsrubyDriver           = holo::sensors::rsruby::RsrubyDriver;
    using LidarScan              = holo::sensors::format::LidarScan<RSRUBY_CAPACITY>;
    using RsrubyDeviceInfoPacket = holo::sensors::rsruby::RsrubyDeviceInfoPacket;
    /* converter\ipc */
    using RsrubyConverter        = holo::sensors::rsruby::RsrubyPcdConverter;
    using PointType              = holo::point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType         = holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(),
                                                                 sizeof(PointType), holo::point_cloud::UnorganizedLayoutTag>;
    using PointCloudIpc          = holo::sensors::lidar::PointCloudIpc<PointCloudType>;
    using ThreadPool             = holo::thread::ThreadPool;
    using LiveCallbackType       = std::function<void(uint32_t, uint32_t)>;

    RsrubyDriverApp(int32_t id, const std::string& ns)
      : scan_data_{new uint8_t[RSRUBY_CAPACITY](), std::default_delete<uint8_t[]>()}
      , frames_(0)
      , sensor_id_(0)
      , max_thr_num_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
        bus_ = std::make_shared<cmw_wrapper::BusType>(id, ns);
    }

    RsrubyDriverApp(std::shared_ptr<cmw_wrapper::BusType> bus)
      : bus_(bus)
      , scan_data_{new uint8_t[RSRUBY_CAPACITY](), std::default_delete<uint8_t[]>()}
      , frames_(0)
      , sensor_id_(0)
      , max_thr_num_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
    }

    ~RsrubyDriverApp()
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
    void ScanDataCallback(const RsrubyScanType& scan);
    void AddTask(const RsrubyScanType& scan);
    void SavePcdToShm(const RsrubyScanType& scan);
    void Background();

private:
    uint32_t                                   coord_;
    std::string                                scan_topic_;
    std::string                                pcd_topic_;
    bool_t                                     use_compress_;
    bool_t                                     time_check_;
    bool_t                                     publish_scan_;
    // cmw_wrapper::BusType                       bus_;
    std::shared_ptr<cmw_wrapper::BusType>      bus_;
    cmw_wrapper::BusType::WriterType<uint8_t*> scan_pub_;
    cmw_wrapper::BusType::WriterType<uint64_t> pcd_pub_;
    std::shared_ptr<uint8_t>                   scan_data_;
    std::shared_ptr<LidarScan>                 lidar_scan_;
    std::shared_ptr<RsrubyDriver>              driver_;
    std::atomic<uint32_t>                      frames_;
    uint32_t                                   packet_rate_;
    uint32_t                                   scan_rate_;
    holo::common::SensorId                     sensor_id_;
    std::string                                extrinsic_;
    std::shared_ptr<ThreadPool>                thread_pool_ptr_;
    std::shared_ptr<RsrubyConverter>           converter_;
    std::shared_ptr<PointCloudIpc>             pcd_ipc_;
    uint32_t                                   max_thr_num_;
    std::shared_ptr<std::thread>               thread_;
    LiveCallbackType                           live_callback_;
};
}  // namespace holo_cmw

#endif
