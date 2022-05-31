/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _SPLINE_SPLINE_1D_H_
#define _SPLINE_SPLINE_1D_H_

#include <vector>

#include <holo/numerics/matrix.h>

#include <holo/planning/math/spline/spline_1d_seg.h>

namespace holo
{
namespace planning
{
class Spline1d
{
public:
    Spline1d(const std::vector<float64_t>& x_knots, const uint32_t order);

    // @brief: given x return f(x) value, derivative, second order derivative and
    // the third order;
    float64_t operator()(const float64_t x) const;
    float64_t Derivative(const float64_t x) const;
    float64_t SecondOrderDerivative(const float64_t x) const;
    float64_t ThirdOrderDerivative(const float64_t x) const;

    // @brief: set spline segments
    bool_t SetSplineSegs(const numerics::MatrixXd& param_matrix, const uint32_t order);

    const std::vector<float64_t>& x_knots() const;
    uint32_t                      spline_order() const;

private:
    uint32_t FindIndex(const float64_t x) const;

private:
    std::vector<Spline1dSeg> splines_;
    std::vector<float64_t>   x_knots_;
    uint32_t                 spline_order_;
};

}  // namespace planning
}  // namespace holo

#endif  // _SPLINE_SPLINE_1D_H_
