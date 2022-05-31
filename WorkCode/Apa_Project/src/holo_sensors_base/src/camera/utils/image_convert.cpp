/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_convert.cpp.
 * @brief Image Convert.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-13.
 */

#include <holo/sensors/camera/utils/image_convert.h>

namespace holo
{
namespace sensors
{
namespace camera
{
uint8_t LimitToU8(int32_t value)
{
    if (value > 255)
    {
        return 255;
    }
    else if (value < 0)
    {
        return 0;
    }
    else
    {
        return value;
    }
}

static int32_t y_table[256];
static int32_t v_r_table[256];
static int32_t v_g_table[256];
static int32_t u_g_table[256];
static int32_t u_b_table[256];

void InitYuvTable()
{
    for (int32_t i = 0; i <= 255; i++)
    {
        y_table[i]   = i * 1024;
        v_r_table[i] = (i - 128) * 1433;
        v_g_table[i] = (i - 128) * 728;
        u_g_table[i] = (i - 128) * 351;
        u_b_table[i] = (i - 128) * 1807;
    }
}

void Yuv2RgbPixel(uint8_t y1, uint8_t y2, uint8_t u, uint8_t v, uint8_t* rgb2)
{
    int32_t y1192 = y_table[y1];
    rgb2[0]       = LimitToU8((y1192 + v_r_table[v]) >> 10);
    rgb2[1]       = LimitToU8((y1192 - v_g_table[v] - u_g_table[u]) >> 10);
    rgb2[2]       = LimitToU8((y1192 + u_b_table[u]) >> 10);

    y1192   = y_table[y2];
    rgb2[3] = LimitToU8((y1192 + v_r_table[v]) >> 10);
    rgb2[4] = LimitToU8((y1192 - v_g_table[v] - u_g_table[u]) >> 10);
    rgb2[5] = LimitToU8((y1192 + u_b_table[u]) >> 10);
}

void Yuv2BgrPixel(uint8_t y1, uint8_t y2, uint8_t u, uint8_t v, uint8_t* bgr2)
{
    int32_t y1192 = y_table[y1];
    bgr2[2]       = LimitToU8((y1192 + v_r_table[v]) >> 10);
    bgr2[1]       = LimitToU8((y1192 - v_g_table[v] - u_g_table[u]) >> 10);
    bgr2[0]       = LimitToU8((y1192 + u_b_table[u]) >> 10);

    y1192   = y_table[y2];
    bgr2[5] = LimitToU8((y1192 + v_r_table[v]) >> 10);
    bgr2[4] = LimitToU8((y1192 - v_g_table[v] - u_g_table[u]) >> 10);
    bgr2[3] = LimitToU8((y1192 + u_b_table[u]) >> 10);
}

void Yuyv2Rgb(uint8_t* yuyv, uint32_t width, uint32_t height, uint8_t* rgb)
{
    for (uint32_t pixel = 0; pixel < width * height; pixel += 2)
    {
        uint8_t y1 = *yuyv++;
        uint8_t u  = *yuyv++;
        uint8_t y2 = *yuyv++;
        uint8_t v  = *yuyv++;

        Yuv2RgbPixel(y1, y2, u, v, rgb);

        rgb += 6;
    }
}

void Rgb2YuyvPixel(uint8_t* rgb, uint8_t* yuyv)
{
    uint8_t u1, u2, v1, v2;
    yuyv[0] = LimitToU8(0.299 * rgb[0] + 0.587 * rgb[1] + 0.114 * rgb[2]);
    u1      = LimitToU8(-0.169 * rgb[0] - 0.331 * rgb[1] + 0.500 * rgb[2] + 128);
    v1      = LimitToU8(0.500 * rgb[0] - 0.419 * rgb[1] - 0.081 * rgb[2] + 128);

    yuyv[2] = LimitToU8(0.299 * rgb[3] + 0.587 * rgb[4] + 0.114 * rgb[5]);
    u2      = LimitToU8(-0.169 * rgb[3] - 0.331 * rgb[4] + 0.500 * rgb[5] + 128);
    v2      = LimitToU8(0.500 * rgb[3] - 0.419 * rgb[4] - 0.081 * rgb[5] + 128);

    yuyv[1] = (u1 + u2) / 2;
    yuyv[3] = (v1 + v2) / 2;
}

void Rgb2Yuyv(uint8_t* rgb, uint32_t width, uint32_t height, uint8_t* yuyv)
{
    for (uint32_t pixel = 0; pixel < width * height; pixel += 2)
    {
        Rgb2YuyvPixel(rgb, yuyv);
        rgb += 6;
        yuyv += 4;
    }
}

static void Rgb2Yuv(const uint8_t* rgb, uint8_t* yuv)
{
    yuv[0] = LimitToU8(0.299 * rgb[0] + 0.587 * rgb[1] + 0.114 * rgb[2]);
    yuv[1] = LimitToU8(-0.169 * rgb[0] - 0.331 * rgb[1] + 0.500 * rgb[2] + 128);
    yuv[2] = LimitToU8(0.500 * rgb[0] - 0.419 * rgb[1] - 0.081 * rgb[2] + 128);
}

static void Bgr2Yuv(const uint8_t* bgr, uint8_t* yuv)
{
    yuv[0] = LimitToU8(0.299 * bgr[2] + 0.587 * bgr[1] + 0.114 * bgr[0]);
    yuv[1] = LimitToU8(-0.169 * bgr[2] - 0.331 * bgr[1] + 0.500 * bgr[0] + 128);
    yuv[2] = LimitToU8(0.500 * bgr[2] - 0.419 * bgr[1] - 0.081 * bgr[0] + 128);
}

void Rgb2Nv12(const uint8_t* rgb, uint32_t width, uint32_t height, uint8_t* y, uint8_t* u, uint8_t* v)
{
    uint32_t index1, index2, index3, index4;
    uint32_t u_v_index = 0;
    uint8_t  yuv[3];
    uint32_t u_sum = 0, v_sum = 0;
    for (uint32_t i = 0; i < width; i += 2)
    {
        for (uint32_t j = 0; j < height; j += 2)
        {
            index1    = j * width + i;
            index2    = index1 + 1;
            index3    = index1 + width;
            index4    = index3 + 1;
            u_v_index = j / 2 * width / 2 + i / 2;

            Rgb2Yuv(rgb + index1 * 3, yuv);
            y[index1] = yuv[0];
            u_sum += yuv[1];
            v_sum += yuv[2];
            Rgb2Yuv(rgb + index2 * 3, yuv);
            y[index2] = yuv[0];
            u_sum += yuv[1];
            v_sum += yuv[2];
            Rgb2Yuv(rgb + index3 * 3, yuv);
            y[index3] = yuv[0];
            u_sum += yuv[1];
            v_sum += yuv[2];
            Rgb2Yuv(rgb + index4 * 3, yuv);
            y[index4] = yuv[0];
            u_sum += yuv[1];
            v_sum += yuv[2];

            u[u_v_index] = LimitToU8(u_sum / 4);
            v[u_v_index] = LimitToU8(v_sum / 4);
            u_sum        = 0;
            v_sum        = 0;
        }
    }
}

void Bgr2Nv12(const uint8_t* bgr, uint32_t width, uint32_t height, uint8_t* y, uint8_t* u, uint8_t* v)
{
    uint32_t index1, index2, index3, index4;
    uint32_t u_v_index;
    uint8_t  yuv[3];
    uint32_t u_sum = 0, v_sum = 0;
    for (uint32_t i = 0; i < width; i += 2)
    {
        for (uint32_t j = 0; j < height; j += 2)
        {
            index1    = j * width + i;
            index2    = index1 + 1;
            index3    = index1 + width;
            index4    = index3 + 1;
            u_v_index = j / 2 * width / 2 + i / 2;

            Bgr2Yuv(bgr + index1 * 3, yuv);
            y[index1] = yuv[0];
            u_sum += yuv[1];
            v_sum += yuv[2];
            Bgr2Yuv(bgr + index2 * 3, yuv);
            y[index2] = yuv[0];
            u_sum += yuv[1];
            v_sum += yuv[2];
            Bgr2Yuv(bgr + index3 * 3, yuv);
            y[index3] = yuv[0];
            u_sum += yuv[1];
            v_sum += yuv[2];
            Bgr2Yuv(bgr + index4 * 3, yuv);
            y[index4] = yuv[0];
            u_sum += yuv[1];
            v_sum += yuv[2];

            u[u_v_index] = LimitToU8(u_sum / 4);
            v[u_v_index] = LimitToU8(v_sum / 4);
            u_sum        = 0;
            v_sum        = 0;
        }
    }
}

void Nv122Rgb(const uint8_t* y, const uint8_t* u, const uint8_t* v, uint8_t* rgb, uint32_t width, uint32_t height)
{
    uint8_t  y1, y2, y3, y4, uu, vv;
    uint32_t index_y1, index_y2, index_uv;

    for (uint32_t i = 0; i < width / 2; i++)
    {
        for (uint32_t j = 0; j < height / 2; j++)
        {
            index_uv = width / 2 * j + i;
            index_y1 = j * 2 * width + i * 2;
            index_y2 = (j * 2 + 1) * width + i * 2;
            y1       = y[index_y1];
            y2       = y[index_y1 + 1];
            y3       = y[index_y2];
            y4       = y[index_y2 + 1];
            uu       = u[index_uv];
            vv       = v[index_uv];
            Yuv2RgbPixel(y1, y2, uu, vv, rgb + index_y1 * 3);
            Yuv2RgbPixel(y3, y4, uu, vv, rgb + index_y2 * 3);
        }
    }
}

void Nv122Bgr(const uint8_t* y, const uint8_t* u, const uint8_t* v, uint8_t* bgr, uint32_t width, uint32_t height)
{
    uint8_t  y1, y2, y3, y4, uu, vv;
    uint32_t index_y1, index_y2, index_uv;

    for (uint32_t i = 0; i < width / 2; i++)
    {
        for (uint32_t j = 0; j < height / 2; j++)
        {
            index_uv = width / 2 * j + i;
            index_y1 = j * 2 * width + i * 2;
            index_y2 = (j * 2 + 1) * width + i * 2;
            y1       = y[index_y1];
            y2       = y[index_y1 + 1];
            y3       = y[index_y2];
            y4       = y[index_y2 + 1];
            uu       = u[index_uv];
            vv       = v[index_uv];
            Yuv2BgrPixel(y1, y2, uu, vv, bgr + index_y1 * 3);
            Yuv2BgrPixel(y3, y4, uu, vv, bgr + index_y2 * 3);
        }
    }
}

void Nv122Rgb(const uint8_t* y, const uint8_t* uv, uint8_t* rgb, uint32_t width, uint32_t height)
{
    uint8_t  y1, y2, y3, y4, uu, vv;
    uint32_t index_y1, index_y2, index_uv = 0;

    for (uint32_t j = 0; j < height / 2; j++)
    {
        for (uint32_t i = 0; i < width / 2; i++)
        {
            index_y1 = j * 2 * width + i * 2;
            index_y2 = (j * 2 + 1) * width + i * 2;
            y1       = y[index_y1];
            y2       = y[index_y1 + 1];
            y3       = y[index_y2];
            y4       = y[index_y2 + 1];
            uu       = uv[index_uv];
            vv       = uv[index_uv + 1];
            Yuv2RgbPixel(y1, y2, uu, vv, rgb + index_y1 * 3);
            Yuv2RgbPixel(y3, y4, uu, vv, rgb + index_y2 * 3);
            index_uv += 2;
        }
    }
}

void Nv122Bgr(const uint8_t* y, const uint8_t* uv, uint8_t* bgr, uint32_t width, uint32_t height)
{
    uint8_t  y1, y2, y3, y4, uu, vv;
    uint32_t index_y1, index_y2, index_uv = 0;

    for (uint32_t j = 0; j < height / 2; j++)
    {
        for (uint32_t i = 0; i < width / 2; i++)
        {
            index_y1 = j * 2 * width + i * 2;
            index_y2 = (j * 2 + 1) * width + i * 2;
            y1       = y[index_y1];
            y2       = y[index_y1 + 1];
            y3       = y[index_y2];
            y4       = y[index_y2 + 1];
            uu       = uv[index_uv];
            vv       = uv[index_uv + 1];
            Yuv2BgrPixel(y1, y2, uu, vv, bgr + index_y1 * 3);
            Yuv2BgrPixel(y3, y4, uu, vv, bgr + index_y2 * 3);
            index_uv += 2;
        }
    }
}

cv::Mat Image2Mat(const holo::Image& image)
{
    int32_t               type;
    int32_t               rows     = static_cast<int32_t>(image.GetHeight());
    int32_t               cols     = static_cast<int32_t>(image.GetWidth());
    holo::Image::Encoding encoding = image.GetEncoding();
    if (encoding == Image::Encoding::RGB || encoding == Image::Encoding::BGR)
    {
        type = CV_8UC3;
    }
    else if (encoding == Image::Encoding::GRAYSCALE)
    {
        type = CV_8UC1;
    }
    else if ((encoding == Image::Encoding::YUYV) || (encoding == Image::Encoding::UYVY) ||
             (encoding == Image::Encoding::YUV422P))
    {
        type = CV_8UC2;
    }
    else if ((encoding == Image::Encoding::YU12) || (encoding == Image::Encoding::YV12) ||
             (encoding == Image::Encoding::NV12) || (encoding == Image::Encoding::NV21))
    {
        type = CV_8UC1;
    }
    else if (encoding == Image::Encoding::RGBA)
    {
        type = CV_8UC4;
    }
    else
    {
        throw std::runtime_error("unsupported image encoding type");
    }
    return cv::Mat(rows, cols, type, const_cast<uint8_t*>(image.GetData()));
}

}  // namespace camera
}  // namespace sensors
}  // namespace holo