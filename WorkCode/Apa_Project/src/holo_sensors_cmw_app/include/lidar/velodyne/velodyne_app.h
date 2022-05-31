/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file velodyne_app.h
 * @brief This header file define the app of velodyne driver
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/11/26
 */

#ifndef HOLO_CMW_APPS_LIDAR_VELODYNE_VELODYNE_APP_H
#define HOLO_CMW_APPS_LIDAR_VELODYNE_VELODYNE_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/lidar/velodyne/velodyne_converter.h>
#include <holo/sensors/lidar/velodyne/velodyne_driver.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <interface/interface_wrapper.h>
#include <utils/timediff_utils.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>

namespace holo_cmw
{
static constexpr size_t VELODYNE_CAPACITY = 1024 * 1024 * 4;

template <size_t PACKET_RATE = 760u>
class VelodyneDriverApp : public TimediffBase
{
public:
    using VelodyneScan         = holo::sensors::velodyne::VelodyneScan;
    using VelodyneDriver       = holo::sensors::velodyne::VelodyneDriver;
    using VelodynePacket       = holo::sensors::format::VelodynePacket;
    using VelodyneGpsPacket    = holo::sensors::format::VelodyneGpsPacket;
    using SerializerType       = holo::serialization::Serializer<false, 4>;
    using PointCloudType       = holo::sensors::velodyne::VelodynePcdConverter::PointCloudType;
    using PointCloudIpc        = holo::sensors::lidar::PointCloudIpc<PointCloudType>;
    using VelodynePcdConverter = holo::sensors::velodyne::VelodynePcdConverter;
    using LidarScan            = holo::sensors::format::LidarScan<VELODYNE_CAPACITY>;

    /**
     * @brief Construct a new Aceinna Driver object
     *
     * @param argc
     * @param argv
     * @param name
     */
    VelodyneDriverApp(int32_t id, const std::string& ns)
      : bus_(id, ns)
      , scan_data_{new uint8_t[CAPACITY](), std::default_delete<uint8_t[]>()}
      , scan_rate_(0)
      , pcd_counter_(0)
    {
    }

    /**
     * @brief setup this node
     *
     * @param config_file
     */
    void Setup(const std::string& config_file);

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
     * @brief      callback service for ...
     *
     * @param[in]  msg   the message comes from the ... driver
     *
     * @note       this routine fetch and publish the ... messages
     */
    void VelodyneCallbackSendScan(const VelodyneScan& msg);
    void VelodyneCallbackSavePcdToShm(const VelodyneScan& msg);
    void SavePcdToShm(const VelodyneScan& msg);

private:
    static constexpr size_t PACKET_SIZE = holo::sensors::velodyne::VELODYNE_PACKET_BYTE_SIZE;
    static constexpr size_t CAPACITY    = ((PACKET_SIZE + 3) / 4 * 4) * PACKET_RATE / 10 + 12u;

private:
    std::string                                      model_;
    uint32_t                                         rpm_;
    uint32_t                                         coord_;
    bool_t                                           use_gps_;
    bool_t                                           time_check_;
    std::string                                      scan_topic_;
    std::string                                      pcd_topic_;
    cmw_wrapper::BusType                             bus_;
    cmw_wrapper::BusType::WriterType<uint8_t*>       scan_pub_;
    std::shared_ptr<uint8_t>                         scan_data_;
    std::shared_ptr<VelodyneDriver>                  driver_;
    std::shared_ptr<UdpInterface<VelodynePacket>>    data_interface_;
    std::shared_ptr<UdpInterface<VelodyneGpsPacket>> sync_interface_;
    uint32_t                                         scan_rate_;
    bool_t                                           publish_scan_;
    std::string                                      extrinsic_;
    bool_t                                           use_compress_;
    std::shared_ptr<VelodynePcdConverter>            converter_;
    holo::yaml::Node                                 cvt_node_;
    holo::yaml::Node                                 crr_node_;
    std::shared_ptr<PointCloudIpc>                   pcd_ipc_;
    std::shared_ptr<LidarScan>                       lidar_scan_;
    cmw_wrapper::BusType::WriterType<uint64_t>       pcd_pub_;
    holo::common::SensorId                           sensor_id_;
    std::atomic<uint32_t>                            frames_;
    uint32_t                                         pcd_counter_;
};

}  // namespace holo_cmw

#endif
