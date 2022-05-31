/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pandar128.h
 * @brief define the pandar128 packet structure format class
 * @author wujie<wujie@holomatic.com>
 * @date 2021-12-28
 */

#ifndef _HOLO_SENSORS_FORMAT_PANDAR128_PACKET_H
#define _HOLO_SENSORS_FORMAT_PANDAR128_PACKET_H

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
struct Pandar128MSOPPacketHeader
{
public:
    Pandar128MSOPPacketHeader() : start{}, major_version(), minor_version(), reserved{}
    {
    }
    ~Pandar128MSOPPacketHeader() noexcept
    {
    }

public:
    uint8_t start[2];
    uint8_t major_version;
    uint8_t minor_version;
    uint8_t reserved[2];
};

struct Pandar128MSOPDataHeader
{
public:
    Pandar128MSOPDataHeader() : laser_num(), block_num(), first_block_return(), dis_unit(), return_num(), flags()
    {
    }
    ~Pandar128MSOPDataHeader() noexcept
    {
    }

public:
    uint8_t laser_num;
    uint8_t block_num;
    uint8_t first_block_return; /* reserved */
    uint8_t dis_unit;
    uint8_t return_num;
    uint8_t flags;
};

class Pandar128Block
{
public:
    Pandar128Block() : data_{}
    {
    }

    uint16_t Azimuth() const noexcept
    {
        uint16_t azimuth = data_[0] | static_cast<uint32_t>(data_[1]) << 8;
        return azimuth;
    }

    uint16_t Depth(size_t i) const noexcept
    {
        return data_[i * 3 + 2] + (static_cast<uint32_t>(data_[i * 3 + 3]) << 8);
    }

    uint8_t Intensity(size_t i) const noexcept
    {
        return data_[i * 3 + 4];
    }

private:
    static constexpr uint16_t LASER_NUM  = 128u;
    static constexpr uint16_t POINT_SIZE = 3u;

public:
    static constexpr uint16_t BLOCK_DATA_SIZE = LASER_NUM * POINT_SIZE + 2;

private:
    uint8_t data_[BLOCK_DATA_SIZE];
};

struct Pandar128MSOPFunctionalSafety
{
public:
    Pandar128MSOPFunctionalSafety()
      : fs_version(), lidar_state(), total_fault_code_num(), fault_code{}, reserved{}, crc32{}
    {
    }
    ~Pandar128MSOPFunctionalSafety() noexcept
    {
    }

public:
    uint8_t fs_version;
    uint8_t lidar_state;
    uint8_t total_fault_code_num;
    uint8_t fault_code[2];
    uint8_t reserved[8];
    uint8_t crc32[4];
};

struct Pandar128MSOPDataTail
{
public:
    Pandar128MSOPDataTail()
      : reserved{}
      , azimuth_flag{}
      , operational_state()
      , return_mode()
      , motor_speed{}
      , timestamp{}
      , factory_info()
      , udp_sequence{}
      , imu_temperature{}
      , imu_acceleration_unit{}
      , imu_angular_velocity_unit{}
      , imu_timestamp{}
      , imu_axis_acceleration{}
      , imu_axis_angular_velocity{}
      , crc32{}
    {
    }
    ~Pandar128MSOPDataTail() noexcept
    {
    }

public:
    uint8_t reserved[9];
    uint8_t azimuth_flag[2];
    uint8_t operational_state;
    uint8_t return_mode;
    uint8_t motor_speed[2];
    uint8_t timestamp[10];
    uint8_t factory_info;
    uint8_t udp_sequence[4];
    uint8_t imu_temperature[2];
    uint8_t imu_acceleration_unit[2];
    uint8_t imu_angular_velocity_unit[2];
    uint8_t imu_timestamp[4];
    uint8_t imu_axis_acceleration[6];     /* x y z */
    uint8_t imu_axis_angular_velocity[6]; /* x y z */
    uint8_t crc32[4];
};

class Pandar128Packet : public FormatBase
{
public:
    enum LidarStateType : uint8_t
    {
        INITIALIZATION                      = 0x00,
        NORMAL_OPERATION                    = 0x01,
        EARLY_WARNING                       = 0x02,
        PRELIMINARY_PERFORMANCE_DEGRADATION = 0x03,
        PARTIAL_PERFORMANCE_LOSS            = 0x04,
        READY_SHUTDOWN                      = 0x05,
        DIRECT_SHUTDOWN                     = 0x06
    };

    enum FaultCodeType : uint8_t
    {
        CURRENT_FAULT    = 0x01,
        HISTORICAL_FAULT = 0x02
    };

    enum OperationalStateType : uint8_t
    {
        HIGH_PERFORMANCE    = 0x00,
        STANDBY             = 0x01,
        STANDARD            = 0x02,
        ENERGY_CONSERVATION = 0x03
    };

    enum ReturnModeType : uint8_t
    {
        FIRST           = 0x33,
        STRONGEST       = 0x37,
        LAST            = 0x38,
        LAST_STRONGEST  = 0x39,
        LAST_FIRST      = 0x3B,
        FIRST_STRONGEST = 0x3C
    };

public:
    Pandar128Packet() noexcept : crc32_{}, signature_{}
    {
    }

    /* packet header */
    bool Valid() const noexcept
    {
        uint16_t ret = packet_header_.start[1] | static_cast<uint32_t>(packet_header_.start[0]) << 8;
        return ret == PANDAR128_HEADER;
    }

    uint8_t MajorProtocolVersion() const noexcept
    {
        return packet_header_.major_version;
    }

    uint8_t MinorProtocolVersion() const noexcept
    {
        return packet_header_.minor_version;
    }

    /* data header */
    bool ConfidenceFlag() const noexcept
    {
        return data_header_.flags & 0x10;
    }

    bool DigitalSignatureFlag() const noexcept
    {
        return data_header_.flags & 0x08;
    }

    bool Pandar128MSOPFunctionalSafetyFlag() const noexcept
    {
        return data_header_.flags & 0x04;
    }

    bool ImuInformationFlag() const noexcept
    {
        return data_header_.flags & 0x02;
    }

    bool UdpSequenceFlag() const noexcept
    {
        return data_header_.flags & 0x01;
    }

    /* data body */
    const Pandar128Block& Block(size_t i) const noexcept
    {
        return block_[i];
    }

    uint32_t Crc32() const noexcept
    {
        uint32_t ret = static_cast<uint32_t>(crc32_[0]) | static_cast<uint32_t>(crc32_[1]) << 8 |
                       static_cast<uint32_t>(crc32_[2]) << 16 | static_cast<uint32_t>(crc32_[3]) << 24;

        return ret;
    }

    /* function safety */
    uint8_t FsVersion() const noexcept
    {
        return functional_safety.fs_version;
    }

    uint16_t LidarState() const noexcept
    {
        return static_cast<uint16_t>(functional_safety.lidar_state) >> 5;
    }

    uint16_t GetFaultCodeType() const noexcept
    {
        return (static_cast<uint16_t>(functional_safety.lidar_state) & 0x1F) >> 3;
    }

    uint8_t RollingCounter() const noexcept
    {
        return static_cast<uint16_t>(functional_safety.lidar_state) & 0x07;
    }

    uint16_t TotalFaultCodeNum() const noexcept
    {
        return static_cast<uint16_t>(functional_safety.total_fault_code_num) >> 4;
    }

    uint8_t FaultCodeId() const noexcept
    {
        return static_cast<uint16_t>(functional_safety.total_fault_code_num) & 0x0F;
    }

    uint16_t FaultCode() const noexcept
    {
        uint16_t ret;
        ret = static_cast<uint16_t>(functional_safety.fault_code[0]) |
              static_cast<uint32_t>(functional_safety.fault_code[1]) << 8;

        return ret;
    }

    uint32_t Pandar128MSOPFunctionalSafetyCrc32() const noexcept
    {
        uint32_t ret;
        ret = static_cast<uint32_t>(functional_safety.crc32[0]) |
              static_cast<uint32_t>(functional_safety.crc32[1]) << 8 |
              static_cast<uint32_t>(functional_safety.crc32[2]) << 16 |
              static_cast<uint32_t>(functional_safety.crc32[3]) << 24;

        return ret;
    }

    /* data tail */
    uint16_t AzimuthFlag(size_t i) const noexcept
    {
        uint16_t ret;
        ret = data_tail_.azimuth_flag[0] | (static_cast<uint32_t>(data_tail_.azimuth_flag[1]) << 8);
        if (i == 0)
        {
            return ret >> 14;
        }
        if (i == 1)
        {
            return ret & 0x3FFF >> 12;
        }
        return -1;
    }

    OperationalStateType OperationalState() const noexcept
    {
        return static_cast<OperationalStateType>(data_tail_.operational_state);
    }

    uint8_t ReturnMode() const noexcept
    {
        return data_tail_.return_mode;
    }

    uint16_t MotorSpeed() const noexcept
    {
        uint16_t ret;
        ret = data_tail_.motor_speed[0] | static_cast<uint32_t>(data_tail_.motor_speed[1]) << 8;
        return ret;
    }

    holo::common::Timestamp TimeStamp() const noexcept
    {
        holo::common::Timestamp time_stamp;
        struct tm               time;
        time.tm_year = data_tail_.timestamp[0];
        time.tm_mon  = data_tail_.timestamp[1] - 1;
        time.tm_mday = data_tail_.timestamp[2];
        time.tm_hour = data_tail_.timestamp[3];
        time.tm_min  = data_tail_.timestamp[4];
        time.tm_sec  = data_tail_.timestamp[5];

        uint32_t usec =
            static_cast<uint32_t>(data_tail_.timestamp[6]) | static_cast<uint32_t>(data_tail_.timestamp[7]) << 8 |
            static_cast<uint32_t>(data_tail_.timestamp[8]) << 16 | static_cast<uint32_t>(data_tail_.timestamp[9]) << 24;
        return Timestamp(uint32_t(timegm(&time)), uint32_t((usec % 1000000) * 1000));
    }

    uint8_t FactoryInfo() const noexcept
    {
        return data_tail_.factory_info;
    }

    uint32_t UdpSequence() const noexcept
    {
        uint32_t ret = static_cast<uint32_t>(data_tail_.udp_sequence[0]) |
                       static_cast<uint32_t>(data_tail_.udp_sequence[1]) << 8 |
                       static_cast<uint32_t>(data_tail_.udp_sequence[2]) << 16 |
                       static_cast<uint32_t>(data_tail_.udp_sequence[3]) << 24;
        return ret;
    }

    int16_t ImuTemperature() const noexcept
    {
        int16_t ret = data_tail_.imu_temperature[0] | static_cast<int16_t>(data_tail_.imu_temperature[1]) << 8;
        return ret;
    }

    uint16_t ImuAccelerationUnit() const noexcept
    {
        uint16_t ret;
        ret = data_tail_.imu_acceleration_unit[0] | static_cast<uint32_t>(data_tail_.imu_acceleration_unit[1]) << 8;
        return ret;
    }

    uint16_t ImuAngularVelocityUnit() const noexcept
    {
        uint16_t ret;
        ret = data_tail_.imu_angular_velocity_unit[0] | static_cast<uint32_t>(data_tail_.imu_angular_velocity_unit[1])
                                                            << 8;
        return ret;
    }

    uint32_t ImuTimestamp() const noexcept
    {
        uint32_t ret = static_cast<uint32_t>(data_tail_.imu_timestamp[0]) |
                       static_cast<uint32_t>(data_tail_.imu_timestamp[1]) << 8 |
                       static_cast<uint32_t>(data_tail_.imu_timestamp[2]) << 16 |
                       static_cast<uint32_t>(data_tail_.imu_timestamp[3]) << 24;
        return ret;
    }

    int16_t ImuXAxisAcceleration() const noexcept
    {
        uint16_t ret = static_cast<uint32_t>(data_tail_.imu_axis_acceleration[0]) |
                       static_cast<uint32_t>(data_tail_.imu_axis_acceleration[1]) << 8;

        return static_cast<int16_t>(ret);
    }

    int16_t ImuYAxisAcceleration() const noexcept
    {
        uint16_t ret = static_cast<uint32_t>(data_tail_.imu_axis_acceleration[2]) |
                       static_cast<uint32_t>(data_tail_.imu_axis_acceleration[3]) << 8;

        return static_cast<int16_t>(ret);
    }

    int16_t ImuZAxisAcceleration() const noexcept
    {
        uint16_t ret = static_cast<uint32_t>(data_tail_.imu_axis_acceleration[4]) |
                       static_cast<uint32_t>(data_tail_.imu_axis_acceleration[5]) << 8;

        return static_cast<int16_t>(ret);
    }

    int16_t ImuXAxisAngularVelocity() const noexcept
    {
        uint16_t ret = static_cast<uint32_t>(data_tail_.imu_axis_angular_velocity[0]) |
                       static_cast<uint32_t>(data_tail_.imu_axis_angular_velocity[1]) << 8;

        return static_cast<int16_t>(ret);
    }

    int16_t ImuYAxisAngularVelocity() const noexcept
    {
        uint16_t ret = static_cast<uint32_t>(data_tail_.imu_axis_angular_velocity[2]) |
                       static_cast<uint32_t>(data_tail_.imu_axis_angular_velocity[3]) << 8;

        return static_cast<int16_t>(ret);
    }

    int16_t ImuZAxisAngularVelocity() const noexcept
    {
        uint16_t ret = static_cast<uint32_t>(data_tail_.imu_axis_angular_velocity[4]) |
                       static_cast<uint32_t>(data_tail_.imu_axis_angular_velocity[5]) << 8;

        return static_cast<int16_t>(ret);
    }

    uint32_t Pandar128MSOPDataTailCrc32() const noexcept
    {
        uint32_t ret = static_cast<uint32_t>(data_tail_.crc32[0]) | static_cast<uint32_t>(data_tail_.crc32[1]) << 8 |
                       static_cast<uint32_t>(data_tail_.crc32[2]) << 16 |
                       static_cast<uint32_t>(data_tail_.crc32[3]) << 24;

        return ret;
    }

    /* network security: HMAC-SHA256 */
    void Signature(uint8_t* signature) const noexcept
    {
        (void)memcpy(signature, &signature_[0], NETWORK_SECURITY_SIZE);
    }

    uint32_t GetSerializedSize() const noexcept
    {
        return PANDAR128_PACKET_SIZE;
    }

    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < PANDAR128_PACKET_SIZE)
        {
            LOG(ERROR) << "Pandar128 Data Packet Serialize Error!";
            return 0;
        }
        (void)std::memcpy(data, &packet_header_, PANDAR128_PACKET_SIZE);
        return PANDAR128_PACKET_SIZE;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < PANDAR128_PACKET_SIZE - NETWORK_SECURITY_SIZE)
        {
            LOG(ERROR) << "Pandar128 Data Packet Deserialize Error!";
            return 0;
        }
        (void)std::memcpy(&packet_header_, data, bytes);
        return bytes;
    }

private:
    static constexpr uint16_t PACKET_HEADER_SIZE     = 6u;
    static constexpr uint16_t DATA_HEADER_SIZE       = 6u;
    static constexpr uint16_t DATA_BODY_SIZE         = 776u;
    static constexpr uint16_t FUNCTIONAL_SAFETY_SIZE = 17u;
    static constexpr uint16_t DATA_TAIL_SIZE         = 56u;
    static constexpr uint16_t NETWORK_SECURITY_SIZE  = 32u; /* optional */
    static constexpr uint32_t PANDAR128_PACKET_SIZE  = PACKET_HEADER_SIZE + DATA_HEADER_SIZE + DATA_BODY_SIZE +
                                                      FUNCTIONAL_SAFETY_SIZE + DATA_TAIL_SIZE + NETWORK_SECURITY_SIZE;
    static constexpr uint16_t PANDAR128_HEADER       = 0xEEFF;
    static constexpr uint16_t PROTOCOL_VERSION_MAJOR = 0x01;
    static constexpr uint16_t PROTOCOL_VERSION_MINOR = 0x04;
    static constexpr uint16_t LASER_MAX_RETURN_NUM   = 2u;
    static constexpr uint16_t BLOCKS_PER_PACKET      = 2u;

private:
    Pandar128MSOPPacketHeader     packet_header_;
    Pandar128MSOPDataHeader       data_header_;
    Pandar128Block                block_[2];
    uint8_t                       crc32_[4];
    Pandar128MSOPFunctionalSafety functional_safety;
    Pandar128MSOPDataTail         data_tail_;
    uint8_t                       signature_[32];
};

class Pandar128GpsPacket : public FormatBase
{
public:
    Pandar128GpsPacket() noexcept
      : header_()
      , date_{}
      , time_{}
      , reserved1_{}
      , gprmc_gpgga_{}
      , reserved2_{}
      , location_valid_()
      , pps_locked_()
      , reserved3_{}
    {
    }

    bool Valid() const noexcept
    {
        return holo::os::ntoh16(header_) == PANDAR128_GPS_HEADER;
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
            if (gprmc_gpgga_[i] == ',')
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
        if (gprmc_gpgga_[valid_index] == 'A')
        {
            struct tm time;
            time.tm_year =
                (gprmc_gpgga_[date_index + 4] - 0x30) * 10 + (gprmc_gpgga_[date_index + 5] - 0x30) + 2000 - 1900;
            time.tm_mon  = (gprmc_gpgga_[date_index + 2] - 0x30) * 10 + (gprmc_gpgga_[date_index + 3] - 0x30) - 1;
            time.tm_mday = (gprmc_gpgga_[date_index + 0] - 0x30) * 10 + (gprmc_gpgga_[date_index + 1] - 0x30);
            time.tm_hour = (gprmc_gpgga_[hour_index + 0] - 0x30) * 10 + (gprmc_gpgga_[hour_index + 1] - 0x30);
            time.tm_min  = 0;
            time.tm_sec  = 0;
            return timegm(&time);
        }
        return 0;
    }

    uint32_t GetSerializedSize() const noexcept
    {
        return GPS_PACKET_SIZE;
    }

    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < GPS_PACKET_SIZE)
        {
            LOG(ERROR) << "Pandar128 GPS Packet Serialize Error!";
            return 0;
        }
        (void)std::memcpy(data, &header_, GPS_PACKET_SIZE);
        return GPS_PACKET_SIZE;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < GPS_PACKET_SIZE)
        {
            LOG(ERROR) << "Pandar128 GPS Packet Deserialize Error!";
            return 0;
        }
        (void)std::memcpy(&header_, data, GPS_PACKET_SIZE);
        return GPS_PACKET_SIZE;
    }

private:
    static constexpr uint16_t PANDAR128_GPS_HEADER = 0xFFEE;
    static constexpr uint32_t GPS_PACKET_SIZE      = 512u;
    static constexpr uint32_t NMEA_SIZE            = 77u;

private:
    uint16_t header_;
    uint8_t  date_[6];
    uint8_t  time_[6];
    uint8_t  reserved1_[4];
    uint8_t  gprmc_gpgga_[84];
    uint8_t  reserved2_[404];
    uint8_t  location_valid_;
    uint8_t  pps_locked_;
    uint8_t  reserved3_[4];
};

}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif
