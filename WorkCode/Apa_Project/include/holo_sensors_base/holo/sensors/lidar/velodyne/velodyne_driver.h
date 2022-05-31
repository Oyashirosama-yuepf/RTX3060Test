/*!
 * \brief
 * \author liwenjun
 * \date 2017-07-05
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice. */

#ifndef _HOLO_SENSORS_VELODYNE_DRIVER_H
#define _HOLO_SENSORS_VELODYNE_DRIVER_H

#include <mutex>
#include <holo/sensors/format/rawbuf.h>
#include <holo/sensors/lidar/velodyne/velodyne_structure.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace velodyne
{
class VelodyneDriver
{
public:
    // callback if velodyne scan
    using ScanCallback = std::function<void(const VelodyneScan&)>;

    VelodyneDriver(uint32_t packet_rate, uint32_t scan_rate, uint32_t rpm, uint32_t coord, bool_t use_gps_stamp = false);

    void InstallCallback(const ScanCallback& handler) noexcept
    {
        scan_callback_ = handler;
    }

    void PushPacket(const VelodynePacket& data_packet);
    void PushGpsPacket(const VelodyneGpsPacket& gps_packet);

private:
    const bool_t            use_gps_stamp_;
    bool_t                  synchronized_;
    std::mutex              base_hour_mutex_;
    holo::common::Timestamp base_hour_;
    ScanCallback            scan_callback_;
    uint32_t                packet_per_rotation_;
    VelodyneScan            scan_;
    const uint32_t          packet_per_scan_;
    const uint32_t          duration_ns_per_scan_;
    int64_t                 time_temp_ns_;
    bool_t                  time_temp_ns_is_useful_;
};

}  // namespace velodyne
}  // namespace sensors
}  // namespace holo

#endif
