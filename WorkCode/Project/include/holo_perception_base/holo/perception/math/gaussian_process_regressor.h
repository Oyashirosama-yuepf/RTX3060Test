/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gaussian_process_regressor.h
 * @brief This header file defines gaussian process regression.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-04-24"
 */

#ifndef HOLO_PERCEPTION_MATH_GAUSSIAN_PROCESS_REGRESSOR_H_
#define HOLO_PERCEPTION_MATH_GAUSSIAN_PROCESS_REGRESSOR_H_

#include <vector>

#include <holo/numerics/matrix.h>

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
 * @brief single variable gaussian process regressor
 *
 * @tparam T data type
 */
template <typename T>
class GaussianProcessRegressorT
{
public:
    using Scalar     = T;
    using MatrixType = numerics::MatrixXT<Scalar>;

    /**
     * @brief Construct a new Gaussian Process Regressor T object
     *
     * @param[in] length_scale determines the length of the 'wiggles' in the function
     * @param[in] variance determines the average distance of the function away from its mean
     * @ref https://en.wikipedia.org/wiki/Gaussian_process#Gaussian_process_prediction,_or_Kriging
     */
    GaussianProcessRegressorT(Scalar const length_scale, Scalar const variance);

    /**
     * @brief Predict value y based on training set <x_list, y_list> and the query point x
     *
     * @param[in] x the query point
     * @param[in] x_list training set x sequence data
     * @param[in] y_list training set y sequence data
     * @param[in] y_mean suggestion of the mean of y
     * @param[in] noise_variance noise variance of the y list
     * @return Scalar the predicted value of y
     */
    Scalar Predict(Scalar const x, std::vector<Scalar> const& x_list, std::vector<Scalar> const& y_list,
                   Scalar const y_mean, Scalar const noise_variance);

private:
    /**
     * @brief Compute the Radial Basis Function kernel(The Gaussian kernel)
     * @details RBF(x1, x2) = variance * exp(-0.5 * (x1 - x2)^2 / (length_scale^2))
     *
     * @param[in] x1 the first point
     * @param[in] x2 the second point
     * @return Scalar the RBF value
     * @ref https://www.cs.toronto.edu/~duvenaud/cookbook/
     */
    Scalar computeKernel(Scalar const x1, Scalar const x2) const;

private:
    Scalar     length_scale_;
    Scalar     variance_;
    MatrixType k_train_train_;
    MatrixType k_test_train_;
    MatrixType y_;
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_MATH_GAUSSIAN_PROCESS_REGRESSOR_H_
