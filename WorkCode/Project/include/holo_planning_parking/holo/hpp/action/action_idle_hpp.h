/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file action_idle_hpp.h
 * @brief the header of action idle of hpp
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2019-09-20
 */

#ifndef _ACTION_IDLE_HPP_H_
#define _ACTION_IDLE_HPP_H_

#include <holo/hpp/action/action.h>

namespace holo
{
namespace planning
{
/**
 * @brief Class for action idle.
 *
 * @details ActionIdleHpp is used to descirbe vehicle in idle state.
 */
class ActionIdleHpp : public Action
{
public:
    /**
     * @brief Constructor.
     */
    ActionIdleHpp();

    /**
     * @brief Destroys the object.
     */
    virtual ~ActionIdleHpp();

    /**
     * @brief Check the action status.
     *
     * @param car_road_state The car road state
     * @param route The plan route
     *
     * @return True if action is changed in check(), False otherwise.
     */
    virtual bool Check(const HppCarRoadState& hpp_car_road_state, PlanRoute& route);

    /**
     * @brief Perform the action.
     *
     * @param[in]  car_road_state The car road state
     * @param[out] route The route
     *
     * @return True if action is executed successfully. False otherwise.
     */
    virtual bool Perform(const HppCarRoadState& hpp_car_road_state, PlanRoute& route);

private:
    float64_t smooth_step_;
    float64_t dynamic_path_length_;
};

}  // namespace planning
}  // namespace holo

#endif