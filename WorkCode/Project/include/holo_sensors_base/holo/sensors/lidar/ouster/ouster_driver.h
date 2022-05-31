/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ouster_driver.h
 * @brief This header file define the function of ouster driver
 * @author yinweigen@holomatic.com
 * @date 2022-01-17
 */

#ifndef _HOLO_SENSORS_OUSTER_DRIVER_H
#define _HOLO_SENSORS_OUSTER_DRIVER_H

#include <fcntl.h>
#include <stdio.h>
#include <mutex>

#include <holo/sensors/format/rawbuf.h>
#include <holo/sensors/lidar/ouster/ouster_structure.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace ouster
{
class OusterDriver
{
public:
    using RawbufferType = holo::sensors::format::Rawbuffer<8192>;
    using ScanCallback  = std::function<void(const OusterScan&)>;

    OusterDriver(uint32_t packet_rate, uint32_t scan_rate, uint32_t coord);

    void InstallCallback(const ScanCallback handler) noexcept
    {
        scan_callback_ = handler;
    }

    void PushPacket(const OusterPacket& data_packet);
    void PushImuPacket(const OusterImuPacket& Imu_packet);

private:
    std::mutex              base_hour_mutex_;
    holo::common::Timestamp base_hour_;
    ScanCallback            scan_callback_;
    OusterScan              scan_;
    const uint32_t          packet_per_scan_;
    const uint32_t          duration_ns_per_scan_;
    int64_t                 time_temp_ns_;
    bool_t                  time_temp_ns_is_useful_;
};

}  // namespace ouster
}  // namespace sensors
}  // namespace holo

#endif
