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

#ifndef _HOLO_SENSORS_PANDAR128_CONVERTER_H
#define _HOLO_SENSORS_PANDAR128_CONVERTER_H

#include <assert.h>
#include <holo/common/extrinsic.h>
#include <holo/core/exception.h>
#include <holo/geometry/angle.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/lidar/lidar_converter_base.h>
#include <holo/sensors/lidar/pandar128/pandar128_structure.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace pandar128
{
using holo::sensors::LidarCompressAlgorithm;

class CorrectionParameter
{
public:
    CorrectionParameter() noexcept : vertical_angle{}, azimuth_correction{}
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
        return holo::serialization::SerializedSize<ALIGN>(vertical_angle[0]) * 2 * PANDAR128_LASER_NUMS;
    }

    bool_t LoadCorrectionParameters(const holo::yaml::Node& node);

public:
    static constexpr uint32_t PACKET_SIZE = PANDAR128_LASER_NUMS * 2 * sizeof(int16_t);
    int16_t                   vertical_angle[PANDAR128_LASER_NUMS];
    int16_t                   azimuth_correction[PANDAR128_LASER_NUMS];
};

template <typename S>
bool_t CorrectionParameter::Serialize(S& serializer) const
{
    try
    {
        for (uint32_t i = 0; i < PANDAR128_LASER_NUMS; i++)
        {
            serializer << vertical_angle[i];
        }
        for (uint32_t i = 0; i < PANDAR128_LASER_NUMS; i++)
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
        for (uint32_t i = 0; i < PANDAR128_LASER_NUMS; i++)
        {
            deserializer >> vertical_angle[i];
        }
        for (uint32_t i = 0; i < PANDAR128_LASER_NUMS; i++)
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

class LuminousTimeParameter
{
public:
    LuminousTimeParameter() noexcept
      : high_azimuth_far{}, high_azimuth_near{}, standard_azimuth_far{}, standard_azimuth_near{}
    {
    }
    LuminousTimeParameter(const holo::yaml::Node& node)
    {
        if (!LoadLuminousTimeParameters(node))
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
        return holo::serialization::SerializedSize<ALIGN>(high_azimuth_far[0][0]) * 12 * PANDAR128_LASER_NUMS;
    }

    bool_t LoadLuminousTimeParameters(const holo::yaml::Node& node);

public:
    static constexpr uint32_t PACKET_SIZE = PANDAR128_LASER_NUMS * 12 * sizeof(uint16_t);
    uint16_t                  high_azimuth_far[4][PANDAR128_LASER_NUMS];
    uint16_t                  high_azimuth_near[4][PANDAR128_LASER_NUMS];
    uint16_t                  standard_azimuth_far[2][PANDAR128_LASER_NUMS];
    uint16_t                  standard_azimuth_near[2][PANDAR128_LASER_NUMS];
};

template <typename S>
bool_t LuminousTimeParameter::Serialize(S& serializer) const
{
    try
    {
        const uint16_t* ptr = &high_azimuth_far[0][0];
        for (uint32_t i = 0; i < PANDAR128_LASER_NUMS * 12; i++)
        {
            serializer << *ptr;
            ptr++;
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
bool_t LuminousTimeParameter::Deserialize(D& deserializer)
{
    try
    {
        uint16_t* ptr = &high_azimuth_far[0][0];
        for (uint32_t i = 0; i < PANDAR128_LASER_NUMS * 12; i++)
        {
            deserializer >> *ptr;
            ptr++;
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

class Pandar128PcdConverter : public PcdConverterBase
{
public:
    using Extrinsicf       = holo::common::Extrinsicf;
    using Timestamp        = holo::common::Timestamp;
    using PointType        = point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType   = point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(), sizeof(PointType),
                                                    point_cloud::UnorganizedLayoutTag>;
    using DeserializerType = holo::serialization::Deserializer<false, 4>;

    Pandar128PcdConverter(const LuminousTimeParameter& luminous_time_param, const CorrectionParameter& correct_param,
                          const Extrinsicf& extrinsic)
      : PcdConverterBase(extrinsic, DEC_CAPACITY)
      , luminous_time_param_(luminous_time_param)
      , correct_param_(correct_param)
      , dec_scan_()
    {
    }

    Pandar128PcdConverter(const holo::yaml::Node& luminous_time_node, const holo::yaml::Node& correct_node,
                          const Extrinsicf& extrinsic)
      : PcdConverterBase(extrinsic, DEC_CAPACITY), dec_scan_()
    {
        if (!correct_param_.LoadCorrectionParameters(correct_node))
        {
            throw std::runtime_error("failed to load correction parameters");
        }
        if (!luminous_time_param_.LoadLuminousTimeParameters(luminous_time_node))
        {
            throw std::runtime_error("failed to load luminous time parameters");
        }
    }

    size_t ParseScan(const Pandar128Scan& scan, PointCloudType& pcd);
    size_t ParseScan(const Pandar128Scan& scan, PointCloudType& pcd, int64_t time_sync_offset,
                     const Extrinsicf& extrinsic);

    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
                     LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE);
    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd, int64_t time_sync_offset,
                     const Extrinsicf& extrinsic, LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE);

private:
    size_t   Scan2Pcd(const Pandar128Scan& scan, PointCloudType& pcd, const Extrinsicf& extrinsic,
                      int64_t time_sync_offset = 0);
    uint16_t SearchLuminousTime(Pandar128Packet::OperationalStateType operational_state, uint16_t azimuth_flag,
                                uint16_t depth, uint16_t channel);

private:
    static constexpr uint32_t DEC_CAPACITY = 1024 * 1024 * 4u;

private:
    LuminousTimeParameter luminous_time_param_;
    CorrectionParameter   correct_param_;
    Pandar128Scan         dec_scan_;
};

}  // namespace pandar128
}  // namespace sensors
}  // namespace holo

#endif
