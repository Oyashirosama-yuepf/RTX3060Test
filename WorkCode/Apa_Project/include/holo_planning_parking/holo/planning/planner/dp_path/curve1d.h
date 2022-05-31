/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef MODULES_PLANNING_MATH_CURVE1D_CURVE1D_H_
#define MODULES_PLANNING_MATH_CURVE1D_CURVE1D_H_

#include <string>

namespace holo
{
namespace planning
{
// Base type for various types of 1-dimensional curves

class Curve1d {
 public:
  Curve1d() = default;

  virtual ~Curve1d() = default;

  virtual float64_t Evaluate(const std::uint32_t order,
                          const float64_t param) const = 0;

  virtual float64_t ParamLength() const = 0;
};

}  // namespace planning
}  // namespace holo

#endif  // MODULES_PLANNING_MATH_CURVE1D_CURVE1D_H_
