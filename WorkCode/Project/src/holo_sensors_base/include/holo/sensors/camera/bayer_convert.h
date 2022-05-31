/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_utils.h.
 * @brief Image Utils.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-13.
 */
#ifndef _HOLO_SENSORS_CAMERA_BAYER_CONVERT_H
#define _HOLO_SENSORS_CAMERA_BAYER_CONVERT_H

#include <holo/common/image.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/log/hololog.h>
#include <holo/sensors/camera/image_structure.h>

namespace holo
{
namespace sensors
{
namespace camera
{

/**
 * @brief      convert bayer16 order to bayer8 order
 *
 * @param[in]  inbuf   The input bayer16 image
 * @param[out] outbuf  The output bayer8 image
 * @param[in]  width   The width
 * @param[in]  height  The height
 * @param[in]  shift   The shift
 */
void Bayer162Bayer8(const int16_t* inbuf, uint8_t* outbuf, int32_t width, int32_t height, int32_t shift);

/*convert bayer raw data to rgb24
 * args:
 *      pbay: pointer to buffer containing Raw bayer data data
 *      prgb24: pointer to buffer containing rgb24 data
 *      width: picture width
 *      height: picture height
 *      pix_order: bayer pixel order (0=gb/rg   1=gr/bg  2=bg/gr  3=rg/bg)
 */
void Bayer2Rgb24(const uint8_t* pbay, uint8_t* prgb24, uint32_t width, uint32_t height, uint32_t pix_order);

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif