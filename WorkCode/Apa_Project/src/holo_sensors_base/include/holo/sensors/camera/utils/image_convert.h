/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_convert.h.
 * @brief Image Convert.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-13.
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_CONVERT_H
#define _HOLO_SENSORS_CAMERA_IMAGE_CONVERT_H

#include <holo/log/hololog.h>
#include <holo/common/image.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/sensors/camera/bayer_convert.h>

namespace holo
{
namespace sensors
{
namespace camera
{
/**
 * @brief limit yuv value
 *
 * @param value
 * @return uint8_t
 */
uint8_t LimitToU8(int32_t value);

/**
 * @brief init yuv table
 *
 */
void InitYuvTable();

/**
 * @brief yuyv convert rgbrgb
 *
 */
void Yuv2RgbPixel(uint8_t y1, uint8_t y2, uint8_t u, uint8_t v, uint8_t* rgb2);

/**
 * @brief yuyv convert bgrbgr
 *
 */
void Yuv2BgrPixel(uint8_t y1, uint8_t y2, uint8_t u, uint8_t v, uint8_t* bgr2);

/**
 * @brief      convert yuyv image to rgb image
 *
 * @param[in]  yuyv  The buffer of yuyv image
 * @param[in]  width  The width of image
 * @param[in]  height  The width of image
 * @param[out] rgb   The rgb image
 */
void Yuyv2Rgb(uint8_t* yuyv, uint32_t width, uint32_t height, uint8_t* rgb);

/**
 * @brief rgbrgb convert yuyv
 *
 */
void Rgb2YuyvPixel(uint8_t* rgb, uint8_t* yuyv);

/**
 * @brief      convert rgb image to yuyv image
 *
 * @param[in]  rgb  The buffer of rgb image
 * @param[in]  width  The width of image
 * @param[in]  height  The width of image
 * @param[out] yuyv   The yuyv image
 */
void Rgb2Yuyv(uint8_t* rgb, uint32_t width, uint32_t height, uint8_t* yuyv);

/**
 * @brief      convert rgb image to nv12 image
 *
 * @param[in]  rgb  The buffer of rgb image
 * @param[in]  width  The width of image
 * @param[in]  height  The width of image
 * @param[out] y,u,v   The y,u,v component of nv12 image
 */
void Rgb2Nv12(const uint8_t* rgb, uint32_t width, uint32_t height, uint8_t* y, uint8_t* u, uint8_t* v);
void Bgr2Nv12(const uint8_t* bgr, uint32_t width, uint32_t height, uint8_t* y, uint8_t* u, uint8_t* v);

void Nv122Rgb(const uint8_t* y, const uint8_t* u, const uint8_t* v, uint8_t* rgb, uint32_t width, uint32_t height);
void Nv122Bgr(const uint8_t* y, const uint8_t* u, const uint8_t* v, uint8_t* bgr, uint32_t width, uint32_t height);

void Nv122Rgb(const uint8_t* y, const uint8_t* uv, uint8_t* rgb, uint32_t width, uint32_t height);
void Nv122Bgr(const uint8_t* y, const uint8_t* uv, uint8_t* bgr, uint32_t width, uint32_t height);
/**
 * @brief      convert holo image to cv::Mat
 *
 * @param[in]  image  The image
 *
 * @return     the result cv::Mat
 */
cv::Mat Image2Mat(const holo::Image& image);

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  //_HOLO_SENSORS_CAMERA_IMAGE_CONVERT_H