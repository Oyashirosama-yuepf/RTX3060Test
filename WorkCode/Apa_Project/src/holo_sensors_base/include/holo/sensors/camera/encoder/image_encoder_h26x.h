/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_encoder_h26x.h.
 * @brief Image Encoder.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-11.
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_ENCODER_H26X_H
#define _HOLO_SENSORS_CAMERA_IMAGE_ENCODER_H26X_H

#include <queue>

extern "C" {
#include <jpeglib.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}
#include <holo/sensors/camera/encoder/image_encoder_base.h>
#if defined(HOLO_PLATFORM_TDA4)
#include <holo/sensors/camera/encoder/image_encoder_tda4.h>
#include <holo/sensors/camera/encoder/tda4_encode_vx_context.h>
#elif defined(HOLO_PLATFORM_MDC610)
#include <holo/sensors/camera/encoder/image_encoder_mdc610.h>
#endif
#if defined(HOLO_CAMERA_USE_TEGRA_MMA)
#include <holo/sensors/camera/encoder/image_encoder_xavier.h>
#endif

#ifdef HOLO_CAMERA_USE_CUDA
#include <holo/sensors/camera/image_gpu.h>
#endif

namespace holo
{
namespace sensors
{
namespace camera
{
template <ImageType InType>
class H26xEncoderCodecFinder
{
public:
    virtual AVCodec* FindEncoder() = 0;
};

template <>
class H26xEncoderCodecFinder<ImageType::H264>
{
public:
    AVCodec* FindEncoder();
};

template <>
class H26xEncoderCodecFinder<ImageType::H265>
{
public:
    AVCodec* FindEncoder();
};

template <holo::Image::Encoding InType, ImageType OutType>
class ImageEncoder : public H26xEncoderCodecFinder<OutType>, public ImageEncoderBase
{
private:
    static constexpr uint32_t IMAGE_PIXELS_NUM_8MP    = 3840u * 2160u;
    static constexpr int64_t  H26X_BIT_RATE_UNDER_8MP = 3000000u;
    static constexpr int64_t  H26X_BIT_RATE_8MP       = 36000000u;
    static constexpr uint32_t ENCODE_THREAD_NUM       = 4;

public:
    ImageEncoder(uint32_t cols, uint32_t rows, uint32_t fps, uint32_t bitrate = H26X_BIT_RATE_8MP);
    ~ImageEncoder() noexcept;

    bool_t Encode(const Image& image);

private:
    bool_t Image2Ffmpeg(const Image& image);
    bool_t FfmpegEncode(AVFrame* frame);

private:
    uint32_t                  counter_;
    uint32_t                  pts_counter_;
    std::queue<TimestampPair> timestamp_queue_;
    AVCodec*                  codec_;
    AVCodecContext*           codec_context_;
    AVFrame*                  av_frame_;
    AVPacket*                 pkt_;
    uint8_t*                  out_buf_;
    uint8_t*                  frame_buf_;
#if defined(HOLO_CAMERA_USE_CUDA)
    uint8_t* cuda_yuv_;
    uint8_t* cuda_rgb_;
#endif
};

#if defined(HOLO_PLATFORM_TDA4)
class Tda4ImageEncoder : public ImageEncoderBase, public Tda4EncodeVxContext
{
public:
    Tda4ImageEncoder(uint32_t cols, uint32_t rows, uint32_t fps);
    ~Tda4ImageEncoder();

    bool_t Encode(const Image& image);

private:
    static const uint32_t DEFAULT_IPERIOD = 1;
    static const uint32_t DEFAULT_BITRATE = 10000000;
    App_encode_obj        enc_;
    uint32_t              counter_;
    uint32_t              iperiod_;
    uint32_t              bitrate_;
};
#endif

#if defined(HOLO_CAMERA_USE_TEGRA_MMA)
using H264Encoder = ImageXavierEncoder;
#else
using H264Encoder       = ImageEncoder<holo::Image::Encoding::RGB, ImageType::H264>;
#endif
using RgbToH264Encoder = H264Encoder;
using RgbToH265Encoder = ImageEncoder<holo::Image::Encoding::RGB, ImageType::H265>;

#if defined(HOLO_PLATFORM_TDA4)
using Nv12ToH264Encoder = Tda4ImageEncoder;
#else
using Nv12ToH264Encoder = ImageEncoder<holo::Image::Encoding::NV12, ImageType::H264>;
#endif

#if defined(HOLO_PLATFORM_MDC610)
using Nv12ToH265Encoder = ImageEncoderDvpp<holo::Image::Encoding::NV12>;
#else
using Nv12ToH265Encoder = ImageEncoder<holo::Image::Encoding::NV12, ImageType::H265>;
#endif

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif
