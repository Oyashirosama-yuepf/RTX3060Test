/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pandar_app.h
 * @brief This header file define the app of pandar driver
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2021/03/19
 */

#ifndef HOLO_CMW_APPS_LIDAR_PANDAR_PANDAR_APP_H
#define HOLO_CMW_APPS_LIDAR_PANDAR_PANDAR_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/pandar/pandar_converter.h>
#include <holo/sensors/lidar/pandar/pandar_driver.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <interface/interface_wrapper.h>
#include <utils/timediff_utils.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>
#if defined(CMW_WRAPPER_ENABLE_ROS)
#include <holo_base_msg/ros_msg/sensors/pandar_traits.h>
#endif

namespace holo_cmw
{
static constexpr size_t PANDAR_DATA_CAPACITY = 1024 * 1024 * 4;

template <size_t PACKET_RATE>
class PandarDriverApp : public TimediffBase
{
public:
    using PandarScan         = holo::sensors::pandar::PandarScan;
    using PandarDriver       = holo::sensors::pandar::PandarDriver;
    using PandarPacket       = holo::sensors::format::PandarPacket;
    using PandarGpsPacket    = holo::sensors::format::PandarGpsPacket;
    using SerializerType     = holo::serialization::Serializer<false, 4>;
    using PandarPcdConverter = holo::sensors::pandar::PandarPcdConverter;
    using PointCloudType     = holo::sensors::pandar::PandarPcdConverter::PointCloudType;
    using PointCloudIpc      = holo::sensors::lidar::PointCloudIpc<PointCloudType>;
    using LiveCallbackType   = std::function<void(uint32_t, uint32_t)>;
    using LidarScan          = holo::sensors::format::LidarScan<PANDAR_DATA_CAPACITY>;

    /**
     * @brief Construct a new Aceinna Driver object
     *
     * @param argc
     * @param argv
     * @param name
     */
    PandarDriverApp(int32_t id, const std::string& ns)
      : scan_data_{new uint8_t[CAPACITY](), std::default_delete<uint8_t[]>()}
      , pcd_counter_(0)
      , frames_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
        bus_ = std::make_shared<cmw_wrapper::BusType>(id, ns);
    }

    PandarDriverApp(std::shared_ptr<cmw_wrapper::BusType> bus)
      : bus_(bus)
      , scan_data_{new uint8_t[CAPACITY](), std::default_delete<uint8_t[]>()}
      , pcd_counter_(0)
      , frames_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
    }

    ~PandarDriverApp()
    {
        if (thread_ && thread_->joinable())
        {
            thread_->join();
        }
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
     * @brief      callback service for pandar
     *
     * @param[in]  msg   the message comes from the pandar driver
     *
     * @note       this routine fetch and publish the pandar messages
     */
    void DataCallbackSendScan(const PandarScan& msg);

    void DataCallbackSavePcdToShm(const PandarScan& msg);
    void Background(const std::string& config_file);

private:
    // static constexpr size_t PACKET_SIZE = holo::sensors::pandar::PANDAR_PACKET_BYTE_SIZE;
    static constexpr size_t CAPACITY = 1024 * 1024 * 2;

private:
    uint32_t    rpm_;
    uint32_t    coord_;
    bool_t      use_gps_;
    bool_t      time_check_;
    std::string scan_topic_;
    std::string pcd_topic_;
    // cmw_wrapper::BusType                           bus_;
    std::shared_ptr<cmw_wrapper::BusType> bus_;
#ifdef CMW_WRAPPER_ENABLE_ROS
    cmw_wrapper::BusType::WriterType<PandarScan, ros_wrapper::DefaultConversionTraits<PandarScan>> scan_pub_;
#else
    cmw_wrapper::BusType::WriterType<uint8_t*> scan_pub_;
#endif  // ROS

    std::shared_ptr<uint8_t>                       scan_data_;
    std::shared_ptr<PandarDriver>                  driver_;
    std::shared_ptr<UdpInterface<PandarPacket>>    data_interface_;
    std::shared_ptr<UdpInterface<PandarGpsPacket>> sync_interface_;
    uint32_t                                       scan_rate_;
    bool_t                                         publish_scan_;
    std::string                                    extrinsic_;
    bool_t                                         use_compress_;
    std::shared_ptr<PandarPcdConverter>            converter_;
    holo::yaml::Node                               cvt_node_;
    holo::yaml::Node                               crr_node_;
    std::shared_ptr<PointCloudIpc>                 pcd_ipc_;
    std::shared_ptr<LidarScan>                     lidar_scan_;
    cmw_wrapper::BusType::WriterType<uint64_t>     pcd_pub_;
    holo::common::SensorId                         sensor_id_;
    uint32_t                                       pcd_counter_;
    std::atomic<uint32_t>                          frames_;
    std::shared_ptr<std::thread>                   thread_;
    LiveCallbackType                               live_callback_;
};

}  // namespace holo_cmw

#endif
