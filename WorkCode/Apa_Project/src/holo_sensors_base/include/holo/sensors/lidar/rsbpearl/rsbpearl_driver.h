/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsbpearl_driver.h
 * @brief This header file defines rsbpearl lidar driver
 * @author wujie(wujie@holomaitc.com)
 * @date 2022/01/11
 */
#ifndef _HOLO_SENSORS_LIDAR_RSBPEARL_DRIVER_H
#define _HOLO_SENSORS_LIDAR_RSBPEARL_DRIVER_H

#include <holo/sensors/lidar/rsbpearl/rsbpearl_structure.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace rsbpearl
{
class RsbpearlDriver
{
public:
    using ScanCallback = std::function<void(const RsbpearlScan&)>;

    RsbpearlDriver() = default;
    RsbpearlDriver(uint32_t coord, uint32_t packet_rate, uint32_t scan_rate);

    void PushPacket(const RsbpearlPacket& data_packet);
    void InstallScanCallback(const ScanCallback& handler) noexcept;

    void PushDeviceInfoPacket(const RsbpearlPacketDIFOP& info_packet);

    size_t GetScanCapacity()
    {
        return scan_.GetCapacity();
    }

private:
    const uint32_t packet_per_scan_;
    const uint32_t duration_ns_per_scan_;
    int64_t        time_temp_ns_;
    bool_t         time_temp_ns_is_useful_;
    RsbpearlScan   scan_;
    ScanCallback   scan_callback_;
};
}  // namespace rsbpearl
}  // namespace sensors
}  // namespace holo

#endif