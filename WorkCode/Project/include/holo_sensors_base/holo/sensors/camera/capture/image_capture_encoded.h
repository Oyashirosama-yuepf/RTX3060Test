/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_capture_encoded.h
 * @brief Image encoded driver
 * @author guoguangchao(guoguangchao@holomatic.com).
 * @date 2021-05-28
 */

#ifndef _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_CAPTURE_ENCODED_H
#define _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_CAPTURE_ENCODED_H

#include <holo/sensors/camera/decoder/image_decoder.h>
#include <holo/sensors/camera/encoder/image_encoder_base.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/sensors/camera/image_utils.h>

namespace holo
{
namespace sensors
{
namespace camera
{
template <typename Tdec = DummyDecoder>
class ImageCaptureEncoded : public DummyEncoder, public Tdec
{
public:
    using Timestamp           = holo::common::Timestamp;
    using ImageCallbackType   = std::function<void(const holo::Image&)>;
    using CounterCallbackType = std::function<void(uint32_t)>;

    ImageCaptureEncoded(SensorId id, uint32_t cols, uint32_t rows, uint32_t fps, ImageType type,
                        bool_t show_image = false);
    ~ImageCaptureEncoded() = default;

    void ParseData(const StreamBuffer& buffer, const Timestamp& received_stamp, const Timestamp& trigger_stamp,
                   const uint8_t frame_type);

private:
    uint32_t frame_counter_;
};

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif
