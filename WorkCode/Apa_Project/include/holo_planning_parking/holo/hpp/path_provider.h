/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file path_provider.h
 * @brief the header of path provider from path file of odometry
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2020-03-04
 */

#ifndef _HOLO_PLANNING_PATH_PROVIDER_H_
#define _HOLO_PLANNING_PATH_PROVIDER_H_

#include <string>
#include <unordered_map>
#include <vector>

#include <holo/common/odometry.h>
#include <holo/geometry/pose2.h>
#include <holo/parking/map/navigation_road_builder.h>
#include <holo/parking/map/parking_navigation.h>
#include <holo/planning/common/curve_point.h>

namespace holo
{
namespace planning
{
class PathProvider
{
public:
    using Odometry      = common::Odometryd;
    using MapNavigation = holo::map::ParkingNavigation;

    /**
     * @brief Constructor
     */
    PathProvider();

    /**
     * @brief Deconstructor
     */
    virtual ~PathProvider()
    {
    }

    /**
     * @brief Path processing from odometry and front wheel angle
     *
     * @param odometry_vector Odometry vector
     * @param front_wheel_angle_map Front wheel angle map
     */
    bool PathProcessing(const std::vector<Odometry>&                   odometry_vector,
                        const std::unordered_map<uint64_t, float64_t>& front_wheel_angle_map);

    /**
     * @brief Path processing from files which contain odometry and front wheel angle file
     *
     * @param odometry_file File path of odometry infos
     * @param front_wheel_angle_file File path of front wheel angle infos
     */
    bool PathProcessing(const std::string& odometry_file, const std::string& front_wheel_angle_file);

    /**
     * @brief Path processing from path number which can get odometry and front wheel angle file
     *
     * @param path_number Path number
     */
    bool PathProcessing(uint32_t path_number);

    /**
     * @brief Path processing from path number which can get odometry and front wheel angle file
     *
     * @param path_number Path number
     * @param is_discrete Whether is discrete operation
     */
    bool PathProcessing(uint32_t path_number, bool is_discrete);

    /**
     * @brief Path processing, format transform NavigationRoadPoint to CurvePoint
     *
     * @param navigation_points The map::NavigationRoadPoint points
     */
    bool PathProcessing(const MapNavigation navigation_point);

    /**
     * @brief Path split processing, format transform NavigationRoadPoint to CurvePoint
     *
     * @param navigation_points The map::NavigationRoadPoint points (hpa)
     * @param direction The driving direction (hpa)
     */
    bool PathProcessing(const MapNavigation navigation_point, bool_t current_direction, geometry::Pose2 pose);

    /**
     * @brief Path postprocessing
     */
    bool PathPostProcessing();

    /**
     * @brief Smooth the start path segment by current pose
     *
     * @param path Path point.
     * @param pose Current pose.
     * @param forward Forward(true) or backward(false).
     */
    bool SmoothStartPathSegment(std::vector<CurvePoint>& path, geometry::Pose2 pose, bool forward);

    /**
     * @brief Reset path information
     */
    void ResetPathInfo();

    /**
     * @brief smooth and start_zero_speed_path
     */
    bool SmooStart(geometry::Pose2 pose);

private:
    /**
     * @brief Load steering ratio table file
     *
     * @param load_file Load file direction
     */
    bool LoadSteeringRatioTable(const std::string& load_file);

    /**
     * @brief Get steering ratio value
     *
     * @param steering_angle Steering angle
     */
    float64_t GetSteeringRatioValue(const float64_t& steering_angle);

    /**
     * @brief Read path from odometry vector
     *
     * @param odometry_vector Odometry vector
     * @param front_wheel_angle_map Front wheel angle map
     */
    bool PathReader(const std::vector<Odometry>&                   odometry_vector,
                    const std::unordered_map<uint64_t, float64_t>& front_wheel_angle_map);

    /**
     * @brief Smooth piecewise path
     */
    bool PathSmoother();

    /**
     * @brief Add zero speed points in path end
     *
     * @param path Path to be traited
     * @param forward forward
     */
    void AddZeroSpeedPointsInEndOfPath(std::vector<CurvePoint>& path, bool forward);

    /**
     * @brief Add zero speed points in path start
     *
     * @param path Path to be traited
     * @param forward forward
     */
    void AddZeroSpeedPointsInStartOfPath(std::vector<CurvePoint>& path, bool forward);

    /**
     * @brief Generate the turning check list from the path
     *
     * @param path Path to be traited
     * @param forward forward
     */
    void GenerateTurningCheckList(const std::vector<CurvePoint>& path, bool forward);

    /**
     * @brief Load odometry from file
     *
     * @param file_path File path of odometry infos
     */
    std::vector<Odometry> LoadOdometry(const std::string& file_path);

    /**
     * @brief Load front wheel angle from file
     *
     * @param file_path File path of front wheel angle infos
     */
    std::unordered_map<uint64_t, float64_t> LoadFrontWheelAngle(const std::string& file_path);

    /**
     * @brief Compute curvature from front wheel angle
     *
     * @param front_wheel_angle_map Front wheel angle map
     * @param stamp TimeStamp used as index to find related front wheel angle
     */
    float64_t ComputeCurvature(const std::unordered_map<uint64_t, float64_t>& front_wheel_angle_map, uint64_t stamp);

    /**
     * @brief Calculate map path nearest distance by current pose
     *
     * @param navigation_points The map::NavigationRoadPoint points (hpa)
     * @param pose Current pose.
     */
    float64_t GetMapNearestDistanceSquare(const MapNavigation navigation_point, geometry::Pose2 pose, size_t& index);

    /**
     * @brief Generate the junction road point indexs in the path
     */
    void GenerateRoadJunctionPointIndex();

    /**
     * @brief Smooth the crossing path
     *
     * @param navigation_points The map::NavigationRoadPoint points
     * @param start_index The start path points index
     * @param end_index The end path points index
     * @param raw_path The navigation conversion path
     *
     * @return The smooth path
     */
    std::vector<CurvePoint> SmoothCrossing(const MapNavigation            navigation_point,
                                           size_t                         start_index,
                                           size_t                         end_index,
                                           const std::vector<CurvePoint>& raw_path);

    /**
     * @brief Process crossing
     *
     * @param navigation_points The map::NavigationRoadPoint points
     * @param raw_path The navigation conversion path
     *
     * @return The processed path
     */
    std::vector<CurvePoint> ProcessCrossing(const MapNavigation            navigation_point,
                                            const std::vector<CurvePoint>& raw_path);

public:
    std::vector<std::vector<CurvePoint>> piecewise_paths_;     ///< piecewise paths
    std::vector<std::vector<bool>>       turning_check_list_;  ///< turning check list
    std::vector<std::vector<uint8_t>>    path_state_list_;     ///< 0:turn;1:straight;2:turn->straight;3:straight->turn
    std::vector<bool>                    forward_;             ///< piecewise paths forward property
    std::vector<std::vector<CurvePoint>> road_junction_points_;
    std::vector<std::vector<size_t>>     road_junction_start_end_pointidxs_;

    uint32_t  path_total_size_ = 0;           ///< path total size
    float64_t smooth_step_;                   ///< smooth step
    float64_t discrete_step_;                 ///< discrete step
    bool      is_discrete_ = false;           ///< whether is discrete operation
    float64_t start_zero_speed_path_length_;  ///< zero speed path length in path start
    float64_t end_zero_speed_path_length_;    ///< zero speed path length in path end

private:
    bool      front_wheel_angle_left_negative_ = false;  /// front wheel angle left is negative
    bool      use_spline_curvature_;                     ///< compute curvature by spline interpolation
    bool      is_steer_feedback_;
    float64_t steer_ratio_;
    float64_t wheel_base_;                  ///< wheel_base
    float64_t vehicle_width_;               ///< vehicle width
    float64_t max_localization_tolerance_;  ///< supposed max localization telerance
    float64_t min_adjacent_distance_;       ///< min adjacent distance

    float64_t turn_curvature_        = 0.05;  ///< turn curature threshold
    uint32_t  turn_front_expand_num_ = 30;    ///< turn front expand point num
    uint32_t  turn_back_expand_num_  = 20;    ///< turn back expand point num
    uint32_t  turn_valid_num_        = 4;     ///< turn min valid point num

    std::vector<std::pair<float64_t, float64_t>> steering_ratio_table_;  ///< steering ratio table
};
}  // namespace planning
}  // namespace holo
#endif
