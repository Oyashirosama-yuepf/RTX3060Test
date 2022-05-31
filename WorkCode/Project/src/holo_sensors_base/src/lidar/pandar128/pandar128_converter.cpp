/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pandar128_converter.h
 * @brief This header file define the function of pandar128 converter
 * @author wujie@holomatic.com
 * @date 2021-12-30
 */

#include <holo/sensors/lidar/pandar128/pandar128_converter.h>
#include <holo/sensors/utils/sensors_utils.h>

namespace holo
{
namespace sensors
{
namespace pandar128
{
bool_t LuminousTimeParameter::LoadLuminousTimeParameters(const holo::yaml::Node& node)
{
    uint16_t size = node.size();

    if (size != 2)
    {
        LOG(ERROR) << "luminous time parameters size is " << static_cast<uint32_t>(size) << " instead of 2";
        return false;
    }
    try
    {
        for (size_t i = 0; i != 128; i++)
        {
            high_azimuth_far[0][i]      = node["high_performance_mode"]["zero"][i]["Far"].as<uint16_t>();
            high_azimuth_far[1][i]      = node["high_performance_mode"]["one"][i]["Far"].as<uint16_t>();
            high_azimuth_far[2][i]      = node["high_performance_mode"]["two"][i]["Far"].as<uint16_t>();
            high_azimuth_far[3][i]      = node["high_performance_mode"]["three"][i]["Far"].as<uint16_t>();
            high_azimuth_near[0][i]     = node["high_performance_mode"]["zero"][i]["Near"].as<uint16_t>();
            high_azimuth_near[1][i]     = node["high_performance_mode"]["one"][i]["Near"].as<uint16_t>();
            high_azimuth_near[2][i]     = node["high_performance_mode"]["two"][i]["Near"].as<uint16_t>();
            high_azimuth_near[3][i]     = node["high_performance_mode"]["three"][i]["Near"].as<uint16_t>();
            standard_azimuth_far[0][i]  = node["standard_energy_saving_mode"]["zero"][i]["Far"].as<uint16_t>();
            standard_azimuth_far[1][i]  = node["standard_energy_saving_mode"]["one"][i]["Far"].as<uint16_t>();
            standard_azimuth_near[0][i] = node["standard_energy_saving_mode"]["zero"][i]["Near"].as<uint16_t>();
            standard_azimuth_near[1][i] = node["standard_energy_saving_mode"]["one"][i]["Near"].as<uint16_t>();
        }
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "failed to load luminous time parameters: " << e.what();
        return false;
    }
    return true;
}

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
        for (size_t i = 0; i != 128; i++)
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

uint16_t Pandar128PcdConverter::SearchLuminousTime(Pandar128Packet::OperationalStateType operational_state,
                                                   uint16_t azimuth_flag, uint16_t depth, uint16_t channel)
{
    /* high performance mode */
    if (operational_state == Pandar128Packet::OperationalStateType::HIGH_PERFORMANCE)
    {
        if (depth > DEPTH_BOUNDARY)
        {
            return luminous_time_param_.high_azimuth_far[azimuth_flag][channel];
        }
        else
        {
            return luminous_time_param_.high_azimuth_near[azimuth_flag][channel];
        }
    }
    /* standrad & energy conservation */
    else if ((operational_state == Pandar128Packet::OperationalStateType::STANDARD) ||
             (operational_state == Pandar128Packet::OperationalStateType::ENERGY_CONSERVATION))
    {
        if (depth > DEPTH_BOUNDARY)
        {
            return luminous_time_param_.standard_azimuth_far[azimuth_flag][channel];
        }
        else
        {
            return luminous_time_param_.standard_azimuth_near[azimuth_flag][channel];
        }
    }
    else
    {
        /* Operational State Error! */
        return -1;
    }
}

size_t Pandar128PcdConverter::Scan2Pcd(const Pandar128Scan& scan, PointCloudType& pcd, const Extrinsicf& extrinsic,
                                       int64_t time_sync_offset)
{
    if (scan.Size() == 0)
    {
        return 0;
    }
    if (time_sync_offset == std::numeric_limits<int64_t>::min())
    {
        LOG(ERROR) << "time sync offset error!";
        return 0;
    }
    uint64_t correction_time = scan[0].TimeStamp().ToNsec() + time_sync_offset;

    pcd.SetCoordinate(scan.GetCoordinate());
    // get the total point number in this scan and initialize the point cloud based on this point number
    pcd.reserve(scan.Size() * PANDAR_POINTS_PER_PACKET);
    pcd.resize(scan.Size() * PANDAR_POINTS_PER_PACKET);
    pcd.SetTimestamp(holo::common::Timestamp(correction_time));

    uint32_t  point_num_per_scan = 0;
    float32_t luminous_time      = 0;

    /* per packect */
    for (uint32_t i = 0; i < scan.Size(); i++)
    {
        uint32_t                              point_index_per_packet = 0;
        uint16_t                              motor_speed            = scan[i].MotorSpeed();
        Pandar128Packet::OperationalStateType operational_state      = scan[i].OperationalState();
        correction_time                                              = scan[i].TimeStamp().ToNsec();

        /* per block */
        for (uint32_t j = 0; j < 2; j++)
        {
            float32_t      x, y, z;
            float32_t      radius, elevation, azimuth, luminous_time_angle, temp;
            uint16_t       azimuth_flag = scan[i].AzimuthFlag(j);
            Pandar128Block block        = scan[i].Block(j);
            // uint64_t       start_time   = correction_time + PANDAR128_BLOCK_TIME_OFFSET_US * 1000; /* ns */

            /* dual return */
            /* per point */
            for (uint32_t k = 0; k < 128; k++)
            {
                if (0 != block.Depth(k))
                {
                    radius              = block.Depth(k) * DEPTH_RESOLUTION;
                    luminous_time       = SearchLuminousTime(operational_state, azimuth_flag, radius, k) * 1e-9;
                    elevation           = holo::geometry::Radian<float64_t>(correct_param_.vertical_angle[k] * 0.001f);
                    luminous_time_angle = luminous_time * motor_speed * 2 * PI / SECOND_PER_MINUTE;
                    azimuth             = luminous_time_angle +
                              holo::geometry::Radian<float64_t>(block.Azimuth() * ROTATION_RESOLUTION +
                                                                correct_param_.azimuth_correction[k] * 0.001f);

                    temp = radius * std::cos(elevation);

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
                    point.SetIntensity(block.Intensity(k));
                    point.SetTimestamp(holo::common::Timestamp(correction_time + time_sync_offset));
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

size_t Pandar128PcdConverter::ParseScan(const Pandar128Scan& scan, PointCloudType& pcd)
{
    return Scan2Pcd(scan, pcd, extrinsic_);
}

size_t Pandar128PcdConverter::ParseScan(const Pandar128Scan& scan, PointCloudType& pcd, int64_t time_sync_offset,
                                        const Extrinsicf& extrinsic)
{
    return Scan2Pcd(scan, pcd, extrinsic, time_sync_offset);
}

size_t Pandar128PcdConverter::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
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

size_t Pandar128PcdConverter::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
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

}  // namespace pandar128
}  // namespace sensors
}  // namespace holo
