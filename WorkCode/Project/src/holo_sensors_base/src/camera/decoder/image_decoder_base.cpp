/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_decoder_base.h
 * @brief image decoder base class
 * @author guoguangchao(guoguangchao@holomatic.com).
 * @date 2020-10-01
 */

#include <holo/sensors/camera/decoder/image_decoder_base.h>

namespace holo
{
namespace sensors
{
namespace camera
{
ImageDecoderData::ImageDecoderData(SensorId sensor_id, uint16_t cols, uint16_t rows, uint32_t fps, holo::Image::Encoding out_type,
                 bool_t show_image)
  : cols_(cols)
  , rows_(rows)
  , fps_(fps)
  , show_image_(show_image)
  , sensor_id_(sensor_id)
{
    (void)out_type;
}

ImageDecoderBase::ImageDecoderBase() : output_video_cols_(0), output_video_rows_(0), image_callback_(nullptr), counter_callback_(nullptr)
{
}   

void ImageDecoderBase::SetOutputVideoSize(uint32_t output_video_cols, uint32_t output_video_rows)
{
    output_video_cols_ = output_video_cols;
    output_video_rows_ = output_video_rows;
}

void ImageDecoderBase::SetImageCallback(const ImageCallbackType& handler) noexcept
{
    if (handler != nullptr)
    {
        image_callback_ = handler;
    }
}

void ImageDecoderBase::SetImageListCallback(const ImageListCallbackType& handler) noexcept
{
    if (handler != nullptr)
    {
        image_list_callback_ = handler;
    }
}

void ImageDecoderBase::SetImageCounterCallback(const CounterCallbackType& handler) noexcept
{
    if (handler != nullptr)
    {
        counter_callback_ = handler;
    }
}

bool_t ImageDecoderBase::Decode(const ImagePacket& image_packet)
{
    (void)image_packet;
    std::runtime_error("cannot call the interface of ImageDecoderBase base class");
    return false;
}

bool_t ImageDecoderBase::Decode(const uint8_t* data, const size_t size)
{
    (void)data;
    (void)size;
    std::runtime_error("cannot call the interface of ImageDecoderBase base class");
    return false;
}

DummyDecoder::DummyDecoder() : ImageDecoderBase()
{
}

DummyDecoder::DummyDecoder(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps, bool_t show_image)
  : ImageDecoderBase()
{
    (void)id;
    (void)cols;
    (void)rows;
    (void)fps;
    (void)show_image;
}

bool_t DummyDecoder::Decode(const ImagePacket& image_packet)
{
    (void)image_packet;
    return true;
}

ImageType DummyDecoder::GetImageType() const noexcept
{
    return ImageType::INVALID;
}

holo::Image::Encoding DummyDecoder::GetEncoding() const noexcept
{
    return holo::Image::Encoding::UNKNOWN;
}

ImageType DummyDecoder::GetInputType()
{
    return ImageType::INVALID;
}

holo::Image::Encoding DummyDecoder::GetOutputType()
{
    return holo::Image::Encoding::UNKNOWN;
}

}  // namespace camera
}  // namespace sensors
}  // namespace holo