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

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_ENCODER_BASE_H
#define _HOLO_SENSORS_CAMERA_IMAGE_ENCODER_BASE_H

#include <list>

#include <holo/common/image.h>
#include <holo/sensors/camera/image_ipc.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/sensors/camera/image_utils.h>

namespace holo
{
namespace sensors
{
namespace camera
{
using SingleDataSender = std::function<void(const ImagePacket&)>;
using MutilDataSender  = std::function<void(const uint8_t*, const size_t)>;

class ImageEncoderBase
{
public:
    ImageEncoderBase(uint32_t cols, uint32_t rows, uint32_t fps, ImageType type);
    virtual ~ImageEncoderBase() = default;

    ImageType GetOutputType() const noexcept;
    void SetSender(const SingleDataSender& handler) noexcept;
    void SetSender(const MutilDataSender& handler) noexcept;
    virtual bool_t Encode(const Image& image);
    virtual bool_t Encode(const std::list<holo::Image> image_list);

protected:
    uint32_t         cols_;
    uint32_t         rows_;
    uint32_t         fps_;
    ImageType        type_;
    SingleDataSender single_data_sender_;
    MutilDataSender  mutil_data_sender_;
    ImagePacket      encoded_data_;
};

class DummyEncoder : public ImageEncoderBase
{
public:
    DummyEncoder(uint32_t cols, uint32_t rows, uint32_t fps, ImageType image_type = ImageType::INVALID);
    bool_t Encode(const Image&);
};

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  // _HOLO_SENSORS_CAMERA_IMAGE_ENCODER_BASE_H
