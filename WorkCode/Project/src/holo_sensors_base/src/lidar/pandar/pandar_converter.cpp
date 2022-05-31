/*!
 * \brief
 * \author liwenjun
 * \date 2017-07-05
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice. */

#include <holo/sensors/lidar/pandar/pandar_converter.h>
#include <holo/sensors/utils/sensors_utils.h>

namespace holo
{
namespace sensors
{
namespace pandar
{
bool_t ConvertParameter::LoadConvertParameters(const holo::yaml::Node& node)
{
    try
    {
        grid          = node["grid"].as<bool>();
        min_dis       = node["min_dis"].as<float32_t>();
        max_dis       = node["max_dis"].as<float32_t>();
        start_azimuth = node["start_azimuth"].as<float32_t>();
        end_azimuth   = node["end_azimuth"].as<float32_t>();
        start_azimuth = std::min<float32_t>(start_azimuth, 360.0f);
        start_azimuth = std::max<float32_t>(start_azimuth, 0.0f);
        end_azimuth   = std::min<float32_t>(end_azimuth, 360.0f);
        end_azimuth   = std::max<float32_t>(end_azimuth, 0.0f);
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "failed to load convert parameters: " << e.what();
        return false;
    }
    return true;
}

bool CorrectionParameter::LoadCorrectionParameters(const holo::yaml::Node& node)
{
    if (node.size() != 40)
    {
        LOG(ERROR) << "correction parameters size is " << static_cast<uint32_t>(node.size()) << " instead of 40";
        return false;
    }
    try
    {
        for (size_t i = 0; i != node.size(); i++)
        {
            float32_t vertical_angle     = holo::geometry::Radian<float32_t>(node[i]["Vertical"].as<float32_t>());
            float32_t azimuth_correction = node[i]["Azimuth"].as<float32_t>();
            data[i].cosines              = std::cos(vertical_angle);
            data[i].sines                = std::sin(vertical_angle);
            data[i].azimuth_correction   = azimuth_correction;
            data[i].pt_time_offset_one   = node[i]["TimeOffset1"].as<uint16_t>();
            data[i].pt_time_offset_two   = node[i]["TimeOffset2"].as<uint16_t>();
            data[i].time_index           = node[i]["Index"].as<uint16_t>();
        }
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "failed to load correction parameters: " << e.what();
        return false;
    }
    return true;
}

size_t PandarPcdConverter::Unpack(const PandarPacket& packet, const bool_t grid, const Timestamp& base_time,
                                  const size_t offset, PointCloudType& pcd, const Extrinsicf& extrinsic) const
{
    size_t count = 0;
    (void)grid; /* suppress unused variable warning */
    (void)pcd;

    for (size_t block_idx = 0; block_idx < PANDAR_BLOCKS_PER_PACKET; block_idx++)
    {
        const PandarBlock& block = packet.Block(block_idx);
        if (!block.Valid())
        {
            LOG(ERROR) << "1 block header is invalid";
            continue;
        }
        float32_t base_azimuth = block.Azimuth();
        if ((base_azimuth < convert_param_.start_azimuth) || (base_azimuth > convert_param_.end_azimuth))
        {
            LOG(ERROR) << "1 block azimuth is incorrect " << base_azimuth;
            continue;
        }
        float64_t block_offset_us = 0.0;
        /*single mode block time is block_idx(0-9) *55.56 ,dual mode block time is block_idx/2 *55.56*/
        if (packet.GetReturnMode() == PANDAR_DUAL_RETURN)
        {
            block_offset_us = std::floor(block_idx / 2) * PANDAR_BLOCK_TIME_OFFSET_US;
        }
        else
        {
            block_offset_us = block_idx * PANDAR_BLOCK_TIME_OFFSET_US;
        }
        uint32_t point_index = 0;
        for (size_t pt_idx = 0; pt_idx < PANDAR_BEAMS_NUM; pt_idx++)
        {
            float32_t distance = block.Depth(correct_param_sorted_.data[pt_idx].line_index);

            if (distance > PANDAR_MIN_DISTANCE)
            {
                uint32_t  intensity = block.Intensity(correct_param_sorted_.data[pt_idx].line_index);
                float32_t azimuth   = holo::geometry::Radian<float32_t>(
                    base_azimuth + correct_param_sorted_.data[pt_idx].azimuth_correction);
                float32_t cos_azimuth = std::cos(azimuth);
                float32_t sin_azimuth = std::sin(azimuth);
                float32_t x =
                    static_cast<float32_t>(distance * correct_param_sorted_.data[pt_idx].cosines * sin_azimuth);
                float32_t y =
                    static_cast<float32_t>(distance * correct_param_sorted_.data[pt_idx].cosines * cos_azimuth);
                float32_t               z = static_cast<float32_t>(distance * correct_param_sorted_.data[pt_idx].sines);
                holo::geometry::Point3f position(x, y, z);
                position = extrinsic.GetPose().TransformFrom(position);
                // if(fabs(x) < 1e-6 && fabs(y) < 1e-6 && fabs(z) < 1e-6)
                // {
                //     LOG(ERROR) << "-----";
                //     LOG(ERROR) << "pt_idx       = " << pt_idx;
                //     LOG(ERROR) << "base_azimuth = " << base_azimuth;
                //     LOG(ERROR) << "correction   = " << correct_param_.data[pt_idx].azimuth_correction;
                //     LOG(ERROR) << "azimuth      = " << azimuth;
                //     LOG(ERROR) << "distance     = " << distance;
                // }
                // putting point information to the pointcloud
                // LOG(INFO) << "offset + count + correct_param_.data[pt_idx].time_index = " << offset + count +
                // correct_param_.data[pt_idx].time_index;
                PointType& p = pcd.at(offset + count + point_index);
                p.Set(position.GetX(), position.GetY(), position.GetZ());
                p.SetIntensity(intensity);
                p.SetRing(correct_param_sorted_.data[pt_idx].line_index);
                // plus 1 sec caused by PPS and GPRMC syncho problem
                holo::common::Duration duration((correct_param_sorted_.data[pt_idx].pt_offset_us + block_offset_us) /
                                                1e6);
                p.SetTimestamp(base_time + duration);
                point_index++;
            }
        }
        count += point_index;
    }
    return count;
}

size_t PandarPcdConverter::Scan2Pcd(const PandarScan& scan, PointCloudType& pcd, const Extrinsicf& extrinsic,
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
    pcd.SetCoordinate(scan.GetCoordinate());
    // get the total point number in this scan and initialize the point cloud based on this point number
    pcd.reserve(scan.Size() * PANDAR_POINTS_PER_PACKET);
    pcd.resize(scan.Size() * PANDAR_POINTS_PER_PACKET);
    Timestamp base_hour    = scan.GetTimestamp() + holo::common::Duration(time_sync_offset);
    size_t    point_number = 0;
    for (size_t i = 0; i < scan.Size(); i++)
    {
        const PandarPacket& packet = scan[i];
        /* update the timestamp */
        Timestamp base_time = base_hour + holo::common::Duration(scan[i].GetBlockTimeStamp() / 1e6 + 1);
        /* fill the pcd header with the first packet timestamp */
        if (i == 0)
        {
            pcd.SetTimestamp(base_time);
        }
        /* parse the packet and get the count */
        size_t count = Unpack(packet, convert_param_.grid, base_time, point_number, pcd, extrinsic);
        point_number += count;
    }

    if (0 == point_number)
    {
        PointType& point = pcd.at(0);
        point.SetX(0);
        point.SetY(0);
        point.SetZ(0);
        point.SetIntensity(0);
        point.SetTimestamp(base_hour + holo::common::Duration(scan[0].GetBlockTimeStamp() / 1e6 + 1));

        point_number = 1;
    }

    pcd.resize(point_number);
    return pcd.size();
}

bool_t PandarPcdConverter::CorrectParameterSortByTime(const CorrectionParameter& correct_param)
{
    try
    {
        for (size_t i = 0; i != 40; i++)
        {
            correct_param_sorted_.data[correct_param.data[i].time_index].cosines = correct_param.data[i].cosines;
            correct_param_sorted_.data[correct_param.data[i].time_index].sines   = correct_param.data[i].sines;
            correct_param_sorted_.data[correct_param.data[i].time_index].azimuth_correction =
                correct_param.data[i].azimuth_correction;
            correct_param_sorted_.data[correct_param.data[i].time_index].pt_offset_us =
                correct_param.data[i].pt_time_offset_one * PANDAR_PT_TIME_OFFSET_US_1 +
                correct_param.data[i].pt_time_offset_two * PANDAR_PT_TIME_OFFSET_US_2;
            correct_param_sorted_.data[correct_param.data[i].time_index].line_index = i;
        }
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "failed to sort correct parameters by time: " << e.what();
        return false;
    }
    return true;
}

size_t PandarPcdConverter::ParseScan(const PandarScan& scan, PointCloudType& pcd)
{
    return Scan2Pcd(scan, pcd, extrinsic_);
}

size_t PandarPcdConverter::ParseScan(const PandarScan& scan, PointCloudType& pcd, int64_t time_sync_offset,
                                     const Extrinsicf& extrinsic)
{
    return Scan2Pcd(scan, pcd, extrinsic, time_sync_offset);
}

size_t PandarPcdConverter::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
                                     LidarCompressAlgorithm alg)
{
    std::shared_ptr<DeserializerType> deserializer = nullptr;
    if (alg == LidarCompressAlgorithm::LZ4)
    {
        LOG(ERROR) << "pandar is not support LZ4 compress algorithm now!";
    }
    else if (alg == LidarCompressAlgorithm::NONE)
    {
        deserializer = std::make_shared<DeserializerType>(const_cast<uint8_t*>(data), size);
    }
    else
    {
        LOG(ERROR) << "unknown lidar compress algorithm: " << static_cast<uint32_t>(alg);
        return 0;
    }

    if (dec_scan_.Deserialize(*deserializer))
    {
        return ParseScan(dec_scan_, pcd);
    }

    return 0;
}

size_t PandarPcdConverter::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd, int64_t time_sync_offset,
                                     const Extrinsicf& extrinsic, LidarCompressAlgorithm alg)
{
    std::shared_ptr<DeserializerType> deserializer = nullptr;
    if (alg == LidarCompressAlgorithm::LZ4)
    {
        LOG(ERROR) << "pandar is not support LZ4 compress algorithm now!";
    }
    else if (alg == LidarCompressAlgorithm::NONE)
    {
        deserializer = std::make_shared<DeserializerType>(const_cast<uint8_t*>(data), size);
    }
    else
    {
        LOG(ERROR) << "unknown lidar compress algorithm: " << static_cast<uint32_t>(alg);
        return 0;
    }

    if (dec_scan_.Deserialize(*deserializer))
    {
        return ParseScan(dec_scan_, pcd, time_sync_offset, extrinsic);
    }

    return 0;
}

}  // namespace pandar
}  // namespace sensors
}  // namespace holo
