/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file curve_1d_generator.h
 * @brief the header of the 1d curve generator in lattice
 * @author zhangyuchen(zhangyuchen@holomatic.com)
 * @date 2019-12-25
 */

#ifndef _HOLO_PLANNING_LATTICE_CURVE_1D_GENERATOR_H_
#define _HOLO_PLANNING_LATTICE_CURVE_1D_GENERATOR_H_

#include <holo/core/types.h>

#include <holo/planning/math/curve/curve_1d.h>
#include <holo/planning/planner/lattice/end_condition_sampler.h>

namespace holo
{
namespace planning
{
namespace lattice
{
/**
 * @brief Class for generate curve set for longitudinal and lateral respectively
 */
class Curve1dGenerator
{
public:
    using ObstacleList                   = std::vector<std::shared_ptr<ObstacleInfo>>;
    using Curve1dSet                     = std::vector<std::shared_ptr<math::Curve1d>>;
    using State                          = std::array<float64_t, 3>;
    using Condition                      = std::pair<State, float64_t>;
    using predicted_boxes_trajectory_ptr = std::shared_ptr<std::vector<std::vector<NormalBox>>>;
    using ConstraintPtr                  = std::shared_ptr<LatticeConstraint>;
    /**
     * @brief Construct a new Curve 1d Generator object
     *
     * @param init_lon_state initial longitudinal frenet state
     * @param init_lat_state initial lateral frenet state
     * @param boxes_trajectory_ptr pointer of predicted obstacles trajectory boxs
     * @param constraint_ptr pointer of constraint
     * @param enable_avoid_in_lane the switch of avoid in lane
     */
    Curve1dGenerator(const State&                          init_lon_state,
                     const State&                          init_lat_state,
                     const predicted_boxes_trajectory_ptr& boxes_trajectory_ptr,
                     const ConstraintPtr&                  constraint_ptr,
                     bool_t                                enable_avoid_in_lane);

    /**
     * @brief Destroy the Curve 1d Generator object
     */
    ~Curve1dGenerator() = default;

    /**
     * @brief generate longitudinal and lateral curve sets
     *
     * @param obs_list obstacle pointer list
     * @param target_speed reference longitudinal speed
     * @param target_s distance to target point, [0.0 - 500.0] is valid value, other values mean no target point
     * @param road_width road width
     * @param headway_time headway time
     * @param ego_box ego car box
     * @param lon_curve_set set to save longitudinal curves
     * @param lat_curve_set set to save lateral curves
     */
    void GenerateCurveSet(ObstacleList const& obs_list,
                          float64_t           target_speed,
                          float64_t           target_s,
                          float64_t           road_width,
                          float64_t           headway_time,
                          NormalBox const&    ego_box,
                          Curve1dSet&         lon_curve_set,
                          Curve1dSet&         lat_curve_set) const;

private:
    /**
     * @brief generate longitudinal curve set
     *
     * @param obs_list obstacle pointer list
     * @param target_speed reference longitudinal speed
     * @param target_s distance to target point, [0.0 - 500.0] is valid value, other values mean no target point
     * @param headway_time headway time
     * @param ego_box ego car box
     * @param lon_curve_set set to save longitudinal curves
     *
     */
    void GenerateLonCurveSet(const ObstacleList& obs_list,
                             float64_t           target_speed,
                             float64_t           target_s,
                             float64_t           headway_time,
                             NormalBox const&    ego_box,
                             Curve1dSet&         lon_curve_set) const;

    /**
     * @brief generate lateral curve set
     *
     * @param lon_curve_set set to save lateral curves
     * @param road_width road width
     * @param vehicle_width ego car width
     */
    void GenerateLatCurveSet(Curve1dSet& lon_curve_set, float64_t road_width, float64_t vehicle_width) const;

    /**
     * @brief initial longitudinal frenet state
     */
    State init_lon_state_;

    /**
     * @brief initial lateral frenet state
     */
    State init_lat_state_;

    /**
     * @brief object to sample longitudinal and lateral frenet end conditions
     */
    EndConditionSampler end_condition_sampler_;
};

}  // namespace lattice
}  // namespace planning
}  // namespace holo

#endif