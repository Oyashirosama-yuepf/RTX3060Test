/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file commonfunction.h
 * @brief the header of common used function
 * @author yansenwei(yansenwei@holomatic.com)
 * @date 2021-03-27
 */

#ifndef _COMMONFUNCTION_H_
#define _COMMONFUNCTION_H_

#include <holo/hpp/config/hpp_config.h>
#include <holo/hpp/parkingplan/common_struct_type.h>
// #include <holo/planning/math/math_util.h>

namespace holo
{
namespace planning
{
/**
 * @brief  get system time : microsecond
 */
int64_t GetSystemUsTime();

/**
 * @brief local path planning method based on preview method
 *
 * @param[in] start the current vehicle's pose
 * @param[in] input_path reference path，usually global path
 * @param[out] output_path local path generated based on preview method
 * @param[in] index the index of input path which set as beginning preview candidate
 * @param[in] preview_distance preview distance
 * @param[in] gear actual gear of vehicle
 * @param[in] direction expected direction when current gear is N
 * @param[in] total_pathpoint_num expected total pathpoint number
 */
bool_t LocalPathPlan(geometry::Pose2 const&             start,
                     std::vector<CurvePoint> const&     input_path,
                     std::vector<CurvePoint>&           output_path,
                     int32_t                            index,
                     int32_t                            preview_distance,
                     common::ChassisState::GearPosition gear,
                     bool_t                             direction,
                     uint32_t                           total_pathpoint_num);

/**
 * @brief  purepursuit method
 *
 * @param[in] delta the current lateral deviation
 * @param[in] ld preview distance
 *
 * @return expected steering wheel angle
 */
float64_t PurepursuitByDelta(float64_t delta, float64_t ld);

/**
 * @brief  use B-spline interpolation to smooth the path
 *
 * @param[in] source_data original path
 *
 * @return smoothed path
 */
std::vector<CurvePoint> Interpolate(std::vector<CurvePoint> const& source_data);

/**
 * @brief  calculate curvepoint's heading angle and length
 *
 * @param[out] path
 * @param[in] mode results under different coordinate system definitions
 */
void CalculateLinePointHeadingAndLength(std::vector<CurvePoint>& data, uint8_t mode);

/**
 * @brief  calculate curvepoint's heading angle
 *
 * @param[in] point_0 point0
 * @param[in] point_1 point1
 * @param[in] mode forward：0  backward:1
 *
 * @return heading angle
 */
float64_t CalculatePointHeading(CurvePoint point_0, CurvePoint point_1, uint8_t mode);

/**
 * @brief  path screening by threshold
 *
 * @param[in] source_data original path
 * @param[in] threshold threshold ：every threshold distance to pick a point
 *
 * @return processed path
 */
std::vector<CurvePoint> LineFilter(std::vector<CurvePoint> const& source_data, float64_t threshold);

/**
 * @brief  get the sign of input
 *
 * @param[in] x input
 *
 * @return sign of input
 */
template <typename M>
int32_t Sign(M x)
{
    if (x > 0)
    {
        return 1;
    }
    else if (x < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  pick the smaller of the two input
 *
 * @param[in] x1 input 1
 * @param[in] x2 input 2
 *
 * @return return the smaller of the two input
 */
template <typename M, typename N>
M Min(M x1, N x2)
{
    if (x1 <= x2)
    {
        return x1;
    }
    else
    {
        return x2;
    }
}

/**
 * @brief  pick the larger of the two input
 *
 * @param[in] x1 input 1
 * @param[in] x2 input 2
 *
 * @return return the larger of the two input
 */
template <typename M, typename N>
M Max(M x1, N x2)
{
    if (x1 >= x2)
    {
        return x1;
    }
    else
    {
        return x2;
    }
}

/**
 * @brief  calculate the intersection of path and line segment
 *
 * @param[in] path path
 * @param[in] s start of line segment
 * @param[in] e end of line segment
 *
 * @return the sequence number of the path at the intersection of the path and the line segment， if no intersection,
 * return -1
 */
int32_t LineCrossPointID(std::vector<CurvePoint> const& path, CurvePoint s, CurvePoint e);

/**
 * @brief  determine whether two line segments intersect
 *
 * @param[in] a start of line segment1
 * @param[in] b end of line segment1
 * @param[in] c start of line segment2
 * @param[in] d end of line segment2
 *
 * @return determine whether two line segments intersect，if intersect，return true, else return false
 */
bool_t LineCross(CurvePoint a, CurvePoint b, CurvePoint c, CurvePoint d);

/**
 * @brief  calculate the shortest distance from the point to the path (considering the direction)
 *
 * @param[in] tmp_point the point
 * @param[in] tmp_line the path
 * @param[in] min_index end of line segment
 *
 * @return the sequence number of the path located closest to the point
 */
float64_t CalculatePointDistanceToLineWithDirection(CurvePoint                     tmp_point,
                                                    std::vector<CurvePoint> const& tmp_line,
                                                    int32_t&                       min_index);

/**
 * @brief  rotation
 *
 * @param[in] source source point
 * @param[in] theta  theta
 *
 * @return point after rotation
 */
Eigen::Vector3f CoordinateTransRotation(Eigen::Vector3f source, float64_t theta);

/**
 * @brief  translation
 *
 * @param[in] source source point
 * @param[in] basedata reckon data
 *
 * @return point after translation
 */
Eigen::Vector3f CoordinateTranslation(Eigen::Vector3f source, Eigen::Vector3f basedata);

/**
 * @brief  update path data according to reckon data
 *
 * @param[out] current_path current_path updated
 * @param[in] reckon_data reckon data
 */
void UpdatePathData(std::vector<CurvePoint>& current_path, Eigen::Vector3f const& reckon_data);

/**
 * @brief  update path data according to reckon data
 *
 * @param[out] current_path current_path updated
 * @param[in] pose vehicle pose
 * @param[in] last_pose vehicle last pose
 */

void UpdatePathDataBasedOnVehicleWorldCoordinate(std::vector<CurvePoint>& current_path,
                                                 geometry::Pose2 const&   pose,
                                                 geometry::Pose2 const&   last_pose);

/**
 * @brief  calculate curvature based on three points
 *
 * @details
 *          1. curvature = 4*triangleArea/(sideLength1*sideLength2*sideLength3)
 *          2. triangleArea = 1/2*parallelogramArea(by cross multiplication )
 *
 */
void CalculateCurvature(std::vector<CurvePoint>& source_data);

/**
 * @brief  distance from point to line
 *
 * @details consider matrix operation
 *
 * project_x = ((y2 - y1) * (x1 * y2 - x2 * y1) + pow(x2 - x1, 2) * x3 + (x2 - x1) * (y2 - y1) * y3) / (pow(y2 - y1, 2)
 * + pow(x2 - x1,2));
 *
 * project_y = ((x2 - x1) * (x2 * y1 - x1 * y2) + pow(y2 - y1, 2) * y3 + (x2 - x1) * (y2 - y1) * x3) / (pow(y2 - y1, 2)
 * + pow(x2 - x1,2));
 *
 * @param[in] point_a line point
 * @param[in] point_b line point
 * @param[in] point_origin point to calculate
 *
 * @return distance from point_origin to line ab
 */
float64_t DistanceFromPointToLine(PointXY point_a, PointXY point_b, PointXY point_origin);

/**
 * @brief  judge point position whether on line or on the left/right
 *
 * @details line start from s to e
 *
 * @param[in] s start point
 * @param[in] e end point
 * @param[in] u point waiting for judging
 *
 * @return
 * 0: on line
 * 1: on the right
 * 2: on the left
 * 3: error
 */
uint32_t PointPositionToLine(PointXY s, PointXY e, PointXY u);

/**
 * @brief  Whether the overlapping area exceeds a given ratio
 *
 * @param[in] tmp_rect given rectangle, usually a parkinglot
 * @param[in] ratio given ratio
 *
 * @return yes or not
 */
bool_t IsAreaOverlap(RectCorner tmp_rect, float64_t ratio);

/**
 * @brief  Get the overlapping area ratio
 *
 * @param[in] tmp_rect given rectangle, usually a parkinglot
 *
 * @return the overlapping area ratio
 */
float64_t GetAreaOverlap(RectCorner tmp_rect);

/**
 * @brief  Calculate the corner coordinates of the vehicle
 *
 * @param[in] vehicle_point vehicle pose point
 * @param[in] expand_length expand length
 * @param[in] expand_width expand width
 * @param[in] vehicle_cfg vehicle parameters
 *
 * @return the corner coordinates of the vehicle
 */
std::vector<PointXY> CalculateVehicleCornerPosition(PointXY                      vehicle_point,
                                                    float64_t                    expand_length,
                                                    float64_t                    expand_width,
                                                    config::VehicleConfig const& vehicle_cfg);

/**
 * @brief  Calculate the intersection area of two polygons
 *
 * @param[in] p1 the corner coordinates of the first polygon
 * @param[in] n1 the number of corners of the first polygon
 * @param[in] p2 the corner coordinates of the second polygon
 * @param[in] n2 the number of corners of the second polygon
 *
 * @return the intersection area of two polygons
 */
float64_t IntersectArea(PointXY* p1, int32_t n1, PointXY* p2, int32_t n2);

/**
 * @brief  Calculate the area of a polygon
 *
 * @param[in] ps the corner coordinates of the polygon
 * @param[in] n the number of corners of the polygon
 *
 * @return the area of a polygon
 */
float64_t Area(PointXY* ps, int32_t n);

/**
 * @brief  Calculate the intersection area of two triangles
 *
 * @param[in] a the corner coordinate of the first triangle
 * @param[in] b the corner coordinate of the first triangle
 * @param[in] c the corner coordinate of the second triangle
 * @param[in] d the corner coordinate of the second triangle
 *
 * @return the intersection area of two triangles
 */
float64_t IntersectArea(PointXY a, PointXY b, PointXY c, PointXY d);

/**
 * @brief  Judge positive and negative
 *
 * @param[in] d the value
 *
 * @return 1 if positive, -1 if negative
 */
int32_t Sig(float64_t d);

/**
 * @brief  Computes the cross product of vector a and b
 *
 * @param[in] o origin point
 * @param[in] a vector a
 * @param[in] b vector b
 *
 * @return the cross product of vector a and b
 */
float64_t Cross(PointXY o, PointXY a, PointXY b);

/**
 * @brief  Calculate the corner points of the polygon divided by the line segment a b
 *
 * @param[out] p the corner points of the polygon divided by the line segment a b
 * @param[out] n the number of corners of the polygon
 * @param[in] a point a
 * @param[in] b point b
 *
 * @return the cross product of vector a and b
 */
void PolygonCut(PointXY* p, int32_t& n, PointXY a, PointXY b);

/**
 * @brief  determine whether two lines intersect and calculate intersection coordinates
 *
 * @param[in] a start of line segment1
 * @param[in] b end of line segment1
 * @param[in] c start of line segment2
 * @param[in] d end of line segment2
 * @param[out] p intersection
 *
 * @return  if coincide return 2, if intersect，return 1, else return 0
 */
int32_t LineCross(PointXY a, PointXY b, PointXY c, PointXY d, PointXY& p);

/**
 * @brief  Calculate the distance from a point with x and y coordinates to the origin
 *
 * @param[in] x x coordinate
 * @param[in] y y coordinate
 *
 * @return the distance from a point with x and y coordinates to the origin
 */
float64_t Distance(float64_t x, float64_t y);

/**
 * @brief  Calculate the distance between two points
 *
 * @param[in] x1 x coordinate of point1
 * @param[in] y1 y coordinate of point1
 * @param[in] x2 x coordinate of point2
 * @param[in] y2 y coordinate of point2
 *
 * @return the distance between two points
 */
float64_t Distance(float64_t x1, float64_t y1, float64_t x2, float64_t y2);

/**
 * @brief  Calculate the distance between two points
 *
 * @param[in] point1 point1
 * @param[in] point2 point2
 *
 * @return the distance between two points
 */
float64_t Distance(PointXY point1, PointXY point2);

/**
 * @brief  Calculate the angle between two lines according to the law of cosines
 *
 * @param[in] s_a start of a
 * @param[in] e_a end of a
 * @param[in] s_b start of b
 * @param[in] e_b end of b
 *
 * @return the angle between two lines according to the law of cosines
 */
float64_t AngleBetweenLines(PointXY s_a, PointXY e_a, PointXY s_b, PointXY e_b);

/**
 * @brief  Determine if a point is inside a rectangle
 *
 * @param[in] point given point
 * @param[in] rect given rectangle
 *
 * @return true if a point is inside a rectangle, else false
 */
bool_t IsPointInRectangle(PointXY const& point, RectCorner const& rect);

/**
 * @brief  Calculate the cross product
 *
 * @param[in] p1 given start point
 * @param[in] p2 given point
 * @param[in] p3 given point
 *
 * @return the cross product
 */
float64_t CrossProd(PointXY const& p1, PointXY const& p2, PointXY const& p3);

/**
 * @brief Judge if a point is in a polygon or not
 *
 * @param[in] point a given point
 * @param[in] polygon a given polygon
 *
 * @return point in the polygon or not
 */
bool_t IsPointInPolygon(PointXY point, std::vector<PointXY> polygon);

/**
 * @brief Remove duplicate curve point
 *
 * @param[out] source_data a given set of curve point
 * @param[in] threshold threshold
 */
void RemoveDuplicateCurvePoint(std::vector<CurvePoint>& source_data, float64_t threshold);

/**
 * @brief Normalize the angle between -PI and PI
 *
 * @param[in] angle given angle
 *
 * @return the angle between -PI and PI
 */
float64_t NormalizeAngle(const float64_t angle);

/**
 * @brief Find the index of the closest point on the curve
 *
 * @param[in] pose current pose
 * @param[in] path given path
 * @param[in] min_index min index of point
 * @param[in] max_index max index of point
 *
 * @return the index of the closest point
 */
size_t GetNearestIndex(geometry::Pose2 pose, std::vector<CurvePoint> const& path, size_t min_index, size_t max_index);

}  // namespace planning
}  // namespace holo

#endif
