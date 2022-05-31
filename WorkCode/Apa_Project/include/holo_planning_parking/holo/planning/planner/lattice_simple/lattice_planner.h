/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lattice_planner.h
 * @brief the header of lattice planner
 * @author lizhao(lizhao@holomatic.com)
 * @date 2022-2-14
 */

#ifndef _LATTICE_PLANNER_H_
#define _LATTICE_PLANNER_H_

#include <holo/core/types.h>
#include <holo/planning/common/car_road_state.h>

namespace holo
{
namespace planning
{
class LatticePlanner
{
public:
    /**
     * @brief Construct a new Lattice Planner object
     */
    LatticePlanner() = default;

    /**
     * @brief Destroy the Lattice Planner object
     */
    ~LatticePlanner() = default;

    /**
     * @brief plan and generate path
     *
     * @param ref_path reference path
     * @param pose vehicle current pose
     * @param path save generated path
     *
     * @return bool_t true if plan successfully, false otherwise
     */
    virtual bool_t Plan(const std::vector<CurvePoint>&        ref_path,
                        const geometry::Pose2                 pose,
                        const float64_t                       left_road_width,
                        const float64_t                       right_road_width,
                        const float64_t                       interval,
                        const float64_t                       vehicle_width,
                        const float64_t                       lattice_length,
                        std::vector<std::vector<CurvePoint>>& path_set,
                        std::vector<float64_t>&               path_offset);

private:
    void ComputeInitFrenetState(const CurvePoint&         matched_point,
                                const geometry::Pose2     pose,
                                std::array<float64_t, 3>* ptr_s,
                                std::array<float64_t, 3>* ptr_d);
};
}  // namespace planning
}  // namespace holo

#endif  //_LATTICE_PLANNER_H_