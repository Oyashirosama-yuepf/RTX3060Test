/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsbpearl_structure.h
 * @brief This header file defines rsbpearl structure.
 * @author wujie(wujie@holomaitc.com)
 * @date 2022/01/11
 */
#ifndef _HOLO_SENSORS_LIDAR_RSBPEARL_STRUCTURE_H
#define _HOLO_SENSORS_LIDAR_RSBPEARL_STRUCTURE_H

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/log/hololog.h>
#include <holo/sensors/format/rsbpearl.h>
#include <holo/serialization/serialization.h>
#include <functional>
#include <vector>

namespace holo
{
namespace sensors
{
namespace rsbpearl
{
using RsbpearlPacket      = holo::sensors::format::RsbpearlPacketMSOP;
using RsbpearlPacketDIFOP = holo::sensors::format::RsbpearlPacketDIFOP;

static const uint32_t RSBPEARL_HEADER_SIZE              = 42;
static const uint32_t RSBPEARL_BLOCK_SIZE               = 1200;
static const uint32_t RSBPEARL_RAW_POINT_SIZE_PER_BLOCK = 3;
static const uint32_t RSBPEARL_POINTS_PER_BLOCK         = 32;
static const uint32_t RSBPEARL_BLOCKS_PER_PACKET        = 12;
static const uint32_t RSBPEARL_POINTS_PER_PACKET        = RSBPEARL_POINTS_PER_BLOCK * RSBPEARL_BLOCKS_PER_PACKET;

class RsbpearlScan
{
public:
    RsbpearlScan() : coord_(0)
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

    std::vector<RsbpearlPacket>& Packets()
    {
        return packets_;
    }

    const std::vector<RsbpearlPacket>& Packets() const
    {
        return packets_;
    }

    size_t Size() const noexcept
    {
        return packets_.size();
    }

    RsbpearlPacket& operator[](size_t index)
    {
        return packets_[index];
    }

    const RsbpearlPacket& operator[](size_t index) const
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
        return packets_.capacity() * sizeof(RsbpearlPacket);
    }

    void PushBack(const RsbpearlPacket& packet)
    {
        packets_.push_back(packet);
    }

    template <typename S>
    bool_t Serialize(S& serializer) const
    {
        try
        {
            uint8_t* data = const_cast<uint8_t*>(serializer.GetData());
            serializer << coord_ << holo::serialization::align;
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
            deserializer >> coord_ >> holo::serialization::align;
            packets_.clear();
            RsbpearlPacket packet;
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
    holo::common::Coordinate    coord_;
    std::vector<RsbpearlPacket> packets_;
};

}  // namespace rsbpearl
}  // namespace sensors
}  // namespace holo

#endif