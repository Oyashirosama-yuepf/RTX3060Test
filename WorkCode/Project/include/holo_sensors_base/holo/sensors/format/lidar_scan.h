/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lidar_scan.h
 * @brief the lidar scan data definition
 * @author wujie@holomatic.com
 * @date 2021-11-02
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#ifndef HOLO_SENSORS_FORMAT_LIDAR_SCAN_H
#define HOLO_SENSORS_FORMAT_LIDAR_SCAN_H

#include <holo/common/extrinsic.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/format/packed_data.h>
#include <holo/sensors/lidar/lidar_converter_base.h>
#include <holo/sensors/lidar/livox/livox_converter.h>
#if defined(HOLO_PLATFORM_MDC610)
#include <holo/sensors/lidar/mdc610/mdc610_lidar_converter.h>
#endif
#include <holo/sensors/lidar/pandar/pandar_converter.h>
#include <holo/sensors/lidar/pandar128/pandar128_converter.h>
#include <holo/sensors/lidar/rsbpearl/rsbpearl_converter.h>
#include <holo/sensors/lidar/rsm1/rsm1_converter.h>
#include <holo/sensors/lidar/rsruby/rsruby_converter.h>
#include <holo/sensors/lidar/velodyne/velodyne_converter.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <condition_variable>
#include <mutex>

namespace holo
{
namespace sensors
{
namespace format
{
static constexpr size_t MAX_SCAN_CAPACITY = 1024 * 1024 * 4;
using ConverterPtr                        = typename std::shared_ptr<PcdConverterBase>;

/*
    @brief input scan, output pcd
*/
template <uint32_t ScanCapacity = MAX_SCAN_CAPACITY>
class LidarScan
{
public:
    enum class LidarType : uint32_t
    {
        NONE      = 0,
        LIVOX     = 1,
        LIVOXHAP  = 2,
        PANDAR    = 3,
        RSM1      = 4,
        RSRUBY    = 5,
        VELODYNE  = 6,
        PANDAR128 = 7,
        RSBPEARL  = 8,
        MDC610    = 9
    };

public:
    using SerializerType   = holo::serialization::Serializer<false, 4>;
    using DeserializerType = holo::serialization::Deserializer<false, 4>;
    using CompressUtils    = holo::sensors::CompressUtils;
    using Extrinsicf       = holo::common::Extrinsicf;

    /* subscriber */
    LidarScan();
    /* publisher */
    LidarScan(LidarType type, bool_t use_compress, const Extrinsicf& extrinsic, const uint8_t* params = nullptr,
              uint32_t bytes = 0);

    /* pub\sub raw scan */
    LidarScan(LidarType type, bool_t use_compress, const Extrinsicf& extrinsic, bool_t pub_raw_scan,
              const uint8_t* params = nullptr, uint32_t bytes = 0);

    /* publisher set scan */
    template <typename LidarScanType>
    bool_t SetScanData(const LidarScanType& scan);

    /* subscriber get pcd */
    template <typename D, typename PointCloudType>
    bool_t ConvertToPcd(D& deserializer, PointCloudType& pcd);

    template <typename D, typename PointCloudType>
    bool_t ConvertToPcd(D& deserializer, PointCloudType& pcd, const Extrinsicf& extrinsic);

    template <typename S>
    bool_t Serialize(S& serializer) const;

    uint32_t SetConverterParams(const uint8_t* params, uint32_t bytes);

    const Extrinsicf& GetExtrinsic() const noexcept
    {
        return extrinsic_;
    }

    void SetTimeOffset0(const int64_t& time_sync_offset0);

    void SetTimeOffset1(const int64_t& time_sync_offset1);

private:
    template <typename D>
    bool_t IsLegcy(D& deserializer);

    template <typename D>
    bool_t Deserialize(D& deserializer);

    template <typename D>
    bool_t DeserializeLegacy(D& deserializer);

    template <typename D>
    bool_t DeserializeNew(D& deserializer);

    template <typename PointCloudType>
    bool_t ConvertToPcd(PointCloudType& pcd, const Extrinsicf& extrinsic);

    ConverterPtr GetConverter(LidarType type);

    bool_t IsValid(ConverterPtr converter);

    ConverterPtr CreateConverter(LidarType type, std::shared_ptr<DeserializerType> deserializer);

private:
    static constexpr uint32_t         MAX_PARAMS_LENGTH = 4096; /* max: pandar128 */
    static constexpr int32_t          COMPRESS_ACCEL    = 1;
    bool_t                            is_compressed_;
    bool_t                            pub_raw_scan_;
    std::shared_ptr<CompressUtils>    compress_utils_;
    std::map<LidarType, ConverterPtr> converters_;
    std::mutex                        mutex_;
    /*
        data: |version|type|extrinsic|params_len|params|time_sync_offset|packeddata|
    */
    uint32_t                             version_;
    LidarType                            type_;
    Extrinsicf                           extrinsic_;
    uint32_t                             params_len_;
    uint8_t                              params_[MAX_PARAMS_LENGTH];
    int64_t                              time_sync_offsets_[2];
    SensorCompressedPacket<ScanCapacity> scan_data_;
};

template <uint32_t ScanCapacity>
template <typename LidarScanType>
bool_t LidarScan<ScanCapacity>::SetScanData(const LidarScanType& scan)
{
    /* scan to packeddata */
    uint8_t*       scan_data = const_cast<uint8_t*>(scan_data_.GetPayload());
    SerializerType serializer(scan_data, ScanCapacity);
    if (!scan.Serialize(serializer))
    {
        LOG(ERROR) << "Serialize faild!";
        return false;
    }
    scan_data_.SetRawDataLen(serializer.GetSize());

    /* Is compress */
    if (is_compressed_)
    {
        if (nullptr == compress_utils_)
        {
            compress_utils_ = std::make_shared<CompressUtils>(ScanCapacity);
        }
        uint32_t              CompressedSize = 0;
        std::shared_ptr<char> CompressOutput = compress_utils_->CompressInterface(
            serializer.GetData(), serializer.GetSize(), CompressedSize, COMPRESS_ACCEL); /* copy */

        if (CompressedSize != 0)
        {
            (void)scan_data_.SetCompressDataLen(CompressedSize);
            scan_data_.SetCompressAlgorithm(DataCompressAlgorithm::LZ4);
            if (0 == scan_data_.SetPayload(0, reinterpret_cast<uint8_t*>(CompressOutput.get()), CompressedSize, true))
            {
                return false;
            }
        }
        else
        {
            LOG(ERROR) << "Compress faild!";
            return false;
        }
    }
    else /* raw data */
    {
        scan_data_.SetCompressAlgorithm(DataCompressAlgorithm::NONE);
        scan_data_.UpdateCrc32();
    }
    return true;
}

template <uint32_t ScanCapacity>
bool_t LidarScan<ScanCapacity>::IsValid(ConverterPtr converter)
{
    if (nullptr == converter)
    {
        LOG(ERROR) << "Lidar Type InValid!";
        return false;
    }
    return true;
}

template <uint32_t ScanCapacity>
template <typename PointCloudType>
bool_t LidarScan<ScanCapacity>::ConvertToPcd(PointCloudType& pcd, const Extrinsicf& extrinsic)
{
    ConverterPtr converter;
    converter = GetConverter(type_);
    int64_t time_sync_offset;

    if (version_ == 0x01)
    {
        time_sync_offset = 0;
    }
    else if (version_ == 0x02)
    {
        time_sync_offset = time_sync_offsets_[0] + time_sync_offsets_[1];
    }
    return IsValid(converter) ?
               (0 != converter->ParseScan(scan_data_.GetPayload(), scan_data_.GetPayloadLength(), pcd, time_sync_offset,
                                          extrinsic, scan_data_.GetCompressAlgorithm())) :
               false;
}

template <uint32_t ScanCapacity>
template <typename D, typename PointCloudType>
bool_t LidarScan<ScanCapacity>::ConvertToPcd(D& deserializer, PointCloudType& pcd, const Extrinsicf& extrinsic)
{
    std::lock_guard<std::mutex> lock{mutex_};
    return Deserialize(deserializer) ? ConvertToPcd(pcd, extrinsic) : false;
}

template <uint32_t ScanCapacity>
template <typename D, typename PointCloudType>
bool_t LidarScan<ScanCapacity>::ConvertToPcd(D& deserializer, PointCloudType& pcd)
{
    return ConvertToPcd(deserializer, pcd, extrinsic_);
}

template <uint32_t ScanCapacity>
template <typename S>
bool_t LidarScan<ScanCapacity>::Serialize(S& serializer) const
{
    try
    {
        uint8_t* data = const_cast<uint8_t*>(serializer.GetData());
        if (!pub_raw_scan_)
        {
            serializer << version_ << static_cast<uint32_t>(type_) << holo::serialization::align;
            extrinsic_.GetParentCoordinate().Serialize(serializer);
            extrinsic_.GetChildCoordinate().Serialize(serializer);
            extrinsic_.GetPose().Serialize(serializer);
            serializer << holo::serialization::align;
            serializer << params_len_ << holo::serialization::align;
            if (0 != params_len_)
            {
                serializer.Write(&params_[0], params_len_);
            }
            serializer << time_sync_offsets_[0] << time_sync_offsets_[1] << holo::serialization::align;
            uint32_t scan_len = scan_data_.Serialize(data + serializer.GetSize(), scan_data_.GetSerializedSize());
            if (scan_len == 0)
            {
                LOG(INFO) << "Lidar Scan Serialize Error, scan Serialize len = 0 !";
                return false;
            }
            else
            {
                serializer.Write(data + serializer.GetSize(), scan_len);
            }
        }
        else
        {
            serializer.Write(scan_data_.GetPayload(), scan_data_.GetPayloadLength());
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

template <uint32_t ScanCapacity>
template <typename D>
bool_t LidarScan<ScanCapacity>::IsLegcy(D& deserializer)
{
    uint32_t len  = 0;
    uint16_t code = 0;
    uint32_t size = deserializer.GetSize();
    D        des(deserializer.GetData(), size);
    des.Skip(64);
    des >> len;
    if (len > size - deserializer.GetOffset())
    {
        return true;
    }
    des.Skip(len + 16);
    des >> code;
    return code != 0xFFFF;
}

template <uint32_t ScanCapacity>
template <typename D>
bool_t LidarScan<ScanCapacity>::Deserialize(D& deserializer)
{
    if (!pub_raw_scan_)
    {
        if (IsLegcy(deserializer))
        {
            return DeserializeLegacy(deserializer);
        }
        return DeserializeNew(deserializer);
    }
    else
    {
        uint8_t* scan_data = const_cast<uint8_t*>(scan_data_.GetPayload());
        deserializer.Read(scan_data, deserializer.GetSize());
        if (is_compressed_)
        {
            scan_data_.SetCompressAlgorithm(DataCompressAlgorithm::LZ4);
            scan_data_.SetCompressDataLen(deserializer.GetSize());
        }
        else
        {
            scan_data_.SetCompressAlgorithm(DataCompressAlgorithm::NONE);
            scan_data_.SetRawDataLen(deserializer.GetSize());
        }
    }
}

template <uint32_t ScanCapacity>
template <typename D>
bool_t LidarScan<ScanCapacity>::DeserializeLegacy(D& deserializer)
{
    try
    {
        version_ = 0x01;
        Extrinsicf::Coordinate coord;
        Extrinsicf::Pose3Type  pose;
        uint32_t&              type = reinterpret_cast<uint32_t&>(type_);

        deserializer >> type >> holo::serialization::align;
        coord.Deserialize(deserializer);
        extrinsic_.SetParentCoordinate(coord);
        coord.Deserialize(deserializer);
        extrinsic_.SetChildCoordinate(coord);
        pose.Deserialize(deserializer);
        extrinsic_.SetPose(pose);
        deserializer >> holo::serialization::align;
        deserializer >> params_len_ >> holo::serialization::align;
        if (0 != params_len_)
        {
            deserializer.Read(&params_[0], params_len_);
        }
        const uint32_t size = deserializer.GetSize() - deserializer.GetOffset();
        if (0 == scan_data_.Deserialize(deserializer.GetData() + deserializer.GetOffset(), size))
        {
            return false;
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

template <uint32_t ScanCapacity>
template <typename D>
bool_t LidarScan<ScanCapacity>::DeserializeNew(D& deserializer)
{
    try
    {
        Extrinsicf::Coordinate coord;
        Extrinsicf::Pose3Type  pose;
        uint32_t&              type = reinterpret_cast<uint32_t&>(type_);

        deserializer >> version_ >> type >> holo::serialization::align;
        coord.Deserialize(deserializer);
        extrinsic_.SetParentCoordinate(coord);
        coord.Deserialize(deserializer);
        extrinsic_.SetChildCoordinate(coord);
        pose.Deserialize(deserializer);
        extrinsic_.SetPose(pose);
        deserializer >> holo::serialization::align;
        deserializer >> params_len_ >> holo::serialization::align;
        if (0 != params_len_)
        {
            deserializer.Read(&params_[0], params_len_);
        }
        deserializer >> time_sync_offsets_[0] >> time_sync_offsets_[1] >> holo::serialization::align;
        const uint32_t size = deserializer.GetSize() - deserializer.GetOffset();
        if (0 == scan_data_.Deserialize(deserializer.GetData() + deserializer.GetOffset(), size))
        {
            return false;
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

}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif
