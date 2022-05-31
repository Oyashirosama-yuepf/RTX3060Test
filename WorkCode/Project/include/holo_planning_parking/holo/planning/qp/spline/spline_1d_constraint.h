/*!
 *  \brief
 *  \author liwenjun (liwenjun@holomatic.ai)
 *  \date Jul 14, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */


#ifndef _SPLINE_SPLINE_1D_CONSTRAINT_H_
#define _SPLINE_SPLINE_1D_CONSTRAINT_H_

#include <algorithm>
#include <functional>
#include <vector>

#include <Eigen/Core>

#include <holo/planning/qp/spline/affine_constraint.h>
#include <holo/planning/qp/spline/spline_1d.h>

namespace holo {
namespace planning {

class Spline1dConstraint {
 public:
  explicit Spline1dConstraint(const Spline1d& pss);
  Spline1dConstraint(const std::vector<float64_t>& x_knots, const uint32_t order);

  // direct methods
  bool AddInequalityConstraint(const Eigen::MatrixXd& constraint_matrix,
                               const Eigen::MatrixXd& constraint_boundary);
  bool AddEqualityConstraint(const Eigen::MatrixXd& constraint_matrix,
                             const Eigen::MatrixXd& constraint_boundary);

  // preset method
  /**
   * @brief: inequality boundary constraints
   * if no boundary, do specify either by std::infinity or
   * let vector.size() = 0
   **/
  bool AddBoundary(const std::vector<float64_t>& x_coord,
                   const std::vector<float64_t>& lower_bound,
                   const std::vector<float64_t>& upper_bound);

  bool AddDerivativeBoundary(const std::vector<float64_t>& x_coord,
                             const std::vector<float64_t>& lower_bound,
                             const std::vector<float64_t>& upper_bound);

  bool AddSecondDerivativeBoundary(const std::vector<float64_t>& x_coord,
                                   const std::vector<float64_t>& lower_bound,
                                   const std::vector<float64_t>& upper_bound);

  bool AddThirdDerivativeBoundary(const std::vector<float64_t>& x_coord,
                                  const std::vector<float64_t>& lower_bound,
                                  const std::vector<float64_t>& upper_bound);

  /**
   * @brief: equality constraint to guarantee joint smoothness
   * boundary equality constriant constraint on fx, dfx, ddfx ... in vector
   * form; upto third order
   **/
  bool AddPointConstraint(const float64_t x, const float64_t fx);
  bool AddPointDerivativeConstraint(const float64_t x, const float64_t dfx);
  bool AddPointSecondDerivativeConstraint(const float64_t x, const float64_t ddfx);
  bool AddPointThirdDerivativeConstraint(const float64_t x, const float64_t dddfx);

  bool AddPointConstraintInRange(const float64_t x, const float64_t fx,
                                 const float64_t range);
  bool AddPointDerivativeConstraintInRange(const float64_t x, const float64_t dfx,
                                           const float64_t range);
  bool AddPointSecondDerivativeConstraintInRange(const float64_t x,
                                                 const float64_t ddfx,
                                                 const float64_t range);
  bool AddPointThirdDerivativeConstraintInRange(const float64_t x,
                                                const float64_t dddfx,
                                                const float64_t range);
  // guarantee upto values are joint
  bool AddSmoothConstraint();

  // guarantee upto derivative are joint
  bool AddDerivativeSmoothConstraint();

  // guarantee upto second order derivative are joint
  bool AddSecondDerivativeSmoothConstraint();

  // guarantee upto third order derivative are joint
  bool AddThirdDerivativeSmoothConstraint();

  /**
   * @brief: Add monotone constraint inequality, guarantee the monotone city at
   * evaluated point. customized monotone inequality constraint at x_coord
   **/
  bool AddMonotoneInequalityConstraint(const std::vector<float64_t>& x_coord);

  // default inequality constraint at knots
  bool AddMonotoneInequalityConstraintAtKnots();

  /**
   * @brief: output interface inequality constraint
   **/
  const AffineConstraint& inequality_constraint() const;
  const AffineConstraint& equality_constraint() const;

 private:
  uint32_t FindIndex(const float64_t x) const;

  bool FilterConstraints(const std::vector<float64_t>& x_coord,
                         const std::vector<float64_t>& lower_bound,
                         const std::vector<float64_t>& upper_bound,
                         std::vector<float64_t>* const filtered_lower_bound_x,
                         std::vector<float64_t>* const filtered_lower_bound,
                         std::vector<float64_t>* const filtered_upper_bound_x,
                         std::vector<float64_t>* const filtered_upper_bound);
  void GeneratePowerX(const float64_t x, const uint32_t order,
                      std::vector<float64_t>* const power_x) const;

  using AddConstraintInRangeFunc =
      std::function<bool(const std::vector<float64_t>&, const std::vector<float64_t>&,
                         const std::vector<float64_t>&)>;
  bool AddConstraintInRange(AddConstraintInRangeFunc func, const float64_t x,
                            const float64_t val, const float64_t range);

 private:
  AffineConstraint inequality_constraint_;
  AffineConstraint equality_constraint_;
  std::vector<float64_t> x_knots_;
  uint32_t spline_order_;
};

}  // namespace planning
}  // namespace holo

#endif  // _SPLINE_1D_CONSTRAINT_H_
