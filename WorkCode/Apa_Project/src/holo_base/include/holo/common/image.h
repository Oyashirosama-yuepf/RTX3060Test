/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image.h
 * @brief image header file
 * @author duyanwei@holomatic.com
 * @date 2019-11-29
 */

#ifndef HOLO_COMMON_IMAGE_H_
#define HOLO_COMMON_IMAGE_H_

// 3rdparty library, should be deprecated in future
#include <opencv2/opencv.hpp>

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
/**
 * @brief define image class
 *
 * @details
 *     a. it only supports rgb and grayscale type
 *     b. it leverages cv::Mat from OpenCV and does not handle "step", "stride" or "data alignment" explicitly but leave
 *        them to opencv
 */
class Image
{
public:
    /**
     * @brief internal encoding of image
     */
    enum class Encoding : uint8_t
    {
        RGB       = 0u,
        GRAYSCALE = 1u,
        YUYV      = 2u,
        UYVY      = 3u,
        YUV422P   = 4u,
        YU12      = 5u,
        YV12      = 6u,
        NV12      = 7u,
        NV21      = 8u,
        BGR       = 9u,
        RGBA      = 10u,
        UNKNOWN   = 255u,
    };

    /**
     * @brief default constructor
     *
     * @throw std::bad_alloc if initialization fails
     */
    Image();

    /**
     * @brief image constructor with image width, height and encoding
     *
     * @note the user should take care of the externally allocated memory if provided, it will not be deallocated inside
     *
     * @param width image width
     * @param height image height
     * @param type image encoding type
     * @param buffer external buffer, if provided, no new memory will be allocated
     * @param buffer_size external buffer size
     * @throw std::bad_alloc if initialization fails
     */
    Image(const uint16_t width, const uint16_t height, const Encoding type, uint8_t* buffer = nullptr,
          const uint32_t buffer_size = 0u);

    /**
     * @brief copy constructor (shallow copy)
     *
     * @param other the other image
     * @throw std::bad_alloc if initialization fails
     */
    Image(const Image& other);

    /**
     * @brief assignment operator (shallow copy)
     *
     * @param other the other image
     * @throw std::bad_alloc if initialization fails
     * @
     */
    Image& operator=(const Image& other);

    /**
     * @brief deep copy
     *
     * @return copied new image
     * @throw std::bad_alloc if initialization fails
     */
    Image Clone() const;

    /**
     * @brief configure the image parameters and re-alloc the space of image according to new parameters
     *
     * @note the user should take care of the externally allocated memory if provided, it will not be deallocated inside
     *
     * @param width image width
     * @param height image height
     * @param type image encoding type
     * @param buffer external buffer, if provided, no new memory will be allocated
     * @param buffer_size external buffer size
     * @throw std::bad_alloc if initialization fails
     */
    void ConfigImage(const uint16_t width, const uint16_t height, const Encoding type, uint8_t* buffer = nullptr,
                     const uint32_t buffer_size = 0u);

    /**
     * @brief deep copy
     *
     * @param other the other image
     * @throw std::bad_alloc if initialization fails
     */
    void CopyTo(Image& other) const;

    /**
     * @brief set trigger stamp
     *
     * @param stamp trigger stamp
     */
    inline void SetTriggerStamp(const holo::common::Timestamp& stamp) noexcept
    {
        trigger_stamp_ = stamp;
    }

    /**
     * @brief set received stamp
     *
     * @param stamp received stamp
     */
    inline void SetReceivedStamp(const holo::common::Timestamp& stamp) noexcept
    {
        received_stamp_ = stamp;
    }

    /**
     * @brief set image data
     *
     * @param buffer image raw data buffer
     * @param buffer_size image raw data buffer size
     * @param width image width
     * @param height image height
     * @param type image encoding type
     * @throw std::rumtime_error if buffer size overflows or underflows or encoding type is not supported
     */
    [[deprecated]] void SetData(const uint8_t* const buffer, const uint32_t buffer_size, const uint16_t width,
                                const uint16_t height, const Encoding type);

    /**
     * @brief update image data this function would not change the size of data
     *
     * @param buffer image raw data buffer
     * @param buffer_size image raw data buffer size
     * @throw std::rumtime_error if buffer size overflows or underflows or encoding type is not supported
     */
    void UpdateData(const uint8_t* const buffer, const uint32_t buffer_size);

    /**
     * @brief get trigger stamp
     *
     * @return trigger stamp
     *
     */
    const holo::common::Timestamp& GetTriggerStamp() const noexcept
    {
        return trigger_stamp_;
    }

    /**
     * @brief get received stamp
     *
     * @return received stamp
     */
    const holo::common::Timestamp& GetReceivedStamp() const noexcept
    {
        return received_stamp_;
    }

    /**
     * @brief friendly-API to get image stamp
     *
     * @return trigger stamp
     *
     */
    const holo::common::Timestamp& GetTimestamp() const noexcept
    {
        return trigger_stamp_;
    }

    /**
     * @brief get image encoding
     *
     * @return image encoding
     */
    Encoding GetEncoding() const noexcept
    {
        return encoding_;
    }

    /**
     * @brief return image width
     *
     * @return image width
     */
    uint16_t GetWidth() const noexcept;

    /**
     * @brief return image pixel format width
     * 
     * @return image pixel format width 
     */
    uint16_t GetPixelCols() const noexcept;

    /**
     * @brief return image height
     *
     * @return image height
     */
    uint16_t GetHeight() const noexcept;

    /**
     * @brief return image pixel format height
     * 
     * @return image pixel format height 
     */
    uint16_t GetPixelRows() const noexcept;

    /**
     * @brief return image memery size
     * 
     * @return image memery size 
     */
    size_t GetSize() const noexcept;

    /**
     * @brief get data
     *
     * @return image raw data pointer
     */
    uint8_t* GetData() noexcept;

    /**
     * @brief get data
     *
     * @return image raw data pointer
     */
    const uint8_t* GetData() const noexcept;

    /**
     * @brief return cv type
     *
     * @deprecated please be cautious when using this API, it'll be deprecated soon !!!
     *
     * @return cv mat
     */
    const cv::Mat& GetCvType() const
    {
        return mat_;
    }

private:
    holo::common::Timestamp trigger_stamp_;   ///< image trigger stamp
    holo::common::Timestamp received_stamp_;  ///< image received stamp
    Encoding                encoding_;        ///< image encoding
    cv::Mat                 mat_;             ///< cv mat

};  // class Image

}  // namespace holo

#endif  // HOLO_COMMON_IMAGE_H_
