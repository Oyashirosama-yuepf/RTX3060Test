/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ouster_packet.h
 * @brief define the ouster packet structure format class
 * @author yinweigen@holomatic.com
 * @date 2022-01-18
 */

#ifndef _HOLO_SENSORS_FORMAT_OUSTER_PACKET_H
#define _HOLO_SENSORS_FORMAT_OUSTER_PACKET_H

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
class OusterBlock
{
public:
    OusterBlock()
    {
        (void)std::memset(data_, 0, sizeof(data_));
    }

    uint16_t GetFrameid() const noexcept
    {
        return static_cast<uint16_t>((measurement_id_ & 0xffff0000) >> 16);
    }

    uint16_t GetMeasurementid() const noexcept
    {
        return static_cast<uint16_t>((measurement_id_ & 0x0000ffff) >> 0);
    }

    void SetMeasurementid(uint16_t measurementid, uint16_t frameid) noexcept
    {
        measurement_id_ = (static_cast<uint32_t>(measurementid) << 0) + (static_cast<uint32_t>(frameid) << 16);
    }

    uint32_t GetEncodercount() const noexcept
    {
        return encoder_count_;
    }

    void SetEncodercount(uint32_t encodercount) noexcept
    {
        encoder_count_ = encodercount;
    }

    const uint8_t* GetData() const noexcept
    {
        return data_;
    }

    uint8_t* GetData()
    {
        return data_;
    }

    bool Valid() const
    {
        return (packet_status_ == OUSTER_PACKET_STATUS_OK);
    }

    void SetStatus(uint32_t status) noexcept
    {
        if (status == 1)
        {
            packet_status_ = 0xFFFFFFFF;
        }
        else
        {
            packet_status_ = 0x00000000;
        }
    }

    uint32_t GetStatus() const noexcept
    {
        return packet_status_;
    }

    uint64_t GetBlockTimeStamp() const
    {
        uint64_t timestamp_u64 = 0;
        for (size_t i = 8; i > 0; i--)
        {
            timestamp_u64 += (static_cast<uint64_t>(timestamp_[i - 1]) << (i - 1) * 8);
        }
        return timestamp_u64;
    }

    const uint8_t* GetTimestampAdress() const noexcept
    {
        return timestamp_;
    }

    void SetBlockTimeStamp(uint64_t blocktimestamp) noexcept
    {
        uint64_t btime = blocktimestamp;
        for (size_t i = 0; i < 8; i++)
        {
            timestamp_[i] = static_cast<uint8_t>(btime >> (i * 8));
        }
    }

    float32_t Azimuth() const
    {
        float32_t measure = static_cast<float32_t>(GetMeasurementid());
        return (360.0f - measure * OUSTER_ATHIMUTH_FACTOR);
    }

    float32_t Depth(size_t i) const
    {
        uint32_t res;
        (void)std::memcpy(&res, &data_[i * OUSTER_POINT_SIZE], sizeof(uint32_t));
        res &= 0x000fffff;
        return (static_cast<float32_t>(res) * 1e-3);
    }

    uint16_t Intensity(size_t i) const
    {
        uint16_t res;
        (void)std::memcpy(&res, &data_[i * OUSTER_POINT_SIZE + 4], sizeof(uint16_t));
        return res;
    }

    uint16_t SignalPhotons(size_t i) const
    {
        uint16_t res;
        (void)std::memcpy(&res, &data_[i * OUSTER_POINT_SIZE + 6], sizeof(uint16_t));
        return res;
    }

    uint16_t NoisePhotons(size_t i) const
    {
        uint16_t res;
        (void)std::memcpy(&res, &data_[i * OUSTER_POINT_SIZE + 8], sizeof(uint16_t));
        return res;
    }

private:
    static constexpr uint16_t  OUSTER_EAMS_NUM             = 128; /*OS-128*/
    static constexpr uint16_t  OUSTER_POINT_SIZE           = 12u;
    static constexpr uint16_t  OUSTER_BLOCK_DATA_BYTE_SIZE = OUSTER_EAMS_NUM * OUSTER_POINT_SIZE;
    static constexpr uint32_t  OUSTER_PACKET_STATUS_OK     = 0xFFFFFFFF;
    static constexpr uint32_t  OUSTER_MAX_ENCODER_COUNT    = 90112;
    static constexpr uint32_t  OUSTER_SCAN_WIDTH           = 1024;
    static constexpr float32_t OUSTER_ATHIMUTH_FACTOR      = 360.0f / OUSTER_SCAN_WIDTH;

private:
    uint8_t  timestamp_[8];
    uint32_t measurement_id_;
    uint32_t encoder_count_;
    uint8_t  data_[OUSTER_BLOCK_DATA_BYTE_SIZE];
    uint32_t packet_status_;
};

class OusterPacket
{
public:
    const OusterBlock& Block(size_t i) const
    {
        return blocks_[i];
    }

    OusterBlock& Block(size_t i)
    {
        return blocks_[i];
    }

    uint64_t GetBlockTimeStamp() const
    {
        uint64_t timestamp_u64 = blocks_[0].GetBlockTimeStamp();
        return timestamp_u64;
    }

    uint32_t GetSerializedSize() const noexcept
    {
        return OUSTER_PACKET_BYTE_SIZE;
    }

    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < OUSTER_PACKET_BYTE_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(data, this, OUSTER_PACKET_BYTE_SIZE);
        return OUSTER_PACKET_BYTE_SIZE;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < OUSTER_PACKET_BYTE_SIZE)
        {
            LOG(ERROR) << "bytes < OUSTER_PACKET_BYTE_SIZE";
            return 0;
        }
        (void)std::memcpy(this, data, OUSTER_PACKET_BYTE_SIZE);
        return OUSTER_PACKET_BYTE_SIZE;
    }

private:
    static constexpr uint16_t OUSTER_BLOCKS_PER_PACKET = 16;
    static constexpr uint32_t OUSTER_PACKET_BYTE_SIZE  = 24896; /*OS-128*/

private:
    OusterBlock blocks_[OUSTER_BLOCKS_PER_PACKET];
};

class OusterImuPacket : public FormatBase
{
public:
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
        (void)std::memcpy(data, &start_read_time_, PACKET_SIZE);
        return PACKET_SIZE;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < PACKET_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(&start_read_time_, data, PACKET_SIZE);
        return PACKET_SIZE;
    }

private:
    static constexpr uint32_t PACKET_SIZE = 64u;

private:
    uint64_t  start_read_time_;
    uint64_t  accel_read_time_;
    uint64_t  gyro_read_time_;
    float32_t accel_x_;
    float32_t accel_y_;
    float32_t accel_z_;
    float32_t angle_rate_x_;
    float32_t angle_rate_y_;
    float32_t angel_rate_z_;
};

}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif
