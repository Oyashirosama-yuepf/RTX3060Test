/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_encoder_mdc610.h
 * @brief Image Encoder on mdc610 platform
 * @author guoguangchao(guoguangchao@holomatic.com).
 * @date 2021-06-07
 */
#ifndef _HOLO_SENSORS_CAMERA_ENCODER_IMAGE_ENCODER_MDC610_H
#define _HOLO_SENSORS_CAMERA_ENCODER_IMAGE_ENCODER_MDC610_H

#include <functional>
#include <memory>
#include <mutex>
#include <thread>

#include <core/core.h>
#include <video/haf_venc.h>

#include <holo/sensors/camera/encoder/image_encoder_base.h>

namespace holo
{
namespace sensors
{
namespace camera
{
template <holo::Image::Encoding InType>
class ImageEncoderDvpp : public ImageEncoderBase
{
public:
    ImageEncoderDvpp(uint32_t cols, uint32_t rows, uint32_t fps);
    ~ImageEncoderDvpp();
    bool_t Encode(const Image& image);

protected:
    static constexpr int32_t MIN_VDEC_CHANNEL_ID = 25;
    static constexpr int32_t MAX_VDEC_CHANNEL_ID = 46;
    static constexpr int32_t MIN_IMAGE_WIDTH     = 128;
    static constexpr int32_t MAX_IMAGE_WIDTH     = 4096;
    static constexpr int32_t MIN_IMAGE_HIGHT     = 128;
    static constexpr int32_t MAX_IMAGE_HIGHT     = 4096;

private:
    int32_t                         frame_index_;
    std::shared_ptr<uint8_t>        data_;
    std::shared_ptr<Adsfi::HafVenc> encoder_;
    int32_t                         current_channel_id_;
    struct Adsfi::HafContext        haf_context_;
};
}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif