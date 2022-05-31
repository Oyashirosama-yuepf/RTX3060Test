/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_resize.h.
 * @brief Image Resize.
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-12-11.
 */

#ifndef _HOLO_SENSORS_IMAGE_RESIZE_IMAGE_RESIZE_H
#define _HOLO_SENSORS_IMAGE_RESIZE_IMAGE_RESIZE_H

#include <holo/log/hololog.h>
#include <holo/common/image.h>
#include <libyuv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace holo
{
namespace sensors
{
namespace image
{
enum ImageResizeMode : uint8_t
{
    QUALITY_LOW     = 0,
    QUALITY_MEDIUM  = 1,
    QUALITY_HIGH    = 2,
    QUALITY_HIGHEST = 3
};

bool_t RGB24Resize(uint8_t* src_data, uint8_t* dst_data, 
                   uint16_t src_cols, uint16_t src_rows, 
                   uint16_t dst_cols, uint16_t dst_rows,
                   enum ImageResizeMode image_resize_mode = QUALITY_HIGH);
bool_t BGR24Resize(uint8_t* src_data, uint8_t* dst_data, 
                     uint16_t src_cols, uint16_t src_rows, 
                     uint16_t dst_cols, uint16_t dst_rows,
                     enum ImageResizeMode image_resize_mode = QUALITY_HIGH);
bool_t NV12Resize(uint8_t* src_data, uint8_t* dst_data, 
                  uint16_t src_cols, uint16_t src_rows, 
                  uint16_t dst_cols, uint16_t dst_rows,
                  enum ImageResizeMode image_resize_mode = QUALITY_HIGH);
bool_t YUV420PResize(uint8_t* src_data, uint8_t* dst_data, 
                     uint16_t src_cols, uint16_t src_rows, 
                     uint16_t dst_cols, uint16_t dst_rows,
                     enum ImageResizeMode image_resize_mode = QUALITY_HIGH);

bool_t RGB24Resize(const holo::Image& src_image, holo::Image& dst_image,
                   enum ImageResizeMode image_resize_mode = QUALITY_HIGH);
bool_t BGR24Resize(const holo::Image& src_image, holo::Image& dst_image,
                     enum ImageResizeMode image_resize_mode = QUALITY_HIGH);
bool_t NV12Resize(const holo::Image& src_image, holo::Image& dst_image,
                  enum ImageResizeMode image_resize_mode = QUALITY_HIGH);
bool_t YUV420PResize(const holo::Image& src_image, holo::Image& dst_image,
                     enum ImageResizeMode image_resize_mode = QUALITY_HIGH);
}  // namespace image
}  // namespace sensors
}  // namespace holo

#endif  //_HOLO_SENSORS_IMAGE_RESIZE_IMAGE_RESIZE_H