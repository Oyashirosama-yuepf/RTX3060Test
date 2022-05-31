/*!
 *  \brief Bezier Curve class
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2020-06-08
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_MATH_BEZIER_CURVE_HPP_
#define _HOLO_PLANNING_MATH_BEZIER_CURVE_HPP_

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

#include <holo/log/hololog.h>

namespace holo
{
namespace planning
{
namespace math
{
// ==, !=, [], size()
template <typename Point, uint32_t DIM>
BezierPoint<Point, DIM>::BezierPoint()
{
    coordinate.resize(DIM);
    curvature = -1.0;
}

template <typename Point, uint32_t DIM>
BezierPoint<Point, DIM>::BezierPoint(Point coords)
{
    if (coords.size() == DIM)
    {
        coordinate = coords;
    }
    else
    {
        coordinate.resize(DIM);
        LOG(ERROR) << "Wrong in Bezier Curve: invalid coords size";
    }
    curvature = -1.0;
}

template <typename Point, uint32_t DIM>
BezierPoint<Point, DIM>::BezierPoint(Point coords, float64_t curvature_in)
{
    curvature = curvature_in;
    if (coords.size() == DIM)
    {
        coordinate = coords;
    }
    else
    {
        coordinate.resize(DIM);
        LOG(ERROR) << "Wrong in Bezier Curve: invalid coords size";
    }
}

template <typename Point, uint32_t DIM>
bool_t BezierPoint<Point, DIM>::operator==(BezierPoint const& t) const
{
    return ((t.coordinate == this->coordinate) && (std::fabs(t.curvature - this->curvature) < 0.001));
}

template <typename Point, uint32_t DIM>
bool_t BezierPoint<Point, DIM>::operator!=(BezierPoint const& t) const
{
    return (!(t.coordinate == this->coordinate) || (std::fabs(t.curvature - this->curvature) > 0.001));
}

// Beizer
template <typename Point, uint32_t DIM>
Bezier<Point, DIM>::Bezier()
{
    dimension_ = DIM;
    order_     = 0;
}

template <typename Point, uint32_t DIM>
Bezier<Point, DIM>::Bezier(uint32_t curve_order)
{
    dimension_ = DIM;
    SetOrder(curve_order);
}

template <typename Point, uint32_t DIM>
Bezier<Point, DIM>::~Bezier()
{
}

template <typename Point, uint32_t DIM>
void Bezier<Point, DIM>::SetOrder(uint32_t curve_order)
{
    if (curve_order > 5 || curve_order < 1)
    {
        order_ = 0;
        LOG(ERROR) << "Wrong in Bezier Curve: Currently only support up to 5th order Bezier Curve";
        return;
    }
    order_ = curve_order;
    switch (curve_order)
    {
        case 1:
            bezier_curve_ = [this](float64_t t) -> BezierPoint<Point, DIM> {
                BezierPoint<Point, DIM> temp;
                for (uint32_t i = 0; i < DIM; ++i)
                {
                    temp.coordinate[i] =
                        (1 - t) * this->GetStartPt().coordinate[i] + t * this->GetEndPt().coordinate[i];
                }
                return temp;
            };
            break;
        case 2:
            bezier_curve_ = [this](float64_t t) -> BezierPoint<Point, DIM> {
                BezierPoint<Point, DIM> temp;
                for (uint32_t i = 0; i < DIM; ++i)
                {
                    temp.coordinate[i] = (1 - t) * (1 - t) * this->GetStartPt().coordinate[i] +
                                         2 * t * (1 - t) * this->GetCtrlPts()[0].coordinate[i] +
                                         t * t * this->GetEndPt().coordinate[i];
                }
                return temp;
            };
            deriv_1st_ = [this](float64_t t) -> std::vector<float64_t> {
                std::vector<float64_t> temp(DIM, 0.0);
                for (uint32_t i = 0; i < DIM; ++i)
                {
                    temp[i] = 2 * (t - 1) * this->GetStartPt().coordinate[i] +
                              (2 - 4 * t) * this->GetCtrlPts()[0].coordinate[i] +
                              2 * t * this->GetEndPt().coordinate[i];
                }
                return temp;
            };
            deriv_2nd_ = [this](float64_t t) -> std::vector<float64_t> {
                std::vector<float64_t> temp(DIM, 0.0);
                for (uint32_t i = 0; i < DIM; ++i)
                {
                    temp[i] = 2 * this->GetStartPt().coordinate[i] - 4 * this->GetCtrlPts()[0].coordinate[i] -
                              2 * this->GetEndPt().coordinate[i] + t * 0.0;
                }
                return temp;
            };
            break;
        case 3:
            bezier_curve_ = [this](float64_t t) -> BezierPoint<Point, DIM> {
                BezierPoint<Point, DIM> temp;
                for (uint32_t i = 0; i < DIM; ++i)
                {
                    temp.coordinate[i] = std::pow((1 - t), 3) * this->GetStartPt().coordinate[i] +
                                         3 * t * (1 - t) * (1 - t) * this->GetCtrlPts()[0].coordinate[i] +
                                         3 * t * t * (1 - t) * this->GetCtrlPts()[1].coordinate[i] +
                                         t * t * t * this->GetEndPt().coordinate[i];
                }
                return temp;
            };
            deriv_1st_ = [this](float64_t t) -> std::vector<float64_t> {
                std::vector<float64_t> temp(DIM, 0.0);
                for (uint32_t i = 0; i < DIM; ++i)
                {
                    temp[i] = -3 * (1 - t) * (1 - t) * this->GetStartPt().coordinate[i] +
                              (9 * t * t - 12 * t + 3) * this->GetCtrlPts()[0].coordinate[i] +
                              (6 * t - 9 * t * t) * this->GetCtrlPts()[1].coordinate[i] +
                              6 * t * t * this->GetEndPt().coordinate[i];
                }
                return temp;
            };
            deriv_2nd_ = [this](float64_t t) -> std::vector<float64_t> {
                std::vector<float64_t> temp(DIM, 0.0);
                for (uint32_t i = 0; i < DIM; ++i)
                {
                    temp[i] = -6 * (1 - t) * this->GetStartPt().coordinate[i] +
                              (18 * t - 12) * this->GetCtrlPts()[0].coordinate[i] +
                              (6 - 18 * t) * this->GetCtrlPts()[1].coordinate[i] + 6 * this->GetEndPt().coordinate[i];
                }
                return temp;
            };
            break;
        case 4:
            bezier_curve_ = [this](float64_t t) -> BezierPoint<Point, DIM> {
                BezierPoint<Point, DIM> temp;
                for (uint32_t i = 0; i < DIM; ++i)
                {
                    temp.coordinate[i] = std::pow((1 - t), 4) * this->GetStartPt().coordinate[i] +
                                         4 * std::pow((1 - t), 3) * t * this->GetCtrlPts()[0].coordinate[i] +
                                         6 * (1 - t) * (1 - t) * t * t * this->GetCtrlPts()[1].coordinate[i] +
                                         4 * (1 - t) * std::pow(t, 3) * this->GetCtrlPts()[2].coordinate[i] +
                                         std::pow(t, 4) * this->GetEndPt().coordinate[i];
                }
                return temp;
            };
            deriv_1st_ = [this](float64_t t) -> std::vector<float64_t> {
                std::vector<float64_t> temp(DIM, 0.0);
                for (uint32_t i = 0; i < DIM; ++i)
                {
                    temp[i] = 4 * std::pow((1 - t), 3) * this->GetStartPt().coordinate[i] +
                              (-8 * std::pow(t, 3) + 12 * t * t - 4) * this->GetCtrlPts()[0].coordinate[i] +
                              (24 * std::pow(t, 3) - 36 * t * t + 12 * t) * this->GetCtrlPts()[1].coordinate[i] +
                              (-16 * std::pow(t, 3) + 12 * t * t) * this->GetCtrlPts()[2].coordinate[i] +
                              4 * std::pow(t, 3) * this->GetEndPt().coordinate[i];
                }
                return temp;
            };
            deriv_2nd_ = [this](float64_t t) -> std::vector<float64_t> {
                std::vector<float64_t> temp(DIM, 0.0);
                for (uint32_t i = 0; i < DIM; ++i)
                {
                    temp[i] = 12 * (1 - t) * (1 - t) * this->GetStartPt().coordinate[i] +
                              (-24 * t * t + 24 * t) * this->GetCtrlPts()[0].coordinate[i] +
                              (72 * t * t - 72 * t + 12) * this->GetCtrlPts()[1].coordinate[i] +
                              (-48 * t * t + 24 * t) * this->GetCtrlPts()[2].coordinate[i] +
                              12 * t * t * this->GetEndPt().coordinate[i];
                }
                return temp;
            };
            break;
        case 5:
            bezier_curve_ = [this](float64_t t) -> BezierPoint<Point, DIM> {
                BezierPoint<Point, DIM> temp;
                for (uint32_t i = 0; i < DIM; ++i)
                {
                    temp.coordinate[i] = std::pow((1 - t), 5) * this->GetStartPt().coordinate[i] +
                                         5 * std::pow((1 - t), 4) * t * this->GetCtrlPts()[0].coordinate[i] +
                                         10 * std::pow((1 - t), 3) * t * t * this->GetCtrlPts()[1].coordinate[i] +
                                         10 * (1 - t) * (1 - t) * std::pow(t, 3) * this->GetCtrlPts()[2].coordinate[i] +
                                         5 * (1 - t) * std::pow(t, 4) * this->GetCtrlPts()[3].coordinate[i] +
                                         std::pow(t, 5) * this->GetEndPt().coordinate[i];
                }
                return temp;
            };
            deriv_1st_ = [this](float64_t t) -> std::vector<float64_t> {
                std::vector<float64_t> temp(DIM, 0.0);
                for (uint32_t i = 0; i < DIM; ++i)
                {
                    temp[i] = -5 * std::pow((1 - t), 4) * this->GetStartPt().coordinate[i] +
                              (20 * t * std::pow((t - 1), 3) + 5 * std::pow((1 - t), 4)) *
                                  this->GetCtrlPts()[0].coordinate[i] +
                              (20 * t * std::pow((1 - t), 3) - 30 * std::pow((1 - t), 2) * t * t) *
                                  this->GetCtrlPts()[1].coordinate[i] +
                              (30 * t * t * std::pow((t - 1), 2) + 20 * std::pow(t, 3) * (t - 1)) *
                                  this->GetCtrlPts()[2].coordinate[i] +
                              (-25 * std::pow(t, 4) + 20 * std::pow(t, 3)) * this->GetCtrlPts()[3].coordinate[i] +
                              5 * std::pow(t, 4) * this->GetEndPt().coordinate[i];
                }
                return temp;
            };
            deriv_2nd_ = [this](float64_t t) -> std::vector<float64_t> {
                std::vector<float64_t> temp(DIM, 0.0);
                for (uint32_t i = 0; i < DIM; ++i)
                {
                    temp[i] =
                        20 * std::pow((1 - t), 3) * this->GetStartPt().coordinate[i] +
                        (40 * std::pow((t - 1), 3) + 60 * t * (t - 1) * (t - 1)) * this->GetCtrlPts()[0].coordinate[i] +
                        (20 * std::pow((1 - t), 3) - 80 * t * (t - 1) * (t - 1) - 60 * t * t * (t - 1)) *
                            this->GetCtrlPts()[1].coordinate[i] +
                        (60 * t * (t - 1) * (t - 1) + 120 * t * t * (t - 1) + 20 * std::pow(t, 3)) *
                            this->GetCtrlPts()[2].coordinate[i] +
                        (-100 * std::pow(t, 3) + 60 * t * t) * this->GetCtrlPts()[3].coordinate[i] +
                        20 * std::pow(t, 3) * this->GetEndPt().coordinate[i];
                }
                return temp;
            };
            break;
    }
}

template <typename Point, uint32_t DIM>
uint32_t Bezier<Point, DIM>::GetOrder() const
{
    return order_;
}

template <typename Point, uint32_t DIM>
void Bezier<Point, DIM>::SetEndPt(BezierPoint<Point, DIM> end_point)
{
    end_ = end_point;
}

template <typename Point, uint32_t DIM>
BezierPoint<Point, DIM> Bezier<Point, DIM>::GetEndPt() const
{
    return end_;
}

template <typename Point, uint32_t DIM>
void Bezier<Point, DIM>::SetStartPt(BezierPoint<Point, DIM> start_point)
{
    start_ = start_point;
}

template <typename Point, uint32_t DIM>
BezierPoint<Point, DIM> Bezier<Point, DIM>::GetStartPt() const
{
    return start_;
}

template <typename Point, uint32_t DIM>
bool_t Bezier<Point, DIM>::SetCtrlPts(std::vector<BezierPoint<Point, DIM>> ctrl_points)
{
    if (order_ == 0)
    {
        LOG(ERROR) << "Wrong in Beizer Curve: number of ctrl_pts != curve order.";
        return false;
    }
    if (order_ != ctrl_points.size() + 1)
    {
        LOG(ERROR) << "Wrong in Beizer Curve: wrong input size of ctrl_points";
        return false;
    }
    ctrl_pts_ = ctrl_points;
    return true;
}

template <typename Point, uint32_t DIM>
std::vector<BezierPoint<Point, DIM>> Bezier<Point, DIM>::GetCtrlPts() const
{
    return ctrl_pts_;
}

template <typename Point, uint32_t DIM>
std::function<BezierPoint<Point, DIM>(float64_t t)> Bezier<Point, DIM>::GetBezierFunction() const
{
    return bezier_curve_;
}

template <typename Point, uint32_t DIM>
void Bezier<Point, DIM>::PtsOnCurve(std::vector<BezierPoint<Point, DIM>>& curve_points, uint32_t quantity)
{
    if (curve_points.size() != quantity)
    {
        LOG(ERROR) << "Wrong in Bezier Curve: container size != quantity.";
        return;
    }
    if (order_ <= 0 || (ctrl_pts_.size() + 1) != order_ || dimension_ < 1 || dimension_ > 3)
    {
        LOG(ERROR) << "Wrong in Bezier Curve: not enough setup";
        return;
    }
    for (uint32_t i = 0; i < quantity; ++i)
    {
        float64_t t_temp = 1.0 * i / (quantity - 1);
        curve_points[i]  = bezier_curve_(t_temp);
        if (order_ == 1)
        {
            curve_points[i].curvature = 0.0;
            break;
        }
        std::vector<float64_t> deriv_1       = deriv_1st_(t_temp);
        std::vector<float64_t> deriv_2       = deriv_2nd_(t_temp);
        float64_t              norm_square   = 0.0;
        float64_t              cross_product = 0.0;
        if (dimension_ == 2)
        {
            cross_product = deriv_1[0] * deriv_2[1] - deriv_1[1] * deriv_2[0];
            norm_square   = std::pow(deriv_1[0], 2) + std::pow(deriv_1[1], 2);
        }
        else if (dimension_ == 3)
        {
            cross_product = std::pow((deriv_1[1] * deriv_2[2] - deriv_1[2] * deriv_2[1]), 2) +
                            std::pow((deriv_1[2] * deriv_2[0] - deriv_1[0] * deriv_2[2]), 2) +
                            std::pow((deriv_1[0] * deriv_2[1] - deriv_1[1] * deriv_2[0]), 2);
            norm_square = std::pow(deriv_1[0], 2) + std::pow(deriv_1[1], 2) + std::pow(deriv_1[2], 2);
        }
        curve_points[i].curvature = cross_product / std::pow(norm_square, 1.5);
        // to do: [1] y; [0]: x; only two dimension considered
        curve_points[i].theta = std::atan(deriv_1[0] / deriv_1[1]);
    }
}

}  // namespace math
}  // namespace planning
}  // namespace holo

#endif