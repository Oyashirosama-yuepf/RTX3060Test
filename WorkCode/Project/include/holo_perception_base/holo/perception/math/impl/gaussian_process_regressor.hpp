/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gaussian_process_regrerror.hpp
 * @brief This header file defines implementation of single variable GP regressor.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-04-26"
 */
#ifndef HOLO_PERCEPTION_MATH_GAUSSIAN_PROCESS_REGRESSOR_HPP_
#define HOLO_PERCEPTION_MATH_GAUSSIAN_PROCESS_REGRESSOR_HPP_

#include <holo/perception/math/gaussian_process_regressor.h>

#include <cmath>
#include <vector>

namespace holo
{
namespace perception
{
template <typename Scalar>
GaussianProcessRegressorT<Scalar>::GaussianProcessRegressorT(Scalar const length_scale, Scalar const variance)
  : length_scale_(length_scale), variance_(variance)
{
}

template <typename Scalar>
Scalar GaussianProcessRegressorT<Scalar>::Predict(Scalar const x, std::vector<Scalar> const& x_list,
                                                  std::vector<Scalar> const& y_list, Scalar const y_mean,
                                                  Scalar const noise_variance)
{
    // 0. Prepare matrices
    k_train_train_.Resize(x_list.size(), x_list.size());
    k_test_train_.Resize(1U, x_list.size());
    y_.Resize(y_list.size(), 1U);

    // 1. Compute kernel matrices
    for (size_t i = 0U; i < x_list.size(); ++i)
    {
        k_test_train_(0U, i) = computeKernel(x, x_list[i]);
        for (size_t j = 0U; j < x_list.size(); ++j)
        {
            k_train_train_(i, j) = computeKernel(x_list[i], x_list[j]);
            if (i == j)
            {
                k_train_train_(i, j) += noise_variance;
            }
        }
    }

    // 2. Compute y matrix
    for (size_t i = 0U; i < y_list.size(); ++i)
    {
        y_(i, 0U) = y_list[i] - y_mean;
    }

    // 3. Compute posterior
    MatrixType y_mean_mat(1U, 1U);
    y_mean_mat(0U, 0U)        = y_mean;
    MatrixType posterior_mean = k_test_train_ * k_train_train_.Inverse() * y_ + y_mean_mat;
    return posterior_mean(0U, 0U);
}

template <typename Scalar>
inline Scalar GaussianProcessRegressorT<Scalar>::computeKernel(Scalar const x1, Scalar const x2) const
{
    Scalar const delta = x1 - x2;
    return variance_ * expf(-static_cast<Scalar>(0.5f) * delta * delta / (length_scale_ * length_scale_));
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_MATH_GAUSSIAN_PROCESS_REGRESSOR_HPP_
