/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2019-08-29
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_FALLBACK_EVENT_ID_H_
#define _HOLO_PLANNING_FALLBACK_EVENT_ID_H_

#include <sstream>

namespace holo
{
namespace planning
{
namespace fallback
{
/**
 * @brief      Class for event identifier.
 * @details    This class is used to describe the event identifier.
 */
class EventId
{
public:
    /**
     * @brief      Class for id.
     */
    enum class ID
    {
        UNKNOWN    = 0,
        REVERSE_ID = 1,
        COUNT,
    };

    /**
     * @brief      Constructs the object.
     */
    EventId() : id_(ID::UNKNOWN)
    {
    }

    /**
     * @brief      Constructs the object.
     *
     * @param[in]  id    The identifier
     */
    EventId(ID id) : id_(id)
    {
    }

    /**
     * @brief      Constructs the object.
     *
     * @param[in]  id    The identifier
     */
    EventId(const int32_t& id) : id_(static_cast<ID>(id))
    {
    }

    /**
     * @brief      Get the number value from enum value
     *
     * @return     The identifier number value.
     */
    int32_t UnderLying() const
    {
        return static_cast<int32_t>(id_);
    }

    /**
     * @brief      Check the event identifier is the same.
     *
     * @param[in]  event_id  The event identifier
     *
     * @return     True if the event identifier is the same, False otherwise.
     */
    bool_t operator==(const EventId& event_id) const
    {
        return id_ == event_id.id_;
    }

    /**
     * @brief      Compare the event identifier.
     *
     * @param[in]  event_id  The event identifier
     *
     * @return     True if the this event identifier is less than comparison
     *             object, False otherwise.
     */
    bool_t operator<(const EventId& event_id) const
    {
        return id_ < event_id.id_;
    }

    /**
     * @brief      Get the description of this event.
     *
     * @return     The description of this event.
     */
    std::string String() const
    {
        switch (id_)
        {
            case ID::UNKNOWN:
            {
                return "unknown";
            }
            case ID::REVERSE_ID:
            {
                return "revised_id";
            }
            default:
                return "unknown";
        }
    }

private:
    /**
     * the identifier
     */
    ID id_;
};

}  // namespace fallback
}  // namespace planning
}  // namespace holo

#endif