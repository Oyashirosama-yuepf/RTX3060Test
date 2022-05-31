/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2018-10-30
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_MATH_CURVE_1D_H_
#define _HOLO_PLANNING_MATH_CURVE_1D_H_

#include <holo/planning/common/headers.h>

namespace holo
{
namespace planning
{
namespace math
{
/**
 * @brief      Curve1d class
 *
 *             Base type for various types of 1-dimensional curves
 */
class Curve1d
{
public:
    Curve1d() = default;

    virtual ~Curve1d() = default;

    virtual float64_t Evaluate(const uint32_t order, const float64_t param) const = 0;
    virtual float64_t ParamLength() const = 0;

    /**
     * @brief Curve1d to string
     *
     * @return string
     */
    virtual std::string String() const = 0;
};

}  // namespace math

std::ostream& operator<<(std::ostream& os, const math::Curve1d& curve);
std::ostream& operator<<(std::ostream& os, const std::shared_ptr<math::Curve1d>& curve);

}  // namespace planning
}  // namespace holo

#endif
