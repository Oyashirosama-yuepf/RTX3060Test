/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file park_velocity_planner.h
 * @brief the header of park velocity planner
 * @author huangnan(huangnan@holomatic.com)
 * @date 2021-12-11
 */

#ifndef _HOLO_PLANNING_PARK_VELOCITY_PLANNER
#define _HOLO_PLANNING_PARK_VELOCITY_PLANNER

#include <holo/common/path.h>
#include <holo/hpp/parkingplan/commonfunction.h>
#include <holo/planning/common/config/vehicle_config.h>

namespace holo
{
namespace planning
{
/**
 * @brief trapezoid velocity planner for a path with equal distance interval.
 *        the accelerate and decelerate are invariant.
 */
class ParkVelocityPlanner
{
public:
    /**
     * @brief Constructor
     */
    ParkVelocityPlanner();

    /**
     * @brief Set parameter
     *
     * @param[in] vehicle_cfg config to init accelerate and decelerate
     */
    void SetParam(config::VehicleConfig const& vehicle_cfg);

    /**
     * @brief Speed plan. If brake lates, the first point's velocity is not current_velocity
     *
     * @param[in] current_velocity Current velocity
     * @param[in] max_velocity Max velocity
     * @param[in] end_velocity End velocity, 0 if stop in the end
     * @param[in] input_path path input
     * @param[out] path common::Path to be traited
     *
     * @return True if plan successfully
     */
    bool Plan(float64_t                      current_velocity,
              float64_t                      max_velocity,
              float64_t                      end_velocity,
              std::vector<CurvePoint> const& input_path,
              common::Path&                  planned_path);

private:
    float64_t decelerate_;  ///< max decelerate
    float64_t accelerate_;  ///< max accelerate
    float64_t park_min_velocity_;
};
}  // namespace planning
}  // namespace holo
#endif