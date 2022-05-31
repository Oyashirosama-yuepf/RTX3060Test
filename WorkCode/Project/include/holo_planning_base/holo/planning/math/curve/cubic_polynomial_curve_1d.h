/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2018-12-17
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_MATH_CUBIC_POLYNOMIAL_CURVE_1D_H_
#define _HOLO_PLANNING_MATH_CUBIC_POLYNOMIAL_CURVE_1D_H_

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
 * @brief      CubicPolynomialCurve1d class
 *
 *             1-dimensional cubic polynomial curve.
 */
class CubicPolynomialCurve1d : public Curve1d
{
public:
    CubicPolynomialCurve1d() = default;

    CubicPolynomialCurve1d(const std::array<float64_t, 2>& start,
                           const std::array<float64_t, 2>& end,
                           const float64_t param);

    CubicPolynomialCurve1d(const float64_t x0, const float64_t dx0,
                           const float64_t x1, const float64_t dx1,
                           const float64_t param);

    CubicPolynomialCurve1d(const CubicPolynomialCurve1d& other);

    virtual ~CubicPolynomialCurve1d() = default;

    float64_t Evaluate(const uint32_t order, const float64_t p) const override;

    float64_t ParamLength() const;

    /**
     * @brief Curve1d to string
     *
     * @return string
     */
    virtual std::string String() const;

protected:
    void ComputeCoefficients(const float64_t x0, const float64_t dx0,
                             const float64_t x1, const float64_t dx1,
                             const float64_t param);

protected:
    float64_t param_ = 0.0;

    // f = sum(coef_[i] * x^i), i from 0 to 5
    std::array<float64_t, 4> coef_{{0.0, 0.0, 0.0, 0.0}};
    std::array<float64_t, 2> start_condition_{{0.0, 0.0}};
    std::array<float64_t, 2> end_condition_{{0.0, 0.0}};
};

}  // namespace math
}  // namespace planning
}  // namespace holo

#endif
