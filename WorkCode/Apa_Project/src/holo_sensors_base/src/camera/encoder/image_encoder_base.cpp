/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_encoder_base.h
 * @brief image encoder base
 * @author guoguangchao(guoguangchao@holomatic.com).
 * @date 2020-09-29
 */

#include <holo/sensors/camera/encoder/image_encoder_base.h>

namespace holo
{
namespace sensors
{
namespace camera
{
ImageEncoderBase::ImageEncoderBase(uint32_t cols, uint32_t rows, uint32_t fps, ImageType type)
    : cols_(cols)
    , rows_(rows)
    , fps_(fps)
    , type_(type)
    , single_data_sender_(nullptr)
    , mutil_data_sender_(nullptr)
{
}

ImageType ImageEncoderBase::GetOutputType() const noexcept
{
    return type_;
}

void ImageEncoderBase::SetSender(const SingleDataSender& handler) noexcept
{
    if (handler != nullptr)
    {
        single_data_sender_ = handler;
    }
}

void ImageEncoderBase::SetSender(const MutilDataSender& handler) noexcept
{
    if (handler != nullptr)
    {
        mutil_data_sender_ = handler;
    }
}

bool_t ImageEncoderBase::Encode(const Image& image)
{
    (void)image;
    std::runtime_error("cannot call the interface of ImageEncoderBase base class");
    return false;
}

bool_t ImageEncoderBase::Encode(const std::list<holo::Image> image_list)
{
    (void)image_list;
    std::runtime_error("cannot call the interface of ImageEncoderBase base class");
    return false;
}

DummyEncoder::DummyEncoder(uint32_t cols, uint32_t rows, uint32_t fps, ImageType image_type)
    : ImageEncoderBase(cols, rows, fps, image_type)
{

}

bool_t DummyEncoder::Encode(const Image&)
{
    return true;
}
}  // namespace camera
}  // namespace sensors
}  // namespace holo