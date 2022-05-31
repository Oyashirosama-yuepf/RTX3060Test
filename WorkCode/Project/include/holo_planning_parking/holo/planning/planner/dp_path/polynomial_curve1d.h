/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef MODULES_PLANNING_MATH_CURVE1D_POLYNOMIAL_CURVE1D_H_
#define MODULES_PLANNING_MATH_CURVE1D_POLYNOMIAL_CURVE1D_H_

#include <holo/planning/planner/dp_path/curve1d.h>

namespace holo
{
namespace planning
{
class PolynomialCurve1d : public Curve1d
{
public:
    PolynomialCurve1d() = default;
    virtual ~PolynomialCurve1d() = default;

protected:
    float64_t param_ = 0.0;
};

}  // namespace planning
}  // namespace holo

#endif  // MODULES_PLANNING_MATH_CURVE1D_POLYNOMIAL_CURVE1D_H_
