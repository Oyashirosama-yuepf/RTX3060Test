/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_boundary.h
 * @brief the header of road boundary in frenet
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2020-04-30
 */

#ifndef _HOLO_PLANNING_COMMON_ROAD_BOUNDARY_H_
#define _HOLO_PLANNING_COMMON_ROAD_BOUNDARY_H_

#include <holo/planning/common/config/vehicle_config.h>
#include <holo/planning/common/headers.h>

#include <vector>

namespace holo
{
namespace planning
{
/**
 * @brief Class of one road boundary in frenet
 */
class RoadBoundary
{
public:
    /**
     * @brief Constructor
     *
     * @param s_evaluated The values of evaluated s
     * @param boundary_min Boundary min of l
     * @param boundary_max Boundary max of l
     * @param vehicle_cfg Vehicle config
     */
    RoadBoundary(std::vector<float64_t>&      s_evaluated,
                 std::vector<float64_t>&      boundary_min,
                 std::vector<float64_t>&      boundary_max,
                 config::VehicleConfig const& vehicle_cfg);

    /**
     * @brief Destructor
     */
    ~RoadBoundary() = default;

    /**
     * @brief Get boundary of s
     *
     * @param[in]   s The s value
     * @param[out]  min Min l value of boundary of s
     * @param[out]  max Max l value of boundary of s
     */
    void GetBoundaryPoint(float64_t s, float64_t& min, float64_t& max) const;

    /**
     * @brief Get boundary of s of a box vehicle
     *
     * @param[in]   s The s value
     * @param[out]  min Min l value of boundary of s
     * @param[out]  max Max l value of boundary of s
     */
    void GetVehicleBoundaryPoint(float64_t s, float64_t& min, float64_t& max) const;

private:
    /**
     * @brief Return 0.0 for min and max
     *
     * @param min Min l value of boundary of s
     * @param max Max l value of boundary of s
     */
    static void NoAvailableArea(float64_t& min, float64_t& max);

private:
    /**
     * @brief S evaluated
     */
    std::vector<float64_t> s_evaluated_;

    /**
     * @brief Boundary min of l
     */
    std::vector<float64_t> boundary_min_;

    /**
     * @brief Boundary max of l
     */
    std::vector<float64_t> boundary_max_;

    /**
     * @brief Front edge to center
     */
    float64_t vehicle_front_edge_to_center_;

    /**
     * @brief Back edge to center
     */
    float64_t vehicle_back_edge_to_center_;

    /**
     * @brief Side edge to center
     */
    float64_t vehicle_side_edge_to_center_;
};
}  // namespace planning
}  // namespace holo

#endif
