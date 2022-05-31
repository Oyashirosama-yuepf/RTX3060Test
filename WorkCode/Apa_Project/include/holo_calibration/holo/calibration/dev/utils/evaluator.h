/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file evaluator.h
 * @brief a tool providing static functions to evaluate error for each calibration algorithm
 * @author Shuaijie Li @ lishuaijie@holomatic.com
 * @date 2022-02-14
 */

#ifndef HOLO_CALIBRATION_DEV_UTILS_EVALUATOR_H_
#define HOLO_CALIBRATION_DEV_UTILS_EVALUATOR_H_

#include <holo/calibration/dev/common_types.h>

namespace holo
{
namespace calibration
{
using namespace holo::calibration::camera;
/**
 * @brief functions to compute errors
 */
class Evaluator
{
public:
    /**
     * @brief evaluate average projection error
     *
     * @param[in] multi_point_correspondences multi point correspondences contain 3D-2D pairs
     * @param[in] wTc pose of camera in  world frame
     * @param[in] intrinsic intrinsic of the camera
     *
     * @return average projection error, the evaluation failed if the average projection error is smaller than 0
     */
    static Scalar EvaluateProjectionError(std::vector<PointCorrespondence> const& multi_point_correspondences,
                                          Pose3 const& wTc, CameraIntrinsicBase const& intrinsic);

    /**
     * @brief evaluate projection for one 3D-2D pair
     *
     * @param[in] point_correspondence point correspondence contains a 3D-2D pair
     * @param[in] wTc pose of camera in  world frame
     * @param[in] intrinsic intrinsic of the camera
     *
     * @return projection error, the evaluation failed if the first is false
     */
    static std::pair<bool_t, Scalar> EvaluateProjectionError(PointCorrespondence const& point_correspondence,
                                                             Pose3 const& wTc, CameraIntrinsicBase const& intrinsic);

    /**
     * @brief evaluate average projection error
     *
     * @param[in] multi_object_points multi 3d points in world frame
     * @param[in] multi_image_points multi 2d points in image plane
     * @param[in] wTc pose of camera in  world frame
     * @param[in] intrinsic intrinsic of the camera
     *
     * @return average projection error, the evaluation failed if the average projection error is smaller than 0
     */
    static Scalar EvaluateProjectionError(std::vector<Point3> const& multi_object_points,
                                          std::vector<Point2> const& multi_image_points, Pose3 const& wTc,
                                          CameraIntrinsicBase const& intrinsic);

    /**
     * @brief evaluate projection for one 3D-2D pair
     *
     * @param[in] object_point 3d point in world frame
     * @param[in] image_point 2d point in image plane
     * @param[in] wTc pose of camera in  world frame
     * @param[in] intrinsic intrinsic of the camera
     *
     * @return projection error, the evaluation failed if the first is false
     */
    static std::pair<bool_t, Scalar> EvaluateProjectionError(Point3 const& object_point, Point2 const& image_point,
                                                             Pose3 const& wTc, CameraIntrinsicBase const& intrinsic);

    /**
     * @brief project the 3d point in world frame on the image
     *
     * @param[in] object_point 3d point in world frame
     * @param[in] wTc pose of camera in  world frame
     * @param[in] intrinsic intrinsic of the camera
     *
     * @return projection result, the projection failed if the first is false
     */
    static std::pair<bool_t, CvPoint2f> ProjectPoint(CvPoint3f const& object_point, Pose3 const& wTc,
                                                     CameraIntrinsicBase const& intrinsic);

    /**
     * @brief project the 3d point in world frame on the image
     *
     * @param[in] object_point 3d point in world frame
     * @param[in] wTc pose of camera in  world frame
     * @param[in] intrinsic intrinsic of the camera
     *
     * @return projection result, the projection failed if the first is false
     */
    static std::pair<bool_t, Point2> ProjectPoint(Point3 const& object_point, Pose3 const& wTc,
                                                  CameraIntrinsicBase const& intrinsic);
};  // Evaluator

}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_DEV_UTILS_EVALUATOR_H_

