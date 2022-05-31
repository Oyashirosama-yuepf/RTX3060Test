/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2019-08-29
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_FALLBACK_EVENT_HANDLE_H_
#define _HOLO_PLANNING_FALLBACK_EVENT_HANDLE_H_

#include <holo/planning/common/car_road_state.h>
#include <holo/planning/common/plan_route.h>
#include <holo/planning/framework/fallback/event.h>

namespace holo
{
namespace planning
{
namespace fallback
{
/**
 * @brief      Class for event handle.
 * @details    EventHandle is a base class with no concrete implementation, just
 *             a framework.
 */
class EventHandle
{
public:
    /**
     * @brief      Constructs the object.
     */
    EventHandle() = default;

    /**
     * @brief      Destroys the object.
     */
    virtual ~EventHandle() = default;

    /**
     * @brief      event handle function
     *
     * @param[in]  e               The event
     * @param[in]  car_road_state  The car road state
     * @param      route           The route
     *
     * @return     { description_of_the_return_value }
     */
    virtual bool_t Process(const std::shared_ptr<Event> e, const CarRoadState& car_road_state, PlanRoute& route) = 0;

private:
};

}  // namespace fallback
}  // namespace planning
}  // namespace holo

#endif