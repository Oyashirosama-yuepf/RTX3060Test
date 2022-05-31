/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file grid_map_frenet.h
 * @brief the header of grid map in fetnet
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2020-03-27
 */

#ifndef _HOLO_PLANNING_COMMON_GRID_MAP_FRENET_H_
#define _HOLO_PLANNING_COMMON_GRID_MAP_FRENET_H_

#include <holo/common/path.h>
#include <holo/geometry/pose2.h>
#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/planning/common/config/grid_map_frenet_config.h>
#include <holo/planning/common/sl_path.h>

namespace holo
{
namespace planning
{
/**
 * @brief Class grip map frenet
 */
class GridMapFrenet
{
public:
    typedef holo::ObstacleGeneralT<holo::float32_t> Obstacle;
    typedef holo::ObstaclePtrListT<Obstacle>        ObstacleList;
    typedef std::shared_ptr<ObstacleList>           ObstacleListPtr;

public:
    /**
     * @brief Constructor
     */
    GridMapFrenet(config::GridMapFrenetConfig const& grid_map_frenet_cfg);

    /**
     * @brief Reset map, define the area of occupancy map
     *
     * @param reference_path reference path
     */
    bool Reset(common::Path const& reference_path);

    /**
     * @brief Update map
     *
     * @param pose              current pose
     * @param free_spaces       free spaces
     * @param ranges            ranges
     * @param obstacles         obstacles
     * @param free_space_end_s  the s value of first point of turning along the path starting from pose
     */
    void Update(geometry::Pose2 const&           pose,
                ObstacleListPtr const& free_spaces,
                ObstacleListPtr const& ranges,
                ObstacleListPtr const& obstacles,
                float64_t              free_space_end_s);

    /**
     * @brief Check SL point occupancy
     *
     * @param point point checked
     */
    bool CheckOccupancy(SLPoint const& point) const;

    /**
     * @brief Get min l
     */
    float64_t GetMinL() const
    {
        return l_min_;
    }

    /**
     * @brief Get max l
     */
    float64_t GetMaxL() const
    {
        return l_max_;
    }

    /**
     * @brief Get s interval
     */
    float64_t GetIntervalS() const
    {
        return s_interval_;
    }

    /**
     * @brief Get l interval
     */
    float64_t GetIntervalL() const
    {
        return l_interval_;
    }

private:
    /**
     * @brief Check the s value is monotone increasing
     *
     * @param reference_path    reference path
     */
    bool IsReferencePathValid(common::Path const& reference_path) const;

    /**
     * @brief Check pt is in obstalces or not
     *
     * @param pt                point checked
     * @param obstacles         obstacles
     */
    bool InObstacles(geometry::Point2 const& pt, ObstacleListPtr const& obstacles) const;

    /**
     * @brief Check pt is in free spaces or not
     *
     * @param pt                point checked
     * @param free_spaces       free spaces
     */
    bool InFreeSpaces(geometry::Point2 const& pt, ObstacleListPtr const& free_spaces) const;

    /**
     * @brief Check pt is in ranges or not
     *
     * @param pt                point checked
     * @param ranges            ranges
     */
    bool InRange(geometry::Point2 const& pt, ObstacleListPtr const& ranges) const;

private:
    /**
     * @brief Sample s inteval
     */
    float64_t s_interval_ = 0.5;

    /**
     * @brief Sample l inteval
     */
    float64_t l_interval_ = 0.2;

    /**
     * @brief Min l
     */
    float64_t l_min_ = -3.5;

    /**
     * @brief Max l
     */
    float64_t l_max_ = 3.5;

    /**
     * @brief Update distance
     */
    float64_t update_distance_ = 15.0;

    /**
     * @brief Sample s
     */
    std::vector<float64_t> s_sample_;

    /**
     * @brief Sample l
     */
    std::vector<float64_t> l_sample_;

    /**
     * @brief Reference path
     */
    common::Path reference_path_;

    /**
     * @brief Occupancy map
     */
    std::vector<std::vector<bool>> occupancy_map_;
};
}  // namespace planning
}  // namespace holo

#endif