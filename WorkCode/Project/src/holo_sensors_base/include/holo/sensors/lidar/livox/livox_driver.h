/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file livox_driver.h
 * @brief This header file defines livox lidar driver
 * @author huzhiyuan(huzhiyuan@holomaitc.com)
 * @date 2020/12/02
 */

#ifndef _HOLO_SENSORS_LIDAR_LIVOX_LIVOX_DRIVER_H
#define _HOLO_SENSORS_LIDAR_LIVOX_LIVOX_DRIVER_H

#include <holo/core/exception.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/format/rawbuf.h>
#include <holo/sensors/lidar/livox/livox_structure.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace livox
{
class LivoxDriverBase
{
public:
    LivoxDriverBase() = default;
    virtual ~LivoxDriverBase() = default;

public:
    void generateHandshakePacket(uint16_t seq, uint8_t* data, uint32_t& len, const std::string& host_ip,
                                 uint16_t data_port, uint16_t cmd_port);
    void generateHeartbeatPacket(uint16_t seq, uint8_t* data, uint32_t& len);
    void generateStartsamplingPacket(uint16_t seq, uint8_t* data, uint32_t& len);
    void generateUpdateUtcPacket(uint16_t seq, uint8_t* data, uint32_t& len, uint32_t s, uint32_t us);
};

template <typename LivoxPacketType>
class LivoxDriver : public LivoxDriverBase
{
public:
    using LivoxScanType = holo::sensors::livox::LivoxScan<LivoxPacketType>;
    using ScanCallback  = std::function<void(const LivoxScanType&)>;

    LivoxDriver(uint32_t coord, uint32_t packet_rate, uint32_t scan_rate);

    void InstallCallback(const ScanCallback& handler) noexcept
    {
        scan_callback_ = handler;
    }

    void PushPacket(const LivoxPacketType& data_packet);

    size_t GetScanCapacity()
    {
        return scan_.GetCapacity();
    }

private:
    const uint32_t packet_per_scan_;
    const uint32_t duration_ns_per_scan_;
    int64_t        time_temp_ns_;
    bool_t         time_temp_ns_is_useful_;
    LivoxScanType  scan_;
    ScanCallback   scan_callback_;
};

}  // namespace livox
}  // namespace sensors
}  // namespace holo

#endif
