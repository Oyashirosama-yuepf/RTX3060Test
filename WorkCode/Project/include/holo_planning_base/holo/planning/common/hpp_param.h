/*!
 *  \brief
 *  \author zhangchun (zhangchun@holomatic.com)
 *  \date 2 Nov, 2019
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */
#ifndef _HOLO_PLANNING_HPP_PARAM_H_
#define _HOLO_PLANNING_HPP_PARAM_H_

#include <holo/core/types.h>
#include <math.h>
#include <stddef.h>
#include <string>

namespace holo
{
namespace planning
{
class HppParam
{
public:
    static HppParam& Instance()
    {
        static HppParam instance;
        return instance;
    }

private:
    HppParam()
    {
    }

    virtual ~HppParam()
    {
    }

public:
    float64_t vehicle_front_edge_to_center = 3.5;
    float64_t vehicle_back_edge_to_center = 0.5;
    float64_t vehicle_side_edge_to_center = 1.2;
    float64_t vehicle_length = vehicle_front_edge_to_center + vehicle_back_edge_to_center;
    float64_t vehicle_width = vehicle_side_edge_to_center * 2;
    float64_t max_accelerate = 0.3;
    float64_t max_decelerate = 0.15;
    float64_t back_speed = 2;
    float64_t turn_speed = 3;
    float64_t follow_path_speed = 4;
    size_t zero_speed_path_idx_size = 50;

    bool_t use_obs_avoid = true;
    bool_t use_smooth = true;

    bool_t enable_sqp_solver = true;
    float64_t default_active_set_eps_num = -1e-7;
    float64_t default_active_set_eps_den = 1e-7;
    float64_t default_active_set_eps_iter_ref = 1e-7;
    bool_t default_enable_active_set_debug_info = false;
    int32_t default_qp_iteration_num = 1000;

    uint32_t xy_spline_order = 4;
    float64_t xy_spline_length = 50;
    float64_t xy_constraint_interval = 5;
    float64_t xy_longitudinal_boundary_bound = 1;
    float64_t xy_lateral_boundary_bound = 3;

    float64_t max_distance_tolerance_for_start = 3.0;
    float64_t max_distance_tolerance_for_shift_gear = 1.0;
    float64_t max_speed_tolerance = 0.05;
    float64_t max_localization_tolerance = 0.05;
    float64_t min_adjacent_distance = 0.05;
    float64_t smooth_step = 0.05;
};
}  // namespace planning
}  // namespace holo

#endif