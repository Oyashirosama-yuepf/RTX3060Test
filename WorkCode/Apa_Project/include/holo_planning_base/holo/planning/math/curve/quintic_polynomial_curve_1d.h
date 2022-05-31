/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2018-10-30
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_MATH_QUINTIC_POLYNOMIAL_CURVE_1D_H_
#define _HOLO_PLANNING_MATH_QUINTIC_POLYNOMIAL_CURVE_1D_H_

#include <array>

#include <holo/planning/common/headers.h>
#include <holo/planning/math/curve/curve_1d.h>

namespace holo
{
namespace planning
{
namespace math
{
/**
 * @brief      QuinticPolynomialCurve1d class
 *
 *             1-dimensional quintic polynomial curve.
 */
class QuinticPolynomialCurve1d : public Curve1d
{
public:
    QuinticPolynomialCurve1d() {}

    QuinticPolynomialCurve1d(const std::array<float64_t, 3>& start,
                             const std::array<float64_t, 3>& end,
                             const float64_t param);

    QuinticPolynomialCurve1d(const float64_t x0, const float64_t dx0, const float64_t ddx0,
                             const float64_t x1, const float64_t dx1, const float64_t ddx1,
                             const float64_t param);

    QuinticPolynomialCurve1d(const QuinticPolynomialCurve1d& other);

    virtual ~QuinticPolynomialCurve1d() = default;

    virtual float64_t Evaluate(const uint32_t order, const float64_t p) const override;

    virtual float64_t ParamLength() const;

    /**
     * @brief Curve1d to string
     *
     * @return string
     */
    virtual std::string String() const;

protected:
    void ComputeCoefficients(const float64_t x0, const float64_t dx0, const float64_t ddx0,
                             const float64_t x1, const float64_t dx1, const float64_t ddx1,
                             const float64_t param);

protected:
    float64_t param_ = 0.0;

    // f = sum(coef_[i] * x^i), i from 0 to 5
    std::array<float64_t, 6> coef_{{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}};
    std::array<float64_t, 3> start_condition_{{0.0, 0.0, 0.0}};
    std::array<float64_t, 3> end_condition_{{0.0, 0.0, 0.0}};
};

}  // namespace math
}  // namespace planning
}  // namespace holo

#endif
