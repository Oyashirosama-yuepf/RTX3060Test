/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file curve_fitter.h
 * @brief define curve fitter
 * @author Wenzhi Liu (liuwenzhi@holomatic.com)
 * @date 2021-07-08
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_CURVE_FITTER_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_CURVE_FITTER_H_

#include <holo/localization/tightly_coupled_fusion/lane/types.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
namespace lane
{
/**
 * @addtogroup lane
 * @{
 *
 */

/**
 * @brief define curve fitter
 * @note
 * 1, the polynomial form of fitting curve is y = a0 + a1*x + a2*x^2 + a3*x^3 + ...
 * 2, we use linear optimization to calculate the coefficients of the curve polynomial, and the formula is
 *    coefficient = H^-1 * b (H is Hessian matrix).
 * 3, the form of Hessian matrix is [sum_x^0, sum_x^1, sum_x^2...
 *                                   sum_x^1, sum_x^2, sum_x^3...
 *                                   sum_x^2, sum_x^3, sum_x^4...
 *                                   ...                         ]
 *    sum_x^n in matrix is sum of the n-order exponent of the X-coordinate value of the points. So we can record the
 *    values of these elements to reduce the amount of computation in adaptive fitting curve.
 *    sum_x^n = x0^n + x1^n + x2^n +...
 * 4, the form of b vector is [sum_y_x^0, sum_y_x^1, sum_y_x^2 ...]', similar as Article 3, we can record the values of
 *    these elements to reduce the amount of computation in adaptive fitting curve.
 *    sum_y_x^n = y0*x0^n + y1*x1^n + y2*x2^n + ...
 * 5, We will determine the degree according to the mean value of the residual square and the decrease rate of the sum
 *    of the residual square.
 * 6, We will judge whether to do the fitting according to the distribution of the points.
 *
 */
class CurveFitter
{
public:
    using Ptr      = std::shared_ptr<CurveFitter>;
    using ConstPtr = std::shared_ptr<CurveFitter const>;

    /**
     * @brief define parameters
     *
     */
    struct Parameters
    {
        /// the max degree of fitting curve polynomial by adaptive method, default: 5.
        uint16_t max_degree_of_curve = 5u;
        /// threshold value of end condition of the descent rate of the sum of squares of residuals in the adaptive
        /// fitting curve, current_residual / last_residual > residual_gradient_ratio_tolerance -> convergence. default:
        /// 0.3.
        Scalar residual_gradient_ratio_tolerance = 0.3;
        /// mean value of squared residuals is smaller than residual_mean_value_tolerance -> convergence in the adaptive
        /// fitting curve, default: 0.01.
        Scalar residual_mean_value_tolerance = 0.01;
        /// threshold value of dispersion of the x-coordinate of sampling points, the dispresion is equal to the
        /// variance of the x-coordinate of the sampling point. default: 50
        Scalar min_dispersion_of_sampling_points_in_x_direction = 50.0;
        /// threshold value of angle between main direction of sampling points and x axis. (unit: deg) If the include
        /// angle is greater than this value, curve fitting is not performed.
        Scalar threshold_of_angle_between_main_direction_of_sampling_points_and_x_axis = 30.0;

        /**
         * @brief generate example parameters
         *
         * @return Parameters example parameters
         */
        static Parameters GenerateExample();

        /**
         * @brief Static method to load parameters from yaml
         *
         * @param[in] node Yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief output stream for curve fitter parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters);
    };

    /**
     * @brief Construct a new Curve Fitter object
     *
     * @param _parameters parameters of curve fitter
     */
    CurveFitter(Parameters const& _parameters) : parameters_(_parameters)
    {
    }

    /**
     * @brief Destroy the Curve Fitter object
     *
     */
    ~CurveFitter() = default;

    /**
     * @brief Get the Fitted Curve object
     *
     * @param points 2d points waiting for fitting
     * @param curve_coefficients coefficients of curve fitting, y = sum(curve_coefficients(n) * x^n)
     * @param degree degree of fitting polynomial, if this value is default or equal to 0, then degree of fitting
     * polynomial is adaptived.
     * @return bool_t return false if can not be fitted
     */
    bool_t Run(std::vector<Point2Type> const& points, VectorXType& curve_coefficients,
               uint16_t const degree = 0u) const;

protected:
    /**
     * @brief check distribution of points
     * @note here, we will check two conditions:
     * 1, the dispersion of the x-coordinate of points, if this value too small, the precision of the fitted curve will
     *    be poor, and return false.
     * 2, the angle between the main direction of the points and the x-axis direction, if this value too big , the
     *    precision of the fitted curve will be poor, and return false.
     * @param points 2d points waiting for checking
     * @return bool_t refer to '@note'
     */
    bool_t checkPointsDistribution(std::vector<Point2Type> const& points) const;

    /**
     * @brief fit curve polynomial with adaptived method
     * @details We fit the curve in the order of degree from low to high. We will determine the degree according to the
     * mean value of the residual square and the decrease rate of the sum of the residual square.
     * Such as, we set adaptive_residual_threshold which is in Parameters as 0.5, this degree is used when the mean
     * value of the sum of squares of the distances from the fitted curve to each point is less than this value.
     * Another example, suppose we fit the sum of the residual square of the quadratic curve is 'a', and the sum of
     * squares of the residuals of a cubic curve is 'b', we will choose result of quadratic curve when 'b/a >
     * residual_gradient_ratio_tolerance(which is in Parameters)'.
     *
     * @param points 2d points used to fit the curve
     * @param curve_coefficients coefficients of curve fitting
     * @return bool_t true -> success, false -> otherwise
     */
    bool_t fitCurveWithAdaptiveMethod(std::vector<Point2Type> const& points, VectorXType& curve_coefficients) const;

    /**
     * @brief fit curve polynomial
     * @details we will select elements of the H_matrix_elements to create Hessian matrix and select elements of the
     * b_vector_elements to create b vector. We use the following formula to compute the curve coefficients:
     * curve_coefficients = Hessian^-1*b.
     *
     * @param degree degree of fitting polynomial
     * @param H_matrix_elements elements container of H matrix
     * @param b_vector_elements elements container of b vector
     * @param curve_coefficients coefficients of curve fitting
     * @return bool_t return false if can not be fitted
     */
    bool_t fitCurveWithGivenDegree(uint16_t const degree, std::vector<Scalar> const& H_matrix_elements,
                                   std::vector<Scalar> const& b_vector_elements, VectorXType& curve_coefficients) const;

    /**
     * @brief compute H matrix elements ane b vector elements
     *
     * @param points 2d points waiting for fitting
     * @param degree degree of fitting polynomial
     * @param H_matrix_elements elements container of H matrix
     * @param b_vector_elements elements container of b vector
     * @param x_exponent_matrix elements container of X-coordinate value exponent of points
     * @return bool_t return false if can not be computed.
     */

    bool_t computeHb(std::vector<Point2Type> const& points, uint16_t const degree,
                     std::vector<Scalar>& H_matrix_elements, std::vector<Scalar>& b_vector_elements,
                     std::vector<std::vector<Scalar>>& x_exponent_matrix) const;

    /**
     * @brief initialize H matrix elements and b vector elements
     *
     * @param points 2d points waiting for fitting
     * @param H_matrix_elements elements container of H matrix
     * @param b_vector_elements elements container of b vector
     * @param x_exponent_matrix elements container of X-coordinate value exponent of points
     */
    void InitializeHb(std::vector<Point2Type> const& points, std::vector<Scalar>& H_matrix_elements,
                      std::vector<Scalar>&              b_vector_elements,
                      std::vector<std::vector<Scalar>>& x_exponent_matrix) const;

    /**
     * @brief compute H matrix elements ane b vector elements with incremental method
     *
     * @param points 2d points waiting for fitting
     * @param H_matrix_elements elements container of H matrix
     * @param b_vector_elements elements container of b vector
     * @param x_exponent_matrix elements container of X-coordinate value exponent of points
     */
    void computeHbWithIncremental(std::vector<Point2Type> const& points, std::vector<Scalar>& H_matrix_elements,
                                  std::vector<Scalar>&              b_vector_elements,
                                  std::vector<std::vector<Scalar>>& x_exponent_matrix) const;

    /**
     * @brief evaluate error
     * @note we will use x_exponent_matrix to speed up the calculation of the sum of squares of residuals under
     * different degree curve coefficients.
     *
     * @param points 2d points waiting for fitting
     * @param x_exponent_matrix elements container of X-coordinate value exponent of points
     * @param curve_coefficients coefficients of curve fitting
     * @param sum_of_squared_residual sum of residuals squares
     * @return bool_t return false if dimension of curve_coefficients is not equal to size of x_exponent_matrix_
     */
    bool_t evaluateError(std::vector<Point2Type> const&          points,
                         std::vector<std::vector<Scalar>> const& x_exponent_matrix,
                         VectorXType const& curve_coefficients, Scalar& sum_of_squared_residual) const;

    /**
     * @brief compute covariance matrix of sampling points
     *
     * @param points sampling points
     * @param covariance_matrix covariance matrix
     * @return bool_t return false if can not be computed.
     */
    bool_t computeSamplingPointsCovarianceMatrix(std::vector<Point2Type> const& points,
                                                 MatrixXType&                   covariance_matrix) const;

private:
    Parameters parameters_;  ///< parameters

};  // class CurveFitter

/**
 * @}
 *
 */
}  // namespace lane
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_CURVE_FITTER_H_
