/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_panoramic_encode.h
 * @brief Image Panoramic Encode
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-11
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_PANORAMIC_ENCODE_H
#define _HOLO_SENSORS_CAMERA_IMAGE_PANORAMIC_ENCODE_H

#include <holo/sensors/camera/encoder/image_encoder_base.h>
#include <holo/sensors/camera/encoder/image_sync_encoder_tda4.h>
#include <holo/sensors/camera/encoder/tda4_encode_vx_context.h>
#include <cstring>
#include <iostream>
#include <memory>

namespace holo
{
namespace sensors
{
namespace camera
{
class ImagePanoramicEncode : public ImageEncoderBase, public Tda4EncodeVxContext
{
public:
    ImagePanoramicEncode() = delete;
    ImagePanoramicEncode(uint32_t fps, uint32_t bitrate = BITRATE);
    ~ImagePanoramicEncode();

    bool_t Encode(const std::list<holo::Image> image_list) override;

private:
    struct AppSyncEncodeObject object_;
    uint64_t                   counter_;
    std::shared_ptr<uint8_t>   output0_;
    uint8_t*                   output1_;

private:
    static constexpr uint64_t BUFFER_SIZE = 1280 * 800 * 3 / 2;
    static constexpr uint32_t SRC_WIDTH   = 1280;
    static constexpr uint32_t SRC_HEIGHT  = 1600;
    static constexpr uint32_t BITRATE     = 10000000;
};
}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  //_HOLO_SENSORS_CAMERA_IMAGE_PANORAMIC_ENCODE_H