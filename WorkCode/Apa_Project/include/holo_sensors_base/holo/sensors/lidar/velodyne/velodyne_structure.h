/*!
 * \brief
 * \author liwenjun
 * \date 2017-07-05
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice. */

#ifndef _HOLO_SENSORS_VELODYNE_STRUCTURES_H
#define _HOLO_SENSORS_VELODYNE_STRUCTURES_H

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/log/hololog.h>
#include <holo/sensors/format/velodyne.h>
#include <holo/serialization/serialization.h>
#include <functional>
#include <vector>

namespace holo
{
namespace sensors
{
namespace velodyne
{
static constexpr uint16_t  VLP_HEADER                    = 0xeeff;
static constexpr float32_t VELODYNE_ROTATION_RESOLUTION  = 0.01f;  // degrees
static constexpr uint16_t  VELODYNE_ROTATION_MAX_UNITS   = 36000;  // degrees
static constexpr float32_t VELODYNE_DEPTH_MAX            = 130.0f; /**< meters */
static constexpr float32_t VELODYNE_DEPTH_RESOLUTION     = 0.002f; /**< meters */
static constexpr int32_t   VELODYNE_DEPTH_MAX_UNITS      = (VELODYNE_DEPTH_MAX / VELODYNE_DEPTH_RESOLUTION + 1);
static constexpr int32_t   VELODYNE_BLOCK_BYTE_SIZE      = 100;
static constexpr int32_t   VELODYNE_RAW_POINT_BYTE_SIZE  = 3;
static constexpr int32_t   VELODYNE_POINTS_PER_BLOCK     = 32;
static constexpr int32_t   VELODYNE_BLOCK_DATA_BYTE_SIZE = (VELODYNE_POINTS_PER_BLOCK * VELODYNE_RAW_POINT_BYTE_SIZE);
static constexpr int32_t   VELODYNE_PACKET_BYTE_SIZE     = 1206;
static constexpr int32_t   VELODYNE_BLOCKS_PER_PACKET    = 12;
static constexpr int32_t   VELODYNE_PACKET_STATUS_SIZE   = 2;
static constexpr int32_t   VELODYNE_PACKET_STAMPS_SIZE   = 4;
static constexpr int32_t   VELODYNE_POINTS_PER_PACKET    = (VELODYNE_POINTS_PER_BLOCK * VELODYNE_BLOCKS_PER_PACKET);
static constexpr int32_t   VLP16_SECTORS_PER_BLOCK       = 2;
static constexpr int32_t   VLP16_SCANS_PER_SECTOR        = 16;
static constexpr float32_t VLP16_BLOCK_TDURATION         = 110.592f;
static constexpr float32_t VLP16_DSR_TOFFSET             = 2.304f;
static constexpr float32_t VLP16_SECTOR_TOFFSET          = 55.296f;
static constexpr int32_t   VELODYNE_GPS_PACKET_BYTE_SIZE = 512;
static constexpr int32_t   VELODYNE_NMEA_BYTE_SIZE       = 72;
static constexpr uint16_t  VELODYNE_STRONGEST_RETURN     = 0x37;
static constexpr uint16_t  VELODYNE_LAST_RETURN          = 0x38;
static constexpr uint16_t  VELODYNE_DUAL_RETURN          = 0x39;
static constexpr uint16_t  VELODYNE_HDL32                = 0x21;
static constexpr uint16_t  VELODYNE_VLP16                = 0x22;
static constexpr uint16_t  VELODYNE_VLP32A               = 0x23;
static constexpr uint16_t  VELODYNE_VLP16HD              = 0x24;
static constexpr float64_t VELODYNE_HDL32_PACKET_TIME    = 0.55296f;  /* the time to receive one packet in ms */
static constexpr float64_t VELODYNE_VLP16_PACKET_TIME    = 1.327104f; /* the time to receive one packet in ms */

using holo::sensors::format::VelodyneBlock;
using holo::sensors::format::VelodyneGpsPacket;
using holo::sensors::format::VelodynePacket;

class VelodyneScan
{
public:
    VelodyneScan() : coord_(0), timestamp_(0, 0)
    {
        packets_.clear();
    }

    void SetCoordinate(const holo::common::Coordinate& coord) noexcept
    {
        coord_ = coord;
    }

    const holo::common::Coordinate& GetCoordinate() const noexcept
    {
        return coord_;
    }

    void SetTimestamp(const holo::common::Timestamp& timestamp) noexcept
    {
        timestamp_ = timestamp;
    }

    const holo::common::Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    std::vector<VelodynePacket>& Packets()
    {
        return packets_;
    }

    const std::vector<VelodynePacket>& Packets() const
    {
        return packets_;
    }

    size_t Size() const noexcept
    {
        return packets_.size();
    }

    const VelodynePacket& operator[](size_t index) const
    {
        return packets_[index];
    }

    void Clear() noexcept
    {
        packets_.clear();
    }

    void Reserve(size_t size)
    {
        packets_.reserve(size);
    }

    void PushBack(const VelodynePacket& packet)
    {
        packets_.push_back(packet);
    }

    template <typename S>
    bool_t Serialize(S& serializer) const
    {
        try
        {
            uint8_t* data = const_cast<uint8_t*>(serializer.GetData());
            serializer << coord_ << timestamp_ << holo::serialization::align;
            for (uint32_t i = 0; i < packets_.size(); i++)
            {
                uint32_t reserved   = VELODYNE_PACKET_BYTE_SIZE;
                uint32_t serialized = packets_[i].Serialize(data + serializer.GetSize(), reserved);
                serializer.Write(data + serializer.GetSize(), serialized);
                serializer << holo::serialization::align;
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
    bool_t Deserialize(D& deserializer)
    {
        try
        {
            deserializer >> coord_ >> timestamp_ >> holo::serialization::align;
            packets_.clear();
            VelodynePacket packet;
            const uint32_t size = (VELODYNE_PACKET_BYTE_SIZE + (4 - 1)) / 4 * 4;
            uint32_t       n    = (deserializer.GetSize() - deserializer.GetOffset()) / size;
            for (uint32_t i = 0; i < n; i++)
            {
                if (packet.Deserialize(deserializer.GetData() + deserializer.GetOffset(), size))
                {
                    packets_.push_back(packet);
                }
                (void)deserializer.Skip(size);
            }
            deserializer >> holo::serialization::align;
        }
        catch (holo::serialization::DeserializationBufferUnderflowException& e)
        {
            LOG(ERROR) << "deserialization underflow: " << e.what();
            return false;
        }
        catch (...)
        {
            LOG(ERROR) << "deserialization unexpected exception";
            return false;
        }
        return true;
    }

private:
    holo::common::Coordinate    coord_;     /* the source of the velodyne scan */
    holo::common::Timestamp     timestamp_; /* hour resolution timestamp */
    std::vector<VelodynePacket> packets_;   /* use vector for the number of packets in 1scan is not constant */
};

}  // namespace velodyne
}  // namespace sensors
}  // namespace holo

#endif
