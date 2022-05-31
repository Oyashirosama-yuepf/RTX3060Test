/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file livox_hap_driver.h
 * @brief This header file defines livox hap lidar driver
 * @author wujie(wujie@holomaitc.com)
 * @date 2020/08/18
 */

#ifndef _HOLO_SENSORS_LIDAR_LIVOX_HAP_DRIVER_H
#define _HOLO_SENSORS_LIDAR_LIVOX_HAP_DRIVER_H

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
/* Livox hap driver class */
class LivoxHapDriverBase
{
public:
    LivoxHapDriverBase() = default;
    virtual ~LivoxHapDriverBase() = default;

public:
    /* Broadcast descovery lidar */
    void generateBroadcastDiscoveryPacket(uint16_t seq, uint8_t* data, uint32_t& len);
    /* lidar work control */
    void generateWorkControlPacket(uint16_t seq, uint8_t* data, uint32_t& len, const LivoxHapControlInfo& info);
};

template <typename LivoxPacketType>
class LivoxHapDriver : public LivoxHapDriverBase
{
public:
    using LivoxScanType = holo::sensors::livox::LivoxScan<LivoxPacketType>;
    using ScanCallback  = std::function<void(const LivoxScanType&)>;

    LivoxHapDriver(uint32_t coord, uint32_t packet_rate, uint32_t scan_rate);

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
