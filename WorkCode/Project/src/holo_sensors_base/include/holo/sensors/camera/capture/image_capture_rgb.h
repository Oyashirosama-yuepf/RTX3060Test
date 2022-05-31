/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_capture_rgb.h
 * @brief Image rgb driver
 * @author guoguangchao(guoguangchao@holomatic.com).
 * @date 2020-09-27
 */

#ifndef _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_CAPTURE_RGB_H
#define _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_CAPTURE_RGB_H

#include <functional>
#include <memory>

#include <holo/sensors/camera/capture/image_converter.h>
#include <holo/sensors/camera/capture/image_timestamper.h>
#include <holo/sensors/camera/encoder/image_encoder.h>
#include <holo/sensors/camera/image_ipc.h>
#include <holo/sensors/image/resize/image_resize.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/sensors/camera/image_utils.h>

namespace holo
{
namespace sensors
{
namespace camera
{
using Timestamp = holo::common::Timestamp;

template <typename Tcvt, typename Tenc = DummyEncoder>
class ImageCaptureBasic : public Tcvt, public Tenc
{
public:
    using ImageCallbackType   = std::function<void(const holo::Image&)>;
    using CounterCallbackType = std::function<void(uint32_t)>;

    ImageCaptureBasic(SensorId sensor_id, uint32_t cols, uint32_t rows, uint32_t fps, bool_t show_image = false);
    virtual ~ImageCaptureBasic() = default;
    void SetImageCallback(const ImageCallbackType& handler) noexcept;
    [[deprecated("ImageCapture removed IPC functionality")]] void SetImageCounterCallback(const CounterCallbackType& handler) noexcept;
    void ParseData(const StreamBuffer& buffer, const Timestamp& received_stamp, const Timestamp& trigger_stamp);
    void SetOutputVideoSize(uint32_t output_video_cols, uint32_t output_video_rows);

private:
    uint32_t                  cols_;
    uint32_t                  rows_;
    uint32_t                  output_video_cols_;
    uint32_t                  output_video_rows_;
    SensorId                  sensor_id_;
    bool_t                    show_image_;
    ImageCallbackType         image_callback_;
    CounterCallbackType       image_counter_callback_;
    Image                     rgb_image_;
};

template <typename Tcvt, typename Tenc = DummyEncoder, typename Tsync = HoloSyncDiffPacket>
class ImageCaptureRgbT : public ImageCaptureBasic<Tcvt, Tenc>, public ImageTimestamperT<Tsync>
{
public:
    ImageCaptureRgbT(SensorId sensor_id, uint32_t cols, uint32_t rows, uint32_t fps, bool_t trigger_mode,
                     bool_t show_image = false);
    ~ImageCaptureRgbT() = default;
    void ParseData(const StreamBuffer& buffer, const Timestamp& image_stamp);
};

template <typename Tcvt, typename Tenc = DummyEncoder>
class ImageCaptureVirtual : public ImageCaptureBasic<Tcvt, Tenc>
{
public:
    ImageCaptureVirtual(SensorId sensor_id, uint32_t cols, uint32_t rows, uint32_t fps, bool_t show_image = false);
    ~ImageCaptureVirtual() = default;
    void ParseData(const StreamBuffer& buffer, const Timestamp& image_stamp, const Timestamp& trigger_stamp);
};

template <typename Tcvt, typename Tenc = DummyEncoder>
using ImageCaptureRgb = ImageCaptureRgbT<Tcvt, Tenc, HoloSyncPacket>;

template <typename Tcvt, typename Tenc = DummyEncoder>
using ImageCaptureRgbDPMode = ImageCaptureRgbT<Tcvt, Tenc, HoloSyncDiffPacket>;
}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  // _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_CAPTURE_RGB_H