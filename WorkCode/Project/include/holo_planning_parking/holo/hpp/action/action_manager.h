/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2018-01-18
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_ACTION_MANAGER_H_
#define _HOLO_PLANNING_ACTION_MANAGER_H_

#include <map>
#include <set>

#include <holo/core/types.h>
#include <holo/hpp/action/action.h>

namespace holo
{
namespace planning
{
/**
 * @brief      Class for action manager.
 * @details    ActionManager is action manager, which store actions and check
 *             the action changing validity.
 */
class ActionManager
{
public:
    /**
     * @brief      action type enum
     */
    enum ACTION
    {
        UNKNOWN = -1,
    };

    /**
     * @brief      Change action.
     *
     * @param[in]  action  The action
     *
     * @return     True if successfully, False otherwise.
     */
    bool ChangeAction(uint32_t action);

    uint32_t GetCurrentActionValue() const
    {
        return curr_action_;
    }

    /**
     * @brief      Gets the current action.
     *
     * @return     The current action.
     */
    std::shared_ptr<Action> GetCurrentAction();

protected:
    ActionManager();
    virtual ~ActionManager();

    /**
     * current action index
     */
    uint32_t curr_action_;

    /**
     * actions changing edge
     */
    std::set<std::pair<uint32_t, uint32_t>> edges_;

    /**
     * actions container
     */
    std::map<uint32_t, std::shared_ptr<Action>> actions_;
};

}  // namespace planning
}  // namespace holo

#endif