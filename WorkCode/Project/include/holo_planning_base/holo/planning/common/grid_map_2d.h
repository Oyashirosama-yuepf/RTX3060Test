/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file grid_map_2d.h
 * @brief the header of the grid map in 2d
 * @author zhanghcun(zhangchun@holomatic.com)
 * @date 2020-05-21
 */

#ifndef _HOLO_PLANNING_COMMON_GRID_MAP_2D_H_
#define _HOLO_PLANNING_COMMON_GRID_MAP_2D_H_

#include <holo/geometry/point2.h>
#include <holo/planning/common/headers.h>

namespace holo
{
namespace planning
{
/**
 * @brief Grid map in Frenet
 */
class GridMap2d
{
public:
    struct UnitGrid
    {
        bool_t    occupancy  = false;  ///< true if unit grid is occupied
        float64_t left_bound = 0.0;  ///< left_bound >= 0.0, which is the free distance along positive y axis direction
        float64_t right_bound =
            0.0;  ///< right_bound >= 0.0, which is the free distance along nagative y axis direction
    };

public:
    /**
     * @brief The default constructor
     */
    GridMap2d() = default;

    /**
     * @brief The constructor
     *
     * @param x_start Min x of grid map
     * @param x_end Max x of grid map
     * @param y_start Min y of grid map
     * @param y_end Max y of grid map
     * @param x_interval Interval of x
     * @param y_interval Interval of y
     */
    GridMap2d(float64_t x_start,
              float64_t x_end,
              float64_t y_start,
              float64_t y_end,
              float64_t x_interval,
              float64_t y_interval);

    /**
     * @brief Reset map, define the area of occupancy map
     *
     * @param x_start Min x of grid map
     * @param x_end Max x of grid map
     * @param y_start Min y of grid map
     * @param y_end Max y of grid map
     * @param x_interval Interval of x
     * @param y_interval Interval of y
     */
    void Reset(float64_t x_start,
               float64_t x_end,
               float64_t y_start,
               float64_t y_end,
               float64_t x_interval,
               float64_t y_interval);

    /**
     * @brief Valid
     *
     * @return True if map valid
     */
    bool_t IsValid() const noexcept;

    /**
     * @brief Update map
     *
     * @param x_start Min x to be updated
     * @param x_end Max x to be updated
     * @param y_start Min l to be updated
     * @param y_end Max l to be updated
     * @param free_spaces_range Free spaces range
     * @param free_spaces Free spaces
     * @param obstacles Obstacles
     */
    bool_t Update(float64_t                                         x_start,
                  float64_t                                         x_end,
                  float64_t                                         y_start,
                  float64_t                                         y_end,
                  std::vector<std::vector<geometry::Point2>> const& free_spaces_range,
                  std::vector<std::vector<geometry::Point2>> const& free_spaces,
                  std::vector<std::vector<geometry::Point2>> const& obstacles);

    /**
     * @brief Update map
     *
     * @param x_start Min x to be updated
     * @param x_end Max x to be updated
     * @param y_start Min l to be updated
     * @param y_end Max l to be updated
     * @param avm_free_spaces Avm free spaces
     * @param obstacles Obstacles
     */
    bool_t Update(float64_t                                         x_start,
                  float64_t                                         x_end,
                  float64_t                                         y_start,
                  float64_t                                         y_end,
                  std::vector<std::vector<geometry::Point2>> const& avm_free_spaces,
                  std::vector<std::vector<geometry::Point2>> const& obstacles);

    /**
     * @brief Update map
     *
     * @param free_spaces_range Free spaces range
     * @param free_spaces Free spaces
     * @param obstacles Obstacles
     */
    bool_t Update(std::vector<std::vector<geometry::Point2>> const& free_spaces_range,
                  std::vector<std::vector<geometry::Point2>> const& free_spaces,
                  std::vector<std::vector<geometry::Point2>> const& obstacles);

    /**
     * @brief Free part of active map(TODO)
     */
    void Delete(){};

    /**
     * @brief Check point occupancy use four surrounding points
     *
     * @param x X of point to be checked
     * @param y Y of point to be checked
     *
     * @return True if point is occupied
     */
    bool_t IsOccupied(float64_t x, float64_t y) const;

    /**
     * @brief Calculate point bounds
     *
     * @param[in] x X of point to be checked
     * @param[in] y Y of point to be checked
     * @param[out] left_bound Left bound of point
     * @param[out] right_bound Right bound of point
     */
    void GetSideBound(float64_t x, float64_t y, float64_t& left_bound, float64_t& right_bound) const;

    /**
     * @brief Check box occupancy
     *
     * @param x_start Min x of box to be checked
     * @param x_end Max x of box to be checked
     * @param y_start Min y of box to be checked
     * @param y_end Max y of box to be checked
     *
     * @return True if box is occupied
     */
    bool_t IsOccupied(float64_t x_start, float64_t x_end, float64_t y_start, float64_t y_end) const;

    /**
     * @brief Calculate box bounds
     *
     * @param[in] x_start Min x of box to be checked
     * @param[in] x_end Max x of box to be checked
     * @param[in] y_start Min y of box to be checked
     * @param[in] y_end Max y of box to be checked
     * @param[out] left_bound Left bound of box
     * @param[out] right_bound Right bound of box
     */
    void GetSideBound(float64_t  x_start,
                      float64_t  x_end,
                      float64_t  y_start,
                      float64_t  y_end,
                      float64_t& left_bound,
                      float64_t& right_bound) const;

private:
    /**
     * @brief Sample x
     */
    std::vector<float64_t> x_sample_;

    /**
     * @brief Sample y
     */
    std::vector<float64_t> y_sample_;

    /**
     * @brief Data of grid map
     */
    std::vector<std::vector<UnitGrid>> grid_;
};

}  // namespace planning
}  // namespace holo

#endif  //_HOLO_PLANNING_COMMON_GRID_MAP_FRENET_H_
