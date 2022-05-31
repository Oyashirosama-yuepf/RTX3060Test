/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_capture_raw.h
 * @brief image raw data dirver
 * @author guoguangchao(guoguangchao@holomatic.com).
 * @date 2020-09-27
 */

#ifndef _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_CAPTURE_RAW_H
#define _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_CAPTURE_RAW_H

#include <holo/sensors/camera/capture/image_timestamper.h>
#include <holo/sensors/camera/image_ipc.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/sensors/camera/image_utils.h>
#include <functional>
#include <memory>

namespace holo
{
namespace sensors
{
namespace camera
{
template <ImageType Type>
class ImageCaptureRaw : public ImageTimestamperT<HoloSyncPacket>
{
public:
    using RawCallback = std::function<void(const ImagePacket&)>;

    ImageCaptureRaw(SensorId sensor_id, uint32_t cols, uint32_t rows, uint32_t fps, bool_t trigger_mode);
    void SetRawCallback(const RawCallback& handler) noexcept;
    void ParseData(const StreamBuffer& buffer);

private:
    SensorId    sensor_id_;
    uint32_t    frame_counter_;
    RawCallback raw_callback_;
    uint8_t     rawbuf_[IMAGE_RAW_SIZE_MAX];
    ImagePacket raw_image_;
};

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  // _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_CAPTURE_RAW_H
