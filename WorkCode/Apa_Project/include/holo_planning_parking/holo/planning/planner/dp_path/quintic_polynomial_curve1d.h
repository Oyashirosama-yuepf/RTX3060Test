/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef MODULES_PLANNING_MATH_CURVE1D_QUINTIC_POLYNOMIAL_CURVE1D_H_
#define MODULES_PLANNING_MATH_CURVE1D_QUINTIC_POLYNOMIAL_CURVE1D_H_

#include <array>
#include <string>

#include <holo/planning/planner/dp_path/polynomial_curve1d.h>

namespace holo
{
namespace planning
{

// 1D quintic polynomial curve:
// (x0, dx0, ddx0) -- [0, param] --> (x1, dx1, ddx1)
class QuinticPolynomialCurve1d : public PolynomialCurve1d {
 public:
  QuinticPolynomialCurve1d() = default;

  QuinticPolynomialCurve1d(const std::array<float64_t, 3>& start,
                           const std::array<float64_t, 3>& end,
                           const float64_t param);

  QuinticPolynomialCurve1d(const float64_t x0, const float64_t dx0, const float64_t ddx0,
                           const float64_t x1, const float64_t dx1, const float64_t ddx1,
                           const float64_t param);

  QuinticPolynomialCurve1d(const QuinticPolynomialCurve1d& other);

  virtual ~QuinticPolynomialCurve1d() = default;

  float64_t Evaluate(const std::uint32_t order, const float64_t p) const override;

  float64_t ParamLength() const { return param_; }

 protected:
  void ComputeCoefficients(const float64_t x0, const float64_t dx0, const float64_t ddx0,
                           const float64_t x1, const float64_t dx1, const float64_t ddx1,
                           const float64_t param);

  // f = sum(coef_[i] * x^i), i from 0 to 5
  std::array<float64_t, 6> coef_{{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}};
  std::array<float64_t, 3> start_condition_{{0.0, 0.0, 0.0}};
  std::array<float64_t, 3> end_condition_{{0.0, 0.0, 0.0}};
};

}  // namespace planning
}  // namespace holo

#endif  // MODULES_PLANNING_MATH_CURVE1D_QUINTIC_POLYNOMIAL_CURVE1D_H_
