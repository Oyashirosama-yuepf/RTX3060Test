/*!
 *  \brief record several plan_route history data
 *  \author lijiawen (lijiawen@holomatic.com)
 *  \date 2018-09-19
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_PLAN_ROUTE_HISTORY_H_
#define _HOLO_PLANNING_PLAN_ROUTE_HISTORY_H_

#include <list>

#include <holo/planning/common/macro.h>
#include <holo/planning/common/plan_route.h>

namespace holo
{
namespace planning
{

class PlanRouteHistory
{
public:

    bool AddPlanRoute(std::shared_ptr<PlanRoute> plan_route);

    const std::shared_ptr<PlanRoute> GetLastPlanRoute() const;

    void Reset();


protected:

    const uint32_t plan_route_num_ = 3;
    std::list<std::shared_ptr<PlanRoute>> plan_route_list_;

    DECLARE_SINGLETON(PlanRouteHistory)

};

}
}

#endif