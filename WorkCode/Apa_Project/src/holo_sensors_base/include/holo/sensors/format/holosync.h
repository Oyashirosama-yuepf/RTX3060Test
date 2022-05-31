/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file holosync.h
 * @brief define the holo can structure format class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020-07-24
 */

#ifndef _HOLO_SENSORS_FORMAT_HOLOSYNC_H
#define _HOLO_SENSORS_FORMAT_HOLOSYNC_H

#include <holo/common/timestamp.h>
#include <holo/log/hololog.h>
#include <holo/os/endian.h>
#include <holo/sensors/format/format.h>
#include <holo/serialization/serialization.h>
#include <holo_c/core/static_assert.h>

namespace holo
{
namespace sensors
{
namespace format
{
using Timestamp = holo::common::Timestamp;
using Duration  = holo::common::Duration;
class HoloSyncPacket : public FormatBase
{
public:
    HoloSyncPacket() noexcept;
    ~HoloSyncPacket() = default;

    uint32_t GetSec() const noexcept;
    uint32_t GetNsec() const noexcept;
    uint32_t GetCounter() const noexcept;
    uint32_t GetSerializedSize() const noexcept;
    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept;
    uint32_t Deserialize(const uint8_t* data, uint32_t bytes);

private:
    uint32_t sec_;      //!< timestamp sec
    uint32_t nsec_;     //!< timestamp usec
    uint32_t counter_;  //!< general counter

private:
    static constexpr uint32_t SIZE = 12u;
};

class HoloSyncDiffPacket
{
public:
    HoloSyncDiffPacket() noexcept;
    ~HoloSyncDiffPacket() = default;

    bool      IsHeaderValid() const noexcept;
    uint8_t   IsSourceValid() const noexcept;
    uint8_t   IsTargetValid() const noexcept;
    uint16_t  GetCounter() const noexcept;
    Timestamp GetSourceTimestamp() const noexcept;
    Timestamp GetTargetTimestamp() const noexcept;
    Duration  GetTimeDiff() const noexcept;
    uint32_t  GetSerializedSize() const noexcept;
    uint32_t  Serialize(uint8_t* data, uint32_t bytes) const noexcept;
    uint32_t  Deserialize(const uint8_t* data, uint32_t bytes);

private:
    uint32_t  header_;
    uint8_t   source_time_valid_;
    uint8_t   target_time_valid_;
    uint16_t  counter_;
    Timestamp source_timestamp_;
    Timestamp target_timestamp_;
    Duration  time_diff_;

private:
    static constexpr uint32_t SIZE        = 32u;
    static constexpr uint32_t TIME_HEADER = 0X21402323;
};

}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif
