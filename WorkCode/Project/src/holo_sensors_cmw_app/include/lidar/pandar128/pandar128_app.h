/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pandar128_app.h
 * @brief This header file define the app of pandar128 driver
 * @author wujie<wujie@holomatic.com>
 * @date 2021/12/30
 */

#ifndef HOLO_CMW_APPS_LIDAR_PANDAR128_APP_H
#define HOLO_CMW_APPS_LIDAR_PANDAR128_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/pandar128/pandar128_converter.h>
#include <holo/sensors/lidar/pandar128/pandar128_driver.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/thread/thread_pool.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <interface/interface_wrapper.h>
#include <utils/timediff_utils.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>

namespace holo_cmw
{
static constexpr size_t P128_DATA_CAPACITY = 1024 * 1024 * 4;

class Pandar128DriverApp : public TimediffBase
{
public:
    using Pandar128Scan         = holo::sensors::pandar128::Pandar128Scan;
    using Pandar128Driver       = holo::sensors::pandar128::Pandar128Driver;
    using Pandar128Packet       = holo::sensors::format::Pandar128Packet;
    using Pandar128GpsPacket    = holo::sensors::format::Pandar128GpsPacket;
    using SerializerType        = holo::serialization::Serializer<false, 4>;
    using Pandar128PcdConverter = holo::sensors::pandar128::Pandar128PcdConverter;
    using PointCloudType        = holo::sensors::pandar128::Pandar128PcdConverter::PointCloudType;
    using LidarScan             = holo::sensors::format::LidarScan<P128_DATA_CAPACITY>;
    using PointCloudIpc         = holo::sensors::lidar::PointCloudIpc<PointCloudType>;
    using ThreadPool            = holo::thread::ThreadPool;
    using LiveCallbackType      = std::function<void(uint32_t, uint32_t)>;
    using HoloSyncDiffPacket    = holo::sensors::format::HoloSyncDiffPacket;

    /**
     * @brief Construct a new pandar128 Driver object
     *
     * @param argc
     * @param argv
     * @param name
     */
    Pandar128DriverApp(int32_t id, const std::string& ns)
      : TimediffBase()
      , rpm_(0)
      , coord_(0)
      , use_gps_(false)
      , time_check_(false)
      , packet_rate_(0)
      , scan_rate_(0)
      , publish_scan_(false)
      , max_thr_num_(0)
      , sensor_id_(0)
      , scan_data_{new uint8_t[P128_DATA_CAPACITY](), std::default_delete<uint8_t[]>()}
      , frames_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
        bus_ = std::make_shared<cmw_wrapper::BusType>(id, ns);
    }

    Pandar128DriverApp(std::shared_ptr<cmw_wrapper::BusType> bus)
      : TimediffBase()
      , rpm_(0)
      , coord_(0)
      , use_gps_(false)
      , time_check_(false)
      , packet_rate_(0)
      , scan_rate_(0)
      , publish_scan_(false)
      , max_thr_num_(0)
      , sensor_id_(0)
      , bus_(bus)
      , scan_data_{new uint8_t[P128_DATA_CAPACITY](), std::default_delete<uint8_t[]>()}
      , frames_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
    }

    ~Pandar128DriverApp()
    {
        if (thread_ && thread_->joinable())
        {
            thread_->join();
        }
        thread_pool_ptr_->WaitAndDestroy();
    }

    /**
     * @brief setup this node
     *
     * @param config_file
     */
    void Setup(const std::string& config_file, bool_t blocking_mode = true);
    void InstallLiveCallback(const LiveCallbackType& handler) noexcept
    {
        live_callback_ = handler;
    }

private:
    /**
     * @brief      Gets the parameters.
     *
     * @param[in]  config_file  The configuration file
     *
     * @return     The parameters.
     */
    bool GetParameters(const std::string& config_file);

    /**
     * @brief      callback service for pandar128
     *
     * @param[in]  scan the message comes from the pandar128 driver
     *
     * @note       this routine fetch and publish the pandar128 messages
     */
    void ScanDataCallback(const Pandar128Scan& scan);

    void SavePcdToShm(const Pandar128Scan& scan);
    void SavePcdToShmDataCallback(const Pandar128Scan& scan);
    void Background(const std::string& config_file);

private:
    uint32_t               rpm_;
    uint32_t               coord_;
    bool_t                 use_gps_;
    bool_t                 time_check_;
    uint32_t               packet_rate_;
    uint32_t               scan_rate_;
    bool_t                 publish_scan_;
    uint32_t               max_thr_num_;
    bool_t                 use_compress_;
    holo::yaml::Node       correct_node_;
    holo::yaml::Node       luminous_time_node_;
    std::string            extrinsic_;
    holo::common::SensorId sensor_id_;
    // cmw_wrapper::BusType                       bus_;
    std::shared_ptr<cmw_wrapper::BusType>      bus_;
    cmw_wrapper::BusType::WriterType<uint8_t*> scan_pub_;
    cmw_wrapper::BusType::WriterType<uint64_t> pcd_pub_;
    std::string                                scan_topic_;
    std::string                                pcd_topic_;
    std::shared_ptr<Pandar128Driver>           driver_;
    std::shared_ptr<Pandar128PcdConverter>     converter_;
    std::shared_ptr<PointCloudIpc>             pcd_ipc_;
    std::shared_ptr<LidarScan>                 lidar_scan_;
    std::shared_ptr<ThreadPool>                thread_pool_ptr_;
    std::shared_ptr<uint8_t>                   scan_data_;
    uint32_t                                   frames_;
    std::shared_ptr<std::thread>               thread_;
    LiveCallbackType                           live_callback_;
};

}  // namespace holo_cmw

#endif
