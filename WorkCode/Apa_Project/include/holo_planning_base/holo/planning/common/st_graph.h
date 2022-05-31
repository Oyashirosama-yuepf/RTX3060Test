/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file st_graph.h
 * @brief the header of shift-time graph
 * @author wangchantong(wangchantong@holomatic.com)
 * @date 2020-09-07
 */
#ifndef _HOLO_PLANNING_COMMON_ST_GRAPH_H_
#define _HOLO_PLANNING_COMMON_ST_GRAPH_H_

#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <holo/core/types.h>

#include <holo/planning/common/box/normal_box.h>
#include <holo/planning/common/plan_route.h>
#include <holo/planning/common/st_boundary.h>

namespace holo
{
namespace planning
{
/**
 * @brief Struct for shift-time graph element, each obstacle indicate an element.
 */
struct StGraphElement
{
    using ObstacleList                 = std::vector<std::shared_ptr<ObstacleInfo>>;
    using Predicted_box_trajectory_ptr = std::shared_ptr<std::vector<NormalBox>>;

    StGraphElement(uint32_t const& id, std::vector<NormalBox> const& predicted_box_trajectory) : id_(id)
    {
        predict_trajectory_ = std::make_shared<std::vector<NormalBox>>(predicted_box_trajectory);
        is_static_          = false;
    }

    StGraphElement(uint32_t const& id, NormalBox const& bounding_box) : id_(id)
    {
        std::vector<NormalBox> temp = {bounding_box};
        predict_trajectory_         = std::make_shared<std::vector<NormalBox>>(std::move(temp));
        is_static_                  = true;
    }

    uint32_t                     id_;                  ///< obstacle id
    bool_t                       is_static_;           ///< true if obstacle is static
    Predicted_box_trajectory_ptr predict_trajectory_;  ///< the predicted trajectory of obstacle
};

/**
 * @brief Struct for shift-time graph.
 */
class StGraph
{
public:
    using ObstacleList                   = std::vector<std::shared_ptr<ObstacleInfo>>;
    using Predicted_boxes_trajectory_ptr = std::shared_ptr<std::vector<std::vector<NormalBox>>>;
    using Predicted_box_trajectory_ptr   = std::shared_ptr<std::vector<NormalBox>>;

    /**
     * @brief Construct the Shift-time point object.
     *
     * @param obstacles The obstacles which have already been transfered to Frenet.
     * @param predict_boxes_trajectory_ptr The pointer of obstacles' predicted normal box trajectory.
     * @param predict_time_interval The time interval of prediction.
     * @param time_range The maximum time horizon.
     */
    StGraph(ObstacleList const&                   obstacles,
            Predicted_boxes_trajectory_ptr const& predict_boxes_trajectory_ptr,
            float64_t const&                      init_time             = 0.0,
            float64_t const&                      predict_time_interval = 0.1,
            float64_t const&                      time_range            = 8.0);

    /**
     * @brief Get all obstacle shift-time boudaries.
     *
     * @param st_boundaries Vector of all obstacles' shift-time boundaries.
     *
     * @return true if getting boundaries successfully.
     */
    bool_t GetAllObstacleStBoundary(std::vector<StBoundary>& st_boundaries) const;

    /**
     * @brief Get a single obstacle shift-time boudaries.
     *
     * @param obs_id The identity number of obstacle.
     * @param st_boundary An obstacle shift-time boundaries.
     *
     * @return true if getting boundaries successfully.
     */
    bool_t GetObstacleStBoundary(uint32_t const& obs_id, StBoundary& st_boundary) const;

    /**
     * @brief Get all obstacles' block range (upper and lower bound) by giving specific time.
     *
     * @param time The specific time.
     * @param blocked_ranges Vector of pairs of range [lower_bound, upper_bound].
     *
     * @return true if getting blocked range successfully.
     */
    bool_t GetAllBlockedRangesByTime(float64_t const                               time,
                                     std::vector<std::pair<float64_t, float64_t>>& blocked_ranges) const;

    /**
     * @brief Get a single obstacle's block range (upper and lower bound) by giving specific time.
     *
     * @param time The specific time.
     * @param obs_id The identity number of obstacle.
     * @param blocked_range Pair of range [lower_bound, upper_bound].
     *
     * @return true if getting blocked range successfully.
     */
    bool_t GetBlockedRangeByTime(float64_t const                  time,
                                 uint32_t const&                  obs_id,
                                 std::pair<float64_t, float64_t>& blocked_range) const;

    /**
     * @brief Get initial time alligned with trajectory stitcher.
     *
     * @param init_time The initial time
     */
    void GetInitialTime(float64_t& init_time) const
    {
        init_time = init_time_;
    }

    /**
     * @brief Get obstacle's static mode.
     *
     * @param obs_id The identity number of obstacle.
     * @param is_static True if the obstacle is static.
     *
     * @return true if obtaining static mode successfully.
     */
    bool_t GetObstacleStaticMode(uint32_t obs_id, bool_t& is_static) const;

    /**
     * @brief Set obstacle's status.
     *
     * @param obs_id The identity number of obstacle.
     * @param status Obstacle status.
     *
     * @return true if setting successfully.
     */
    bool_t SetObstacleStatus(uint32_t obs_id, ObstableStatus status);

    /**
     * @brief Set obstacle's static mode.
     *
     * @param obs_id The identity number of obstacle.
     * @param is_static True if the obstacle is static.
     *
     * @return true if setting successfully.
     */
    bool_t SetObstacleStaticMode(uint32_t obs_id, bool_t is_static);

private:
    /**
     * @brief Calculate all obstacle shift-time boundaries.
     *
     * @param boundary_elements Vector of all obstacles' boundary elements.
     *
     * @return true if getting blocked range successfully.
     */
    void calculateAllObstacleStBoundary(std::vector<StGraphElement> const& boundary_elements);

    /**
     * @brief Calculate a single obstacle shift-time boundary.
     *
     * @param element The element used to build shift-time boundary.
     * @param boundary_elements An obstacle's boundary elements.
     *
     * @return true if calculate shift-time boundary successfully.
     */
    bool_t calculateObstacleStBoundary(StGraphElement const& element, StBoundary& st_boundary) const;

    /**
     * @brief Calculate static obstacle shift-time boundary.
     *
     * @param element The element used to build shift-time boundary.
     * @param boundary_elements An obstacle's boundary elements.
     *
     * @return true if calculate shift-time boundary successfully.
     */
    bool_t calculateStaticObstacleStBoundary(StGraphElement const& element, StBoundary& st_boundary) const;

    /**
     * @brief Calculate dynamic obstacle shift-time boundary.
     *
     * @param element The element used to build shift-time boundary.
     * @param boundary_elements An obstacle's boundary elements.
     *
     * @return true if calculate shift-time boundary successfully.
     */
    bool_t calculateDynamicObstacleStBoundary(StGraphElement const& element, StBoundary& st_boundary) const;

private:
    std::unordered_map<uint32_t, StBoundary> obs_st_boundary_;  ///< Obstacle Shift-Time boundary mapping

    float64_t const init_time_;              ///< Initial time allign with trajectory stitcher
    float64_t const predict_time_interval_;  ///< Time interval of prediction
    float64_t const time_range_;             ///< Time horizon of planning
};
}  // namespace planning
}  // namespace holo

#endif
