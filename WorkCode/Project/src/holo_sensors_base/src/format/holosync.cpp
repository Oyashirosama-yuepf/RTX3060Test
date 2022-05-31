/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file holosync.cpp
 * @brief define the holo can structure format class
 * @author yongchuan<yongchuan@holomatic.com>
 * @date 2021-11-05
 */

#include <holo/sensors/format/holosync.h>

namespace holo
{
namespace sensors
{
namespace format
{
using Timestamp = holo::common::Timestamp;
using Duration  = holo::common::Duration;

HoloSyncPacket::HoloSyncPacket() noexcept : sec_(0), nsec_(0), counter_(0)
{
}

uint32_t HoloSyncPacket::GetSec() const noexcept
{
    return sec_;
}

uint32_t HoloSyncPacket::GetNsec() const noexcept
{
    return nsec_;
}

uint32_t HoloSyncPacket::GetCounter() const noexcept
{
    return counter_;
}

uint32_t HoloSyncPacket::GetSerializedSize() const noexcept
{
    return SIZE;
}

uint32_t HoloSyncPacket::Serialize(uint8_t* data, uint32_t bytes) const noexcept
{
    if (bytes < SIZE)
    {
        return 0;
    }
    uint32_t* convert_data = reinterpret_cast<uint32_t*>(data);
    convert_data[0]        = holo::os::hton32(sec_);
    convert_data[1]        = holo::os::hton32(nsec_);
    convert_data[2]        = holo::os::hton32(counter_);
    return SIZE;
}

uint32_t HoloSyncPacket::Deserialize(const uint8_t* data, uint32_t bytes)
{
    if (bytes < SIZE)
    {
        return 0;
    }
    uint32_t* convert_data = reinterpret_cast<uint32_t*>(const_cast<uint8_t*>(data));
    sec_                   = holo::os::ntoh32(convert_data[0]);
    nsec_                  = holo::os::ntoh32(convert_data[1]);
    counter_               = holo::os::ntoh32(convert_data[2]);
    return SIZE;
}

HoloSyncDiffPacket::HoloSyncDiffPacket() noexcept
  : header_(0)
  , source_time_valid_(0)
  , target_time_valid_(0)
  , counter_(0)
  , source_timestamp_(0, 0)
  , target_timestamp_(0, 0)
  , time_diff_(0, 0)
{
}

bool HoloSyncDiffPacket::IsHeaderValid() const noexcept
{
    return (header_ == TIME_HEADER);
}

uint8_t HoloSyncDiffPacket::IsSourceValid() const noexcept
{
    return source_time_valid_;
}

uint8_t HoloSyncDiffPacket::IsTargetValid() const noexcept
{
    return target_time_valid_;
}

uint16_t HoloSyncDiffPacket::GetCounter() const noexcept
{
    return counter_;
}

Timestamp HoloSyncDiffPacket::GetSourceTimestamp() const noexcept
{
    return source_timestamp_;
}

Timestamp HoloSyncDiffPacket::GetTargetTimestamp() const noexcept
{
    return target_timestamp_;
}

Duration HoloSyncDiffPacket::GetTimeDiff() const noexcept
{
    return time_diff_;
}

uint32_t HoloSyncDiffPacket::GetSerializedSize() const noexcept
{
    return SIZE;
}

uint32_t HoloSyncDiffPacket::Serialize(uint8_t* data, uint32_t bytes) const noexcept
{
    if (bytes < SIZE)
    {
        return 0;
    }
    int64_t  diff_nsec;
    uint64_t source_timestamp;
    uint64_t target_timestamp;
    diff_nsec        = time_diff_.ToNsec();
    source_timestamp = source_timestamp_.ToNsec();
    target_timestamp = target_timestamp_.ToNsec();

    uint8_t                                  buffer[SIZE];
    holo::serialization::Serializer<true, 4> serializer(buffer, SIZE);
    serializer << header_ << source_time_valid_ << target_time_valid_ << counter_ << source_timestamp
               << target_timestamp << diff_nsec << holo::serialization::align;
    (void)std::memcpy(data, serializer.GetData(), serializer.GetSize());
    return serializer.GetSize();
}

uint32_t HoloSyncDiffPacket::Deserialize(const uint8_t* data, uint32_t bytes)
{
    if (bytes < SIZE)
    {
        return 0;
    }

    int64_t                                    duration;
    uint64_t                                   source_timestamp;
    uint64_t                                   target_timestamp;
    holo::serialization::Deserializer<true, 4> deserializer(data, SIZE);
    deserializer >> header_ >> source_time_valid_ >> target_time_valid_ >> counter_ >> source_timestamp >>
        target_timestamp >> duration >> holo::serialization::align;

    if ((1 == source_time_valid_) && (1 == target_time_valid_))
    {
        time_diff_        = Duration(duration);
        source_timestamp_ = Timestamp(source_timestamp);
        target_timestamp_ = Timestamp(target_timestamp);
    }

    return SIZE;
}

}  // namespace format
}  // namespace sensors
}  // namespace holo