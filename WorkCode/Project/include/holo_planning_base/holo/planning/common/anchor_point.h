/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2018-01-18
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_ANCHOR_POINT_H_
#define _HOLO_PLANNING_ANCHOR_POINT_H_

#include <holo/core/types.h>

#include <holo/planning/common/curve_point.h>

namespace holo
{
namespace planning
{
struct AnchorPoint
{
    CurvePoint reference_path_point;
    float64_t  weight             = 1.0;
    float64_t  longitudinal_bound = 0.0;
    float64_t  lateral_bound      = 0.0;
};

}  // namespace planning
}  // namespace holo

#endif  //_HOLO_PLANNING_COMMON_H_