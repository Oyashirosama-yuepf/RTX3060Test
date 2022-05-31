/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file keypoint.h
 * @brief This header file defines keypoint used for perception.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2020-09-16"
 */

#ifndef HOLO_PERCEPTION_COMMON_KEYPOINT_H_
#define HOLO_PERCEPTION_COMMON_KEYPOINT_H_

#include <holo/core/epsilon.h>
#include <holo/core/types.h>
#include <holo/vision/keypoint2.h>
#include <holo/vision/keypoint3.h>
#include <iomanip>

namespace holo
{
namespace perception
{
/**
 * @addtogroup common
 *
 * @{
 */

/**
 * @brief define KeyPoint
 *
 * @tparam T
 */
template <typename T>
class KeyPointT
{
public:
    using Scalar            = T;
    using BaseKeyPoint2Type = holo::vision::KeyPoint2T<Scalar>;
    using BaseKeyPoint3Type = holo::vision::KeyPoint3T<Scalar>;
    using KeyPointType      = KeyPointT<Scalar>;
    Scalar const tol        = holo::EpsilonT<Scalar>::value;

    /**
     * @brief Default Constructor
     *
     */
    KeyPointT() noexcept
      : x_(static_cast<Scalar>(0.0))
      , y_(static_cast<Scalar>(0.0))
      , z_(static_cast<Scalar>(0.0))
      , confidence_(static_cast<Scalar>(0.0))
      , visibility_(false)
    {
    }

    /**
     * @brief Constructor with params
     *
     * @param x, x value
     * @param y, y value
     * @param z, z value, when used in 2D dimension, set it as zero
     * @param confidence the confidence of point
     * @param visibility the visibility of point
     * @throw std::range_error throw, if confidence is not in [0.0f, 1.0f]
     */
    KeyPointT(Scalar const x, Scalar const y, Scalar const z, float32_t const confidence, bool_t const visibility)
      : x_(x), y_(y), z_(z), confidence_(confidence), visibility_(visibility)
    {
        if (confidence_ < 0.0f || confidence_ > 1.0f)
        {
            throw std::range_error("Confidence should be between 0.0 and 1.0!");
        }
    }

    /**
     * @brief Desconstructor
     *
     */
    ~KeyPointT() = default;

    /**
     * @brief Assign operator
     *
     * @param keypoint, the other keypoint object
     * @return KeyPointType&
     */
    KeyPointType& operator=(KeyPointType const& keypoint) noexcept;

    /**
     * @brief Equal operator
     *
     * @param keypoint, other keypoint
     * @return bool_t, true if same, otherwise false
     */
    bool_t operator==(KeyPointType const& keypoint) const noexcept;

    /**
     * @brief Set x of keypoint
     *
     * @param x, x value
     */
    void SetX(Scalar const x) noexcept
    {
        x_ = x;
    }

    /**
     * @brief Set y of keypoint
     *
     * @param y, y value
     */
    void SetY(Scalar const y) noexcept
    {
        y_ = y;
    }

    /**
     * @brief Set z of keypoint
     *
     * @param z, z value, when used in 2d dimension, just set it with zero.
     */
    void SetZ(Scalar const z) noexcept
    {
        z_ = z;
    }

    /**
     * @brief Set confidence of the keypoint
     *
     * @param confidence, should be between 0.0 and 1.0
     * @throw std::range_error throw, if confidence is not in [0.0f, 1.0f]
     */
    void SetConfidence(float32_t const confidence)
    {
        if (confidence < 0.0f || confidence > 1.0f)
        {
            throw std::range_error("Confidence should be between 0.0 and 1.0");
        }
        confidence_ = confidence;
    }

    /**
     * @brief Set visibility of the keypoint
     *
     * @param visibility, true if visible, otherwise false
     */
    void SetVisibility(bool_t const visibility) noexcept
    {
        visibility_ = visibility;
    }

    /**
     * @brief Get the x value of the keypoint
     *
     * @return Scalar
     */
    Scalar GetX() const noexcept
    {
        return x_;
    }

    /**
     * @brief Get the y value of the keypoint
     *
     * @return Scalar
     */
    Scalar GetY() const noexcept
    {
        return y_;
    }

    /**
     * @brief Get the z value of the keypoint
     *
     * @return Scalar
     */
    Scalar GetZ() const noexcept
    {
        return z_;
    }

    /**
     * @brief Get the confidence of the keypoint
     *
     * @return float32_t
     */
    float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }

    /**
     * @brief Check whether the keypoint's visibility
     *
     * @return bool_t, true for visibile, false for invisibile
     */
    bool_t IsVisible() const noexcept
    {
        return visibility_;
    }

    /**
     * @brief Compute the dist between two keypoints
     *
     * @param target, the other keypoint
     * @return Scalar, distance
     */
    Scalar Dist(KeyPointType const& target) const noexcept;

    /**
     * @brief Convert the keypoint to keypoint2 in holo_base
     *
     * @param keypoint2_out, type is holo_base/keypoint2
     * @note the z of the keypoint will be discarded
     */
    void ConvertToBaseKeyPoint2(BaseKeyPoint2Type& keypoint2_out) const noexcept;

    /**
     * @brief Convert the holo_base/KeyPoint2 to KeyPoint
     *
     * @param keypoint2_in, type is holo_base/KeyPoint2
     * @note the z of the keypoint will be zero in default
     */
    void ConvertFromBaseKeyPoint2(BaseKeyPoint2Type const& keypoint2_in) noexcept;

    void ConvertToBaseKeyPoint3(BaseKeyPoint3Type& keypoint3_out) const noexcept;

    void ConvertFromBaseKeyPoint3(BaseKeyPoint3Type const& keypoint3_in) noexcept;

    /**
     * @brief Convert to string for readable
     *
     * @return std::string
     */
    virtual std::string ToString() const
    {
        std::stringstream ss;
        ss << "KeyPoint: x = " << std::setiosflags(std::ios_base::fixed) << std::setprecision(2) << x_ << ", y = " << y_
           << ", z = " << z_ << ", confidence = " << confidence_ << ", visibility = " << visibility_ << std::endl;
        return ss.str();
    }

    /**
     * @brief output stream
     *
     * @param os std::ostream
     * @param in KeyPoint
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, KeyPointType const& in)
    {
        os << in.ToString();
        return os;
    }

private:
    Scalar    x_;
    Scalar    y_;
    Scalar    z_;
    float32_t confidence_;  ///< the value should be between 0.0 and 1.0
    bool_t    visibility_;
};

/**
 * @brief handy typedefs
 *
 */
using KeyPointf = KeyPointT<float32_t>;
using KeyPointd = KeyPointT<float64_t>;

/**
 * @}
 */

}  // namespace perception
}  // namespace holo
#endif  // !HOLO_PERCEPTION_COMMON_KEYPOINT_H_
