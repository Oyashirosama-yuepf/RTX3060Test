/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ouster_converter.h
 * @brief This header file define the ouster scan converter
 * @author wangzhaobing<wangzhaobing@holomatic.com>
 * @date 2022/03/2
 */

#ifndef HOLO_CMW_APPS_LIDAR_OUSTER_OUSTER_CONVERTER_H
#define HOLO_CMW_APPS_LIDAR_OUSTER_OUSTER_CONVERTER_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/sensors/lidar/libply/libply.h>
#include <holo/sensors/lidar/ouster/ouster_converter.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <holo_c/core/types.h>
#include <interface/interface_wrapper.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>
#if defined(CMW_WRAPPER_ENABLE_ROS)
#include <holo_base_msg/ros_msg/sensors/ouster_traits.h>
#endif

namespace holo_cmw
{
class OusterConverterApp
{
public:
    using OusterScan          = holo::sensors::ouster::OusterScan;
    using ConvertParameter    = holo::sensors::ouster::ConvertParameter;
    using CorrectionParameter = holo::sensors::ouster::CorrectionParameter;
    using OusterPcdConverter  = holo::sensors::ouster::OusterPcdConverter;
    using PointCloudType      = holo::sensors::ouster::OusterPcdConverter::PointCloudType;
    using SerializerType      = holo::serialization::Serializer<false, 4>;
    using PointCloudIpc       = holo::sensors::lidar::PointCloudIpc<PointCloudType>;

    OusterConverterApp(int32_t id, const std::string& ns) : bus_(id, ns)
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
    void DataCallbackGetScan(OusterScan const& scan);
    void DataCallbackGetDDSScan(const uint8_t* data, size_t size);

    void DataCallbackGetPcdShm(const uint64_t info);

private:
    cmw_wrapper::BusType bus_;
    ConvertParameter     convert_param_;
    CorrectionParameter  correct_param_;
    std::string          scan_topic_;
    std::string          pcd_topic_;
#ifdef CMW_WRAPPER_ENABLE_ROS
    cmw_wrapper::BusType::ReaderType<holo::sensors::ouster::OusterScan,
                                     ros_wrapper::DefaultConversionTraits<holo::sensors::ouster::OusterScan>>
                                        scan_sub_;
#else
    cmw_wrapper::BusType::ReaderType<uint8_t*> scan_sub_;
#endif
    std::shared_ptr<OusterPcdConverter> converter_;
    bool_t                              use_compress_;
    std::string                         extrinsic_;
    holo::sensors::LidarUtils           lidar_utils_;
    std::shared_ptr<PointCloudIpc>      pcd_client_;
    bool_t                              publish_scan_;
    holo::common::SensorId              sensor_id_;
};

}  // namespace holo_cmw
#endif
