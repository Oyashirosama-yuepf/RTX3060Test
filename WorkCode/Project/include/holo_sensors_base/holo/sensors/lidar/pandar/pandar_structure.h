/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pandar_structure.h
 * @brief This header file define the structures of pandar driver
 * @author guoguangchao@holomatic.com
 * @date 2021-03-15
 */

#ifndef _HOLO_SENSORS_BASE_LIDAR_PANDAR_PANDAR_STRUCTURE_H
#define _HOLO_SENSORS_BASE_LIDAR_PANDAR_PANDAR_STRUCTURE_H

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/log/hololog.h>
#include <holo/sensors/format/pandar.h>
#include <functional>
#include <vector>

namespace holo
{
namespace sensors
{
namespace pandar
{
// static const uint16_t PANDAR_HEADER = 0xFFEE;
// static const float32_t PANDAR_ROTATION_RESOLUTION = 0.01f;

// static const float32_t PANDAR_DEPTH_RESOLUTION = 0.004f;
static const uint16_t PANDAR_BEAMS_NUM = 40;
// static const uint16_t PANDAR_POINT_SIZE = 3;
// static const uint16_t PANDAR_BLOCK_DATA_BYTE_SIZE = PANDAR_BEAMS_NUM * PANDAR_POINT_SIZE;
static const uint16_t PANDAR_BLOCKS_PER_PACKET = 10;
static const uint16_t PANDAR_PACKET_BYTE_SIZE  = 1256;
static const uint16_t PANDAR_GPS_PACKET_SIZE   = 512;

static const uint16_t  PANDAR_POINTS_PER_PACKET    = PANDAR_BLOCKS_PER_PACKET * PANDAR_BEAMS_NUM;
static const float32_t PANDAR_PT_TIME_OFFSET_US_1  = 0.93f;
static const float32_t PANDAR_PT_TIME_OFFSET_US_2  = 1.6f;
static const float32_t PANDAR_BLOCK_TIME_OFFSET_US = 55.56f;

static const uint8_t PANDAR_STRONGEST_RETURN = 0x37;
static const uint8_t PANDAR_LAST_RETURN      = 0x38;
static const uint8_t PANDAR_DUAL_RETURN      = 0x39;

using holo::sensors::format::PandarBlock;
using holo::sensors::format::PandarGpsPacket;
using holo::sensors::format::PandarPacket;

class PandarScan
{
public:
    PandarScan() : coord_(0), timestamp_(0, 0)
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

    std::vector<PandarPacket>& Packets()
    {
        return packets_;
    }

    const std::vector<PandarPacket>& Packets() const
    {
        return packets_;
    }

    size_t Size() const noexcept
    {
        return packets_.size();
    }

    const PandarPacket& operator[](size_t index) const
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

    void PushBack(const PandarPacket& packet)
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
                uint32_t reserved   = packets_[i].GetSerializedSize();
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
            PandarPacket   packet;
            const uint32_t size = (packet.GetSerializedSize() + (4 - 1)) / 4 * 4;
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

private:
    holo::common::Coordinate  coord_;     /* the source of the velodyne scan */
    holo::common::Timestamp   timestamp_; /* hour resolution timestamp */
    std::vector<PandarPacket> packets_;   /* use vector for the number of packets in 1scan is not constant */
};

}  // namespace pandar
}  // namespace sensors
}  // namespace holo

#endif
