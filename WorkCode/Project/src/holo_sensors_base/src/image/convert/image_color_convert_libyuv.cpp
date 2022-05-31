/**
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_color_convert_libyuv.cpp.
 * @brief Image Color Convert By Libyuv.
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2022-1-25.
 */

#include <holo/sensors/image/convert/image_color_convert_libyuv.h>

namespace holo
{
namespace sensors
{
namespace image
{
namespace hololibyuv
{
//YUYV422ToNV12
holo::bool_t YUYV422ToNV12(uint8_t* yuyv422_data, uint8_t* nv12_data, const uint32_t cols, const uint32_t rows)
{
    if (nullptr == yuyv422_data)
    {
        LOG(ERROR) << "YUYV422ToNV12: input data is invalid";
        return false;
    }
    else if (nullptr == nv12_data)
    {
        LOG(ERROR) << "YUYV422ToNV12: output data is invalid";
        return false;
    }

    int result = libyuv::YUY2ToNV12(yuyv422_data, cols * 2, nv12_data, cols, nv12_data + cols * rows, cols, cols, rows);
    if(result != 0)
    {
        LOG(ERROR) << "YUYV422ToNV12: convert failed";
        return false;
    }

    return true;
}

//YUYV422ToYUV420
holo::bool_t YUYV422ToYUV420P(uint8_t* yuyv422_data, uint8_t* yuv420p_data, const uint32_t cols, const uint32_t rows)
{
    if (nullptr == yuyv422_data)
    {
        LOG(ERROR) << "YUYV422ToYUV420P: input data is invalid";
        return false;
    }
    else if (nullptr == yuv420p_data)
    {
        LOG(ERROR) << "YUYV422ToYUV420P: output data is invalid";
        return false;
    }

    int result = libyuv::YUY2ToI420(yuyv422_data, cols * 2, yuv420p_data, cols, yuv420p_data + cols * rows, cols / 2, yuv420p_data + cols * rows * 5 / 4, cols / 2, cols, rows);
    if(result != 0)
    {
        LOG(ERROR) << "YUYV422ToYUV420P: convert failed";
        return false;
    }

    return true;
}

//NV12ToYUV420P
holo::bool_t NV12ToYUV420P(uint8_t* nv12_data, uint8_t* yuv420p_data, const uint32_t cols, const uint32_t rows)
{
    if (nullptr == nv12_data)
    {
        LOG(ERROR) << "NV12ToYUV420P: input data is invalid";
        return false;
    }
    else if (nullptr == yuv420p_data)
    {
        LOG(ERROR) << "NV12ToYUV420P: output data is invalid";
        return false;
    }

    int result = libyuv::NV12ToI420(nv12_data, cols, nv12_data + cols * rows, cols, 
                                    yuv420p_data, cols, yuv420p_data + cols * rows, cols / 2, yuv420p_data + cols * rows * 5 / 4, cols / 2, cols, rows);
    if(result != 0)
    {
        LOG(ERROR) << "NV12ToYUV420P: convert failed";
        return false;
    }

    return true;
}

//YUV420PToRGB24
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

    int result = libyuv::I420ToRGB24(yuv420p_data, cols, yuv420p_data + cols * rows * 5 / 4, cols / 2, yuv420p_data + cols * rows, cols / 2,
                                     rgb24_data, cols * 3, cols, rows);
    if(result != 0)
    {
        LOG(ERROR) << "YUV420PToRGB24: convert failed";
        return false;
    }

    return true;
}
//YUV420PToNV12
holo::bool_t YUV420PToNV12(uint8_t* yuv420p_data, uint8_t* nv12_data, const uint32_t cols, const uint32_t rows)
{
    if (nullptr == yuv420p_data)
    {
        LOG(ERROR) << "YUV420PToNV12: input data is invalid";
        return false;
    }
    else if (nullptr == nv12_data)
    {
        LOG(ERROR) << "YUV420PToNV12: output data is invalid";
        return false;
    }

    int result = libyuv::I420ToNV12(yuv420p_data, cols, yuv420p_data + cols * rows, cols / 2, yuv420p_data + cols * rows * 5 / 4, cols / 2, 
                                    nv12_data, cols, nv12_data + cols * rows, cols, cols, rows);
    if(result != 0)
    {
        LOG(ERROR) << "YUV420PToNV12: convert failed";
        return false;
    }

    return true;
}
//RGB24ToYUV420P
holo::bool_t RGB24ToYUV420P(uint8_t* rgb24_data, uint8_t* yuv420p_data, const uint32_t cols, const uint32_t rows)
{
    if (nullptr == rgb24_data)
    {
        LOG(ERROR) << "RGB24ToYUV420P: input data is invalid";
        return false;
    }
    else if (nullptr == yuv420p_data)
    {
        LOG(ERROR) << "RGB24ToYUV420P: output data is invalid";
        return false;
    }

    int result = libyuv::RGB24ToI420(rgb24_data, cols * 3, yuv420p_data, cols, yuv420p_data + cols * rows * 5 / 4, cols / 2, yuv420p_data + cols * rows, cols / 2, cols, rows);
    if(result != 0)
    {
        LOG(ERROR) << "RGB24ToYUV420P: convert failed";
        return false;
    }

    return true;
}
//UYVY422ToNV12
holo::bool_t UYVY422ToNV12(uint8_t* uyvy422_data, uint8_t* nv12_data, const uint32_t cols, const uint32_t rows)
{
    if (nullptr == uyvy422_data)
    {
        LOG(ERROR) << "UYVY422ToNV12: input data is invalid";
        return false;
    }
    else if (nullptr == nv12_data)
    {
        LOG(ERROR) << "UYVY422ToNV12: output data is invalid";
        return false;
    }

    int result = libyuv::UYVYToNV12(uyvy422_data, cols * 2, nv12_data, cols, nv12_data + cols * rows, cols, cols, rows);
    if(result != 0)
    {
        LOG(ERROR) << "UYVY422ToNV12: convert failed";
        return false;
    }

    return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//YUYV422ToNV12
holo::bool_t YUYV422ToNV12(holo::Image& yuyv422_image, holo::Image& nv12_image)
{
    if (yuyv422_image.GetEncoding() != holo::Image::Encoding::YUYV)
    {
        LOG(ERROR) << "YUYV422ToNV12: the holo::Image you want input is not a YUYV422 format";
        return false;
    }

    if (nv12_image.GetEncoding() != holo::Image::Encoding::NV12)
    {
        LOG(ERROR) << "YUYV422ToNV12: the holo::Image you want output is not a NV12 format";
        return false;
    }

    if ((yuyv422_image.GetPixelCols() != nv12_image.GetPixelCols()) || 
        (yuyv422_image.GetPixelRows() != nv12_image.GetPixelRows()))
    {
        LOG(ERROR) << "YUYV422ToNV12: The resolution of the image to be input and the image to be output are inconsistent";
        return false;
    }

    int result = libyuv::YUY2ToNV12(yuyv422_image.GetData(), 
                                    yuyv422_image.GetPixelCols() * 2, 
                                    nv12_image.GetData(), 
                                    yuyv422_image.GetPixelCols(), 
                                    nv12_image.GetData() + yuyv422_image.GetPixelCols() * yuyv422_image.GetPixelRows(), 
                                    yuyv422_image.GetPixelCols(), 
                                    yuyv422_image.GetPixelCols(), 
                                    yuyv422_image.GetPixelRows());
    if(result != 0)
    {
        LOG(ERROR) << "YUYV422ToNV12: convert failed";
        return false;
    }

    return true;
}

//YUYV422ToYUV420P
holo::bool_t YUYV422ToYUV420P(holo::Image& yuyv422_image, holo::Image& yuv420p_image)
{
    if (yuyv422_image.GetEncoding() != holo::Image::Encoding::YUYV)
    {
        LOG(ERROR) << "YUYV422ToYUV420P: the holo::Image you want input is not a YUYV422 format";
        return false;
    }

    if (yuv420p_image.GetEncoding() != holo::Image::Encoding::YV12)
    {
        LOG(ERROR) << "YUYV422ToYUV420P: the holo::Image you want output is not a YUV420P format";
        return false;
    }

    if ((yuyv422_image.GetPixelCols() != yuv420p_image.GetPixelCols()) || 
        (yuyv422_image.GetPixelRows() != yuv420p_image.GetPixelRows()))
    {
        LOG(ERROR) << "YUYV422ToYUV420P: The resolution of the image to be input and the image to be output are inconsistent";
        return false;
    }

    int result = libyuv::YUY2ToI420(yuyv422_image.GetData(), 
                                    yuyv422_image.GetPixelCols() * 2, 
                                    yuv420p_image.GetData(), 
                                    yuyv422_image.GetPixelCols(), 
                                    yuv420p_image.GetData() + yuyv422_image.GetPixelCols() * yuyv422_image.GetPixelRows(), 
                                    yuyv422_image.GetPixelCols() / 2, 
                                    yuv420p_image.GetData() + yuyv422_image.GetPixelCols() * yuyv422_image.GetPixelRows() * 5 / 4, 
                                    yuyv422_image.GetPixelCols() / 2, 
                                    yuyv422_image.GetPixelCols(), 
                                    yuyv422_image.GetPixelRows());
    if(result != 0)
    {
        LOG(ERROR) << "YUYV422ToYUV420P: convert failed";
        return false;
    }

    return true;
}

//NV12ToYUV420P
holo::bool_t NV12ToYUV420P(holo::Image& nv12_image, holo::Image& yuv420p_image)
{
    if (nv12_image.GetEncoding() != holo::Image::Encoding::NV12)
    {
        LOG(ERROR) << "NV12ToYUV420P: the holo::Image you want input is not a NV12 format";
        return false;
    }

    if (yuv420p_image.GetEncoding() != holo::Image::Encoding::YV12)
    {
        LOG(ERROR) << "NV12ToYUV420P: the holo::Image you want output is not a YUV420P format";
        return false;
    }

    if ((nv12_image.GetPixelCols() != yuv420p_image.GetPixelCols()) || 
        (nv12_image.GetPixelRows() != yuv420p_image.GetPixelRows()))
    {
        LOG(ERROR) << "NV12ToYUV420P: The resolution of the image to be input and the image to be output are inconsistent";
        return false;
    }

    int result = libyuv::NV12ToI420(nv12_image.GetData(), 
                                    nv12_image.GetPixelCols(), 
                                    nv12_image.GetData() + nv12_image.GetPixelCols() * nv12_image.GetPixelRows(), 
                                    nv12_image.GetPixelCols(), 
                                    yuv420p_image.GetData(), 
                                    nv12_image.GetPixelCols(), 
                                    yuv420p_image.GetData() + nv12_image.GetPixelCols() * nv12_image.GetPixelRows(), 
                                    nv12_image.GetPixelCols() / 2, 
                                    yuv420p_image.GetData() + nv12_image.GetPixelCols() * nv12_image.GetPixelRows() * 5 / 4, 
                                    nv12_image.GetPixelCols() / 2, 
                                    nv12_image.GetPixelCols(), 
                                    nv12_image.GetPixelRows());
    if(result != 0)
    {
        LOG(ERROR) << "NV12ToYUV420P: convert failed";
        return false;
    }

    return true;
}

//YUV420PToRGB24
holo::bool_t YUV420PToRGB24(holo::Image& yuv420p_image, holo::Image& rgb24_image)
{
    if (yuv420p_image.GetEncoding() != holo::Image::Encoding::YV12)
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

    int result = libyuv::I420ToRGB24(yuv420p_image.GetData(), 
                                     yuv420p_image.GetPixelCols(), 
                                     yuv420p_image.GetData() + yuv420p_image.GetPixelCols() * yuv420p_image.GetPixelRows() * 5 / 4, 
                                     yuv420p_image.GetPixelCols() / 2, 
                                     yuv420p_image.GetData() + yuv420p_image.GetPixelCols() * yuv420p_image.GetPixelRows(), 
                                     yuv420p_image.GetPixelCols() / 2,
                                     rgb24_image.GetData(), 
                                     yuv420p_image.GetPixelCols() * 3, 
                                     yuv420p_image.GetPixelCols(), 
                                     yuv420p_image.GetPixelRows());
    if(result != 0)
    {
        LOG(ERROR) << "YUV420PToRGB24: convert failed";
        return false;
    }

    return true;
}

//YUV420PToNV12
holo::bool_t YUV420PToNV12(holo::Image& yuv420p_image, holo::Image& nv12_image)
{
    if (yuv420p_image.GetEncoding() != holo::Image::Encoding::YV12)
    {
        LOG(ERROR) << "YUV420PToNV12: the holo::Image you want input is not a YUV420P format";
        return false;
    }

    if (nv12_image.GetEncoding() != holo::Image::Encoding::NV12)
    {
        LOG(ERROR) << "YUV420PToNV12: the holo::Image you want input is not a NV12 format";
        return false;
    }

    if ((yuv420p_image.GetPixelCols() != nv12_image.GetPixelCols()) || 
        (yuv420p_image.GetPixelRows() != nv12_image.GetPixelRows()))
    {
        LOG(ERROR) << "YUV420PToNV12: The resolution of the image to be input and the image to be output are inconsistent";
        return false;
    }

    int result = libyuv::I420ToNV12(yuv420p_image.GetData(), 
                                    yuv420p_image.GetPixelCols(), 
                                    yuv420p_image.GetData() + yuv420p_image.GetPixelCols() * yuv420p_image.GetPixelRows(), 
                                    yuv420p_image.GetPixelCols() / 2, 
                                    yuv420p_image.GetData() + yuv420p_image.GetPixelCols() * yuv420p_image.GetPixelRows() * 5 / 4, 
                                    yuv420p_image.GetPixelCols() / 2, 
                                    nv12_image.GetData(), 
                                    yuv420p_image.GetPixelCols(), 
                                    nv12_image.GetData() + yuv420p_image.GetPixelCols() * yuv420p_image.GetPixelRows(), 
                                    yuv420p_image.GetPixelCols(), 
                                    yuv420p_image.GetPixelCols(), 
                                    yuv420p_image.GetPixelRows());
    if(result != 0)
    {
        LOG(ERROR) << "YUV420PToNV12: convert failed";
        return false;
    }

    return true;
}

//RGB24ToYUV420P
holo::bool_t RGB24ToYUV420P(holo::Image& rgb24_image, holo::Image& yuv420p_image)
{
    if (rgb24_image.GetEncoding() != holo::Image::Encoding::RGB)
    {
        LOG(ERROR) << "RGB24ToYUV420P: the holo::Image you want input is not a RGB24 format";
        return false;
    }

    if (yuv420p_image.GetEncoding() != holo::Image::Encoding::YV12)
    {
        LOG(ERROR) << "RGB24ToYUV420P: the holo::Image you want input is not a YUV420P format";
        return false;
    }

    if ((rgb24_image.GetPixelCols() != yuv420p_image.GetPixelCols()) || 
        (rgb24_image.GetPixelRows() != yuv420p_image.GetPixelRows()))
    {
        LOG(ERROR) << "RGB24ToYUV420P: The resolution of the image to be input and the image to be output are inconsistent";
        return false;
    }

    int result = libyuv::RGB24ToI420(rgb24_image.GetData(), 
                                     rgb24_image.GetPixelCols() * 3, 
                                     yuv420p_image.GetData(), 
                                     rgb24_image.GetPixelCols(), 
                                     yuv420p_image.GetData() + rgb24_image.GetPixelCols() * rgb24_image.GetPixelRows() * 5 / 4, 
                                     rgb24_image.GetPixelCols() / 2, 
                                     yuv420p_image.GetData() + rgb24_image.GetPixelCols() * rgb24_image.GetPixelRows(), 
                                     rgb24_image.GetPixelCols() / 2, 
                                     rgb24_image.GetPixelCols(), 
                                     rgb24_image.GetPixelRows());
    if(result != 0)
    {
        LOG(ERROR) << "RGB24ToYUV420P: convert failed";
        return false;
    }

    return true;
}
//UYVY422ToNV12
holo::bool_t UYVY422ToNV12(holo::Image& uyvy422_image, holo::Image& nv12_image)
{
    if (uyvy422_image.GetEncoding() != holo::Image::Encoding::UYVY)
    {
        LOG(ERROR) << "UYVY422ToNV12: the holo::Image you want input is not a UYVY422 format";
        return false;
    }

    if (nv12_image.GetEncoding() != holo::Image::Encoding::NV12)
    {
        LOG(ERROR) << "UYVY422ToNV12: the holo::Image you want input is not a NV12 format";
        return false;
    }

    if ((uyvy422_image.GetPixelCols() != nv12_image.GetPixelCols()) || 
        (uyvy422_image.GetPixelRows() != nv12_image.GetPixelRows()))
    {
        LOG(ERROR) << "UYVY422ToNV12: The resolution of the image to be input and the image to be output are inconsistent";
        return false;
    }

    int result = libyuv::UYVYToNV12(uyvy422_image.GetData(), 
                                    uyvy422_image.GetPixelCols() * 2, 
                                    nv12_image.GetData(), 
                                    uyvy422_image.GetPixelCols(), 
                                    nv12_image.GetData() + uyvy422_image.GetPixelCols() * uyvy422_image.GetPixelRows(), 
                                    uyvy422_image.GetPixelCols(), 
                                    uyvy422_image.GetPixelCols(), 
                                    uyvy422_image.GetPixelRows());
    if(result != 0)
    {
        LOG(ERROR) << "UYVY422ToNV12: convert failed";
        return false;
    }

    return true;
}
}  // namespace hololibyuv
}  // namespace image
}  // namespace sensors
}  // namespace holo