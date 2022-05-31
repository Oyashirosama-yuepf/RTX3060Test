/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rect.h
 * @brief rect header file
 * @author duyanwei@holomatic.com
 * @date 2019-11-29
 */

#ifndef HOLO_LOCALIZATION_VISION_COMMON_RECT_H_
#define HOLO_LOCALIZATION_VISION_COMMON_RECT_H_

#include <holo/localization/vision/common/size.h>

namespace holo
{
namespace localization
{
/**
 * @brief define rect class
 *
 * @tparam T could be signed or unsigned type
 */
template <typename T>
class RectT : public SizeT<T>
{
public:
    using Base = SizeT<T>;
    using Base::Scalar;

    /**
     * @brief default constructor
     *
     */
    RectT() noexcept : RectT(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0))
    {
    }

    /**
     * @brief constructor
     *
     * @param x x start position of rectangle
     * @param y y start position of rectangle
     * @param width width of rectangle
     * @param height height of rectangle
     * @throw std::runtime_error if width or height is less than zero
     *
     */
    RectT(const T x, const T y, const T width, const T height) : Base(width, height), x_(x), y_(y)
    {
    }

    /**
     * @brief Construct a new Rect T object
     * @param x x start position of rectangle
     * @param y y start position of rectangle
     * @param size size of rectangle
     */
    RectT(const T x, const T y, const SizeT<T>& size) noexcept : Base(size), x_(x), y_(y)
    {
    }

    /**
     * @brief destructor
     *
     */
    virtual ~RectT() noexcept
    {
        static_assert(std::is_signed<T>::value, "RectT only supports signed type");
    }

    /**
     * @brief get top left x
     *
     * @return top left x
     *
     */
    T GetTopLeftX() const noexcept
    {
        return x_;
    }

    /**
     * @brief get top left y
     *
     * @return top left y
     *
     */
    T GetTopLeftY() const noexcept
    {
        return y_;
    }

    /**
     * @brief get bottom right x
     *
     * @return bottom right x
     *
     */
    T GetBottomRightX() const noexcept
    {
        return x_ + width_;
    }

    /**
     * @brief get bottom right y
     *
     * @return bottom right y
     *
     */
    T GetBottomRightY() const noexcept
    {
        return y_ + height_;
    }

    /**
     * @brief get size
     *
     * @return size
     *
     */
    SizeT<T> GetSize() const noexcept
    {
        return SizeT<T>(width_, height_);
    }

    /**
     * @brief return cv type
     *
     * @return cv type
     *
     * @deprecated please be cautious when using this API, it'll be deprecated soon !!!
     * @ref https://www.docs.opencv.org/3.3.1/d2/d44/classcv_1_1Rect__.html
     */
    cv::Rect_<T> GetCvType() const
    {
        return cv::Rect_<T>(x_, y_, width_, height_);
    }

protected:
    using Base::height_;  ///< height
    using Base::width_;   ///< width

    T x_;  ///< x value
    T y_;  ///< y value

};  // class RectT

using Rect2i = RectT<int32_t>;
using Rect2f = RectT<float32_t>;
using Rect2d = RectT<float64_t>;

}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_COMMON_RECT_H_
