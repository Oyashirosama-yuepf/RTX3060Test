/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file trajectory_predictor.h
 * @brief the header of trajectory predictor in lattice
 * @author zhangyuchen(zhangyuchen@holomatic.com)
 * @date 2019-12-25
 */

#ifndef _HOLO_PLANNING_LATTICE_TRAJECTORY_PREDICTOR_H_
#define _HOLO_PLANNING_LATTICE_TRAJECTORY_PREDICTOR_H_

#include <unordered_map>

#include <holo/core/types.h>

#include <holo/planning/common/box/normal_box.h>
#include <holo/planning/common/plan_route.h>

namespace holo
{
namespace planning
{
namespace lattice
{
/**
 * @brief Class for predict frenet trajectory
 */
class TrajectoryPredictor
{
public:
    using predicted_boxes_trajectory_ptr = std::shared_ptr<std::vector<std::vector<NormalBox>>>;
    using ObstacleList                   = std::vector<std::shared_ptr<ObstacleInfo>>;
    /**
     * @brief delete construct
     */
    TrajectoryPredictor() = delete;

    /**
     * @brief predict frenet trajectory
     *
     * @param obs_list obstacle pointer list
     * @param predicted_obs_box pointer to save predicted boxes trajectory
     * @param cut_in_obs_ids set include cut in obstacle id
     * @param init_t the time of initial planning point
     */
    static void Predict(const ObstacleList&                 obs_list,
                        predicted_boxes_trajectory_ptr&     boxes_trajectory_ptr,
                        const std::unordered_set<uint32_t>& cut_in_obs_ids,
                        float64_t                           init_t);

    /**
     * @brief predict frenet trajectory
     *
     * @param obs_list obstacle pointer list
     * @param predicted_obs_box pointer to save predicted boxes trajectory
     * @param filter_acc_map filtered acceleration map of obstacle
     * @param init_t the time of initial planning point
     * @param decay_factor the decay factor
     */
    static void Predict(const ObstacleList&                            obs_list,
                        predicted_boxes_trajectory_ptr&                boxes_trajectory_ptr,
                        const std::unordered_map<uint32_t, float64_t>& filter_acc_map,
                        float64_t                                      init_t,
                        float64_t                                      decay_factor = 0.0);
};

}  // namespace lattice
}  // namespace planning
}  // namespace holo

#endif