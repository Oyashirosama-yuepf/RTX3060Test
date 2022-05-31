/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file range.h
 * @brief range header file
 * @author duyanwei@holomatic.com
 * @date 2019-11-29
 */

#ifndef HOLO_LOCALIZATION_VISION_COMMON_RANGE_H_
#define HOLO_LOCALIZATION_VISION_COMMON_RANGE_H_

#include <stdexcept>

// 3rdparty library, should be deprecated in future
#include <opencv2/core/types.hpp>

#include <holo/core/types.h>

namespace holo
{
namespace localization
{
/**
 * @brief define range class
 *
 * @details particularly range = [start, end) and in only supports int32_t
 */
class RangeInt
{
public:
    /**
     * @brief default constructor
     *
     * @details a range of [0, 1) is constructed
     *
     */
    RangeInt() noexcept : RangeInt(0, 1)
    {
    }

    /**
     * @brief constructor
     *
     * @param start start value
     * @param end end value
     * @throw throw exception if start > rend
     */
    RangeInt(const int32_t start, const int32_t end) : start_(start), end_(end)
    {
        if (start > end)
        {
            throw std::runtime_error("invalid start and end value in range");
        }
    }

    /**
     * @brief get start
     *
     * @return start
     */
    int32_t GetStart() const noexcept
    {
        return start_;
    }

    /**
     * @brief get end
     *
     * @return end
     *
     */
    int32_t GetEnd() const noexcept
    {
        return end_;
    }

    /**
     * @brief get size
     *
     * @return range size
     *
     */
    int32_t GetSize() const noexcept
    {
        return end_ - start_;
    }

    /**
     * @brief return cv type
     *
     * @return cv type
     *
     * @deprecated please be cautious when using this API, it'll be deprecated soon !!!
     * @ref https://www.docs.opencv.org/3.3.1/da/d35/classcv_1_1Range.html
     */
    cv::Range GetCvType() const
    {
        return cv::Range(start_, end_);
    }

private:
    int32_t start_;  ///< start value
    int32_t end_;    ///< end value

};  // class RangeInt

}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_COMMON_RANGE_H_
