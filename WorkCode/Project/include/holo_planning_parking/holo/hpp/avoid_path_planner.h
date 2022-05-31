/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file avoid_path_planner.h
 * @brief the header of avoid path planner
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2020-05-11
 */

#ifndef _HOLO_HPP_AVOID_PATH_PLANNER_H_
#define _HOLO_HPP_AVOID_PATH_PLANNER_H_

#include <holo/planning/common/grid_map_frenet.h>
#include <holo/planning/common/road_boundary.h>
#include <holo/planning/qp/spline/spline_1d_generator.h>

namespace holo
{
namespace planning
{
class AvoidPathPlanner
{
public:
    /**
     * @brief Contructor
     */
    AvoidPathPlanner();

    /**
     * @brief Plan the avoid path
     *
     * @param[in] advice path Global advice path
     * @param[in] pose Car current pose
     * @param[in] boundaries The available boundaries
     * @param[in] path_length The length of avoid path
     * @param[out] path The avoid path
     * @param[out] dbg_info The info to show in simulator
     *
     * @return True if process successfully
     */
    bool Process(common::Path const&                             advice_path,
                 geometry::Pose2 const&                            pose,
                 GridMapFrenet const&                    grid_map,
                 float64_t                               path_length,
                 float64_t                               path_step,
                 float64_t                               stop_s,
                 common::Path&                                   path,
                 std::vector<std::vector<holo::Point3>>& dbg_info);

private:
    /**
     * @brief Init the planner
     *
     * @param start_s The start s
     * @param end_s The end s
     */
    void InitSpline(float64_t const start_s, float64_t const end_s);

    /**
     * @brief Add constraint for planner
     *
     * @param start_s The start s
     * @param start_l The start l
     * @param start_delta_l The start delta l to s
     * @param boundary The path boundary
     *
     * @return True if add constraint successfully
     */
    bool AddConstraint(float64_t           start_s,
                       float64_t           start_l,
                       float64_t           start_delta_l,
                       float64_t           end_s,
                       float64_t           end_l,
                       RoadBoundary const& boundary);

    /**
     * @brief Add cost
     *
     * @param avoid_sl_path The reference sl path generated from dp planner
     */
    void AddKernel(SLPath const& avoid_sl_path);

    /**
     * @brief The qp slover
     */
    bool Solve();

private:
    /**
     * @brief The qp generator
     */
    std::unique_ptr<Spline1dGenerator> spline_generator_ = nullptr;

    /**
     * @brief The knots of piecewise spline for qp problem
     */
    std::vector<float64_t> knots_;

    /**
     * @brief The set of s value to add constraint for qp problem
     */
    std::vector<float64_t> evaluated_s_;

    /**
     * @brief The spline order
     */
    uint32_t sl_spline_order_ = 5;

    /**
     * @brief The piecewise spline length
     */
    float64_t sl_spline_length_ = 10;

    /**
     * @brief The inverval of s for constarint
     */
    float64_t sl_constraint_interval_ = 0.5;

    /**
     * @brief The dl constraint
     */
    float64_t sl_dl_constraint_ = 1.2;

    /**
     * @brief The ddl constraint
     */
    float64_t sl_ddl_constraint_ = 0.7;

    /**
     * @brief The dddl constraint
     */
    float64_t sl_dddl_constraint_ = 0.5;
};
}  // namespace planning
}  // namespace holo

#endif
