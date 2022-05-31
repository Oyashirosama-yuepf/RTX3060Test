/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file velodyne_converter_app.h
 * @brief This header file define the velodyne scan converter app
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/07/07
 */

#ifndef HOLO_CMW_APPS_LIDAR_VELODYNE_VELODYNE_CONVERTER_H
#define HOLO_CMW_APPS_LIDAR_VELODYNE_VELODYNE_CONVERTER_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/sensors/lidar/libply/libply.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/lidar/velodyne/velodyne_converter.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <holo_c/core/types.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>

namespace holo_cmw
{
class VelodyneConverterApp
{
public:
    using VelodyneScanType     = holo::sensors::velodyne::VelodyneScan;
    using VelodynePcdConverter = holo::sensors::velodyne::VelodynePcdConverter;
    using PointCloudType       = holo::sensors::velodyne::VelodynePcdConverter::PointCloudType;
    using DeserializerType     = holo::serialization::Deserializer<false, 4>;
    using PointCloudIpc        = holo::sensors::lidar::PointCloudIpc<PointCloudType>;

    VelodyneConverterApp(int32_t id, const std::string& ns) : bus_(id, ns)
    {
    }

    /**
     * @brief setup this node
     *
     * @param config_file
     */
    void Setup(const std::string& config_file, const std::string& out_fmt);

private:
    bool GetParameters(const std::string& config_file);
    void DataCallbackGetScan(const uint8_t* data, size_t size, holo::sensors::LidarCompressAlgorithm alg);
    void DataCallbackGetPcdShm(const uint64_t info);

    cmw_wrapper::BusType                       bus_;
    std::string                                scan_topic_;
    std::string                                pcd_topic_;
    cmw_wrapper::BusType::ReaderType<uint8_t*> scan_sub_;
    cmw_wrapper::BusType::ReaderType<uint64_t> pcd_sub_;
    std::shared_ptr<VelodynePcdConverter>      converter_;
    bool_t                                     use_compress_;
    std::string                                extrinsic_;
    holo::sensors::LidarUtils                  lidar_utils_;
    std::shared_ptr<PointCloudIpc>             pcd_client_;
    holo::yaml::Node                           cvt_node_;
    holo::yaml::Node                           crr_node_;
    bool_t                                     publish_scan_;
    holo::common::SensorId                     sensor_id_;
};
}  // namespace holo_cmw

#endif