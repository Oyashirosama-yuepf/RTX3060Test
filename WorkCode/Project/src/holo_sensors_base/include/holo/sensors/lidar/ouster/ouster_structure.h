/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ouster_driver.h
 * @brief This header file define the function of ouster driver
 * @author yinweigen@holomatic.com
 * @date 2022-01-17
 */

#ifndef _HOLO_SENSORS_BASE_LIDAR_OUSTER_STRUCTURE_H
#define _HOLO_SENSORS_BASE_LIDAR_OUSTER_STRUCTURE_H

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/log/hololog.h>
#include <holo/sensors/format/ouster.h>

#include <functional>
#include <vector>

namespace holo
{
namespace sensors
{
namespace ouster
{
static const uint16_t OUSTER_BEAMS_NUM         = 128; /*OS-128*/
static const uint16_t OUSTER_BLOCKS_PER_PACKET = 16;
static const uint16_t OUSTER_PACKET_BYTE_SIZE  = 24896; /*OS-128*/
static const uint16_t OUSTER_Imu_PACKET_SIZE   = 48;

static const uint16_t  OUSTER_POINTS_PER_PACKET    = OUSTER_BLOCKS_PER_PACKET * OUSTER_BEAMS_NUM;
static const float32_t OUSTER_PT_TIME_OFFSET_US_1  = 0.93f;
static const float32_t OUSTER_PT_TIME_OFFSET_US_2  = 1.6f;
static const float32_t OUSTER_BLOCK_TIME_OFFSET_US = 55.56f;

static const uint8_t OUSTER_STRONGEST_RETURN = 0x37;
static const uint8_t OUSTER_LAST_RETURN      = 0x38;
static const uint8_t OUSTER_DUAL_RETURN      = 0x39;

using holo::sensors::format::OusterBlock;
using holo::sensors::format::OusterImuPacket;
using holo::sensors::format::OusterPacket;

class OusterScan
{
public:
    OusterScan() : coord_(0), timestamp_(0, 0)
    {
        packets_.clear();
    }

    void SetCoordinate(holo::common::Coordinate coord) noexcept
    {
        coord_ = coord;
    }

    const holo::common::Coordinate& GetCoordinate() const noexcept
    {
        return coord_;
    }

    void SetTimestamp(holo::common::Timestamp timestamp) noexcept
    {
        timestamp_ = timestamp;
    }

    const holo::common::Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    std::vector<OusterPacket>& Packets()
    {
        return packets_;
    }

    const std::vector<OusterPacket>& Packets() const
    {
        return packets_;
    }

    size_t Size() const noexcept
    {
        return packets_.size();
    }

    const OusterPacket& operator[](size_t index) const
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

    void PushBack(const OusterPacket& packet)
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
            OusterPacket   packet;
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
    holo::common::Coordinate  coord_;
    holo::common::Timestamp   timestamp_;
    std::vector<OusterPacket> packets_;
};

}  // namespace ouster
}  // namespace sensors
}  // namespace holo

#endif
