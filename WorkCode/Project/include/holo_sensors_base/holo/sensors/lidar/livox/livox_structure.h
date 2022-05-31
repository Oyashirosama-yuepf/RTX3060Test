/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file livox_structure.h
 * @brief This header file defines livox structure.
 * @author guoguangchao(guoguangchao@holomaitc.com)
 * @date 2021/04/16
 */

#ifndef HOLO_SENSORS_BASE_LIDAR_LIVOX_LIVOX_STRUCTURE_H_
#define HOLO_SENSORS_BASE_LIDAR_LIVOX_LIVOX_STRUCTURE_H_

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/log/hololog.h>
#include <holo/sensors/format/livox.h>
#include <holo/serialization/serialization.h>
#include <functional>
#include <vector>

namespace holo
{
namespace sensors
{
namespace livox
{
/* Livox\LivoxHap Scan */
template <typename LivoxPacketType>
class LivoxScan
{
public:
    LivoxScan() : coord_(0), timestamp_(0, 0)
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

    std::vector<LivoxPacketType>& Packets()
    {
        return packets_;
    }

    const std::vector<LivoxPacketType>& Packets() const
    {
        return packets_;
    }

    size_t Size() const noexcept
    {
        return packets_.size();
    }

    const LivoxPacketType& operator[](size_t index) const
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
        return packets_.capacity() * sizeof(LivoxPacketType);
    }

    void PushBack(const LivoxPacketType& packet)
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
            LivoxPacketType packet;
            const uint32_t  size = packet.GetSerializedSize();
            uint32_t        n    = (deserializer.GetSize() - deserializer.GetOffset()) / size;
            for (uint32_t i = 0; i < n; i++)
            {
                if (packet.Deserialize(deserializer.GetData() + deserializer.GetOffset(), size))
                {
                    if (packet.Valid())
                    {
                        packets_.push_back(packet);
                    }
                    else
                    {
                        LOG(ERROR) << "Packet deserialized error";
                    }
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
    holo::common::Coordinate     coord_;     /* the source of the scan */
    holo::common::Timestamp      timestamp_; /* hour resolution timestamp */
    std::vector<LivoxPacketType> packets_;   /* use vector for the number of packets in 1scan */
};

/* livox protocol */
static constexpr uint8_t LIVOX_START_BYTE       = 0xAAu;
static constexpr uint8_t LIVOX_PROTOCOL_VERSION = 0x01u;
static constexpr uint8_t LIVOX_CMD_TYPE_CMD     = 0x00u;
static constexpr uint8_t LIVOX_CMD_TYPE_ACK     = 0x01u;
static constexpr uint8_t LIVOX_CMD_TYPE_MSG     = 0x02u;

/* livox hap protocol */
/* livox hap packet header */
static constexpr uint8_t  LIVOX_HAP_START_BYTE       = 0xAAu;
static constexpr uint8_t  LIVOX_HAP_PROTOCOL_VERSION = 0x02u;
static constexpr uint16_t LIVOX_HAP_CMD_TYPE_CMD     = 0x00u;
static constexpr uint16_t LIVOX_HAP_CMD_TYPE_ACK     = 0x01u;
static constexpr uint16_t LIVOX_HAP_CMD_TYPE_MSG     = 0x02u;
/* livox hap send\recv device */
static constexpr uint16_t LIVOX_HAP_SEND_ID_CTRL0 = 0x10u;
static constexpr uint16_t LIVOX_HAP_SEND_ID_CTRL1 = 0x11u;
static constexpr uint16_t LIVOX_HAP_SEND_ID_CTRL2 = 0x12u;
static constexpr uint16_t LIVOX_HAP_SEND_ID_SLOT0 = 0x00u;
static constexpr uint16_t LIVOX_HAP_SEND_ID_SLOT1 = 0x01u;
static constexpr uint16_t LIVOX_HAP_SEND_ID_SLOT2 = 0x02u;
static constexpr uint16_t LIVOX_HAP_SEND_ID_SLOT3 = 0x03u;
/* livox hap cmd id */
static constexpr uint16_t LIVOX_HAP_CMD_BROADCAST_DISCOVERY = 0x00;
static constexpr uint16_t LIVOX_HAP_CMD_WORK_CONTROL        = 0x02;
/* livox hap default resv */
static constexpr uint16_t LIVOX_HAP_RESV_DEFAULT = 0x00;

enum LivoxHapParamKeyName : uint16_t
{
    KEY_WORK_MODE        = 0x00,
    KEY_VEHICLE_SPEED    = 0x01,
    KEY_ENVIRONMENT_TEMP = 0x02,
    KEY_SLOT_NUM         = 0x03,
    KEY_ADDR             = 0x04,
    KEY_DEVICEVER        = 0x05,
    KEY_PRODUCT_INFO     = 0x06,
    KEY_POINT_TYPE       = 0x07,
    KEY_GLASS_HEAT       = 0x08,
    KEY_SCAN_PATTERN     = 0x09,
    KEY_BLIND_SPOT_SET   = 0x0A,
    KEY_GLASS_TEMP       = 0x0B,
    KEY_SAFETY_INFO      = 0x0C
};
enum LivoxHapWorkMode : uint8_t
{
    NORMAL_MODE         = 0x01,
    WAKE_MODE           = 0x02,
    SLEEP_MODE          = 0x03,
    ERROR_MODE          = 0x04,
    POWERON_CHECK_MODE  = 0x05,
    MOTOR_STARTING_MODE = 0x06,
    MOTOR_STOPPING_MODE = 0x07
};
enum LivoxHapPointType : uint8_t
{
    POINT_TYPE_32 = 0X01,
    POINT_TYPE_16 = 0X02
};
/* Lidar control info : param list value */
struct LivoxHapControlInfo
{
public:
    LivoxHapControlInfo(uint8_t work_mode, int32_t vehicle_speed, int32_t ev_temp, uint8_t slot)
      : work_mode_(work_mode), vehicle_speed_(vehicle_speed), ev_temp_(ev_temp), slot_(slot)
    {
    }
    uint8_t WorkMode() const noexcept
    {
        return work_mode_;
    }
    uint32_t VehicleSpeed() const noexcept
    {
        return vehicle_speed_;
    }
    uint32_t EvTemp() const noexcept
    {
        return ev_temp_;
    }
    uint32_t Slot() const noexcept
    {
        return slot_;
    }

private:
    uint8_t work_mode_;
    int32_t vehicle_speed_;
    int32_t ev_temp_;
    uint8_t slot_; /* 0xff no need to config */
                   // uint8_t data_type_;  /* default uint_32 */
};
template <typename ValueType>
struct LivoxHapKeyValueParam
{
public:
    void SetValue(uint16_t key, ValueType value)
    {
        (void)memcpy(data_, &key, 2);
        (void)memcpy(data_ + 2, &ValueLength, 2);
        (void)memcpy(data_ + 4, &value, ValueLength);
    }
    uint16_t Key()
    {
        return (static_cast<uint16_t>(data_[1]) << 8) | data_[0];
    }
    uint16_t ValLength()
    {
        return ValueLength;
    }
    ValueType Value()
    {
        if (sizeof(uint8_t) == ValueLength)
        {
            return data_[4];
        }
        if (sizeof(uint32_t) == ValueLength)
        {
            return (static_cast<uint32_t>(data_[7]) << 24) | (static_cast<uint32_t>(data_[6]) << 16) |
                   (static_cast<uint32_t>(data_[5]) << 8) | static_cast<uint32_t>(data_[4]);
        }
    }

private:
    static const uint16_t ValueLength = sizeof(ValueType);

private:
    uint8_t data_[4 + ValueLength];
};

}  // namespace livox
}  // namespace sensors
}  // namespace holo

#endif
