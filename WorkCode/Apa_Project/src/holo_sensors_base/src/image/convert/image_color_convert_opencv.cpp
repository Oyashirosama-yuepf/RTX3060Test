/**
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_color_convert_opencv.cpp.
 * @brief Image Color Convert By Opencv.
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2022-1-25.
 */
#include <holo/sensors/image/convert/image_color_convert_opencv.h>

namespace holo
{
namespace sensors
{
namespace image
{
namespace holoopencv
{
//YUYV422ToRGB24
holo::bool_t YUYV422ToRGB24(uint8_t* yuyv422_data, uint8_t* rgb24_data, const uint32_t cols, const uint32_t rows)
{
    if (nullptr == yuyv422_data)
    {
        LOG(ERROR) << "YUYV422ToRGB24: input data is invalid";
        return false;
    }
    else if (nullptr == rgb24_data)
    {
        LOG(ERROR) << "YUYV422ToRGB24: output data is invalid";
        return false;
    }

    cv::cvtColor(cv::Mat(rows, cols, CV_8UC2, yuyv422_data), 
                 cv::Mat(rows, cols, CV_8UC3, rgb24_data), CV_YUV2RGB_YUYV);

    return true;
}

//YUYV422ToBGR24
holo::bool_t YUYV422ToBGR24(uint8_t* yuyv422_data, uint8_t* bgr24_data, const uint32_t cols, const uint32_t rows)
{
    if (nullptr == yuyv422_data)
    {
        LOG(ERROR) << "YUYV422ToBGR24: input data is invalid";
        return false;
    }
    else if (nullptr == bgr24_data)
    {
        LOG(ERROR) << "YUYV422ToBGR24: output data is invalid";
        return false;
    }

    cv::cvtColor(cv::Mat(rows, cols, CV_8UC2, yuyv422_data), 
                 cv::Mat(rows, cols, CV_8UC3, bgr24_data), CV_YUV2BGR_YUYV);

    return true;
}
//NV12ToRGB24
holo::bool_t NV12ToRGB24(uint8_t* nv12_data, uint8_t* rgb24_data, const uint32_t cols, const uint32_t rows)
{
    if (nullptr == nv12_data)
    {
        LOG(ERROR) << "NV12ToRGB24: input data is invalid";
        return false;
    }
    else if (nullptr == rgb24_data)
    {
        LOG(ERROR) << "NV12ToRGB24: output data is invalid";
        return false;
    }

    cv::cvtColor(cv::Mat(rows, cols, CV_8UC2, nv12_data), 
                 cv::Mat(rows, cols, CV_8UC3, rgb24_data), CV_YUV2RGB_NV12);

    return true;
}

//NV12ToBGR24
holo::bool_t NV12ToBGR24(uint8_t* nv12_data, uint8_t* bgr24_data, const uint32_t cols, const uint32_t rows)
{
    if (nullptr == nv12_data)
    {
        LOG(ERROR) << "NV12ToBGR24: input data is invalid";
        return false;
    }
    else if (nullptr == bgr24_data)
    {
        LOG(ERROR) << "NV12ToBGR24: output data is invalid";
        return false;
    }

    cv::cvtColor(cv::Mat(rows, cols, CV_8UC2, nv12_data), 
                 cv::Mat(rows, cols, CV_8UC3, bgr24_data), CV_YUV2BGR_NV12);

    return true;
}
holo::bool_t YUV420PToRGB24(uint8_t* yuv420p_data, uint8_t* rgb24_data, const uint32_t cols, const uint32_t rows)
{
    if (nullptr == yuv420p_data)
    {
        LOG(ERROR) << "YUV420PToRGB24: input data is invalid";
        return false;
    }
    else if (nullptr == rgb24_data)
    {
        LOG(ERROR) << "YUV420PToRGB24: output data is invalid";
        return false;
    }

    cv::cvtColor(cv::Mat(rows, cols, CV_8UC2, yuv420p_data), 
                 cv::Mat(rows, cols, CV_8UC3, rgb24_data), CV_YUV2RGB_I420);

    return true;
}

//YUV420PToBGR24
holo::bool_t YUV420PToBGR24(uint8_t* yuv420p_data, uint8_t* bgr24_data, const uint32_t cols, const uint32_t rows)
{
    if (nullptr == yuv420p_data)
    {
        LOG(ERROR) << "YUV420PToBGR24: input data is invalid";
        return false;
    }
    else if (nullptr == bgr24_data)
    {
        LOG(ERROR) << "YUV420PToBGR24: output data is invalid";
        return false;
    }

    cv::cvtColor(cv::Mat(rows, cols, CV_8UC2, yuv420p_data), 
                 cv::Mat(rows, cols, CV_8UC3, bgr24_data), CV_YUV2BGR_I420);

    return true;
}
//RGB24ToBGR24
holo::bool_t RGB24ToBGR24(uint8_t* rgb24_data, uint8_t* bgr24_data, const uint32_t cols, const uint32_t rows)
{
    if (nullptr == rgb24_data)
    {
        LOG(ERROR) << "RGB24ToBGR24: input data is invalid";
        return false;
    }
    else if (nullptr == bgr24_data)
    {
        LOG(ERROR) << "RGB24ToBGR24: output data is invalid";
        return false;
    }

    cv::cvtColor(cv::Mat(rows, cols, CV_8UC2, rgb24_data), 
                 cv::Mat(rows, cols, CV_8UC3, bgr24_data), CV_RGB2BGR);

    return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//YUYV422ToRGB24
holo::bool_t YUYV422ToRGB24(holo::Image& yuyv422_image, holo::Image& rgb24_image)
{
    if (yuyv422_image.GetEncoding() != holo::Image::Encoding::YUYV)
    {
        LOG(ERROR) << "YUYV422ToRGB24: the holo::Image you want input is not a YUYV422 format";
        return false;
    }

    if (rgb24_image.GetEncoding() != holo::Image::Encoding::RGB)
    {
        LOG(ERROR) << "YUYV422ToRGB24: the holo::Image you want output is not a RGB24 format";
        return false;
    }

    if ((yuyv422_image.GetPixelCols() != rgb24_image.GetPixelCols()) || 
        (yuyv422_image.GetPixelRows() != rgb24_image.GetPixelRows()))
    {
        LOG(ERROR) << "YUYV422ToRGB24: The resolution of the image to be input and the image to be output are inconsistent";
        return false;
    }

    cv::cvtColor(yuyv422_image.GetCvType(), rgb24_image.GetCvType(), CV_YUV2RGB_YUYV);

    return true;
}

//YUYV422ToBGR24
holo::bool_t YUYV422ToBGR24(holo::Image& yuyv422_image, holo::Image& bgr24_image)
{
    if (yuyv422_image.GetEncoding() != holo::Image::Encoding::YUYV)
    {
        LOG(ERROR) << "YUYV422ToBGR24: the holo::Image you want input is not a YUYV422 format";
        return false;
    }

    if (bgr24_image.GetEncoding() != holo::Image::Encoding::BGR)
    {
        LOG(ERROR) << "YUYV422ToBGR24: the holo::Image you want output is not a BGR24 format";
        return false;
    }

    if ((yuyv422_image.GetPixelCols() != bgr24_image.GetPixelCols()) || 
        (yuyv422_image.GetPixelRows() != bgr24_image.GetPixelRows()))
    {
        LOG(ERROR) << "YUYV422ToBGR24: The resolution of the image to be input and the image to be output are inconsistent";
        return false;
    }

    cv::cvtColor(yuyv422_image.GetCvType(), bgr24_image.GetCvType(), CV_YUV2BGR_YUYV);

    return true;
}
//NV12ToRGB24
holo::bool_t NV12ToRGB24(holo::Image& nv12_image, holo::Image& rgb24_image)
{
    if (nv12_image.GetEncoding() != holo::Image::Encoding::NV12)
    {
        LOG(ERROR) << "NV12ToRGB24: the holo::Image you want input is not a NV12 format";
        return false;
    }

    if (rgb24_image.GetEncoding() != holo::Image::Encoding::RGB)
    {
        LOG(ERROR) << "NV12ToRGB24: the holo::Image you want output is not a RGB24 format";
        return false;
    }

    if ((nv12_image.GetPixelCols() != rgb24_image.GetPixelCols()) || 
        (nv12_image.GetPixelRows() != rgb24_image.GetPixelRows()))
    {
        LOG(ERROR) << "NV12ToRGB24: The resolution of the image to be input and the image to be output are inconsistent";
        return false;
    }

    cv::cvtColor(nv12_image.GetCvType(), rgb24_image.GetCvType(), CV_YUV2RGB_NV12);

    return true;
}

//NV12ToBGR24
holo::bool_t NV12ToBGR24(holo::Image& nv12_image, holo::Image& bgr24_image)
{
    if (nv12_image.GetEncoding() != holo::Image::Encoding::NV12)
    {
        LOG(ERROR) << "NV12ToBGR24: the holo::Image you want input is not a NV12 format";
        return false;
    }

    if (bgr24_image.GetEncoding() != holo::Image::Encoding::BGR)
    {
        LOG(ERROR) << "NV12ToBGR24: the holo::Image you want output is not a BGR24 format";
        return false;
    }

    if ((nv12_image.GetPixelCols() != bgr24_image.GetPixelCols()) || 
        (nv12_image.GetPixelRows() != bgr24_image.GetPixelRows()))
    {
        LOG(ERROR) << "NV12ToBGR24: The resolution of the image to be input and the image to be output are inconsistent";
        return false;
    }

    cv::cvtColor(nv12_image.GetCvType(), bgr24_image.GetCvType(), CV_YUV2BGR_NV12);

    return true;
}
holo::bool_t YUV420PToRGB24(holo::Image& yuv420p_image, holo::Image& rgb24_image)
{
    if (yuv420p_image.GetEncoding() != holo::Image::Encoding::YU12)
    {
        LOG(ERROR) << "YUV420PToRGB24: the holo::Image you want input is not a YUV420P format";
        return false;
    }

    if (rgb24_image.GetEncoding() != holo::Image::Encoding::RGB)
    {
       LOG(ERROR) << "YUV420PToRGB24: the holo::Image you want output is not a RGB24 format";
       return false;
    }

    if ((yuv420p_image.GetPixelCols() != rgb24_image.GetPixelCols()) || 
        (yuv420p_image.GetPixelRows() != rgb24_image.GetPixelRows()))
    {
        LOG(ERROR) << "YUV420PToRGB24: The resolution of the image to be input and the image to be output are inconsistent";
        return false;
    }

    cv::cvtColor(yuv420p_image.GetCvType(), rgb24_image.GetCvType(), CV_YUV2RGB_I420);

    return true;
}

//YUV420PToBGR24
holo::bool_t YUV420PToBGR24(holo::Image& yuv420p_image, holo::Image& bgr24_image)
{
    if (yuv420p_image.GetEncoding() != holo::Image::Encoding::YU12)
    {
        LOG(ERROR) << "YUV420PToBGR24: the holo::Image you want input is not a YUV420P format";
        return false;
    }

    if (bgr24_image.GetEncoding() != holo::Image::Encoding::BGR)
    {
       LOG(ERROR) << "YUV420PToBGR24: the holo::Image you want output is not a BGR24 format";
       return false;
    }

    if ((yuv420p_image.GetPixelCols() != bgr24_image.GetPixelCols()) || 
        (yuv420p_image.GetPixelRows() != bgr24_image.GetPixelRows()))
    {
        LOG(ERROR) << "YUV420PToBGR24: The resolution of the image to be input and the image to be output are inconsistent";
        return false;
    }

    cv::cvtColor(yuv420p_image.GetCvType(), bgr24_image.GetCvType(), CV_YUV2BGR_I420);

    return true;
}
//RGB24ToBGR24
holo::bool_t RGB24ToBGR24(holo::Image& rgb24_image, holo::Image& bgr24_image)
{
    if (rgb24_image.GetEncoding() != holo::Image::Encoding::RGB)
    {
        LOG(ERROR) << "RGB24ToBGR24: the holo::Image you want input is not a RGB24 format";
        return false;
    }

    if (bgr24_image.GetEncoding() != holo::Image::Encoding::BGR)
    {
        LOG(ERROR) << "RGB24ToBGR24: the holo::Image you want input is not a BGR24 format";
        return false;
    }

    if ((rgb24_image.GetPixelCols() != bgr24_image.GetPixelCols()) || 
        (rgb24_image.GetPixelRows() != bgr24_image.GetPixelRows()))
    {
        LOG(ERROR) << "RGB24ToBGR24: The resolution of the image to be input and the image to be output are inconsistent";
        return false;
    }

    cv::cvtColor(rgb24_image.GetCvType(), bgr24_image.GetCvType(), CV_RGB2BGR);

    return true;
}
}  // namespace holoopencv
}  // namespace image
}  // namespace sensors
}  // namespace holo