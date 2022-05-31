/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_foresight_encode.h
 * @brief Image Foresight Encode
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-11
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_FORESIGHT_ENCODE_H
#define _HOLO_SENSORS_CAMERA_IMAGE_FORESIGHT_ENCODE_H

#include <holo/sensors/camera/encoder/image_encoder_base.h>
#include <holo/sensors/camera/encoder/image_resize_encode_tda4.h>
#include <holo/sensors/camera/encoder/tda4_encode_vx_context.h>
#include <cstring>
#include <iostream>

using holo::sensors::camera::IMAGE_ENCODE_SIZE_MAX;

namespace holo
{
namespace sensors
{
namespace camera
{
class ImageForesightEncode : public ImageEncoderBase, public Tda4EncodeVxContext
{
public:
    ImageForesightEncode() = delete;
    ImageForesightEncode(uint32_t fps, uint32_t bitrate = BITRATE);
    ~ImageForesightEncode();

    bool_t Encode(const std::list<holo::Image> image_list) override;

private:
    struct AppResizeEncodeObject object_;
    uint64_t                     counter_;
    std::shared_ptr<uint8_t>     output_;

private:
    static constexpr uint64_t BUFFER_SIZE = 1920 * 1080 * 3 / 2;
    static constexpr uint32_t SRC_WIDTH   = 1920;
    static constexpr uint32_t SRC_HEIGHT  = 1080;
    static constexpr uint32_t DST_WIDTH   = 1280;
    static constexpr uint32_t DST_HEIGHT  = 720;
    static constexpr uint32_t BITRATE     = 10000000;
};
}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  //_HOLO_SENSORS_CAMERA_IMAGE_FORESIGHT_ENCODE_H