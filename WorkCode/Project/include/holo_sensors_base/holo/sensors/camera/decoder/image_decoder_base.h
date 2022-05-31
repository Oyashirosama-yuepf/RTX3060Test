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

#ifndef _HOLO_SENSORS_CAMERA_DECODER_IMAGE_DECODER_BASE_H
#define _HOLO_SENSORS_CAMERA_DECODER_IMAGE_DECODER_BASE_H

#include <holo/common/image.h>
#include <holo/core/types.h>
#include <holo/sensors/camera/image_ipc.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/sensors/camera/image_utils.h>
#include <functional>
#include <list>
#include <memory>

extern "C" {
#include <jpeglib.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <x264.h>
}

namespace holo
{
namespace sensors
{
namespace camera
{
class ImageDecoderData
{
public:
    ImageDecoderData() = delete;
    ImageDecoderData(SensorId sensor_id, uint16_t cols, uint16_t rows, uint32_t fps, holo::Image::Encoding out_type,
                     bool_t show_image = false);

    virtual ~ImageDecoderData() = default;

protected:
    uint16_t                  cols_;
    uint16_t                  rows_;
    uint32_t                  fps_;
    uint32_t                  counter_;
    bool_t                    show_image_;
    holo::Image               out_image_;
    std::shared_ptr<ImageIpc> ipc_server_;
    SensorId                  sensor_id_;
};

class ImageDecoderBase
{
public:
    using ImageCallbackType     = std::function<void(const holo::Image&)>;
    using ImageListCallbackType = std::function<void(const std::list<holo::Image>)>;
    using CounterCallbackType   = std::function<void(uint32_t)>;

    ImageDecoderBase();
    virtual ~ImageDecoderBase() = default;

    void SetOutputVideoSize(uint32_t output_video_cols, uint32_t output_video_rows);
    void SetImageCallback(const ImageCallbackType& handler) noexcept;
    void SetImageListCallback(const ImageListCallbackType& handler) noexcept;
    void SetImageCounterCallback(const CounterCallbackType& handler) noexcept;
    virtual bool_t Decode(const ImagePacket& image_packet);
    virtual bool_t Decode(const uint8_t* data, const size_t size);
    virtual ImageType GetImageType() const noexcept = 0;
    virtual holo::Image::Encoding GetEncoding() const noexcept = 0;

protected:
    uint16_t              output_video_cols_;
    uint16_t              output_video_rows_;
    ImageCallbackType     image_callback_;
    ImageListCallbackType image_list_callback_;
    CounterCallbackType   counter_callback_;
};

class DummyDecoder : public ImageDecoderBase
{
public:
    DummyDecoder();
    DummyDecoder(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps, bool_t show_image = false);
    bool_t Decode(const ImagePacket& image_packet);
    ImageType GetImageType() const noexcept override;
    holo::Image::Encoding GetEncoding() const noexcept override;
    static ImageType GetInputType();
    static holo::Image::Encoding GetOutputType();
};

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  // _HOLO_SENSORS_CAMERA_DECODER_IMAGE_DECODER_BASE_H
