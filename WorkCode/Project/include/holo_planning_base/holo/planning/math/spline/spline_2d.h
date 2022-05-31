/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef MODULES_PLANNING_SMOOTHING_SPLINE_SPLINE_2D_H_
#define MODULES_PLANNING_SMOOTHING_SPLINE_SPLINE_2D_H_

#include <Eigen/Core>
#include <utility>
#include <vector>

#include <holo/numerics/matrix.h>

#include <holo/planning/math/spline/spline_2d_seg.h>

namespace holo
{
namespace planning
{
class Spline2d
{
public:
    Spline2d(const std::vector<float64_t>& t_knots, const uint32_t order);

    std::pair<float64_t, float64_t> operator()(const float64_t t) const;

    float64_t x(const float64_t t) const;
    float64_t y(const float64_t t) const;
    float64_t DerivativeX(const float64_t t) const;
    float64_t DerivativeY(const float64_t t) const;
    float64_t SecondDerivativeX(const float64_t t) const;
    float64_t SecondDerivativeY(const float64_t t) const;
    float64_t ThirdDerivativeX(const float64_t t) const;
    float64_t ThirdDerivativeY(const float64_t t) const;

    bool_t                        set_splines(const Eigen::MatrixXd& params, const uint32_t order);
    const std::vector<float64_t>& t_knots() const;
    uint32_t                      spline_order() const;

private:
    uint32_t find_index(const float64_t x) const;

private:
    std::vector<Spline2dSeg> splines_;
    std::vector<float64_t>   t_knots_;
    uint32_t                 spline_order_;
};

}  // namespace planning
}  // namespace holo

#endif  // MODULES_PLANNING_SMOOTHING_SPLINE_SPLINE_2D_H_
