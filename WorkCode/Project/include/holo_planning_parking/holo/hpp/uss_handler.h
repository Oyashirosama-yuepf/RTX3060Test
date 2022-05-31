/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file uss_handler.h
 * @brief the header of uss handler
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2020-03-15
 */

#ifndef _HPP_USS_HANDLER
#define _HPP_USS_HANDLER

#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_list.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

namespace holo
{
namespace planning
{
class UssHandler
{
public:
    typedef holo::ObstacleGeneralT<holo::float32_t> Obstacle;
    typedef std::shared_ptr<Obstacle>               ObstaclePtr;
    typedef holo::ObstaclePtrListT<Obstacle>        ObstacleList;
    typedef std::shared_ptr<ObstacleList>           ObstacleListPtr;

public:
    /**
     * @brief Generate obstacles of uss
     *
     * @param[in] range Ranges in raw data
     * @param[in] free_space Free spaces in raw data
     * @param[out] generated_obstacles Generated obstacles from range and free space
     */
    static bool GenerateObstacles(const ObstacleListPtr& range,
                                  const ObstacleListPtr& free_space,
                                  ObstacleListPtr&       generated_obstacles);

private:
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
    static void CoordinateTransformFrom(cv::Point                     new_origin,
                                        const std::vector<cv::Point>& old_obs,
                                        std::vector<Point2f>&         new_obs);

    /**
     * @brief Coordinate transform from point to cv
     *
     * @param[in] new_origin Center point defined in image
     * @param[in] old_obs Obstacle in point format
     * @param[out] new_obs Obstacle in cv format
     */
    static void CoordinateTransformTo(cv::Point                   new_origin,
                                      const std::vector<Point2f>& old_obs,
                                      std::vector<Point2f>&       new_obs);
};
}  // namespace planning
}  // namespace holo
#endif