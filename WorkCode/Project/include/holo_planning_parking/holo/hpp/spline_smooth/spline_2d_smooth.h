/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file spline_2d_smooth.h
 * @brief the header of Spline2DSmooth class
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2021-08-31
 */

#ifndef _SPLINE_2D_SMOOTH_H_
#define _SPLINE_2D_SMOOTH_H_

#include <memory>
#include <vector>

#include <holo/core/types.h>

#include <holo/planning/common/anchor_point.h>
#include <holo/planning/qp/spline/spline_2d_solver.h>

namespace holo
{
namespace planning
{
class Spline2DSmooth
{
public:
    /**
     * @brief Constructor.
     */
    Spline2DSmooth();

    /**
     * @brief Smooth raw_path with step_length.
     *
     * @param[in] raw_path The raw path before smoothing.
     * @param[in] step_length The step length during smoothing.
     * @param[out] smoothed_path The smoothed path.
     *
     * @return True if smoothing succeeds, false otherwise.
     */
    bool_t Smooth(std::vector<CurvePoint> const& raw_path,
                  float64_t                      step_length,
                  std::vector<CurvePoint>&       smoothed_path);

    /**
     * @brief Set the weight of second order derivative matrix to be added.
     *
     * @param weight The weight of second order derivative matrix to be added.
     */
    void Set2OrderDerivativeWeight(float64_t weight)
    {
        second_order_derivative_weight_ = weight;
    }

    /**
     * @brief Get the weight of second order derivative matrix to be added.
     *
     * @return The weight of second order derivative matrix to be added.
     */
    float64_t Get2OrderDerivativeWeight() const
    {
        return second_order_derivative_weight_;
    }

    /**
     * @brief Set the weight of third order derivative matrix to be added.
     *
     * @param weight The weight of third order derivative matrix to be added.
     */
    void Set3OrderDerivativeWeight(float64_t weight)
    {
        third_order_derivative_weight_ = weight;
    }

    /**
     * @brief Get the weight of third order derivative matrix to be added.
     *
     * @return The weight of third order derivative matrix to be added.
     */
    float64_t Get3OrderDerivativeWeight() const
    {
        return third_order_derivative_weight_;
    }

    /**
     * @brief Set the regularization parameter of kernel matrix.
     *
     * @param regularization_param The regularization parameter of kernel matrix.
     */
    void SetRegularizationParam(float64_t weight)
    {
        regularization_weight_ = weight;
    }

    /**
     * @brief Get the regularization parameter of kernel matrix.
     *
     * @return The regularization parameter of kernel matrix.
     */
    float64_t GetRegularizationParam() const
    {
        return regularization_weight_;
    }

    /**
     * @brief Set the weight of reference line kernel matrix to be added.
     *
     * @param weight The weight of reference line kernel matrix to be added.
     */
    void SetReferenceLineKernelWeight(float64_t weight)
    {
        reference_line_kernel_weight_ = weight;
    }

    /**
     * @brief Get the weight of reference line kernel matrix to be added.
     *
     * @return The weight of reference line kernel matrix to be added.
     */
    float64_t GetReferenceLineKernelWeight() const
    {
        return reference_line_kernel_weight_;
    }

    /**
     * @brief Get anchor points.
     *
     * @return Anchor points.
     */
    std::vector<AnchorPoint> const& GetAnchorPoints() const
    {
        return anchor_points_;
    }

    /**
     * @brief Get the t values of knots.
     *
     * @return The t values of knots.
     */
    std::vector<float64_t> const& GetKnotsT() const
    {
        return knots_t_;
    }

    /**
     * @brief Get the scale.
     *
     * @return The scale.
     */
    float64_t GetScale() const
    {
        return scale_;
    }

private:
    /**
     * @brief Initialize the anchor points.
     *
     * @param raw_path The raw path before smoothing.
     */
    void initAnchorPoints(std::vector<CurvePoint> const& raw_path);

    /**
     * @brief Initialize the spline.
     *
     * @param raw_path The raw path before smoothing.
     *
     * @return True if initialization succeeds, false otherwise.
     */
    bool_t initSpline(std::vector<CurvePoint> const& raw_path);

    /**
     * @brief Add constraints to the points to be evaluated.
     *
     * @return True if the constraints are added successfully, false otherwise.
     */
    bool_t addConstraint();

    /**
     * @brief Add kernel matrix of quadratic programming.
     */
    void addKernel();

    /**
     * @brief Solve the quadratic programming (smoothing).
     *
     * @return True if solving successfully, false otherwise.
     */
    bool_t solve();

private:
    /**
     * @brief A solver or generator of spline 2d.
     */
    std::unique_ptr<Spline2dSolver> spline_generator_ = nullptr;

    /**
     * @brief The anchor points matched to raw path.
     */
    std::vector<AnchorPoint> anchor_points_;

    /**
     * @brief The t values of the knots (the knot is a point between two adjacent splines).
     */
    std::vector<float64_t> knots_t_;

    /**
     * @brief The t values of the points to be evaluated (or to say anchor points).
     */
    std::vector<float64_t> evaluated_t_;

    /**
     * @brief The weight of second order derivative matrix to be added.
     */
    float64_t second_order_derivative_weight_;

    /**
     * @brief The weight of third order derivative matrix to be added.
     */
    float64_t third_order_derivative_weight_;

    /**
     * @brief The weight of regularized matrix to be added.
     */
    float64_t regularization_weight_;

    /**
     * @brief The weight of reference line kernel matrix to be added.
     */
    float64_t reference_line_kernel_weight_;

    /**
     * @brief The x position used to normalize.
     */
    float64_t ref_x_;

    /**
     * @brief The y position used to normalize.
     */
    float64_t ref_y_;

    /**
     * @brief The scale of coordinate system s to coordinate system t.
     */
    float64_t scale_;
};

}  // namespace planning
}  // namespace holo

#endif  // _SPLINE_2D_SMOOTH_H_
