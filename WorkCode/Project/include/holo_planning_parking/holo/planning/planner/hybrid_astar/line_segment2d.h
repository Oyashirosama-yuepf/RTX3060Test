/*!
 *  \brief
 *  \author panhu (panhu@holomatic.com)
 *  \date 2019-04-15
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _LINESGEMENT2D_H_
#define _LINESGEMENT2D_H_

#include <holo/planning/planner/hybrid_astar/vec2d.h>

namespace holo
{
namespace planning
{
class LineSegment2d
{
public:
    LineSegment2d(const Vec2d& start, const Vec2d& end);

    const Vec2d& start() const
    {
        return start_;
    }

    const Vec2d& end() const
    {
        return end_;
    }

    const Vec2d& unit_direction() const
    {
        return unit_direction_;
    }

    float64_t heading() const
    {
        return heading_;
    }

    float64_t cos_heading() const
    {
        return unit_direction_.x();
    }

    float64_t sin_heading() const
    {
        return unit_direction_.y();
    }

    float64_t length() const
    {
        return length_;
    }

private:
    Vec2d     start_;
    Vec2d     end_;
    Vec2d     unit_direction_;
    float64_t heading_ = 0.0;
    float64_t length_  = 0.0;
};

}  // namespace planning
}  // namespace holo
#endif