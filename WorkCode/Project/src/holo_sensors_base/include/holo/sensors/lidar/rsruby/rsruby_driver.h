/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsruby_driver.h
 * @brief This header file defines ruby lidar driver
 * @author wujie(wujie@holomaitc.com)
 * @date 2021/10/22
 */
#ifndef _HOLO_SENSORS_LIDAR_RSRUBY_RSRUBY_DRIVER_H
#define _HOLO_SENSORS_LIDAR_RSRUBY_RSRUBY_DRIVER_H

#include <holo/sensors/lidar/rsruby/rsruby_structure.h>
#include <holo/utils/yaml.h>
#include <vector>

namespace holo
{
namespace sensors
{
namespace rsruby
{
class RsrubyDriver
{
public:
    using ScanCallback = std::function<void(const RsrubyScan&)>;

    RsrubyDriver() = delete;
    RsrubyDriver(uint32_t coord, uint32_t packet_rate, uint32_t scan_rate);

    void PushPacket(const RsrubyPacket& data_packet);
    void InstallScanCallback(const ScanCallback& handler) noexcept;

    size_t GetScanCapacity()
    {
        return scan_.GetCapacity();
    }

private:
    const uint32_t packet_per_scan_;
    const uint32_t duration_ns_per_scan_;
    int64_t        time_temp_ns_;
    bool_t         time_temp_ns_is_useful_;
    RsrubyScan     scan_;
    ScanCallback   scan_callback_;
};

}  // namespace rsruby
}  // namespace sensors
}  // namespace holo

#endif