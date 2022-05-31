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

#include <qpOASES.hpp>

#include <holo/planning/qp/qp_solver/qp_solver.h>
#include <holo/planning/qp/spline/spline_1d.h>
#include <holo/planning/qp/spline/spline_1d_kernel.h>
#include <holo/planning/qp/spline/spline_1d_constraint.h>

namespace holo {
namespace planning {

class Spline1dGenerator {
 public:
  Spline1dGenerator(const std::vector<float64_t>& x_knots, const uint32_t order);

  void Reset(const std::vector<float64_t>& x_knots, const uint32_t order);

  // add constraint through pss_constraint
  Spline1dConstraint* mutable_spline_constraint();

  // add kernel through pss_kernel
  Spline1dKernel* mutable_spline_kernel();

  // solve
  bool Solve();

  // output
  const Spline1d& spline() const;

 private:
  Spline1d spline_;
  Spline1dConstraint spline_constraint_;
  Spline1dKernel spline_kernel_;

  std::unique_ptr<::qpOASES::SQProblem> sqp_solver_;

  int last_num_constraint_ = 0;
  int last_num_param_ = 0;
  bool last_problem_success_ = false;
};

}  // namespace planning
}  // namespace holo

#endif  // _SPLINE_SPLINE_1D_GENERATOR_H_
