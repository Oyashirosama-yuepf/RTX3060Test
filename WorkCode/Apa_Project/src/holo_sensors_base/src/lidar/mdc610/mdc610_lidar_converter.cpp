/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc610_converter.cpp
 * @brief This header file define the function of mdc610 converter
 * @author wujie@holomatic.com
 * @date 2022-03-09
 */

#include <holo/sensors/lidar/mdc610/mdc610_lidar_converter.h>
#include <holo/sensors/utils/sensors_utils.h>

namespace holo
{
namespace sensors
{
namespace mdc610
{
size_t Mdc610Converter::ParseScan(const Mdc610ScanType& scan, PointCloudType& pcd)
{
    return Scan2Pcd(scan, pcd, extrinsic_);
}

size_t Mdc610Converter::ParseScan(const Mdc610ScanType& scan, PointCloudType& pcd, const Extrinsicf& extrinsic)
{
    return Scan2Pcd(scan, pcd, extrinsic);
}

size_t Mdc610Converter::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd, LidarCompressAlgorithm alg)
{
    std::shared_ptr<DeserializerType> deserializer = nullptr;
    if (DeCompress(data, size, alg, deserializer))
    {
        if (dec_scan_.Deserialize(*deserializer))
        {
            return ParseScan(dec_scan_, pcd);
        }
    }
    return 0;
}
size_t Mdc610Converter::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd, int64_t time_sync_offset,
                                  const Extrinsicf& extrinsic, LidarCompressAlgorithm alg)
{
    (void)time_sync_offset;
    std::shared_ptr<DeserializerType> deserializer = nullptr;
    if (DeCompress(data, size, alg, deserializer))
    {
        if (dec_scan_.Deserialize(*deserializer))
        {
            return ParseScan(dec_scan_, pcd, extrinsic);
        }
    }
    return 0;
}

size_t Mdc610Converter::Scan2Pcd(const Mdc610ScanType& scan, PointCloudType& pcd, const Extrinsicf& extrinsic)
{
    float32_t               time_offset = 0.0f;
    holo::common::Timestamp timestamp   = scan.GetTimestamp();
    holo::common::Duration  duration;

    pcd.SetCoordinate(scan.GetCoordinate());
    pcd.reserve(scan.Size());
    pcd.resize(scan.Size());
    pcd.SetTimestamp(timestamp);

    uint32_t point_counter = 0;
    for (uint64_t i = 0; i < scan.Size(); i++)
    {
        PointType&              point = pcd.at(i);
        holo::geometry::Point3f position(scan[i].x, scan[i].y, scan[i].z);
        position = extrinsic.GetPose().TransformFrom(position);
        point.SetX(position.GetX());
        point.SetY(position.GetY());
        point.SetZ(position.GetZ());
        point.SetIntensity(scan[i].intensity);

        point_counter++;
        if (point_counter >= MAX_POINTS)
        {
            point_counter = 0;
            time_offset += TIME_OFFSET_PER_125_POINT;
        }

        duration.SetSec(0);
        duration.SetNsec(time_offset);
        pcd.SetTimestamp(timestamp + duration);
    }

    return pcd.size();
}

}  // namespace mdc610
}  // namespace sensors
}  // namespace holo
