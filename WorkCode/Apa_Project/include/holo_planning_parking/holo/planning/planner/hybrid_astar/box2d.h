/*!
 *  \brief
 *  \author panhu (panhu@holomatic.com)
 *  \date 2019-04-15
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _BOX2D_H_
#define _BOX2D_H_

#include <cmath>
#include <limits>
#include <vector>

#include <holo/planning/planner/hybrid_astar/line_segment2d.h>
#include <holo/planning/planner/hybrid_astar/vec2d.h>

namespace holo
{
namespace planning
{
class Box2d
{
public:
    Box2d(const Vec2d& center, const float64_t heading, const float64_t length, const float64_t width);

    void InitCorners();

    const Vec2d& center() const
    {
        return center_;
    }

    float64_t center_x() const
    {
        return center_.x();
    }

    float64_t center_y() const
    {
        return center_.y();
    }

    float64_t length() const
    {
        return length_;
    }

    float64_t width() const
    {
        return width_;
    }

    float64_t half_length() const
    {
        return half_length_;
    }

    float64_t half_width() const
    {
        return half_width_;
    }

    float64_t heading() const
    {
        return heading_;
    }

    float64_t cos_heading() const
    {
        return cos_heading_;
    }

    float64_t sin_heading() const
    {
        return sin_heading_;
    }

    float64_t area() const
    {
        return length_ * width_;
    }

    float64_t max_x() const
    {
        return max_x_;
    }

    float64_t min_x() const
    {
        return min_x_;
    }

    float64_t max_y() const
    {
        return max_y_;
    }

    float64_t min_y() const
    {
        return min_y_;
    }

    /**
     * @brief Tests points for membership in the box
     *
     * @param point A point that we wish to test for membership in the box
     *
     * @return True iff the point is contained in the box
     */
    bool IsPointIn(const Vec2d& point) const;

    /**
     * @brief Determines the distance between the box and a given line segment
     *
     * @param line_segment The line segment whose distance to the box we compute
     *
     * @return A distance
     */
    float64_t DistanceTo(const LineSegment2d& line_segment) const;

    /**
     * @brief Determines whether this box overlaps a given line segment
     *
     * @param line_segment The line-segment
     *
     * @return True if they overlap
     */
    bool HasOverlap(const LineSegment2d& line_segment) const;

    /**
     * @brief Getter of the corners of the box
     * @param corners The vector where the corners are listed
     */
    std::vector<Vec2d> GetAllCorners() const;

private:
    Vec2d     center_;
    float64_t length_      = 0.0;
    float64_t width_       = 0.0;
    float64_t half_length_ = 0.0;
    float64_t half_width_  = 0.0;
    float64_t heading_     = 0.0;
    float64_t cos_heading_ = 1.0;
    float64_t sin_heading_ = 0.0;

    std::vector<Vec2d> corners_;

    float64_t max_x_ = std::numeric_limits<float64_t>::min();
    float64_t min_x_ = std::numeric_limits<float64_t>::max();
    float64_t max_y_ = std::numeric_limits<float64_t>::min();
    float64_t min_y_ = std::numeric_limits<float64_t>::max();
};
}  // namespace planning
}  // namespace holo
#endif