/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hpp_config.h
 * @brief the header of config of hpp
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2020-04-27
 */

#ifndef _HOLO_HPP_HPP_CONFIG_H_
#define _HOLO_HPP_HPP_CONFIG_H_

#include <holo/planning/common/config/dp_config.h>
#include <holo/planning/common/config/grid_map_frenet_config.h>
#include <holo/planning/common/config/hybrid_astar_config.h>
#include <holo/planning/common/config/vehicle_config.h>
#include <holo/planning/common/headers.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace planning
{
namespace config
{
struct HppConfig
{
    VehicleConfig       vehicle_cfg;          ///< vehicle size and spec
    GridMapFrenetConfig grid_map_frenet_cfg;  ///< grid map spec
    DpConfig            dp_cfg;               ///< dp planner spec
    HybridAstarConfig   hybrid_astar_cfg;     ///< hybrid astar planner spec
};

class HppConfigHelper
{
public:
    /**
     * @brief Get hpp config
     */
    static HppConfig const& GetHppCfg();

    /**
     * @brief Parse config
     *
     * @param node Node of yaml
     *
     * @return True if parse config successfully
     */
    static bool ParseHppConfig(yaml::Node const& node, yaml::Node const& vehicle_node);

private:
    static HppConfig cfg_;  ///< config data
};

}  // namespace config
}  // namespace planning
}  // namespace holo

#endif
