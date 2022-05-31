/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsbpearl.h
 * @brief define the rsbpearl packet structure format class
 * @author wujie<wujie@holomatic.com>
 * @date 2022-01-10
 */

#ifndef _HOLO_SENSORS_FORMAT_RSBPEARL_H
#define _HOLO_SENSORS_FORMAT_RSBPEARL_H

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
struct RsbpearlBlock
{
public:
    RsbpearlBlock() : header_(), azimuth_(), data_{}
    {
    }

    bool Valid() const
    {
        return holo::os::ntoh16(header_) == RSBPEARL_HEADER;
    }

    uint16_t Azimuth() const
    {
        return holo::os::ntoh16(azimuth_);
    }

    uint16_t Depth(size_t i) const
    {
        uint16_t ret;
        ret = (data_[i * 3 + 1] + (static_cast<uint32_t>(data_[i * 3]) << 8)) - 65535;
        return ret;
    }

    uint32_t Intensity(size_t i) const
    {
        return data_[i * 3 + 2];
    }

private:
    static constexpr uint16_t RSBPEARL_HEADER                = 0xFFEE;
    static constexpr uint16_t RSBPEARL_POINT_SIZE            = 3u;
    static constexpr uint16_t RSBPEARL_BEAMS_NUM             = 32u;
    static constexpr uint16_t RSBPEARL_BLOCK_POINT_DATA_SIZE = RSBPEARL_BEAMS_NUM * RSBPEARL_POINT_SIZE;

private:
    uint16_t header_;
    uint16_t azimuth_;
    uint8_t  data_[RSBPEARL_BLOCK_POINT_DATA_SIZE];
};

class RsbpearlPacketDIFOP : public FormatBase
{
public:
    RsbpearlPacketDIFOP() : data_{}
    {
    }

    uint32_t Size() const noexcept
    {
        return PACKET_SIZE;
    }

    uint64_t PktHeader() const noexcept
    {
        uint64_t ret;
        ret = static_cast<uint64_t>(data_[7]) | (static_cast<uint64_t>(data_[6]) << 8) |
              (static_cast<uint64_t>(data_[5]) << 16) | (static_cast<uint64_t>(data_[4]) << 24) |
              (static_cast<uint64_t>(data_[3]) << 32) | (static_cast<uint64_t>(data_[2]) << 40) |
              (static_cast<uint64_t>(data_[1]) << 48) | (static_cast<uint64_t>(data_[0]) << 56);
        return ret;
    }

    bool_t IsValid() const noexcept
    {
        return PktHeader() == PKT_HEADER;
    }

    uint16_t MotorSpeed() const noexcept
    {
        uint16_t ret;
        ret = data_[9] | static_cast<uint32_t>(data_[8]) << 8;
        return ret;
    }

    /* internet: 10:22 */

    uint32_t FovSettings() const noexcept
    {
        uint32_t ret;
        ret = static_cast<uint32_t>(data_[35]) | static_cast<uint32_t>(data_[34]) << 8 |
              static_cast<uint32_t>(data_[33]) << 16 | static_cast<uint32_t>(data_[32]) << 24;
        return ret;
    }

    /* reserve: 36:37 */

    uint16_t MotorPhaseLock() const noexcept
    {
        uint16_t ret;
        ret = data_[39] | static_cast<uint32_t>(data_[38]) << 8;
        return ret;
    }

    /* Motherboard Firmware */
    uint64_t VersionMF() const noexcept
    {
        uint64_t ret;
        ret = static_cast<uint64_t>(data_[44]) | static_cast<uint64_t>(data_[43]) << 8 |
              static_cast<uint64_t>(data_[42]) << 16 | static_cast<uint64_t>(data_[41]) << 24 |
              static_cast<uint64_t>(data_[40]) << 32;
        return ret;
    }

    /* Backplane Firmware */
    uint64_t VersionBF() const noexcept
    {
        uint64_t ret;
        ret = static_cast<uint64_t>(data_[49]) | static_cast<uint64_t>(data_[48]) << 8 |
              static_cast<uint64_t>(data_[47]) << 16 | static_cast<uint64_t>(data_[46]) << 24 |
              static_cast<uint64_t>(data_[45]) << 32;
        return ret;
    }

    /* reserve: 50:292 */

    uint64_t Sequence() const noexcept
    {
        uint64_t ret;
        ret = static_cast<uint64_t>(data_[297]) | static_cast<uint64_t>(data_[296]) << 8 |
              static_cast<uint64_t>(data_[295]) << 16 | static_cast<uint64_t>(data_[294]) << 24 |
              static_cast<uint64_t>(data_[293]) << 32 | static_cast<uint64_t>(data_[292]) << 40;
        return ret;
    }

    /* Zero angle calibration value */
    uint16_t ZeroAngleCalib() const noexcept
    {
        uint16_t ret;
        ret = data_[299] | static_cast<uint32_t>(data_[298]) << 8;
        return ret;
    }

    uint8_t WaveMode() const noexcept
    {
        return data_[300];
    }

    /* Upper computer driver compatibility information */
    uint16_t UpperInfo() const noexcept
    {
        uint16_t ret;
        ret = data_[302] | static_cast<uint32_t>(data_[301]) << 8;
        return ret;
    }

    holo::common::Timestamp GetTimestamp() const noexcept
    {
        struct tm time;
        time.tm_year  = data_[303] + 2000 - 1900;
        time.tm_mon   = data_[304] - 1;
        time.tm_mday  = data_[305];
        time.tm_hour  = data_[306];
        time.tm_min   = data_[307];
        time.tm_sec   = data_[308];
        uint32_t msec = data_[310] | static_cast<uint32_t>(data_[309]) << 8;
        uint32_t usec = data_[312] | static_cast<uint32_t>(data_[311]) << 8;
        return Timestamp(uint32_t(timegm(&time)), uint32_t(((msec * 1000 + usec) % 1000000) * 1000));
    }

    /* RunStatue -> 313 : 313 + 18 */

    /* Electric Current */
    uint32_t Device_Idata() const noexcept
    {
        uint32_t ret;
        ret = data_[315] | static_cast<uint32_t>(data_[314]) << 8 | static_cast<uint32_t>(data_[313]) << 16;

        if ((ret & 0x800000) == 0)
        {
            ret = ret & 0x7FFFFF;
        }
        else /* -1 */
        {
            ret = (ret & 0x7FFFFF) * -1;
        }
        return ret;
    }

    uint32_t Mainboard_Idata() const noexcept
    {
        uint32_t ret;
        ret = data_[318] | static_cast<uint32_t>(data_[317]) << 8 | static_cast<uint32_t>(data_[316]) << 16;

        if ((ret & 0x800000) == 0)
        {
            ret = ret & 0x7FFFFF;
        }
        else /* -1 */
        {
            ret = (ret & 0x7FFFFF) * -1;
        }
        return ret;
    }

    /* Voltage */
    float32_t Vdata_12V() const noexcept
    {
        uint16_t ret;
        ret = (data_[320] | static_cast<uint32_t>(data_[319]) << 8) & 0x0FFF;
        return ret / 4096 * 2.5f * 12;
    }

    float32_t Vdata_12V_M() const noexcept
    {
        uint16_t ret;
        ret = (data_[322] | static_cast<uint32_t>(data_[321]) << 8) & 0x0FFF;
        return ret / 4096 * 2.5f * 12;
    }

    float32_t Vdata_5V() const noexcept
    {
        uint16_t ret;
        ret = (data_[324] | static_cast<uint32_t>(data_[323]) << 8) & 0x0FFF;
        return ret / 4096 * 2.5f * 4;
    }

    float32_t Vdata_3V3() const noexcept
    {
        uint16_t ret;
        ret = (data_[326] | static_cast<uint32_t>(data_[325]) << 8) & 0x0FFF;
        return ret / 4096 * 2.5f * 2;
    }

    float32_t Vdata_2V5() const noexcept
    {
        uint16_t ret;
        ret = (data_[328] | static_cast<uint32_t>(data_[327]) << 8) & 0x0FFF;
        return ret / 4096 * 2.5f * 2;
    }

    float32_t Vdata_1V2() const noexcept
    {
        uint16_t ret;
        ret = (data_[330] | static_cast<uint32_t>(data_[329]) << 8) & 0x0FFF;
        return ret / 4096 * 2.5f * 2;
    }

    /* reserve: 331:342 */

    /* fault diagnosis: 342 : 382 */
    /*
        @return:
            0: normal
            1: no-normal
    */
    uint8_t EEpromTempDriftValue() const noexcept
    {
        return data_[352];
    }

    float32_t ErrorRate_1bit() const noexcept
    {
        uint16_t ret;
        ret = data_[354] | static_cast<uint32_t>(data_[353]) << 8;
        return ret / 65536 * 0.01f;
    }

    float32_t ErrorRate_2bit() const noexcept
    {
        uint16_t ret;
        ret = data_[356] | static_cast<uint32_t>(data_[355]) << 8;
        return ret / 65536 * 0.01f;
    }

    bool IsValidPPS() const noexcept
    {
        return data_[357] & 0x01;
    }

    bool IsValidGPRMC() const noexcept
    {
        return data_[357] & 0x02;
    }

    bool IsUseUTC() const noexcept
    {
        return data_[357] & 0x04;
    }

    int16_t BottomPlateTemp1() const noexcept
    {
        uint16_t ret, sig;
        ret = data_[359] | static_cast<uint32_t>(data_[358]) << 8;
        sig = ret & 0x8000;
        ret = (ret & 0xFFF8) >> 3;

        if (sig == 1) /* -1 */
        {
            return -1 * ((8192 - ret) / 16);
        }
        else
        {
            return ret / 16;
        }
    }

    int16_t BottomPlateTemp2() const noexcept
    {
        uint16_t ret, sig;
        ret = data_[361] | static_cast<uint32_t>(data_[360]) << 8;
        sig = ret & 0x8000;
        ret = (ret & 0xFFF8) >> 3;

        if (sig == 1) /* -1 */
        {
            return -1 * ((8192 - ret) / 16);
        }
        else
        {
            return ret / 16;
        }
    }

    int16_t TopPlateTemp3() const noexcept
    {
        uint16_t ret, sig;
        ret = data_[363] | static_cast<uint32_t>(data_[362]) << 8;
        sig = ret & 0x8000;
        ret = (ret & 0xFFF8) >> 3;

        if (sig == 1) /* -1 */
        {
            return -1 * ((8192 - ret) / 16);
        }
        else
        {
            return ret / 16;
        }
    }

    int16_t TopPlateTemp4() const noexcept
    {
        uint16_t ret, sig;
        ret = data_[365] | static_cast<uint32_t>(data_[364]) << 8;
        sig = ret & 0x8000;
        ret = (ret & 0xFFF8) >> 3;

        if (sig == 1) /* -1 */
        {
            return -1 * ((8192 - ret) / 16);
        }
        else
        {
            return ret / 16;
        }
    }

    int16_t BottomPlateTemp5() const noexcept
    {
        uint16_t ret, sig;
        ret = data_[367] | static_cast<uint32_t>(data_[366]) << 8;
        sig = ret & 0x0800;
        ret = ret & 0x0FFF;

        if (sig == 1) /* -1 */
        {
            return -1 * (4096 - ret) / 4;
        }
        else
        {
            return ret / 4;
        }
    }

    float32_t RtSpeed() const noexcept
    {
        uint16_t ret;
        ret = data_[374] | static_cast<uint32_t>(data_[373]) << 8;
        return ret / 6;
    }

    /* 382 : 382+86 */
    uint32_t GPRMC() const noexcept
    {
        const uint8_t* gprmc       = &data_[382];
        uint32_t       hour_index  = 0;
        uint32_t       valid_index = 0;
        uint32_t       date_index  = 0;
        uint32_t       comma_index = 0;
        for (uint32_t i = 0; i != NMEA_SIZE; i++)
        {
            if (gprmc[i] == ',')
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
        if (gprmc[valid_index] == 'A')
        {
            struct tm time;
            time.tm_year = (gprmc[date_index + 4] - 0x30) * 10 + (gprmc[date_index + 5] - 0x30) + 2000 - 1900;
            time.tm_mon  = (gprmc[date_index + 2] - 0x30) * 10 + (gprmc[date_index + 3] - 0x30) - 1;
            time.tm_mday = (gprmc[date_index + 0] - 0x30) * 10 + (gprmc[date_index + 1] - 0x30);
            time.tm_hour = (gprmc[hour_index + 0] - 0x30) * 10 + (gprmc[hour_index + 1] - 0x30);
            time.tm_min  = 0;
            time.tm_sec  = 0;
            return timegm(&time);
        }
        return 0;
    }

    void VerticalOffset(float32_t* vertical) const noexcept
    {
        for (int i = 0; i < 32; i++)
        {
            vertical[i] = static_cast<float32_t>(
                ANGLE_DEGREE * (data_[468 + i * 3 + 2] | static_cast<uint32_t>(data_[468 + i * 3 + 1]) << 8));
            if (1 == data_[468 + i * 3]) /* -1 */
            {
                vertical[i] = -1 * vertical[i];
            }
        }
    }

    void HorizontalOffset(float32_t* azimuth) const noexcept
    {
        for (int i = 0; i < 32; i++)
        {
            azimuth[i] = static_cast<float32_t>(
                ANGLE_DEGREE * (data_[564 + i * 3 + 2] | static_cast<uint32_t>(data_[564 + i * 3 + 1]) << 8));
            if (1 == data_[564 + i * 3]) /* -1 */
            {
                azimuth[i] = -1 * azimuth[i];
            }
        }
    }

    /* reserve: 660:586 */

    uint16_t FrameTail() const noexcept
    {
        uint16_t ret;
        ret = data_[1247] | static_cast<uint32_t>(data_[1246]) << 8;
        return ret;
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
    static constexpr uint64_t  PKT_HEADER         = 0xA5FF005A11115555;
    static constexpr uint16_t  PKT_TAIL           = 0x0FF0;
    static constexpr uint32_t  PACKET_SIZE        = 1248;
    static constexpr float64_t ANGLE_DEGREE       = 0.01f;
    static constexpr uint32_t  PACKET_HEADER_SIZE = 8;
    static constexpr uint32_t  PACKET_TAIL_SIZE   = 2;
    static constexpr uint32_t  NMEA_SIZE          = 77u;

    uint8_t data_[PACKET_SIZE];
};

class RsbpearlPacketUCWP : public FormatBase
{
public:
    RsbpearlPacketUCWP() : data_{}
    {
        (void)std::memcpy(&data_[0], &PKT_HEADER, sizeof(uint64_t));
    }

    void SetMotorSpeed(uint16_t motor_speed) noexcept
    {
        (void)std::memcpy(&data_[8], &motor_speed, sizeof(uint16_t));
    }

    void SourceIP(uint32_t source_ip) noexcept
    {
        (void)std::memcpy(&data_[10], &source_ip, sizeof(uint32_t));
    }

    void DestinationIP(uint32_t destination_ip) noexcept
    {
        (void)std::memcpy(&data_[14], &destination_ip, sizeof(uint32_t));
    }

    void MacAddress(uint64_t mac_addr) noexcept
    {
        (void)std::memcpy(&data_[18], &mac_addr, sizeof(uint32_t));
    }

    void Port1_MSOP(uint16_t port1) noexcept
    {
        (void)std::memcpy(&data_[24], &port1, sizeof(uint16_t));
    }

    void Port2_MSOP(uint16_t port2) noexcept
    {
        (void)std::memcpy(&data_[26], &port2, sizeof(uint16_t));
    }

    void Port1_DIFOP(uint16_t port1) noexcept
    {
        (void)std::memcpy(&data_[28], &port1, sizeof(uint16_t));
    }

    void Port2_DIFOP(uint16_t port2) noexcept
    {
        (void)std::memcpy(&data_[30], &port2, sizeof(uint16_t));
    }

    void SetFovStart(uint16_t fov_start) noexcept
    {
        (void)std::memcpy(&data_[32], &fov_start, sizeof(uint16_t));
    }

    void SetFovEnd(uint16_t fov_end) noexcept
    {
        (void)std::memcpy(&data_[34], &fov_end, sizeof(uint16_t));
    }

    void SetTime(uint64_t sec, uint32_t usec) noexcept
    {
        (void)std::memcpy(&data_[36], &sec, sizeof(uint16_t));
        (void)std::memcpy(&data_[42], &usec, sizeof(uint16_t));
    }

    void SetMotorPhaseLock(uint16_t motor_phase_lock) noexcept
    {
        (void)std::memcpy(&data_[46], &motor_phase_lock, sizeof(uint16_t));
    }

private:
    static constexpr uint64_t PKT_HEADER         = 0xAA00FF112222AAAA;
    static constexpr uint32_t PACKET_SIZE        = 48;
    static constexpr uint32_t PACKET_HEADER_SIZE = 8;
    static constexpr uint32_t PACKET_DATA_SIZE   = 40;
    uint8_t                   data_[PACKET_SIZE];
};

class RsbpearlPacketMSOP : public FormatBase
{
public:
    enum ReturnMode : uint8_t
    {
        DoubleEcho    = 0,
        StrongestEcho = 1,
        FinalEcho     = 2,
    };

public:
    RsbpearlPacketMSOP() : header_{}, block_{}, tail_{}
    {
    }

    uint32_t Size() const noexcept
    {
        return PACKET_SIZE;
    }

    bool_t IsValid() const noexcept
    {
        return (PktHeader() == PKT_HEADER) && (PktTail() == PKT_TAIL);
    }

    uint64_t PktHeader() const noexcept
    {
        uint64_t ret;
        ret = static_cast<uint64_t>(header_[7]) | (static_cast<uint64_t>(header_[6]) << 8) |
              (static_cast<uint64_t>(header_[5]) << 16) | (static_cast<uint64_t>(header_[4]) << 24) |
              (static_cast<uint64_t>(header_[3]) << 32) | (static_cast<uint64_t>(header_[2]) << 40) |
              (static_cast<uint64_t>(header_[1]) << 48) | (static_cast<uint64_t>(header_[0]) << 56);
        return ret;
    }

    uint16_t PktTail() const noexcept
    {
        uint16_t ret;
        ret = tail_[5] | static_cast<uint32_t>(tail_[4]) << 8;
        return ret;
    }

    holo::common::Timestamp GetHeaderTimestamp() const
    {
        struct tm time;
        time.tm_year  = header_[20] + 2000 - 1900;
        time.tm_mon   = header_[21] - 1;
        time.tm_mday  = header_[22];
        time.tm_hour  = header_[23];
        time.tm_min   = header_[24];
        time.tm_sec   = header_[25];
        uint32_t msec = header_[27] | static_cast<uint32_t>(header_[26]) << 8;
        uint32_t usec = header_[29] | static_cast<uint32_t>(header_[28]) << 8;
        return Timestamp(uint32_t(timegm(&time)), uint32_t(((msec * 1000 + usec) % 1000000) * 1000));
    }

    const RsbpearlBlock& Block(size_t i) const
    {
        return block_[i];
    }

    uint32_t GetSerializedSize() const noexcept
    {
        return PACKET_SIZE;
    }

    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < PACKET_SIZE)
        {
            LOG(ERROR) << "Rsbpearl MSOP Serialize Error!";
            return 0;
        }
        (void)std::memcpy(data, &header_, PACKET_SIZE);
        return PACKET_SIZE;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < PACKET_SIZE)
        {
            LOG(ERROR) << "Rsbpearl MSOP Deserialize Error!";
            return 0;
        }
        (void)std::memcpy(&header_, data, PACKET_SIZE);
        return PACKET_SIZE;
    }

private:
    static constexpr uint32_t  PACKET_SIZE                       = 1248;
    static constexpr uint64_t  PKT_HEADER                        = 0x55aa050a5aa550a0;
    static constexpr uint64_t  PKT_TAIL                          = 0x00ff;
    static constexpr float64_t RADIUS_DEGREE                     = 0.005f;
    static constexpr float64_t ANGLE_DEGREE                      = 0.01f;
    static constexpr uint32_t  RSBPEARL_HEADER_SIZE              = 42;
    static constexpr uint32_t  RSBPEARL_TAIL_SIZE                = 6;
    static constexpr uint32_t  RSBPEARL_BLOCK_NUMS               = 12;
    static constexpr uint32_t  RSBPEARL_BLOCK_SIZE               = 100;
    static constexpr uint32_t  RSBPEARL_RAW_POINT_SIZE_PER_BLOCK = 3;
    static constexpr uint32_t  RSBPEARL_POINTS_PER_BLOCK         = 32;

private:
    uint8_t       header_[RSBPEARL_HEADER_SIZE];
    RsbpearlBlock block_[RSBPEARL_BLOCK_NUMS];
    uint8_t       tail_[RSBPEARL_TAIL_SIZE];
};
}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif