/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file dp_path.h
 * @brief the header of dp_path
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2020-06-02
 */

#ifndef _HOLO_PLANNING_PLANNER_DP_PATH_DP_PATH_H_
#define _HOLO_PLANNING_PLANNER_DP_PATH_DP_PATH_H_

#include <memory>
#include <vector>

#include <holo/core/types.h>
#include <holo/geometry/point2.h>

#include <holo/planning/common/grid_map_2d.h>
#include <holo/planning/math/curve/curve_1d.h>
#include <holo/planning/planner/dp_path/dp_rectangle_graph.h>
#include <holo/planning/planner/dp_path/dp_trajectory_cost_calculator.h>
#include <holo/planning/util/util.h>

namespace holo
{
namespace planning
{
/**
 * @brief dp_path generator
 */
class DPPath
{
public:
    DPPath() : is_valid_(false){};

    /**
     * @brief constructor
     *
     * @param grid_map the grid map built by outside
     * @param history_path the history path which is generated by planning_path of former loop
     * @param start_point the start position
     * @param end_point the end position
     * @param x_step the parameter used to construct the graph, means step length in x direction
     * @param y_step the parameter used to construct the graph, means step length in y direction
     * @param y_expand_length the parameter used to construct the graph, means expend-range in y direction
     * @param trajectory_cost_calculator the trajectory's cost-calculator pointer
     */
    DPPath(GridMap2d const&                                      grid_map,
           std::shared_ptr<std::vector<geometry::Point2d> const> history_path,
           geometry::Point2d const&                              start_point,
           geometry::Point2d const&                              end_point,
           float64_t                                             x_step,
           float64_t                                             y_step,
           float64_t                                             y_expand_length,
           std::shared_ptr<DPTrajectoryCostCalculator>           trajectory_cost_calculator);

    /**
     * @brief the getter of output path
     *
     * @param x_pos the x position of the path's end
     *
     * @return empty vector if not available, otherwise the output path in form of std::vector<geometry::Point2d>
     */
    std::vector<geometry::Point2d> GetPath(float64_t x_pos) const;

    /**
     * @brief judge if DPPath work successfully
     *
     * @return true if successful, false otherwise
     */
    bool_t IsValid() const
    {
        return is_valid_;
    }

private:
    std::shared_ptr<DPRectangleGraph>           graph_;                       ///< graph of sample points
    std::shared_ptr<DPTrajectoryCostCalculator> trajectory_cost_calculator_;  ///< trajectory's cost-calculator
    bool_t is_valid_;  ///< the flag of construct correctly (default construct is not correct)
};

}  // namespace planning
}  // namespace holo

#endif  // _HOLO_PLANNING_PLANNER_DP_PATH_DP_PATH_H_
