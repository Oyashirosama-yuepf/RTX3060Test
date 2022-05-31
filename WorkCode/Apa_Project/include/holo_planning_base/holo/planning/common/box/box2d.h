/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box2d.h
 * @brief the header of 2d box
 * @author zhangyuchen(zhangyuchen@holomatic.com)
 * @date 2019-12-25
 */

#ifndef _HOLO_PLANNING_BOX_2D_H_
#define _HOLO_PLANNING_BOX_2D_H_

#include <assert.h>
#include <cmath>

#include <holo/core/types.h>
#include <holo/geometry/point2.h>

#include <holo/planning/common/constant.h>

namespace holo
{
namespace planning
{
/**
 * @brief class to express 2d box
 */
class Box2d
{
public:
    /**
     * @brief Construct a new Box 2d object
     */
    Box2d() = default;

    /**
     * @brief Construct a new Box 2d object
     *
     * @param tl_x top left vertex position x
     * @param tl_y top left vertex position y
     * @param tr_x top right vertex position x
     * @param tr_y top right vertex position y
     * @param ll_x lower left vertex position x
     * @param ll_y lower left vertex position y
     * @param lr_x lower right vertex position x
     * @param lr_y lower right vertex position y
     */
    Box2d(float64_t tl_x,
          float64_t tl_y,
          float64_t tr_x,
          float64_t tr_y,
          float64_t ll_x,
          float64_t ll_y,
          float64_t lr_x,
          float64_t lr_y)
      : top_left_vertex_(tl_x, tl_y)
      , top_right_vertex_(tr_x, tr_y)
      , lower_left_vertex_(ll_x, ll_y)
      , lower_right_vertex_(lr_x, lr_y)
    {
    }

    /**
     * @brief Destroy the Box 2d object
     */
    virtual ~Box2d() = default;

    /**
     * @brief get the maximun x of box
     *
     * @return float64_t maximun m
     */
    float64_t GetMaxX() const
    {
        return std::max(top_left_vertex_.GetX(), top_right_vertex_.GetX());
    }

    /**
     * @brief get the maximun y of box
     *
     * @return float64_t maximun y of box
     */
    float64_t GetMaxY() const
    {
        return std::max(lower_left_vertex_.GetY(), top_left_vertex_.GetY());
    }

    /**
     * @brief get the minimun x of box
     *
     * @return float64_t minimun x of box
     */
    float64_t GetMinX() const
    {
        return std::min(lower_left_vertex_.GetX(), lower_right_vertex_.GetX());
    }

    /**
     * @brief get the minimun y of box
     *
     * @return float64_t minimun y of box
     */
    float64_t GetMinY() const
    {
        return std::min(lower_right_vertex_.GetY(), top_right_vertex_.GetY());
    }

    /**
     * @brief judge if box is a rectangle and parallels to axis
     *
     * @return bool_t true if box is a rectangle and parallels to axis, false otherwise
     */
    bool_t IsNormalBox() const
    {
        return fabs(top_left_vertex_.GetX() - top_right_vertex_.GetX()) < ALMOST_ZERO &&
               fabs(lower_left_vertex_.GetX() - lower_right_vertex_.GetX()) < ALMOST_ZERO &&
               fabs(top_left_vertex_.GetY() - lower_left_vertex_.GetY()) < ALMOST_ZERO &&
               fabs(top_right_vertex_.GetY() - lower_right_vertex_.GetY()) < ALMOST_ZERO;
    }

    /**
     * @brief set position
     */
    virtual void SetPosition(float64_t x, float64_t y) = 0;

    /**
     * @brief judge if two boxes are overlapping
     *
     * @param box another box
     *
     * @return bool_t true if two boxes are overlapping, false otherwise
     */
    virtual bool_t IsOverlap(const Box2d& box) const = 0;

    /**
     * @brief get the width of box
     *
     * @return float64_t width of box
     */
    virtual float64_t GetWidth() const = 0;

    /**
     * @brief get the length of box
     *
     * @return float64_t length of box
     */
    virtual float64_t GetLength() const = 0;

protected:
    /**
     * @brief two of the four vertices with the largest x are top vertices
     *        vertex in top vertices with largest y is top_left_vertex
     *        two of the four vertices with the smallest x are lower vertices
     *        vertex in lower vertices with largest y is lower_left_vertex
     *
     *                     y
     *                     |
     *   lower_left________|_______ top_left
     *            |        |       |
     *       —————|————————|———————|——————————>x
     *            |        |       |
     *            |________|_______|
     *  lower_right        |        top_right
     */

    /**
     * @brief top left vertex of box
     */
    geometry::Point2d top_left_vertex_;

    /**
     * @brief top right vertex of box
     */
    geometry::Point2d top_right_vertex_;

    /**
     * @brief lower left vertex of box
     */
    geometry::Point2d lower_left_vertex_;

    /**
     * @brief lower right vertex of box
     */
    geometry::Point2d lower_right_vertex_;
};

}  // namespace planning
}  // namespace holo

#endif