/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file derivative_estimator.hpp
 * @brief This header file defines implementation of derivative estimator.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-04-28"
 */
#ifndef HOLO_PERCEPTION_MATH_DERIVATIVE_ESTIMATOR_HPP_
#define HOLO_PERCEPTION_MATH_DERIVATIVE_ESTIMATOR_HPP_

#include <holo/perception/math/derivative_estimator.h>

#include <algorithm>
#include <cmath>

namespace holo
{
namespace perception
{
template <typename Scalar>
DerivativeEstimatorT<Scalar>::DerivativeEstimatorT(size_t const window_size, size_t const span_steps,
                                                   size_t const start_steps, Scalar const max_value,
                                                   Scalar const y_length_scale, Scalar const y_variance,
                                                   Scalar const y_noise_variance, Scalar const d_length_scale,
                                                   Scalar const d_variance, Scalar const d_noise_variance)
  : window_size_(window_size)
  , span_steps_(span_steps)
  , start_steps_(start_steps)
  , max_value_(max_value)
  , y_length_scale_(y_length_scale)
  , y_variance_(y_variance)
  , y_noise_variance_(y_noise_variance)
  , d_length_scale_(d_length_scale)
  , d_variance_(d_variance)
  , d_noise_variance_(d_noise_variance)
{
    gpr_y_ptr_ = std::make_shared<GPRType>(y_length_scale, y_variance);
    gpr_d_ptr_ = std::make_shared<GPRType>(d_length_scale, d_variance);
}

template <typename Scalar>
void DerivativeEstimatorT<Scalar>::OnlineFit(Scalar const x, Scalar const y, Scalar& smoothed_y, Scalar& derivative)
{
    x_list_.push_back(x);
    y_list_.push_back(y);
    if (x_list_.size() == 1U)
    {
        smoothed_y = y;
        derivative = static_cast<Scalar>(0.0f);
        pred_y_list_.push_back(smoothed_y);
        pred_d_list_.push_back(derivative);
    }
    else
    {
        int32_t const total_steps = static_cast<int32_t>(x_list_.size());
        auto          x_iter      = x_list_.rbegin();
        for (int32_t i = -1; i >= -static_cast<int32_t>(window_size_) && x_iter != x_list_.rend(); --i)
        {
            int32_t      idx = total_steps + i;
            Scalar const x   = *x_iter;
            if (idx < 0 || static_cast<size_t>(std::abs(i)) > span_steps_)
            {
                break;
            }

            int32_t begin = std::max(0, idx - static_cast<int32_t>(span_steps_));
            int32_t end   = std::min(total_steps, idx + static_cast<int32_t>(span_steps_));
            Scalar  predicted_y, predicted_d;
            polyfitInterval(begin, end, x, predicted_y, predicted_d);

            if (i == -1)
            {
                pred_y_list_.push_back(predicted_y);
                pred_d_list_.push_back(predicted_d);
            }
            else
            {
                if (pred_y_list_.size() + i >= 0)
                {
                    auto y_iter = pred_y_list_.begin();
                    auto d_iter = pred_d_list_.begin();
                    for (int32_t count = 0; count < static_cast<int32_t>(pred_y_list_.size()) + i; ++count)
                    {
                        ++y_iter;
                        ++d_iter;
                    }
                    *y_iter = predicted_y;
                    *d_iter = predicted_d;
                }
            }
            --x_iter;
        }
        smoothAndEstimate(*(x_list_.rbegin()), smoothed_y, derivative);
    }
    popHistory();
}

template <typename Scalar>
void DerivativeEstimatorT<Scalar>::polyfitInterval(int32_t const begin, int32_t const end, Scalar const x,
                                                   Scalar& predicted_y, Scalar& predicted_d)
{
    int32_t const degree = std::max(1, std::min(end - begin - 1, 2));
    PolyFit2Type  polyfit(static_cast<uint8_t>(degree));

    std::vector<Point2Type> points;
    fecthMeasurementPoints(begin, end, points);
    bool_t flag = polyfit.Fit(points);
    if (flag == false)
    {
        predicted_y = points[points.size() / 2U].GetY();
        Scalar dy   = points[points.size() - 1U].GetY() - points[0U].GetY();
        Scalar dx   = points[points.size() - 1U].GetX() - points[0U].GetX();
        predicted_d = dy / dx;
    }
    else
    {
        predicted_y = computeValue(x, polyfit.GetCoeffs());
        predicted_d = computeDerivative(x, polyfit.GetCoeffs());
    }
}

template <typename Scalar>
void DerivativeEstimatorT<Scalar>::smoothAndEstimate(Scalar const x, Scalar& smoothed_y, Scalar& derivative)
{
    size_t const length = pred_y_list_.size();
    Scalar const y_mean = *(pred_y_list_.rbegin());
    Scalar       d_mean = static_cast<Scalar>(0.0);
    if (pred_d_list_.size() > start_steps_)
    {
        int32_t const degree = std::max(1, std::min(static_cast<int32_t>(length) - 1, 2));
        PolyFit2Type  polyfit(static_cast<uint8_t>(degree));

        std::vector<Point2Type> points;
        fetchPredictionPoints(points);
        bool_t flag = polyfit.Fit(points);
        if (flag == true)
        {
            d_mean = computeValue(x, polyfit.GetCoeffs());
        }
    }

    std::vector<Scalar> x_vec(length);
    std::vector<Scalar> y_vec(length);
    std::vector<Scalar> d_vec(length);

    auto x_iter = x_list_.rbegin();
    auto y_iter = pred_y_list_.rbegin();
    auto d_iter = pred_d_list_.rbegin();
    for (size_t count = 0U; count < length; ++count)
    {
        if (x_iter == x_list_.rend() || y_iter == pred_y_list_.rend() || d_iter == pred_d_list_.rend())
        {
            break;
        }
        size_t idx = length - 1 - count;
        x_vec[idx] = *x_iter;
        y_vec[idx] = *y_iter;
        d_vec[idx] = *d_iter;
        ++x_iter;
        ++y_iter;
        ++d_iter;
    }

    smoothed_y = gpr_y_ptr_->Predict(x, x_vec, y_vec, y_mean, y_noise_variance_);
    derivative = gpr_d_ptr_->Predict(x, x_vec, d_vec, d_mean, d_noise_variance_);
    derivative = std::max(-max_value_, std::min(max_value_, derivative));
}

template <typename Scalar>
void DerivativeEstimatorT<Scalar>::popHistory()
{
    while (x_list_.size() >= span_steps_ + window_size_)
    {
        x_list_.pop_front();
        y_list_.pop_front();
    }
    while (pred_y_list_.size() > window_size_)
    {
        pred_y_list_.pop_front();
        pred_d_list_.pop_front();
    }
}

template <typename Scalar>
void DerivativeEstimatorT<Scalar>::fecthMeasurementPoints(int32_t const begin, int32_t const end,
                                                          std::vector<Point2Type>& points)
{
    auto x_iter = x_list_.begin();
    auto y_iter = y_list_.begin();
    points.reserve(static_cast<size_t>(end - begin));
    for (int32_t count = 0U; count < static_cast<int32_t>(x_list_.size()); ++count)
    {
        if (count >= begin && count < end)
        {
            Point2Type pt(*x_iter, *y_iter);
            points.push_back(pt);
        }
        ++x_iter;
        ++y_iter;
    }
}

template <typename Scalar>
void DerivativeEstimatorT<Scalar>::fetchPredictionPoints(std::vector<Point2Type>& points)
{
    auto   x_iter = x_list_.begin();
    auto   d_iter = pred_d_list_.begin();
    size_t offset = x_list_.size() - pred_d_list_.size();
    for (size_t i = 0U; i < offset; ++i)
    {
        ++x_iter;
    }
    points.reserve(pred_d_list_.size());
    for (size_t count = 0U; count < pred_d_list_.size(); ++count)
    {
        Point2Type pt(*x_iter, *d_iter);
        points.push_back(pt);
        ++x_iter;
        ++d_iter;
    }
}

template <typename Scalar>
Scalar DerivativeEstimatorT<Scalar>::computeValue(Scalar const x, VectorType const& coeffs)
{
    Scalar result = static_cast<Scalar>(0.0f);
    for (auto i = 0U; i < coeffs.GetRows(); ++i)
    {
        result += coeffs(i) * std::pow(x, static_cast<Scalar>(i));
    }
    return result;
}

template <typename Scalar>
Scalar DerivativeEstimatorT<Scalar>::computeDerivative(Scalar const x, VectorType const& coeffs)
{
    Scalar result = static_cast<Scalar>(0.0f);
    for (auto i = 1U; i < coeffs.GetRows(); ++i)
    {
        result += i * coeffs(i) * std::pow(x, static_cast<Scalar>(i - 1));
    }
    return result;
}

}  // namespace perception
}  // namespace holo

#endif  //! HOLO_PERCEPTION_MATH_GAUSSIAN_PROCESS_REGRESSOR_HPP_
