/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file velocity_estimator.hpp
 * @brief This header file defines .
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-01-10"
 */

#ifndef HOLO_PERCEPTION_SPACE_CONVERTOR_VELOCITY_ESTIMATOR_HPP_
#define HOLO_PERCEPTION_SPACE_CONVERTOR_VELOCITY_ESTIMZTOR_HPP_

#include <holo/log/hololog.h>
#include <sstream>

#include <holo/perception/space_convertor/velocity_estimator.h>

namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
VelocityEstimatorT<T>::VelocityEstimatorT(const uint8_t degree, const uint32_t sample_num, const T min_velocity,
                                          const T max_velocity)
  : degree_(degree), sample_num_(sample_num), min_velocity_(min_velocity), max_velocity_(max_velocity)
{
    if (degree < 1U)
    {
        throw std::runtime_error("Polynomial degree must >= 1");
    }
    if (sample_num <= degree)
    {
        throw std::runtime_error("Sample num must > degree");
    }
    if (min_velocity > max_velocity)
    {
        throw std::runtime_error("Min velocity must <= max velocity");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t VelocityEstimatorT<T>::Estimate(const std::list<DetectedObjectPtr>& track_history,
                                       holo::numerics::Vector3T<T>&        velocity) const
{
    // need at least 2 time step to compute velocity
    size_t  point_num = sample_num_;
    uint8_t degree    = degree_;
    if (track_history.size() < 2U)
    {
        return false;
    }

    if (track_history.size() < sample_num_)
    {
        point_num = track_history.size();
        // try to fit the highest degree
        if (degree_ >= point_num)
        {
            degree = point_num - 1U;
        }
    }
    else
    {
        point_num = sample_num_;
    }

    std::vector<Point2Type> x_points;
    std::vector<Point2Type> y_points;
    T                       velocity_x;
    T                       velocity_y;

    T      time   = fetchPoints(track_history, point_num, x_points, y_points);
    bool_t flag_x = computeVelocityByFitCurve(degree, x_points, time, velocity_x);
    bool_t flag_y = computeVelocityByFitCurve(degree, y_points, time, velocity_y);
    if (flag_x == false || flag_y == false)
    {
        return false;
    }
    // clamp velocity value
    clampVelocityValue(velocity_x);
    clampVelocityValue(velocity_y);
    velocity = holo::numerics::Vector3T<T>(velocity_x, velocity_y, static_cast<T>(0.0));
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
T VelocityEstimatorT<T>::fetchPoints(const std::list<DetectedObjectPtr>& history, const size_t sample_num,
                                     std::vector<Point2Type>& x_points, std::vector<Point2Type>& y_points) const
{
    // find the start iterator
    auto first_sample_iter = history.begin();
    for (size_t i = 0U; i < sample_num; ++i)
    {
        ++first_sample_iter;
    }

    T time = static_cast<T>(0.0);
    // using reverse iterator
    typename std::list<DetectedObjectPtr>::const_reverse_iterator rbegin(first_sample_iter);
    Timestamp                                                     base_time = (*rbegin)->GetTimestamp();
    for (auto iter = rbegin; iter != history.rend(); ++iter)
    {
        Duration duration   = (*iter)->GetTimestamp() - base_time;
        time                = static_cast<T>(duration.ToSec());
        Point3Type position = (*iter)->GetPosition();
        Point2Type x_pt(time, position.GetX());
        Point2Type y_pt(time, position.GetY());
        x_points.push_back(x_pt);
        y_points.push_back(y_pt);
    }

    return time;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t VelocityEstimatorT<T>::computeVelocityByFitCurve(const uint8_t degree, const std::vector<Point2Type>& points,
                                                        const T time, T& diff) const
{
    Polyfit2T<T> polyfit(degree);
    bool_t       flag = polyfit.Fit(points);
    if (flag == false)
    {
        std::stringstream ss;
        ss << "Compute velocity by fit curve failed: Degree = " << degree << ", Time = " << time << std::endl;
        ss << "Points = {";
        for (size_t i = 0U; i < points.size(); ++i)
        {
            ss << points[i];
        }
        ss << "}" << std::endl;
        LOG(WARNING) << ss.str();
        return false;
    }

    diff = computeDerivative(polyfit.GetCoeffs(), time);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
T VelocityEstimatorT<T>::computeDerivative(const VectorXType& coeffs, T x) const
{
    T diff = static_cast<T>(0.0);
    for (uint8_t i = 1U; i < coeffs.GetRows(); ++i)
    {
        diff += static_cast<T>(i) * coeffs[i] * pow(x, static_cast<T>(i - 1));
    }
    return diff;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline void VelocityEstimatorT<T>::clampVelocityValue(T& velocity_value) const
{
    if (velocity_value < min_velocity_)
    {
        velocity_value = min_velocity_;
    }
    if (velocity_value > max_velocity_)
    {
        velocity_value = max_velocity_;
    }
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_SPACE_CONVERTOR_VELOCITY_ESTIMATOR_HPP_
