/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lidar_converter_app.h
 * @brief This header file define the lidar converter app
 * @author wujie<wujie@holomatic.com>
 * @date 2022/01/24
 */

#ifndef HOLO_CMW_APPS_LIDAR_CONVERTER_H
#define HOLO_CMW_APPS_LIDAR_CONVERTER_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/extrinsic.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo/serialization/deserializer.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_c/core/types.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
#include <traits.h>
#else
#include <holo_base_msg/traits.h>
#endif

namespace holo_cmw
{
static constexpr size_t CAPACITY = 1024 * 1024 * 4;

class LidarConverterApp
{
public:
    using DeserializerType = holo::serialization::Deserializer<false, 4>;
    using PointType        = holo::point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType   = holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(),
                                                          sizeof(PointType), holo::point_cloud::UnorganizedLayoutTag>;
    using PointCloudIpc    = holo::sensors::lidar::PointCloudIpc<PointCloudType>;
    using LidarScan        = holo::sensors::format::LidarScan<CAPACITY>;

    LidarConverterApp(int32_t id, const std::string& ns) : bus_(id, ns), pcd_ipc_(nullptr), frames_(0)
    {
    }
    ~LidarConverterApp() noexcept
    {
    }
    void Setup(const std::string& config_file);

private:
    bool GetParameters(const std::string& config_file);
    void SetPcdToShm(const PointCloudType& pcd);
    void DataCallbackDefaultExtrinsic(const uint8_t* data, size_t size);
    void DataCallbackUserExtrinsic(const uint8_t* data, size_t size);

private:
    cmw_wrapper::BusType bus_;
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    cmw_wrapper::BusType::ReaderType<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>> scan_sub_;
    cmw_wrapper::BusType::WriterType<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>        pcd_pub_;
#else
    cmw_wrapper::BusType::ReaderType<uint8_t*> scan_sub_; /* read LidarScan */
    cmw_wrapper::BusType::WriterType<uint64_t> pcd_pub_;  /* write pcd  */
#endif
    std::string                    scan_topic_;
    std::string                    pcd_topic_;
    std::string                    extrinsic_path_;
    std::shared_ptr<PointCloudIpc> pcd_ipc_;
    std::shared_ptr<LidarScan>     lidar_scan_;
    holo::common::SensorId         sensor_id_;
    std::atomic<uint32_t>          frames_;
    holo::common::Extrinsicf       extrinsic_;
};
}  // namespace holo_cmw

#endif