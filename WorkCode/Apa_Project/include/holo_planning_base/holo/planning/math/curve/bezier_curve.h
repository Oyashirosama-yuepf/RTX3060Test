/*!
 *  \brief Bezier Curve Class
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2020-06-08
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_MATH_BEZIER_CURVE_H_
#define _HOLO_PLANNING_MATH_BEZIER_CURVE_H_

#include <functional>
#include <vector>

#include <holo_c/core/types.h>

namespace holo
{
namespace planning
{
namespace math
{
/**
 * @brief BezierPoint Class
 *
 * @details the Type Point should support the following operators: ==, !=, size(), []
 */
template <typename Point, uint32_t DIM>
struct BezierPoint
{
    BezierPoint();
    BezierPoint(Point coords);
    BezierPoint(Point coords, float64_t curvature_in);
    float64_t curvature;
    float64_t theta;
    Point     coordinate;
    bool_t    operator==(BezierPoint const& t) const;
    bool_t    operator!=(BezierPoint const& t) const;
};

template <typename Point, uint32_t DIM>
class Bezier
{
public:
    Bezier();
    Bezier(uint32_t curve_order);
    ~Bezier();
    void                                 SetOrder(uint32_t curve_order);
    uint32_t                             GetOrder() const;
    void                                 SetEndPt(BezierPoint<Point, DIM> end_point);
    BezierPoint<Point, DIM>              GetEndPt() const;
    void                                 SetStartPt(BezierPoint<Point, DIM> start_point);
    BezierPoint<Point, DIM>              GetStartPt() const;
    bool_t                               SetCtrlPts(std::vector<BezierPoint<Point, DIM>> ctrl_points);
    std::vector<BezierPoint<Point, DIM>> GetCtrlPts() const;

    std::function<BezierPoint<Point, DIM>(float64_t t)> GetBezierFunction() const;
    /**
     * @brief Calculate and return "Quantity" number of Points
     */
    void PtsOnCurve(std::vector<BezierPoint<Point, DIM>>& curve_points, uint32_t quantity);

private:
    uint32_t                             order_;
    float64_t                            length_;
    uint32_t                             dimension_;
    BezierPoint<Point, DIM>              start_;
    BezierPoint<Point, DIM>              end_;
    std::vector<BezierPoint<Point, DIM>> ctrl_pts_;

    std::function<BezierPoint<Point, DIM>(float64_t t)> bezier_curve_;
    std::function<std::vector<float64_t>(float64_t t)>  deriv_1st_;
    std::function<std::vector<float64_t>(float64_t t)>  deriv_2nd_;
};

}  // namespace math
}  // namespace planning
}  // namespace holo

#endif