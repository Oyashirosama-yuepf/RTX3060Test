/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file converter_yuyv.h.
 * @brief converter yuyv format
 * @author guoguangchao(guoguangchao@holomatic.com).
 * @date 2020-09-27
 */

#ifndef _HOLO_SENSORS_CAMERA_CAPTURE_CONVERTER_YUYV_H
#define _HOLO_SENSORS_CAMERA_CAPTURE_CONVERTER_YUYV_H

#if defined(HOLO_PLATFORM_MDC610)
#include "core/logger.h"
#include "core/types.h"
#include "core/status.h"
#include "core/stream.h"
#include "acl/acl.h"
#include "acl/acl_base.h"
#endif

#include <holo/sensors/camera/image_structure.h>
#include <holo/sensors/camera/image_utils.h>
#ifdef HOLO_CAMERA_USE_CUDA
#include <holo/sensors/camera/image_gpu.h>
#endif

namespace holo
{
namespace sensors
{
namespace camera
{
class ImageConverterBase
{
public:
    ImageConverterBase(uint32_t cols, uint32_t rows, Image::Encoding encoding);
    virtual ~ImageConverterBase() = default;
    Image::Encoding GetEncoding() const;
    virtual bool_t Convert(const StreamBuffer& buffer, Image& image) = 0;

protected:
    const uint32_t        cols_;
    const uint32_t        rows_;
    const Image::Encoding encoding_;
};

class Bayer8Converter : public ImageConverterBase
{
public:
    Bayer8Converter(uint32_t cols, uint32_t rows);
    ~Bayer8Converter() noexcept;

    bool_t Convert(const StreamBuffer& buffer, Image& image);

private:
    uint8_t* bayer8_;
};

#if defined(HOLO_CAMERA_USE_CUDA)
class YuyvConverter_CUDA : public ImageConverterBase
{
public:
    YuyvConverter_CUDA(uint32_t cols, uint32_t rows);
    ~YuyvConverter_CUDA();

    bool_t Convert(const StreamBuffer& buffer, Image& image);

private:
    uint8_t* cuda_yuyv_;
    uint8_t* cuda_rgb_;
};
#endif

class YuyvConverter_CPU : public ImageConverterBase
{
public:
    YuyvConverter_CPU(uint32_t cols, uint32_t rows);
    ~YuyvConverter_CPU() = default;

    bool_t Convert(const StreamBuffer& buffer, Image& image);
};

class RawToNv12Converter : public ImageConverterBase
{
public:
    RawToNv12Converter(uint32_t cols, uint32_t rows);
    ~RawToNv12Converter() = default;

    bool_t Convert(const StreamBuffer& buffer, Image& image);

private:
    uint32_t target_size_;
};

class UyvyToNv12Converter : public ImageConverterBase
{
public:
    UyvyToNv12Converter(uint32_t cols, uint32_t rows);
    ~UyvyToNv12Converter() = default;

    bool_t Convert(const StreamBuffer& buffer, Image& image);

private:
    uint32_t target_size_;
};

class Nv12ToBgrConverter_OPENCV : public ImageConverterBase
{
public:
    Nv12ToBgrConverter_OPENCV(uint32_t cols, uint32_t rows);
    ~Nv12ToBgrConverter_OPENCV() = default;
    bool_t Convert(const StreamBuffer& buffer, Image& image);

private:
    const uint32_t target_size_;
};

// #if defined(HOLO_PLATFORM_MDC610)
// class Nv12ToBgrConverter_ADSF : public ImageConverterBase
// {
// public:
//     Nv12ToBgrConverter_ADSF(uint32_t cols, uint32_t rows);
//     ~Nv12ToBgrConverter_ADSF();
//     bool_t Convert(const StreamBuffer& buffer, Image& image);

// private:
//     const uint32_t              target_size_;
//     int32_t                     counter_;
//     Adsfi::HafContextParameters context_param_;
//     Adsfi::HafContext           context_;
//     struct acldvppChannelDesc*  channel_desc_;
//     Adsfi::HafStream            stream_;
// };
// #endif

#if defined(HOLO_CAMERA_USE_CUDA)
using YuyvConverter = YuyvConverter_CUDA;
#else
using YuyvConverter = YuyvConverter_CPU;
#endif

#if defined(HOLO_PLATFORM_MDC610)
// using Nv12ToBgrConverter = Nv12ToBgrConverter_ADSF;
using Nv12ToBgrConverter = Nv12ToBgrConverter_OPENCV;
#else
using Nv12ToBgrConverter = Nv12ToBgrConverter_OPENCV;
#endif

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  // _HOLO_SENSORS_CAMERA_CAPTURE_CONVERTER_YUYV_H
