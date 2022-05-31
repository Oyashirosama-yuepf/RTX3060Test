/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pandar_converter.h
 * @brief This header file define the function of pandar converter
 * @author guoguangchao@holomatic.com
 * @date 2021-03-15
 */

#ifndef _HOLO_SENSORS_PANDAR_PCD_CONVERTER_H
#define _HOLO_SENSORS_PANDAR_PCD_CONVERTER_H

#include <assert.h>
#include <holo/common/extrinsic.h>
#include <holo/core/exception.h>
#include <holo/geometry/angle.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/lidar/lidar_converter_base.h>
#include <holo/sensors/lidar/pandar/pandar_structure.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace pandar
{
// parameters for pcd conversion
class ConvertParameter
{
public:
    ConvertParameter() : grid(true), min_dis(0.0), max_dis(0.0), start_azimuth(0.0), end_azimuth(0.0)
    {
    }
    ConvertParameter(const holo::yaml::Node& node)
    {
        if (!LoadConvertParameters(node))
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
        return holo::serialization::SerializedSize<ALIGN>(grid, min_dis, max_dis, start_azimuth, end_azimuth);
    }

    bool_t LoadConvertParameters(const holo::yaml::Node& node);

public:
    bool_t    grid;
    float32_t min_dis;
    float32_t max_dis;
    float32_t start_azimuth;
    float32_t end_azimuth;
};

class CorrectionDesc
{
public:
    CorrectionDesc()
      : sines(0.0), cosines(0.0), azimuth_correction(0.0), pt_time_offset_one(0), pt_time_offset_two(0), time_index(0)
    {
    }
    template <typename S>
    bool_t Serialize(S& serializer) const;

    template <typename D>
    bool_t Deserialize(D& deserializer);

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(sines, cosines, azimuth_correction, pt_time_offset_one,
                                                          pt_time_offset_two, time_index);
    }

public:
    float64_t sines;               // sine values of lidar
    float64_t cosines;             // cosine values of lidar
    float32_t azimuth_correction;  // ...
    uint16_t  pt_time_offset_one;  // ...
    uint16_t  pt_time_offset_two;  // ...
    uint16_t  time_index;          // ...
};

class CorrectionParameter
{
public:
    CorrectionParameter()
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
        return data[0].GetSerializedSize<ALIGN>() * 40;
    }

    bool_t LoadCorrectionParameters(const holo::yaml::Node& node);

public:
    CorrectionDesc data[40];
};

template <typename S>
bool_t ConvertParameter::Serialize(S& serializer) const
{
    try
    {
        serializer << grid << min_dis << max_dis << start_azimuth << end_azimuth << holo::serialization::align;
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
bool_t ConvertParameter::Deserialize(D& deserializer)
{
    try
    {
        deserializer >> grid >> min_dis >> max_dis >> start_azimuth >> end_azimuth >> holo::serialization::align;
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

template <typename S>
bool_t CorrectionDesc::Serialize(S& serializer) const
{
    try
    {
        serializer << sines << cosines << azimuth_correction << pt_time_offset_one << pt_time_offset_two << time_index
                   << holo::serialization::align;
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
bool_t CorrectionDesc::Deserialize(D& deserializer)
{
    try
    {
        deserializer >> sines >> cosines >> azimuth_correction >> pt_time_offset_one >> pt_time_offset_two >>
            time_index >> holo::serialization::align;
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

template <typename S>
bool_t CorrectionParameter::Serialize(S& serializer) const
{
    try
    {
        for (int i = 0; i < 40; i++)
        {
            serializer << data[i];
        }
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
        for (int i = 0; i < 40; i++)
        {
            deserializer >> data[i];
        }
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

struct CorrectionDescTime
{
    float64_t sines;               // sine values of lidar
    float64_t cosines;             // cosine values of lidar
    float32_t azimuth_correction;  // ...
    float64_t pt_offset_us;        // ...
    uint16_t  line_index;
};

struct CorrectionParameterSortByTime
{
    CorrectionDescTime data[40];
};

class PandarPcdConverter : public PcdConverterBase
{
public:
    using Extrinsicf       = holo::common::Extrinsicf;
    using Timestamp        = holo::common::Timestamp;
    using PointType        = point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType   = point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(), sizeof(PointType),
                                                    point_cloud::UnorganizedLayoutTag>;
    using DeserializerType = holo::serialization::Deserializer<false, 4>;

    PandarPcdConverter(const ConvertParameter& convert_param, const CorrectionParameter& correct_param,
                       const Extrinsicf& extrinsic)
      : PcdConverterBase(extrinsic, DEC_CAPACITY), convert_param_(convert_param), correct_param_sorted_{}, dec_scan_()
    {
        /* correct parameter sort by time */
        if (!CorrectParameterSortByTime(correct_param))
        {
            throw std::runtime_error("failed to load correction parameters");
        }
    }

    PandarPcdConverter(const holo::yaml::Node& convert_node, const holo::yaml::Node& correct_node,
                       const Extrinsicf& extrinsic)
      : PcdConverterBase(extrinsic, DEC_CAPACITY), convert_param_{}, correct_param_sorted_{}, dec_scan_()
    {
        if (!convert_param_.LoadConvertParameters(convert_node))
        {
            throw std::runtime_error("failed to load convert parameters");
        }
        CorrectionParameter correct_param(correct_node);
        if (!CorrectParameterSortByTime(correct_param))
        {
            throw std::runtime_error("failed to load correction parameters");
        }
    }

    size_t ParseScan(const PandarScan& scan, PointCloudType& pcd);
    size_t ParseScan(const PandarScan& scan, PointCloudType& pcd, int64_t time_sync_offset,
                     const Extrinsicf& extrinsic);

    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
                     LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE);
    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd, int64_t time_sync_offset,
                     const Extrinsicf& extrinsic, LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE);

private:
    size_t Scan2Pcd(const PandarScan& scan, PointCloudType& pcd, const Extrinsicf& extrinsic,
                    int64_t time_sync_offset = 0);
    size_t Unpack(const PandarPacket& packet, const bool_t grid, const Timestamp& base_time, const size_t offset,
                  PointCloudType& pcd, const Extrinsicf& extrinsic) const;
    bool_t CorrectParameterSortByTime(const CorrectionParameter& correct_param);

private:
    static constexpr uint32_t  DEC_CAPACITY        = 1024 * 1024 * 4u;
    static constexpr float32_t PANDAR_MIN_DISTANCE = 0.01f;

private:
    ConvertParameter              convert_param_;
    CorrectionParameterSortByTime correct_param_sorted_;
    PandarScan                    dec_scan_;
};

}  // namespace pandar
}  // namespace sensors
}  // namespace holo

#endif
