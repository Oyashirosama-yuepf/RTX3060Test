/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pandar128_converter.h
 * @brief This header file define the pandar128 scan converter
 * @author wujie<wujie@holomatic.com>
 * @date 2021/12/30
 */

#ifndef HOLO_CMW_APPS_LIDAR_PANDAR128_CONVERTER_H
#define HOLO_CMW_APPS_LIDAR_PANDAR128_CONVERTER_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/libply/libply.h>
#include <holo/sensors/lidar/pandar128/pandar128_converter.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/sensors/utils/sensors_utils.h>
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

class Pandar128ConverterApp
{
public:
    using Pandar128Scan         = holo::sensors::pandar128::Pandar128Scan;
    using LuminousTimeParameter = holo::sensors::pandar128::LuminousTimeParameter;
    using CorrectionParameter   = holo::sensors::pandar128::CorrectionParameter;
    using PandarPcdConverter    = holo::sensors::pandar128::Pandar128PcdConverter;
    using PointCloudType        = holo::sensors::pandar128::Pandar128PcdConverter::PointCloudType;
    using SerializerType        = holo::serialization::Serializer<false, 4>;
    using DeserializerType      = holo::serialization::Deserializer<false, 4>;
    using PointCloudIpc         = holo::sensors::lidar::PointCloudIpc<PointCloudType>;
    using ThreadPool            = holo::thread::ThreadPool;
    using LidarScan             = holo::sensors::format::LidarScan<CAPACITY>;

    Pandar128ConverterApp(int32_t id, const std::string& ns)
      : bus_(id, ns), publish_scan_(false), ply_max_thr_num_(0), scan_count_(0), converted_count_(0), ply_count_(0)
    {
    }
    ~Pandar128ConverterApp()
    {
    }

    /**
     * @brief setup this node
     *
     * @param config_file
     */
    void Setup(const std::string& config_file, const std::string& out_fmt);

private:
    void AddTask(PointCloudType&& pcd);
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
     * @param[in]  msg   the message comes from the pandar128 driver
     *
     * @note       this routine fetch and publish the pandar128 messages
     */
    void DataCallbackUseUserExtrinsic(const uint8_t* data, size_t size);
    void DataCallbackUseDefaultExtrinsic(const uint8_t* data, size_t size);
    void DataCallbackGetPcdShm(const uint64_t info);

private:
    cmw_wrapper::BusType                       bus_;
    cmw_wrapper::BusType::ReaderType<uint8_t*> scan_sub_;
    cmw_wrapper::BusType::ReaderType<uint64_t> pcd_sub_;
    std::string                                scan_topic_;
    std::string                                pcd_topic_;
    bool_t                                     publish_scan_;
    std::string                                extrinsic_path_;
    holo::common::Extrinsicf                   extrinsic_;
    holo::common::SensorId                     sensor_id_;
    uint32_t                                   ply_max_thr_num_;
    std::shared_ptr<ThreadPool>                thread_pool_ptr_;
    holo::sensors::LidarUtils                  lidar_utils_;
    std::shared_ptr<PointCloudIpc>             pcd_client_;
    std::shared_ptr<LidarScan>                 lidar_scan_;
    uint32_t                                   scan_count_;
    uint32_t                                   converted_count_;
    std::atomic<uint32_t>                      ply_count_;
};

}  // namespace holo_cmw

#endif
