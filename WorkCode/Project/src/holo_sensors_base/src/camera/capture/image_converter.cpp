/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_converter.cpp.
 * @brief Image Converter Driver.
 * @author guoguangchao(guoguangchao@holomatic.com).
 * @date 2021-06-19
 */

// #if defined(HOLO_PLATFORM_MDC610)
// #include <core/memory.h>
// #include <imageprocess/convert_color.h>
// #endif

#include <holo/log/hololog.h>
#include <holo/sensors/camera/capture/image_converter.h>
#include <holo/sensors/image/convert/image_color_convert.hpp>

namespace holo
{
namespace sensors
{
namespace camera
{
ImageConverterBase::ImageConverterBase(uint32_t cols, uint32_t rows, Image::Encoding encoding)
    : cols_(cols), rows_(rows), encoding_(encoding)
{
}

Image::Encoding ImageConverterBase::GetEncoding() const
{
    return encoding_;
}

Bayer8Converter::Bayer8Converter(uint32_t cols, uint32_t rows)
    : ImageConverterBase(cols, rows, Image::Encoding::RGB), bayer8_(nullptr)
{
    bayer8_ = static_cast<uint8_t*>(std::malloc(rows_ * cols_ * 3));
}

Bayer8Converter::~Bayer8Converter() noexcept
{
    if (bayer8_)
    {
        free(bayer8_);
    }
}

bool_t Bayer8Converter::Convert(const StreamBuffer& buffer, Image& image)
{
    Bayer162Bayer8(static_cast<int16_t*>(buffer.start), bayer8_, cols_, rows_, 4);
    Bayer2Rgb24(bayer8_, image.GetData(), cols_, rows_, 1);
    return true;
}

#if defined(HOLO_CAMERA_USE_CUDA)
YuyvConverter_CUDA::YuyvConverter_CUDA(uint32_t cols, uint32_t rows)
  : ImageConverterBase(cols, rows, Image::Encoding::RGB), cuda_yuyv_(nullptr), cuda_rgb_(nullptr)
{
    if (cudaMalloc((void**)&cuda_yuyv_, rows * cols * 2) != cudaSuccess)
    {
        std::string error = "could not set cuda yuyv memory";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
    if (cudaMalloc((void**)&cuda_rgb_, rows * cols * 3) != cudaSuccess)
    {
        std::string error = "could not set cuda rgb memory";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
}

YuyvConverter_CUDA::~YuyvConverter_CUDA()
{
    if (cuda_rgb_)
    {
        cudaFree(cuda_rgb_);
    }
    if (cuda_yuyv_)
    {
        cudaFree(cuda_yuyv_);
    }
}

bool_t YuyvConverter_CUDA::Convert(const StreamBuffer& buffer, Image& image)
{
    if (buffer.size != static_cast<uint32_t>(rows_ * cols_ * 2))
    {
        LOG(WARNING) << "invalid buffer size: " << buffer.size << " != " << rows_ * cols_ * 2;
        return false;
    }
    CudaYUYVToRGB(cols_, rows_, cuda_yuyv_, cuda_rgb_, static_cast<uint8_t*>(buffer.start), image.GetData());
    return true;
}
#endif

YuyvConverter_CPU::YuyvConverter_CPU(uint32_t cols, uint32_t rows)
    : ImageConverterBase(cols, rows, Image::Encoding::RGB)
{
    InitYuvTable();
}

bool_t YuyvConverter_CPU::Convert(const StreamBuffer& buffer, Image& image)
{
    if (buffer.size != static_cast<uint32_t>(rows_ * cols_ * 2))
    {
        LOG(WARNING) << "invalid buffer size: " << buffer.size << " != " << rows_ * cols_ * 2;
        return false;
    }
    Yuyv2Rgb(static_cast<uint8_t*>(buffer.start), rows_, cols_, image.GetData());
    return true;
}

RawToNv12Converter::RawToNv12Converter(uint32_t cols, uint32_t rows)
    : ImageConverterBase(cols, rows, Image::Encoding::NV12), target_size_(cols * rows * 3 / 2)
{
}

bool_t RawToNv12Converter::Convert(const StreamBuffer& buffer, Image& image)
{
    if (buffer.init == false)
    {
        return false;
    }
    if (buffer.size != target_size_)
    {
        return false;
    }
    (void)std::memcpy(image.GetData(), buffer.start, buffer.size);
    return true;
}

UyvyToNv12Converter::UyvyToNv12Converter(uint32_t cols, uint32_t rows)
    : ImageConverterBase(cols, rows, Image::Encoding::NV12), target_size_(cols * rows * 3 / 2)
{
}

bool_t UyvyToNv12Converter::Convert(const StreamBuffer& buffer, Image& image)
{
    if (buffer.init == false)
    {
        return false;
    }
    if (buffer.size * 3 / 4 != target_size_)
    {
        return false;
    }
    holo::sensors::image::UYVY422ToNV12(static_cast<uint8_t*>(buffer.start), image.GetData(), cols_, rows_);
    return true;
}


Nv12ToBgrConverter_OPENCV::Nv12ToBgrConverter_OPENCV(uint32_t cols, uint32_t rows)
    : ImageConverterBase(cols, rows, holo::Image::Encoding::BGR)
    , target_size_(cols * rows * 3)
{
}

bool_t Nv12ToBgrConverter_OPENCV::Convert(const StreamBuffer& buffer, Image& image)
{
    if (buffer.init == false)
    {
        return false;
    }
    if (buffer.size * 2 != target_size_)
    {
        return false;
    }
    cv::Mat in(rows_, cols_* 1.5, CV_8UC1, buffer.start);
    cv::Mat out(rows_, cols_, CV_8UC1);
    cv::cvtColor(in, out, CV_YUV2BGR_NV12);
    (void)std::memcpy(image.GetData(), out.data, target_size_);
    return true;
}

// #if defined(HOLO_PLATFORM_MDC610)
// Nv12ToBgrConverter_ADSF::Nv12ToBgrConverter_ADSF(uint32_t cols, uint32_t rows)
//     : ImageConverterBase(cols, rows, holo::Image::Encoding::BGR)
//     , target_size_(cols * rows * 3)
//     , counter_(0)
// {
//     if (Adsfi::HafStatus::HAF_SUCCESS != Adsfi::HafInitialize(context_, context_param_))
//     {
//         std::string error = "failed to create contex";
//         LOG(ERROR) << error;
//         throw std::runtime_error(error);
//     }
//     if (Adsfi::HafStatus::HAF_SUCCESS != Adsfi::HafStreamCreate(stream_))
//     {
//         std::string error = "failed to create stream";
//         LOG(ERROR) << error;
//         throw std::runtime_error(error);
//     }
//     channel_desc_ = Adsfi::HafCreateChannelDesc();
//     if (channel_desc_ == nullptr)
//     {
//         std::string error = "failed to create channel desc";
//         LOG(ERROR) << error;
//         throw std::runtime_error(error);
//     }
// }

// Nv12ToBgrConverter_ADSF::~Nv12ToBgrConverter_ADSF()
// {
//     (void)Adsfi::HafSetCurrentContext(context_);
//     (void)Adsfi::HafDestroyChannelDesc(&channel_desc_);
//     (void)Adsfi::HafStreamDestroy(stream_);
//     (void)Adsfi::HafRelease(context_);
// }

// bool_t Nv12ToBgrConverter_ADSF::Convert(const StreamBuffer& buffer, Image& image)
// {
//     if (buffer.init == false)
//     {
//         return false;
//     }
//     if (buffer.size * 2 != target_size_)
//     {
//         return false;
//     }
//     if (Adsfi::HafStatus::HAF_SUCCESS != Adsfi::HafSetCurrentContext(context_))
//     {
//         return false;
//     }
//     Adsfi::ImageData inputImage;
//     inputImage.width      = cols_;
//     inputImage.height     = rows_;
//     inputImage.dataSize   = buffer.size;
//     inputImage.bufferType = Adsfi::HafBufferType::HAF_BUFFER_CPU;
//     inputImage.imageType  = Adsfi::HafImageType::HAF_IMAGE_YUV420SP_NV12_UINT8;
//     inputImage.seq        = counter_++;
//     inputImage.rawData    = static_cast<uint8_t*>(buffer.start);
//     Adsfi::ImageData outputImage;
//     outputImage.bufferType = Adsfi::HafBufferType::HAF_BUFFER_DVPP;
//     outputImage.imageType  = Adsfi::HafImageType::HAF_IMAGE_BGR_UINT8;
//     Adsfi::HafStatus status = Adsfi::HafImageCvtColor(channel_desc_, inputImage, outputImage, stream_);
//     if (Adsfi::HafStatus::HAF_SUCCESS != status)
//     {
//         LOG(ERROR) << "failed to convert color by dvpp";
//         return false;
//     }
//     /* @TODO: judge size of image data */
//     bool_t ret = true;
//     status = Adsfi::HafMemcpy(image.GetData(), target_size_, outputImage.rawData, outputImage.dataSize,
//         Adsfi::HafMemcpyKind::HAF_MEM_COPY_DEVICE_TO_HOST);
//     if (Adsfi::HafStatus::HAF_SUCCESS != status)
//     {
//         LOG(ERROR) << "failed to copy data from device to host";
//         ret = false;
//     }
//     (void)Adsfi::HafImageDestroy(inputImage);
//     (void)Adsfi::HafImageDestroy(outputImage);
//     return ret;
// }
// #endif

}  // namespace camera
}  // namespace sensors
}  // namespace holo
