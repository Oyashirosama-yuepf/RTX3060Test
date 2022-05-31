/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file util.h
 * @brief control base common function
 * @author zhengshaoqian(zhengshaoqian@holomatic.com)
 * @date 2020-06-23
 */

#ifndef HOLO_C_CONTROL_UTIL_H_
#define HOLO_C_CONTROL_UTIL_H_

#include <assert.h>
#include <holo_c/common/odometry_float32.h>
#include <holo_c/common/path_float32.h>
#include <holo_c/core/types.h>

#include <holo_c/common/chassis_state.h>
#include <holo_c/common/coordinate.h>
#include <holo_c/geometry/angle_float32.h>
#include <holo_c/geometry/point2_float32.h>
#include <holo_c/geometry/point3.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief get linear speed from odometry
 *
 * @param odometry
 * @param vx
 */
float32_t control_base_get_vx(const struct Odometryf* odometry);

/**
 * @brief get linear speed from odometry
 *
 * @param odometry
 * @param vy
 */
float32_t control_base_get_vy(const struct Odometryf* odometry);

/**
 * @brief get linear speed from odometry
 *
 * @param odometry
 * @param linear_v
 */
float32_t control_base_get_liner_v(const struct Odometryf* odometry);

/**
 * @brief tell if current vehicle is backward or not
 *
 * @param path
 * @param chassis_state
 * @return true - backward
 */
bool_t control_base_is_backward(const struct Pathf* path, const struct ChassisState* chassis_state);

/**
 * @brief According to the path information, tell if vehicle need emergency braking or not
 *
 * @param path
 * @return true - emergency braking
 */
bool_t control_base_is_emergency_braking(const struct Pathf* path);

/**
 * @brief Cal the projection point from the current point to a line segment
 *
 * @param pt_start start point of line segment
 * @param pt_end end point of the segment
 * @param pt_cur current point
 * @param pt_proj projection point on the segment
 * @param t projection scale of projection point to line segment
 * @param s distance from projection point to starting point
 */
void control_base_project_point_to_segment(const struct Point2f* pt_start,
                                           const struct Point2f* pt_end,
                                           const struct Point2f* pt_cur,
                                           struct Point2f*       pt_proj,
                                           float32_t*            t,
                                           float32_t*            s);

/**
 * @brief Find the time-matched index point on the path
 *
 * @param path_f planning trajectory
 * @return time-matched index
 */
uint32_t control_base_find_time_matched_pt_index(const struct Pathf* path_f);

/**
 * @brief Considering the time delay bewtween path and control, find the time-matched point on the path.
 *
 * @param path_f planning trajectory
 * @param time_delay the transit time from planning to control
 * @return time matched point
 */
struct PathPointf control_base_find_time_matched_point(const struct Pathf* path_f, float64_t time_delay);

/**
 * @brief Find the nearest index point on the path
 *
 * @param path_f planning trajectory
 * @param pt_cur current point
 * @return nearest index
 */
uint32_t control_base_path_find_front_nearest_pt_index(const struct Pathf* path_f, const struct Point3f* pt_cur);

/**
 * @brief Get the projection point from the current point to the path
 *
 * @param path_f planning trajectory
 * @param pt_cur current point
 * @param pt_proj projection point on the segment
 * @param s distance from projection point to starting point
 */
void control_base_project_point_to_path(const struct Pathf*   path_f,
                                        const struct Point3f* pt_cur,
                                        struct PathPointf*    ppt_proj,
                                        float32_t*            s);

/**
 * @brief According to the distance interpolation, the pre path points are obtained
 *
 * @param path_f planning trajectory
 * @param s distance from starting point
 * @param ppt_interpolate interpolation points from distance
 */
void control_base_path_interpolate(const struct Pathf* path_f, float32_t s, struct PathPointf* ppt_interpolate);

/**
 * @brief the direction of the current point to a point
 *
 * @param ppt_proj a path point
 * @param pt_cur current point
 *
 * @return the direction of the current point to a point
 */
int32_t control_base_orientation(const struct PathPointf* ppt_proj, const struct Point3f* pt_cur);

/**
 * @brief Calculates the projection point from the current point to a line segment
 *
 * @param pt_start start point of line segment
 * @param pt_end end point of the segment
 * @param pt_cur current point
 * @param ppt_proj projection point on the segment
 * @param t projection scale of projection point to line segment
 * @param s distance from projection point to starting point
 */
void control_base_project_point_to_pp_segment(const struct PathPointf* ppt_start,
                                              const struct PathPointf* ppt_end,
                                              const struct Point3f*    pt_cur,
                                              struct PathPointf*       ppt_proj,
                                              float32_t*               t,
                                              float32_t*               s);

/**
 * @brief Calculating linear interpolation
 *
 * @param table Interpolation table
 * @param table_size Interpolation table size
 * @param x Interpolation points
 *
 * @return interpolation coef

 */
float32_t control_base_linear_interpolation(const struct Point2f* table, uint32_t table_size, float32_t x);

/**
 * @brief Calculating 2D linear interpolation
 *
 * @param table_2D 2D Interpolation table
 * @param rows the rows of table
 * @param cols the cols of table
 * @param x the value in x-axis
 * @param y the value in y-axis
 *
 * @return the interpolated value

 */
float32_t control_base_linear_interpolation2D(const struct Point3f* table_2D, uint32_t rows, uint32_t cols, float32_t x, float32_t y);

/**
 * @brief Find the preview point on path
 *
 * @param path planning path
 * @param car_position car's position
 * @param preview_dist preview distance
 *
 * @return the index of preview point.
 */
uint32_t control_base_find_preview_point_index(const struct Pathf* path,
                                               struct Point3f*     car_position,
                                               float32_t           preview_dist);

/**
 * @brief Find the index of zero velocity point on path.
 * @param point planning path
 */
void control_base_find_still_point_index(const struct Pathf* path, uint32_t* still_index);

/**
 * @brief an comparator of hyperplane
 *
 * @param plane_l hyperplane
 * @param plane_r hyperplane
 *
 * @return RC_FAIL plane_l is greater than or equal to plane_r
 * @return RC_SUCCESS plane_l is less than plane_r in higher dimension
 */
retcode_t control_base_ff_plane_cmp_higher_dimension_lt(uint32_t dimension, const float32_t* plane_l, const float32_t* plane_r);

/**
 * @brief an comparator of hyperplane
 *
 * @param plane_l hyperplane
 * @param plane_r hyperplane
 *
 * @return RC_FAIL plane_l is greater than plane_r
 * @return RC_SUCCESS plane_l is less than or equal to plane_r in every dimension
 */
retcode_t control_base_ff_plane_cmp_lt(uint32_t dimension, const float32_t* plane_l, const float32_t* plane_r);

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_CONTROL_UTIL_H_
