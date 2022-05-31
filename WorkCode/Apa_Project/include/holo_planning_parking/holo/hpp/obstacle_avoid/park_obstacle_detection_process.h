/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file park_obstacle_detection_process.h
 * @brief the header of obstacle detection process
 * @author huangnan(huangnan@holomatic.com)
 * @date 2022-01-14
 */

#ifndef _HOLO_HPP_PARK_OBSTACLE_DETECTION_PROCESS_H_
#define _HOLO_HPP_PARK_OBSTACLE_DETECTION_PROCESS_H_

#include <holo/hpp/hpp_car_road_state.h>
#include <holo/hpp/scenario/scenario_hpp_struct.h>
#include <holo/planning/util/collision_checker.h>

namespace holo
{
namespace planning
{
class ParkObstacleDetectionProcess
{
public:
    /**
     * @brief Contructor
     */
    ParkObstacleDetectionProcess();

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
                 bool                     use_freespace,
                 bool                     use_avm_freespace,
                 float64_t&               max_speed,
                 HppOutput&               output);

private:
    /**
     * @brief Calculate the distance to obstacle in front of the vehicle
     *
     * @param[in] info  Road info
     * @param[in] path  The driving path
     * @param[in] use_detection  Use detection
     * @param[in] use_freespace  Use freespace
     * @param[in] use_avm_freespace  Use avm freespace
     * @param[out] end_s The end s
     * @param[out] has_pedestrian_obstacle True if it has dynamic obstacle,else false
     *
     * @return The distance to obstacle in front of the vehicle
     */
    float64_t FrontObstaclesDetection(RoadInfo const&          info,
                                      std::vector<CurvePoint>& path,
                                      bool                     use_detection,
                                      bool                     use_freespace,
                                      bool                     use_avm_freespace,
                                      float64_t&               end_s,
                                      bool&                    has_pedestrian_obstacle);

    /**
     * @brief Judge whether has slope
     *
     * @param[in] path  The driving path
     */
    void SlopeConditionJudge(std::vector<CurvePoint>& path);

private:
    /**
     * @brief The collision checker
     */
    CollisionChecker collision_checker_;

    /**
     * @brief The dead distance
     */
    float64_t front_dead_distance_pullout_     = 2.0;
    float64_t emergency_dead_distance_pullout_ = 0.25;
    float64_t back_dead_distance_pullout_      = 0.25;

    /**
     * @brief The check width
     */
    float64_t foa_check_width_pullout_ = 0.2;  // m

    float64_t front_dead_distance_parkin_     = 2.0;
    float64_t emergency_dead_distance_parkin_ = 0.25;
    float64_t back_dead_distance_parkin_      = 0.25;

    float64_t foa_check_width_parkin_ = 0.0;  // m

    float64_t mirror_width_ = 0.2;

    float64_t foa_check_width_ = 0.0;  // m

    float64_t check_length_               = 2.0;
    float64_t check_interval_             = 0.1;
    float64_t collision_check_end_buffer_ = 0.3;

    bool slope_case_        = false;  //  true if in slope
    bool slope_change_case_ = false;  //  true if in process of entering or exiting slope

    float64_t pede_obs_dis_     = 1.0;
    float64_t non_pede_obs_dis_ = 0.3;
};
}  // namespace planning
}  // namespace holo

#endif
