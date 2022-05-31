/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file dp_rectangle_graph.h
 * @brief the header of the dp_rectangle_graph
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2020-05-14
 */

#ifndef _HOLO_PLANNING_PLANNER_DP_PATH_DP_RECTANGLE_GRAPH_H_
#define _HOLO_PLANNING_PLANNER_DP_PATH_DP_RECTANGLE_GRAPH_H_

#include <holo/log/hololog.h>
#include <vector>

#include <holo/core/types.h>

#include <holo/planning/common/graph_2d.h>

namespace holo
{
namespace planning
{
/**
 * @brief the graph for DP
 */
class DPRectangleGraph : public Graph2d
{
public:
    /**
     * @brief the constructor
     */
    DPRectangleGraph(float64_t x_start,
                     float64_t x_end,
                     float64_t y_start,
                     float64_t y_end,
                     float64_t x_step,
                     float64_t y_step)
      : Graph2d(x_start, x_end, y_start, y_end), x_step_(x_step), y_step_(y_step)
    {
        sampleNodes();
    }

public:
    /**
     * @brief Get the path by the 1st-axis's position
     *
     * @param x_pos The position of the 1st axis
     *
     * @return The path
     */
    std::vector<geometry::Point2d> GetPath(float64_t x_pos);

    /**
     * @brief Get the graph's X-size
     *
     * @return The X-size
     */
    uint32_t GetXSize() const;

    /**
     * @brief Get the graph's X-size
     *
     * @return The X-size
     */
    uint32_t GetYSize() const;

private:
    /**
     * @brief Sample the node's position
     */
    void sampleNodes();

private:
    float64_t x_step_;  ///< the step-length of 1st axis
    float64_t y_step_;  ///< the step-length of 2nd axis
};

}  // namespace planning
}  // namespace holo

#endif  //_HOLO_PLANNING_PLANNER_DP_PATH_DP_RECTANGLE_GRAPH_H_
