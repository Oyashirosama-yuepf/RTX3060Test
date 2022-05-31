/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file size.h
 * @brief size header file
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#ifndef HOLO_LOCALIZATION_VISION_COMMON_SIZE_H_
#define HOLO_LOCALIZATION_VISION_COMMON_SIZE_H_

#include <type_traits>

// 3rdparty library, should be deprecated in future
#include <opencv2/core/types.hpp>

#include <holo/core/types.h>

namespace holo
{
namespace localization
{
/**
 * @brief define size class
 *
 * @tparam T can be signed or unsigned type
 */
template <typename T>
class SizeT
{
public:
    using Scalar = T;

    /**
     * @brief default constructor
     *
     */
    SizeT() noexcept : SizeT(static_cast<T>(0), static_cast<T>(0))
    {
    }

    /**
     * @brief constructor
     *
     * @param width width value
     * @param height height value
     *
     * @throw std::runtime_error if width or height is less than zero
     */
    SizeT(const T width, const T height) : width_(width), height_(height)
    {
        const T zero(static_cast<T>(0));
        if (width < zero || height < zero)
        {
            throw std::runtime_error("invalid size value");
        }
    }

    /**
     * @brief copy constructor
     *
     * @param other other size
     */
    SizeT(const SizeT& other) noexcept : width_(other.width_), height_(other.height_)
    {
    }

    /**
     * @brief copy assignment operator
     *
     */
    SizeT& operator=(SizeT const&) = default;

    /**
     * @brief destructor
     *
     */
    virtual ~SizeT() noexcept
    {
        static_assert(std::is_signed<T>::value, "SizeT only supports signed type");
    }

    /**
     * @brief get width
     *
     * @return width
     *
     */
    T GetWidth() const noexcept
    {
        return width_;
    }

    /**
     * @brief get height
     *
     * @return height
     *
     */
    T GetHeight() const noexcept
    {
        return height_;
    }

    /**
     * @brief get area
     *
     * @return area
     *
     */
    T GetArea() const noexcept
    {
        return width_ * height_;
    }

    /**
     * @brief return cv type
     *
     * @return cv type
     *
     * @deprecated please be cautious when using this API, it'll be deprecated soon !!!
     * @ref https://www.docs.opencv.org/3.3.1/d6/d50/classcv_1_1Size__.html
     */
    cv::Size_<T> GetCvType() const
    {
        return cv::Size_<T>(width_, height_);
    }

protected:
    T width_;   ///< width value
    T height_;  ///< height value

};  // class SizeT

using Size2i = SizeT<int32_t>;
using Size2f = SizeT<float32_t>;
using Size2d = SizeT<float64_t>;

}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_COMMON_SIZE_H_
