/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file polygon_iou.h
 * @brief This file define to compute polygon iou .
 * @author wuyulun(wuyulun1@holomatic.com)
 * @date "2021-05-18"
 */

#ifndef HOLO_PERCEPTION_GEOMETRY_PLYGON_IOU_H_
#define HOLO_PERCEPTION_GEOMETRY_PLYGON_IOU_H_

#include <vector>

#include <holo/geometry/line_segment2.h>
#include <holo/geometry/point2.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup polygon iou
 * @{
 */
using Point2Type = holo::geometry::Point2T<float64_t>;
using Vertexes   = std::vector<Point2Type>;
using Line2Type  = holo::geometry::LineSegment2T<float64_t>;

/**
 * @brief intersection area between two polygon
 *
 * @param[in] corner_points1 one corner box
 * @param[in] corner_points2 another corner box
 * @return float64_t return area of two corner box intersection
 */
float64_t AreaIntersection(Vertexes const& corner_points1, Vertexes const& corner_points2);

/**
 * @brief union area between two polygon
 *
 * @param[in] corner_points1 one corner box
 * @param[in] corner_points2 another one corner box
 * @return float64_t return area of two corner box union
 */
float64_t AreaUnion(Vertexes const& corner_points1, Vertexes const& corner_points2);

/**
 * @brief iou between two polygon
 *
 * @param[in] corner_points1 one corner box
 * @param[in] corner_points2 another one corner box
 * @return float64_t return iou AreaIntersection/AreaUnion
 */
float64_t Iou(Vertexes const& corner_points1, Vertexes const& corner_points2);

/**
 * @brief area of a polygon
 *
 * @param[in] corner_points one corner box
 * @return float64_t return area of this corner box
 */
float64_t Area(Vertexes const& corner_points);

/**
 * @brief wise type
 *
 * @param[in] corner_points  corner points
 * @return int8_t return wise type
 */
int8_t WhichWise(Vertexes const& corner_points);  //  0 NoneWise,   1  ClockWise,   2  AntiClockWise

/**
 * @brief checkout corner points type and sort all point
 *
 * @param[in] corner_points corner points
 * @param[in] wise_type wise type
 */
void BeInSomeWise(Vertexes& corner_points, int8_t const wise_type);

/**
 * @brief check point whether in polygon
 *
 * @param[in] corner_points corner points
 * @param[in] local_point  one point
 * @return int8_t return type
 */
int8_t Location(Vertexes const& corner_points, Point2Type const& local_point);  // 0  Outside,  1  OnEdge,  2 Inside

/**
 * @brief find inter point between a point and a polygon
 *
 * @param[in] corner_points corner points
 * @param[in] line line segment
 * @param[out] result_points inter points between corner line and line
 * @return int32_t return inter points num
 */
int32_t InterPts(Vertexes const& corner_points, Line2Type const& line, Vertexes& result_points);

/**
 * @brief find inter point between two polygon
 *
 * @param[in] corner_points1
 * @param[in] corner_points2
 * @param[out] result_points inter points between corner polygon and corner polygon
 * @return int32_t return inter point num
 */
int32_t FindInterPoints(Vertexes const& corner_points1, Vertexes const& corner_points2, Vertexes& result_points);

/**
 * @brief check corner point whether in another polygon
 *
 * @param[in] corner_points1
 * @param[in] corner_points2
 * @param[out] result_points the corner point in corner box
 * @return int32_t return inner points num
 */
int32_t FindInnerPoints(Vertexes const& corner_points1, Vertexes const& corner_points2, Vertexes& result_points);

/**
 * @brief check point whether on line
 *
 * @param[in] line line segment
 * @param[in] p point2
 * @return bool_t return true if point on line segment
 */
bool_t IsOnEdge(Vertexes const& line, Point2Type const& p);

/**
 * @}
 */
}  // namespace perception
}  // namespace holo
#endif
