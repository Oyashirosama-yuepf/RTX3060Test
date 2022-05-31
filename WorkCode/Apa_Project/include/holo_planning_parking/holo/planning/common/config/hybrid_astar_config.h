/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hybrid_astar_config.h
 * @brief the header of config of hybrid astar config
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2021-01-13
 */

#ifndef _HOLO_PLANNING_CONFIG_HYBRID_ASTAR_CONFIG_H_
#define _HOLO_PLANNING_CONFIG_HYBRID_ASTAR_CONFIG_H_

#include <holo/core/types.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace planning
{
namespace config
{
struct HybridAstarConfig
{
    float64_t xy_grid_resolution;
    float64_t phi_grid_resolution;
    float64_t min_safety_distance;
    float64_t max_front_wheel_angle;
    float64_t step_size;
    float64_t delta_t;
    size_t    next_node_num;

    float64_t traj_forward_penalty;
    float64_t traj_back_penalty;
    float64_t traj_gear_switch_penalty;
    float64_t traj_steer_penalty;
    float64_t traj_steer_change_penalty;
    float64_t heu_rs_forward_penalty;
    float64_t heu_rs_back_penalty;
    float64_t heu_rs_gear_switch_penalty;
    float64_t heu_rs_steer_penalty;
    float64_t heu_rs_steer_change_penalty;
};

bool ParseHybridAstarConfig(yaml::Node const& node, HybridAstarConfig& cfg);
}  // namespace config
}  // namespace planning
}  // namespace holo

#endif