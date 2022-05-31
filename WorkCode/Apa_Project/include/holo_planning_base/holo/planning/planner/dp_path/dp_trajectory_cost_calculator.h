/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file dp_trajectory_cost_calculator.h
 * @brief the header of trajectory_cost_calculator
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2020-06-01
 */

#ifndef _HOLO_PLANNING_PLANNER_DP_PATH_DP_TRAJECTORY_COST_CALCULATOR_H_
#define _HOLO_PLANNING_PLANNER_DP_PATH_DP_TRAJECTORY_COST_CALCULATOR_H_

#include <holo/core/types.h>

#include <holo/planning/common/comparable_cost.h>
#include <holo/planning/common/grid_map_2d.h>
#include <holo/planning/common/park_param.h>  //todo:delete
#include <holo/planning/math/curve/quintic_polynomial_curve_1d.h>

namespace holo
{
namespace planning
{
/**
 * @brief The calculator for computing the cost of a trajectory which is in form of QuinticPolynomialCurve1d.
 */
class DPTrajectoryCostCalculator
{
public:
    /**
     * @brief normal constructor
     */
    DPTrajectoryCostCalculator(float64_t start_x_margin,
                               float64_t end_x_margin,
                               float64_t start_y_margin,
                               float64_t end_y_margin)
      : start_x_margin_(start_x_margin)
      , end_x_margin_(end_x_margin)
      , start_y_margin_(start_y_margin)
      , end_y_margin_(end_y_margin){};

    /**
     * @brief Calculate the cost of a trajectory
     *
     * @param curve The trajectory
     * @param history_path The history path
     * @param grid_map The grid map
     * @param start_x The start-state's x value
     * @param end_x The end-state's x value
     * @param curr_level The current level
     * @param total_level The total level
     *
     * @return The cost of the trajectory
     */
    ComparableCost Calculate(std::shared_ptr<math::Curve1d const> curve,
                             std::shared_ptr<math::Curve1d const> history_path,
                             GridMap2d const&                     grid_map,
                             float64_t                            start_x,
                             float64_t                            end_x,
                             uint32_t                             curr_level,
                             uint32_t                             total_level);

private:
    /**
     * @brief calculate the sum cost of the history_path and smoothness cost
     *
     * @param curve The trajectory
     * @param start_x The start-state's x value
     * @param end_x The end-state's x value
     * @param is_curr_level_equals_total_level True if the current level is equal to the total level, false otherwise
     *
     * @return The sum cost of the history_path and smoothness cost
     */
    ComparableCost calcSmoothCost(std::shared_ptr<math::Curve1d const> curve,
                                  std::shared_ptr<math::Curve1d const> history_path,
                                  float64_t                            start_x,
                                  float64_t                            end_x,
                                  bool_t                               is_curr_level_equals_total_level);

    /**
     * @brief calculate a single trajectory-point's safety cost by using grid map
     *
     * @param position_x The x-coordinate of the position to calculate the safety cost by using grid map
     * @param position_y The y-coordinate of the position to calculate the safety cost by using grid map
     *
     * @return The single trajectory-point's safety cost by using grid map
     */
    ComparableCost calcSinglePointSafetyCost(float64_t position_x, float64_t position_y, GridMap2d const& grid_map);

    /**
     * @brief calculate the whole trajectory's safety cost by using grid map
     *
     * @param curve The trajectory
     * @param start_x The x-value of the start-position to calculate the whole trajectory's safety cost
     * @param end_x The x-value of the end-position to calculate the whole trajectory's safety cost
     *
     * @return The single trajectory-point's safety cost by using grid map
     */
    ComparableCost calcSafetyCost(std::shared_ptr<math::Curve1d const> curve,
                                  float64_t                            start_x,
                                  float64_t                            end_x,
                                  GridMap2d const&                     grid_map);

private:
    float64_t start_x_margin_ = -3.0;  ///< the longitudinal swell margin behind ego during collision check//todo
    float64_t end_x_margin_   = 5.0;   ///< the longitudinal swell margin in front of ego during collision check//todo
    /// the latitude swell margin in right of ego during collision check
    float64_t start_y_margin_ = -ParkParam::Instance().dp_path_cost_lateral_ignore_dist;
    /// the latitude swell margin in left of ego during collision check
    float64_t end_y_margin_ = ParkParam::Instance().dp_path_cost_lateral_ignore_dist;
};

}  // namespace planning
}  // namespace holo

#endif  // _HOLO_PLANNING_PLANNER_DP_PATH_DP_TRAJECTORY_COST_CALCULATOR_H_
