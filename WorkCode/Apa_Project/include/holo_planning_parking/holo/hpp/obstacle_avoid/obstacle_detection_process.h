/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_detection_process.h
 * @brief the header of obstacle detection process
 * @author lizhao(lizhao@holomatic.com)
 * @date 2021-09-25
 */

#ifndef _HOLO_HPP_OBSTACLE_DETECTION_PROCESS_H_
#define _HOLO_HPP_OBSTACLE_DETECTION_PROCESS_H_

#include <holo/hpp/hpp_car_road_state.h>
#include <holo/hpp/scenario/scenario_hpp_struct.h>
#include <holo/planning/util/collision_checker.h>

namespace holo
{
namespace planning
{
class ObstacleDetectionProcess
{
public:
    /**
     * @brief Contructor
     */
    ObstacleDetectionProcess();

    /**
     * @brief Plan safe speed
     *
     * @param[in] cur_scene  0 : backward, 1 : Straight Line, 2 : Turnning
     * @param[in] info  Road info
     * @param[in] behavior_state  The vehicle driving state
     * @param[in] path  The driving path
     * @param[in] use_detection  Use detection
     * @param[in] use_freespace  Use freespace
     * @param[in] use_avm_freespace  Use avm freespace
     * @param[out] max_speed The max speed value
     * @param[out] output The output
     *
     * @return True if process successfully
     */
    bool Process(int32_t                  cur_scene,
                 HppCarRoadState const&   state,
                 RoadInfo const&          info,
                 BehaviorState&           behavior_state,
                 std::vector<CurvePoint>& path,
                 bool                     use_detection,
                 bool                     use_avm_freespace,
                 float64_t&               max_speed,
                 HppOutput&               output);

    /**
     * @brief Plan safe speed for AVP
     *
     * @param[in] cur_scene  0 : backward, 1 : Straight Line, 2 : Turnning
     * @param[in] info  Road info
     * @param[in] behavior_state  The vehicle driving state
     * @param[in] path  The driving path
     * @param[in] use_detection  Use detection
     * @param[in] use_freespace  Use freespace
     * @param[in] use_avm_freespace  Use avm freespace
     * @param[out] max_speed The max speed value
     * @param[out] output The output
     *
     * @return True if process successfully
     */
    bool ProcessAVP(int32_t                  cur_scene,
                    HppCarRoadState const&   state,
                    RoadInfo const&          info,
                    BehaviorState&           behavior_state,
                    std::vector<CurvePoint>& path,
                    bool                     use_detection,
                    bool                     use_avm_freespace,
                    float64_t&               max_speed,
                    HppOutput&               output);

private:
    /**
     * @brief Calculate the distance to obstacle in front of the vehicle
     *
     * @param[in] state The car road state
     * @param[in] info  Road info
     * @param[in] path  The driving path
     * @param[in] use_detection  Use detection
     * @param[in] use_avm_freespace  Use avm freespace
     * @param[out] end_s The end s
     * @param[out] has_dynamic_obstacle True if it has dynamic obstacle,else false
     *
     * @return The distance to obstacle in front of the vehicle
     */
    float64_t FrontObstaclesDetection(HppCarRoadState const&    state,
                                      RoadInfo const&           info,
                                      std::vector<CurvePoint>&  path,
                                      bool                      use_detection,
                                      bool                      use_avm_freespace,
                                      float64_t&                end_s,
                                      ObstacleType&             obstacle_type,
                                      std::array<float64_t, 2>& side_collision_distance);

    /**
     * @brief Calculate the distance to obstacle on both side of the vehicle
     *
     * @param[in] info  Road info
     * @param[in] path  The driving path
     * @param[in] use_detection  Use detection
     * @param[in] use_avm_freespace  Use avm freespace
     * @param[out] end_s The end s
     * @param[out] check_width The check width
     * @param[out] has_dynamic_obstacle True if it has dynamic obstacle,else false
     *
     * @return The distance to obstacle in front of the vehicle
     */
    float64_t SideObstaclesDetection(HppCarRoadState const&   state,
                                     RoadInfo const&          info,
                                     std::vector<CurvePoint>& path,
                                     bool                     use_detection,
                                     bool                     use_avm_freespace,
                                     float64_t&               end_s,
                                     float64_t const          check_width,
                                     ObstacleType&            obstacle_type);

    /**
     * @brief Calculate the distance to obstacle on both side of the vehicle in avp
     *
     * @param[in] info  Road info
     * @param[in] path  The driving path
     * @param[in] use_detection  Use detection
     * @param[in] use_avm_freespace  Use avm freespace
     * @param[out] end_s The end s
     * @param[out] check_width The check width
     * @param[out] obstacle_type obstacle type
     *
     * @return The distance to obstacle in front of the vehicle
     */
    float64_t AVPSideObstaclesDetection(HppCarRoadState const&   state,
                                        RoadInfo const&          info,
                                        std::vector<CurvePoint>& path,
                                        bool                     use_detection,
                                        bool                     use_avm_freespace,
                                        float64_t&               end_s,
                                        float64_t const          check_width,
                                        ObstacleType&            obstacle_type);

    /**
     * @brief Judge whether there is a collision 1meters behind the vehicle
     *
     * @param[in] info  Road info
     * @param[in] use_detection  Use detection
     * @param[in] use_avm_freespace  Use avm freespace
     * @param[out] end_s The end s
     * @param[out] check_width The check width
     *
     * @return The distance to obstacle in front of the vehicle
     */
    bool BackwardObstaclesDetection(RoadInfo const& info,
                                    bool            use_detection,
                                    bool            use_avm_freespace,
                                    float64_t const check_width);

    /**
     * @brief Judge whether there is a collision  behind the vehicle based on pose
     *
     * @param[in] info  Road info
     * @param[in] use_detection  Use detection
     * @param[in] use_avm_freespace  Use avm freespace
     * @param[in] check_width The check width
     * @param[in] backward_distance_range backward distance range
     *
     * @return true: has no collision  false :has collision
     */
    bool_t BackwardObstaclesDetection(RoadInfo const& info,
                                      bool_t          use_detection,
                                      bool_t          use_avm_freespace,
                                      float64_t const check_width,
                                      float64_t       backward_distance_range);
    /**
     * @brief Judge whether has slope
     *
     * @param[in] path  The driving path
     */
    void SlopeConditionJudge(std::vector<CurvePoint>& path);

    /**
     * @brief Calculate vehicle drive distance by wheel pulse
     *
     * @param[in] state  The car road state
     * @param[in] start_left_pulse  The start left wheel pulse
     * @param[in] start_right_pulse  The start right wheel pulse
     *
     * @return The vehicle driving distance
     */
    float64_t CalcuDrivingDistanceByWheelPulse(HppCarRoadState const& state,
                                               uint32_t const&        start_left_pulse,
                                               uint32_t const&        start_right_pulse);

private:
    /**
     * @brief The collision checker
     */
    CollisionChecker collision_checker_;

    /**
     * @brief The speed limit
     */
    float64_t slow_speed_   = 0.83;  // m/s
    float64_t middle_speed_ = 1.66;
    float64_t high_speed_   = 2.77;

    float64_t avp_front_range_obs_speed_  = 1.67;  ///< 5-20m has obs
    float64_t avp_soa_normal_speed_       = 2.78;
    float64_t avp_soa_slow_speed_         = 1.67;
    float64_t avp_soa_minimum_speed_      = 0.83;
    float64_t avp_soa_dynamic_slow_speed_ = 1.94;

    /**
     * @brief The dead distance
     */
    float64_t front_dead_distance_       = 5.0;
    float64_t start_slow_brake_distance_ = 6.0;
    float64_t emergency_dead_distance_   = 1.5;
    float64_t back_dead_distance_        = 1.5;

    float64_t avp_emergency_dead_distance_         = 1;
    float64_t avp_foa_start_slow_brake_distance_   = 5.0;
    float64_t avp_soa_normal_spped_distance_       = 5.0;
    float64_t avp_soa_slow_speed_distance_         = 1.0;
    float64_t avp_soa_minimum_speed_back_distance_ = 1.0;

    /**
     * @brief The check width
     */
    float64_t foa_check_width_        = 0.1;  // m
    float64_t soa_narrow_check_width_ = 0.5;
    float64_t soa_wide_check_width_   = 1.0;
    float64_t mirror_width_           = 0.2;

    float64_t soa_narrow_expand_width_ = 0.3;   ///< by circle 0.3 -> vehicle body expansion 0.5m
    float64_t soa_wide_expand_width_   = 0.85;  ///< by circle 0.85m -> vehicle body expansion 1.0m

    float64_t avp_soa_check_width_        = 1.0;
    float64_t avp_soa_narrow_check_width_ = 0.5;
    float64_t avp_soa_wide_check_width_   = 1.0;

    float64_t check_length_               = 10.0;
    float64_t check_interval_             = 0.5;
    float64_t collision_check_end_buffer_ = 0.3;

    float64_t avp_start_slow_length_                = 10.0;
    float64_t avp_soa_check_length_                 = 20.0;
    float64_t avp_soa_dynamic_minimum_speed_length_ = 5.0;

    bool slope_case_        = false;  //  true if in slope
    bool slope_change_case_ = false;  //  true if in process of entering or exiting slope

    float64_t suspend_state_brk_dist_          = 1.0;
    bool      is_set_suspend_stop_             = false;
    uint32_t  suspend_start_left_wheel_pulse_  = 0;
    uint32_t  suspend_start_right_wheel_pulse_ = 0;

    bool     enable_slow_brake_                = false;
    uint32_t obstacle_start_left_wheel_pulse_  = 0;
    uint32_t obstacle_start_right_wheel_pulse_ = 0;

    uint32_t  max_wheel_pulse_num_   = 4096;
    float64_t wheel_pulse_per_cycle_ = 86.0f;
    float64_t wheel_diameter_        = 0.65f;

    float64_t max_speed_for_speed_hump_          = 3.0 / 3.6;
    float64_t dis_slowdown_for_speed_hump_       = 1.0;
    bool      flag_slowdown_for_speed_hump_      = false;
    uint32_t  speedhump_start_left_wheel_pulse_  = 0;
    uint32_t  speedhump_start_right_wheel_pulse_ = 0;

    float64_t static_start_time_ = 0;
};
}  // namespace planning
}  // namespace holo

#endif
