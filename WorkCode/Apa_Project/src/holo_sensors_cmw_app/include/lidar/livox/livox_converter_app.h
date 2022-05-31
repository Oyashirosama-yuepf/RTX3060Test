/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file livox_converter.h
 * @brief This header file define the livox scan converter
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2021/03/22
 */

#ifndef HOLO_CMW_APPS_LIDAR_LIVOX_LIVOX_CONVERTER_H
#define HOLO_CMW_APPS_LIDAR_LIVOX_LIVOX_CONVERTER_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/sensors/format/lidar_scan.h>
#include <holo/sensors/lidar/libply/libply.h>
#include <holo/sensors/lidar/livox/livox_converter.h>
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

template <typename PacketType>
class LivoxConverterApp
{
public:
    using LivoxScanType     = holo::sensors::livox::LivoxScan<PacketType>;
    using LivoxPcdConverter = holo::sensors::livox::LivoxPcdConverter<PacketType>;
    using PointCloudType    = typename holo::sensors::livox::LivoxPcdConverter<PacketType>::PointCloudType;
    using SerializerType    = holo::serialization::Serializer<false, 4>;
    using LidarScan         = holo::sensors::format::LidarScan<CAPACITY>;
    using DeserializerType  = holo::serialization::Deserializer<false, 4>;
    using PointCloudIpc     = holo::sensors::lidar::PointCloudIpc<PointCloudType>;

    LivoxConverterApp(int32_t id, const std::string& ns) : bus_(id, ns)
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
     * @brief      callback service for livox compressed data
     *
     * @param[in]  msg   the message comes from the livox driver
     *
     * @note       this routine fetch and publish the livox messages
     */
    void DataCallbackUseUserExtrinsic(const uint8_t* data, size_t size);
    void DataCallbackUseDefaultExtrinsic(const uint8_t* data, size_t size);
    void DataCallbackGetPcdShm(const uint64_t info);

private:
    cmw_wrapper::BusType                       bus_;
    std::string                                scan_topic_;
    cmw_wrapper::BusType::ReaderType<uint8_t*> scan_sub_;
    std::string                                extrinsic_path_;
    holo::common::Extrinsicf                   extrinsic_;
    std::shared_ptr<LivoxPcdConverter>         converter_;
    holo::sensors::LidarUtils                  lidar_utils_;
    std::string                                pcd_topic_;
    cmw_wrapper::BusType::ReaderType<uint64_t> pcd_sub_;
    std::shared_ptr<PointCloudIpc>             pcd_client_;
    bool_t                                     publish_scan_;
    bool_t                                     use_lidarscan_;
    bool_t                                     use_compress_;
    holo::common::SensorId                     sensor_id_;
    std::shared_ptr<LidarScan>                 lidar_scan_;
    uint32_t                                   packet_rate_;
};

}  // namespace holo_cmw

#endif
