/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file planning_state.h
 * @brief planning state
 * @author yansenwei(yansenwei@holomatic.com)
 * @date 2021-05-31
 */

#ifndef _HOLO_PLANNING_PLANNING_STATE_H_
#define _HOLO_PLANNING_PLANNING_STATE_H_

namespace holo
{
namespace planning
{
// enum class HPAPlanningState
// {
//     STANDBY = 0,
//     ACTIVE,
//     INTERRUPT,
//     SUCCEED,
//     FAILED,
//     COMPLETED,
//     OBSTACLE_STOPPING,
//     OBSTACLE_AVOID,
// };
struct HPAPlanningState
{
    enum class PlanState : uint8_t
    {
        STANDBY = 0,
        ACTIVE,
        INTERRUPT,
        SUCCEED,
        FAILED,
        COMPLETED,
        OBSTACLE_STOPPING,
        OBSTACLE_AVOID,
    } planning_state;
    enum class SceneState : uint8_t
    {
        DEFAULT = 0,
        CROSS_ROAD,
        TURN_RIGHT,
        TURN_LEFT,
    } scene_state;
};
enum class PathProcessState
{
    STANDBY = 0,
    ACTIVE,
    SUCCEED,
    FAILED,
};

}  // namespace planning
}  // namespace holo

#endif
