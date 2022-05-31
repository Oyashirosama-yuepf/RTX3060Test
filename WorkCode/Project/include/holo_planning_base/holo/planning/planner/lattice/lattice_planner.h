/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lattice_planner.h
 * @brief the header of lattice planner
 * @author zhangyuchen(zhangyuchen@holomatic.com)
 * @date 2019-12-25
 */

#ifndef _HOLO_PLANNING_LATTICE_PLANNER_H_
#define _HOLO_PLANNING_LATTICE_PLANNER_H_

#include <holo/core/types.h>

#include <holo/planning/common/box/normal_box.h>
#include <holo/planning/common/car_road_state.h>
#include <holo/planning/common/plan_route.h>
#include <holo/planning/planner/lattice/constraint_checker.h>

namespace holo
{
namespace planning
{
namespace lattice
{
/**
 * @brief data needed by lattice planner
 */
struct LatticeFrame
{
    LatticeConstraint            constraint;
    float64_t                    linear_speed;
    float64_t                    linear_acc;
    float64_t                    vheading;
    float64_t                    road_width           = 3.75;
    float64_t                    target_speed         = 120.0;
    float64_t                    target_s             = 1000.0;
    float64_t                    headway_time         = 1.9;
    bool_t                       enable_avoid_in_lane = true;
    common::PathPoint            init_planning_pt;
    float64_t                    init_time = 0.0;
    std::unordered_set<uint32_t> cut_in_obs_ids;
};

/**
 * @brief Class for Lattice Planner
 */
class LatticePlanner
{
public:
    using ObstacleList = std::vector<std::shared_ptr<ObstacleInfo>>;
    /**
     * @brief Construct a new Lattice Planner object
     */
    LatticePlanner() = default;

    /**
     * @brief Destroy the Lattice Planner object
     */
    ~LatticePlanner() = default;

    /**
     * @brief plan and generate path
     *
     * @param obs_list obstacle pointer list
     * @param ref_path reference path
     * @param data some data needed by lattce planner
     * @param ego_box ego car 2d box
     * @param path save generated path
     *
     * @return bool_t true if plan successfully, false otherwise
     */
    virtual bool_t Plan(const ObstacleList&            obs_list,
                        const std::vector<CurvePoint>& ref_path,
                        const LatticeFrame&            data,
                        NormalBox&                     ego_box,
                        common::Path&                  path) const;
};

}  // namespace lattice
}  // namespace planning
}  // namespace holo

#endif