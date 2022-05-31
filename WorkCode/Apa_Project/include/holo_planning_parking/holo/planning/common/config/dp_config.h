/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file dp_config.h
 * @brief the header of config of dp planner
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2020-05-08
 */

#ifndef _HOLO_PLANNING_COMMON_CONFIG_DP_CONFIG_H_
#define _HOLO_PLANNING_COMMON_CONFIG_DP_CONFIG_H_

#include <holo/core/types.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace planning
{
namespace config
{
struct DpConfig
{
    bool use_obs_avoid;

    float64_t path_cost_l_quasi_softmax_l0;  ///< path lateral quasi softmax parameter
    float64_t path_cost_l_quasi_softmax_b;   ///< path lateral quasi softmax parameter
    float64_t path_cost_l_quasi_softmax_k;   ///< path lateral quasi softmax parameter
    float64_t path_cost_resolution;          ///< path resolution for calculating cost
    float64_t path_cost_l_cost;              ///< path l cost
    float64_t path_cost_his_l_cost;          ///< path his l cost
    float64_t path_cost_dl_cost;             ///< path dl cost
    float64_t path_cost_ddl_cost;            ///< path dl cost
    float64_t path_cost_endl_cost;           ///< path endl cost

    float64_t obstacle_collision_distance;   ///< paramter for calculating obstalce cost
    float64_t obstacle_collision_cost;       ///< obstalce cost
    float64_t obstacle_static_nudge_l;       ///< min lateral distance of obstacle
    float64_t obstacle_static_safe_l_dist;   ///< max lateral distance of obstacle to calculate cost
    float64_t obstacle_lateral_ignore_dist;  ///< max lateral distance of obstacle considered

    float64_t path_sample_start_l;  ///< min sample l
    float64_t path_sample_end_l;    ///< max sample l
    float64_t path_sample_l_step;   ///< interval of l sampled
    float64_t path_level_step;      ///< interval of s sampled

    float64_t start_x_margin;       ///< the longitudinal swell margin behind ego during collision check
    float64_t end_x_margin;         ///< the longitudinal swell margin in front of ego during collision check
    float64_t start_y_margin;       ///< the latitude swell margin in right of ego during collision check
    float64_t end_y_margin;         ///< the latitude swell margin in left of ego during collision check
};

bool ParseDpConfig(const yaml::Node& node, DpConfig& cfg);

}  // namespace config
}  // namespace planning
}  // namespace holo

#endif