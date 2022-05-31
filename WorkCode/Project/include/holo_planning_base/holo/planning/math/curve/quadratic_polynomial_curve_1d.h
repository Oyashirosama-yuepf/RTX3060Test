/*!
 *  \brief
 *  \author koujiayu (koujiayu@holomatic.com)
 *  \date 2019-11-25
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_MATH_QUADRATIC_POLYNOMIAL_CURVE_1D_H_
#define _HOLO_PLANNING_MATH_QUADRATIC_POLYNOMIAL_CURVE_1D_H_

#include <holo/planning/common/headers.h>
#include <holo/planning/math/curve/curve_1d.h>
#include <array>
namespace holo
{
namespace planning
{
namespace math
{
class QuadraticPolynomialCurve1d : public Curve1d
{
public:
    QuadraticPolynomialCurve1d() = default;
    QuadraticPolynomialCurve1d(const std::array<float64_t, 2>& point_0, const std::array<float64_t, 2>& point_1,
                               const std::array<float64_t, 2>& point_2);
    QuadraticPolynomialCurve1d(const float64_t x0, const float64_t y0, const float64_t x1, const float64_t y1,
                               const float64_t x2, const float64_t y2);

    virtual float64_t Evaluate(const uint32_t order, const float64_t p) const override;
    virtual float64_t ParamLength() const;

    /**
     * @brief Curve1d to string
     *
     * @return string
     */
    virtual std::string String() const;

    virtual ~QuadraticPolynomialCurve1d() = default;

protected:
    void ComputeCoefficients(const float64_t x0, const float64_t y0, const float64_t x1, const float64_t y1,
                             const float64_t x2, const float64_t y2);

protected:
    std::array<float64_t, 2> point_0_{{0.0, 0.0}};
    std::array<float64_t, 2> point_1_{{0.0, 0.0}};
    std::array<float64_t, 2> point_2_{{0.0, 0.0}};
    std::array<float64_t, 3> coef_{{0.0, 0.0, 0.0}};
};
}  // namespace math
}  // namespace planning

}  // namespace holo
#endif