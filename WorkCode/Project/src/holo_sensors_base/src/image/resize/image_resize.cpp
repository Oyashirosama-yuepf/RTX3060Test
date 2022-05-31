/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_resize.cpp.
 * @brief Image Resize.
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-12-11.
 */

#include <holo/sensors/image/resize/image_resize.h>

namespace holo
{
namespace sensors
{
namespace image
{
static libyuv::FilterMode ResizeMode2FilterMode(enum ImageResizeMode image_resize_mode)
{
    switch (image_resize_mode)
    {
    case ImageResizeMode::QUALITY_LOW:
        return libyuv::FilterMode::kFilterNone;
        break;
    case ImageResizeMode::QUALITY_MEDIUM:
        return libyuv::FilterMode::kFilterLinear;
        break;
    case ImageResizeMode::QUALITY_HIGH:
        return libyuv::FilterMode::kFilterBilinear;
        break;
    case ImageResizeMode::QUALITY_HIGHEST:
        return libyuv::FilterMode::kFilterBox;
        break;
    default:
        return libyuv::FilterMode::kFilterBilinear;
        break;
    }
}

bool_t RGB24Resize(uint8_t* src_data, uint8_t* dst_data, 
                   uint16_t src_cols, uint16_t src_rows, 
                   uint16_t dst_cols, uint16_t dst_rows,
                   enum ImageResizeMode image_resize_mode)
{
    if (nullptr == src_data)
    {
        LOG(ERROR) << "RGB24Resize src_data is nullptr";
        return false;
    }
    if (nullptr == dst_data)
    {
        LOG(ERROR) << "RGB24Resize dst_data is nullptr";
        return false;
    }

    cv::resize(cv::Mat(src_rows, src_cols, CV_8UC3, src_data), 
               cv::Mat(dst_rows, dst_cols, CV_8UC3, dst_data),
               cv::Size(dst_cols, dst_rows), 0, 0,
               image_resize_mode);

    return true;

}

bool_t BGR24Resize(uint8_t* src_data, uint8_t* dst_data, 
                     uint16_t src_cols, uint16_t src_rows, 
                     uint16_t dst_cols, uint16_t dst_rows,
                     enum ImageResizeMode image_resize_mode)
{
    if (nullptr == src_data)
    {
        LOG(ERROR) << "BGR24Resize src_data is nullptr";
        return false;
    }
    if (nullptr == dst_data)
    {
        LOG(ERROR) << "BGR24Resize dst_data is nullptr";
        return false;
    }

    cv::resize(cv::Mat(src_rows, src_cols, CV_8UC3, src_data), 
               cv::Mat(dst_rows, dst_cols, CV_8UC3, dst_data),
               cv::Size(dst_cols, dst_rows), 0, 0,
               image_resize_mode);

    return true;

}

bool_t NV12Resize(uint8_t* src_data, uint8_t* dst_data, 
                  uint16_t src_cols, uint16_t src_rows, 
                  uint16_t dst_cols, uint16_t dst_rows,
                  enum ImageResizeMode image_resize_mode)
{
    if (nullptr == src_data)
    {
        LOG(ERROR) << "NV12Resize src_data is nullptr";
        return false;
    }
    if (nullptr == dst_data)
    {
        LOG(ERROR) << "NV12Resize dst_data is nullptr";
        return false;
    }

    int32_t result = libyuv::NV12Scale(src_data, src_cols, 
                                       src_data + src_cols * src_rows, src_cols,
                                       src_cols, src_rows,
                                       dst_data, dst_cols,
                                       dst_data + dst_cols * dst_rows, dst_cols,
                                       dst_cols, dst_rows,
                                       ResizeMode2FilterMode(image_resize_mode));

    return (0 == result);
}

bool_t YUV420PResize(uint8_t* src_data, uint8_t* dst_data, 
                     uint16_t src_cols, uint16_t src_rows, 
                     uint16_t dst_cols, uint16_t dst_rows,
                     enum ImageResizeMode image_resize_mode)
{
    if (nullptr == src_data)
    {
        LOG(ERROR) << "YUV420PResize src_data is nullptr";
        return false;
    }
    if (nullptr == dst_data)
    {
        LOG(ERROR) << "YUV420PResize dst_data is nullptr";
        return false;
    }

    int32_t result = libyuv::I420Scale(src_data, src_cols,
                                       src_data + src_cols * src_rows, src_cols / 2,
                                       src_data + src_cols * src_rows * 5 / 4, src_cols / 2,
                                       src_cols, src_rows,
                                       dst_data, dst_cols,
                                       dst_data + dst_cols * dst_rows, dst_cols / 2,
                                       dst_data + dst_cols * dst_rows * 5 / 4, dst_cols / 2,
                                       dst_cols, dst_rows,
                                       ResizeMode2FilterMode(image_resize_mode));

    return (0 == result);
}

bool_t RGB24Resize(const holo::Image& src_image, holo::Image& dst_image,
                   enum ImageResizeMode image_resize_mode)
{
    if (nullptr == src_image.GetData())
    {
        LOG(ERROR) << "RGB24Resize src_image is invalid";
        return false;
    }
    if (nullptr == dst_image.GetData())
    {
        LOG(ERROR) << "RGB24Resize dst_image is invalid";
        return false;
    }

    cv::resize(src_image.GetCvType(), 
               dst_image.GetCvType(),
               cv::Size(dst_image.GetWidth(), dst_image.GetHeight()), 0, 0,
               image_resize_mode);

    return true;
}

bool_t BGR24Resize(const holo::Image& src_image, holo::Image& dst_image,
                     enum ImageResizeMode image_resize_mode)
{
    if (nullptr == src_image.GetData())
    {
        LOG(ERROR) << "BGR24Resize src_image is invalid";
        return false;
    }
    if (nullptr == dst_image.GetData())
    {
        LOG(ERROR) << "BGR24Resize dst_image is invalid";
        return false;
    }

    cv::resize(src_image.GetCvType(), 
               dst_image.GetCvType(),
               cv::Size(dst_image.GetWidth(), dst_image.GetHeight()), 0, 0,
               image_resize_mode);

    return true;
}

bool_t NV12Resize(const holo::Image& src_image, holo::Image& dst_image,
                  enum ImageResizeMode image_resize_mode)
{
    if (nullptr == src_image.GetData())
    {
        LOG(ERROR) << "NV12Resize src_image is invalid";
        return false;
    }
    if (nullptr == dst_image.GetData())
    {
        LOG(ERROR) << "NV12Resize dst_image is invalid";
        return false;
    }

    int32_t result = libyuv::NV12Scale(src_image.GetData(), src_image.GetWidth(), 
                                       src_image.GetData() + src_image.GetWidth() * src_image.GetHeight() * 2 / 3,
                                       src_image.GetWidth(),
                                       src_image.GetWidth(), src_image.GetHeight() * 2 / 3,
                                       dst_image.GetData(), dst_image.GetWidth(),
                                       dst_image.GetData() + dst_image.GetWidth() * dst_image.GetHeight() * 2 / 3, 
                                       dst_image.GetWidth(),
                                       dst_image.GetWidth(), dst_image.GetHeight() * 2 / 3,
                                       ResizeMode2FilterMode(image_resize_mode));

    return (0 == result);
}

bool_t YUV420PResize(const holo::Image& src_image, holo::Image& dst_image,
                     enum ImageResizeMode image_resize_mode)
{
    if (nullptr == src_image.GetData())
    {
        LOG(ERROR) << "YUV420PResize src_image is invalid";
        return false;
    }
    if (nullptr == dst_image.GetData())
    {
        LOG(ERROR) << "YUV420PResize dst_image is invalid";
        return false;
    }

    int32_t result = libyuv::I420Scale(src_image.GetData(), src_image.GetWidth(),
                                       src_image.GetData() + src_image.GetWidth() * src_image.GetHeight() * 2 / 3, 
                                       src_image.GetWidth() / 2,
                                       src_image.GetData() + (src_image.GetWidth() * src_image.GetHeight() * 2 / 3) * 5 / 4, 
                                       src_image.GetWidth() / 2,
                                       src_image.GetWidth(), 
                                       src_image.GetHeight() * 2 / 3,
                                       dst_image.GetData(), dst_image.GetWidth(),
                                       dst_image.GetData() + dst_image.GetWidth() * dst_image.GetHeight() * 2 / 3, 
                                       dst_image.GetWidth() / 2,
                                       dst_image.GetData() + (dst_image.GetWidth() * dst_image.GetHeight() * 2 / 3) * 5 / 4, 
                                       dst_image.GetWidth() / 2,
                                       dst_image.GetWidth(), dst_image.GetHeight() * 2 / 3,
                                       ResizeMode2FilterMode(image_resize_mode));

    return (0 == result);
}
}  // namespace image
}  // namespace sensors
}  // namespace holo