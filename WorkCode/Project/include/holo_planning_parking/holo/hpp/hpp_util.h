/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hpp_util.h
 * @brief the header of util for hpp
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2021-01-19
 */

#ifndef _HPP_UTIL_
#define _HPP_UTIL_

#include <vector>

#include <holo/obstacle/obstacle_list.h>
#include <holo/planning/common/curve_point.h>

namespace holo
{
namespace planning
{
/**
 * @brief Transform obstalce coordinate from body to global
 *
 * @param[in] origin Obstacle in body frame
 * @param[out] transformed Obstacle in global frame
 * @param[in] pose Current pose
 */
void ObstaclePreprocess(std::vector<std::vector<geometry::Point2>> const& origin,
                        std::vector<std::vector<geometry::Point2>>&       transformed,
                        std::vector<std::vector<geometry::Point2>>&       not_transformed,
                        geometry::Pose2                                   pose);

/**
 * @brief Transform obstalce coordinate from body to global
 *        Only detection is in use, and now the detection format
 *        is changed to eight corners for each obstacle, and the
 *        first four are points on the ground.
 *
 * @param[in] origin Obstacle in body frame
 * @param[out] transformed Obstacle in global frame
 * @param[out] types Obstacle types
 * @param[out] obstacle_motion_status Obstacle motion status
 * @param[in] pose Current pose
 */
void ObstaclePreprocess(
    std::shared_ptr<holo::obstacle::ObstaclePtrListT<holo::obstacle::ObstacleGeneralT<holo::float32_t>, 128UL>> const&
                                                                               origin,
    std::vector<std::vector<geometry::Point2>>&                                transformed,
    std::vector<std::vector<geometry::Point2>>&                                not_transformed,
    std::vector<std::pair<Classification::MainType, Classification::SubType>>& types,
    std::vector<holo::obstacle::details::MotionStatus>&                        obstacle_motion_status,
    geometry::Pose2                                                            pose,
    const float64_t&                                                           obstacle_x,
    const float64_t&                                                           obstacle_y,
    const float64_t&                                                           obstacle_width,
    bool_t&                                                                    obstacle_existance_score_abnormal);

/**
 * @brief Translate body path to global frame
 *
 * @param path Origin path
 * @param pose Current pose
 */
void TranslatePath(std::vector<CurvePoint>& path, const geometry::Pose2d& pose);
}  // namespace planning
}  // namespace holo

#endif
