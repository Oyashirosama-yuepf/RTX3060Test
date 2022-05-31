/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ouster_converter.h
 * @brief This header file define the function of ouster converter
 * @author wangzhaobing@holomatic.com
 * @date 2022-03-2
 */

#ifndef _HOLO_SENSORS_OUSTER_PCD_CONVERTER_H
#define _HOLO_SENSORS_OUSTER_PCD_CONVERTER_H

#include <assert.h>
#include <holo/common/extrinsic.h>
#include <holo/core/exception.h>
#include <holo/geometry/angle.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/lidar/lidar_converter_base.h>
#include <holo/sensors/lidar/ouster/ouster_structure.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace ouster
{
class ConvertParameter
{
public:
    ConvertParameter()
      : grid(true)
      , min_dis(0.0)
      , max_dis(0.0)
      , start_azimuth(0.0)
      , end_azimuth(0.0)
      , lidar_origin_to_beam_origin_mm(0.0)
    {
    }

    template <typename S>
    bool_t Serialize(S& serializer) const;

    template <typename D>
    bool_t Deserialize(D& deserializer);

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(grid, min_dis, max_dis, start_azimuth, end_azimuth,
                                                          lidar_origin_to_beam_origin_mm);
    }

public:
    bool_t    grid;
    float32_t min_dis;
    float32_t max_dis;
    float32_t start_azimuth;
    float32_t end_azimuth;
    float32_t lidar_origin_to_beam_origin_mm;
};

class CorrectionDesc
{
public:
    CorrectionDesc() : sines(0.0), cosines(0.0), azimuth_correction(0.0)
    {
    }

    template <typename S>
    bool_t Serialize(S& serializer) const;

    template <typename D>
    bool_t Deserialize(D& deserializer);

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(sines, cosines, azimuth_correction);
    }

public:
    float64_t sines;               // sine values of lidar
    float64_t cosines;             // cosine values of lidar
    float32_t azimuth_correction;  // ...
};

class CorrectionParameter
{
public:
    template <typename S>
    bool_t Serialize(S& serializer) const;

    template <typename D>
    bool_t Deserialize(D& deserializer);

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return data[0].GetSerializedSize<ALIGN>() * 128;
    }

public:
    CorrectionDesc data[128]; /*OS-128*/
};

class OusterPcdConverter
{
public:
    using Extrinsicf       = holo::common::Extrinsicf;
    using Timestamp        = holo::common::Timestamp;
    using PointType        = point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType   = point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(), sizeof(PointType),
                                                    point_cloud::UnorganizedLayoutTag>;
    using DeserializerType = holo::serialization::Deserializer<false, 4>;

    OusterPcdConverter(const ConvertParameter& convert_param, const CorrectionParameter& correct_param,
                       const Extrinsicf& extrinsic)
      : convert_param_(convert_param), correct_param_(correct_param), extrinsic_(extrinsic)
    {
        /*nothing*/
    }

    size_t ParseScan(OusterScan const& scan, PointCloudType& pcd);
    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd);

private:
    size_t Scan2Pcd(OusterScan const& scan, PointCloudType& pcd, const Extrinsicf& extrinsic);
    size_t Unpack(OusterPacket& packet, const bool_t grid, const Timestamp& base_time, const size_t offset,
                  PointCloudType& pcd, const Extrinsicf& extrinsic) const;

private:
    static constexpr uint32_t  DEC_CAPACITY        = 1024 * 1024 * 4u;
    static constexpr float32_t OUSTER_MIN_DISTANCE = 0.01f;

private:
    ConvertParameter    convert_param_;
    CorrectionParameter correct_param_;
    Extrinsicf          extrinsic_;
    OusterScan          dec_scan_;
};
}  // namespace ouster

}  // namespace sensors

}  // namespace holo
#endif
