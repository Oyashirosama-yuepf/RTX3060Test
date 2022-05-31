/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsruby_converter.h
 * @brief This header file defines robosense ruby lidar converter
 * @author wujie(wujie@holomaitc.com)
 * @date 2021/10/26
 */
#ifndef _HOLO_SENSORS_LIDAR_RSRUBY_RSRUBY_CONVERTER_H
#define _HOLO_SENSORS_LIDAR_RSRUBY_RSRUBY_CONVERTER_H

#include <assert.h>
#include <holo/common/extrinsic.h>
#include <holo/core/exception.h>
#include <holo/geometry/angle.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/format/rsruby.h>
#include <holo/sensors/lidar/lidar_converter_base.h>
#include <holo/sensors/lidar/rsruby/rsruby_structure.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace rsruby
{
using holo::sensors::LidarCompressAlgorithm;
using RsrubyScanType = holo::sensors::rsruby::RsrubyScan;

class CorrectionParameter
{
public:
    CorrectionParameter() : vertical_angle{}, azimuth_correction{}
    {
    }
    CorrectionParameter(const holo::yaml::Node& node)
    {
        if (!LoadCorrectionParameters(node))
        {
            std::ostringstream oss;
            oss << "yaml node load failed!";
            LOG(ERROR) << oss.str();
            throw std::invalid_argument(oss.str());
        }
    }

    template <typename S>
    bool_t Serialize(S& serializer) const;

    template <typename D>
    bool_t Deserialize(D& deserializer);

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(vertical_angle[0]) * 256;
    }

    bool LoadCorrectionParameters(const holo::yaml::Node& node);

public:
    static constexpr uint32_t PACKET_SIZE = 128 * 2 * sizeof(int16_t);
    int16_t                   vertical_angle[128];
    int16_t                   azimuth_correction[128];
};

template <typename S>
bool_t CorrectionParameter::Serialize(S& serializer) const
{
    try
    {
        for (int i = 0; i < 128; i++)
        {
            serializer << vertical_angle[i];
        }
        for (int i = 0; i < 128; i++)
        {
            serializer << azimuth_correction[i];
        }
        serializer << holo::serialization::align;
    }
    catch (holo::serialization::SerializationBufferOverflowException& e)
    {
        LOG(ERROR) << "serialization overflow: " << e.what();
        return false;
    }
    catch (...)
    {
        LOG(ERROR) << "serialization unexpected exception";
        return false;
    }
    return true;
}

template <typename D>
bool_t CorrectionParameter::Deserialize(D& deserializer)
{
    try
    {
        for (int i = 0; i < 128; i++)
        {
            deserializer >> vertical_angle[i];
        }
        for (int i = 0; i < 128; i++)
        {
            deserializer >> azimuth_correction[i];
        }
        deserializer >> holo::serialization::align;
    }
    catch (holo::serialization::DeserializationBufferUnderflowException& e)
    {
        LOG(ERROR) << "deserialization overflow: " << e.what();
        return false;
    }
    catch (...)
    {
        LOG(ERROR) << "deserialization unexpected exception";
        return false;
    }
    return true;
}

class RsrubyPcdConverter : public PcdConverterBase
{
public:
    using Extrinsicf       = holo::common::Extrinsicf;
    using Timestamp        = holo::common::Timestamp;
    using PointType        = point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType   = holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(),
                                                          sizeof(PointType), point_cloud::UnorganizedLayoutTag>;
    using DeserializerType = holo::serialization::Deserializer<false, 4>;

    RsrubyPcdConverter(const Extrinsicf& extrinsic, const CorrectionParameter& correct_param)
      : PcdConverterBase(extrinsic, DEC_CAPACITY), correct_param_(correct_param), dec_scan_()
    {
    }

    RsrubyPcdConverter(const Extrinsicf& extrinsic, const holo::yaml::Node& correct_node)
      : PcdConverterBase(extrinsic, DEC_CAPACITY), correct_param_{}, dec_scan_()
    {
        if (!correct_param_.LoadCorrectionParameters(correct_node))
        {
            throw std::runtime_error("failed to load correction parameters");
        }
    }

    size_t ParseScan(const RsrubyScanType& scan, PointCloudType& pcd);
    size_t ParseScan(const RsrubyScanType& scan, PointCloudType& pcd, int64_t time_sync_offset,
                     const Extrinsicf& extrinsic);

    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
                     LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE);
    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd, int64_t time_sync_offset,
                     const Extrinsicf& extrinsic, LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE);

private:
    size_t Scan2Pcd(const RsrubyScanType& scan, PointCloudType& pcd, const Extrinsicf& extrinsic,
                    int64_t time_sync_offset = 0);

private:
    static constexpr uint32_t DEC_CAPACITY = 1024 * 1024 * 4u;

private:
    static constexpr float64_t DISTANCE_DEGREE = 0.005f;
    static constexpr float64_t ANGLE_DEGREE    = 0.01f;
    CorrectionParameter        correct_param_;
    RsrubyScanType             dec_scan_;
};
}  // namespace rsruby
}  // namespace sensors
}  // namespace holo

#endif