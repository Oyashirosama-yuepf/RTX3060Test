/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mat.h
 * @brief mat header file
 * @author duyanwei@holomatic.com
 * @date 2019-11-29
 */

#ifndef HOLO_LOCALIZATION_VISION_COMMON_MAT_H_
#define HOLO_LOCALIZATION_VISION_COMMON_MAT_H_

// 3rdparty library, should be deprecated in future
#include <opencv2/opencv.hpp>

#include <holo/common/image.h>
#include <holo/localization/vision/common/range.h>
#include <holo/localization/vision/common/rect.h>

namespace holo
{
namespace localization
{
/**
 * @brief define mat class
 *
 * @details internally it uses cv::Mat from opencv
 *
 */
class Mat
{
public:
    /**
     * @brief default constructor
     *
     * @throw std::bad_alloc if initialization fails
     */
    Mat();

    /**
     * @brief Construct a new Mat object from holo::Image
     *
     * @param image holo image
     * @throw std::bad_alloc if initialization fails
     */
    explicit Mat(const holo::Image& image);

    /**
     * @brief copy constructor (shallow copy)
     *
     * @param other the other mat
     * @throw std::bad_alloc if initialization fails
     */
    Mat(const Mat& other);

    /**
     * @brief assignment operator (shallow copy)
     *
     * @param other the other mat
     * @return mat
     * @throw std::bad_alloc if initialization fails
     */
    Mat& operator=(const Mat& other);

    /**
     * @brief this operation assigns all the elements in maat to value
     *
     * @details only supports element of type uint8_t
     * @param value element value
     * @throw std::runtime_error if element type is not uint8_t
     */
    void operator=(const uint8_t value);

    /**
     * @brief extract a region of interest given row and col range
     *
     * @param row_range row range
     * @param col_range col range
     * @return roi
     */
    Mat operator()(const RangeInt& row_range, const RangeInt& col_range) const noexcept;

    /**
     * @brief extract a region of interest given an rectangle
     *
     * @param rect rectangle
     * @return roi
     */
    Mat operator()(const Rect2i& rect) const noexcept;

    /**
     * @brief destructor
     *
     * @throw std::bad_alloc if memory fails to release
     */
    virtual ~Mat() noexcept;

    /**
     * @brief check if mat is empty
     *
     * @return it return false if holo::Mat is initialized by default constructor
     */
    bool_t IsEmpty() const noexcept;

    /**
     * @brief image clone(deep copy)
     *
     * @return copied new mat
     * @throw std::bad_alloc if initialization fails
     */
    Mat Clone() const;

    /**
     * @brief image copy to (deep copy)
     *
     * @param other the other mat
     * @throw std::bad_alloc if initialization fails
     */
    void CopyTo(Mat& other) const;

    /**
     * @brief get width
     *
     * @return width
     */
    uint16_t GetWidth() const noexcept;

    /**
     * @brief get height
     *
     * @return height
     */
    uint16_t GetHeight() const noexcept;

    /**
     * @brief return const cv type
     *
     * @return const cv type
     *
     * @deprecated please be cautious when using this API, it'll be deprecated soon !!!
     * @ref https://www.docs.opencv.org/3.3.1/d3/d63/classcv_1_1Mat.html
     */
    const cv::Mat& GetCvType() const noexcept
    {
        return mat_;
    }

    /**
     * @brief return cv type
     *
     * @return cv type
     *
     * @deprecated please be cautious when using this API, it'll be deprecated soon !!!
     * @ref https://www.docs.opencv.org/3.3.1/d3/d63/classcv_1_1Mat.html
     */
    cv::Mat& GetCvType()
    {
        return mat_;
    }

protected:
    /**
     * @brief friendly API to initialize holo::Mat from cv::Mat
     *
     * @details internal usage only
     * @param mat mat type
     * @deprecated please be cautious when using this API
     *
     */
    Mat(const cv::Mat& mat) noexcept;

    cv::Mat mat_;  ///< cv mat to hold image data

};  // class Mat

}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_COMMON_MAT_H_
