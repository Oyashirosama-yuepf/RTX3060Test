/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file derivative_estimator.h
 * @brief This header file defines online derivative estimator.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-04-28"
 */
#ifndef HOLO_PERCEPTION_MATH_DERIVATIVE_ESTIMATOR_H_
#define HOLO_PERCEPTION_MATH_DERIVATIVE_ESTIMATOR_H_

#include <algorithm>
#include <list>
#include <sstream>
#include <vector>

#include <holo/geometry/point2.h>
#include <holo/geometry/polyfit2.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>
#include <holo/perception/math/gaussian_process_regressor.h>

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
 * @brief online derivative estimator
 *
 * @tparam T data type
 */
template <typename T>
class DerivativeEstimatorT
{
public:
    using Scalar       = T;
    using MatrixType   = numerics::MatrixXT<Scalar>;
    using VectorType   = numerics::VectorXT<Scalar>;
    using PolyFit2Type = holo::geometry::details::Polyfit2T<Scalar>;
    using Point2Type   = holo::geometry::details::Point2T<Scalar>;
    using GPRType      = GaussianProcessRegressorT<Scalar>;
    using GPRPtrType   = std::shared_ptr<GPRType>;

    /**
     * @brief Construct a new Derivative Estimator T object
     *
     * @param[in] window_size window size of stored measurements
     * @param[in] span_steps window size for curve fitting
     * @param[in] start_steps when to use curve fitting result as y_mean suggestion
     * @param[in] max_value estimated derivative shall in [-max_value, max_value]
     * @param[in] y_length_scale y value GP regressor length scale
     * @param[in] y_variance y value GP regressor variance
     * @param[in] y_noise_variance noise variance of y measurements
     * @param[in] d_length_scale derivative GP regressor length scale
     * @param[in] d_variance derivative GP regressor variance
     * @param[in] d_noise_variance noise variance of derivative measurements
     */
    DerivativeEstimatorT(size_t const window_size, size_t const span_steps, size_t const start_steps,
                         Scalar const max_value, Scalar const y_length_scale, Scalar const y_variance,
                         Scalar const y_noise_variance, Scalar const d_length_scale, Scalar const d_variance,
                         Scalar const d_noise_variance);

    /**
     * @brief estimate derivative and smooth y value
     *
     * @param[in] x measurement of x
     * @param[in] y measurement of y
     * @param[out] smoothed_y smoothed y value
     * @param[out] derivative estimated derivative
     */
    void OnlineFit(Scalar const x, Scalar const y, Scalar& smoothed_y, Scalar& derivative);

private:
    /**
     * @brief fit a 2 degree polynomial in interval [begin, end)
     *
     * @param[in] begin begin index
     * @param[in] end end sentinel
     * @param[in] x expand from this point
     * @param[out] predicted_y predicted y value at point x
     * @param[out] predicted_d predicted derivative at point x
     */
    void polyfitInterval(int32_t const begin, int32_t const end, Scalar const x, Scalar& predicted_y,
                         Scalar& predicted_d);

    /**
     * @brief smooth y value and estimate derivative
     *
     * @param[in] x query point
     * @param[out] smoothed_y smoothed y value at query point
     * @param[out] derivative estimated derivative at query point
     */
    void smoothAndEstimate(Scalar const x, Scalar& smoothed_y, Scalar& derivative);

    /**
     * @brief pop old history
     */
    void popHistory();

    /**
     * @brief fetch measurement points for local curve fitting
     *
     * @param[in] begin begin index
     * @param[in] end end sentinel
     * @param[out] points collected points in interval [begin, end)
     */
    void fecthMeasurementPoints(int32_t const begin, int32_t const end, std::vector<Point2Type>& points);

    /**
     * @brief fetch predicted points for curvefitting to generate derivative suggestion
     *
     * @param[out] points collected point from x_list and pred_d_list
     */
    void fetchPredictionPoints(std::vector<Point2Type>& points);

    /**
     * @brief compute value of the polynomial at point x
     *
     * @param[in] x query point
     * @param[in] coeffs polynomial coefficients
     * @return Scalar value at x
     */
    Scalar computeValue(Scalar const x, VectorType const& coeffs);

    /**
     * @brief compute derivative of th polynomial at point x
     *
     * @param[in] x query point
     * @param[in] coeffs polynomial coefficients
     * @return Scalar derivative at x
     */
    Scalar computeDerivative(Scalar const x, VectorType const& coeffs);

private:
    size_t            window_size_;       ///< window size of stored measurements
    size_t            span_steps_;        ///< window size for curve fitting
    size_t            start_steps_;       ///< when to use curve fitting result as y_mean suggestion
    Scalar            max_value_;         ///< estimated derivative shall in [-max_value, max_value]
    Scalar            y_length_scale_;    ///< y value GP regressor length scale
    Scalar            y_variance_;        ///< y value GP regressor variance
    Scalar            y_noise_variance_;  ///< noise variance of y measurements
    Scalar            d_length_scale_;    ///< derivative GP regressor length scale
    Scalar            d_variance_;        ///< derivative GP regressor variance
    Scalar            d_noise_variance_;  ///< noise variance of derivative measurements
    std::list<Scalar> x_list_;            ///< list of x measurements
    std::list<Scalar> y_list_;            ///< list of y measurements
    std::list<Scalar> pred_y_list_;       ///< list of y predictions
    std::list<Scalar> pred_d_list_;       ///< list of derivative predictions
    GPRPtrType        gpr_y_ptr_;         ///< y value GP regressor
    GPRPtrType        gpr_d_ptr_;         ///< derivative GP regressor
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_MATH_DERIVATIVE_ESTIMATOR_H_
