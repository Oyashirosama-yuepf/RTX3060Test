/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file normal_box.h
 * @brief the header of normal box
 * @author zhangyuchen(zhangyuchen@holomatic.com)
 * @date 2019-12-25
 */

#ifndef _HOLO_PLANNING_NORMAL_BOX_H_
#define _HOLO_PLANNING_NORMAL_BOX_H_

#include <assert.h>

#include <holo/planning/common/box/box2d.h>

namespace holo
{
namespace planning
{
/**
 * @brief class to express normal box which is a rectangle and parallels to axis
 */
class NormalBox : public Box2d
{
public:
    /**
     * @brief Construct a new Normal Box object
     *
     * @param x box position x
     * @param y box position y
     * @param dist_to_top dist to top edge from coordinate point
     * @param dist_to_lower dist to lower edge from coordinate point
     * @param dist_to_left dist to left edge from coordinate point
     * @param dist_to_right dist to right edge from coordinate point
     */
    NormalBox(float64_t x,
              float64_t y,
              float64_t dist_to_top,
              float64_t dist_to_lower,
              float64_t dist_to_left,
              float64_t dist_to_right)
      : Box2d(x + dist_to_top,
              y + dist_to_left,
              x + dist_to_top,
              y - dist_to_right,
              x - dist_to_lower,
              y + dist_to_left,
              x - dist_to_lower,
              y - dist_to_right)
      , position_(x, y)
    {
        assert(dist_to_top > ALMOST_ZERO);
        assert(dist_to_lower > ALMOST_ZERO);
        assert(dist_to_left > ALMOST_ZERO);
        assert(dist_to_right > ALMOST_ZERO);

        dist_to_top_edge_   = dist_to_top;
        dist_to_lower_edge_ = dist_to_lower;
        dist_to_left_edge_  = dist_to_left;
        dist_to_right_edge_ = dist_to_right;
    }

    /**
     * @brief Construct a new Normal Box object
     *
     * @param max_x maximun position x of box
     * @param max_y maximun position y of box
     * @param min_x minimun position x of box
     * @param min_y minimun position y of box
     */
    NormalBox(float64_t max_x, float64_t max_y, float64_t min_x, float64_t min_y)
      : Box2d(max_x, max_y, max_x, min_y, min_x, max_y, min_x, min_y)
    {
        assert(max_x - min_x > ALMOST_ZERO);
        assert(max_y - min_y > ALMOST_ZERO);

        position_.Set(max_x * 0.5 + min_x * 0.5, max_y * 0.5 + min_y * 0.5);
        dist_to_top_edge_   = (max_x - min_x) * 0.5;
        dist_to_lower_edge_ = (max_x - min_x) * 0.5;
        dist_to_left_edge_  = (max_y - min_y) * 0.5;
        dist_to_right_edge_ = (max_y - min_y) * 0.5;

        top_left_vertex_.Set(max_x, max_y);
        top_right_vertex_.Set(max_x, min_y);
        lower_left_vertex_.Set(min_x, max_y);
        lower_right_vertex_.Set(min_x, min_y);
    }

    /**
     * @brief Destroy the Box object
     */
    virtual ~NormalBox() = default;

    /**
     * @brief set position
     *
     * @param x position x
     * @param y position y
     */
    void SetPosition(float64_t x, float64_t y) override
    {
        position_.Set(x, y);
        top_left_vertex_.Set(x + dist_to_top_edge_, y + dist_to_left_edge_);
        top_right_vertex_.Set(x + dist_to_top_edge_, y - dist_to_right_edge_);
        lower_left_vertex_.Set(x - dist_to_lower_edge_, y + dist_to_left_edge_);
        lower_right_vertex_.Set(x - dist_to_lower_edge_, y - dist_to_right_edge_);
    }

    /**
     * @brief judge if two boxes are overlapping
     *
     * @param box another box
     *
     * @return bool_t true if two boxes are overlapping, false otherwise
     */
    bool_t IsOverlap(const Box2d& box) const override
    {
        // todo: if another box is not a normal box, how to judge if two boxes are overlapping
        assert(IsNormalBox() == true);

        return !(GetMaxX() < box.GetMinX() || GetMaxY() < box.GetMinY() || GetMinX() > box.GetMaxX() ||
                 GetMinY() > box.GetMaxY());
    }

    /**
     * @brief get the width of box
     *
     * @return float64_t width of box
     */
    float64_t GetWidth() const override
    {
        return dist_to_left_edge_ + dist_to_right_edge_;
    }

    /**
     * @brief get the length of box
     *
     * @return float64_t length of box
     */
    float64_t GetLength() const override
    {
        return dist_to_top_edge_ + dist_to_lower_edge_;
    }

    /**
     * @brief get linear velocity of box
     *
     * @return float64_t linear velocity
     */
    float64_t GetVelocity() const
    {
        return velocity_;
    }

    /**
     * @brief set linear velocity of box
     *
     * @param vel the velocity
     */
    void SetVelocity(float64_t vel)
    {
        velocity_ = vel;
    }

private:
    /**
     * @brief position of box
     */
    geometry::Point2d position_;

    /**
     * @brief distance from coordinate point to top edge
     */
    float64_t dist_to_top_edge_;

    /**
     * @brief distance from coordinate point to lower edge
     */
    float64_t dist_to_lower_edge_;

    /**
     * @brief distance from coordinate point to left edge
     */
    float64_t dist_to_left_edge_;

    /**
     * @brief distance from coordinate point to right edge
     */
    float64_t dist_to_right_edge_;

    /**
     * @brief box linear velocity
     */
    float64_t velocity_;
};

}  // namespace planning
}  // namespace holo

#endif