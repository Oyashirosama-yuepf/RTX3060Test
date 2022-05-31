/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image.cpp
 * @brief image implemetation file
 * @author duyanwei@holomatic.com
 * @date 2019-11-29
 */

#include <holo/common/image.h>

namespace holo
{
namespace HoloOpencv
{
/**
 * @brief define cv mat meta data
 *
 */
struct CvMatMetaData
{
    int32_t rows;
    int32_t cols;
    int32_t type;
    int32_t channel;

    /**
     * @brief Construct a new Cv Mat Meta Data object
     *
     * @param width
     * @param height
     * @param encoding
     * @throw std::runtime_error if encoding is not supported
     */
    CvMatMetaData(uint16_t const width, uint16_t const height, Image::Encoding const encoding)
      : rows{static_cast<int32_t>(height)}, cols{static_cast<int32_t>(width)}, type{}, channel{}
    {
        if (encoding == Image::Encoding::RGB || encoding == Image::Encoding::BGR)
        {
            type    = CV_8UC3;
            channel = 3;
        }
        else if (encoding == Image::Encoding::GRAYSCALE)
        {
            type    = CV_8UC1;
            channel = 1;
        }
        else if ((encoding == Image::Encoding::YUYV) || (encoding == Image::Encoding::UYVY) ||
                 (encoding == Image::Encoding::YUV422P))
        {
            type    = CV_8UC2;
            channel = 2;
        }
        else if ((encoding == Image::Encoding::YU12) || (encoding == Image::Encoding::YV12) ||
                 (encoding == Image::Encoding::NV12) || (encoding == Image::Encoding::NV21))
        {
            type    = CV_8UC1;
            channel = 1;

            float64_t value = height * 1.5;
            rows            = static_cast<int32_t>(value);
        }
        else if (encoding == Image::Encoding::RGBA)
        {
            type    = CV_8UC4;
            channel = 4;
        }
        else
        {
            throw std::runtime_error("unsupported image encoding type");
        }
    }

    /**
     * @brief get size in byte
     *
     * @return uint64_t
     */
    uint64_t GetSizeInByte() const
    {
        int64_t size = rows * cols * channel;
        return static_cast<uint64_t>(size);
    }
};

}  // namespace HoloOpencv

Image::Image() : trigger_stamp_(), received_stamp_(), encoding_(Encoding::UNKNOWN), mat_()
{
}

Image::Image(const uint16_t width, const uint16_t height, const Encoding type, uint8_t* buffer,
             const uint32_t buffer_size)
  : trigger_stamp_(), received_stamp_(), encoding_(type)
{
    ConfigImage(width, height, type, buffer, buffer_size);
}

Image::Image(const Image& other)
  : trigger_stamp_(other.trigger_stamp_)
  , received_stamp_(other.received_stamp_)
  , encoding_(other.encoding_)
  , mat_(other.mat_)
{
}

Image& Image::operator=(const Image& other)
{
    this->trigger_stamp_  = other.trigger_stamp_;
    this->received_stamp_ = other.received_stamp_;
    this->encoding_       = other.encoding_;
    this->mat_            = other.mat_;

    return *this;
}

Image Image::Clone() const
{
    Image other;
    other.trigger_stamp_  = this->trigger_stamp_;
    other.received_stamp_ = this->received_stamp_;
    other.encoding_       = this->encoding_;
    other.mat_            = this->mat_.clone();
    
    return other;
}

void Image::ConfigImage(const uint16_t width, const uint16_t height, const Encoding type, uint8_t* buffer,
                        const uint32_t buffer_size)
{
    HoloOpencv::CvMatMetaData meta(width, height, type);
    if (buffer == nullptr)
    {
        mat_.create(meta.rows, meta.cols, meta.type);
    }
    else
    {
        if (meta.GetSizeInByte() != buffer_size)
        {
            throw std::runtime_error("image raw buffer size underflows or overflows!!!");
        }
        mat_ = cv::Mat(meta.rows, meta.cols, meta.type, buffer);
    }

    encoding_ = type;
}

void Image::CopyTo(Image& other) const
{
    other.trigger_stamp_  = this->trigger_stamp_;
    other.received_stamp_ = this->received_stamp_;
    other.encoding_       = this->encoding_;
    this->mat_.copyTo(other.mat_);
}

void Image::SetData(const uint8_t* const buffer, const uint32_t buffer_size, const uint16_t width,
                    const uint16_t height, const Encoding type)
{
    // create cv mat meta data
    HoloOpencv::CvMatMetaData meta(width, height, type);

    // size check
    if (meta.GetSizeInByte() != buffer_size)
    {
        throw std::runtime_error("image raw buffer size underflows or overflows!!!");
    }

    // copy image data
    mat_.create(meta.rows, meta.cols, meta.type);
    (void)memcpy(mat_.data, buffer, buffer_size);

    // set encoding
    encoding_ = type;
}

void Image::UpdateData(const uint8_t* const buffer, const uint32_t buffer_size)
{
    if (!mat_.isContinuous())
    {
        throw std::runtime_error("the image buffer is not continous");
    }

    const uint64_t image_size = mat_.total() * mat_.elemSize();

    if (image_size != buffer_size)
    {
        throw std::runtime_error("the image size is not the same as buffer size");
    }

    (void)memcpy(mat_.data, buffer, buffer_size);
}

uint16_t Image::GetWidth() const noexcept
{
    return static_cast<uint16_t>(mat_.cols);
}

uint16_t Image::GetPixelCols() const noexcept
{
    return static_cast<uint16_t>(mat_.cols);
}

uint16_t Image::GetHeight() const noexcept
{
    return static_cast<uint16_t>(mat_.rows);
}

uint16_t Image::GetPixelRows() const noexcept
{
    uint16_t rows = static_cast<int32_t>(mat_.rows);
    if ((encoding_ == Image::Encoding::YU12) || (encoding_ == Image::Encoding::YV12) ||
        (encoding_ == Image::Encoding::NV12) || (encoding_ == Image::Encoding::NV21))
    {
        rows = rows * 2 / 3;
    }
    return rows;
}

size_t Image::GetSize() const noexcept
{
    return mat_.rows * mat_.cols * mat_.elemSize();
}

uint8_t* Image::GetData() noexcept
{
    return mat_.data;
}

const uint8_t* Image::GetData() const noexcept
{
    return mat_.data;
}

}  // namespace holo
