/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file graph_2d.h
 * @brief the header of the graph_2d
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2020-05-14
 */

#ifndef _HOLO_PLANNING_COMMON_GRAPH_2D_H_
#define _HOLO_PLANNING_COMMON_GRAPH_2D_H_

#include <assert.h>
#include <vector>

#include <holo/core/types.h>
#include <holo/geometry/point2.h>

#include <holo/planning/common/comparable_cost.h>
#include <holo/planning/common/constant.h>

namespace holo
{
namespace planning
{
/**
 * @brief the node in Graph2d
 */
class Node2d
{
public:
    Node2d() : min_cost_prev_node_(nullptr), min_cost_(true, true, true, MAX_DOUBLE, MAX_DOUBLE)
    {
    }

    Node2d(float64_t x, float64_t y)
      : pos_(x, y), min_cost_prev_node_(nullptr), min_cost_(true, true, true, MAX_DOUBLE, MAX_DOUBLE)
    {
    }

public:
    geometry::Point2d const& GetPosition() const
    {
        return pos_;
    }

    void SetPosition(float64_t x, float64_t y)
    {
        pos_.Set(x, y);
    }

    void SetPosition(geometry::Point2d const& pos)
    {
        pos_ = pos;
    }

    std::shared_ptr<const Node2d> GetPreNode() const
    {
        return min_cost_prev_node_;
    }

    void SetPreNode(std::shared_ptr<const Node2d> pre_node)
    {
        assert(pre_node != nullptr);

        min_cost_prev_node_ = pre_node;
    }

    ComparableCost const& GetCost() const
    {
        return min_cost_;
    }

    void SetCost(ComparableCost const& cost)
    {
        min_cost_ = cost;
    }

    void SetSmoothnessCost(float64_t input_smoothness_cost) noexcept
    {
        min_cost_.SetSmoothnessCost(input_smoothness_cost);
    }

    void SetSafetyCost(float64_t input_safety_cost) noexcept
    {
        min_cost_.SetSafetyCost(input_safety_cost);
    }

    void SetCollisionFlag(bool_t is_collision) noexcept
    {
        min_cost_.SetCollisionFlag(is_collision);
    }

    void SetOutOfBoundaryFlag(bool_t is_out_of_boundary) noexcept
    {
        min_cost_.SetOutOfBoundaryFlag(is_out_of_boundary);
    }

    void SetOutOfLaneFlag(bool_t is_out_of_lane) noexcept
    {
        min_cost_.SetOutOfLaneFlag(is_out_of_lane);
    }

private:
    geometry::Point2d             pos_;                 ///< position of the node
    std::shared_ptr<const Node2d> min_cost_prev_node_;  ///< the pointer to the previous-layer node which is min cost
    ComparableCost                min_cost_;            ///< the min cost
};

/**
 * @brief the Graph2d, a base class
 */
class Graph2d
{
public:
    /**
     * @brief the default constructor
     */
    Graph2d() = default;

    /**
     * @brief the constructor
     */
    Graph2d(float64_t x_start, float64_t x_end, float64_t y_start, float64_t y_end)
      : x_start_(x_start), x_end_(x_end), y_start_(y_start), y_end_(y_end)
    {
    }

public:
    /**
     * @brief Get the node by the it's index
     *
     * @param x_index The node's index of 1st axis
     * @param y_index The node's index of 2nd axis
     *
     * @return The node
     */
    virtual std::shared_ptr<Node2d> GetNode(uint32_t x_index, uint32_t y_index)
    {
        assert(node_list_[x_index][y_index] != nullptr);

        return node_list_[x_index][y_index];
    }

    /**
     * @brief Get the path by the node's index
     *
     * @param x_index The node's index of 1st axis
     * @param y_index The node's index of 2nd axis
     *
     * @return The path in the format of a vector of geometry::Point2d
     */
    std::vector<geometry::Point2d> GetPath(uint32_t x_index, uint32_t y_index)
    {
        assert(x_index < node_list_.size());
        assert(y_index < node_list_[x_index].size());

        std::shared_ptr<const Node2d> temp_node = node_list_[x_index][y_index];

        assert(temp_node != nullptr);

        std::vector<geometry::Point2d> ret_path;
        ret_path.resize(x_index + 1);
        while (temp_node->GetPreNode())
        {
            geometry::Point2d temp_pos = temp_node->GetPosition();
            ret_path[x_index]          = temp_pos;
            temp_node                  = temp_node->GetPreNode();
            --x_index;
        }

        geometry::Point2d temp_pos = temp_node->GetPosition();
        ret_path[x_index]          = temp_pos;

        assert(x_index == 0);

        return ret_path;
    }

protected:
    float64_t x_start_;  ///< the graph's area, 1st-axis's start position
    float64_t x_end_;    ///< the graph's area, 1st-axis's end position
    float64_t y_start_;  ///< the graph's area, 2nd-axis's start position
    float64_t y_end_;    ///< the graph's area, 2nd-axis's start position

    std::vector<std::vector<std::shared_ptr<Node2d> > > node_list_;  ///< the nodes' table of the graph
};

}  // namespace planning
}  // namespace holo

#endif  //_HOLO_PLANNING_COMMON_GRAPH_2D_H_
