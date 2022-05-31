/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_capture_raw.cpp
 * @brief image raw data dirver
 * @author guoguangchao(guoguangchao@holomatic.com).
 * @date 2021-09-27
 */

#include <holo/sensors/camera/capture/image_capture_raw.h>

namespace holo
{
namespace sensors
{
namespace camera
{
template <ImageType Type>
ImageCaptureRaw<Type>::ImageCaptureRaw(SensorId sensor_id, uint32_t cols, uint32_t rows, uint32_t fps,
                                       bool_t trigger_mode)
  : ImageTimestamperT<HoloSyncPacket>(fps, trigger_mode)
  , sensor_id_(sensor_id)
  , frame_counter_(0)
  , raw_callback_(nullptr)
{
    {
        (void)std::memset(rawbuf_, 0, sizeof(IMAGE_RAW_SIZE_MAX));
        raw_image_.image_type = Type;
        raw_image_.data       = rawbuf_;
        raw_image_.cols       = cols;
        raw_image_.rows       = rows;
        raw_image_.size       = cols * rows * 2;
    }
}

template <ImageType Type>
void ImageCaptureRaw<Type>::SetRawCallback(const RawCallback& handler) noexcept
{
    raw_callback_ = handler;
}

template <ImageType Type>
void ImageCaptureRaw<Type>::ParseData(const StreamBuffer& buffer)
{
    holo::common::Timestamp received_stamp;
    holo::common::Timestamp trigger_stamp;
    if (false == UpdateTimestamp(received_stamp, trigger_stamp))
    {
        return;
    }
    /* ... */
    if (buffer.size != raw_image_.size)
    {
        LOG(ERROR) << "invalid yuyv size " << buffer.size << ", want " << raw_image_.size;
        return;
    }
    if (raw_callback_)
    {
        (void)std::memcpy(raw_image_.data, buffer.start, buffer.size);
        raw_image_.trigger_stamp  = trigger_stamp;
        raw_image_.received_stamp = received_stamp;
        raw_image_.seq            = frame_counter_;
        raw_callback_(raw_image_);
    }
    frame_counter_++;
}

template class ImageCaptureRaw<ImageType::H264>;
template class ImageCaptureRaw<ImageType::H265>;
template class ImageCaptureRaw<ImageType::JPEG>;
template class ImageCaptureRaw<ImageType::RAW_YUYV>;

}  // namespace camera
}  // namespace sensors
}  // namespace holo