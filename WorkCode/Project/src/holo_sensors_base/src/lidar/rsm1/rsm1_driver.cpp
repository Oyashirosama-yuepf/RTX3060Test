/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsm1_driver.cpp
 * @brief A rsm1 driver
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/08/09
 */
#include <holo/log/hololog.h>
#include <holo/sensors/lidar/rsm1/rsm1_driver.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/sensors/utils/sensors_utils.h>

namespace holo
{
namespace sensors
{
namespace rsm1
{
Rsm1Driver::Rsm1Driver(uint32_t coord, uint32_t packet_rate, uint32_t scan_rate)
  : packet_per_scan_(packet_rate / scan_rate)
  , duration_ns_per_scan_(holo::sensors::NSEC_PER_SEC / scan_rate)
  , time_temp_ns_(0)
  , time_temp_ns_is_useful_(false)
  , scan_callback_(nullptr)
#if defined(MDC_PRODUCTION_MDC610)
  , use_datalayer_timestamp_(true)
#endif
{
    if (!LidarUtils::LidarScanRateIsValid(scan_rate))
    {
        std::ostringstream oss;
        oss << "Not supported scan rate!";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

#if defined(MDC_PRODUCTION_MDC610)
    holo::mdc610::GetTimeDiffBlocked(timediff_);
#endif
    
    scan_.SetCoordinate(coord);
    /* reserve space increased 1.5 times */
    scan_.Reserve(packet_per_scan_ * 1.5);
}

void Rsm1Driver::PushPacket(const Rsm1Packet& data_packet)
{
    int64_t current_time_ns = data_packet.GetHeaderTimestamp().ToNsec();
    if (!time_temp_ns_is_useful_)
    {
        time_temp_ns_           = current_time_ns;
        time_temp_ns_is_useful_ = true;
    }

    if (scan_.Size() >= packet_per_scan_ * 1.5)
    {
        throw holo::exception::OutOfRangeException("Out of rsm1 scan space!");
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
#if defined(MDC_PRODUCTION_MDC610)
    if (!use_datalayer_timestamp_)
    {
        (void)holo::mdc610::GetTimeDiff(timediff_);
        holo::common::Timestamp stamp = data_packet.GetHeaderTimestamp() + timediff_;
        scan_[scan_.Size() - 1].SetHeaderTimestamp(stamp);
    }
#endif
    time_temp_ns_ = current_time_ns;
}

void Rsm1Driver::InstallScanCallback(const ScanCallback& handler) noexcept
{
    scan_callback_ = handler;
}

// void Rsm1Driver::PushDeviceInfoPacket(const Rsm1DeviceInfoPacket& info_packet)
// {
// }

// void Rsm1Driver::InstallInfoCallback(const InfoCallback& handler) noexcept
// {
//     info_callback_ = handler;
// }
}  // namespace rsm1
}  // namespace sensors
}  // namespace holo