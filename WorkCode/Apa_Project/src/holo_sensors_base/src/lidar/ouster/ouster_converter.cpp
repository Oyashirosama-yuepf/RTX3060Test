/*!
 * \brief
 * \author wangzhaobing
 * \date 2022-03-03
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice. */

#include <holo/sensors/lidar/ouster/ouster_converter.h>
#include <holo/sensors/utils/sensors_utils.h>

namespace holo
{
namespace sensors
{
namespace ouster
{
size_t OusterPcdConverter::Unpack(OusterPacket& packet, const bool_t grid, const Timestamp& base_time,
                                  const size_t offset, PointCloudType& pcd, const Extrinsicf& extrinsic) const
{
    size_t count = 0;
    (void)grid; /* suppress unused variable warning */
    (void)pcd;

    for (size_t block_idx = 0; block_idx < OUSTER_BLOCKS_PER_PACKET; block_idx++)
    {
        OusterBlock block = packet.Block(block_idx);
        if (!block.Valid())
        {
            LOG(ERROR) << "1 block header is invalid";
            // continue;
        }
        float32_t base_azimuth     = holo::geometry::Radian<float32_t>(block.Azimuth());
        float32_t cos_base_azimuth = std::cos(base_azimuth);
        float32_t sin_base_azimuth = std::sin(base_azimuth);

        uint32_t point_index = 0;

        float32_t n = convert_param_.lidar_origin_to_beam_origin_mm * 1e-3;

        for (size_t pt_idx = 0; pt_idx < OUSTER_BEAMS_NUM; pt_idx++)
        {
            float32_t distance = block.Depth(pt_idx) - n;

            if (distance > OUSTER_MIN_DISTANCE)
            {
                uint32_t intensity = block.Intensity(pt_idx);

                float32_t azimuth     = base_azimuth + correct_param_.data[pt_idx].azimuth_correction;
                float32_t cos_azimuth = std::cos(azimuth);
                float32_t sin_azimuth = std::sin(azimuth);

                float32_t x = static_cast<float32_t>(distance * correct_param_.data[pt_idx].cosines * cos_azimuth +
                                                     n * cos_base_azimuth);
                float32_t y = static_cast<float32_t>(distance * correct_param_.data[pt_idx].cosines * sin_azimuth +
                                                     n * sin_base_azimuth);
                float32_t z = static_cast<float32_t>(distance * correct_param_.data[pt_idx].sines);
                holo::geometry::Point3f position(x, y, z);
                position     = extrinsic.GetPose().TransformFrom(position);
                PointType& p = pcd.at(offset + count + point_index);
                p.Set(position.GetX(), position.GetY(), position.GetZ());
                p.SetIntensity(intensity);
                p.SetRing(pt_idx);
                p.SetTimestamp(base_time);
                point_index++;
            }
        }
        count += point_index;
    }
    return count;
}
size_t OusterPcdConverter::Scan2Pcd(OusterScan const& scan, PointCloudType& pcd, const Extrinsicf& extrinsic)
{
    if (scan.Size() == 0)
    {
        return 0;
    }
    pcd.SetCoordinate(scan.GetCoordinate());
    // get the total point number in this scan and initialize the point cloud based on this point number
    pcd.reserve(scan.Size() * OUSTER_POINTS_PER_PACKET);
    pcd.resize(scan.Size() * OUSTER_POINTS_PER_PACKET);
    Timestamp base_hour    = scan.GetTimestamp();
    size_t    point_number = 0;
    for (size_t i = 0; i < scan.Size(); i++)
    {
        OusterPacket packet = scan[i];
        /* update the timestamp */
        Timestamp base_time = base_hour + holo::common::Duration(packet.GetBlockTimeStamp() / 1e9 + 1);
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

size_t OusterPcdConverter::ParseScan(OusterScan const& scan, PointCloudType& pcd)
{
    return Scan2Pcd(scan, pcd, extrinsic_);
}

size_t OusterPcdConverter::ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd)
{
    std::shared_ptr<DeserializerType> deserializer = nullptr;
    deserializer = std::make_shared<DeserializerType>(const_cast<uint8_t*>(data), size);
    if (dec_scan_.Deserialize(*deserializer))
    {
        return Scan2Pcd(dec_scan_, pcd, extrinsic_);
    }

    return 0;
}

}  // namespace ouster

}  // namespace sensors

}  // namespace holo
