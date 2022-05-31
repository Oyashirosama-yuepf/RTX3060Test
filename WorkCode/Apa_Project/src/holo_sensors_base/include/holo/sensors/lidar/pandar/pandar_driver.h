/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pandar_driver.h
 * @brief This header file define the function of pandar driver
 * @author guoguangchao@holomatic.com
 * @date 2021-03-15
 */

#ifndef _HOLO_SENSORS_PANDAR_DRIVER_H
#define _HOLO_SENSORS_PANDAR_DRIVER_H

#include <fcntl.h>
#include <stdio.h>
#include <mutex>

#include <holo/sensors/lidar/pandar/pandar_structure.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace pandar
{
class PandarDriver
{
public:
    // callback if Pandar scan
    using ScanCallback = std::function<void(const PandarScan&)>;

    PandarDriver(uint32_t packet_rate, uint32_t scan_rate, uint32_t rpm, uint32_t coord, bool_t use_gps_stamp = false);

    void InstallCallback(const ScanCallback& handler) noexcept
    {
        scan_callback_ = handler;
    }

    void PushPacket(const PandarPacket& data_packet);
    void PushGpsPacket(const PandarGpsPacket& gps_packet);

private:
    const bool_t            use_gps_stamp_;
    bool_t                  synchronized_;
    std::mutex              base_hour_mutex_;
    holo::common::Timestamp base_hour_;
    ScanCallback            scan_callback_;
    uint32_t                packet_per_rotation_;
    PandarScan              scan_;
    const uint32_t          packet_per_scan_;
    const uint32_t          duration_ns_per_scan_;
    int64_t                 time_temp_ns_;
    bool_t                  time_temp_ns_is_useful_;
};

}  // namespace pandar
}  // namespace sensors
}  // namespace holo

#endif
