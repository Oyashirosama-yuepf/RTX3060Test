/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file graph_processing.h
 * @brief the header of graph processing to handle freespace of monocular
 * @author zhangjie(zhangjie@holomatic.com)
 * @date 2020-03-04
 */

#ifndef _HOLO_PLANNING_GRAPH_PROCESSING_H_
#define _HOLO_PLANNING_GRAPH_PROCESSING_H_

#include <holo/hpp/hpp_car_road_state.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

namespace holo
{
namespace planning
{
class GraphProcessing
{
    using FreeSpacePtr = std::shared_ptr<common::AutoFreespace<geometry::Point3f>>;
    using polygon      = std::vector<geometry::Point2>;
    using polygons     = std::vector<polygon>;

public:
    /**
     * @brief Handle and classify obstacles from free spaces
     *
     * @param[in] min_valid_obstacle_area Min area for a valid obstacle
     * @param[in] raw_data Raw data
     * @param[out] free_spaces Free spaces in raw data
     * @param[out] ranges Ranges in raw data
     * @param[out] free_spaces_fusioned_obstacles Fusioned obstacles
     * @param[out] non_free_spaces_obstacles Non-free spaces in raw data
     */
    static void HandleAndClassifyObstaclesFromFreeSpaces(float64_t           min_valid_obstacle_area,
                                                         const FreeSpacePtr& raw_data,
                                                         polygons&           free_spaces,
                                                         polygons&           ranges,
                                                         polygons&           free_spaces_fusioned_obstacles,
                                                         polygons&           non_free_spaces_obstacles);

    /**
     * @brief Handle and classify obstacles from free spaces
     *
     * @param[in] raw_data Raw data
     * @param[out] free_spaces Free spaces in raw data
     */
    static void HandleFreeSpacesContour(const FreeSpacePtr& raw_data, polygons& free_spaces);
private:
    /**
     * @brief Convert free spaces to common obstacles
     *
     * @param[in] min_valid_obstacle_area Min area for a valid obstacle
     * @param[in] free_spaces Free spaces in raw data
     * @param[in] ranges Ranges in raw data
     * @param[out] fp_obs Fusioned obstacles
     */
    static void GetFinalObstacleBeyondFreeSpace(float64_t       min_valid_obstacle_area,
                                                const polygons& free_spaces,
                                                const polygons& ranges,
                                                polygons&       fp_obs);

    /**
     * @brief Find contours from gray image
     *
     * @param[in] src_gray Source gray image
     * @param[out] output_contours contours generated
     */
    static void ThreshFindContours(cv::Mat& src_gray, std::vector<std::vector<cv::Point>>& output_contours);

    /**
     * @brief Coordinate transform from cv to point
     *
     * @param[in] new_origin Center point defined in image
     * @param[in] old_obs Obstacle in cv format
     * @param[out] new_obs Obstacle in point format
     */
    static void CoordinateTransformFrom(cv::Point new_origin, const std::vector<cv::Point>& old_obs, polygon& new_obs);
    /**
     * @brief Coordinate transform from point to cv
     *
     * @param[in] new_origin Center point defined in image
     * @param[in] old_obs Obstacle in point format
     * @param[out] new_obs Obstacle in cv format
     */
    static void CoordinateTransformTo(cv::Point new_origin, const polygon& old_obs, std::vector<cv::Point>& new_obs);

    /**
     * @brief Remove frame contour
     *
     * @param contours contours to be traited
     */
    static void DeleteContourWithMaxArea(std::vector<std::vector<cv::Point>>& contours);

    /**
     * @brief Remove countours that contained by others
     *
     * @param contours contours to be traited
     */
    static void EliminateContourByContained(std::vector<std::vector<cv::Point>>& contours);
};

}  // namespace planning
}  // namespace holo

#endif