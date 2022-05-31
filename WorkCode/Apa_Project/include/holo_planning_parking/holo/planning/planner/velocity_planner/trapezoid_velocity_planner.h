/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file trapezoid_velocity_planner.h
 * @brief the header of trapezoid velocity planner
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2019-12-13
 */

#ifndef _HOLO_PLANNING_PLANNER_TRAPEZOID_VELOCITY_PLANNER
#define _HOLO_PLANNING_PLANNER_TRAPEZOID_VELOCITY_PLANNER

#include <holo/common/path.h>
#include <holo/planning/common/config/vehicle_config.h>

namespace holo
{
namespace planning
{
/**
 * @brief trapezoid velocity planner for a path with equal distance interval.
 *        the accelerate and decelerate are invariant.
 */
class TrapezoidVelocityPlanner
{
public:
    /**
     * @brief Constructor
     */
    TrapezoidVelocityPlanner();

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
     * @param[in] end_distance End point s value
     * @param[out] path common::Path to be traited
     * @param[in] path_step common::Path step
     *
     * @return True if plan successfully
     */
    bool Plan(float64_t     current_velocity,
              float64_t     max_velocity,
              float64_t     end_velocity,
              float64_t     end_distance,
              common::Path& path,
              float64_t     path_step);

    /**
     * @brief Speed plan. If brake lates, the first point's velocity is not current_velocity
     *
     * @param[in] current_v Current velocity
     * @param[in] desire_v Desired velocity
     * @param[in] max_v Max velocity
     * @param[out] speed_plan_list The vector to store planned velocity
     * @param[in] end_distance End point s value
     * @param[in] current_idx Current path indx
     * @param[in] path_step Path step
     *
     * @return True if plan successfully
     */
    bool Plan(const float64_t         current_v,
              const float64_t         desire_v,
              const float64_t         max_v,
              std::vector<float64_t>& speed_plan_list,
              const float64_t         end_distance,
              const size_t            current_idx,
              const float64_t         path_step);

private:
    float64_t decelerate_;  ///< max decelerate
    float64_t accelerate_;  ///< max accelerate
};
}  // namespace planning
}  // namespace holo
#endif