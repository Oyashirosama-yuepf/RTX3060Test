/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file first_order_adaptive_windowing.h
 * @brief This header file defines first order adaptive windowing algorithm.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-06-23"
 */
#ifndef HOLO_PERCEPTION_MATH_FIRST_ORDER_ADAPTIVE_WINDOWING_H_
#define HOLO_PERCEPTION_MATH_FIRST_ORDER_ADAPTIVE_WINDOWING_H_

#include <list>
#include <stdlib.h>

#include <holo/core/types.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup math
 *
 * @{
 */

/**
 * @brief first order adaptive windowing algorithm
 *
 * @tparam T data type
 */
template <typename T>
class FirstOrderAdaptiveWindowingT
{
public:
    using Scalar = T;

    /**
     * @brief Construct a new First Order Adaptive Windowing T object
     *
     * @param max_window_size max history window size
     * @param max_delta max delta value between observed value and value of the first order approximation
     * @ref https://www.researchgate.net/publication/3332201_Discrete-Time_Adaptive_Windowing_for_Velocity_Estimation
     */
    FirstOrderAdaptiveWindowingT(size_t const max_window_size, Scalar const max_delta);

    /**
     * @brief Update states and estimate derivative (dy/dx)
     *
     * @param x the variable (e.g. current time)
     * @param y the function value (e.g. current position)
     * @return Scalar estimated derivative (e.g. current velocity)
     */
    Scalar Update(Scalar const x, Scalar const y);

    /**
     * @brief Get the current window size
     *
     * @return size_t current window size
     */
    size_t GetWindowSize() const
    {
        return window_size_;
    }

private:
    size_t max_window_size_;    ///< max history window size
    Scalar max_delta_;          ///< max delta value between observed value and value of the first order approximation
    size_t window_size_;        ///< current window_size
    Scalar derivative_;         ///< current derivative
    std::list<Scalar> x_list_;  ///< list of x values
    std::list<Scalar> y_list_;  ///< list of y values
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_MATH_FIRST_ORDER_ADAPTIVE_WINDOWING_H_
