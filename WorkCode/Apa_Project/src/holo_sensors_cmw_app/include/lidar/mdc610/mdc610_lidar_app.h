/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc610_lidar_app.h
 * @brief This header file define the app of mdc610 lidar driver
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2021/07/03
 */

#ifndef HOLO_CMW_APPS_LIDAR_MDC610_MDC610_LIDAR_APP_H
#define HOLO_CMW_APPS_LIDAR_MDC610_MDC610_LIDAR_APP_H

#include <atomic>
#include <exception>

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/log/hololog.h>
#include <holo/os/time.h>
#include <holo/os/timer.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/interface/mdc610_lidar_interface.h>
#include <holo/sensors/lidar/mdc610/mdc610_lidar_converter.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <interface/interface_wrapper.h>
#include <cmw_wrapper/utils/cxxopts.hpp>

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
#include <traits.h>
#else
#include <holo_base_msg/traits.h>
#endif

namespace holo_cmw
{
static constexpr size_t CAPACITY = 1024 * 1024 * 4;

class Mdc610LidarDriverApp
{
public:
    using SerializerType     = holo::serialization::Serializer<false, 4>;
    using LidarScan          = holo::sensors::format::LidarScan<CAPACITY>;
    using LidarFrame         = holo::sensors::mdc610::huawei::LidarFrame<holo::sensors::mdc610::huawei::PointXYZIRT>;
    using Mdc610ScanType     = holo::sensors::mdc610::Mdc610Scan;
    using Mdc610PcdConverter = holo::sensors::mdc610::Mdc610Converter;
    using PointCloudType     = typename holo::sensors::mdc610::Mdc610Converter::PointCloudType;
    using PointCloudIpc      = holo::sensors::lidar::PointCloudIpc<PointCloudType>;

    Mdc610LidarDriverApp(int32_t id, const std::string& ns)
      : bus_(id, ns), scan_data_{new uint8_t[CAPACITY](), std::default_delete<uint8_t[]>()}, frames_(0)
    {
    }
    ~Mdc610LidarDriverApp() = default;

    void Setup(const std::string& config_file);

private:
    bool GetParameters(const std::string& config_file);
    void ScanDataCallback(std::shared_ptr<const LidarFrame> frame);
    void SavePcdDataCallback(std::shared_ptr<const LidarFrame> frame);

private:
    uint32_t               coord_;
    uint32_t               instance_;
    std::string            scan_topic_;
    std::string            pcd_topic_;
    std::string            extrinsic_;
    holo::common::SensorId sensor_id_;
    holo::bool_t           use_compress_;
    holo::bool_t           publish_scan_;
    cmw_wrapper::BusType   bus_;
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    cmw_wrapper::BusType::WriterType<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>> scan_pub_;
    cmw_wrapper::BusType::WriterType<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>        pcd_pub_;
#else
    cmw_wrapper::BusType::WriterType<uint8_t*> scan_pub_;
    cmw_wrapper::BusType::WriterType<uint64_t> pcd_pub_;
#endif
    std::shared_ptr<uint8_t>            scan_data_;
    std::atomic<uint32_t>               frames_;
    std::shared_ptr<LidarScan>          lidar_scan_;
    std::shared_ptr<PointCloudIpc>      pcd_ipc_;
    std::shared_ptr<Mdc610PcdConverter> converter_;
};

}  // namespace holo_cmw

#endif
