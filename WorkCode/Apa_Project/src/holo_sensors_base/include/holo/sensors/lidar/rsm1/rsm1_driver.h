/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsm1_driver.h
 * @brief This header file defines m1 lidar driver
 * @author zhangtongyang(zhangtongyang@holomaitc.com)
 * @date 2021/8/09
 */
#ifndef _HOLO_SENSORS_LIDAR_RSM1_RSM1_DRIVER_H
#define _HOLO_SENSORS_LIDAR_RSM1_RSM1_DRIVER_H

#include <holo/sensors/lidar/rsm1/rsm1_structure.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace rsm1
{
class Rsm1Driver
{
public:
    using ScanCallback = std::function<void(const Rsm1Scan&)>;

    Rsm1Driver() = default;
    Rsm1Driver(uint32_t coord, uint32_t packet_rate, uint32_t scan_rate);

    void PushPacket(const Rsm1Packet& data_packet);
    void InstallScanCallback(const ScanCallback& handler) noexcept;

    size_t GetScanCapacity()
    {
        return scan_.GetCapacity();
    }

#if defined(MDC_PRODUCTION_MDC610)
    void SetDatalayerTimestamp(bool_t use_datalayer_timestamp) noexcept
    {
        use_datalayer_timestamp_ = use_datalayer_timestamp;
    }
#endif

private:
    const uint32_t packet_per_scan_;
    const uint32_t duration_ns_per_scan_;
    int64_t        time_temp_ns_;
    bool_t         time_temp_ns_is_useful_;
    Rsm1Scan       scan_;
    ScanCallback   scan_callback_;

#if defined(MDC_PRODUCTION_MDC610)
    bool_t                 use_datalayer_timestamp_;
    holo::common::Duration timediff_;
#endif
};
}  // namespace rsm1
}  // namespace sensors
}  // namespace holo

#endif