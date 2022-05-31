/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2019-8-29
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_FALLBACK_EVENT_TRIGGER_H_
#define _HOLO_PLANNING_FALLBACK_EVENT_TRIGGER_H_
#include <holo/planning/common/car_road_state.h>
#include <holo/planning/common/headers.h>
#include <holo/planning/common/plan_route.h>
#include <holo/planning/framework/fallback/event.h>
#include <holo/planning/framework/fallback/event_handle.h>
#include <holo/planning/framework/fallback/event_id.h>
#include <stack>

namespace holo
{
namespace planning
{
namespace fallback
{
/**
 * @brief      Class for event trigger.
 * @details    EventTrigger is a manager of the events and their handlers. We
 *             can raise an event everywhere using EventTrigger. But the events'
 *             handlers are called only once per loop.
 */
class EventTrigger
{
public:
    /**
     * @brief      Adds an event handle.
     *
     * @param[in]  id      The identifier
     * @param[in]  handle  The handle
     *
     * @return     True if success, False otherwise.
     */
    bool_t AddEventHandle(int32_t id, std::shared_ptr<EventHandle> handle);

    /**
     * @brief      Raise an event.
     *
     * @param[in]  e     Event.
     *
     * @return     True if success, False otherwise.
     */
    bool_t RaiseEvent(std::shared_ptr<Event> e);

    /**
     * @brief      Raise an event.
     *
     * @param[in]  id    The identifier number value.
     *
     * @return     True if success, False otherwise.
     */
    bool_t RaiseEvent(int32_t id);

    /**
     * @brief      Raise an event.
     *
     * @param[in]  id    The identifier number value.
     *
     * @return     True if success, False otherwise.
     */
    bool_t RaiseEvent(EventId::ID id);

    /**
     * @brief      Trigger the event handler.
     *
     * @param[in]  car_road_state  The car road state
     * @param      route           The route
     *
     * @return     True if success, False otherwise.
     */
    bool_t Trigger(const CarRoadState& car_road_state, PlanRoute& route);

    /**
     * @brief      Clear all event handlers and events.
     */
    void ClearHandler();

private:
    typedef std::vector<std::shared_ptr<EventHandle>> EventHandleContainer;

    /**
     * the event handlers
     */
    std::array<EventHandleContainer, static_cast<uint32_t>(EventId::ID::COUNT)> handles_;

    /**
     * the events
     */
    std::stack<std::shared_ptr<Event>> events_;

    DECLARE_SINGLETON(EventTrigger)
};

}  // namespace fallback
}  // namespace planning
}  // namespace holo

#endif
