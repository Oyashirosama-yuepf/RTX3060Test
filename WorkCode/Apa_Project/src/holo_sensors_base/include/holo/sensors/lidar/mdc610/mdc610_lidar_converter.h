/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc610_lidar_converter.h
 * @brief This header file define the function of mdc610 converter
 * @author wujie@holomatic.com
 * @date 2022-03-09
 */

#ifndef _HOLO_SENSORS_MDC610_PCD_CONVERTER_H
#define _HOLO_SENSORS_MDC610_PCD_CONVERTER_H

#include <assert.h>
#include <holo/common/extrinsic.h>
#include <holo/core/exception.h>
#include <holo/geometry/angle.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/lidar/lidar_converter_base.h>
#include <holo/sensors/lidar/mdc610/mdc610_lidar_structure.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace mdc610
{
using holo::sensors::LidarCompressAlgorithm;

class Mdc610Converter : public PcdConverterBase
{
public:
    using Extrinsicf       = holo::common::Extrinsicf;
    using Timestamp        = holo::common::Timestamp;
    using PointType        = holo::point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType   = holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(),
                                                          sizeof(PointType), holo::point_cloud::UnorganizedLayoutTag>;
    using Mdc610ScanType   = holo::sensors::mdc610::Mdc610Scan;
    using DeserializerType = holo::serialization::Deserializer<false, 4>;

public:
    Mdc610Converter(const Extrinsicf& extrinsic) : PcdConverterBase(extrinsic, DEC_CAPACITY), dec_scan_()
    {
    }

    size_t ParseScan(const Mdc610ScanType& scan, PointCloudType& pcd);
    size_t ParseScan(const Mdc610ScanType& scan, PointCloudType& pcd, const Extrinsicf& extrinsic);

    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
                     LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE);
    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd, int64_t time_sync_offset,
                     const Extrinsicf& extrinsic, LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE);

private:
    size_t Scan2Pcd(const Mdc610ScanType& scan, PointCloudType& pcd, const Extrinsicf& extrinsic);

private:
    static constexpr uint32_t  MAX_POINTS                = 124;
    static constexpr uint32_t  DEC_CAPACITY              = 1024 * 1024 * 4u;
    static constexpr float32_t TIME_OFFSET_PER_125_POINT = 100000000 / 78750 * 125;

private:
    Mdc610ScanType dec_scan_;
};

}  // namespace mdc610
}  // namespace sensors
}  // namespace holo

#endif
