/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */


#ifndef MODULES_PLANNING_SMOOTHING_SPLINE_SPLINE_2D_CONSTRAINT_H_
#define MODULES_PLANNING_SMOOTHING_SPLINE_SPLINE_2D_CONSTRAINT_H_

#include <vector>
#include <Eigen/Core>

#include <holo/geometry/point2.h>

#include <holo/planning/qp/spline/affine_constraint.h>
#include <holo/planning/qp/spline/spline_2d.h>

namespace holo {
namespace planning {

class Spline2dConstraint {
 public:
  Spline2dConstraint(const std::vector<float64_t>& t_knots, const uint32_t order);

  // direct method
  bool AddInequalityConstraint(const Eigen::MatrixXd& constraint_matrix,
                               const Eigen::MatrixXd& constraint_boundary);
  bool AddEqualityConstraint(const Eigen::MatrixXd& constraint_matrix,
                             const Eigen::MatrixXd& constraint_boundary);

  // preset method
  /**
   *   @brief: inequality boundary constraints
   *   if no boundary, do specify either by std::infinity or let vector.size() =
   *0
   **/
  bool Add2dBoundary(const std::vector<float64_t>& t_coord,
                     const std::vector<float64_t>& angle,
                     const std::vector<geometry::Point2>& ref_point,
                     const std::vector<float64_t>& longitudinal_bound,
                     const std::vector<float64_t>& lateral_bound);

  // ref point refer to derivative reference point
  bool Add2dDerivativeBoundary(
      const std::vector<float64_t>& t_coord, const std::vector<float64_t>& angle,
      const std::vector<geometry::Point2>& ref_point,
      const std::vector<float64_t>& longitudinal_bound,
      const std::vector<float64_t>& lateral_bound);

  // ref point refer to second derivative ref point
  bool Add2dSecondDerivativeBoundary(
      const std::vector<float64_t>& t_coord, const std::vector<float64_t>& angle,
      const std::vector<geometry::Point2>& ref_point,
      const std::vector<float64_t>& longitudinal_bound,
      const std::vector<float64_t>& lateral_bound);

  // ref point refer to third derivative ref point
  bool Add2dThirdDerivativeBoundary(
      const std::vector<float64_t>& t_coord, const std::vector<float64_t>& angle,
      const std::vector<geometry::Point2>& ref_point,
      const std::vector<float64_t>& longitudinal_bound,
      const std::vector<float64_t>& lateral_bound);

  bool AddPointConstraint(const float64_t t, const float64_t x, const float64_t y);
  bool AddPointSecondDerivativeConstraint(const float64_t t, const float64_t ddx,
                                          const float64_t ddy);
  bool AddPointThirdDerivativeConstraint(const float64_t t, const float64_t dddx,
                                         const float64_t dddy);
  bool AddPointAngleConstraint(const float64_t t, const float64_t angle);

  // guarantee upto values are joint
  bool AddSmoothConstraint();

  // guarantee upto derivative are joint
  bool AddDerivativeSmoothConstraint();

  // guarantee upto second order derivative are joint
  bool AddSecondDerivativeSmoothConstraint();

  // guarantee upto third order derivative are joint
  bool AddThirdDerivativeSmoothConstraint();

  /**
   *   @brief: output interface inequality constraint
   **/
  const AffineConstraint& inequality_constraint() const;
  const AffineConstraint& equality_constraint() const;

 private:
  uint32_t FindIndex(const float64_t t) const;
  std::vector<float64_t> AffineCoef(const float64_t angle, const float64_t t) const;
  std::vector<float64_t> AffineDerivativeCoef(const float64_t angle,
                                           const float64_t t) const;
  std::vector<float64_t> AffineSecondDerivativeCoef(const float64_t angle,
                                                 const float64_t t) const;
  std::vector<float64_t> AffineThirdDerivativeCoef(const float64_t angle,
                                                const float64_t t) const;
  std::vector<float64_t> PolyCoef(const float64_t t) const;
  std::vector<float64_t> DerivativeCoef(const float64_t t) const;
  std::vector<float64_t> SecondDerivativeCoef(const float64_t t) const;
  std::vector<float64_t> ThirdDerivativeCoef(const float64_t t) const;
  float64_t SignDistance(const geometry::Point2& xy_point,
                      const float64_t angle) const;
  bool AddPointKthOrderDerivativeConstraint(
      const float64_t t, const float64_t x_kth_derivative,
      const float64_t y_kth_derivative, const std::vector<float64_t>& kth_coeff);

 private:
  AffineConstraint inequality_constraint_;
  AffineConstraint equality_constraint_;
  std::vector<float64_t> t_knots_;
  uint32_t spline_order_;
  uint32_t total_param_;
};

}  // namespace planning
}  // namespace apollo

#endif  // MODULES_PLANNING_SMOOTHING_SPLINE_SPLINE_2D_CONSTRAINT_H_
