/*!
 * \brief
 * \author liwenjun
 * \date 2017-07-05
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice. */

#ifndef _HOLO_SENSORS_VELODYNE_PCD_CONVERTER_H
#define _HOLO_SENSORS_VELODYNE_PCD_CONVERTER_H

#include <holo/common/extrinsic.h>
#include <holo/core/exception.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/sensors/lidar/lidar_converter_base.h>
#include <holo/sensors/lidar/velodyne/velodyne_structure.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace velodyne
{
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
    bool_t    grid;           // if the pointcloud is needed to be grided
    float32_t min_dis;        // the min distance of the pointcloud
    float32_t max_dis;        // the max distance of the pointcloud
    float32_t start_azimuth;  // the min angle of the pointcloud
    float32_t end_azimuth;    // the max angle of the pointcloud
};

class CorrectionParameter
{
public:
    CorrectionParameter() : sines{}, cosines{}
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
        return holo::serialization::SerializedSize<ALIGN>(sines[0]) * 32;
    }

    bool_t LoadCorrectionParameters(const holo::yaml::Node& node);

public:
    float64_t sines[16];    // sine values of vlp16
    float64_t cosines[16];  // cosine values of vlp16
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
bool_t CorrectionParameter::Serialize(S& serializer) const
{
    try
    {
        for (int i = 0; i < 16; i++)
        {
            serializer << sines[i];
        }
        for (int i = 0; i < 16; i++)
        {
            serializer << cosines[i];
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
        for (int i = 0; i < 16; i++)
        {
            deserializer >> sines[i];
        }
        for (int i = 0; i < 16; i++)
        {
            deserializer >> cosines[i];
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

class VelodynePcdConverter : public PcdConverterBase
{
public:
    using Extrinsicf       = holo::common::Extrinsicf;
    using PointType        = point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType   = point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(), sizeof(PointType),
                                                    point_cloud::UnorganizedLayoutTag>;
    using DeserializerType = holo::serialization::Deserializer<false, 4>;
    VelodynePcdConverter(const ConvertParameter& convert_param, const CorrectionParameter& correct_param,
                         const Extrinsicf& extrinsic)
      : PcdConverterBase(extrinsic, DEC_CAPACITY)
      , convert_param_(convert_param)
      , correct_param_(correct_param)
      , dec_scan_()
    {
    }

    VelodynePcdConverter(const holo::yaml::Node& convert_node, const holo::yaml::Node& correct_node,
                         const Extrinsicf& extrinsic)
      : PcdConverterBase(extrinsic, DEC_CAPACITY), convert_param_{}, correct_param_{}, dec_scan_()
    {
        if (!convert_param_.LoadConvertParameters(convert_node))
        {
            throw std::runtime_error("failed to load convert parameters");
        }
        if (!correct_param_.LoadCorrectionParameters(correct_node))
        {
            throw std::runtime_error("failed to load correction parameters");
        }
    }

    size_t ParseScan(const VelodyneScan& scan, PointCloudType& pcd);
    size_t ParseScan(const VelodyneScan& scan, PointCloudType& pcd, int64_t time_sync_offset,
                     const Extrinsicf& extrinsic);

    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd,
                     LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE);
    size_t ParseScan(const uint8_t* data, uint32_t size, PointCloudType& pcd, int64_t time_sync_offset,
                     const Extrinsicf& extrinsic, LidarCompressAlgorithm alg = LidarCompressAlgorithm::NONE);

private:
    static constexpr uint32_t  DEC_CAPACITY          = 1024 * 1024 * 4u;
    static constexpr float32_t VELODYNE_MIN_DISTANCE = 0.01f;

private:
    size_t UnpackVLP16(const VelodynePacket& packet, bool grid, const holo::common::Timestamp& base_time, size_t offset,
                       PointCloudType& pcd, const Extrinsicf& extrinsic) const;
    void   GetPacketAzimuth(const VelodynePacket& packet, float32_t azimuths[][2]) const;
    bool   CheckPacketFrame(const uint32_t last_velodyne_timestamp, const VelodynePacket& packet,
                            holo::common::Timestamp& base_hour) const;
    size_t Scan2Pcd(const VelodyneScan& scan, PointCloudType& pcd, const Extrinsicf& extrinsic,
                    int64_t time_sync_offset = 0);
    bool   CheckAzimuth(int block, int sector, float32_t azimuths[][VLP16_SECTORS_PER_BLOCK]) const;

private:
    ConvertParameter      convert_param_;
    CorrectionParameter   correct_param_;
    const Extrinsicf      extrinsic_;
    std::shared_ptr<char> dec_data_;
    VelodyneScan          dec_scan_;
};

}  // namespace velodyne
}  // namespace sensors
}  // namespace holo

#endif
