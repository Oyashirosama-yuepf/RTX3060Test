/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file spline_2d_solver_osqp.h
 * @brief the header of spline_2d_solver_osqp
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2021-11-27
 */

#ifndef _HOLO_PLANNING_MATH_SPLINE_SPLINE_2D_SOLVER_OSQP_H_
#define _HOLO_PLANNING_MATH_SPLINE_SPLINE_2D_SOLVER_OSQP_H_

#include <assert.h>
#include <vector>

#include <holo/core/types.h>

#include <holo/planning/common/csc_matrix.h>
#include <holo/planning/common/osqp_config.h>
#include <holo/planning/math/spline/spline_2d.h>
#include <holo/planning/math/spline/spline_2d_constraint_dense_blocks.h>
#include <holo/planning/math/spline/spline_2d_kernel_csc.h>

namespace holo
{
namespace planning
{
class Spline2dSolverOsqp
{
public:
    Spline2dSolverOsqp(std::vector<float64_t> const& t_knots,
                       uint32_t const                spline_order,
                       OsqpConfig const&             osqp_config)
      : spline_(t_knots, spline_order)
      , kernel_(t_knots, spline_order)
      , constraint_(t_knots, spline_order)
      , spline_order_(spline_order)
      , osqp_config_(osqp_config)
    {
        num_splines_ = t_knots.empty() ? 0 : t_knots.size() - 1;
    }

    void Reset(std::vector<float64_t> const& t_knots, uint32_t const spline_order)
    {
        assert(!t_knots.empty());

        spline_       = Spline2d(t_knots, spline_order);
        kernel_       = Spline2dKernelCSC(t_knots, spline_order);
        constraint_   = Spline2dConstraintDenseBlocks(t_knots, spline_order);
        spline_order_ = spline_order;
        num_splines_  = t_knots.size() - 1;

        for (size_t i = 1; i < t_knots.size(); i++)
        {
            assert(t_knots[i] > t_knots[i - 1] + std::numeric_limits<float64_t>::epsilon());
        }
    }

    bool_t Solve();

    Spline2dConstraintDenseBlocks* mutable_constraint()
    {
        return &constraint_;
    }

    Spline2dKernelCSC* mutable_kernel()
    {
        return &kernel_;
    }

    Spline2d* mutable_spline()
    {
        return &spline_;
    }

    Spline2d const& GetSpline() const
    {
        return spline_;
    }

private:
    /**
     * @brief copy data from a vector
     *
     * @param vec the vector of data
     *
     * @tparam T the type of vector
     *
     * @return the copied data pointer
     */
    template <typename T>
    T* copyData(const std::vector<T>& vec) const
    {
        T* data = new T[vec.size()];
        memcpy(data, vec.data(), sizeof(T) * vec.size());
        return data;
    }

private:
    Spline2d                      spline_;
    Spline2dKernelCSC             kernel_;
    Spline2dConstraintDenseBlocks constraint_;
    float64_t                     spline_order_;
    uint32_t                      num_splines_;
    OsqpConfig                    osqp_config_;
};

}  // namespace planning
}  // namespace holo

#endif  // _HOLO_PLANNING_MATH_SPLINE_SPLINE_2D_SOLVER_OSQP_H_
