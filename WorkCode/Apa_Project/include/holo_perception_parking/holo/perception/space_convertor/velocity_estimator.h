/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file velocity_estimator.h
 * @brief velocity estimator.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-01-09"
 */

#ifndef HOLO_PERCEPTION_SPACE_CONVERTOR_VELOCITY_ESTIMATOR_H_
#define HOLO_PERCEPTION_SPACE_CONVERTOR_VELOCITY_ESTIMATOR_H_

#include <list>

#include <holo/geometry/polyfit2.h>
#include <holo/perception/common/camera_detected_object.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup space_convertor
 *
 * @{
 */
/**
 * @brief estimate velocity of detected object by curve fitting
 *
 * @tparam T data type
 */
template <typename T>
class VelocityEstimatorT
{
public:
    using CameraDetectedObjectType = CameraDetectedObjectT<T>;
    using CameraDetectedObjectPtr  = std::shared_ptr<CameraDetectedObjectType>;
    using DetectedObjectType       = DetectedObjectT<T>;
    using DetectedObjectPtr        = std::shared_ptr<DetectedObjectType>;
    using Polyfit2Type             = holo::geometry::Polyfit2T<T>;
    using Point3Type               = holo::geometry::Point3T<T>;
    using Point2Type               = holo::geometry::Point2T<T>;
    using VectorXType              = holo::numerics::VectorXT<T>;

    /**
     * @brief Default constructor
     * @details Construct with default parameters
     *
     */
    VelocityEstimatorT()
      : degree_(3U), sample_num_(5U), min_velocity_(static_cast<T>(-20.0)), max_velocity_(static_cast<T>(20.0))
    {
    }

    /**
     * @brief Construct a new VelocityEstimatorT object
     *
     * @param degree degree of the curve fit polynomial
     * @param sample_num sample number for curve fit
     * @param min_velocity min output velocity
     * @param max_velocity max output velocity
     *
     * @throw std::runtime error if degree is 0 or sample num <= degree
     */
    VelocityEstimatorT(const uint8_t degree, const uint32_t sample_num, const T min_velocity, const T max_velocity);

    /**
     * @brief Estimate velocity of the newest detected object in the track_history
     * @details track_history.front() is the newest detected object pointer
     *
     * @param track_history the track_history
     * @param[out] velocity estimated velocity
     *
     * @return bool_t true if successfully estimate velocity else false
     */
    bool_t Estimate(const std::list<DetectedObjectPtr>& track_history, holo::numerics::Vector3T<T>& velocity) const;

    /**
     * @brief Set the Degree
     *
     * @param degree polynomial degree
     * @return true if degree is valid else false
     */
    bool_t SetDegree(const uint8_t degree) noexcept
    {
        if (degree > 0 && degree < sample_num_)
        {
            degree_ = degree;
            return true;
        }
        return false;
    }

    /**
     * @brief Set the sample num
     *
     * @param sample_num sample number
     * @return true if sample num is valid else false
     */
    bool_t SetSampleNum(const uint32_t sample_num) noexcept
    {
        if (sample_num > degree_)
        {
            sample_num_ = sample_num;
            return true;
        }
        return false;
    }

    /**
     * @brief Set the min velocity
     *
     * @param min_velocity
     */
    void SetMinVelocity(const T min_velocity) noexcept
    {
        min_velocity_ = min_velocity;
    }

    /**
     * @brief Set the Max Velocity
     *
     * @param max_velocity
     */
    void SetMaxVelocity(const T max_velocity) noexcept
    {
        max_velocity_ = max_velocity;
    }

    /**
     * @brief Get the Degree
     *
     * @return uint8_t polynomial degree
     */
    uint8_t GetDegree() const noexcept
    {
        return degree_;
    }

    /**
     * @brief Get the sample number
     *
     * @return uint32_t sample number
     */
    uint32_t GetSampleNum() const noexcept
    {
        return sample_num_;
    }

    /**
     * @brief Get the Min Velocity object
     *
     * @return T min velocity
     */
    T GetMinVelocity() const noexcept
    {
        return min_velocity_;
    }

    /**
     * @brief Get the Max Velocity object
     *
     * @return T velocity
     */
    T GetMaxVelocity() const noexcept
    {
        return max_velocity_;
    }

private:
    /**
     * @brief fetch data points for curve fitting from history
     *
     * @param history track history
     * @param sample_num data points number
     * @param x_points points of (time, position_x) pair
     * @param y_points points of (time, position_y) pair
     * @return T the current time from the first sample to current sample
     */
    T fetchPoints(const std::list<DetectedObjectPtr>& history, const size_t sample_num,
                  std::vector<Point2Type>& x_points, std::vector<Point2Type>& y_points) const;

    /**
     * @brief fit curve using sample points, and estimate current velocity
     *
     * @param degree degree of polynomial
     * @param points sample points
     * @param time duration time from start sample to current sample
     * @param[out] velocity current velocity(derivative of curve at current time)
     * @return bool_t true if fit success else false
     */
    bool_t computeVelocityByFitCurve(const uint8_t degree, const std::vector<Point2Type>& points, const T time,
                                     T& velocity) const;

    /**
     * @brief Compute derivative of the polynomial at x
     *
     * @param coeffs coefficents of the polynomial
     * @param x query point
     * @return T the derivative at x
     *
     * @note coeffs array:
     * coeffs[0] + coeffs[1]*x + coeffs[2]*x^2 + ...
     */
    T computeDerivative(const VectorXType& coeffs, T x) const;

    /**
     * @brief clamp velocity to interval [min_velocity_, max_velocity_]
     *
     * @param[in, out] velocity the velocity value of x or y direction
     */
    void clampVelocityValue(T& velocity) const;

private:
    uint8_t  degree_;
    uint32_t sample_num_;
    T        min_velocity_;
    T        max_velocity_;
};

/**
 * @}
 *
 */

}  // namespace perception
}  // namespace holo

#endif
