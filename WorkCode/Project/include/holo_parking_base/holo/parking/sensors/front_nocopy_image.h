/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file front_nocopy_image.h
 * @brief This header file defines front camera nocopy image class
 * @author chengxiang(chengxiang@holomatic.com)
 * @date 2022-03-23
 */

#ifndef HOLO_PARKING_SENSORS_FRONT_NOCOPY_IMAGE_H
#define HOLO_PARKING_SENSORS_FRONT_NOCOPY_IMAGE_H

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>
#include <holo/common/image.h>

namespace holo
{
namespace parking
{
namespace sensors 
{

template<size_t CHANNEL_SIZE>
class FrontNocopyImage
{
public:
    static size_t const s_channel_size = CHANNEL_SIZE;

    struct ChannelData
    {
        void *v_ptr;
        holo::uint64_t size;
    };

    struct Channels {
        ChannelData data[s_channel_size];
    };

public:
    FrontNocopyImage()
    :recieve_timestamp_(),
    trigger_timestamp_(),
    width_(0), height_(0),
    encode_(holo::Image::Encoding::UNKNOWN)
    {
    }

    FrontNocopyImage(const FrontNocopyImage &other)
    : recieve_timestamp_(other.GetRecieveTimestamp()),
    trigger_timestamp_(other.GetTriggerTimestamp()),
    width_(other.GetWidth()),
    height_(other.GetHeight()),
    encode_(other.GetEncoding()),
    channel_data_(other.GetChannels())
    {}

    void SetRecieveTimestamp(holo::common::Timestamp const& timestamp)
    {
        recieve_timestamp_ = timestamp;
    }

    holo::common::Timestamp const& GetRecieveTimestamp() const 
    {
        return recieve_timestamp_;
    }

    void SetTriggerTimestamp(holo::common::Timestamp const& timestamp)
    {
        trigger_timestamp_ = timestamp;
    }

    holo::common::Timestamp const& GetTriggerTimestamp() const
    {
        return trigger_timestamp_;
    }

    void SetEncoding(holo::Image::Encoding const & encoding)
    {
        encode_ = encoding;
    }

    holo::Image::Encoding const & GetEncoding() const
    {
        return encode_;
    }

    void SetChannels(Channels const& channel)
    {
        channel_data_ = channel;
    }

    Channels const& GetChannels() const
    {
        return channel_data_;
    }

    void SetWidth(holo::uint32_t width)
    {
        width_ = width;
    }

    holo::uint32_t GetWidth() const noexcept
    {
        return width_;
    }

    void SetHeight(holo::uint32_t height)
    {
        height_ = height;
    }

    holo::uint32_t GetHeight() const noexcept
    {
        return height_;
    }

private:
    holo::common::Timestamp recieve_timestamp_;
    holo::common::Timestamp trigger_timestamp_;
    holo::uint32_t width_;
    holo::uint32_t height_;
    holo::Image::Encoding   encode_;

    Channels channel_data_;
};
}
}
}

#endif /// HOLO_PARKING_SENSORS_FRONT_NOCOPY_IMAGE_H