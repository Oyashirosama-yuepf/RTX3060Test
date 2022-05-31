/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file action_manager_hpp.h
 * @brief the header of action manager of hpp
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2019-09-20
 */

#ifndef _HOLO_PLANNING_ACTION_MANAGER_HPP_H_
#define _HOLO_PLANNING_ACTION_MANAGER_HPP_H_

#include <holo/hpp/action/action_manager.h>

namespace holo
{
namespace planning
{
/**
 * @brief      Class for action manager.
 * @details    ActionManager is action manager, which store actions and check
 *             the action changing validity.
 */
class ActionManagerHpp : public ActionManager
{
public:
    enum ActionState
    {
        IDLE,
        PATH_FOLLOW,
        VERTICLE_PARKIN,
    };

private:
    DECLARE_SINGLETON(ActionManagerHpp)
};

}  // namespace planning
}  // namespace holo

#endif