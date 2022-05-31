/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2018-01-18
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_ACTION_H_
#define _HOLO_PLANNING_ACTION_H_

#include <holo/core/types.h>

#include <holo/hpp/hpp_car_road_state.h>
#include <holo/planning/common/plan_route.h>

namespace holo
{
namespace planning
{
/**
 * @brief      Class for Action.
 * @details    There are a lot of actions, like lane keeping, lane changing,
 *             etc. And Action Class is used to describe the car's action. But,
 *             it has a few concrete implementations, and more is the framework
 *             structure.
 */
class Action
{
public:
    /**
     * @brief      Constructor.
     */
    Action();

    /**
     * @brief      Destroys the object.
     */
    virtual ~Action();

    /**
     * @brief      Check the action status.
     *
     * @param[in]  car_road_state  The car road state
     * @param      route           The plan route
     *
     * @return     True if action is changed in check(), False otherwise.
     */
    virtual bool Check(const HppCarRoadState& hpp_car_road_state, PlanRoute& route);

    /**
     * @brief      Perform the action.
     *
     * @param[in]  car_road_state  The car road state
     * @param      route           The route
     *
     * @return     True if action is executed successfully. False otherwise.
     */
    virtual bool Perform(const HppCarRoadState& hpp_car_road_state, PlanRoute& route);

    /**
     * @brief      Reset the action state.
     */
    virtual void Reset();

protected:
};

}  // namespace planning
}  // namespace holo

#endif