/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2018-10-31
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_UTIL_PATH_MATCHER_H_
#define _HOLO_PLANNING_UTIL_PATH_MATCHER_H_

#include <vector>

#include <holo/planning/common/curve_point.h>
#include <holo/planning/common/headers.h>

namespace holo
{
namespace planning
{
class PathMatcher
{
public:
    PathMatcher() = delete;

    static CurvePoint Match2Path(const std::vector<CurvePoint>& reference_line, const float64_t x, const float64_t y);

    static CurvePoint Match2Path(const std::vector<CurvePoint>& reference_line, const float64_t s);

    static std::pair<float64_t, float64_t> GetPathFrenetCoordinate(const std::vector<CurvePoint>& reference_line,
                                                                   const float64_t                x,
                                                                   const float64_t                y);

private:
    static CurvePoint
    FindProjectionPoint(const CurvePoint& p0, const CurvePoint& p1, const float64_t x, const float64_t y);
};

}  // namespace planning
}  // namespace holo

#endif