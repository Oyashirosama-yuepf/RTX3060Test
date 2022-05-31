/*!
 * \brief
 * \author liwenjun
 * \date 2017-07-05
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice. */

#include <assert.h>
#include <holo/log/hololog.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/lidar/velodyne/velodyne_converter.h>
#include <holo/sensors/utils/sensors_utils.h>

namespace holo
{
namespace sensors
{
namespace velodyne
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

bool_t CorrectionParameter::LoadCorrectionParameters(const holo::yaml::Node& node)
{
    try
    {
        for (size_t i = 0; i != node.size(); i++)
        {
            uint32_t laser_id = node[i]["Laser_id"].as<uint32_t>();
            if (i >= 16 || laser_id >= 16)
            {
                LOG(ERROR) << "invalid correction parameter: index = " << uint32_t(i) << ", laser-id = " << laser_id;
                return false;
            }
            float32_t vertical_angle = holo::geometry::Radian<float32_t>(node[i]["Vertical"].as<float32_t>());
            cosines[laser_id]        = std::cos(vertical_angle);
            sines[laser_id]          = std::sin(vertical_angle);
        }
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "failed to load correction parameters: " << e.what();
        return false;
    }
    return true;
}

void VelodynePcdConverter::GetPacketAzimuth(const VelodynePacket& packet, float32_t azimuths[][2]) const
{
    float32_t azimuth_diff = 0.0;
    for (int block = 0; block < VELODYNE_BLOCKS_PER_PACKET; block++)
    {
        // the rotation for the first sector is able to be obtained,
        // but for the second sector, the rotation has to be caculated
        azimuths[block][0] = packet.Block(block).Azimuth();
        if (block < (VELODYNE_BLOCKS_PER_PACKET - 1))
        {
            float32_t next_azimuth = packet.Block(block + 1).Azimuth();
            if (azimuths[block][0] > next_azimuth)
            {
                next_azimuth = static_cast<float32_t>(next_azimuth + 360.0f);
            }
            // the rotation of the second sector is obtained here
            azimuths[block][1] = azimuths[block][0] + (next_azimuth - azimuths[block][0]) / 2;
            // get azimuth_diff for the last block
            azimuth_diff = azimuths[block][1] - azimuths[block][0];
        }
        else
        {
            azimuths[block][1] = azimuths[block][0] + azimuth_diff;
        }
    }
}

bool VelodynePcdConverter::CheckPacketFrame(const uint32_t last_velodyne_timestamp, const VelodynePacket& packet,
                                            holo::common::Timestamp& base_hour) const
{
    (void)base_hour;

    bool proceed = true;
    // check if there is frame skipping when the packets are transmitting
    if (packet.Timestamp() >= last_velodyne_timestamp)
    {
        // if the forward jump is bigger than 0.1 second, we raise a warning and ignore it
        const float64_t d = (float64_t)packet.Timestamp() - (float64_t)last_velodyne_timestamp;
        if (d <= 0.1 * 1000000)  // the normal situation the gap between two packets are smaller than 0.1 sec
        {
            proceed = true;
        }
        else if ((d > 0.1 * 1000000) && (d < 3597.0 * 1000000))
        {
            LOG(INFO) << "velodyne converter detects major forward timestamp jitter! --> " << last_velodyne_timestamp
                      << ", " << packet.Timestamp() << ", " << d << std::endl;
            proceed = false;
        }
        else
        {
            // maybe there is a packet from last hour
            base_hour = base_hour + holo::common::Duration(-3600, 0);
            // LOG(INFO) << "hour-- "
            //           << ", last_velodyne_timestamp = " << last_velodyne_timestamp
            //           << ", packet.Timestamp() = " << packet.Timestamp() << ", base_hour = " <<
            //           base_hour
            //           << std::endl;
            proceed = true;
        }
    }
    else
    {
        const float64_t d = (float64_t)last_velodyne_timestamp - (float64_t)packet.Timestamp();
        if (d <= (0.1 * 1000000))
        {
            // if the backward jump is less than 0.1 seconds, we proceed as normal
            LOG(WARNING) << "velodyne converter detects minor backward timestamp jitter! --> "
                         << last_velodyne_timestamp << ", " << packet.Timestamp() << ", " << d << std::endl;
            proceed = true;
        }
        else if ((d > (0.1 * 1000000)) && (d <= (3597.0 * 1000000)))
        {
            // if the backward jump is between 0.1-3597 seconds, this is a serious problem
            LOG(WARNING) << "velodyne converter detects major backward timestamp jitter! --> "
                         << last_velodyne_timestamp << ", " << packet.Timestamp() << ", " << d << std::endl;
            proceed = false;
        }
        else  // if the backward jump is between 3595-3600 seconds, we say this is a reasonable backward jump
        {
            base_hour = base_hour + holo::common::Duration(3600, 0);
            proceed   = true;
        }
    }
    return proceed;
}

bool VelodynePcdConverter::CheckAzimuth(int block, int sector, float32_t azimuths[][VLP16_SECTORS_PER_BLOCK]) const
{
    if (convert_param_.start_azimuth <= convert_param_.end_azimuth)
    {
        /* regular range, like [90,360] */
        if (azimuths[block][sector] < convert_param_.start_azimuth ||
            azimuths[block][sector] > convert_param_.end_azimuth)
        {
            return false;
        }
    }
    else
    {
        /* irregular range, like [180, 90] */
        if (azimuths[block][sector] < convert_param_.start_azimuth &&
            azimuths[block][sector] > convert_param_.end_azimuth)
        {
            return false;
        }
    }
    return true;
}

size_t VelodynePcdConverter::UnpackVLP16(const VelodynePacket& packet, bool grid,
                                         const holo::common::Timestamp& base_time, size_t offset, PointCloudType& pcd,
                                         const Extrinsicf& extrinsic) const
{
    (void)pcd;
    float32_t azimuths[VELODYNE_BLOCKS_PER_PACKET][VLP16_SECTORS_PER_BLOCK];
    GetPacketAzimuth(packet, azimuths);
    size_t count = 0;
    for (int block = 0; block < VELODYNE_BLOCKS_PER_PACKET; block++)
    {
        // check if the header is correct
        if (!packet.Block(block).Valid())
        {
            LOG(ERROR) << "UnpackVLP16 meets invalid block header ";
            continue;
        }
        /* sector */
        for (int sector = 0, k = 0; sector < VLP16_SECTORS_PER_BLOCK; sector++)
        {
            const VelodyneBlock& b = packet.Block(block);

            /* apply azimuth check if not dense */
            if (!grid && !CheckAzimuth(block, sector, azimuths))
            {
                continue;
            }

            // for VLP16 each block has two sectors
            for (int ring = 0; ring < VLP16_SCANS_PER_SECTOR; ring++, k++)
            {
                const float distance = b.Depth(k);
                if ((!grid) && (distance < convert_param_.min_dis || distance > convert_param_.max_dis))
                {
                    // the distance is out of range
                    continue;
                }

                if (distance > VELODYNE_MIN_DISTANCE)
                {
                    float32_t theta =
                        static_cast<float32_t>(holo::geometry::Radian<float32_t>(azimuths[block][sector]));
                    float32_t x = static_cast<float32_t>(
                        distance * static_cast<float32_t>(correct_param_.cosines[ring]) * std::sin(theta));
                    float32_t y = static_cast<float32_t>(
                        distance * static_cast<float32_t>(correct_param_.cosines[ring]) * std::cos(theta));
                    float32_t z = static_cast<float32_t>(distance * static_cast<float32_t>(correct_param_.sines[ring]));

                    holo::geometry::Point3f position(x, y, z);
                    position = extrinsic.GetPose().TransformFrom(position);

                    // put point information to the pointcloud
                    PointType& point   = pcd.at(offset + count);
                    float32_t  toffset = (2 * block + sector) * VLP16_SECTOR_TOFFSET + ring * VLP16_DSR_TOFFSET;
                    holo::common::Duration duration(toffset / 1e6);
                    point.SetTimestamp(base_time + duration);
                    point.Set(position.GetX(), position.GetY(), position.GetZ());
                    point.SetIntensity(b.Intensity(k));
                    point.SetRing(ring);
                    count++;
                }
            }
        }
    }
    return count;
}

size_t VelodynePcdConverter::Scan2Pcd(const VelodyneScan& scan, PointCloudType& pcd, const Extrinsicf& extrinsic,
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
    pcd.reserve(scan.Size() * VELODYNE_POINTS_PER_PACKET);
    pcd.resize(scan.Size() * VELODYNE_POINTS_PER_PACKET);
    holo::common::Timestamp base_hour               = scan.GetTimestamp();
    uint32_t                last_velodyne_timestamp = scan[0].Timestamp();
    size_t                  point_number            = 0;
    for (size_t i = 0; i < scan.Size(); i++)
    {
        /// update the base hour and time if needed
        const VelodynePacket& packet = scan[i];
        if (!CheckPacketFrame(last_velodyne_timestamp, packet, base_hour))
        {
            continue;
        }
        /* update the timestamp */
        last_velodyne_timestamp = packet.Timestamp();
        holo::common::Duration  duration(scan[i].Timestamp() / 1e6);
        holo::common::Timestamp base_time = base_hour + duration + holo::common::Duration(time_sync_offset);
        /* fill the pcd header with the first packet timestamp */
        if (i == 0)
        {
            pcd.SetTimestamp(base_time);
        }
        /* parse the packet and get the count */
        size_t count = UnpackVLP16(packet, convert_param_.grid, base_time, point_number, pcd, extrinsic);
        point_number += count;
    }

    if (0 == point_number)
    {
        PointType& point = pcd.at(0);
        point.SetX(0);
        point.SetY(0);
        point.SetZ(0);
        point.SetIntensity(0);
        point.SetTimestamp(pcd.GetTimestamp());

        point_number = 1;
    }

    pcd.resize(point_number);
    return pcd.size();
}

size_t VelodynePcdConverter::ParseScan(const VelodyneScan& scan, PointCloudType& pcd)
{
    return Scan2Pcd(scan, pcd, extrinsic_);
}

size_t VelodynePcdConverter::ParseScan(const VelodyneScan& scan, PointCloudType& pcd, int64_t time_sync_offset,
                                       const Extrinsicf& extrinsic)
{
    return Scan2Pcd(scan, pcd, extrinsic, time_sync_offset);
}

size_t VelodynePcdConverter::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
                                       LidarCompressAlgorithm alg)
{
    std::shared_ptr<DeserializerType> deserializer = nullptr;
    if (alg == LidarCompressAlgorithm::LZ4)
    {
        LOG(ERROR) << "velodyne is not support LZ4 compress algorithm now!";
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

size_t VelodynePcdConverter::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
                                       int64_t time_sync_offset, const Extrinsicf& extrinsic,
                                       LidarCompressAlgorithm alg)
{
    std::shared_ptr<DeserializerType> deserializer = nullptr;
    if (alg == LidarCompressAlgorithm::LZ4)
    {
        LOG(ERROR) << "velodyne is not support LZ4 compress algorithm now!";
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

}  // namespace velodyne
}  // namespace sensors
}  // namespace holo
