/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsruby_converter.h
 * @brief This header file define the rsruby scan converter
 * @author wujie<wujie@holomatic.com>
 * @date 2021/10/26
 */

#ifndef HOLO_CMW_APPS_LIDAR_RSRUBY_RSRUBY_CONVERTER_H
#define HOLO_CMW_APPS_LIDAR_RSRUBY_RSRUBY_CONVERTER_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/extrinsic.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/libply/libply.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/lidar/rsruby/rsruby_converter.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo/serialization/deserializer.h>
#include <holo/thread/thread_pool.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <holo_c/core/types.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>

namespace holo_cmw
{
static constexpr size_t CAPACITY = 1024 * 1024 * 4;

class RsrubyConverterApp
{
public:
    using DeserializerType = holo::serialization::Deserializer<false, 4>;
    using RsrubyScanType   = holo::sensors::rsruby::RsrubyScan;
    using RsrubyConverter  = holo::sensors::rsruby::RsrubyPcdConverter;
    using PointCloudType   = typename holo::sensors::rsruby::RsrubyPcdConverter::PointCloudType;
    using PointCloudIpc    = holo::sensors::lidar::PointCloudIpc<PointCloudType>;
    using ThreadPool       = holo::thread::ThreadPool;
    using LidarScan        = holo::sensors::format::LidarScan<CAPACITY>;

    RsrubyConverterApp(int32_t id, const std::string& ns)
      : bus_(id, ns), ply_max_thr_num_(0), scan_count_(0), converted_count_(0), ply_count_(0)
    {
    }
    ~RsrubyConverterApp()
    {
    }
    void Setup(const std::string& config_file, const std::string out_fmt);

    void AddTask(PointCloudType&& pcd);

private:
    bool GetParameters(const std::string& config_file);
    void DataCallbackGetScan(const uint8_t* data, size_t size);
    void DataCallbackGetPcdShm(const uint64_t info);

private:
    cmw_wrapper::BusType                       bus_;
    cmw_wrapper::BusType::ReaderType<uint8_t*> scan_sub_;
    std::string                                scan_topic_;
    std::string                                extrinsic_;
    holo::sensors::LidarUtils                  lidar_utils_;
    std::string                                pcd_topic_;
    cmw_wrapper::BusType::ReaderType<uint64_t> pcd_sub_;
    std::shared_ptr<PointCloudIpc>             pcd_client_;
    bool_t                                     publish_scan_;
    std::shared_ptr<LidarScan>                 lidar_scan_;
    holo::common::SensorId                     sensor_id_;
    std::shared_ptr<ThreadPool>                thread_pool_ptr_;
    uint32_t                                   ply_max_thr_num_;
    uint32_t                                   scan_count_;
    uint32_t                                   converted_count_;
    std::atomic<uint32_t>                      ply_count_;
};
}  // namespace holo_cmw

#endif