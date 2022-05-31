/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsm1_converter.h
 * @brief This header file define the rsm1 scan converter
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/08/18
 */

#ifndef HOLO_CMW_APPS_LIDAR_RSM1_RSM1_CONVERTER_H
#define HOLO_CMW_APPS_LIDAR_RSM1_RSM1_CONVERTER_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/extrinsic.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/libply/libply.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/lidar/rsm1/rsm1_converter.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo/serialization/deserializer.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <holo_c/core/types.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>

namespace holo_cmw
{
static constexpr size_t CAPACITY = 1024 * 1024 * 4;

class Rsm1ConverterApp
{
public:
    using DeserializerType = holo::serialization::Deserializer<false, 4>;
    using Rsm1ScanType     = holo::sensors::rsm1::Rsm1Scan;
    using PointCloudType   = typename holo::sensors::rsm1::Rsm1PcdConverter::PointCloudType;
    using PointCloudIpc    = holo::sensors::lidar::PointCloudIpc<PointCloudType>;
    using LidarScan        = holo::sensors::format::LidarScan<CAPACITY>;
    Rsm1ConverterApp(int32_t id, const std::string& ns) : bus_(id, ns)
    {
    }
    void Setup(const std::string& config_file, const std::string out_fmt);

private:
    bool GetParameters(const std::string& config_file);
    void DataCallbackGetScan(const uint8_t* data, size_t size);
    void DataCallbackGetPcdShm(const uint64_t info);

private:
    cmw_wrapper::BusType                       bus_;
    cmw_wrapper::BusType::ReaderType<uint8_t*> scan_sub_;
    std::string                                scan_topic_;
    bool_t                                     use_compress_;
    std::string                                extrinsic_;
    holo::sensors::LidarUtils                  lidar_utils_;
    std::string                                pcd_topic_;
    cmw_wrapper::BusType::ReaderType<uint64_t> pcd_sub_;
    std::shared_ptr<PointCloudIpc>             pcd_client_;
    bool_t                                     publish_scan_;
    bool_t                                     use_lidarscan_;
    std::shared_ptr<LidarScan>                 lidar_scan_;
    holo::common::SensorId                     sensor_id_;
};
}  // namespace holo_cmw

#endif