/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file collision_checker.h
 * @brief the header of collision checker
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2019-12-13
 */

#ifndef _HPP_COLLISION_CHECKER
#define _HPP_COLLISION_CHECKER

#include <holo/geometry/box2.h>
#include <holo/geometry/pose2.h>
#include <holo/hpp/scenario/scenario_hpp_struct.h>
#include <holo/planning/common/config/vehicle_config.h>
#include <holo/planning/common/curve_point.h>
#include <holo/planning/util/util.h>

namespace holo
{
namespace planning
{
struct Circle
{
    float64_t pos_x;
    float64_t pos_y;
    float64_t radius;
};

class CollisionChecker
{
    using ObstacleGeneral =
        std::shared_ptr<holo::obstacle::ObstaclePtrListT<holo::obstacle::ObstacleGeneralT<holo::float32_t>, 128UL>>;

public:
    /**
     * @brief Constructor
     */
    CollisionChecker();

    /**
     * @brief Set parameter
     *
     * @param[in] vehicle_cfg config to init accelerate and decelerate
     */
    void SetParam(config::VehicleConfig const& vehicle_cfg);

    /**
     * @brief Reset the collision checker's path
     *
     * @param path Path to be traited
     * @param interval_distance interval s for check object
     * @param end_distance Max s to be checked
     * @param lateral_buffer Lateral buffer in check
     * @param max_check_distance Max check distance
     * @param pose Current pose
     */
    void Reset(std::vector<CurvePoint> const& path,
               float64_t                      interval_distance,
               float64_t                      end_distance,
               float64_t                      lateral_buffer,
               float64_t                      max_check_distance,
               geometry::Pose2 const&         pose);

    /**
     * @brief Reset the collision checker's path by circle
     *
     * @param path Path to be traited
     * @param interval_distance interval s for check object
     * @param end_distance Max s to be checked
     * @param lateral_buffer Lateral buffer in check
     * @param max_check_distance Max check distance
     * @param max_radius Max circle radius
     * @param pose Current pose
     */
    void ResetByCircle(std::vector<CurvePoint> const& path,
                       float64_t                      interval_distance,
                       float64_t                      end_distance,
                       float64_t                      lateral_buffer,
                       float64_t                      max_check_distance,
                       geometry::Pose2 const&         pose);

    /**
     * @brief Check the distance of nearest obstacle from the first point of path
     *
     * @param obstacles Obstacles to be considered
     *
     * @return nearest obstacle distance
     */
    float64_t ObstaclesCollisionCheck(std::vector<std::vector<geometry::Point2>> const& obstacles);

    /**
     * @brief Check the distance of nearest obstacle from the first point of path
     *
     * @param obstacles Obstacles to be considered
     * @param obstacles_type Obstacles type
     *
     * @return nearest obstacle distance
     */
    float64_t ObstaclesCollisionCheck(
        std::vector<std::vector<geometry::Point2>> const&                                obstacles,
        std::vector<std::pair<Classification::MainType, Classification::SubType>> const& obstacles_type);

    /**
     * @brief Check the distance of nearest obstacle from the first point of path
     *
     * @param obstacles Obstacles to be considered
     *
     * @return nearest obstacle distance
     */
    float64_t ObstaclesCollisionCheckByCircle(
        std::vector<std::vector<geometry::Point2>> const&                                obstacles,
        std::vector<std::pair<Classification::MainType, Classification::SubType>> const& obstacles_type);

    /**
     * @brief Check the distance of nearest obstacle from the first point of path
     *
     * @param[in] obstacles Obstacles to be considered
     * @param[in] obstacles_type Obstacles type to be considered
     * @param[in] obstacle_motion_status Obstacles motion status
     * @param[out] has_dynamic_obstacle True if it has dynamic obstacle.
     *
     * @return nearest obstacle distance
     */
    float64_t ObstaclesCollisionCheckByCircle(
        const ObstacleGeneral&                                                           obstacle_general,
        std::vector<std::vector<geometry::Point2>> const&                                obstacles,
        std::vector<std::pair<Classification::MainType, Classification::SubType>> const& obstacles_type,
        std::vector<holo::obstacle::details::MotionStatus> const&                        obstacle_motion_status,
        ObstacleType&                                                                    obstacle_type);

    /**
     * @brief Check the distance of nearest obstacle from the first point of path
     *
     * @param[in] obstacles Obstacles to be considered
     * @param[in] obstacles_type Obstacles type to be considered
     * @param[in] obstacle_motion_status Obstacles motion status
     * @param[out] has_dynamic_obstacle True if it has dynamic obstacle.
     *
     * @return nearest obstacle distance
     */
    float64_t ObstaclesCollisionCheck(
        const ObstacleGeneral&                                                           obstacle_general,
        std::vector<std::vector<geometry::Point2>> const&                                obstacles,
        std::vector<std::pair<Classification::MainType, Classification::SubType>> const& obstacles_type,
        std::vector<holo::obstacle::details::MotionStatus> const&                        obstacle_motion_status,
        ObstacleType&                                                                    obstacle_type);

    float64_t ObstaclesCollisionCheck(
        std::vector<std::vector<geometry::Point2>> const&                                obstacles,
        std::vector<std::pair<Classification::MainType, Classification::SubType>> const& obstacles_type,
        bool&                                                                            has_pedestrian_obstacle);

    /**
     * @brief Check whether there is a collision at vehicle backward distance
     *
     * @param pose Vehicle current pose
     * @param forward_distance The backward distance
     * @param lateral_buffer Lateral buffer in check
     * @param freespaces Freespaces to be considered
     *
     * @return True if no collision happens
     */
    bool ObstaclesCollisionCheckByCircle(geometry::Pose2 const&                            vehicle_pose,
                                         float64_t                                         backward_distance,
                                         float64_t                                         lateral_buffer,
                                         std::vector<std::vector<geometry::Point2>> const& freespaces);

    /**
     * @brief Check the distance of nearest freespace from the first point of path
     *
     * @param[in] freespaces Freespaces to be considered
     * @param[in] expansion_widths Expansion widths
     *
     * @return nearest freespace intersect distance
     */
    std::array<float64_t, 3>
    FreespaceCollisionCheckByCircle(std::vector<std::vector<geometry::Point2>> const& freespaces,
                                    std::array<float64_t, 3>&                         expansion_widths);

    /**
     * @brief Check the distance of nearest freespace from the first point of path
     *
     * @param freespaces Freespaces to be considered
     *
     * @return nearest freespace intersect distance
     */
    float64_t FreespaceCollisionCheckByCircle(std::vector<std::vector<geometry::Point2>> const& freespaces);

    /**
     * @brief Check the distance of nearest freespace from the first point of path
     *
     * @param freespaces Freespaces to be considered
     *
     * @return nearest freespace intersect distance
     */
    float64_t FreespaceCollisionCheck(std::vector<std::vector<geometry::Point2>> const& freespaces);

    /**
     * @brief Check collision according to uss
     *
     * @param obstacles Obstacles to be considered
     *
     * @return True if no collision happens
     */
    bool UssCollisionCheck(std::vector<std::vector<geometry::Point2>> const& obstacles);

    /**
     * @brief Distance from pt to vehicles_
     *
     * @param pt Point to be traited
     *
     * @return Distance from pt to vehicles_, 0.0 if collision exists
     */
    float64_t DistanceToTrajectory(geometry::Point2 const& pt);

private:
    /**
     * @brief Check the dynamic obstacle and opposite comming car
     *
     * @param[in] obstacles_type Obstacles type to be considered
     * @param[in] obstacle_motion_status Obstacles motion status
     * @param[in] subscript The vector subscript
     * @param[out] has_dynamic_obstacle True if it has dynamic obstacle.
     * @param[out] is_opposite_comming_car True if it has opposite comming car.
     *
     * @return nearest obstacle distance
     */
    void
    ObstacleTypeJudge(const ObstacleGeneral&                                                           obstacle_general,
                      std::vector<std::pair<Classification::MainType, Classification::SubType>> const& obstacles_type,
                      std::vector<holo::obstacle::details::MotionStatus> const& obstacle_motion_status,
                      size_t const                                              subscript,
                      ObstacleType&                                             obstacle_type);

    /**
     * @brief Convert rectangle to multi circles
     *
     * @param pt The center position
     * @param theta The heading
     * @param length The length
     * @param width The width
     * @param max_radius The max radius
     *
     * @return True if no collision happens
     */
    std::vector<Circle> ConvertRectangle2Circle(geometry::Point2d const& pt,
                                                float64_t const          theta,
                                                float64_t const          length,
                                                float64_t const          width);

    /**
     * @brief Judge circle and polygon intersect
     *
     * @param circle The circle
     * @param polygon The polygon
     *
     * @return True if no collision happens
     */
    bool_t CirclePolygonIntersect(Circle circle, std::vector<geometry::Point2> polygon);

    /**
     * @brief Judge circle and polygon intersect
     *
     * @param circle The circle
     * @param polygon The polygon
     * @param check_radius The check radius
     * @param check_index The check index
     *
     * @return True if no collision happens
     */
    bool_t CirclePolygonIntersect(Circle                        circle,
                                  std::vector<geometry::Point2> polygon,
                                  std::array<float64_t, 3>&     check_radius,
                                  std::array<bool_t, 3>&        check_flag);

    /**
     * @brief Caculate expansion radius by expansion widths
     *
     * @param[in] expansion_widths Expansion widths
     *
     * @return radius values
     */
    std::array<float64_t, 3> GetCheckRadius(const std::array<float64_t, 3>& expansion_widths);

    /**
     * @brief Convert rectangle to multi circles
     *
     * @param x The point coor x
     * @param x The point coor y
     * @param x1 The segment start point coor x
     * @param y1 The segment start point coor y
     * @param x2 The segment end point coor x
     * @param y2 The segment end point coor y
     *
     * @return True if no collision happens
     */
    float64_t PointToSegDistSquare(float64_t x, float64_t y, float64_t x1, float64_t y1, float64_t x2, float64_t y2);

    /**
     * @brief Fast check Collision between obstacle and vechile
     *
     * @param obstacle The obstacle
     * @param vehicle The vehicle
     *
     * @return True if no collision happens
     */
    bool FastIntersectionCheck(std::vector<geometry::Point2> const&       obstacle,
                               geometry::details::Box2T<float64_t> const& vehicle);
    /**
     * @brief Fast check Collision between vechile and linesegment
     *
     * @param vehicle The vehicle
     * @param obs_seg The LineSegment
     *
     * @return True if no collision happens
     */
    bool FastBoxSegmentIntersectCheck(geometry::details::Box2T<float64_t> const& vehicle,
                                      geometry::LineSegment2d const&             obs_seg);
    /**
     * @brief Check Collision between obstacle and vechile
     *
     * @param obstacle The obstacle
     * @param vehicle The vehicle
     *
     * @return True if no collision happens
     */
    bool ObstacleCollisionCheck(std::vector<geometry::Point2> const&       obstacle,
                                geometry::details::Box2T<float64_t> const& vehicle);

    /**
     * @brief Distance from pt to box
     *
     * @param pt The point
     * @param box The box of vehicle
     *
     * @return The distance
     */
    float64_t DistancePtToBox(geometry::Point2 const& pt, geometry::details::Box2T<float64_t> const box);

    /**
     * @brief Whether is same direction vehicle
     *
     * @param obstacle_general The obstacle data
     * @param index The obstacles index
     *
     * @return True if it is same direction vehicle
     */
    bool_t IsSameDirectionVehicle(ObstacleGeneral obstacle_general, size_t index);

    /**
     * @brief Whether is opposite direction vehicle
     *
     * @param obstacle_general The obstacle data
     * @param index The obstacles index
     *
     * @return @return True if it is opposite direction vehicle
     */
    bool_t IsOppositeDirectionVehicle(ObstacleGeneral obstacle_general, size_t index);

private:
    float64_t                                                              ego_length_;
    float64_t                                                              ego_width_;
    float64_t                                                              shift_distance_;
    float64_t                                                              max_check_distance_ = 0.0;
    geometry::Pose2                                                        pose_;
    std::vector<std::pair<float64_t, geometry::details::Box2T<float64_t>>> vehicles_;
    std::vector<std::pair<float64_t, std::vector<Circle>>>                 vehicle_outline_;
};
}  // namespace planning
}  // namespace holo
#endif
