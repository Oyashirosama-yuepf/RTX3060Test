/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file livox_converter.h
 * @brief This header file define the function of livox converter
 * @author guoguangchao@holomatic.com
 * @date 2021-04-20
 */

#ifndef _HOLO_SENSORS_LIDAR_LIVOX_LIVOX_CONVERTER_H
#define _HOLO_SENSORS_LIDAR_LIVOX_LIVOX_CONVERTER_H

#include <assert.h>
#include <holo/common/extrinsic.h>
#include <holo/core/exception.h>
#include <holo/geometry/angle.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/lidar/lidar_converter_base.h>
#include <holo/sensors/lidar/livox/livox_structure.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/serialization/deserializer.h>
#include <holo/utils/yaml.h>
#include <memory>

namespace holo
{
namespace sensors
{
namespace livox
{
using holo::sensors::LidarCompressAlgorithm;
using holo::sensors::format::LivoxPacket;

template <typename LivoxPacketType>
class LivoxPcdConverter : public PcdConverterBase
{
public:
    using Extrinsicf       = holo::common::Extrinsicf;
    using Duration         = holo::common::Duration;
    using Timestamp        = holo::common::Timestamp;
    using PointType        = holo::point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType   = holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(),
                                                          sizeof(PointType), point_cloud::UnorganizedLayoutTag>;
    using DeserializerType = holo::serialization::Deserializer<false, 4>;

    LivoxPcdConverter(const Extrinsicf& extrinsic, uint32_t packet_rate)
      : PcdConverterBase(extrinsic, DEC_CAPACITY)
      , duration_(float64_t(1.0) / packet_rate / LivoxPacketType::CAPACITY)
      , dec_scan_()
    {
    }

    size_t ParseScan(const LivoxScan<LivoxPacketType>& scan, PointCloudType& pcd);
    size_t ParseScan(const LivoxScan<LivoxPacketType>& scan, PointCloudType& pcd, int64_t time_sync_offset,
                     const Extrinsicf& extrinsic);

    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
                     LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE);
    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd, int64_t time_sync_offset,
                     const Extrinsicf& extrinsic, LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE);

private:
    size_t Scan2Pcd(const LivoxScan<LivoxPacketType>& scan, PointCloudType& pcd, const Extrinsicf& extrinsic,
                    int64_t time_sync_offset = 0);

private:
    static constexpr uint32_t DEC_CAPACITY = 1024 * 1024 * 4u;

private:
    const Duration             duration_;
    LivoxScan<LivoxPacketType> dec_scan_;
};

}  // namespace livox
}  // namespace sensors
}  // namespace holo

#endif
