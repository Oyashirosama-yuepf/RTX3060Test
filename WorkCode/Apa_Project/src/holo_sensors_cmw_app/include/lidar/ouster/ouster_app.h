
/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ouster_app.h
 * @brief This header file define the app of ouster driver
 * @author yinweigen<yinweigen@holomatic.com>
 * @date 2022/01/24
 */

#ifndef HOLO_CMW_APPS_LIDAR_OUSTER_APP_H
#define HOLO_CMW_APPS_LIDAR_OUSTER_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/sensors/lidar/ouster/ouster_driver.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <interface/interface_wrapper.h>
#if defined(CMW_WRAPPER_ENABLE_ROS)
#include <holo_base_msg/ros_msg/sensors/ouster_traits.h>
#endif

namespace holo_cmw {
template <size_t PACKET_RATE> class OusterDriverApp {
public:
  using OusterScan        = holo::sensors::ouster::OusterScan;
  using OusterDriver      = holo::sensors::ouster::OusterDriver;
  using OusterPacket      = holo::sensors::format::OusterPacket;
  using SerializerType    = holo::serialization::Serializer<false, 4>;
  using LiveCallbackType  = std::function<void(uint32_t, uint32_t)>;

  OusterDriverApp(int32_t id, const std::string &ns)
    : scan_data_{new uint8_t[CAPACITY](),std::default_delete<uint8_t[]>()}
    , frames_(0)
    , thread_(nullptr)
    , live_callback_(nullptr)
  {
      bus_ = std::make_shared<cmw_wrapper::BusType>(id, ns);
  }

  OusterDriverApp(std::shared_ptr<cmw_wrapper::BusType> bus)
    : bus_(bus)
    , scan_data_{new uint8_t[CAPACITY](),std::default_delete<uint8_t[]>()}
    , frames_(0)
    , thread_(nullptr)
    , live_callback_(nullptr)
  {
  }

  ~OusterDriverApp()
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
  bool GetParamters(const std::string &config_file);

  void DataCallbackSendScan(const OusterScan &msg);
  void Background();

private:
  static constexpr size_t CAPACITY = 1024 * 1024 * 4;

private:
#ifdef CMW_WRAPPER_ENABLE_ROS
  cmw_wrapper::BusType::WriterType<OusterScan, ros_wrapper::DefaultConversionTraits<OusterScan>>    scan_pub_;
#else
  cmw_wrapper::BusType::WriterType<uint8_t *>                   scan_pub_;
#endif
  uint32_t                                                      coord_;
  bool_t                                                        time_check_;
  std::string                                                   scan_topic_;
  // cmw_wrapper::BusType                                          bus_;
  std::shared_ptr<cmw_wrapper::BusType>                         bus_;
  std::shared_ptr<uint8_t>                                      scan_data_;
  std::shared_ptr<OusterDriver>                                 driver_;
  std::shared_ptr<UdpInterface<OusterPacket>>                   data_interface_;
  std::shared_ptr<TcpcliInterface<OusterDriver::RawbufferType>> ctrl_interface_;
  uint32_t                                                      scan_rate_;
  bool_t                                                        publish_scan_;
  std::string                                                   extrinsic_;
  bool_t                                                        use_compress_;
  holo::common::SensorId                                        sensor_id_;
  std::string                                                   lidar_mode_;
  std::string                                                   udp_port_lidar_;
  std::string                                                   udp_port_imu_;
  std::string                                                   udp_ip_;
  std::atomic<uint32_t>                                         frames_;
  std::shared_ptr<std::thread>                                  thread_;
  LiveCallbackType                                              live_callback_;
};

} // namespace holo_cmw

#endif
