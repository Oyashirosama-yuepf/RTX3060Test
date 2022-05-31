/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file recursive_least_square_filter.h
 * @brief This header file defines RLS filter.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-06-09"
 */

#ifndef HOLO_PERCEPTION_MATH_RECURSIVE_LEAST_SQUARE_FILTER_H_
#define HOLO_PERCEPTION_MATH_RECURSIVE_LEAST_SQUARE_FILTER_H_

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

template <typename T>
class RecursiveLeastSquareFilterT
{
public:
    using Scalar     = T;
    using MatrixType = numerics::MatrixXT<Scalar>;

    /**
     * @brief Construct a new Recursive Least Square Filter T object
     *
     * @param lambda forget factor
     * @param sigma initial variance
     * @param degree degree of the polynomial
     *
     * @tparam T data type
     * @ref https://en.wikipedia.org/wiki/Recursive_least_squares_filter
     */
    RecursiveLeastSquareFilterT(Scalar const lambda, Scalar const sigma, uint8_t const degree);

    /**
     * @brief Update the filter
     *
     * @param x variable
     * @param y function value
     * @param smoothed_y smoothed function value
     * @param derivative estimated derivative (dy/dx)
     */
    void Update(Scalar const x, Scalar const y, Scalar& smoothed_y, Scalar& derivative);

    /**
     * @brief Update the filter
     *
     * @param x variable
     * @param y function value
     * @return Scalar smoothed function value
     */
    Scalar Update(Scalar const x, Scalar const y);

    /**
     * @brief Get current derivative
     *
     * @return Scalar estimated derivative (dy/dx)
     */
    Scalar GetDerivative() const;

    /**
     * @brief Set the Forget Factor
     *
     * @param forget_factor forget factor
     */
    void SetForgetFactor(Scalar const forget_factor)
    {
        lambda_ = forget_factor;
    }

private:
    Scalar     lambda_;       ///< forget factor
    Scalar     sigma_;        ///< initial variance
    Scalar     degree_;       ///< degree of the polynomial
    MatrixType w_;            ///< weight vector of RLS
    MatrixType x_;            ///< matrix of x
    MatrixType y_;            ///< matrix of y
    MatrixType p_;            ///< covariance matrix
    bool_t     initialized_;  ///< if the filter is initialized
    Scalar     one_;
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_MATH_RECURSIVE_LEAST_SQUARE_FILTER_H_
