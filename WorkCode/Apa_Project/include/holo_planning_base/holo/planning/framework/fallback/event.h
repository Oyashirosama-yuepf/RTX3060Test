/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2019-08-29
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_FALLBACK_EVENT_H_
#define _HOLO_PLANNING_FALLBACK_EVENT_H_

#include <holo/planning/common/headers.h>
#include <holo/planning/framework/fallback/event_id.h>

namespace holo
{
namespace planning
{
namespace fallback
{
/**
 * @brief      Class for event.
 * @details    When an error occurs, we raise an event.
 */
class Event
{
public:
    /**
     * @brief      Constructs the object.
     *
     * @param[in]  id    The identifier
     */
    Event(uint32_t id);

    /**
     * @brief      Constructs the object.
     *
     * @param[in]  id    The identifier
     */
    Event(EventId id);

    /**
     * @brief      Constructs the object.
     *
     * @param[in]  id    The identifier
     * @param[in]  info  The information
     */
    Event(uint32_t id, const std::string& info);

    /**
     * @brief      Constructs the object.
     *
     * @param[in]  id    The identifier
     * @param[in]  info  The information
     */
    Event(EventId id, const std::string& info);

    /**
     * @brief      Destroys the object.
     */
    ~Event();

    /**
     * @brief      Gets the identifier.
     *
     * @return     The identifier.
     */
    EventId GetId() const;

    /**
     * @brief      Get the explanatory string.
     *
     * @return     The explanatory string.
     */
    std::string What() const;

private:
    /**
     * the identifier
     */
    EventId id_;

    /**
     * the explanatory string
     */
    std::string info_;
};

}  // namespace fallback
}  // namespace planning
}  // namespace holo

#endif