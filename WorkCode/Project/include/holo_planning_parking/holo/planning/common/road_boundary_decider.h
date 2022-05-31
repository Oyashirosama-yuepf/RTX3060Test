/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_boundaries_decider.h
 * @brief the header of road boundary decider
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2020-03-30
 */

#ifndef _HOLO_PLANNING_COMMON_ROAD_BOUNDARY_DECIDER_H_
#define _HOLO_PLANNING_COMMON_ROAD_BOUNDARY_DECIDER_H_

#include <holo/planning/common/grid_map_frenet.h>
#include <holo/planning/common/road_boundary.h>

namespace holo
{
namespace planning
{
/**
 * @brief Class to decide road boundaries according to grid map frenet
 */
class RoadBoundaryDecider
{
public:
    /**
     * @brief Contruct the road boundary decider
     *
     * @param grid_map Grid map in frenet
     * @param vehicle_cfg Vehicle config
     */
    RoadBoundaryDecider(GridMapFrenet const& grid_map, config::VehicleConfig const& vehicle_cfg);

    /**
     * @brief Destroy the road boundary decider
     */
    virtual ~RoadBoundaryDecider() = default;

    /**
     * @brief Decide road boundary
     *
     * @param[in]  s_start From which s the boundary is active
     * @param[in]  s_end To which s the boundary is active
     * @param[in]  length The length of output boundaries
     * @param[in]  left_buffer Left shrink buffer
     * @param[in]  right_buffer Right shrink buffer
     * @param[out] road_boundaries The result of several road boundaries
     *
     * @return True if process successfully
     */
    bool Process(float64_t                  s_start,
                 float64_t                  s_end,
                 float64_t                  length,
                 float64_t                  left_buffer,
                 float64_t                  right_buffer,
                 std::vector<RoadBoundary>& road_boundaries);

private:
    /**
     * @brief Update current level road boundary
     *
     * @param[in] sample_s The s value to be updated
     * @param[in] l_min The min lower bound of l
     * @param[in] l_max The max upper bound of l
     * @param[out] l_start The lower bound of l of current s
     * @param[out] l_end The upper bound of l of current s
     */
    void UpdateRoadBoundary(float64_t const sample_s,
                            float64_t const l_min,
                            float64_t const l_max,
                            float64_t&      l_start,
                            float64_t&      l_end);

private:
    /**
     * @brief Grid map
     */
    GridMapFrenet const& grid_map_;

    /**
     * @brief Vehicle config
     */
    config::VehicleConfig const& vehicle_cfg_;

    /**
     * @brief Min l
     */
    float64_t l_min_ = -3.5;

    /**
     * @brief Max l
     */
    float64_t l_max_ = 3.5;

    /**
     * @brief Sample s inteval
     */
    float64_t s_interval_ = 0.5;

    /**
     * @brief Sample l inteval
     */
    float64_t l_interval_ = 0.2;
};
}  // namespace planning
}  // namespace holo

#endif