/*!
 * \brief
 * \author liwenjun
 * \date 2017-07-05
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice. */

#include <holo/log/hololog.h>
#include <holo/sensors/lidar/velodyne/velodyne_driver.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/sensors/utils/sensors_utils.h>

namespace holo
{
namespace sensors
{
namespace velodyne
{
VelodyneDriver::VelodyneDriver(uint32_t packet_rate, uint32_t scan_rate, uint32_t rpm, uint32_t coord, bool_t use_gps_stamp)
    : use_gps_stamp_(use_gps_stamp)
    , synchronized_(false)
    , base_hour_mutex_()
    , base_hour_(0, 0)
    , scan_callback_(nullptr)
    , packet_per_rotation_(packet_rate * 60.0f / rpm)
    , packet_per_scan_(packet_rate / scan_rate)
    , duration_ns_per_scan_(holo::sensors::NSEC_PER_SEC / scan_rate)
    , time_temp_ns_(0)
    , time_temp_ns_is_useful_(false)
{
    if (!LidarUtils::LidarScanRateIsValid(scan_rate))
    {
        std::ostringstream oss;
        oss << "Not supported scan rate!";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    /* set coord */
    scan_.SetCoordinate(coord);
    /* reserve space increased 1.5 times */
    scan_.Reserve(packet_per_scan_ * 1.5);
}

void VelodyneDriver::PushPacket(const VelodynePacket& data_packet)
{
    if(use_gps_stamp_ && !synchronized_)
    {
        return;
    }
    int64_t current_time_ns = (base_hour_ + holo::common::Duration(data_packet.Timestamp() / 1e6)).ToNsec();
    if (!time_temp_ns_is_useful_)
    {
        time_temp_ns_           = current_time_ns;
        time_temp_ns_is_useful_ = true;
    }

    if (scan_.Size() >= packet_per_scan_ * 1.5)
    {
        throw holo::exception::OutOfRangeException("Out of velodyne scan space!");
    }

    
    if ((current_time_ns / duration_ns_per_scan_) > (time_temp_ns_ / duration_ns_per_scan_))
    {
        {
            std::unique_lock<std::mutex> lck(base_hour_mutex_);
            scan_.SetTimestamp(base_hour_);
        }
        if (scan_callback_)
        {
            scan_callback_(scan_);
        }
        scan_.Clear();
    }
    scan_.PushBack(data_packet);
    time_temp_ns_ = current_time_ns;
}

void VelodyneDriver::PushGpsPacket(const VelodyneGpsPacket& gps_packet)
{
    bool_t pps_received = gps_packet.IsPpsLocked();
    uint32_t sec = gps_packet.GetTimestamp();
    bool_t nmea_received = static_cast<bool_t>(sec != 0);
    synchronized_ = pps_received && nmea_received;
    std::unique_lock<std::mutex> lck(base_hour_mutex_);
    base_hour_ = holo::common::Timestamp(sec, 0);
}

}  // namespace velodyne
}  // namespace sensors
}  // namespace holo
