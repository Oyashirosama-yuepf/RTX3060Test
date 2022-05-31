/*!
 *  \brief
 *  \author liwenjun (liwenjun@holomatic.ai)
 *  \date Jul 14, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _SPLINE_SPLINE_1D_GENERATOR_H_
#define _SPLINE_SPLINE_1D_GENERATOR_H_

#include <memory>
#include <vector>

#include <assert.h>

#include <holo/planning/math/spline/qp_solver.h>
#include <holo/planning/math/spline/spline_1d.h>
#include <holo/planning/math/spline/spline_1d_constraint.h>
#include <holo/planning/math/spline/spline_1d_kernel.h>

namespace holo
{
namespace planning
{
class Spline1dSolver
{
public:
    Spline1dSolver(const std::vector<float64_t>& x_knots, const uint32_t order);

    void Reset(const std::vector<float64_t>& x_knots, const uint32_t order);

    /**
     * @brief Set the constraint of Spline.
     *
     * @param input_constraint The input constraint.
     */
    void SetConstraint(std::shared_ptr<Spline1dConstraint> input_constraint)
    {
        assert(input_constraint != nullptr);

        spline_constraint_ = input_constraint;
    }

    /**
     * @brief Get the constraint of Spline.
     *
     * @return input_constraint The input constraint.
     */
    std::shared_ptr<Spline1dConstraint const> GetConstraint() const
    {
        return spline_constraint_;
    }

    /**
     * @brief Set the kernel of Spline.
     *
     * @param input_kernel The input kernel.
     */
    void SetKernel(std::shared_ptr<Spline1dKernel> input_kernel)
    {
        assert(input_kernel != nullptr);

        spline_kernel_ = input_kernel;
    }

    /**
     * @brief Get the kernel of Spline.
     *
     * @return input_kernel The input kernel.
     */
    std::shared_ptr<Spline1dKernel const> GetKernel()
    {
        return spline_kernel_;
    }

    // solve
    bool_t Solve();

    // output
    const Spline1d& spline() const;

private:
    Spline1d spline_;

    std::shared_ptr<Spline1dConstraint> spline_constraint_;
    std::shared_ptr<Spline1dKernel>     spline_kernel_;

    QpSolver qp_solver;
};

}  // namespace planning
}  // namespace holo

#endif  // _SPLINE_SPLINE_1D_GENERATOR_H_
