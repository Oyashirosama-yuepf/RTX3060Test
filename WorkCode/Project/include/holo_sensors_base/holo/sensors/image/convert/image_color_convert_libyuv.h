/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_color_convert_libyuv.h.
 * @brief Image Color Convert By Libyuv.
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2022-1-25.
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_PROCESS_CONVERT_IMAGE_COLOR_CONVERT_LIBYUV_H
#define _HOLO_SENSORS_CAMERA_IMAGE_PROCESS_CONVERT_IMAGE_COLOR_CONVERT_LIBYUV_H

#include <holo/log/hololog.h>
#include <holo/common/image.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/sensors/camera/bayer_convert.h>
#include <libyuv.h>

namespace holo
{
namespace sensors
{
namespace image
{
namespace hololibyuv
{
holo::bool_t YUYV422ToNV12(uint8_t* yuyv422_data, uint8_t* nv12_data, const uint32_t cols, const uint32_t rows);
holo::bool_t YUYV422ToYUV420P(uint8_t* yuyv422_data, uint8_t* yuv420p_data, const uint32_t cols, const uint32_t rows);
holo::bool_t NV12ToYUV420P(uint8_t* nv12_data, uint8_t* yuv420p_data, const uint32_t cols, const uint32_t rows);
holo::bool_t YUV420PToRGB24(uint8_t* yuv420p_data, uint8_t* rgb24_data, const uint32_t cols, const uint32_t rows);
holo::bool_t YUV420PToNV12(uint8_t* yuv420p_data, uint8_t* nv12_data, const uint32_t cols, const uint32_t rows);
holo::bool_t RGB24ToYUV420P(uint8_t* rgb24_data, uint8_t* yuv420p_data, const uint32_t cols, const uint32_t rows);
holo::bool_t UYVY422ToNV12(uint8_t* uyvy422_data, uint8_t* nv12_data, const uint32_t cols, const uint32_t rows);

holo::bool_t YUYV422ToNV12(holo::Image& yuyv422_image, holo::Image& nv12_image);
holo::bool_t YUYV422ToYUV420P(holo::Image& yuyv422_image, holo::Image& yuv420p_image);
holo::bool_t NV12ToYUV420P(holo::Image& nv12_image, holo::Image& yuv420p_image);
holo::bool_t YUV420PToRGB24(holo::Image& yuv420p_image, holo::Image& rgb24_image);
holo::bool_t YUV420PToNV12(holo::Image& yuv420p_image, holo::Image& nv12_image);
holo::bool_t RGB24ToYUV420P(holo::Image& rgb24_image, holo::Image& yuv420p_image);
holo::bool_t UYVY422ToNV12(holo::Image& uyvy422_image, holo::Image& nv12_image);
}  // namespace hololibyuv
}  // namespace image
}  // namespace sensors
}  // namespace holo

#endif  //_HOLO_SENSORS_CAMERA_IMAGE_PROCESS_CONVERT_IMAGE_COLOR_CONVERT_LIBYUV_H