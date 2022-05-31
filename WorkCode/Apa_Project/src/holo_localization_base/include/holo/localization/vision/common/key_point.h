/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file key_point.h
 * @brief key_point header file
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#ifndef HOLO_LOCALIZATION_VISION_COMMON_KEY_POINT_H_
#define HOLO_LOCALIZATION_VISION_COMMON_KEY_POINT_H_

// 3rdparty library, should be deprecated in future
#include <opencv2/core/types.hpp>

#include <holo/core/types.h>
#include <holo/geometry/point2.h>

namespace holo
{
namespace localization
{
/**
 * @brief define key point class
 *
 */
class KeyPoint2f
{
public:
    using Point2f = holo::geometry::Point2f;

    /**
     * @brief default constructor
     *
     */
    KeyPoint2f() noexcept : KeyPoint2f(Point2f::Zero())
    {
    }

    /**
     * @brief Construct a new Key Point object
     *
     * @param pt coordinates of the keypoints
     * @param size diameter of the meaningful keypoint neighborhood
     * @param angle computed orientation of the keypoint (-1 if not applicable); it's in [0,360) degrees and measured
     *              relative to image coordinate system, ie in clockwise.
     * @param response the response by which the most strong keypoints have been selected. Can be used for the further
     *        sorting or subsampling
     * @param octave octave (pyramid layer) from which the keypoint has been extracted
     * @param class_id object class (if the keypoints need to be clustered by an object they belong to)
     */
    KeyPoint2f(const Point2f& pt, const float32_t size = 1.0f, const float32_t angle = -1.0f,
               const float32_t response = 0.0f, const int32_t octave = 0, const int32_t class_id = -1) noexcept
      : pt_(pt), size_(size), angle_(angle), response_(response), octave_(octave), class_id_(class_id)
    {
    }

    /**
     * @brief get point
     *
     * @return point
     *
     */
    const Point2f& GetPoint() const noexcept
    {
        return pt_;
    }

    /**
     * @brief get size
     *
     * @return size
     */
    float32_t GetSize() const noexcept
    {
        return size_;
    }

    /**
     * @brief get angle
     *
     * @return angle
     */
    float32_t GetAngle() const noexcept
    {
        return angle_;
    }

    /**
     * @brief get response
     *
     * @return response
     */
    float32_t GetResponse() const noexcept
    {
        return response_;
    }

    /**
     * @brief get octave
     *
     * @return octave
     */
    int32_t GetOctave() const noexcept
    {
        return octave_;
    }

    /**
     * @brief get class id
     *
     * @return class id
     */
    int32_t GetClassId() const noexcept
    {
        return class_id_;
    }

    /**
     * @brief return cv type
     *
     * @return cv type
     *
     * @deprecated please be cautious when using this API, it'll be deprecated soon !!!
     * @ref https://www.docs.opencv.org/3.3.1/d2/d29/classcv_1_1KeyPoint.html
     */
    cv::KeyPoint GetCvType() const
    {
        return cv::KeyPoint(pt_.GetX(), pt_.GetY(), size_, angle_, response_, octave_, class_id_);
    }

private:
    Point2f   pt_;        ///< coordindates of keypoints
    float32_t size_;      ///< diameter of meaningful keypoint neighbourhood
    float32_t angle_;     ///< key point angle
    float32_t response_;  ///< response of keypoints
    int32_t   octave_;    ///< extracted octave
    int32_t   class_id_;  ///< object class if clustered

};  // class KeyPoint2f

}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_COMMON_KEY_POINT_H_
