/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsm1.h
 * @brief define the rsm1 packet structure format class
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021-08-09
 */

#ifndef _HOLO_SENSORS_FORMAT_rsm1_H
#define _HOLO_SENSORS_FORMAT_rsm1_H

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/geometry/angle.h>
#include <holo/os/endian.h>
#include <holo/sensors/format/format.h>

namespace holo
{
namespace sensors
{
namespace format
{
enum class TimeSyncMode
{
    INTERNAL_MODE = 0,
    PPS           = 1,
    PTP           = 2,
};

class Rsm1REAI
{
public:
    Rsm1REAI() noexcept : radius_(0), elevation_(0), azimuth_(), intensity_(0)
    {
    }

public:
    uint16_t GetRadius() const noexcept
    {
        return holo::os::ntoh16(radius_);
    }
    int16_t GetElevation() const noexcept
    {
        return holo::os::ntoh16(elevation_) - 32768;
    }
    int16_t GetAzimuth() const noexcept
    {
        return holo::os::ntoh16(azimuth_) - 32768;
    }
    uint8_t GetIntensity() const noexcept
    {
        return intensity_;
    }

public:
    uint16_t radius_;
    uint16_t elevation_;
    uint16_t azimuth_;
    uint8_t  intensity_;
};

class Rsm1PacketDIFOP : public FormatBase
{
public:
    Rsm1PacketDIFOP() noexcept
    {
        (void)std::memset(data_, 0, sizeof(data_));
    }

    uint32_t Size() const noexcept
    {
        return PACKET_SIZE;
    }

    bool_t IsValid() const noexcept
    {
        if ((data_[0] == 0xa5) && (data_[1] == 0xff) && (data_[2] == 0x00) && (data_[3] == 0x5a) &&
            (data_[4] == 0x11) && (data_[5] == 0x11) && (data_[6] == 0x55) && (data_[7] == 0x55))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    uint8_t FrameRate() const noexcept
    {
        return data_[9];
    }

    uint32_t SourceIP() const noexcept
    {
        uint32_t ret;
        ret = static_cast<uint32_t>(data_[13]) | static_cast<uint32_t>(data_[12]) << 8 |
              static_cast<uint32_t>(data_[11]) << 16 | static_cast<uint32_t>(data_[10]) << 24;

        return ret;
    }

    uint32_t DestinationIP() const noexcept
    {
        uint32_t ret;
        ret = static_cast<uint32_t>(data_[17]) | static_cast<uint32_t>(data_[16]) << 8 |
              static_cast<uint32_t>(data_[15]) << 16 | static_cast<uint32_t>(data_[14]) << 24;

        return ret;
    }

    uint64_t MacAddress() const noexcept
    {
        uint64_t ret;
        ret = static_cast<uint64_t>(data_[23]) | static_cast<uint64_t>(data_[22]) << 8 |
              static_cast<uint64_t>(data_[21]) << 16 | static_cast<uint64_t>(data_[20]) << 24 |
              static_cast<uint64_t>(data_[19]) << 32 | static_cast<uint64_t>(data_[18]) << 40;

        return ret;
    }

    uint16_t Port_MSOP() const noexcept
    {
        uint16_t ret;
        ret = static_cast<uint16_t>(data_[25]) | static_cast<uint16_t>(data_[24]) << 8;

        return ret;
    }

    uint16_t Port_DIFOP() const noexcept
    {
        uint16_t ret;
        ret = static_cast<uint16_t>(data_[27]) | static_cast<uint16_t>(data_[26]) << 8;

        return ret;
    }

    uint64_t VersionPL() const noexcept
    {
        uint64_t ret;
        ret = static_cast<uint64_t>(data_[40]) | static_cast<uint64_t>(data_[39]) << 8 |
              static_cast<uint64_t>(data_[38]) << 16 | static_cast<uint64_t>(data_[37]) << 24 |
              static_cast<uint64_t>(data_[36]) << 32;

        return ret;
    }

    uint64_t VersionPS() const noexcept
    {
        uint64_t ret;
        ret = static_cast<uint64_t>(data_[45]) | static_cast<uint64_t>(data_[44]) << 8 |
              static_cast<uint64_t>(data_[43]) << 16 | static_cast<uint64_t>(data_[42]) << 24 |
              static_cast<uint64_t>(data_[41]) << 32;

        return ret;
    }

    uint64_t SN() const noexcept
    {
        uint64_t ret;
        ret = static_cast<uint64_t>(data_[51]) | static_cast<uint64_t>(data_[50]) << 8 |
              static_cast<uint64_t>(data_[49]) << 16 | static_cast<uint64_t>(data_[48]) << 24 |
              static_cast<uint64_t>(data_[47]) << 32 | static_cast<uint64_t>(data_[46]) << 40;

        return ret;
    }

    uint8_t WaveMode() const noexcept
    {
        return data_[52];
    }

    TimeSyncMode SyncMode() const noexcept
    {
        return static_cast<TimeSyncMode>(data_[53]);
    }

    bool_t SyncStatus() const noexcept
    {
        return (data_[54] == 1);
    }

    holo::common::Timestamp GetTimestamp()
    {
        holo::common::Timestamp time_stamp;
        uint64_t                sec = static_cast<uint64_t>(data_[60]) | (static_cast<uint64_t>(data_[59]) << 8) |
                       (static_cast<uint64_t>(data_[58]) << 16) | (static_cast<uint64_t>(data_[57]) << 24) |
                       (static_cast<uint64_t>(data_[56]) << 32) | (static_cast<uint64_t>(data_[55]) << 40);
        uint32_t usec = static_cast<uint64_t>(data_[64]) | (static_cast<uint64_t>(data_[63]) << 8) |
                        (static_cast<uint64_t>(data_[62]) << 16) | (static_cast<uint64_t>(data_[61]) << 24);

        time_stamp.SetSec(sec);
        time_stamp.SetNsec(usec * 1000);

        return time_stamp;
    }

    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < PACKET_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(data, data_, PACKET_SIZE);
        return PACKET_SIZE;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < PACKET_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(data_, data, PACKET_SIZE);
        return PACKET_SIZE;
    }

private:
    static constexpr uint32_t PACKET_SIZE = 256;
    uint8_t                   data_[PACKET_SIZE];
};

class Rsm1PacketMSOP : public FormatBase
{
public:
    Rsm1PacketMSOP()
    {
        (void)std::memset(data_, 0, sizeof(data_));
    }

    const Rsm1REAI* GetRawPoint(size_t index) const
    {
        uint32_t blk = index / RSM1_POINTS_PER_BLOCK;
        return reinterpret_cast<const Rsm1REAI*>(data_ + RSM1_HEADER_SIZE + blk * RSM1_BLOCK_SIZE + 2 +
                                                 (index % RSM1_POINTS_PER_BLOCK) * RSM1_RAW_POINT_SIZE_PER_BLOCK);
    }

    const uint8_t& operator[](size_t index) const
    {
        return data_[index];
    }

    uint8_t GetData(uint32_t i) const
    {
        return data_[i];
    }

    uint32_t Size() const noexcept
    {
        return PACKET_SIZE;
    }

    bool_t IsValid() const noexcept
    {
        return (PktHeader() == PKT_HEADER);
    }

    uint32_t PktHeader() const noexcept
    {
        uint32_t ret;
        ret = static_cast<uint32_t>(data_[3]) | (static_cast<uint32_t>(data_[2]) << 8) |
              (static_cast<uint32_t>(data_[1]) << 16) | (static_cast<uint32_t>(data_[0]) << 24);

        return ret;
    }

    uint16_t PsnPkt() const noexcept
    {
        return static_cast<uint16_t>(data_[5]) | (static_cast<uint16_t>(data_[4]) << 8);
    }

    uint16_t ProtocolVersion() const noexcept
    {
        return static_cast<uint16_t>(data_[7]) | (static_cast<uint16_t>(data_[6]) << 8);
    }

    uint8_t WaveMode() const noexcept
    {
        return data_[8];
    }

    TimeSyncMode SyncMode() const noexcept
    {
        return static_cast<TimeSyncMode>(data_[9]);
    }

    holo::common::Timestamp GetHeaderTimestamp() const
    {
        holo::common::Timestamp time_stamp;
        uint64_t                sec = static_cast<uint64_t>(data_[15]) | (static_cast<uint64_t>(data_[14]) << 8) |
                       (static_cast<uint64_t>(data_[13]) << 16) | (static_cast<uint64_t>(data_[12]) << 24) |
                       (static_cast<uint64_t>(data_[11]) << 32) | (static_cast<uint64_t>(data_[10]) << 40);
        uint32_t usec = static_cast<uint64_t>(data_[19]) | (static_cast<uint64_t>(data_[18]) << 8) |
                        (static_cast<uint64_t>(data_[17]) << 16) | (static_cast<uint64_t>(data_[16]) << 24);
        time_stamp.SetSec(sec);
        time_stamp.SetNsec(usec * 1000);

        return time_stamp;
    }

    void SetHeaderTimestamp(holo::common::Timestamp stamp) noexcept
    {
        uint32_t sec = stamp.GetSec();
        data_[10] = static_cast<uint8_t>(0);
        data_[11] = static_cast<uint8_t>(0);
        data_[12] = static_cast<uint8_t>(sec >> 24);
        data_[13] = static_cast<uint8_t>(sec >> 16);
        data_[14] = static_cast<uint8_t>(sec >> 8);
        data_[15] = static_cast<uint8_t>(sec >> 0);
        uint32_t nsec = stamp.GetNsec() / 1000;
        data_[16] = static_cast<uint8_t>(nsec >> 24);
        data_[17] = static_cast<uint8_t>(nsec >> 16);
        data_[18] = static_cast<uint8_t>(nsec >> 8);
        data_[19] = static_cast<uint8_t>(nsec >> 0);
    }

    uint8_t LidarType() const noexcept
    {
        return data_[30];
    }

    uint8_t MemsTmp() const noexcept
    {
        return data_[31];
    }

    uint32_t GetSerializedSize() const noexcept
    {
        /* algin for 4 byte, 1210 -> 1212*/
        return PACKET_SIZE + 2;
    }

    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < PACKET_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(data, data_, PACKET_SIZE);
        return PACKET_SIZE;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < PACKET_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(data_, data, PACKET_SIZE);
        return PACKET_SIZE;
    }

private:
    static constexpr uint32_t  PACKET_SIZE                   = 1210;
    static constexpr uint32_t  PKT_HEADER                    = 0x55aa5aa5;
    static constexpr float64_t RADIUS_DEGREE                 = 0.005f;
    static constexpr float64_t ANGLE_DEGREE                  = 0.01f;
    static constexpr uint32_t  RSM1_HEADER_SIZE              = 32;
    static constexpr uint32_t  RSM1_BLOCK_SIZE               = 47;
    static constexpr uint32_t  RSM1_RAW_POINT_SIZE_PER_BLOCK = 9;
    static constexpr uint32_t  RSM1_POINTS_PER_BLOCK         = 5;
    uint8_t                    data_[PACKET_SIZE];
};
}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif