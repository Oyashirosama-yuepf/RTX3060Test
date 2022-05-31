/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pandar_converter.h
 * @brief This header file define the pandar scan converter
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2021/03/22
 */

#ifndef HOLO_CMW_APPS_LIDAR_PANDAR_PANDAR_CONVERTER_H
#define HOLO_CMW_APPS_LIDAR_PANDAR_PANDAR_CONVERTER_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/libply/libply.h>
#include <holo/sensors/lidar/pandar/pandar_converter.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <holo_c/core/types.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>

namespace holo_cmw
{
static constexpr size_t CAPACITY = 1024 * 1024 * 4;

class PandarConverterApp
{
public:
    using PandarScan          = holo::sensors::pandar::PandarScan;
    using ConvertParameter    = holo::sensors::pandar::ConvertParameter;
    using CorrectionParameter = holo::sensors::pandar::CorrectionParameter;
    using PandarPcdConverter  = holo::sensors::pandar::PandarPcdConverter;
    using PointCloudType      = holo::sensors::pandar::PandarPcdConverter::PointCloudType;
    using SerializerType      = holo::serialization::Serializer<false, 4>;
    using DeserializerType    = holo::serialization::Deserializer<false, 4>;
    using PointCloudIpc       = holo::sensors::lidar::PointCloudIpc<PointCloudType>;
    using LidarScan           = holo::sensors::format::LidarScan<CAPACITY>;

    PandarConverterApp(int32_t id, const std::string& ns) : bus_(id, ns)
    {
    }

    /**
     * @brief setup this node
     *
     * @param config_file
     */
    void Setup(const std::string& config_file, const std::string& out_fmt);

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
     * @brief      callback service for pandar
     *
     * @param[in]  msg   the message comes from the pandar driver
     *
     * @note       this routine fetch and publish the pandar messages
     */
    void DataCallbackUseUserExtrinsic(const uint8_t* data, size_t size);
    void DataCallbackUseDefaultExtrinsic(const uint8_t* data, size_t size);
    void DataCallbackGetPcdShm(const uint64_t info);

private:
    cmw_wrapper::BusType                       bus_;
    ConvertParameter                           convert_param_;
    CorrectionParameter                        correct_param_;
    std::string                                scan_topic_;
    std::string                                pcd_topic_;
    cmw_wrapper::BusType::ReaderType<uint8_t*> scan_sub_;
    cmw_wrapper::BusType::ReaderType<uint64_t> pcd_sub_;
    std::shared_ptr<PandarPcdConverter>        converter_;
    bool_t                                     use_compress_;
    std::string                                extrinsic_path_;
    holo::common::Extrinsicf                   extrinsic_;
    holo::sensors::LidarUtils                  lidar_utils_;
    std::shared_ptr<LidarScan>                 lidar_scan_;
    std::shared_ptr<PointCloudIpc>             pcd_client_;
    bool_t                                     publish_scan_;
    holo::common::SensorId                     sensor_id_;
    uint32_t                                   scan_count_;
    uint32_t                                   converted_count_;
    std::atomic<uint32_t>                      ply_count_;
};

}  // namespace holo_cmw

#endif
