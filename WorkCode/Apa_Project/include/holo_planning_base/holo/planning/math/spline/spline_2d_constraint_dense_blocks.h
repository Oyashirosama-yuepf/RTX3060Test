/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file spline_2d_constraint_dense_blocks.h
 * @brief the header of the spline_2d_constraint_dense_blocks
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2021-11-26
 */

#ifndef _HOLO_PLANNING_MATH_SPLINE_SPLINE_2D_CONSTRAINT_DENSE_BLOCKS_H_
#define _HOLO_PLANNING_MATH_SPLINE_SPLINE_2D_CONSTRAINT_DENSE_BLOCKS_H_

#include <Eigen/Core>

#include <assert.h>
#include <memory>
#include <utility>
#include <vector>

#include <holo/core/types.h>

#include <holo/geometry/point2.h>

namespace holo
{
namespace planning
{
class Spline2dConstraintDenseBlocks
{
public:
    Spline2dConstraintDenseBlocks(std::vector<float64_t> const& t_knots, uint32_t const spline_order)
      : t_knots_(t_knots), spline_order_(spline_order)
    {
        assert(inequality_constraint_.empty());
        assert(inequality_lower_bounds_.empty());
        assert(inequality_upper_bounds_.empty());
        assert(equality_constraint_.empty());
        assert(equality_bounds_.empty());

        for (size_t i = 1; i < t_knots_.size(); i++)
        {
            assert(t_knots_[i] > t_knots_[i - 1] + std::numeric_limits<float64_t>::epsilon());
        }
    }

    void AddInequalityConstraint(uint32_t                         spline_index,
                                 std::shared_ptr<Eigen::MatrixXd> constraint_matrix,
                                 std::shared_ptr<Eigen::MatrixXd> lower_bounds,
                                 std::shared_ptr<Eigen::MatrixXd> upper_bounds);

    void AddEqualityConstraint(uint32_t                         spline_index,
                               std::shared_ptr<Eigen::MatrixXd> constraint_matrix,
                               std::shared_ptr<Eigen::MatrixXd> bounds);

    /**
     *   @brief: inequality boundary constraints acting on lon&lat direction
     **/
    void Add2dBoundary(std::vector<float64_t> const&        t_coord,
                       std::vector<float64_t> const&        angle,
                       std::vector<geometry::Point2> const& ref_point,
                       std::vector<float64_t> const&        longitudinal_bound,
                       std::vector<float64_t> const&        lateral_bound);

    void AddPointAngleConstraint(float64_t const t, float64_t const angle);

    void AddPointSecondDerivativeConstraint(float64_t const t, float64_t const ddx, float64_t const ddy);

    void AddSecondDerivativeSmoothConstraint();  // guarantee upto second order derivative are joint

public:  // getters
    std::vector<std::pair<uint32_t, std::shared_ptr<Eigen::MatrixXd> > > const& GetInequalityConstraint() const
    {
        return inequality_constraint_;
    }

    std::vector<std::shared_ptr<Eigen::MatrixXd> > const& GetInequalityLowerBounds() const
    {
        return inequality_lower_bounds_;
    }

    std::vector<std::shared_ptr<Eigen::MatrixXd> > const& GetInequalityUpperBounds() const
    {
        return inequality_upper_bounds_;
    }

    std::vector<std::pair<uint32_t, std::shared_ptr<Eigen::MatrixXd> > > const& GetEqualityConstraint() const
    {
        return equality_constraint_;
    }

    std::vector<std::shared_ptr<Eigen::MatrixXd> > const& GetEqualityBounds() const
    {
        return equality_bounds_;
    }

private:
    uint32_t               findIndex(float64_t const t) const;
    std::vector<float64_t> affineCoef(float64_t const angle, float64_t const t) const;
    std::vector<float64_t> affineDerivativeCoef(float64_t const angle, float64_t const t) const;
    std::vector<float64_t> affineSecondDerivativeCoef(float64_t const angle, float64_t const t) const;
    std::vector<float64_t> affineThirdDerivativeCoef(float64_t const angle, float64_t const t) const;
    std::vector<float64_t> polyCoef(float64_t const t) const;
    std::vector<float64_t> derivativeCoef(float64_t const t) const;
    std::vector<float64_t> secondDerivativeCoef(float64_t const t) const;
    std::vector<float64_t> thirdDerivativeCoef(float64_t const t) const;
    float64_t              signDistance(geometry::Point2 const& xy_point, float64_t const angle) const;
    void                   addPointKthOrderDerivativeConstraint(float64_t const               t,
                                                                float64_t const               x_kth_derivative,
                                                                float64_t const               y_kth_derivative,
                                                                std::vector<float64_t> const& kth_coeff);

private:
    /**
     * @brief the inequality-constraint's Non-zero blocks
     *
     * @details the vector's index indicate to different constraint;
     *          "uint32_t" indicate the index of spline segment;
     *          shared_ptr point to the constraint matrix block;
     *          every single constraint only acting on one spline segment;
     *          "acting on" means this constraint block is not zero;
     */
    std::vector<std::pair<uint32_t, std::shared_ptr<Eigen::MatrixXd> > > inequality_constraint_;
    std::vector<std::shared_ptr<Eigen::MatrixXd> >                       inequality_lower_bounds_;
    std::vector<std::shared_ptr<Eigen::MatrixXd> >                       inequality_upper_bounds_;

    /**
     * @brief the equality-constraint's Non-zero blocks
     *
     * @details the vector's index indicate to different constraint;
     *          "uint32_t" indicate the index of spline segment;
     *          shared_ptr point to the constraint matrix block;
     *          every single constraint only acting on one spline segment;
     *          "acting on" means this constraint block is not zero;
     */
    std::vector<std::pair<uint32_t, std::shared_ptr<Eigen::MatrixXd> > > equality_constraint_;
    std::vector<std::shared_ptr<Eigen::MatrixXd> >                       equality_bounds_;

    std::vector<float64_t> t_knots_;       ///< number of spline segments
    uint32_t               spline_order_;  ///< the order of spline segments
};

}  // namespace planning
}  // namespace holo

#endif  // _HOLO_PLANNING_MATH_SPLINE_SPLINE_2D_CONSTRAINT_DENSE_BLOCKS_H_
