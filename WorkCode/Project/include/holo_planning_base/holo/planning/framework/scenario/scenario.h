/*!
 *  \brief This header file define a scenario.
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2019-09-04
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_SCENARIO_H_
#define _HOLO_PLANNING_SCENARIO_H_

#include <holo/planning/common/car_road_state.h>
#include <holo/planning/common/headers.h>
#include <holo/planning/common/plan_route.h>

namespace holo
{
namespace planning
{

class Scenario
{
public:
    Scenario() = default;
    virtual ~Scenario() = default;

    virtual bool_t Plan(const CarRoadState& state, PlanRoute& route) = 0;

protected:

};

}
}

#endif