/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_timestamper.h
 * @brief image timestamper
 * @author guoguangchao(guoguangchao@holomatic.com).
 * @date 2020-09-27
 */

#include <holo/sensors/camera/capture/image_timestamper.h>

namespace holo
{
namespace sensors
{
namespace camera
{
ImageTimestamperT<HoloSyncPacket>::ImageTimestamperT(uint32_t fps, bool_t trigger_mode)
  : ImageTimestamperBase(fps, trigger_mode), trigger_index_(0), image_sync_packet_(), kcycle_(1.0f / fps_)
{
}

bool_t ImageTimestamperT<HoloSyncPacket>::SetSyncInfo(const HoloSyncPacket& packet)
{
    std::lock_guard<std::mutex> guard(image_sync_mutex_);
    image_sync_packet_ = packet;
    trigger_index_     = 0;
    triggered_done_    = true;
    return triggered_done_;
}

bool_t ImageTimestamperT<HoloSyncPacket>::UpdateTimestamp(holo::common::Timestamp& received_stamp,
                                                          holo::common::Timestamp& trigger_stamp)
{
    /*get system time*/
    uint32_t utc_sec, utc_nsec;
    holo::os::GetSystemTime(utc_sec, utc_nsec);
    received_stamp = holo::common::Timestamp(utc_sec, utc_nsec);

    if (trigger_mode_ && triggered_done_)
    {
        std::lock_guard<std::mutex> guard(image_sync_mutex_);
        holo::common::Timestamp     sync_stamp(image_sync_packet_.GetSec(), image_sync_packet_.GetNsec());
        trigger_stamp = sync_stamp + kcycle_ * trigger_index_;
        trigger_index_++;
    }
    return (!trigger_mode_) | triggered_done_;
}

ImageTimestamperT<HoloSyncDiffPacket>::ImageTimestamperT(uint32_t fps, bool_t trigger_mode)
  : ImageTimestamperBase(fps, trigger_mode), image_sync_diff_packet_()
{
}

bool_t ImageTimestamperT<HoloSyncDiffPacket>::SetSyncInfo(const HoloSyncDiffPacket& packet)
{
    if (!packet.IsSourceValid())
    {
        LOG(INFO) << "source timestamp is invalid";
        triggered_done_ = false;
        return triggered_done_;
    }
    if (!packet.IsTargetValid())
    {
        LOG(INFO) << "target timestamp is invalid";
        triggered_done_ = false;
        return triggered_done_;
    }
    std::lock_guard<std::mutex> guard(image_sync_mutex_);
    image_sync_diff_packet_ = packet;
    triggered_done_ = true;
    return triggered_done_;
}

bool_t ImageTimestamperT<HoloSyncDiffPacket>::UpdateTimestamp(holo::common::Timestamp& received_stamp,
                                                              holo::common::Timestamp& trigger_stamp)
{
    /*get system time*/
    uint32_t utc_sec, utc_nsec;
    holo::os::GetSystemTime(utc_sec, utc_nsec);
    received_stamp = holo::common::Timestamp(utc_sec, utc_nsec);

    if (trigger_mode_ && triggered_done_)
    {
        std::lock_guard<std::mutex> guard(image_sync_mutex_);
        holo::common::Duration      diff;
        // get diff time
        diff = image_sync_diff_packet_.GetTimeDiff();
        //  fix image time
        trigger_stamp = holo::common::Timestamp(trigger_stamp + diff);
    }
    return (!trigger_mode_) | triggered_done_;
}

template class ImageTimestamperT<HoloSyncPacket>;
template class ImageTimestamperT<HoloSyncDiffPacket>;
}  // namespace camera
}  // namespace sensors
}  // namespace holo