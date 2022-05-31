/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_capture.cpp.
 * @brief Image Capture Driver.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-05.
 */

#include <holo/common/sensor_id.h>
#include <holo/log/hololog.h>
#include <holo/os/time.h>
#include <holo/sensors/camera/capture/image_capture_encoded.h>
#include <holo/sensors/camera/capture/image_capture_raw.h>
#include <holo/sensors/camera/capture/image_capture_rgb.h>
#include <holo/sensors/camera/decoder/image_decoder.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/sensors/camera/image_utils.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace camera
{
template class ImageCaptureBasic<Bayer8Converter>;
template class ImageCaptureBasic<YuyvConverter>;
template class ImageCaptureBasic<RawToNv12Converter>;
template class ImageCaptureBasic<Nv12ToBgrConverter>;

template class ImageCaptureRaw<ImageType::RAW_YUYV>;
template class ImageCaptureRgbT<Bayer8Converter>;
template class ImageCaptureRgbT<YuyvConverter>;

template <typename Tdec>
ImageCaptureEncoded<Tdec>::ImageCaptureEncoded(SensorId id, uint32_t cols, uint32_t rows, uint32_t fps, ImageType type,
                                               bool_t show_image)
  : DummyEncoder(cols, rows, fps, type), Tdec(id, cols, rows, fps, show_image), frame_counter_(0)
{
}

template <typename Tdec>
void ImageCaptureEncoded<Tdec>::ParseData(const StreamBuffer& buffer, const Timestamp& received_stamp,
                                          const Timestamp& trigger_stamp, const uint8_t frame_type)
{
    if (buffer.init)
    {
        encoded_data_.frame_type     = frame_type;
        encoded_data_.image_type     = type_;
        encoded_data_.cols           = cols_;
        encoded_data_.rows           = rows_;
        encoded_data_.seq            = frame_counter_;
        encoded_data_.received_stamp = received_stamp;
        encoded_data_.trigger_stamp  = trigger_stamp;
        encoded_data_.size           = buffer.size;
        encoded_data_.data           = static_cast<uint8_t*>(buffer.start);
        if (ImageEncoderBase::single_data_sender_)
        {
            ImageEncoderBase::single_data_sender_(encoded_data_);
        }
        frame_counter_++;
    }
}

template class ImageCaptureEncoded<DummyDecoder>;

template class ImageCaptureEncoded<H264ToNv12Decoder>;
template class ImageCaptureEncoded<H264ToBGRDecoder>;
template class ImageCaptureEncoded<H264ToRGBDecoder>;

template class ImageCaptureEncoded<H265ToNv12Decoder>;
template class ImageCaptureEncoded<H265ToBGRDecoder>;
template class ImageCaptureEncoded<H265ToRGBDecoder>;

}  // namespace camera
}  // namespace sensors
}  // namespace holo
