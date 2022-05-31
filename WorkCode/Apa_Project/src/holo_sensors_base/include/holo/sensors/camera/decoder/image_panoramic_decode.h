/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_panoramic_decode.h
 * @brief Image Panoramic Decode
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-11
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_PANORAMIC_DECODE_H
#define _HOLO_SENSORS_CAMERA_IMAGE_PANORAMIC_DECODE_H

#include <holo/sensors/camera/decoder/image_sync_decoder_tda4.h>
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
class ImagePanoramicDecode : public ImageDecoderBase, public Tda4DecodeVxContext
{
public:
    ImagePanoramicDecode();
    ~ImagePanoramicDecode() override;
    bool_t Decode(const uint8_t* data, const size_t size) override;
    ImageType GetImageType() const noexcept override;
    holo::Image::Encoding GetEncoding() const noexcept override;

private:
    struct AppSyncDecodeObject object_;
    ImagePacket                compress_data_;
    std::shared_ptr<uint8_t>   decode_buffer_;
    std::list<holo::Image>     image_list_;
    holo::Image                the_last_image0_;
    holo::Image                the_last_image1_;
    holo::bool_t               skip_this_frame_;
    holo::bool_t               finish_flag_;

private:
    static constexpr uint64_t BUFFER_SIZE = 1280 * 1600 * 3 / 2;
    static constexpr uint32_t DST_WIDTH   = 1280;
    static constexpr uint32_t DST_HEIGHT  = 1600;
    static constexpr uint32_t OUT_WIDTH   = 1280;
    static constexpr uint32_t OUT_HEIGHT  = 800;
};
}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  //_HOLO_SENSORS_CAMERA_IMAGE_PANORAMIC_DECODE_H