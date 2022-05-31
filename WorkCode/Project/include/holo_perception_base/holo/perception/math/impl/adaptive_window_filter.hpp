/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file adaptive_window_filter.hpp
 * @brief This header file defines implementation of adaptive window filter.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-06-28"
 */
#ifndef HOLO_PERCEPTION_MATH_ADAPTIVE_WINDOW_FILTER_HPP_
#define HOLO_PERCEPTION_MATH_ADAPTIVE_WINDOW_FILTER_HPP_

#include <holo/perception/math/adaptive_window_filter.h>

namespace holo
{
namespace perception
{
template <typename T>
AdaptiveWindowFilterT<T>::AdaptiveWindowFilterT(size_t const max_window_size, Scalar const max_delta,
                                                Scalar const min_forget_factor, Scalar const sigma,
                                                uint8_t const degree)
  : min_forget_factor_(min_forget_factor)
{
    max_window_size_ = std::max(static_cast<size_t>(1U), max_window_size / static_cast<size_t>(2U));
    foaw_ptr_        = std::make_shared<FOAWType>(max_window_size, max_delta);
    rls_ptr_         = std::make_shared<RLSType>(min_forget_factor, sigma, degree);
}

template <typename T>
T AdaptiveWindowFilterT<T>::Update(Scalar const x, Scalar const y)
{
    foaw_ptr_->Update(x, y);
    size_t window_size   = foaw_ptr_->GetWindowSize();
    max_window_size_     = std::max(window_size, max_window_size_);
    Scalar forget_factor = static_cast<Scalar>(window_size) / static_cast<Scalar>(max_window_size_) *
                               (static_cast<Scalar>(1.0f) - min_forget_factor_) +
                           min_forget_factor_;
    rls_ptr_->SetForgetFactor(forget_factor);
    return rls_ptr_->Update(x, y);
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_MATH_ADAPTIVE_WINDOW_FILTER_HPP_
