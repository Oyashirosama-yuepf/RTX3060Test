/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_decoder_h26x.h
 * @brief Image Decoder.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-11.
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_DECODER_H26X_H
#define _HOLO_SENSORS_CAMERA_IMAGE_DECODER_H26X_H

#include <chrono>
#include <condition_variable>
#include <map>
#include <mutex>
#include <queue>

#include <holo/sensors/camera/decoder/image_decoder_base.h>
#include <holo/sensors/image/resize/image_resize.h>
#if defined(HOLO_PLATFORM_TDA4)
#include <holo/sensors/camera/decoder/image_decoder_tda4.h>
#include <holo/sensors/camera/decoder/tda4_decode_vx_context.h>
#endif
#ifdef HOLO_PLATFORM_MDC610
#include <holo/sensors/camera/decoder/image_decoder_mdc610.h>
#endif

namespace holo
{
namespace sensors
{
namespace camera
{
template <ImageType InType>
class H26xDecoderCodecFinder
{
public:
    virtual AVCodec* FindDecoder() = 0;
};

template <>
class H26xDecoderCodecFinder<ImageType::H264>
{
public:
    AVCodec* FindDecoder();
};

template <>
class H26xDecoderCodecFinder<ImageType::H265>
{
public:
    AVCodec* FindDecoder();
};

template <ImageType InType, holo::Image::Encoding OutType>
class H26xDecoderBase : public ImageDecoderBase, public ImageDecoderData, public H26xDecoderCodecFinder<InType>
{
private:
    static constexpr size_t STAMP_QUEUE_CAPACITY = 60u;

public:
    H26xDecoderBase(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps, bool_t show_image = false);
    virtual ~H26xDecoderBase() noexcept;

private:
    bool_t FindDecoder();

protected:
    std::map<int64_t, int64_t> timestamp_map_;
    AVCodec*                   codec_;
    AVFrame*                   frame_;
    AVCodecContext*            codec_context_;
    AVPacket*                  pkt_;
};

template <ImageType InType, holo::Image::Encoding OutType = holo::Image::Encoding::RGB>
class H26xDecoder : public H26xDecoderBase<InType, OutType>
{
public:
    H26xDecoder() = delete;
    ImageType GetImageType() const noexcept override;
    holo::Image::Encoding GetEncoding() const noexcept override;
    static ImageType GetInputType();
    static holo::Image::Encoding GetOutputType();
};

template <ImageType InType>
class H26xDecoder<InType, holo::Image::Encoding::RGB> : public H26xDecoderBase<InType, holo::Image::Encoding::RGB>
{
public:
    using BASE = H26xDecoderBase<InType, holo::Image::Encoding::RGB>;

    H26xDecoder(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps, bool_t show_image = false);
    ImageType GetImageType() const noexcept override;
    holo::Image::Encoding GetEncoding() const noexcept override;
    static ImageType GetInputType();
    static holo::Image::Encoding GetOutputType();
    bool_t Decode(const ImagePacket& image_packet) override;
};

template <ImageType InType>
class H26xDecoder<InType, holo::Image::Encoding::BGR> : public H26xDecoderBase<InType, holo::Image::Encoding::BGR>
{
public:
    using BASE = H26xDecoderBase<InType, holo::Image::Encoding::BGR>;

    H26xDecoder(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps, bool_t show_image = false);
    ImageType GetImageType() const noexcept override;
    holo::Image::Encoding GetEncoding() const noexcept override;
    static ImageType GetInputType();
    static holo::Image::Encoding GetOutputType();
    bool_t Decode(const ImagePacket& image_packet) override;
};

template <ImageType InType>
class H26xDecoder<InType, holo::Image::Encoding::NV12> : public H26xDecoderBase<InType, holo::Image::Encoding::NV12>
{
public:
    using BASE = H26xDecoderBase<InType, holo::Image::Encoding::NV12>;

    H26xDecoder(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps, bool_t show_image = false);
    ImageType GetImageType() const noexcept override;
    holo::Image::Encoding GetEncoding() const noexcept override;
    static ImageType GetInputType();
    static holo::Image::Encoding GetOutputType();
    bool_t Decode(const ImagePacket& image_packet) override;
};

#if defined(HOLO_PLATFORM_TDA4)
template <>
class H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>
  : public ImageDecoderBase, public ImageDecoderData, public Tda4DecodeVxContext
{
public:
    H26xDecoder(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps, bool_t show_image = false);
    ~H26xDecoder();
    ImageType GetImageType() const noexcept override;
    holo::Image::Encoding GetEncoding() const noexcept override;
    static ImageType GetInputType();
    static holo::Image::Encoding GetOutputType();
    bool_t Decode(const ImagePacket& image_packet) override;

private:
    std::queue<TimestampPair> timestamp_cache_;
    bool_t                    skip_this_frame_;
    App_decode_Obj            dec_;
};
#endif
#ifdef HOLO_PLATFORM_MDC610
template <>
class H26xDecoder<ImageType::H265, holo::Image::Encoding::RGB>
  : public ImageDecoderBase, public ImageDecoderData, public ImageDecoderDvpp
{
public:
    H26xDecoder(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps, bool_t show_image = false);
    ImageType GetImageType() const noexcept override;
    holo::Image::Encoding GetEncoding() const noexcept override;
    static ImageType GetInputType();
    static holo::Image::Encoding GetOutputType();
    bool_t Decode(const ImagePacket& image_packet) override;

private:
    bool_t                    found_first_key_frame_;
    std::queue<TimestampPair> timestamp_cache_;
};

template <>
class H26xDecoder<ImageType::H265, holo::Image::Encoding::BGR>
  : public ImageDecoderBase, public ImageDecoderData, public ImageDecoderDvpp
{
public:
    H26xDecoder(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps, bool_t show_image = false);
    ImageType GetImageType() const noexcept override;
    holo::Image::Encoding GetEncoding() const noexcept override;
    static ImageType GetInputType();
    static holo::Image::Encoding GetOutputType();
    bool_t Decode(const ImagePacket& image_packet) override;

private:
    bool_t                    found_first_key_frame_;
    std::queue<TimestampPair> timestamp_cache_;
};

template <>
class H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>
  : public ImageDecoderBase, public ImageDecoderData, public ImageDecoderDvpp
{
public:
    H26xDecoder(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps, bool_t show_image = false);
    ImageType GetImageType() const noexcept override;
    holo::Image::Encoding GetEncoding() const noexcept override;
    static ImageType GetInputType();
    static holo::Image::Encoding GetOutputType();
    bool_t Decode(const ImagePacket& image_packet) override;

private:
    bool_t                    found_first_key_frame_;
    std::queue<TimestampPair> timestamp_cache_;
};
#endif

using H264ToNv12Decoder = H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>;
using H264ToBGRDecoder  = H26xDecoder<ImageType::H264, holo::Image::Encoding::BGR>;
using H264ToRGBDecoder  = H26xDecoder<ImageType::H264, holo::Image::Encoding::RGB>;

using H265ToNv12Decoder = H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>;
using H265ToBGRDecoder  = H26xDecoder<ImageType::H265, holo::Image::Encoding::BGR>;
using H265ToRGBDecoder  = H26xDecoder<ImageType::H265, holo::Image::Encoding::RGB>;

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  // _HOLO_SENSORS_CAMERA_IMAGE_DECODER_H26X_H
