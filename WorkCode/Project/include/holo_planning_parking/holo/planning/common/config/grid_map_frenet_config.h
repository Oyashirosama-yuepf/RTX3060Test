/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file grid_map_frenet_config.h
 * @brief the header of config of grid map in fetnet
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2020-04-27
 */

#ifndef _HOLO_PLANNING_CONFIG_GRID_MAP_FRENET_CONFIG_H_
#define _HOLO_PLANNING_CONFIG_GRID_MAP_FRENET_CONFIG_H_

#include <holo/core/types.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace planning
{
namespace config
{
struct GridMapFrenetConfig
{
    float32_t grid_map_s_interval;
    float32_t grid_map_l_interval;
    float32_t grid_map_l_min;
    float32_t grid_map_l_max;
    float32_t grid_map_update_distance;
};

bool ParseGridMapFrenetConfig(yaml::Node const& node, GridMapFrenetConfig& cfg);
}  // namespace config
}  // namespace planning
}  // namespace holo

#endif