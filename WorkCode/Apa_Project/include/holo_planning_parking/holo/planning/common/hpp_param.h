/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hpp_param.h
 * @brief the header of hpp param
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2019-09-20
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
    float64_t back_speed                      = 0.6;
    float64_t turn_speed                      = 0.6;
    float64_t follow_path_speed               = 1.1;
    float64_t follow_path_middle_speed        = 1.6;
    float64_t smooth_step                     = 0.1;
    float64_t discrete_step                   = 0.3;
    float64_t start_zero_speed_path_length    = 5;
    float64_t end_zero_speed_path_length      = 20;
    float64_t dynamic_path_length             = 15;
    float64_t min_valid_obstacle_area         = 0.04;
    float64_t foa_check_width                 = 0.2;
    float64_t soa_narrow_check_width          = 0.5;
    float64_t soa_wide_check_width            = 1.0;
    float64_t mirror_width                    = 0.36;
    float64_t soa_narrow_expand_width         = 0.3;
    float64_t soa_wide_expand_width           = 0.85;
    float64_t avoid_check_width               = 0.5;
    float64_t straight_dead_distance          = 5.0;
    float64_t start_slow_brake_distance       = 6.0;
    float64_t turn_dead_distance              = 1.5;
    float64_t back_dead_distance              = 1.5;
    float64_t steer_ratio                     = 16.82;
    uint32_t  takeover_frame                  = 20;
    float64_t suspend_state_brk_dist          = 1.0;
    float64_t soa_check_width                 = 0.5;
    float64_t front_dead_distance_pullout     = 2.0;
    float64_t emergency_dead_distance_pullout = 0.25;
    float64_t back_dead_distance_pullout      = 0.25;
    float64_t foa_check_width_pullout         = 0.03;
    float64_t soa_check_width_pullout         = 0.05;
    float64_t back_speed_pullout              = 0.2;
    float64_t forward_speed_pullout           = 0.4;
    float64_t front_dead_distance_parkin      = 2.0;
    float64_t emergency_dead_distance_parkin  = 0.25;
    float64_t back_dead_distance_parkin       = 0.25;
    float64_t foa_check_width_parkin          = 0.03;
    float64_t soa_check_width_parkin          = 0.05;
    float64_t back_speed_parkin               = 0.2;
    float64_t forward_speed_parkin            = 0.4;
    float64_t park_min_velocity               = 0.28;
    uint32_t  max_wheel_pulse_num             = 4096;
    float64_t wheel_diameter                  = 0.65f;
    float64_t wheel_pulse_per_cycle           = 86.0f;
    float64_t pede_obs_dis                    = 1.0;
    float64_t non_pede_obs_dis                = 0.3;
    float64_t max_speed_for_speed_hump        = 3.0 / 3.6;
    float64_t dis_slowdown_for_speed_hump     = 1.0;

    float64_t turn_curvature        = 0.05;
    uint32_t  turn_front_expand_num = 30;
    uint32_t  turn_back_expand_num  = 20;
    uint32_t  turn_valid_num        = 4;

    bool front_wheel_angle_left_negative = false;

    bool      use_control_output            = false;
    bool      use_spline_curvature          = false;
    bool      use_freespace                 = true;
    bool      use_avm_freespace             = true;
    bool      use_detection                 = true;
    bool      use_uss                       = true;
    bool      use_avoid                     = true;
    bool      use_parkin                    = true;
    bool      is_steer_feedback             = false;
    bool      enable_pullout                = false;
    bool      enable_constraint_4_init_pose = false;
    float64_t distance_not_to_pullout       = 0.5;
    float64_t distance_to_parkin            = 5.0;
    uint32_t  stop_exit_waiting_cycle       = 300;
    bool      enable_detect_slot            = false;
    float64_t x_translate                   = 10.0;
    float64_t y_translate                   = 2.0;
    bool      enable_hpa2apa                = false;

    bool      enable_avoid_obstacle                = false;
    float64_t obstacle_coor_x                      = 100.0;
    float64_t obstacle_coor_y                      = 100.0;
    float64_t obstacle_edge_length                 = 0.3;
    bool      enable_sqp_solver                    = true;
    float64_t default_active_set_eps_num           = -1e-7;
    float64_t default_active_set_eps_den           = 1e-7;
    float64_t default_active_set_eps_iter_ref      = 1e-7;
    bool      default_enable_active_set_debug_info = false;
    int32_t   default_qp_iteration_num             = 4000;

    uint32_t  xy_spline_order                = 4;
    float64_t xy_spline_length               = 5;
    float64_t xy_constraint_interval         = 1;
    float64_t xy_longitudinal_boundary_bound = 0.1;
    float64_t xy_lateral_boundary_bound      = 0.08;

    uint32_t  sl_spline_order        = 4;
    float64_t sl_spline_length       = 10;
    float64_t sl_constraint_interval = 0.5;
    float64_t sl_dl_constraint       = 1;
    float64_t sl_ddl_constraint      = 0.5;
    float64_t sl_dddl_constraint     = 0.05;

    float64_t init_allow_lon_displace               = 5.0;
    float64_t init_allow_lat_displace               = 2.0;
    float64_t init_allow_heading_diff               = 0.26;
    float64_t max_distance_tolerance_for_shift_gear = 0.5;
    float64_t max_position_change                   = 5.0;
    float64_t max_speed_tolerance                   = 0.05;
    float64_t max_localization_tolerance            = 0.35;
    float64_t min_adjacent_distance                 = 0.3;
    float64_t max_allow_distance                    = 50;
    float64_t max_allow_heading_diff                = 1.74;
    float64_t min_allow_heading_diff                = -0.17;  /// <-10~100°

    bool      enable_safety_monitor           = false;
    float64_t chassis_timeout_threshold       = 0.3;
    float64_t odometry_timeout_threshold      = 0.5;
    float64_t detection_timeout_threshold     = 0.5;
    float64_t freespace_timeout_threshold     = 0.5;
    float64_t avm_freespace_timeout_threshold = 0.5;

    float32_t high_limit_speed        = 3.06;
    float32_t low_limit_speed         = 1.11;
    float64_t max_curvature_threshold = 0.2;

    std::string steering_ratio_table_file = "";
};
}  // namespace planning
}  // namespace holo

#endif
