/*!
 *  \brief
 *  \author dongyong (dongyong@holomatic.com)
 *  \date Apr 8, 2018
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */
#ifndef _PARK_PARAM_H_
#define _PARK_PARAM_H_

#include <holo/core/types.h>
#include <math.h>
#include <stddef.h>
#include <string>

namespace holo
{
namespace planning
{
class ParkParam
{
public:
    static ParkParam& Instance()
    {
        static ParkParam instance;
        return instance;
    }

private:
    ParkParam()
    {
    }

    ~ParkParam()
    {
    }

public:
    std::string spiral_yaml_file_path = "spiral.yaml";

    bool_t use_obs_avoid = true;
    bool_t use_near_park_avoid = false;

    float64_t vehicle_front_edge_to_center = 3.5;
    float64_t vehicle_back_edge_to_center = 0.5;
    float64_t vehicle_side_edge_to_center = 1.2;
    float64_t vehicle_length = vehicle_front_edge_to_center + vehicle_back_edge_to_center;
    float64_t vehicle_width = vehicle_side_edge_to_center * 2;
    float64_t back_speed = 2;
    float64_t park_speed = 3;
    float64_t follow_path_speed = 4;
    float64_t max_accelerate = 0.3;
    float64_t max_decelerate = 0.15;

    float64_t park_avoid_obs_head_dist = 15;
    float64_t front_obs_ignore_dis = 30;
    float64_t back_obs_ignore_dis = 10;
    float64_t side_obs_ignore_dis = 10;
    float64_t obstalce_inflate_range = 5;
    float64_t obstalce_inflate_buffer_limit = 0.5;
    float64_t obstacle_check_preview_distance = 1.5;
    size_t zero_speed_path_idx_size = 50;

    float64_t dp_path_cost_resolution = 0.5;
    float64_t dp_path_cost_lateral_ignore_dist = 3.0;
    float64_t dp_path_cost_l_cost = 800;  //6.5;
    float64_t dp_path_cost_his_l_cost = 200;
    float64_t dp_path_cost_dl_cost = 8000.0;  //8000.0;
    float64_t dp_path_cost_ddl_cost = 500.0;  //1;
    float64_t dp_path_cost_endl_cost = 0;     //10000.0;

    float64_t dp_path_cost_l_quasi_softmax_l0 = 1.5;
    float64_t dp_path_cost_l_quasi_softmax_b = 0.4;
    float64_t dp_path_cost_l_quasi_softmax_k = 1.5;

    float64_t dp_obstacle_collision_distance = 0.2;
    float64_t dp_obstacle_collision_cost = 1000.0;
    float64_t dp_obstacle_static_nudge_l = 0.3;
    float64_t dp_obstacle_static_safe_l_dist = 0.6;

    float64_t dp_path_sample_start_l = -8;
    float64_t dp_path_sample_end_l = 8;
    float64_t dp_path_sample_l_step = 0.5;
    float64_t dp_path_level_step = 3;

    bool_t enable_sqp_solver = true;
    float64_t default_active_set_eps_num = -1e-7;
    float64_t default_active_set_eps_den = 1e-7;
    float64_t default_active_set_eps_iter_ref = 1e-7;
    bool_t default_enable_active_set_debug_info = false;
    int32_t default_qp_iteration_num = 1000;

    uint32_t sl_spline_order = 4;
    float64_t sl_spline_length = 5;
    float64_t sl_constraint_interval = 0.5;
    float64_t sl_dl_constraint = 1;
    float64_t sl_ddl_constraint = 0.5;
    float64_t sl_dddl_constraint = 0.05;
    float64_t sl_path_smooth_step = 1;

    uint32_t xy_spline_order = 4;
    float64_t xy_spline_length = 50;
    float64_t xy_constraint_interval = 5;
    float64_t xy_longitudinal_boundary_bound = 1;
    float64_t xy_lateral_boundary_bound = 3;

    float64_t rrt_roi_range = 4;
    size_t rrt_max_loop = 10000;
    float64_t rrt_random_area_gap = 10;
    float64_t obstacle_inflate_size_max = 1.8;
};
}  // namespace planning
}  // namespace holo

#endif