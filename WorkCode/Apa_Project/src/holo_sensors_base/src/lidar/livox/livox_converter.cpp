/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file livox_converter.cpp
 * @brief This header file define the function of livox converter
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2021-04-20
 */

#include <holo/sensors/lidar/livox/livox_converter.h>
#include <holo/sensors/utils/sensors_utils.h>

namespace holo
{
namespace sensors
{
namespace livox
{
template <typename LivoxPacketType>
size_t LivoxPcdConverter<LivoxPacketType>::Scan2Pcd(const LivoxScan<LivoxPacketType>& scan, PointCloudType& pcd,
                                                    const Extrinsicf& extrinsic, int64_t time_sync_offset)
{
    uint32_t point_index = 0;
    do
    {
        if (scan.Size() == 0)
        {
            pcd.reserve(1);
            pcd.resize(1);
            LOG(ERROR) << "Receive data is null!";
            break;
        }
        else
        {
            pcd.reserve(scan.Size() * scan[0].Size());
            pcd.resize(scan.Size() * scan[0].Size());
        }
        if (time_sync_offset == std::numeric_limits<int64_t>::min())
        {
            LOG(ERROR) << "Time sync offset error!";
            break;
        }
        if (scan[0].TimestampType() != holo::sensors::format::LivoxHapPacket<1440>::TimeSyncType::GPTP)
        {
            LOG(ERROR) << "Hap gptp sync error!";
            break;
        }

        uint64_t correction_time = scan[0].GetTimestamp().ToNsec() + time_sync_offset;
        pcd.SetCoordinate(scan.GetCoordinate());
        pcd.SetTimestamp(holo::common::Timestamp(correction_time));

        for (size_t i = 0; i < scan.Size(); i++)
        {
            correction_time = scan[i].GetTimestamp().ToNsec() + time_sync_offset;

            for (uint32_t j = 0; j < scan[i].Size(); j++)
            {
                if ((0 != scan[i].Point(j)->GetX()) || (0 != scan[i].Point(j)->GetY()) ||
                    (0 != scan[i].Point(j)->GetZ()))
                {
                    holo::geometry::Point3f position;
                    position.SetX(0.001f * scan[i].Point(j)->GetX());
                    position.SetY(0.001f * scan[i].Point(j)->GetY());
                    position.SetZ(0.001f * scan[i].Point(j)->GetZ());
                    position         = extrinsic.GetPose().TransformFrom(position);
                    PointType& point = pcd.at(point_index);
                    point.SetX(position.GetX());
                    point.SetY(position.GetY());
                    point.SetZ(position.GetZ());
                    point.SetIntensity(scan[i].Point(j)->GetIntensity());
                    point.SetTimestamp(holo::common::Timestamp(correction_time) + duration_ * j);
                    point_index++;
                }
                else
                {
                    // LOG(INFO) << "The point is 0 !!!";
                }
            }
        }
    } while (0);

    if (0 == point_index)
    {
        PointType& point = pcd.at(0);
        point.SetX(0);
        point.SetY(0);
        point.SetZ(0);
        point.SetIntensity(0);
        point.SetTimestamp(pcd.GetTimestamp());

        point_index = 1;
    }

    pcd.resize(point_index);
    return point_index;
}

template <typename LivoxPacketType>
size_t LivoxPcdConverter<LivoxPacketType>::ParseScan(const LivoxScan<LivoxPacketType>& scan, PointCloudType& pcd)
{
    return Scan2Pcd(scan, pcd, extrinsic_);
}

template <typename LivoxPacketType>
size_t LivoxPcdConverter<LivoxPacketType>::ParseScan(const LivoxScan<LivoxPacketType>& scan, PointCloudType& pcd,
                                                     int64_t time_sync_offset, const Extrinsicf& extrinsic)
{
    return Scan2Pcd(scan, pcd, extrinsic, time_sync_offset);
}

template <typename LivoxPacketType>
size_t LivoxPcdConverter<LivoxPacketType>::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
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

template <typename LivoxPacketType>
size_t LivoxPcdConverter<LivoxPacketType>::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
                                                     int64_t time_sync_offset, const Extrinsicf& extrinsic,
                                                     LidarCompressAlgorithm alg)
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

template class LivoxPcdConverter<LivoxPacket<48>>;
template class LivoxPcdConverter<LivoxPacket<96>>;
template class LivoxPcdConverter<LivoxPacket<100>>;
template class LivoxPcdConverter<holo::sensors::format::LivoxHapPacket<1440>>;

}  // namespace livox
}  // namespace sensors
}  // namespace holo
