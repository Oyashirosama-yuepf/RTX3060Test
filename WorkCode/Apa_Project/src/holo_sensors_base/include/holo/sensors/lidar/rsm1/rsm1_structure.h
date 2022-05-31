/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsm1_structure.h
 * @brief This header file defines rsm1 structure.
 * @author zhangtongyang(zhangtongyang@holomaitc.com)
 * @date 2021/08/09
 */
#ifndef _HOLO_SENSORS_LIDAR_RSM1_RSM1_STRUCTURE_H
#define _HOLO_SENSORS_LIDAR_RSM1_RSM1_STRUCTURE_H

#include <holo/log/hololog.h>
#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/sensors/format/rsm1.h>
#include <holo/serialization/serialization.h>
#include <functional>
#include <vector>

namespace holo
{
namespace sensors
{
namespace rsm1
{
using Rsm1Packet           = holo::sensors::format::Rsm1PacketMSOP;
using Rsm1DeviceInfoPacket = holo::sensors::format::Rsm1PacketDIFOP;

static const uint32_t RSM1_HEADER_SIZE              = 32;
static const uint32_t RSM1_BLOCK_SIZE               = 47;
static const uint32_t RSM1_RAW_POINT_SIZE_PER_BLOCK = 9;
static const uint32_t RSM1_POINTS_PER_BLOCK         = 5;
static const uint32_t RSM1_BLOCKS_PER_PACKET        = 25;
static const uint32_t RSM1_POINTS_PER_PACKET        = RSM1_POINTS_PER_BLOCK * RSM1_BLOCKS_PER_PACKET;

class Rsm1Scan
{
public:
    Rsm1Scan() : coord_(0)
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

    std::vector<Rsm1Packet>& Packets()
    {
        return packets_;
    }

    const std::vector<Rsm1Packet>& Packets() const
    {
        return packets_;
    }

    size_t Size() const noexcept
    {
        return packets_.size();
    }

    Rsm1Packet& operator[](size_t index)
    {
        return packets_[index];
    }

    const Rsm1Packet& operator[](size_t index) const
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
        return packets_.capacity() * sizeof(Rsm1Packet);
    }

    void PushBack(const Rsm1Packet& packet)
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
            Rsm1Packet     packet;
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
    holo::common::Coordinate coord_;
    std::vector<Rsm1Packet>  packets_;
};

}  // namespace rsm1
}  // namespace sensors
}  // namespace holo

#endif