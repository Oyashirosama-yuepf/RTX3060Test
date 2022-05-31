/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_encoder_xavier.h
 * @brief Image Encoder.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2020-07-31.
 */
#ifndef _HOLO_SENSORS_CAMERA_IMAGE_ENCODER_XAVIER_H
#define _HOLO_SENSORS_CAMERA_IMAGE_ENCODER_XAVIER_H

#include <holo/sensors/camera/encoder/image_encoder_base.h>
#include <holo/sensors/camera/image_gpu.h>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include "EGL/egl.h"
#include "EGL/eglext.h"
#include "NvCudaProc.h"
#include "NvVideoEncoder.h"
#include "nvbuf_utils.h"

namespace holo
{
namespace sensors
{
namespace camera
{
class ImageXavierEncoder : public ImageEncoderBase
{
public:
    ImageXavierEncoder(uint32_t cols, uint32_t rows, uint32_t fps) : ImageEncoderBase(cols, rows, fps, ImageType::H264);
    ~ImageXavierEncoder();
    void SetSender(const CompressDataSender& handler) noexcept;
    bool_t Encode(const Image& rgb_image);

private:
    bool_t        InitEncoder();
    static bool_t DqCallback(struct v4l2_buffer* v4l2_buf, NvBuffer* buffer, NvBuffer* shared_buffer, void* arg);

private:
    static const int32_t             START_SKIPPED_FRAMES;
    static int32_t                   frame_index_;
    static std::queue<TimestampPair> time_stamp_queue_;
    static CompressDataSender        encoded_sender_;
    static ImagePacket               encoded_data_;
    static NvVideoEncoder*           enc_;

    uint8_t*    cuda_yuv_;
    uint8_t*    cuda_rgb_;
    uint8_t*    yuv_image_data_;
    EGLDisplay  eglDisplay_;
    EGLImageKHR eglimg_;
};

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif
