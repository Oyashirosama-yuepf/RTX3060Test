/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */


#ifndef MODULES_PLANNING_SMOOTHING_SPLINE_SPLINE_2D_SOLVER_H_
#define MODULES_PLANNING_SMOOTHING_SPLINE_SPLINE_2D_SOLVER_H_

#include <qpOASES.hpp>

#include <memory>
#include <vector>

#include <holo/planning/qp/qp_solver/qp_solver.h>
#include <holo/planning/qp/spline/spline_2d.h>
#include <holo/planning/qp/spline/spline_2d_constraint.h>
#include <holo/planning/qp/spline/spline_2d_kernel.h>

namespace holo {
namespace planning {

class Spline2dSolver {
 public:
  Spline2dSolver(const std::vector<float64_t>& t_knots, const uint32_t order);

  void Reset(const std::vector<float64_t>& t_knots, const uint32_t order);

  // customize setup
  Spline2dConstraint* mutable_constraint();
  Spline2dKernel* mutable_kernel();
  Spline2d* mutable_spline();

  // solve
  bool Solve();

  // extract
  const Spline2d& spline() const;

 private:
  Spline2d spline_;
  Spline2dKernel kernel_;
  Spline2dConstraint constraint_;
  std::unique_ptr<::qpOASES::SQProblem> sqp_solver_;

  int last_num_constraint_ = 0;
  int last_num_param_ = 0;
  bool last_problem_success_ = false;
};

}  // namespace planning
}  // namespace apollo

#endif  // MODULES_PLANNING_SMOOTHING_SPLINE_SPLINE_2D_SOLVER_H_
