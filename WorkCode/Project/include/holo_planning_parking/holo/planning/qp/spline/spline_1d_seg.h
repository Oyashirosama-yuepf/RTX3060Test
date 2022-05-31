/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */


#ifndef _SPLINE_SPLINE_1D_SEG_H_
#define _SPLINE_SPLINE_1D_SEG_H_

#include <vector>
#include <Eigen/Core>

#include <holo/planning/qp/spline/polynomial_xd.h>

namespace holo {
namespace planning {

class Spline1dSeg {
 public:
  // order represents the highest order.
  explicit Spline1dSeg(const uint32_t order);
  explicit Spline1dSeg(const std::vector<float64_t>& params);
  ~Spline1dSeg() = default;

  void SetParams(const std::vector<float64_t>& params);
  float64_t operator()(const float64_t x) const;
  float64_t Derivative(const float64_t x) const;
  float64_t SecondOrderDerivative(const float64_t x) const;
  float64_t ThirdOrderDerivative(const float64_t x) const;

  const PolynomialXd& spline_func() const;
  const PolynomialXd& Derivative() const;
  const PolynomialXd& SecondOrderDerivative() const;
  const PolynomialXd& ThirdOrderDerivative() const;

 private:
  inline void SetSplineFunc(const PolynomialXd& spline_func);

  PolynomialXd spline_func_;
  PolynomialXd derivative_;
  PolynomialXd second_order_derivative_;
  PolynomialXd third_order_derivative_;
};

}  // namespace planning
}  // namespace holo

#endif  // _SPLINE_SPLINE_1D_SEG_H_
