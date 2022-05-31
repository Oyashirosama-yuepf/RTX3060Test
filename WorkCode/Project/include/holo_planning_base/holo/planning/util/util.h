/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2017-08-11
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_UTIL_H_
#define _HOLO_PLANNING_UTIL_H_

#include <string>

#include <holo/common/path.h>
#include <holo/core/types.h>
#include <holo/geometry/pose2.h>

#include <holo/planning/common/car_road_state.h>
#include <holo/planning/common/curve_point.h>
#include <holo/planning/common/plan_route.h>

namespace holo
{
namespace planning
{
bool_t IsAbsolutePath(const std::string& path);

float64_t CalcKinematicBicycleCurvature(float64_t velocity, float64_t wheelbase, float64_t heading, float64_t thta);
float64_t
CalcKinematicBicycleCurvatureSimp(float64_t velocity, float64_t wheelbase, float64_t heading, float64_t tan_thta);

float64_t CalcRotateAngleFromX(float64_t x, float64_t y);
float64_t CalcAngleDifference(float64_t angle1, float64_t angle2);

bool_t TranslatePath(holo::common::Path& path, const geometry::Pose2d& pose);

bool_t TranslatePath(PublishedPath& path, const geometry::Pose2d& pose);

bool_t TranslatePath(std::vector<geometry::Point3d>& path,
                     const geometry::Pose3d&         pose,
                     std::vector<geometry::Point3d>& points,
                     bool_t                          cut     = false,
                     bool_t                          forward = true);

/**
 * @brief      Smooth the target_value by cutting it with step_length
 *
 * @param[in]  reference_value  The reference value of smooth
 * @param      input_value      The value before smooth
 * @param      step_length      The step length of smooth
 *
 * @return     The smoothed value.
 */
float64_t SmoothByStepLength(float64_t reference_value, float64_t input_value, float64_t step_length);

float64_t Mod2Pi(float64_t x);
float64_t ModSignPi(float64_t x);
bool_t    IsPointInPolygon(const geometry::Point2& point, const std::vector<std::vector<geometry::Point2>>& polygons);
bool_t    IsPointInPolygonWithIdx(const geometry::Point2&                           point,
                                  const std::vector<std::vector<geometry::Point2>>& polygons,
                                  size_t&                                           idx);
float64_t AngleOf(const geometry::Point2& s, const geometry::Point2& d);

float64_t InnerProd(const float64_t x0, const float64_t y0, const float64_t x1, const float64_t y1);

void      UniformSlice(const float64_t start, const float64_t end, const uint32_t num, std::vector<float64_t>* sliced);
float64_t ComputeCurvature(const float64_t dx, const float64_t d2x, const float64_t dy, const float64_t d2y);
float64_t ComputeCurvatureDerivative(const float64_t dx,
                                     const float64_t d2x,
                                     const float64_t d3x,
                                     const float64_t dy,
                                     const float64_t d2y,
                                     const float64_t d3y);

/**
 * @brief This function can find the closest point from points_set.
 *
 * @param[in] target The target point used to find the closest point.
 * @param[in] points_set The points set to find the closest point.
 * @param[in] start_index This function will start to find at this index.
 * @param[out] closest_index The index of the closest point.
 *
 * @return true if find successfully, false otherwise
 */
bool_t GetClosestPointFromPointsSet(const geometry::Point2d&              target,
                                    const std::vector<geometry::Point2d>& points_set,
                                    uint32_t                              start_index,
                                    uint32_t&                             closest_index);

/**
 * @brief Calc the lane width according the two set of vectors of lane line points
 * @details The return vector of width has direction, that is:
 *          a width pointing to the right side from the left lane is -;
 *          a width pointing to the left side from the right lane is +.
 *
 * @param reliable_line The reliable lane line
 * @param biased_line The biased lane line
 *
 * @return     bool: succeed or not
 */
bool_t CalcLaneWidth(const std::vector<CurvePoint>& reliable_line,
                     const std::vector<CurvePoint>& biased_line,
                     std::vector<float64_t>&        lane_width);
/**
 * @brief Calculate the center line from a reliable lane line and the corresponding lane widths
 * @details Assumption: 1. 2 dimensional space;
 *                      2. vehicle position will not be perpendicular to the lane lines;
 *                      3. input point number in the two sets are equal;
 *                      4. this method should be stable, as long as the input feature error is bounded and not too large
 *
 * @param reliable_line The reliable lane line
 * @param lane_width Lane width at each point in the reliable_line
 * @param ref_path Generated center line
 *
 * @return bool: indicating whether or not successfully generating center line
 */

bool_t GenerateMidLine(const std::vector<CurvePoint>& reliable_line,
                       const std::vector<float64_t>&  lane_width,
                       std::vector<CurvePoint>&       ref_path);

/**
 * @brief Calculate the center line from two lane lines
 * @details Assumption: 1. 2 dimensional space;
 *                      2. vehicle position will not be perpendicular to the lane lines;
 *                      3. input point number in the two sets are equal;
 *                      4. for any 0 <= i < size, the pair left[i] and right[i] should be close to "a pair that could
 *                         generate the mid point of two curve".
 *
 * @param left_line Left lane line
 * @param right_line Right Lane Line
 * @param ref_path Generated center line
 *
 * @return bool: indicating whether or not successfully generating center line
 */
bool_t GenerateMidLine(const std::vector<CurvePoint>& left_line,
                       const std::vector<CurvePoint>& right_line,
                       std::vector<CurvePoint>&       ref_path);
/**
 * @brief Calculate the tan line, kappa, dkappa of a set discretilized points separately
 * @details Assumption: y could be written in the function with x: y = f(x);
 *                      the curve is not represented by a set of parametric equations
 *                      Currently a very brief version is provided, a more beautiful method with higher order of
 * accurancy using matrix calculus will be provided later
 *
 * @param ref_path Generated center line
 *
 * @return bool: succeed or not
 */
bool_t NumericalCurvature(std::vector<CurvePoint>& ref_path);

bool_t RectangleIsOverlap(float64_t s_max_1,
                          float64_t s_min_1,
                          float64_t l_max_1,
                          float64_t l_min_1,
                          float64_t s_max_2,
                          float64_t s_min_2,
                          float64_t l_max_2,
                          float64_t l_min_2);

// use a rectangle area to select obs from obstacles_aggregate_
std::vector<std::shared_ptr<ObstacleInfo>>
SelectObsByRectangle(float64_t s_max, float64_t s_min, float64_t l_max, float64_t l_min, PlanRoute& route);

common::Timestamp GetTimestampNow(void);

float64_t CalFrenetS(float64_t t, std::shared_ptr<math::Curve1d> curve);

template <typename T>
bool_t WithinRange(const T v, const T lower, const T upper)
{
    return lower <= v && v <= upper;
}

/**
 * @brief Calculate the distance from the point to the curve
 * @details The curve should be a convex or concave one
 *
 * @param pt The point
 * @param curve The curve
 *
 * @return The distance fromt the point to the curve, if curve is empty, return 0.0
 */
float64_t CalDistFromPoint2Curve(CurvePoint const& pt, std::vector<CurvePoint> const& curve);

/**
 * @brief Query the index in a Path by position
 *
 * @param path The path to be queried
 * @param pos_x The position's x value
 * @param pos_y The position's y value
 *
 * @return The index of position(pos_x, pos_y)
 */
uint32_t QueryNearestPoint(common::Path const& path, float64_t pos_x, float64_t pos_y);

/**
 * @brief Query lower bound point's index.
 *
 * @param relative_time The relative time.
 * @param epsilon The tiny bias.
 *
 * @return The index which matches lower bound point.
 */
uint32_t QueryLowerBoundPoint(common::Path const& path, float64_t relative_time, float64_t epsilon = 0.05);

bool_t GetPointByRelativeTime(common::PathPoint&  point,
                              common::Path const& path,
                              float64_t           relative_time,
                              float64_t           epsilon = 0.00001);

/**
 * @brief Query nearest point's index.
 *
 * @param pose The pose in odometry.
 *
 * @return The index which matches nearest point.
 */
uint32_t QueryNearestPoint(common::Path const& path, geometry::Pose3d const& pose);

/**
 * @brief Calculate the ego's curvature
 *
 * @param odometry The odometry
 * @param chassis_state The chassis state
 * @param wheel_base The wheel_base of ego car
 *
 * @return The curvature
 */
float64_t CalEgoCurvature(std::shared_ptr<holo::common::Odometryd>       odometry,
                          std::shared_ptr<common::details::ChassisState> chassis_state,
                          float64_t                                      wheel_base);

/**
 * @brief Transfer CurvePoint Vector into Pathd Type in order to pub reference path
 *
 * @param curve The reference path
 * @param transfered_ref_path The transfered reference path
 *
 * @return False if transfered failed.
 */
bool_t TransferReferencePathToPathd(std::vector<CurvePoint> const& curve, holo::common::Path& transfered_ref_path);

}  // namespace planning
}  // namespace holo

#endif
