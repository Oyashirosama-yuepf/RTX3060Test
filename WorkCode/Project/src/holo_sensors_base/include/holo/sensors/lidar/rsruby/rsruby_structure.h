/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsruby_structure.h
 * @brief This header file defines rsruby structure.
 * @author wujie(wujie@holomaitc.com)
 * @date 2021/10/26
 */
#ifndef _HOLO_SENSORS_LIDAR_RSRUBY_RSRUBY_STRUCTURE_H
#define _HOLO_SENSORS_LIDAR_RSRUBY_RSRUBY_STRUCTURE_H

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/log/hololog.h>
#include <holo/sensors/format/rsruby.h>
#include <holo/serialization/serialization.h>
#include <functional>
#include <vector>

namespace holo
{
namespace sensors
{
namespace rsruby
{
using RsrubyPacket           = holo::sensors::format::RsrubyPacketMSOP;
using RsrubyDeviceInfoPacket = holo::sensors::format::RsrubyPacketDIFOP;

static const uint32_t RSRUBY_HEADER_SIZE              = 80;
static const uint32_t RSRUBY_BLOCK_SIZE               = 388;
static const uint32_t RSRUBY_RAW_POINT_SIZE_PER_BLOCK = 3;
static const uint32_t RSRUBY_POINTS_PER_BLOCK         = 128;
static const uint32_t RSRUBY_BLOCKS_PER_PACKET        = 3;
static const uint32_t RSRUBY_POINTS_PER_PACKET        = RSRUBY_POINTS_PER_BLOCK * RSRUBY_BLOCKS_PER_PACKET;

class RsrubyScan
{
public:
    RsrubyScan() : coord_(0), timestamp_(0, 0)
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

    std::vector<RsrubyPacket>& Packets()
    {
        return packets_;
    }

    const std::vector<RsrubyPacket>& Packets() const
    {
        return packets_;
    }

    size_t Size() const noexcept
    {
        return packets_.size();
    }

    RsrubyPacket& operator[](size_t index)
    {
        return packets_[index];
    }

    const RsrubyPacket& operator[](size_t index) const
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

    size_t GetCapacity()
    {
        return packets_.capacity() * sizeof(RsrubyPacket);
    }

    void PushBack(const RsrubyPacket& packet)
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
            RsrubyPacket   packet;
            const uint32_t size = packet.GetSerializedSize();
            uint32_t       n    = (deserializer.GetSize() - deserializer.GetOffset()) / size;
            for (uint32_t i = 0; i < n; i++)
            {
                if (0 != packet.Deserialize(deserializer.GetData() + deserializer.GetOffset(), size))
                {
                    packets_.push_back(packet);
                }
                (void)deserializer.Skip(size);
                deserializer >> holo::serialization::align;
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

private:
    holo::common::Coordinate  coord_;
    holo::common::Timestamp   timestamp_; /* hour resolution timestamp */
    std::vector<RsrubyPacket> packets_;
};

}  // namespace rsruby
}  // namespace sensors
}  // namespace holo

#endif