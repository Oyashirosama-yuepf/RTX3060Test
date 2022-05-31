/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc610_lidar_converter_converterapp.h
 * @brief This header file define the mdc610 lidar scan converter
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/08/16
 */

#ifndef HOLO_CMW_APPS_LIDAR_MDC610_MDC610_LIDAR_CONVERTER_APP_H
#define HOLO_CMW_APPS_LIDAR_MDC610_MDC610_LIDAR_CONVERTER_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/extrinsic.h>
#include <holo/common/timestamp.h>
#include <holo/log/hololog.h>
#include <holo/os/time.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/libply/libply.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/utils/lidar_utils.h>
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
enum class NameFormat
{
    W8 = 0,
    TS = 1,
};
static constexpr size_t CAPACITY = 1024 * 1024 * 4;

class Mdc610LidarConverterApp
{
public:
    using DeserializerType = holo::serialization::Deserializer<false, 4>;
    using PointCloudType   = typename holo::sensors::mdc610::Mdc610Converter::PointCloudType;
    using LidarScan        = holo::sensors::format::LidarScan<CAPACITY>;
    using PointCloudIpc    = holo::sensors::lidar::PointCloudIpc<PointCloudType>;

    Mdc610LidarConverterApp(int32_t id, const std::string& ns) : bus_(id, ns), scan_count_(0), converted_count_(0), ply_count_(0)
    {
    }
    void Setup(const std::string& config_file, const std::string out_fmt);

private:
    bool GetParameters(const std::string& config_file);
    void DataCallbackGetLidarScan(const uint8_t* data, size_t size);
    void DataCallbackGetPcdShm(const uint64_t info);

private:
    /* cycly=100ms，contain 78750 points, per 125 points use one timestamp. */
    static constexpr float32_t TIME_OFFSET_PER_125_POINT = 100000000 / 78750 * 125;

private:
    cmw_wrapper::BusType bus_;
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    cmw_wrapper::BusType::ReaderType<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>> scan_sub_;
    cmw_wrapper::BusType::ReaderType<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>        pcd_sub_;
#else
    cmw_wrapper::BusType::ReaderType<uint8_t*> scan_sub_;
    cmw_wrapper::BusType::ReaderType<uint64_t> pcd_sub_;
#endif
    std::string                       scan_topic_;
    std::string                       pcd_topic_;
    bool_t                            publish_scan_;
    uint32_t                          sensor_id_;
    std::string                       extrinsic_;
    std::map<std::string, NameFormat> map_format_;
    std::shared_ptr<LidarScan>        lidar_scan_;
    std::shared_ptr<PointCloudIpc>    pcd_client_;
    holo::sensors::LidarUtils         lidar_utils_;
    uint32_t                          scan_count_;
    uint32_t                          converted_count_;
    std::atomic<uint32_t>             ply_count_;
};
}  // namespace holo_cmw

#endif
