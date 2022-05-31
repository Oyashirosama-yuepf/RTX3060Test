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

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_FORESIGHT_DECODE_H
#define _HOLO_SENSORS_CAMERA_IMAGE_FORESIGHT_DECODE_H

#include <holo/sensors/camera/decoder/image_resize_decoder_tda4.h>
#include <holo/sensors/camera/decoder/image_decoder_base.h>
#include <holo/sensors/camera/decoder/tda4_decode_vx_context.h>
#include <cstring>
#include <iostream>

namespace holo
{
namespace sensors
{
namespace camera
{
class ImageForesightDecode : public ImageDecoderBase, public Tda4DecodeVxContext
{
public:
    ImageForesightDecode();
    ~ImageForesightDecode() override;
    bool_t Decode(const uint8_t* data, const size_t size) override;
    ImageType GetImageType() const noexcept override;
    holo::Image::Encoding GetEncoding() const noexcept override;

private:
    struct AppResizeDecodeObject object_;
    ImagePacket                  compress_data_;
    std::shared_ptr<uint8_t>     decode_buffer_;
    std::list<holo::Image>       image_list_;
    holo::Image                  the_last_image_;
    holo::bool_t                 skip_this_frame_;

private:
    static constexpr uint64_t BUFFER_SIZE = 1920 * 1080 * 3 / 2;
    static constexpr uint32_t SRC_WIDTH   = 1280;
    static constexpr uint32_t SRC_HEIGHT  = 720;
    static constexpr uint32_t DST_WIDTH   = 1920;
    static constexpr uint32_t DST_HEIGHT  = 1080;
};
}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  //_HOLO_SENSORS_CAMERA_IMAGE_FORESIGHT_DECODE_H