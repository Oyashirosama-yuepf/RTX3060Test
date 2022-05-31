/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsm1_converter.cpp
 * @brief A converter to convert rsm1 scan messages to pcd
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/08/09
 */

#include <holo/sensors/lidar/rsm1/rsm1_converter.h>

namespace holo
{
namespace sensors
{
namespace rsm1
{
size_t Rsm1PcdConverter::Scan2Pcd(const Rsm1ScanType& scan, PointCloudType& pcd, const Extrinsicf& extrinsic,
                                  int64_t time_sync_offset)
{
    if (time_sync_offset == std::numeric_limits<int64_t>::min())
    {
        LOG(ERROR) << "time sync offset error!";
        return 0;
    }
    uint64_t correction_time = scan[0].GetHeaderTimestamp().ToNsec() + time_sync_offset;

    pcd.SetCoordinate(scan.GetCoordinate());
    pcd.reserve(scan.Size() * RSM1_POINTS_PER_PACKET);
    pcd.resize(scan.Size() * RSM1_POINTS_PER_PACKET);
    pcd.SetTimestamp(holo::common::Timestamp(correction_time));

    uint32_t point_num_per_scan = 0;
    /* per packect */
    for (uint32_t i = 0; i < scan.Size(); i++)
    {
        uint32_t point_index_per_packet = 0;
        /* per block */
        for (uint32_t j = 0; j < RSM1_BLOCKS_PER_PACKET; j++)
        {
            uint8_t                 time_offset = scan[i][RSM1_HEADER_SIZE + j * RSM1_BLOCK_SIZE];
            holo::common::Timestamp timestamp;
            holo::common::Duration  duration(0, time_offset * 1000);

            timestamp = scan[i].GetHeaderTimestamp() + holo::common::Duration(time_sync_offset) + duration;

            float32_t x, y, z;
            float32_t radius, elevation, azimuth, temp;

            /* per point */
            for (uint32_t k = 0; k < RSM1_POINTS_PER_BLOCK; k++)
            {
                auto reai = scan[i].GetRawPoint(j * RSM1_POINTS_PER_BLOCK + k);

                if (0 != reai->GetRadius())
                {
                    radius = static_cast<float32_t>(reai->GetRadius() * RADIUS_DEGREE);
                    elevation =
                        static_cast<float32_t>(holo::geometry::Radian<float64_t>(reai->GetElevation() * ANGLE_DEGREE));
                    azimuth =
                        static_cast<float32_t>(holo::geometry::Radian<float64_t>(reai->GetAzimuth() * ANGLE_DEGREE));
                    temp = radius * std::cos(elevation);

                    x = temp * std::cos(azimuth);
                    y = temp * std::sin(azimuth);
                    z = radius * std::sin(elevation);

                    PointType& point = pcd.at(point_num_per_scan + point_index_per_packet);
                    point_index_per_packet++;

                    holo::geometry::Point3f position;
                    position.SetX(x);
                    position.SetY(y);
                    position.SetZ(z);
                    position = extrinsic.GetPose().TransformFrom(position);
                    point.SetX(position.GetX());
                    point.SetY(position.GetY());
                    point.SetZ(position.GetZ());
                    point.SetIntensity(reai->GetIntensity());
                    point.SetTimestamp(timestamp);
                }
                else
                {
                    // LOG(INFO) << "The point is 0 !!!";
                }
            }
        }
        point_num_per_scan += point_index_per_packet;
    }

    if (0 == point_num_per_scan)
    {
        PointType& point = pcd.at(0);
        point.SetX(0);
        point.SetY(0);
        point.SetZ(0);
        point.SetIntensity(0);
        point.SetTimestamp(pcd.GetTimestamp());

        point_num_per_scan = 1;
    }

    pcd.resize(point_num_per_scan);
    return pcd.size();
}

size_t Rsm1PcdConverter::ParseScan(const Rsm1ScanType& scan, PointCloudType& pcd)
{
    return Scan2Pcd(scan, pcd, extrinsic_);
}

size_t Rsm1PcdConverter::ParseScan(const Rsm1ScanType& scan, PointCloudType& pcd, int64_t time_sync_offset,
                                   const Extrinsicf& extrinsic)
{
    return Scan2Pcd(scan, pcd, extrinsic, time_sync_offset);
}

size_t Rsm1PcdConverter::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd, LidarCompressAlgorithm alg)
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

size_t Rsm1PcdConverter::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd, int64_t time_sync_offset,
                                   const Extrinsicf& extrinsic, LidarCompressAlgorithm alg)
{
    std::shared_ptr<DeserializerType> deserializer = nullptr;
    if (DeCompress(data, size, alg, deserializer))
    {
        if (dec_scan_.Deserialize(*deserializer))
        {
            return ParseScan(dec_scan_, pcd, time_sync_offset, extrinsic);
        }
    }
    return 0;
}

}  // namespace rsm1
}  // namespace sensors
}  // namespace holo
