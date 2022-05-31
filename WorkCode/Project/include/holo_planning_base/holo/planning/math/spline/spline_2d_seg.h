/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef MODULES_PLANNING_SMOOTHER_SPLINE_SPLINE_2D_SEG_H_
#define MODULES_PLANNING_SMOOTHER_SPLINE_SPLINE_2D_SEG_H_

#include <utility>
#include <vector>

#include <holo/planning/math/spline/polynomial_xd.h>

namespace holo
{
namespace planning
{
class Spline2dSeg
{
public:
    // order represent the number of parameters (not the highest order);
    explicit Spline2dSeg(const uint32_t order);
    explicit Spline2dSeg(const std::vector<float64_t>& x_param, const std::vector<float64_t>& y_param);
    ~Spline2dSeg() = default;

    bool_t SetParams(const std::vector<float64_t>& x_param, const std::vector<float64_t>& y_param);

    std::pair<float64_t, float64_t> operator()(const float64_t t) const;

    float64_t x(const float64_t t) const;
    float64_t y(const float64_t t) const;
    float64_t DerivativeX(const float64_t t) const;
    float64_t DerivativeY(const float64_t t) const;
    float64_t SecondDerivativeX(const float64_t t) const;
    float64_t SecondDerivativeY(const float64_t t) const;
    float64_t ThirdDerivativeX(const float64_t t) const;
    float64_t ThirdDerivativeY(const float64_t t) const;

    const PolynomialXd& spline_func_x() const;
    const PolynomialXd& spline_func_y() const;
    const PolynomialXd& DerivativeX() const;
    const PolynomialXd& DerivativeY() const;
    const PolynomialXd& SecondDerivativeX() const;
    const PolynomialXd& SecondDerivativeY() const;
    const PolynomialXd& ThirdDerivativeX() const;
    const PolynomialXd& ThirdDerivativeY() const;

private:
    PolynomialXd spline_func_x_;
    PolynomialXd spline_func_y_;
    PolynomialXd derivative_x_;
    PolynomialXd derivative_y_;
    PolynomialXd second_derivative_x_;
    PolynomialXd second_derivative_y_;
    PolynomialXd third_derivative_x_;
    PolynomialXd third_derivative_y_;
};

}  // namespace planning
}  // namespace holo

#endif  // MODULES_PLANNING_SMOOTHER_SPLINE_SMOOTHER_SPLINE2D_H_
