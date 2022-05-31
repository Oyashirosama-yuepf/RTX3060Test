/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pandar128_structure.h
 * @brief This header file define the structures of pandar128 driver
 * @author wujie@holomatic.com
 * @date 2021-12-28
 */

#ifndef _HOLO_SENSORS_BASE_LIDAR_PANDAR128_STRUCTURE_H
#define _HOLO_SENSORS_BASE_LIDAR_PANDAR128_STRUCTURE_H

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/log/hololog.h>
#include <holo/sensors/format/pandar128.h>
#include <functional>
#include <vector>

namespace holo
{
namespace sensors
{
namespace pandar128
{
using holo::sensors::format::Pandar128Block;
using holo::sensors::format::Pandar128GpsPacket;
using holo::sensors::format::Pandar128Packet;

static constexpr uint32_t  PANDAR128_LASER_NUMS           = 128;
static constexpr uint32_t  PANDAR_POINTS_PER_PACKET       = PANDAR128_LASER_NUMS * 2;
static constexpr float32_t ROTATION_RESOLUTION            = 0.01f;
static constexpr float32_t DEPTH_RESOLUTION               = 0.004f;
static constexpr float32_t DEPTH_BOUNDARY                 = 2.85f;
static constexpr float32_t PI                             = 3.1415926f;
static constexpr float32_t SECOND_PER_MINUTE              = 60;
static constexpr float32_t PANDAR128_BLOCK_TIME_OFFSET_US = 3.148f;

class Pandar128Scan
{
public:
    Pandar128Scan() : coord_(0), timestamp_(0, 0)
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

    std::vector<Pandar128Packet>& Packets()
    {
        return packets_;
    }

    const std::vector<Pandar128Packet>& Packets() const
    {
        return packets_;
    }

    size_t Size() const noexcept
    {
        return packets_.size();
    }

    const Pandar128Packet& operator[](size_t index) const
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

    void PushBack(const Pandar128Packet& packet)
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
            Pandar128Packet packet;
            const uint32_t  size = (packet.GetSerializedSize() + (4 - 1)) / 4 * 4;
            uint32_t        n    = (deserializer.GetSize() - deserializer.GetOffset()) / size;
            for (uint32_t i = 0; i < n; i++)
            {
                if (packet.Deserialize(deserializer.GetData() + deserializer.GetOffset(), size))
                {
                    packets_.push_back(packet);
                }
                deserializer.Skip(size);
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
    holo::common::Coordinate     coord_;     /* the source of the velodyne scan */
    holo::common::Timestamp      timestamp_; /* hour resolution timestamp */
    std::vector<Pandar128Packet> packets_;   /* use vector for the number of packets in 1scan is not constant */
};

}  // namespace pandar128
}  // namespace sensors
}  // namespace holo

#endif
