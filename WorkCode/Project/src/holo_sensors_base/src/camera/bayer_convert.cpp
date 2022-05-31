/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bayer_convert.hpp
 * @brief Bayer Convert Process.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-13.
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_BAYER_CONVERT_H
#define _HOLO_SENSORS_CAMERA_IMAGE_BAYER_CONVERT_H

#include <holo/common/image.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/log/hololog.h>
#include <holo/sensors/camera/bayer_convert.h>
#include <holo/sensors/camera/image_structure.h>

namespace holo
{
namespace sensors
{
namespace camera
{
void BorderBayerLine2Bgr24StartWithGreen(const uint8_t* bayer, const uint8_t* adjacent_bayer, uint8_t* bgr,
                                         uint32_t& width, int32_t start_with_green, int32_t blue_line)
{
    int32_t t0, t1;
    if (start_with_green)
    {
        /* First pixel */
        if (blue_line)
        {
            *bgr++ = bayer[1];
            *bgr++ = bayer[0];
            *bgr++ = adjacent_bayer[0];
        }
        else
        {
            *bgr++ = adjacent_bayer[0];
            *bgr++ = bayer[0];
            *bgr++ = bayer[1];
        }
        /* Second pixel */
        t0 = (bayer[0] + bayer[2] + adjacent_bayer[1] + 1) / 3;
        t1 = (adjacent_bayer[0] + adjacent_bayer[2] + 1) >> 1;
        if (blue_line)
        {
            *bgr++ = bayer[1];
            *bgr++ = t0;
            *bgr++ = t1;
        }
        else
        {
            *bgr++ = t1;
            *bgr++ = t0;
            *bgr++ = bayer[1];
        }
        bayer++;
        adjacent_bayer++;
        width -= 2;
    }
    else
    {
        /* First pixel */
        t0 = (bayer[1] + adjacent_bayer[0] + 1) >> 1;
        if (blue_line)
        {
            *bgr++ = bayer[0];
            *bgr++ = t0;
            *bgr++ = adjacent_bayer[1];
        }
        else
        {
            *bgr++ = adjacent_bayer[1];
            *bgr++ = t0;
            *bgr++ = bayer[0];
        }
        width--;
    }
}
void BorderBayerLine2Bgr24BlueLine(const uint8_t* bayer, const uint8_t* adjacent_bayer, uint8_t* bgr, uint32_t& width,
                                   int32_t blue_line)
{
    int32_t t0, t1;
    if (blue_line)
    {
        for (; width > 2; width -= 2)
        {
            t0     = (bayer[0] + bayer[2] + 1) >> 1;
            *bgr++ = t0;
            *bgr++ = bayer[1];
            *bgr++ = adjacent_bayer[1];
            bayer++;
            adjacent_bayer++;

            t0     = (bayer[0] + bayer[2] + adjacent_bayer[1] + 1) / 3;
            t1     = (adjacent_bayer[0] + adjacent_bayer[2] + 1) >> 1;
            *bgr++ = bayer[1];
            *bgr++ = t0;
            *bgr++ = t1;
            bayer++;
            adjacent_bayer++;
        }
    }
    else
    {
        for (; width > 2; width -= 2)
        {
            t0     = (bayer[0] + bayer[2] + 1) >> 1;
            *bgr++ = adjacent_bayer[1];
            *bgr++ = bayer[1];
            *bgr++ = t0;
            bayer++;
            adjacent_bayer++;

            t0     = (bayer[0] + bayer[2] + adjacent_bayer[1] + 1) / 3;
            t1     = (adjacent_bayer[0] + adjacent_bayer[2] + 1) >> 1;
            *bgr++ = t1;
            *bgr++ = t0;
            *bgr++ = bayer[1];
            bayer++;
            adjacent_bayer++;
        }
    }
}
void BorderBayerLine2Bgr24SetLastPixel(const uint8_t* bayer, const uint8_t* adjacent_bayer, uint8_t* bgr,
                                       uint32_t width, int32_t blue_line)
{
    int32_t t0;
    if (width == 2)
    {
        /* Second to last pixel */
        t0 = (bayer[0] + bayer[2] + 1) >> 1;
        if (blue_line)
        {
            *bgr++ = t0;
            *bgr++ = bayer[1];
            *bgr++ = adjacent_bayer[1];
        }
        else
        {
            *bgr++ = adjacent_bayer[1];
            *bgr++ = bayer[1];
            *bgr++ = t0;
        }
        /* Last pixel */
        t0 = (bayer[1] + adjacent_bayer[2] + 1) >> 1;
        if (blue_line)
        {
            *bgr++ = bayer[2];
            *bgr++ = t0;
            *bgr++ = adjacent_bayer[1];
        }
        else
        {
            *bgr++ = adjacent_bayer[1];
            *bgr++ = t0;
            *bgr++ = bayer[2];
        }
    }
    else
    {
        /* Last pixel */
        if (blue_line)
        {
            *bgr++ = bayer[0];
            *bgr++ = bayer[1];
            *bgr++ = adjacent_bayer[1];
        }
        else
        {
            *bgr++ = adjacent_bayer[1];
            *bgr++ = bayer[1];
            *bgr++ = bayer[0];
        }
    }
}
void ConvertBorderBayerLine2Bgr24(const uint8_t* bayer, const uint8_t* adjacent_bayer, uint8_t* bgr, uint32_t width,
                                  int32_t start_with_green, int32_t blue_line)
{
    BorderBayerLine2Bgr24StartWithGreen(bayer, adjacent_bayer, bgr, width, start_with_green, blue_line);
    BorderBayerLine2Bgr24BlueLine(bayer, adjacent_bayer, bgr, width, blue_line);
    BorderBayerLine2Bgr24SetLastPixel(bayer, adjacent_bayer, bgr, width, blue_line);
}

void Bayer2Rgbbgr24StartWithGreen(const uint8_t* bayer, uint8_t* bgr, uint32_t width, int32_t start_with_green,
                                  int32_t blue_line)
{
    int32_t t0, t1;
    if (start_with_green)
    {
        /* OpenCV has a bug in the next line, which was
        t0 = (bayer[0] + bayer[width * 2] + 1) >> 1; */
        t0 = (bayer[1] + bayer[width * 2 + 1] + 1) >> 1;
        /* Write first pixel */
        t1 = (bayer[0] + bayer[width * 2] + bayer[width + 1] + 1) / 3;
        if (blue_line)
        {
            *bgr++ = t0;
            *bgr++ = t1;
            *bgr++ = bayer[width];
        }
        else
        {
            *bgr++ = bayer[width];
            *bgr++ = t1;
            *bgr++ = t0;
        }

        /* Write second pixel */
        t1 = (bayer[width] + bayer[width + 2] + 1) >> 1;
        if (blue_line)
        {
            *bgr++ = t0;
            *bgr++ = bayer[width + 1];
            *bgr++ = t1;
        }
        else
        {
            *bgr++ = t1;
            *bgr++ = bayer[width + 1];
            *bgr++ = t0;
        }
        bayer++;
    }
    else
    {
        /* Write first pixel */
        t0 = (bayer[0] + bayer[width * 2] + 1) >> 1;
        if (blue_line)
        {
            *bgr++ = t0;
            *bgr++ = bayer[width];
            *bgr++ = bayer[width + 1];
        }
        else
        {
            *bgr++ = bayer[width + 1];
            *bgr++ = bayer[width];
            *bgr++ = t0;
        }
    }
}
void Bayer2Rgbbgr24BlueLine(const uint8_t* bayer, uint8_t* bgr, uint32_t width, int32_t blue_line,
                            const uint8_t* bayerEnd)
{
    int32_t t0, t1;

    if (blue_line)
    {
        for (; bayer <= bayerEnd - 2; bayer += 2)
        {
            t0     = (bayer[0] + bayer[2] + bayer[width * 2] + bayer[width * 2 + 2] + 2) >> 2;
            t1     = (bayer[1] + bayer[width] + bayer[width + 2] + bayer[width * 2 + 1] + 2) >> 2;
            *bgr++ = t0;
            *bgr++ = t1;
            *bgr++ = bayer[width + 1];

            t0     = (bayer[2] + bayer[width * 2 + 2] + 1) >> 1;
            t1     = (bayer[width + 1] + bayer[width + 3] + 1) >> 1;
            *bgr++ = t0;
            *bgr++ = bayer[width + 2];
            *bgr++ = t1;
        }
    }
    else
    {
        for (; bayer <= bayerEnd - 2; bayer += 2)
        {
            t0     = (bayer[0] + bayer[2] + bayer[width * 2] + bayer[width * 2 + 2] + 2) >> 2;
            t1     = (bayer[1] + bayer[width] + bayer[width + 2] + bayer[width * 2 + 1] + 2) >> 2;
            *bgr++ = bayer[width + 1];
            *bgr++ = t1;
            *bgr++ = t0;

            t0     = (bayer[2] + bayer[width * 2 + 2] + 1) >> 1;
            t1     = (bayer[width + 1] + bayer[width + 3] + 1) >> 1;
            *bgr++ = t1;
            *bgr++ = bayer[width + 2];
            *bgr++ = t0;
        }
    }
}
void Bayer2Rgbbgr24SetLastPixel(const uint8_t* bayer, uint8_t* bgr, uint32_t width, int32_t blue_line,
                                const uint8_t* bayerEnd)
{
    int32_t t0, t1;
    if (bayer < bayerEnd)
    {
        /* write second to last pixel */
        t0 = (bayer[0] + bayer[2] + bayer[width * 2] + bayer[width * 2 + 2] + 2) >> 2;
        t1 = (bayer[1] + bayer[width] + bayer[width + 2] + bayer[width * 2 + 1] + 2) >> 2;
        if (blue_line)
        {
            *bgr++ = t0;
            *bgr++ = t1;
            *bgr++ = bayer[width + 1];
        }
        else
        {
            *bgr++ = bayer[width + 1];
            *bgr++ = t1;
            *bgr++ = t0;
        }
        /* write last pixel */
        t0 = (bayer[2] + bayer[width * 2 + 2] + 1) >> 1;
        if (blue_line)
        {
            *bgr++ = t0;
            *bgr++ = bayer[width + 2];
            *bgr++ = bayer[width + 1];
        }
        else
        {
            *bgr++ = bayer[width + 1];
            *bgr++ = bayer[width + 2];
            *bgr++ = t0;
        }
        bayer++;
    }
    else
    {
        /* write last pixel */
        t0 = (bayer[0] + bayer[width * 2] + 1) >> 1;
        t1 = (bayer[1] + bayer[width * 2 + 1] + bayer[width] + 1) / 3;
        if (blue_line)
        {
            *bgr++ = t0;
            *bgr++ = t1;
            *bgr++ = bayer[width + 1];
        }
        else
        {
            *bgr++ = bayer[width + 1];
            *bgr++ = t1;
            *bgr++ = t0;
        }
    }
}
static void Bayer2Rgbbgr24(const uint8_t* bayer, uint8_t* bgr, uint32_t width, uint32_t height,
                           int32_t start_with_green, int32_t blue_line)
{
    /* render the first line */
    ConvertBorderBayerLine2Bgr24(bayer, bayer + width, bgr, width, start_with_green, blue_line);
    bgr += width * 3;

    /* reduce height by 2 because of the special case top/bottom line */
    for (height -= 2; height; height--)
    {
        /* (width - 2) because of the border */
        const uint8_t* bayerEnd = bayer + (width - 2);

        Bayer2Rgbbgr24StartWithGreen(bayer, bgr, width, start_with_green, blue_line);
        Bayer2Rgbbgr24BlueLine(bayer, bgr, width, blue_line, bayerEnd);
        Bayer2Rgbbgr24SetLastPixel(bayer, bgr, width, blue_line, bayerEnd);

        /* skip 2 border pixels */
        bayer += 2;

        blue_line        = !blue_line;
        start_with_green = !start_with_green;
    }

    /* render the last line */
    ConvertBorderBayerLine2Bgr24(bayer + width, bayer, bgr, width, !start_with_green, !blue_line);
}

void Bayer2Rgb24(const uint8_t* pbay, uint8_t* prgb24, uint32_t width, uint32_t height, uint32_t pix_order)
{
    switch (pix_order)
    {
        /*conversion functions are build for bgr, by switching b and r lines we get rgb*/
        case 0: /* gbgbgb... | rgrgrg... (V4L2_PIX_FMT_SGBRG8)*/
            Bayer2Rgbbgr24(pbay, prgb24, width, height, true, false);
            break;

        case 1: /* grgrgr... | bgbgbg... (V4L2_PIX_FMT_SGRBG8)*/
            Bayer2Rgbbgr24(pbay, prgb24, width, height, true, true);
            break;

        case 2: /* bgbgbg... | grgrgr... (V4L2_PIX_FMT_SBGGR8)*/
            Bayer2Rgbbgr24(pbay, prgb24, width, height, false, false);
            break;

        case 3: /* rgrgrg... ! gbgbgb... (V4L2_PIX_FMT_SRGGB8)*/
            Bayer2Rgbbgr24(pbay, prgb24, width, height, false, true);
            break;

        default: /* default is 0*/
            Bayer2Rgbbgr24(pbay, prgb24, width, height, true, false);
            break;
    }
}

void Bayer162Bayer8(const int16_t* inbuf, uint8_t* outbuf, int32_t width, int32_t height, int32_t shift)
{
    int32_t i = 0, j = 0;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            outbuf[i * width + j] = (inbuf[i * width + j] >> shift);
        }
    }
}

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif