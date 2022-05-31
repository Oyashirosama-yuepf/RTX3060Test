/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pandar_driver.cpp
 * @brief This source file impl the functions of ouster driver
 * @author yinweigen@holomatic.com
 * @date 2022-01-17
 */

#include <holo/log/hololog.h>
#include <holo/sensors/lidar/ouster/ouster_driver.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/sensors/utils/sensors_utils.h>

namespace holo
{
namespace sensors
{
namespace ouster
{
OusterDriver::OusterDriver(uint32_t packet_rate, uint32_t scan_rate, uint32_t coord)
  : base_hour_mutex_()
  , base_hour_(0, 0)
  , scan_callback_(nullptr)
  , packet_per_scan_(packet_rate / scan_rate)
  , duration_ns_per_scan_(holo::sensors::NSEC_PER_SEC / scan_rate)
  , time_temp_ns_(0)
  , time_temp_ns_is_useful_(false)
{
    if (!LidarUtils::LidarScanRateIsValid(scan_rate))
    {
        std::ostringstream oss;
        oss << "Not support scan rate!";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    scan_.SetCoordinate(coord);

    scan_.Reserve(packet_per_scan_ * 1.5);
}

void OusterDriver::PushPacket(const OusterPacket& data_packet)
{
    //    LOG(ERROR) << "--------------\n";
    int64_t current_time_ns = data_packet.GetBlockTimeStamp();
    if (!time_temp_ns_is_useful_)
    {
        time_temp_ns_           = current_time_ns;
        time_temp_ns_is_useful_ = true;
    }

    if (scan_.Size() >= packet_per_scan_ * 1.5)
    {
        throw holo::exception::OutOfRangeException("Out of ouster scan space!");
    }
    if (data_packet.Block(0).GetMeasurementid() == 0)
    {
        std::unique_lock<std::mutex> lck(base_hour_mutex_);
        scan_.SetTimestamp(base_hour_);
        if (scan_callback_)
        {
            scan_callback_(scan_);
        }
        scan_.Clear();
    }
    if(scan_.Size() < 64)
    {
        scan_.PushBack(data_packet);
    }
    time_temp_ns_ = current_time_ns;
}

}  // namespace ouster
}  // namespace sensors
}  // namespace holo
