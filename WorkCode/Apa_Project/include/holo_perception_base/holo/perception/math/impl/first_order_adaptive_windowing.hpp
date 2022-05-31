/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file first_order_adaptive_windowing.hpp
 * @brief This header file defines implementation of FOAW algorithm.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-06-23"
 */
#ifndef HOLO_PERCEPTION_MATH_FIRST_ORDER_ADAPTIVE_WINDOWING_HPP_
#define HOLO_PERCEPTION_MATH_FIRST_ORDER_ADAPTIVE_WINDOWING_HPP_

#include <holo/perception/math/first_order_adaptive_windowing.h>

#include <cmath>
#include <iterator>

namespace holo
{
namespace perception
{
template <typename T>
FirstOrderAdaptiveWindowingT<T>::FirstOrderAdaptiveWindowingT(size_t const max_window_size, Scalar const max_delta)
  : max_window_size_(max_window_size), max_delta_(max_delta), window_size_(0U), derivative_(static_cast<T>(0.0))
{
}

template <typename T>
T FirstOrderAdaptiveWindowingT<T>::Update(Scalar const x, Scalar const y)
{
    x_list_.push_back(x);
    y_list_.push_back(y);
    if (x_list_.size() > max_window_size_)
    {
        x_list_.pop_front();
        y_list_.pop_front();
    }

    if (x_list_.size() > 1U)
    {
        auto start_x_iter = ++x_list_.rbegin();
        auto start_y_iter = ++y_list_.rbegin();
        derivative_       = (y_list_.back() - *start_y_iter) / (x_list_.back() - *start_x_iter);
        // check if can increase window size
        bool_t can_increase_window = true;
        size_t max_len             = std::min(max_window_size_, x_list_.size());
        for (size_t i = 2U; i < max_len; ++i)
        {
            ++start_x_iter;
            ++start_y_iter;
            Scalar const start_x = *start_x_iter;
            Scalar const start_y = *start_y_iter;
            Scalar const slop    = (y_list_.back() - start_y) / (x_list_.back() - start_x);
            // check max delta
            auto test_x_iter = x_list_.rbegin();
            auto test_y_iter = y_list_.rbegin();
            for (size_t j = 1U; j < i; ++j)
            {
                ++test_x_iter;
                ++test_y_iter;
                Scalar const val_x = *test_x_iter;
                Scalar const val_y = *test_y_iter;
                Scalar const y_hat = start_y + slop * (val_x - start_x);
                Scalar const delta = std::fabs(y_hat - val_y);
                if (delta > max_delta_)
                {
                    can_increase_window = false;
                    break;
                }
            }
            if (false == can_increase_window)
            {
                window_size_ = i - 2U;
                break;
            }
            window_size_ = i - 1U;
            derivative_  = slop;
        }
    }
    return derivative_;
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_MATH_FIRST_ORDER_ADAPTIVE_WINDOWING_HPP_
