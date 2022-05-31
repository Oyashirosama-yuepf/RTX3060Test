/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsm1_app.h
 * @brief This header file define the app of rsm1 driver
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/08/18
 */

#ifndef HOLO_CMW_APPS_LIDAR_RSM1_RSM1_APP_H
#define HOLO_CMW_APPS_LIDAR_RSM1_RSM1_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/os/time.h>
#include <holo/os/timer.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/lidar/rsm1/rsm1_converter.h>
#include <holo/sensors/lidar/rsm1/rsm1_driver.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/thread/thread_pool.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <interface/interface_wrapper.h>
#include <atomic>
#include <cmw_wrapper/utils/cxxopts.hpp>

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
#include <traits.h>
#else
#include <holo_base_msg/traits.h>
#endif

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
#include <traits.h>
#else
#include <holo_base_msg/traits.h>
#endif

namespace holo_cmw
{
static constexpr size_t CAPACITY = 1024 * 1024 * 4;

class Rsm1DriverApp
{
public:
    using SerializerType       = holo::serialization::Serializer<false, 4>;
    using Rsm1ScanType         = holo::sensors::rsm1::Rsm1Scan;
    using Rsm1Packet           = holo::sensors::rsm1::Rsm1Packet;
    using Rsm1Driver           = holo::sensors::rsm1::Rsm1Driver;
    using LidarScan            = holo::sensors::format::LidarScan<CAPACITY>;
    using Rsm1DeviceInfoPacket = holo::sensors::rsm1::Rsm1DeviceInfoPacket;
    using CompressUtils        = holo::sensors::CompressUtils;
    /* converter\ipc */
    using Rsm1Converter  = holo::sensors::rsm1::Rsm1PcdConverter;
    using PointType      = holo::point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType = holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(),
                                                          sizeof(PointType), holo::point_cloud::UnorganizedLayoutTag>;
    using PointCloudIpc  = holo::sensors::lidar::PointCloudIpc<PointCloudType>;
    using ThreadPool     = holo::thread::ThreadPool;

    Rsm1DriverApp(int32_t id, const std::string& ns)
      : bus_(id, ns)
      , scan_data_{new uint8_t[CAPACITY](), std::default_delete<uint8_t[]>()}
      , frames_(0)
      , sensor_id_(0)
      , max_thr_num_(0)
    {
    }

    void Setup(const std::string& config_file);

private:
    bool GetParameters(const std::string& config_file);
    void ScanDataCallback(const Rsm1ScanType& scan);
    void AddTask(const Rsm1ScanType& scan);
    void SavePcdToShm(const Rsm1ScanType& scan);

private:
    uint32_t             coord_;
    std::string          scan_topic_;
    std::string          pcd_topic_;
    bool_t               use_compress_;
    bool_t               time_check_;
    bool_t               publish_scan_;
    bool_t               use_lidarscan_;
    cmw_wrapper::BusType bus_;
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    cmw_wrapper::BusType::WriterType<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>> scan_pub_;
    cmw_wrapper::BusType::WriterType<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>        pcd_pub_;
#else
    cmw_wrapper::BusType::WriterType<uint8_t*> scan_pub_;
    cmw_wrapper::BusType::WriterType<uint64_t> pcd_pub_;
#endif
    std::shared_ptr<uint8_t>       scan_data_;
    std::shared_ptr<LidarScan>     lidar_scan_;
    std::shared_ptr<Rsm1Driver>    driver_;
    std::atomic<uint32_t>          frames_;
    uint32_t                       packet_rate_;
    uint32_t                       scan_rate_;
    holo::common::SensorId         sensor_id_;
    std::string                    extrinsic_;
    std::shared_ptr<ThreadPool>    thread_pool_ptr_;
    std::shared_ptr<Rsm1Converter> converter_;
    std::shared_ptr<PointCloudIpc> pcd_ipc_;
    uint32_t                       max_thr_num_;
    holo::bool_t                   use_datalayer_timestamp_;
};
}  // namespace holo_cmw

#endif
