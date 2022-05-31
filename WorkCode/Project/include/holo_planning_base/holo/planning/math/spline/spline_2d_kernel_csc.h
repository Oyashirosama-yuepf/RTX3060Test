/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file spline_2d_kernel_csc.h
 * @brief the header of Spline2DKernelCSC class
 * @author jiangshunchang(jiangshunchang@holomatic.com)
 * @date 2021-11-19
 */

#ifndef _HOLO_PLANNING_MATH_SPLINE_SPLINE_2D_KERNEL_CSC_H_
#define _HOLO_PLANNING_MATH_SPLINE_SPLINE_2D_KERNEL_CSC_H_

#include <vector>

#include <holo/geometry/point2.h>

#include <holo/planning/common/csc_matrix.h>

namespace holo
{
namespace planning
{
class Spline2dKernelCSC
{
public:
    /**
     * @brief Constructor.
     *
     * @param t_knots The t values of the knots.
     * @param spline_order The order of the polynomial of the splines.
     */
    Spline2dKernelCSC(std::vector<float64_t> const& t_knots, uint32_t const spline_order);

    /**
     * @brief Add the anchor kernel and the offset.
     *
     * @param t_coord The absolute t values of anchor points.
     * @param ref_points The x and y values of anchor points.
     * @param points_weight The weight of every anchor point.
     * @param weight The weight of kernel and offset.
     *
     * @return True if adding succeeds, false otherwise.
     */
    bool_t AddAnchorPointsKernel(std::vector<float64_t> const&        t_coord,
                                 std::vector<geometry::Point2> const& ref_points,
                                 std::vector<float64_t> const&        points_weight,
                                 float64_t const                      weight);

    /**
     * @brief Add the regularization kernel to the knot kernel.
     *
     * @param weight The weight of the regularization kernel.
     */
    void AddRegularizationKernel(float64_t const weight);

    /**
     * @brief Add the nth order derivative kernel to the knot kernel.
     *
     * @param kernel_order The order of the kernel.
     * @param weight The weight of the nth order derivative kernel.
     *
     * @return True if adding succeeds, false otherwise.
     */
    bool_t AddNthOrderDerivativeKernel(uint32_t const kernel_order, float64_t const weight);

public:
    /**
     * @brief Get the kernel.
     *
     * @return The kernel.
     */
    CSCMatrix const& GetKernel() const
    {
        return kernel_;
    }

    /**
     * @brief Get the offset.
     *
     * @return The offset.
     */
    std::vector<float64_t> const& GetOffset() const
    {
        return offset_;
    }

private:
    /**
     * @brief Find the index of the point ( as to say finding which spline the point is in ).
     *`
     * @param t The absolute t value of the point.
     *
     * @return The index of the point.
     */
    uint32_t find_Index(float64_t const t) const;

private:
    /**
     * @brief  The t values of the knots (the knot is a point between two adjacent splines).
     */
    std::vector<float64_t> t_knots_;

    /**
     * @brief The number of parameters for each spline's x or y.
     */
    uint32_t num_params_;

    /**
     * @brief The number of total parameters of all splines (x and y).
     */
    uint32_t num_total_params_;

    /**
     * @brief The number of elements of an upper triangular for each spline's x or y.
     */
    uint32_t num_upper_triangular_elements_;

private:
    /**
     * @brief The upper triangular matrix of the kernel in CSC matrix format;
     */
    CSCMatrix kernel_;

    /**
     * @brief The offset in vector format.
     */
    std::vector<float64_t> offset_;
};

}  // namespace planning
}  // namespace holo

#endif  // _HOLO_PLANNING_MATH_SPLINE_SPLINE_2D_KERNEL_CSC_H_
