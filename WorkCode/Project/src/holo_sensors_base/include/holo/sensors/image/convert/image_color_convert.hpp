/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_color_convert.h.
 * @brief Image Color Convert.
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2022-1-25.
 */

/**
 * If you are not familiar with image manipulation, 
 * it is recommended that you use an overload with the parameter holo:: image
 * RGB24   -> holo::Image::Encoding::RGB
 * BGR24   -> holo::Image::Encoding::BGR
 * YUYV422 -> holo::Image::Encoding::YUYV
 * YUV420P -> holo::Image::Encoding::YU12
 * NV12    -> holo::Image::Encoding::NV12
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_PROCESS_CONVERT_IMAGE_COLOR_CONVERT_H
#define _HOLO_SENSORS_CAMERA_IMAGE_PROCESS_CONVERT_IMAGE_COLOR_CONVERT_H

#include <holo/sensors/image/convert/image_color_convert_libyuv.h>
#include <holo/sensors/image/convert/image_color_convert_opencv.h>

namespace holo
{
namespace sensors
{
namespace image
{
//YUYV422ToRGB24
inline holo::bool_t YUYV422ToRGB24(uint8_t* yuyv422_data, uint8_t* rgb24_data, const uint32_t cols, const uint32_t rows)
{
    return holoopencv::YUYV422ToRGB24(yuyv422_data, rgb24_data, cols, rows);
}
//YUYV422ToBGR24
inline holo::bool_t YUYV422ToBGR24(uint8_t* yuyv422_data, uint8_t* bgr24_data, const uint32_t cols, const uint32_t rows)
{
    return holoopencv::YUYV422ToBGR24(yuyv422_data, bgr24_data, cols, rows);
}
//YUYV422ToNV12
inline holo::bool_t YUYV422ToNV12(uint8_t* yuyv422_data, uint8_t* nv12_data, const uint32_t cols, const uint32_t rows)
{
    return hololibyuv::YUYV422ToNV12(yuyv422_data, nv12_data, cols, rows);
}
//YUYV422ToYUV420P
inline holo::bool_t YUYV422ToYUV420P(uint8_t* yuyv422_data, uint8_t* yuv420p_data, const uint32_t cols, const uint32_t rows)
{
    return hololibyuv::YUYV422ToYUV420P(yuyv422_data, yuv420p_data, cols, rows);
}
//NV12ToRGB24
inline holo::bool_t NV12ToRGB24(uint8_t* nv12_data, uint8_t* rgb24_data, const uint32_t cols, const uint32_t rows)
{
    return holoopencv::NV12ToRGB24(nv12_data, rgb24_data, cols, rows);
}
//NV12ToBGR24
inline holo::bool_t NV12ToBGR24(uint8_t* nv12_data, uint8_t* bgr24_data, const uint32_t cols, const uint32_t rows)
{
    return holoopencv::NV12ToBGR24(nv12_data, bgr24_data, cols, rows);
}
//NV12ToYUV420P
inline holo::bool_t NV12ToYUV420P(uint8_t* nv12_data, uint8_t* yuv420p_data, const uint32_t cols, const uint32_t rows)
{
    return hololibyuv::NV12ToYUV420P(nv12_data, yuv420p_data, cols, rows);
}
//YUV420PToRGB24
inline holo::bool_t YUV420PToRGB24(uint8_t* yuv420p_data, uint8_t* rgb24_data, const uint32_t cols, const uint32_t rows)
{
    return holoopencv::YUV420PToRGB24(yuv420p_data, rgb24_data, cols, rows);
}
// inline holo::bool_t YUV420PToRGB24(uint8_t* yuv420p_data, uint8_t* rgb24_data, const uint32_t cols, const uint32_t rows)
// {
//     return hololibyuv::YUV420PToRGB24(yuv420p_data, rgb24_data, cols, rows);
// }
//YUV420PToBGR24
inline holo::bool_t YUV420PToBGR24(uint8_t* yuv420p_data, uint8_t* bgr24_data, const uint32_t cols, const uint32_t rows)
{
    return holoopencv::YUV420PToBGR24(yuv420p_data, bgr24_data, cols, rows);
}
//YUV420PToNV12
inline holo::bool_t YUV420PToNV12(uint8_t* yuv420p_data, uint8_t* nv12_data, const uint32_t cols, const uint32_t rows)
{
    return hololibyuv::YUV420PToNV12(yuv420p_data, nv12_data, cols, rows);
}
//RGB24ToBGR24
inline holo::bool_t RGB24ToBGR24(uint8_t* rgb24_data, uint8_t* bgr24_data, const uint32_t cols, const uint32_t rows)
{
    return holoopencv::RGB24ToBGR24(rgb24_data, bgr24_data, cols, rows);
}
//RGB24ToYUV420P
inline holo::bool_t RGB24ToYUV420P(uint8_t* rgb24_data, uint8_t* yuv420p_data, const uint32_t cols, const uint32_t rows)
{
    return hololibyuv::RGB24ToYUV420P(rgb24_data, yuv420p_data, cols, rows);
}
//UYVY422ToNV12
inline holo::bool_t UYVY422ToNV12(uint8_t* uyvy422_data, uint8_t* nv12_data, const uint32_t cols, const uint32_t rows)
{
    return hololibyuv::UYVY422ToNV12(uyvy422_data, nv12_data, cols, rows);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//YUYV422ToRGB24
inline holo::bool_t YUYV422ToRGB24(holo::Image& yuyv422_image, holo::Image& rgb24_image)
{
    return holoopencv::YUYV422ToRGB24(yuyv422_image, rgb24_image);
}
//YUYV422ToBGR24
inline holo::bool_t YUYV422ToBGR24(holo::Image& yuyv422_image, holo::Image& bgr24_image)
{
    return holoopencv::YUYV422ToBGR24(yuyv422_image, bgr24_image);
}
//YUYV422ToNV12
inline holo::bool_t YUYV422ToNV12(holo::Image& yuyv422_image, holo::Image& nv12_image)
{
    return hololibyuv::YUYV422ToNV12(yuyv422_image, nv12_image);
}
//YUYV422ToYUV420P
holo::bool_t YUYV422ToYUV420P(holo::Image& yuyv422_image, holo::Image& yuv420p_image)
{
    return hololibyuv::YUYV422ToYUV420P(yuyv422_image, yuv420p_image);
}
//NV12ToRGB24
inline holo::bool_t NV12ToRGB24(holo::Image& nv12_image, holo::Image& rgb24_image)
{
    return holoopencv::NV12ToRGB24(nv12_image, rgb24_image);
}
//NV12ToBGR24
inline holo::bool_t NV12ToBGR24(holo::Image& nv12_image, holo::Image& bgr24_image)
{
    return holoopencv::NV12ToBGR24(nv12_image, bgr24_image);
}
//NV12ToYUV420P
inline holo::bool_t NV12ToYUV420P(holo::Image& nv12_image, holo::Image& yuv420p_image)
{
    return hololibyuv::NV12ToYUV420P(nv12_image, yuv420p_image);
}
//YUV420PToRGB24
inline holo::bool_t YUV420PToRGB24(holo::Image& yuv420p_image, holo::Image& rgb24_image)
{
    return holoopencv::YUV420PToRGB24(yuv420p_image, rgb24_image);
}

// inline holo::bool_t YUV420PToRGB24(holo::Image& yuv420p_image, holo::Image& rgb24_image)
// {
//     return hololibyuv::YUV420PToRGB24(yuv420p_image, rgb24_image);
// }
//YUV420PToBGR24
inline holo::bool_t YUV420PToBGR24(holo::Image& yuv420p_image, holo::Image& bgr24_image)
{
    return holoopencv::YUV420PToBGR24(yuv420p_image, bgr24_image);
}
//YUV420PToNV12
inline holo::bool_t YUV420PToNV12(holo::Image& yuv420p_image, holo::Image& nv12_image)
{
    return hololibyuv::YUV420PToNV12(yuv420p_image, nv12_image);
}
//RGB24ToBGR24
inline holo::bool_t RGB24ToBGR24(holo::Image& rgb24_image, holo::Image& bgr24_image)
{
    return holoopencv::RGB24ToBGR24(rgb24_image, bgr24_image);
}
//RGB24ToYUV420P
inline holo::bool_t RGB24ToYUV420P(holo::Image& rgb24_image, holo::Image& yuv420p_image)
{
    return hololibyuv::RGB24ToYUV420P(rgb24_image, yuv420p_image);
}
//UYVY422ToNV12
inline holo::bool_t UYVY422ToNV12(holo::Image& uyvy422_image, holo::Image& nv12_image)
{
    return hololibyuv::UYVY422ToNV12(uyvy422_image, nv12_image);
}
}  // namespace image
}  // namespace sensors
}  // namespace holo

#endif  //_HOLO_SENSORS_CAMERA_IMAGE_PROCESS_CONVERT_IMAGE_COLOR_CONVERT_H