/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsruby.h
 * @brief define the rsruby packet structure format class
 * @author wujie<wujie@holomatic.com>
 * @date 2021-10-22
 */

#ifndef _HOLO_SENSORS_FORMAT_RSRUBY_H
#define _HOLO_SENSORS_FORMAT_RSRUBY_H

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
class RsrubyREAI
{
public:
    enum class TimeSyncMode
    {
        PPS = 1,
        PTP = 2,
    };

public:
    RsrubyREAI() noexcept : radius_(0), channel_id_(0), azimuth_(), intensity_(0)
    {
    }
    uint16_t GetRadius() const noexcept
    {
        return holo::os::ntoh16(radius_);
    }
    uint16_t GetChannelId() const noexcept
    {
        return channel_id_;
    }
    uint16_t GetAzimuth() const noexcept
    {
        return holo::os::ntoh16(azimuth_);
    }
    uint8_t GetIntensity() const noexcept
    {
        return intensity_;
    }
    void SetRadius(const uint16_t radius)
    {
        radius_ = radius;
    }
    void SetChannelId(const uint16_t channel_id)
    {
        channel_id_ = channel_id;
    }
    void SetAzimuth(const uint16_t azimuth)
    {
        azimuth_ = azimuth;
    }
    void SetIntensity(const uint8_t intensity)
    {
        intensity_ = intensity;
    }

public:
    uint16_t radius_;     /* Distance */
    uint16_t channel_id_; /* find Vertical angle */
    uint16_t azimuth_;    /* Level angle */
    uint8_t  intensity_;
};

/*
    DIFOP: Device Info Output Protocol.
*/
class RsrubyPacketDIFOP : public FormatBase
{
public:
    RsrubyPacketDIFOP() noexcept
    {
        (void)std::memset(data_, 0, sizeof(data_));
    }

    uint32_t Size() const noexcept
    {
        return PACKET_SIZE;
    }

    bool_t IsValid() const noexcept
    {
        if (0 == std::memcmp(&data_[0], &PKT_HEADER[0], 8))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    uint16_t MotorSpeed() const noexcept
    {
        uint16_t ret;
        ret = static_cast<uint16_t>(data_[9]) | static_cast<uint16_t>(data_[8]) << 8;

        return ret;
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

    uint64_t LocalMacAddress() const noexcept
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

    /* resv: data_[26:27] */

    uint16_t Port_DIFOP() const noexcept
    {
        uint16_t ret;
        ret = static_cast<uint16_t>(data_[29]) | static_cast<uint16_t>(data_[28]) << 8;

        return ret;
    }

    /* resv: data_[30:31] */

    uint16_t FovStartAngle() const noexcept
    {
        uint16_t ret;
        ret = static_cast<uint16_t>(data_[33]) | static_cast<uint16_t>(data_[32]) << 8;

        return ret;
    }

    uint16_t FovEndAngle() const noexcept
    {
        uint16_t ret;
        ret = static_cast<uint16_t>(data_[35]) | static_cast<uint16_t>(data_[34]) << 8;

        return ret;
    }

    /* resv: data_[36:37] */

    uint16_t MotorPhaseLock() const noexcept
    {
        uint16_t ret;
        ret = static_cast<uint16_t>(data_[39]) | static_cast<uint16_t>(data_[38]) << 8;

        return ret;
    }

    uint64_t MotherBoardFirmwareVersion() const noexcept
    {
        uint64_t ret;
        ret = static_cast<uint64_t>(data_[44]) | static_cast<uint64_t>(data_[43]) << 8 |
              static_cast<uint64_t>(data_[42]) << 16 | static_cast<uint64_t>(data_[41]) << 24 |
              static_cast<uint64_t>(data_[40]) << 32;

        return ret;
    }

    uint64_t BottomPlateFirmwareVersion() const noexcept
    {
        uint64_t ret;
        ret = static_cast<uint64_t>(data_[49]) | static_cast<uint64_t>(data_[48]) << 8 |
              static_cast<uint64_t>(data_[47]) << 16 | static_cast<uint64_t>(data_[46]) << 24 |
              static_cast<uint64_t>(data_[45]) << 32;

        return ret;
    }

    uint64_t BottomPlateSoftwareVersion() const noexcept
    {
        uint64_t ret;
        ret = static_cast<uint64_t>(data_[54]) | static_cast<uint64_t>(data_[53]) << 8 |
              static_cast<uint64_t>(data_[52]) << 16 | static_cast<uint64_t>(data_[51]) << 24 |
              static_cast<uint64_t>(data_[50]) << 32;

        return ret;
    }

    uint64_t MotorFirmwareVersion() const noexcept
    {
        uint64_t ret;
        ret = static_cast<uint64_t>(data_[59]) | static_cast<uint64_t>(data_[58]) << 8 |
              static_cast<uint64_t>(data_[57]) << 16 | static_cast<uint64_t>(data_[56]) << 24 |
              static_cast<uint64_t>(data_[55]) << 32;

        return ret;
    }

    uint32_t DeviceHardwareVersion() const noexcept
    {
        uint32_t ret;
        ret = static_cast<uint64_t>(data_[62]) | static_cast<uint64_t>(data_[61]) << 8 |
              static_cast<uint64_t>(data_[60]) << 16;

        return ret;
    }

    /* resv: data_[63:291] */

    uint64_t License() const noexcept
    {
        uint64_t ret;
        ret = static_cast<uint64_t>(data_[297]) | static_cast<uint64_t>(data_[296]) << 8 |
              static_cast<uint64_t>(data_[295]) << 16 | static_cast<uint64_t>(data_[294]) << 24 |
              static_cast<uint64_t>(data_[293]) << 32 | static_cast<uint64_t>(data_[292]) << 40;

        return ret;
    }

    uint16_t ZeroAngleCalibrationValue() const noexcept
    {
        uint16_t ret;
        ret = static_cast<uint16_t>(data_[299]) | static_cast<uint16_t>(data_[298]) << 8;

        return ret;
    }

    uint8_t WaveMode() const noexcept
    {
        return data_[300];
    }

    RsrubyREAI::TimeSyncMode SyncMode() const noexcept
    {
        return static_cast<RsrubyREAI::TimeSyncMode>(data_[301]);
    }

    bool_t SyncStatus() const noexcept
    {
        return (data_[302] == 1);
    }

    holo::common::Timestamp GetTimestamp()
    {
        holo::common::Timestamp time_stamp;
        uint64_t                sec = static_cast<uint64_t>(data_[308]) | (static_cast<uint64_t>(data_[307]) << 8) |
                       (static_cast<uint64_t>(data_[306]) << 16) | (static_cast<uint64_t>(data_[305]) << 24) |
                       (static_cast<uint64_t>(data_[304]) << 32) | (static_cast<uint64_t>(data_[303]) << 40);

        uint32_t usec = static_cast<uint64_t>(data_[312]) | (static_cast<uint64_t>(data_[311]) << 8) |
                        (static_cast<uint64_t>(data_[310]) << 16) | (static_cast<uint64_t>(data_[309]) << 24);

        time_stamp.SetSec(sec);
        time_stamp.SetNsec(usec * 1000);

        return time_stamp;
    }

    /* other field */

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
    static constexpr uint32_t PACKET_SIZE   = 1248;
    static constexpr uint8_t  PKT_HEADER[8] = {0xA5, 0xFF, 0x00, 0x5A, 0x11, 0x11, 0x55, 0x55};
    uint8_t                   data_[PACKET_SIZE];
};

/*
    MSOP: Main data Stream Output Protocol
*/
class RsrubyPacketMSOP : public FormatBase
{
public:
    RsrubyPacketMSOP()
    {
        (void)std::memset(data_, 0, sizeof(data_));
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

    /* data[4-6] : Resv */

    uint8_t WaveMode() const noexcept
    {
        return data_[7];
    }

    uint16_t Temperature() const noexcept
    {
        return static_cast<uint16_t>(data_[9]) | (static_cast<uint16_t>(data_[8]) << 8);
    }

    holo::common::Timestamp GetHeaderTimestamp() const
    {
        holo::common::Timestamp time_stamp;
        uint64_t                sec = static_cast<uint64_t>(data_[15]) | (static_cast<uint64_t>(data_[14]) << 8) |
                       (static_cast<uint64_t>(data_[13]) << 16) | (static_cast<uint64_t>(data_[12]) << 24) |
                       (static_cast<uint64_t>(data_[11]) << 32) | (static_cast<uint64_t>(data_[10]) << 40);
        uint32_t nsec = static_cast<uint64_t>(data_[19]) | (static_cast<uint64_t>(data_[18]) << 8) |
                        (static_cast<uint64_t>(data_[17]) << 16) | (static_cast<uint64_t>(data_[16]) << 24);
        time_stamp.SetSec(sec);
        time_stamp.SetNsec(nsec * 1000);

        return time_stamp;
    }

    /* data[20-80] : Resv */

    void GetRawPoint(size_t index, RsrubyREAI& point) const
    {
        uint32_t       block_id     = index / RSRUBY_POINTS_PER_BLOCK;
        uint16_t       channel_id   = index % RSRUBY_POINTS_PER_BLOCK;
        const uint8_t* cur_blk_addr = data_ + RSRUBY_HEADER_SIZE + block_id * RSRUBY_BLOCK_SIZE;
        uint16_t       azimuth      = *(reinterpret_cast<const uint16_t*>(cur_blk_addr + 2));
        // uint8_t  ret_id  = *(cur_blk_addr + 1);

        point.SetChannelId(channel_id);
        point.SetAzimuth(azimuth);
        point.SetRadius(
            *(reinterpret_cast<const uint16_t*>(cur_blk_addr + 4 + channel_id * RSRUBY_RAW_POINT_SIZE_PER_BLOCK)));
        point.SetIntensity(*(cur_blk_addr + 4 + channel_id * RSRUBY_RAW_POINT_SIZE_PER_BLOCK + 2));
    }

    uint32_t CheckSum() const noexcept
    {
        return static_cast<uint32_t>(data_[PACKET_SIZE - 1]) | (static_cast<uint32_t>(data_[PACKET_SIZE - 2]) << 8) |
               (static_cast<uint32_t>(data_[PACKET_SIZE - 3]) << 16) |
               (static_cast<uint32_t>(data_[PACKET_SIZE - 4]) << 24);
    }

    uint32_t GetSerializedSize() const noexcept
    {
        /* algin for 4 byte, 1248 */
        return PACKET_SIZE;
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
    static constexpr uint32_t  PACKET_SIZE                     = 1248;
    static constexpr uint32_t  PKT_HEADER                      = 0x55aa055a;
    static constexpr float64_t DISTANCE_DEGREE                 = 0.005f; /* Distance:       0.5cm */
    static constexpr float64_t ANGLE_DEGREE                    = 0.01f;  /* Azimuth Angel:  0.01° */
    static constexpr uint32_t  RSRUBY_HEADER_SIZE              = 80;
    static constexpr uint32_t  RSRUBY_BLOCK_SIZE               = 388;
    static constexpr uint32_t  RSRUBY_RAW_POINT_SIZE_PER_BLOCK = 3;
    static constexpr uint32_t  RSRUBY_POINTS_PER_BLOCK         = 128;
    uint8_t                    data_[PACKET_SIZE];
};
}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif