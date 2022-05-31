/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsruby_driver.cpp
 * @brief A rsruby driver
 * @author wujie<wujie@holomatic.com>
 * @date 2021/10/22
 */

#include <holo/log/hololog.h>
#include <holo/sensors/lidar/rsruby/rsruby_driver.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <fstream>
#include <sstream>
#include <string>

namespace holo
{
namespace sensors
{
namespace rsruby
{
RsrubyDriver::RsrubyDriver(uint32_t coord, uint32_t packet_rate, uint32_t scan_rate)
  : packet_per_scan_(packet_rate / scan_rate)
  , duration_ns_per_scan_(holo::sensors::NSEC_PER_SEC / scan_rate)
  , time_temp_ns_(0)
  , time_temp_ns_is_useful_(false)
  , scan_callback_(nullptr)
{
    if (!LidarUtils::LidarScanRateIsValid(scan_rate))
    {
        std::ostringstream oss;
        oss << "Not supported scan rate!";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    scan_.SetCoordinate(coord);
    /* reserve space increased 1.5 times */
    scan_.Reserve(packet_per_scan_ * 1.5);
}

void RsrubyDriver::PushPacket(const RsrubyPacket& data_packet)
{
    int64_t current_time_ns = data_packet.GetHeaderTimestamp().ToNsec();

    if (!time_temp_ns_is_useful_)
    {
        time_temp_ns_           = current_time_ns;
        time_temp_ns_is_useful_ = true;
    }
    else
    {
        if (scan_.Size() >= packet_per_scan_ * 1.5)
        {
            throw holo::exception::OutOfRangeException("Out of rsruby scan space!");
        }

        /* current time beyond the point in scan duration time */
        if ((current_time_ns / duration_ns_per_scan_) > (time_temp_ns_ / duration_ns_per_scan_))
        {
            if (scan_callback_)
            {
                scan_callback_(scan_);
            }
            scan_.Clear();
        }
        scan_.PushBack(data_packet);
        time_temp_ns_ = current_time_ns;
    }
}

void RsrubyDriver::InstallScanCallback(const ScanCallback& handler) noexcept
{
    scan_callback_ = handler;
}

// void RsrubyDriver::PushDeviceInfoPacket(const Rsm1DeviceInfoPacket& info_packet)
// {
// }

// void RsrubyDriver::InstallInfoCallback(const InfoCallback& handler) noexcept
// {
//     info_callback_ = handler;
// }
}  // namespace rsruby
}  // namespace sensors
}  // namespace holo