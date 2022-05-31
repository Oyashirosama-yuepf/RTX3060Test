/*!
 *  \brief
 *  \author dongyong (dongyong@holomatic.com)
 *  \date May 29, 2018
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_TYPES_H_
#define _HOLO_PLANNING_TYPES_H_

#include <assert.h>

#include <holo/core/types.h>
#include <holo/obstacle/obstacle_general.h>

namespace holo
{
namespace planning
{
struct SLBoundary
{
    SLBoundary(float64_t ss, float64_t es, float64_t sl, float64_t el)
    {
        assert(es > ss);
        assert(el > sl);
        start_s = ss;
        end_s   = es;
        start_l = sl;
        end_l   = el;
    };
    float64_t start_s;
    float64_t end_s;
    float64_t start_l;
    float64_t end_l;
};
/**
 * types for planning
 */
typedef obstacle::ObstacleGeneralT<float64_t> ObstacleGeneral;

}  // namespace planning
}  // namespace holo

#endif
