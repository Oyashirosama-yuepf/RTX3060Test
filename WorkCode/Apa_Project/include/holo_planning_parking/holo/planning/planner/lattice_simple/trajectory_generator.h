/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file trajectory_generator.h
 * @brief the header of trajectory generator in lattice
 * @author lizhao(lizhao@holomatic.com)
 * @date 2022-2-14
 */

#ifndef _HOLO_PLANNING_LATTICE_TRAJECTORY_GENERATOR_H_
#define _HOLO_PLANNING_LATTICE_TRAJECTORY_GENERATOR_H_

#include <holo/core/types.h>

#include <holo/planning/common/car_road_state.h>
#include <holo/planning/common/plan_route.h>

namespace holo
{
namespace planning
{
/**
 * @brief Class for generate 2d trajectory
 */
class TrajectoryGenerator
{
public:
    /**
     * @brief delete constructor
     */
    TrajectoryGenerator() = delete;

    /**
     * @brief combine longitudinal and lateral curves into 2D path
     *
     * @param ref_path reference path
     * @param lon_curve longitudinal curve
     * @param lat_curve lateral curve
     * @param trajectory generated 2D path
     */
    static void Generate(const std::vector<CurvePoint>&       ref_path,
                         const std::shared_ptr<math::Curve1d> lat_curve,
                         const float64_t&                     start_s,
                         std::vector<CurvePoint>&             trajectory);
};

}  // namespace planning
}  // namespace holo

#endif