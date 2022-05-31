/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsm1_converter.h
 * @brief This header file defines robosense m1 lidar converter
 * @author zhangtongyang(zhangtongyang@holomaitc.com)
 * @date 2021/8/09
 */
#ifndef _HOLO_SENSORS_LIDAR_RSM1_RSM1_CONVERTER_H
#define _HOLO_SENSORS_LIDAR_RSM1_RSM1_CONVERTER_H

#include <assert.h>
#include <holo/common/extrinsic.h>
#include <holo/core/exception.h>
#include <holo/geometry/angle.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/format/rsm1.h>
#include <holo/sensors/lidar/lidar_converter_base.h>
#include <holo/sensors/lidar/rsm1/rsm1_structure.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace rsm1
{
using holo::sensors::LidarCompressAlgorithm;
using Rsm1ScanType = holo::sensors::rsm1::Rsm1Scan;

class Rsm1PcdConverter : public PcdConverterBase
{
public:
    using Extrinsicf       = holo::common::Extrinsicf;
    using Timestamp        = holo::common::Timestamp;
    using PointType        = point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType   = holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(),
                                                          sizeof(PointType), point_cloud::UnorganizedLayoutTag>;
    using DeserializerType = holo::serialization::Deserializer<false, 4>;

    Rsm1PcdConverter(const Extrinsicf& extrinsic) : PcdConverterBase(extrinsic, DEC_CAPACITY), dec_scan_()
    {
    }

    size_t ParseScan(const Rsm1ScanType& scan, PointCloudType& pcd);
    size_t ParseScan(const Rsm1ScanType& scan, PointCloudType& pcd, int64_t time_sync_offset,
                     const Extrinsicf& extrinsic);

    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
                     LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE);
    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd, int64_t time_sync_offset,
                     const Extrinsicf& extrinsic, LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE);

private:
    size_t Scan2Pcd(const Rsm1ScanType& scan, PointCloudType& pcd, const Extrinsicf& extrinsic,
                    int64_t time_sync_offset = 0);

private:
    static constexpr uint32_t DEC_CAPACITY = 1024 * 1024 * 4u;

private:
    static constexpr float64_t RADIUS_DEGREE = 0.005f;
    static constexpr float64_t ANGLE_DEGREE  = 0.01f;
    Rsm1ScanType               dec_scan_;
};
}  // namespace rsm1
}  // namespace sensors
}  // namespace holo

#endif