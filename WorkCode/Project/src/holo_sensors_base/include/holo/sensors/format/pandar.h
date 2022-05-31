/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pandar_packet.h
 * @brief define the pandar packet structure format class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020-11-27
 */

#ifndef _HOLO_SENSORS_FORMAT_PANDAR_PACKET_H
#define _HOLO_SENSORS_FORMAT_PANDAR_PACKET_H

#include <cstring>

#include <holo/os/endian.h>
#include <holo/sensors/format/format.h>
#include <holo_c/core/static_assert.h>

namespace holo
{
namespace sensors
{
namespace format
{
class PandarBlock
{
public:
    PandarBlock() noexcept : header_(), rotation_()
    {
        (void)std::memset(data_, 0, sizeof(data_));
    }

    uint16_t GetHeader() const noexcept
    {
        return header_;
    }

    uint16_t GetRotation() const noexcept
    {
        return rotation_;
    }

    const uint8_t* GetData() const noexcept
    {
        return data_;
    }

    bool Valid() const
    {
        return holo::os::ntoh16(header_) == PANDAR_HEADER;
    }

    float32_t Azimuth() const
    {
        return rotation_ * PANDAR_ROTATION_RESOLUTION;
    }

    float32_t Depth(size_t i) const
    {
        return (data_[i * 3] + (static_cast<uint32_t>(data_[i * 3 + 1]) << 8)) * PANDAR_DEPTH_RESOLUTION;
    }

    uint32_t Intensity(size_t i) const
    {
        return data_[i * 3 + 2];
    }

private:
    static constexpr uint16_t  PANDAR_HEADER               = 0xFFEE;
    static constexpr float32_t PANDAR_ROTATION_RESOLUTION  = 0.01f;
    static constexpr float32_t PANDAR_DEPTH_RESOLUTION     = 0.004f;
    static constexpr uint16_t  PANDAR_POINT_SIZE           = 3u;
    static constexpr uint16_t  PANDAR_BEAMS_NUM            = 40u;
    static constexpr uint16_t  PANDAR_BLOCK_DATA_BYTE_SIZE = PANDAR_BEAMS_NUM * PANDAR_POINT_SIZE;

private:
    uint16_t header_;
    uint16_t rotation_;
    uint8_t  data_[PANDAR_BLOCK_DATA_BYTE_SIZE];
};
HOLO_STATIC_ASSERT(sizeof(PandarBlock) == 124);

class PandarPacket : public FormatBase
{
public:
    PandarPacket() noexcept
      : reserved1_{0, 0, 0, 0, 0}
      , stopped_{0}
      , reserved2_{0, 0}
      , motor_speed_{0}
      , timestamp_low_{0}
      , timestamp_high_{0}
      , return_mode_{0}
      , factory_info_{0}
    {
    }

    const PandarBlock& Block(size_t i) const
    {
        return blocks_[i];
    }

    uint8_t GetStopped() const noexcept
    {
        return stopped_;
    }

    uint16_t GetMotoSpeed() const noexcept
    {
        return motor_speed_;
    }

    uint8_t GetFactoryInfo() const noexcept
    {
        return factory_info_;
    }

    uint8_t GetReturnMode() const noexcept
    {
        return return_mode_;
    }

    uint32_t GetBlockTimeStamp() const
    {
        return (static_cast<uint32_t>(timestamp_high_) << 16) + timestamp_low_;
    }
    void SetBlockTimeStamp(uint32_t timestamp)
    {
        timestamp_high_ = (timestamp & 0xFFFF0000) >> 16;
        timestamp_low_  = (timestamp & 0x0000FFFF);
    }

    uint32_t GetSerializedSize() const noexcept
    {
        return PANDAR_PACKET_BYTE_SIZE;
    }
    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < PANDAR_PACKET_BYTE_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(data, &blocks_, PANDAR_PACKET_BYTE_SIZE);
        return PANDAR_PACKET_BYTE_SIZE;
    }
    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < PANDAR_PACKET_BYTE_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(&blocks_, data, PANDAR_PACKET_BYTE_SIZE);
        return PANDAR_PACKET_BYTE_SIZE;
    }

private:
    static constexpr uint16_t PANDAR_BLOCKS_PER_PACKET = 10;
    static constexpr uint32_t PANDAR_PACKET_BYTE_SIZE  = 1256;

private:
    PandarBlock blocks_[PANDAR_BLOCKS_PER_PACKET];
    uint8_t     reserved1_[5];
    uint8_t     stopped_;
    uint8_t     reserved2_[2];
    uint16_t    motor_speed_;
    uint16_t    timestamp_low_;
    uint16_t    timestamp_high_;
    uint8_t     return_mode_;
    uint8_t     factory_info_;
};

class PandarGpsPacket : public FormatBase
{
public:
    PandarGpsPacket() noexcept : header_(), location_valid_(), pps_locked_()
    {
        (void)std::memset(&header_, 0, PACKET_SIZE);
    }

    bool Valid() const
    {
        return holo::os::ntoh16(header_) == PANDAR_HEADER;
    }

    uint8_t PpsState() const noexcept
    {
        return location_valid_;
    }

    bool_t IsPpsLocked() const noexcept
    {
        return pps_locked_ == 1;
    }

    uint32_t GetTimestamp() const noexcept
    {
        uint32_t hour_index  = 0;
        uint32_t valid_index = 0;
        uint32_t date_index  = 0;
        uint32_t comma_index = 0;
        for (uint32_t i = 0; i != NMEA_SIZE; i++)
        {
            if (gprmc_[i] == ',')
            {
                comma_index++;
                if (comma_index == 1)
                {
                    hour_index = i + 1;
                }
                else if (comma_index == 2)
                {
                    valid_index = i + 1;
                }
                else if (comma_index == 9)
                {
                    date_index = i + 1;
                }
            }
        }
        if (gprmc_[valid_index] == 'A')
        {
            struct tm time;
            time.tm_year = (gprmc_[date_index + 4] - 0x30) * 10 + (gprmc_[date_index + 5] - 0x30) + 2000 - 1900;
            time.tm_mon  = (gprmc_[date_index + 2] - 0x30) * 10 + (gprmc_[date_index + 3] - 0x30) - 1;
            time.tm_mday = (gprmc_[date_index + 0] - 0x30) * 10 + (gprmc_[date_index + 1] - 0x30);
            time.tm_hour = (gprmc_[hour_index + 0] - 0x30) * 10 + (gprmc_[hour_index + 1] - 0x30);
            time.tm_min  = 0;
            time.tm_sec  = 0;
            return timegm(&time);
        }
        return 0;
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
        (void)std::memcpy(data, &header_, PACKET_SIZE);
        return PACKET_SIZE;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < PACKET_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(&header_, data, PACKET_SIZE);
        return PACKET_SIZE;
    }

private:
    static constexpr uint16_t PANDAR_HEADER = 0xFFEE;
    static constexpr uint32_t PACKET_SIZE   = 512u;
    static constexpr uint32_t NMEA_SIZE     = 77u;

private:
    uint16_t header_;
    uint8_t  date_[6];
    uint8_t  time_[6];
    uint8_t  us_time_[4];
    uint8_t  gprmc_[77];
    uint8_t  reserved1_[411];
    uint8_t  location_valid_;
    uint8_t  pps_locked_;
    uint8_t  reserved2_[4];
};

}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif
