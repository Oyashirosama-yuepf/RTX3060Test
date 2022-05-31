/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file velodyne_packet.h
 * @brief define the velodyne packet structure format class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020-11-27
 */

#ifndef _HOLO_SENSORS_FORMAT_VELODYNE_PACKET_H
#define _HOLO_SENSORS_FORMAT_VELODYNE_PACKET_H

#include <holo/sensors/format/format.h>
#include <holo_c/core/static_assert.h>

namespace holo
{
namespace sensors
{
namespace format
{
class VelodyneBlock
{
public:
    VelodyneBlock() noexcept : header_(0), rotation_(0)
    {
        (void)std::memset(data_, 0, sizeof(data_));
    }

    bool_t Valid() const noexcept
    {
        return header_ == VLP_HEADER;
    }

    /* azimuth around the z-axis in degree */
    float32_t Azimuth() const noexcept
    {
        return rotation_ * 0.01f;
    }

    /* depth of ith measurement in meter */
    float32_t Depth(size_t i) const
    {
        return (data_[i * 3] + (static_cast<uint32_t>(data_[i * 3 + 1]) << 8)) * 0.002f;
    }

    /* intensity of ith measurement */
    uint8_t Intensity(size_t i) const
    {
        return data_[i * 3 + 2];
    }

private:
    static constexpr uint16_t VLP_HEADER       = 0xeeff;
    static constexpr uint32_t BLOCK_SIZE       = 100u;
    static constexpr uint32_t POINT_SIZE       = 3u;
    static constexpr uint32_t POINTS_PER_BLOCK = 32u;
    static constexpr uint32_t BLOCK_DATA_SIZE  = POINTS_PER_BLOCK * POINT_SIZE;

private:
    uint16_t header_;                 // eeff or ddff
    uint16_t rotation_;               // 0.01 degree
    uint8_t  data_[BLOCK_DATA_SIZE];  // data
};
HOLO_STATIC_ASSERT(sizeof(VelodyneBlock) == 100);

class VelodynePacket : public FormatBase
{
public:
    VelodynePacket() noexcept : timestamp_(0), sensor_type_(0), return_type_(0)
    {
    }

    VelodyneBlock& Block(size_t i)
    {
        return blocks_[i];
    }

    const VelodyneBlock& Block(size_t i) const
    {
        return blocks_[i];
    }

    uint32_t Timestamp() const noexcept
    {
        return timestamp_;
    }

    uint8_t SensorType() const noexcept
    {
        return sensor_type_;
    }

    uint8_t ReturnType() const noexcept
    {
        return return_type_;
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
        (void)std::memcpy(data, &blocks_, PACKET_SIZE);
        return PACKET_SIZE;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < PACKET_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(&blocks_, data, PACKET_SIZE);
        return PACKET_SIZE;
    }

private:
    static constexpr uint32_t BLOCKS_PER_PACKET = 12u;
    static constexpr uint32_t PACKET_SIZE       = 1206u;

private:
    VelodyneBlock blocks_[BLOCKS_PER_PACKET]; /* blocks */
    uint32_t      timestamp_;                 /* time stamp inside hour */
    uint8_t       sensor_type_;               /* sensor type */
    uint8_t       return_type_;               /* return type */
};

class VelodyneGpsPacket : public FormatBase
{
public:
    VelodyneGpsPacket() noexcept : unused0_{0}, pps_state_(0), unused1_{0}, nmea_{0}, unused2_{0}
    {
    }

    uint8_t PpsState() const noexcept
    {
        return pps_state_;
    }

    bool_t IsPpsLocked() const noexcept
    {
        return pps_state_ == 2;
    }

    uint32_t GetTimestamp() const noexcept
    {
        uint32_t hour_index  = 0;
        uint32_t valid_index = 0;
        uint32_t date_index  = 0;
        uint32_t comma_index = 0;
        for (uint32_t i = 0; i != NMEA_SIZE; i++)
        {
            if (nmea_[i] == ',')
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
        if (nmea_[valid_index] == 'A')
        {
            struct tm time;
            time.tm_year = (nmea_[date_index + 4] - 0x30) * 10 + (nmea_[date_index + 5] - 0x30) + 2000 - 1900;
            time.tm_mon  = (nmea_[date_index + 2] - 0x30) * 10 + (nmea_[date_index + 3] - 0x30) - 1;
            time.tm_mday = (nmea_[date_index + 0] - 0x30) * 10 + (nmea_[date_index + 1] - 0x30);
            time.tm_hour = (nmea_[hour_index + 0] - 0x30) * 10 + (nmea_[hour_index + 1] - 0x30);
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
        (void)std::memcpy(data, &unused0_, PACKET_SIZE);
        return PACKET_SIZE;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < PACKET_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(&unused0_, data, PACKET_SIZE);
        return PACKET_SIZE;
    }

private:
    static constexpr uint32_t PACKET_SIZE = 512u;
    static constexpr uint32_t NMEA_SIZE   = 72u;

private:
    uint8_t unused0_[202];    /* unused */
    uint8_t pps_state_;       /* 0: absent, 1: attemp to sync, 2: locked, 3: error */
    uint8_t unused1_[3];      /* unused */
    uint8_t nmea_[NMEA_SIZE]; /* 0: "V" invalid, 1:"A" received, 2: unkonwn */
    uint8_t unused2_[234];    /* unused */
};

}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif
