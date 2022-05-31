/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ipm_convertor.h
 * @brief This header file defines a class convert a 2d point on image to 3d point.
 * Using inverse perspective mapping(IPM)
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2019-12-05"
 */

#ifndef HOLO_PERCEPTION_SPACE_CONVERTOR_IPM_CONVERTOR_H_
#define HOLO_PERCEPTION_SPACE_CONVERTOR_IPM_CONVERTOR_H_

#include <vector>

#include <holo/common/camera_base.h>
#include <holo/core/types.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/matrix_base.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup space_convertor
 *
 * @{
 */

/**
 * @brief This class define methods convert a 2d point to 3d point using IPM.
 * @details The intuition of this method is intersecting a ray and a plane in 3d space.
 * We use a pinhole camera model and place the image plane between camera optical center and real world.
 * The ray is starting from camera optical center and pointing to 2d point on image plane.
 * The ground plane is a plane in ground frame, with Z_ground == 0.('frame' means coordinate system, same below)
 * If we know the pose from ground frame to camera frame, and camera intrinsics
 * then we can intersect the ray and ground plane at 3d point.
 *
 *```
 * camera             | <- image plane
 * optical            |
 * center             |
 *       O------------|
 *             .      |
 *                   .| <- 2d point
 *                    |    .                 --- 3d point
 *                               .           |
 *                                     .     v
 * ==========================================*===================== ground plane
 *
 * ground frame:
 *     ^ Z_ground
 *     |
 *     |______> Y_ground
 *    *
 *   *
 * X_ground
 *
 * camera frame:
 *     Z_camera
 *     *
 *    *_____> X_camera
 *   |
 *   |
 *   v
 *  Y_camera
 *```
 * @tparam Scalar data type
 */
template <typename Scalar>
class IPMConvertor
{
public:
    using ColSizeType = typename MatrixBaseT<Scalar, -1, -1>::ColSizeType;
    using RowSizeType = typename MatrixBaseT<Scalar, -1, -1>::RowSizeType;
    using Point2Type  = holo::geometry::Point2T<Scalar>;
    using Point3Type  = holo::geometry::Point3T<Scalar>;
    using Pose3Type   = holo::geometry::Pose3T<Scalar>;
    /**
     * @brief Convert a 2d point to a 3d point.
     *
     * @param[in] point2 undistorted 2d point on image plane.
     * @param[in] camera the camera model to undistort and unproject 2d points.
     * @param[in] ground2camera_pose ground to camera pose.
     * @param[out] point3 3d point in camera frame.
     *
     * @return bool_t true if the conversion is successful else false.
     *
     * @note The coordinate of this 3d point is in camera frame.
     */
    static bool_t Convert(const Point2Type& point2, const CameraBaseT<Scalar>& camera,
                          const Pose3Type& ground2camera_pose, Point3Type& point3);

    /**
     * @brief Convert a 2d point(in image frame, (u, v, 1)) to a 3d point(in body frame).
     *
     * @param[in] ground_normal_body
     * @param[in] point_uv1 undistorted 2d point on image plane.
     * @param[in] height_camera_ground the height of camera to the ground.
     * @param[in] camera the camera model to undistort and unproject 2d points.
     * @param[in] camera2body_pose camera to body pose.
     * @param[out] point3 3d point in body frame.
     * @return bool_t true if the conversion is successful else false.
     */
    static bool_t Convert2BodyFrame(const numerics::Vector3T<Scalar>& ground_normal_body, const Point3Type& point_uv1,
                                    const Scalar& height_camera_ground, const CameraBaseT<Scalar>& camera,
                                    const Pose3Type& camera2body_pose, Point3Type& point3);
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_SPACE_CONVERTOR_IPM_CONVERTOR_H_
