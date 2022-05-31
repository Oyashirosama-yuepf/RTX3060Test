/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file recursive_least_square_filter.hpp
 * @brief This header file defines implementation of RLS filter.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-06-09"
 */
#ifndef HOLO_PERCEPTION_RECURSIVE_LEAST_SQUARE_FILTER_HPP_
#define HOLO_PERCEPTION_RECURSIVE_LEAST_SQUARE_FILTER_HPP_

#include <holo/perception/math/recursive_least_square_filter.h>

#include <cmath>

namespace holo
{
namespace perception
{
template <typename T>
RecursiveLeastSquareFilterT<T>::RecursiveLeastSquareFilterT(Scalar const lambda, Scalar const sigma,
                                                            uint8_t const degree)
  : lambda_(lambda), sigma_(sigma), degree_(degree), initialized_(false), one_(static_cast<Scalar>(1.0f))
{
    uint8_t const rows = degree_ + 1U;
    w_.Resize(rows, 1U);
    x_.Resize(rows, 1U);
    y_.Resize(1U, 1U);
    p_.Resize(rows, rows);

    w_.SetZero();
    x_.SetZero();
    y_.SetZero();
    p_.SetIdentity();

    x_(0U, 0U) = static_cast<Scalar>(1.0f);
    p_ *= sigma_;
}

template <typename T>
void RecursiveLeastSquareFilterT<T>::Update(Scalar const x, Scalar const y, Scalar& smoothed_y, Scalar& derivative)
{
    smoothed_y = Update(x, y);
    derivative = GetDerivative();
}

template <typename T>
T RecursiveLeastSquareFilterT<T>::Update(Scalar const x, Scalar const y)
{
    if (false == initialized_)
    {
        initialized_ = true;
        w_(0U, 0U)   = y;
    }
    else
    {
        for (uint8_t i = 1U; i < degree_ + 1U; ++i)
        {
            x_(i, 0U) = static_cast<Scalar>(powf(static_cast<float>(x), static_cast<float>(i)));
        }
        y_(0U, 0U) = y;

        Scalar inv_lamb = one_ / lambda_;
        Scalar denom    = (inv_lamb * x_.Transpose() * p_ * x_)(0U, 0U);
        auto   K        = inv_lamb * p_ * x_ / (denom + one_);

        auto e = y_ - x_.Transpose() * w_;
        w_     = w_ + K * e;
        p_     = inv_lamb * p_ - inv_lamb * K * x_.Transpose() * p_;
    }
    return (x_.Transpose() * w_)(0U, 0U);
}

template <typename T>
T RecursiveLeastSquareFilterT<T>::GetDerivative() const
{
    Scalar derivative = static_cast<Scalar>(0.0f);
    if (degree_ > 0U)
    {
        Scalar x = x_(1U, 0U);
        for (uint8_t i = 1U; i < degree_ + 1U; ++i)
        {
            derivative += static_cast<Scalar>(i) * w_(i, 0U) *
                          static_cast<Scalar>(powf(static_cast<float>(x), static_cast<float>(i - 1)));
        }
    }
    return derivative;
}

}  // namespace perception
}  // namespace holo

#endif  //! HOLO_PERCEPTION_RECURSIVE_LEAST_SQUARE_FILTER_HPP_
