/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsruby_converter.cpp
 * @brief A converter to convert rsruby scan messages to pcd
 * @author wujie<wujie@holomatic.com>
 * @date 2021/10/26
 */

#include <holo/sensors/lidar/rsruby/rsruby_converter.h>

namespace holo
{
namespace sensors
{
namespace rsruby
{
bool CorrectionParameter::LoadCorrectionParameters(const holo::yaml::Node& node)
{
    uint16_t size = node.size();
    if (size != 128)
    {
        LOG(ERROR) << "correction parameters size is " << static_cast<uint32_t>(size) << " instead of 128";
        return false;
    }
    try
    {
        for (size_t i = 0; i != size; i++)
        {
            vertical_angle[i]     = node[i]["Vertical"].as<int16_t>();
            azimuth_correction[i] = node[i]["Azimuth"].as<int16_t>();
        }
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "failed to load correction parameters: " << e.what();
        return false;
    }
    return true;
}

size_t RsrubyPcdConverter::Scan2Pcd(const RsrubyScanType& scan, PointCloudType& pcd, const Extrinsicf& extrinsic,
                                    int64_t time_sync_offset)
{
    if (time_sync_offset == std::numeric_limits<int64_t>::min())
    {
        LOG(ERROR) << "time sync offset error!";
        return 0;
    }
    uint64_t correction_time = scan[0].GetHeaderTimestamp().ToNsec() + time_sync_offset;

    (void)pcd;
    pcd.SetCoordinate(scan.GetCoordinate());
    pcd.reserve(scan.Size() * RSRUBY_POINTS_PER_PACKET);
    pcd.resize(scan.Size() * RSRUBY_POINTS_PER_PACKET);
    pcd.SetTimestamp(holo::common::Timestamp(correction_time));

    uint32_t                          point_num_per_scan = 0;
    holo::sensors::format::RsrubyREAI reai;

    /* per packect */
    for (uint32_t i = 0; i < scan.Size(); i++)
    {
        uint32_t point_index_per_packet = 0;
        /* per block */
        for (uint32_t j = 0; j < RSRUBY_BLOCKS_PER_PACKET; j++)
        {
            float32_t x, y, z;
            float32_t radius, elevation, azimuth, temp;

            /* per point */
            for (uint32_t k = 0; k < RSRUBY_POINTS_PER_BLOCK; k++)
            {
                scan[i].GetRawPoint(j * RSRUBY_POINTS_PER_BLOCK + k, reai);

                if (0 != reai.GetRadius())
                {
                    radius    = static_cast<float32_t>(reai.GetRadius() * DISTANCE_DEGREE);
                    elevation = static_cast<float32_t>(holo::geometry::Radian<float64_t>(
                        correct_param_.vertical_angle[reai.GetChannelId()] * ANGLE_DEGREE));
                    azimuth   = static_cast<float32_t>(holo::geometry::Radian<float64_t>(
                        (reai.GetAzimuth() + correct_param_.azimuth_correction[reai.GetChannelId()]) * ANGLE_DEGREE));
                    temp      = radius * std::cos(elevation);

                    x = temp * std::sin(azimuth);
                    y = temp * std::cos(azimuth);
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
                    point.SetIntensity(reai.GetIntensity());
                    point.SetTimestamp(scan[i].GetHeaderTimestamp() + holo::common::Duration(time_sync_offset));
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

size_t RsrubyPcdConverter::ParseScan(const RsrubyScanType& scan, PointCloudType& pcd)
{
    return Scan2Pcd(scan, pcd, extrinsic_);
}

size_t RsrubyPcdConverter::ParseScan(const RsrubyScanType& scan, PointCloudType& pcd, int64_t time_sync_offset,
                                     const Extrinsicf& extrinsic)
{
    return Scan2Pcd(scan, pcd, extrinsic, time_sync_offset);
}

size_t RsrubyPcdConverter::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
                                     LidarCompressAlgorithm alg)
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

size_t RsrubyPcdConverter::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd, int64_t time_sync_offset,
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

}  // namespace rsruby
}  // namespace sensors
}  // namespace holo
