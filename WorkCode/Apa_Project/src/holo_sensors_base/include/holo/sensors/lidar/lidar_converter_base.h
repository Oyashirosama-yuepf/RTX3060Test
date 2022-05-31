/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file converter_base.h
 * @brief This header file define the function of lidar converter base
 * @author wujie@holomatic.com
 * @date 2021-04-20
 */

#ifndef _HOLO_SENSORS_LIDAR_CONVERTER_BASE_H
#define _HOLO_SENSORS_LIDAR_CONVERTER_BASE_H

#include <holo/common/extrinsic.h>
#include <holo/sensors/utils/lidar_utils.h>

namespace holo
{
namespace sensors
{
using holo::sensors::LidarCompressAlgorithm;

class PcdConverterBase
{
public:
    using Extrinsicf       = holo::common::Extrinsicf;
    using PointType        = holo::point_cloud::PointXYZIRSt<float32_t>;
    using DeserializerType = holo::serialization::Deserializer<false, 4>;
    using PointCloudType   = holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(),
                                                          sizeof(PointType), point_cloud::UnorganizedLayoutTag>;

    PcdConverterBase(const Extrinsicf& extrinsic, uint32_t decompress_capacity)
      : extrinsic_(extrinsic)
      , dec_data_(new char[decompress_capacity](), std::default_delete<char[]>())
      , decompress_capacity_(decompress_capacity)
    {
    }

    virtual ~PcdConverterBase() = default;

    virtual size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
                             LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE) = 0;
    virtual size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd, int64_t time_sync_offset,
                             const Extrinsicf&      extrinsic,
                             LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE) = 0;

protected:
    bool_t DeCompress(const uint8_t* data, uint32_t size, LidarCompressAlgorithm alg,
                      std::shared_ptr<DeserializerType>& deserializer)
    {
        (void)deserializer;

        /* LZ4 DeCompress */
        if (alg == LidarCompressAlgorithm::LZ4)
        {
            if (size < 1024 + 6)
            {
                LOG(ERROR) << "unable to decompress due to data too small: " << size;
                return false;
            }
            /* provide memory for decompress, pcl raw data size + 1024 byte*/
            uint32_t dec_capacity = (((static_cast<uint32_t>(data[size - 3]) & 0xff) << 24) |
                                     ((static_cast<uint32_t>(data[size - 4]) & 0xff) << 16) |
                                     ((static_cast<uint32_t>(data[size - 5]) & 0xff) << 8) |
                                     ((static_cast<uint32_t>(data[size - 6]) & 0xff) << 0)) +
                                    1024;
            if (dec_capacity > decompress_capacity_)
            {
                LOG(ERROR) << "unable to decompress due to data too large: " << size << ", " << dec_capacity;
                return false;
            }

            /* do decompress*/
            int32_t dec_size = LZ4_decompress_safe(reinterpret_cast<const char*>(data), dec_data_.get(),
                                                   static_cast<int>(size - 6), dec_capacity);
            if (dec_size <= 0)
            {
                LOG(INFO) << "lidar pcd converter failed to decompress data: " << dec_size;
                return false;
            }
            /* checksum after Decompress */
            uint8_t checksum_a;
            uint8_t checksum_b;
            holo::sensors::CompressCalChecksum(reinterpret_cast<const uint8_t*>(dec_data_.get()), dec_size, checksum_a,
                                               checksum_b);
            if ((checksum_a != data[size - 2]) || (checksum_b != data[size - 1]))
            {
                LOG(ERROR) << "lidar scan data checksum is error!";
                return false;
            }
            deserializer = std::make_shared<DeserializerType>(reinterpret_cast<uint8_t*>(dec_data_.get()), dec_size);
        }
        else if (alg == LidarCompressAlgorithm::NONE)
        {
            deserializer = std::make_shared<DeserializerType>(const_cast<uint8_t*>(data), size);
        }
        else
        {
            LOG(ERROR) << "unknown lidar compress algorithm: " << static_cast<uint32_t>(alg);
            return false;
        }

        return true;
    }

protected:
    const Extrinsicf      extrinsic_;
    std::shared_ptr<char> dec_data_;

private:
    uint32_t decompress_capacity_;
};

}  // namespace sensors
}  // namespace holo

#endif
