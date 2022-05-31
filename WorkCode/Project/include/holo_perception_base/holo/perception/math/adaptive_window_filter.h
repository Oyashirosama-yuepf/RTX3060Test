/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file adaptive_window_filter.h
 * @brief This header file defines adaptive window filter.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-06-24"
 */
#ifndef HOLO_PERCEPTION_MATH_ADAPTIVE_WINDOW_FILTER_H_
#define HOLO_PERCEPTION_MATH_ADAPTIVE_WINDOW_FILTER_H_

#include <holo/perception/math/first_order_adaptive_windowing.h>
#include <holo/perception/math/recursive_least_square_filter.h>

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
 * @brief Select RLS's forgetting factor automatically using FOAW's window size
 *
 * @tparam T data type
 */
template <typename T>
class AdaptiveWindowFilterT
{
public:
    using Scalar   = T;
    using RLSType  = RecursiveLeastSquareFilterT<Scalar>;
    using RLSPtr   = std::shared_ptr<RLSType>;
    using FOAWType = FirstOrderAdaptiveWindowingT<Scalar>;
    using FOAWPtr  = std::shared_ptr<FOAWType>;

    /**
     * @brief Construct a new Adaptive Window Filter T object
     *
     * @param max_window_size max history window size
     * @param max_delta max delta value between observed value and value of the first order approximation
     * @param min_forget_factor min forget factor of RLS filter
     * @param sigma initial variance of the RLS filter
     * @param degree polynomial degree of the RLS filter
     */
    AdaptiveWindowFilterT(size_t const max_window_size, Scalar const max_delta, Scalar const min_forget_factor,
                          Scalar const sigma, uint8_t const degree);

    /**
     * @brief Update the filter
     *
     * @param x the variable
     * @param y the function value
     * @return Scalar smoothed function value
     */
    Scalar Update(Scalar const x, Scalar const y);

    /**
     * @brief Get the current derivative
     *
     * @return Scalar current derivative
     */
    Scalar GetDerivative() const
    {
        return rls_ptr_->GetDerivative();
    }

private:
    size_t  max_window_size_;    ///< max history window size
    Scalar  min_forget_factor_;  ///< min forget factor
    FOAWPtr foaw_ptr_;
    RLSPtr  rls_ptr_;
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_MATH_ADAPTIVE_WINDOW_FILTER_H_
