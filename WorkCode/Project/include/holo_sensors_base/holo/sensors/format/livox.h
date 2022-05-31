/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file livox.h
 * @brief define the velodyne packet structure format class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2021-04-10
 */

#ifndef _HOLO_SENSORS_FORMAT_LIVOX_H
#define _HOLO_SENSORS_FORMAT_LIVOX_H

#include <holo/common/timestamp.h>
#include <holo/sensors/format/format.h>
#include <holo/sensors/utils/livox_crc.h>
#include <holo_c/core/static_assert.h>

namespace holo
{
namespace sensors
{
namespace format
{
using holo::common::Timestamp;
using holo::sensors::format::FormatBase;

class LivoxPoint
{
public:
    LivoxPoint() noexcept : x_(0), y_(0), z_(0), intensity_(0u), tag_(0u)
    {
    }

    int32_t GetX() const noexcept
    {
        return x_;
    }

    int32_t GetY() const noexcept
    {
        return y_;
    }

    int32_t GetZ() const noexcept
    {
        return z_;
    }

    uint8_t GetIntensity() const noexcept
    {
        return intensity_;
    }

    uint8_t GetTag() const noexcept
    {
        return tag_;
    }

    uint8_t GetReturnNum() const noexcept
    {
        return (tag_ >> 4) & 0x03;
    }

private:
    int32_t x_;          // X axis, Unit: mm
    int32_t y_;          // Y axis, Unit: mm
    int32_t z_;          // Z axis, Unit: mm
    uint8_t intensity_;  // Reflectivity
    uint8_t tag_;        // Tag

public:
    static const uint32_t SIZE = 14u;
};

/* livox */
template <uint32_t Capacity, typename PointType = LivoxPoint>
class LivoxPacket : public FormatBase
{
public:
    LivoxPacket() noexcept
    {
        (void)std::memset(&data_[0], 0, sizeof(data_));
    }

    uint8_t Version() const noexcept
    {
        return data_[0];
    }

    uint8_t SlotId() const noexcept
    {
        return data_[1];
    }

    uint8_t LidarId() const noexcept
    {
        return data_[2];
    }

    uint32_t StatusCode() const noexcept
    {
        return (static_cast<uint32_t>(data_[7]) << 24) | (static_cast<uint32_t>(data_[6]) << 16) |
               (static_cast<uint32_t>(data_[5]) << 8) | static_cast<uint32_t>(data_[4]);
    }

    uint8_t TimestampType() const noexcept
    {
        return data_[8];
    }

    uint8_t DataType() const noexcept
    {
        return data_[9];
    }

    uint32_t Size() const noexcept
    {
        return Capacity;
    }

    Timestamp GetTimestamp() const noexcept
    {
        struct tm time;
        time.tm_year  = data_[10] + 2000 - 1900;
        time.tm_mon   = data_[11] - 1;
        time.tm_mday  = data_[12];
        time.tm_hour  = data_[13];
        uint32_t usec = (static_cast<uint32_t>(data_[17]) << 24) | (static_cast<uint32_t>(data_[16]) << 16) |
                        (static_cast<uint32_t>(data_[15]) << 8) | data_[14];
        time.tm_min = (usec / 1000000) / 60;
        time.tm_sec = (usec / 1000000) % 60;
        return Timestamp(uint32_t(timegm(&time)), uint32_t((usec % 1000000) * 1000));
    }

    const PointType* Point(size_t index) const noexcept
    {
        return reinterpret_cast<const PointType*>(data_ + HEAD_SIZE + index * PointType::SIZE);
    }

    bool_t Valid() const noexcept
    {
        return VERSION == Version();
    }

    uint32_t GetSerializedSize() const noexcept
    {
        return PACKET_SIZE;
    }

    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < PACKET_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(data, &data_[0], PACKET_SIZE);
        return PACKET_SIZE;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < PACKET_SIZE)
        {
            return 0;
        }
        if (TIMESTAMP_TYPE_GPS != data[8])
        {
            return 0;
        }
        (void)std::memcpy(&data_[0], data, PACKET_SIZE);
        return PACKET_SIZE;
    }

public:
    static constexpr uint32_t CAPACITY = Capacity;

private:
    static constexpr uint8_t  VERSION            = 5u;
    static constexpr uint32_t HEAD_SIZE          = 18u;
    static constexpr uint32_t PACKET_SIZE        = HEAD_SIZE + PointType::SIZE * Capacity;
    static constexpr uint8_t  TIMESTAMP_TYPE_GPS = 3;

private:
    uint8_t data_[PACKET_SIZE];
};
class LivoxCmdPacket : public FormatBase
{
public:
    uint8_t StartByte() const noexcept
    {
        return data_[0];
    }

    uint8_t Version() const noexcept
    {
        return data_[1];
    }

    uint16_t Length() const noexcept
    {
        return (static_cast<uint16_t>(data_[3]) << 8) | data_[2];
    }

    uint8_t CmdType() const noexcept
    {
        return data_[4];
    }

    uint16_t SeqNum() const noexcept
    {
        return (static_cast<uint16_t>(data_[6]) << 8) | data_[5];
    }

    uint16_t Crc16() const noexcept
    {
        return (static_cast<uint16_t>(data_[8]) << 8) | data_[7];
    }

    uint8_t CmdSet() const noexcept
    {
        return data_[9];
    }

    uint8_t CmdId() const noexcept
    {
        return data_[10];
    }

    uint8_t RetCode() const noexcept
    {
        return data_[11];
    }

    const uint8_t* CmdData() const noexcept
    {
        return &data_[9];
    }

    uint32_t Crc32() const noexcept
    {
        return (static_cast<uint32_t>(data_[data_size_ - 1]) << 24) |
               (static_cast<uint32_t>(data_[data_size_ - 2]) << 16) |
               (static_cast<uint32_t>(data_[data_size_ - 3]) << 8) | static_cast<uint32_t>(data_[data_size_ - 4]);
    }

    uint32_t GetSerializedSize() const noexcept
    {
        return static_cast<uint32_t>(Length());
    }

    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < static_cast<uint32_t>(Length()) || (0 == static_cast<uint32_t>(Length())))
        {
            LOG(ERROR) << "LivoxCmdPackage Serialize error：buffer too small (" << bytes << " | " << Length() << ")";
            return 0;
        }
        (void)std::memcpy(data, &data_[0], static_cast<uint32_t>(Length()));
        return static_cast<uint32_t>(Length());
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes > LIVOX_MAX_FRAME_LENGTH)
        {
            return 0;
        }
        (void)std::memcpy(&data_[0], data, bytes);
        data_size_ = bytes;
        return bytes;
    }

    bool_t Valid() const noexcept
    {
        return (data_size_ == Length()) && (0xAA == StartByte()) &&
               (CalcCRC16(data_, 7, LIVOX_INIT_CRC16) == Crc16()) &&
               (CalcCRC32(data_, GetSerializedSize() - 4, LIVOX_INIT_CRC32) == Crc32());
    }

private:
    static constexpr uint16_t LIVOX_MAX_FRAME_LENGTH = 1400U;

private:
    uint32_t data_size_;
    uint8_t  data_[LIVOX_MAX_FRAME_LENGTH];
};

/* livox hap */
template <uint32_t Capacity, typename PointType = LivoxPoint>
class LivoxHapPacket : public FormatBase
{
public:
    enum TimeSyncType : uint8_t
    {
        NONE = 0x00,
        GPTP = 0x01
    };

public:
    LivoxHapPacket() noexcept
    {
        (void)std::memset(&data_[0], 0, sizeof(data_));
    }

    uint8_t Version() const noexcept
    {
        return data_[0];
    }

    uint8_t SlotId() const noexcept
    {
        return data_[1];
    }

    uint16_t Length() const noexcept
    {
        return (static_cast<uint16_t>(data_[3]) << 8) | data_[2];
    }

    uint16_t TimeInterval() const noexcept
    {
        return (static_cast<uint16_t>(data_[5]) << 8) | static_cast<uint16_t>(data_[4]);
    }

    uint16_t FrameCounter() const noexcept
    {
        return (static_cast<uint16_t>(data_[7]) << 8) | static_cast<uint16_t>(data_[6]);
    }

    uint8_t DataType() const noexcept
    {
        return data_[8];
    }

    TimeSyncType TimestampType() const noexcept
    {
        return static_cast<TimeSyncType>(data_[9]);
    }

    /* reserved (10-15) */

    uint32_t Size() const noexcept
    {
        return Capacity;
    }

    Timestamp GetTimestamp() const noexcept
    {
        /* 16 - 24 */
        uint64_t nsec = (static_cast<uint64_t>(data_[23]) << 56) | (static_cast<uint64_t>(data_[22]) << 48) |
                        (static_cast<uint64_t>(data_[21]) << 40) | (static_cast<uint64_t>(data_[20]) << 32) |
                        (static_cast<uint64_t>(data_[19]) << 24) | (static_cast<uint64_t>(data_[18]) << 16) |
                        (static_cast<uint64_t>(data_[17]) << 8) | data_[16];
        return Timestamp(nsec);
    }

    void SetTimestamp(const Timestamp& timestamp)
    {
        uint64_t nsec = timestamp.ToNsec();
        data_[16]     = (nsec)&0xFF;
        data_[17]     = (nsec >> 8) & 0xFF;
        data_[18]     = (nsec >> 16) & 0xFF;
        data_[19]     = (nsec >> 24) & 0xFF;
        data_[20]     = (nsec >> 32) & 0xFF;
        data_[21]     = (nsec >> 40) & 0xFF;
        data_[22]     = (nsec >> 48) & 0xFF;
        data_[23]     = (nsec >> 56) & 0xFF;
    }

    const PointType* Point(size_t index) const noexcept
    {
        return reinterpret_cast<const PointType*>(data_ + HEAD_SIZE + index * PointType::SIZE);
    }

    bool_t Valid() const noexcept
    {
        return VERSION == Version();
    }

    uint32_t GetSerializedSize() const noexcept
    {
        return PACKET_SIZE;
    }

    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < PACKET_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(data, &data_[0], PACKET_SIZE);
        return PACKET_SIZE;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < PACKET_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(&data_[0], data, PACKET_SIZE);
        return PACKET_SIZE;
    }

public:
    static constexpr uint32_t CAPACITY = Capacity;

private:
    static constexpr uint8_t  VERSION     = 6u;
    static constexpr uint32_t HEAD_SIZE   = 24u;
    static constexpr uint32_t PACKET_SIZE = HEAD_SIZE + PointType::SIZE * Capacity;

private:
    uint8_t data_[PACKET_SIZE];
};
class LivoxHapCmdPacket : public FormatBase
{
public:
    uint8_t StartByte() const noexcept
    {
        return data_[0];
    }

    uint8_t Version() const noexcept
    {
        return data_[1];
    }

    uint16_t Length() const noexcept
    {
        return (static_cast<uint16_t>(data_[3]) << 8) | data_[2];
    }

    uint16_t CmdType() const noexcept
    {
        return (static_cast<uint16_t>(data_[5]) << 8) | data_[4];
    }

    uint16_t CmdId() const noexcept
    {
        return (static_cast<uint16_t>(data_[7]) << 8) | data_[6];
    }

    uint16_t SeqNum() const noexcept
    {
        return (static_cast<uint16_t>(data_[9]) << 8) | data_[8];
    }

    uint16_t SendId() const noexcept
    {
        return (static_cast<uint16_t>(data_[11]) << 8) | data_[10];
    }

    // 12-13 rsvd

    uint16_t Crc16() const noexcept
    {
        return (static_cast<uint16_t>(data_[15]) << 8) | data_[14];
    }

    const uint8_t* CmdData() const noexcept
    {
        return &data_[16];
    }

    uint32_t Crc32() const noexcept
    {
        return (static_cast<uint32_t>(data_[data_size_ - 1]) << 24) |
               (static_cast<uint32_t>(data_[data_size_ - 2]) << 16) |
               (static_cast<uint32_t>(data_[data_size_ - 3]) << 8) | data_[data_size_ - 4];
    }

    uint32_t GetSerializedSize() const noexcept
    {
        return static_cast<uint32_t>(Length());
    }

    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < static_cast<uint32_t>(Length()) || 0 == static_cast<uint32_t>(Length()))
        {
            LOG(ERROR) << "LivoxCmdPackage Serialize error：buffer too small (" << bytes << " | " << Length() << ")";
            return 0;
        }
        (void)std::memcpy(data, &data_[0], static_cast<uint32_t>(Length()));
        return static_cast<uint32_t>(Length());
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes > LIVOX_MAX_FRAME_LENGTH)
        {
            return 0;
        }
        (void)std::memcpy(&data_[0], data, bytes);
        data_size_ = bytes;
        return bytes;
    }

    bool_t Valid() const noexcept
    {
        return (data_size_ == Length()) && (0xAA == StartByte()) &&
               (CalcCRC16(data_, 7, LIVOX_INIT_CRC16) == Crc16()) &&
               (CalcCRC32(data_, GetSerializedSize() - 4, LIVOX_INIT_CRC32) == Crc32());
    }

private:
    static constexpr uint16_t LIVOX_MAX_FRAME_LENGTH = 1400U;

private:
    uint32_t data_size_;
    uint8_t  data_[LIVOX_MAX_FRAME_LENGTH];
};

/* livox hap request info : only lidar send when lidar run error */
/* LivoxHapLogInfo in LivoxHapCmdPacket CmdData */
class LivoxHapLogInfo : public FormatBase
{
public:
    uint8_t LogType() const noexcept
    {
        return data_[0];
    }
    uint8_t FileIndex() const noexcept
    {
        return data_[1];
    }
    uint8_t Rsvd() const noexcept
    {
        return data_[2];
    }
    uint32_t TransIndex() const noexcept
    {
        return (static_cast<uint32_t>(data_[6]) << 24) | (static_cast<uint32_t>(data_[5]) << 16) |
               (static_cast<uint32_t>(data_[4]) << 8) | data_[3];
    }
    uint16_t LogDataLength() const noexcept
    {
        return (static_cast<uint16_t>(data_[8]) << 8) | data_[7];
    }
    const uint8_t* LogData() const noexcept
    {
        return &data_[9];
    }
    uint32_t GetSerializedSize() const noexcept
    {
        return static_cast<uint32_t>(LogDataLength());
    }
    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < static_cast<uint32_t>(LogDataLength()) || 0 == static_cast<uint32_t>(LogDataLength()))
        {
            LOG(ERROR) << "LivoxCmdPackage Serialize error：buffer too small (" << bytes << " | " << LogDataLength()
                       << ")";
            return 0;
        }
        (void)std::memcpy(data, &data_[0], static_cast<uint32_t>(LogDataLength()));
        return static_cast<uint32_t>(LogDataLength());
    }
    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes > LIVOX_MAX_LOG_DATA_LENGTH)
        {
            return 0;
        }
        (void)std::memcpy(&data_[0], data, bytes);
        data_size_ = bytes;
        return bytes;
    }

private:
    static constexpr uint16_t LIVOX_MAX_LOG_DATA_LENGTH = 1400U;

private:
    uint32_t data_size_;
    uint8_t  data_[LIVOX_MAX_LOG_DATA_LENGTH];
};

}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif
