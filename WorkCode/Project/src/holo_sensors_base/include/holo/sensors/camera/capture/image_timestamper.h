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

#ifndef _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_TIMESTAMPER_H
#define _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_TIMESTAMPER_H

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/os/time.h>
#include <holo/sensors/camera/image_structure.h>
#include <mutex>

namespace holo
{
namespace sensors
{
namespace camera
{
using HoloSyncPacket     = holo::sensors::format::HoloSyncPacket;
using HoloSyncDiffPacket = holo::sensors::format::HoloSyncDiffPacket;

class ImageTimestamperBase
{
public:
    ImageTimestamperBase(uint32_t fps, bool_t trigger_mode)
      : fps_(fps), trigger_mode_(trigger_mode), triggered_done_(false){};
    virtual ~ImageTimestamperBase() = default;

protected:
    uint32_t   fps_;
    bool_t     trigger_mode_;
    bool_t     triggered_done_;
    std::mutex image_sync_mutex_;
};

template <typename T>
class ImageTimestamperT : public ImageTimestamperBase
{
public:
    ImageTimestamperT(uint32_t fps, bool_t trigger_mode);
    virtual ~ImageTimestamperT() = default;
    virtual bool_t SetSyncInfo(const T& packet) = 0;

protected:
    virtual bool_t UpdateTimestamp(holo::common::Timestamp&, holo::common::Timestamp&) = 0;
};

template <>
class ImageTimestamperT<HoloSyncPacket> : public ImageTimestamperBase
{
public:
    ImageTimestamperT(uint32_t fps, bool_t trigger_mode);
    virtual ~ImageTimestamperT() = default;
    bool_t SetSyncInfo(const HoloSyncPacket& packet);

protected:
    bool_t UpdateTimestamp(holo::common::Timestamp& received_stamp, holo::common::Timestamp& trigger_stamp);

protected:
    int64_t                      trigger_index_;
    HoloSyncPacket               image_sync_packet_;
    const holo::common::Duration kcycle_;
};

template <>
class ImageTimestamperT<HoloSyncDiffPacket> : public ImageTimestamperBase
{
public:
    ImageTimestamperT(uint32_t fps, bool_t trigger_mode);
    virtual ~ImageTimestamperT() = default;
    bool_t SetSyncInfo(const HoloSyncDiffPacket& packet);

protected:
    bool_t UpdateTimestamp(holo::common::Timestamp& received_stamp, holo::common::Timestamp& time_diff);

protected:
    HoloSyncDiffPacket image_sync_diff_packet_;
};
}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  // _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_TIMESTAMPER_H
