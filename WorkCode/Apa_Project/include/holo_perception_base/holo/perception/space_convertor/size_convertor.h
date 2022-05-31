/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file size_convertor.h
 * @brief This header file defines a class convert a 2d point on image to 3d point.
 * Using target object size(e.g. car width);
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2019-12-06"
 */

#ifndef HOLO_PERCEPTION_SPACE_CONVERTOR_SIZE_CONVERTOR_H_
#define HOLO_PERCEPTION_SPACE_CONVERTOR_SIZE_CONVERTOR_H_

#include <holo/common/camera_base.h>
#include <holo/core/types.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/numerics/matrix.h>

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
 * @brief This class define methods convert a 2d point to 3d point using target obstacle size.
 * @details This method mainly has two steps.
 * 1. Compute target object distance of Z_camera direction, using target object real size and image size.
 * 2. Compute coordinate of X_camera and Y_camera by target object angle of X_camera and Y_camera direction.
 * The line segment where real size is measured must be parallel to
 * the line segment where image size is measured,
 * and must be perpendicular to Z_camera axis.
 * Distance of Z_camera direction is computed using similar triangle.
 * E.g.
 *```
 * Z_camera
 * ^
 * |
 * |--------------real_size-------------|
 * |                                 .
 * |                              .
 * |                           .
 * |                        .
 * |                     .
 * |----image_size----|       <- image plane
 * |               .
 * |            .
 * |         .
 * |      .
 * |   .
 * O <- camera optical center
 *
 * camera_frame:
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
class SizeConvertor
{
public:
    using Point2Type = holo::geometry::details::Point2T<Scalar>;
    using Point3Type = holo::geometry::details::Point3T<Scalar>;

    /**
     * @brief Convert 2d point to 3d point using target object width.
     *
     * @param[in] image_width target object width on image (pixel)
     * @param[in] real_width target object real width (meter)
     * @param[in] point2 a undistorted 2d point on image, indicating target object angle of X_camera and Y_camera
     * direction.
     * @param[in] camera the camera model to undistort 2d point
     * @param[out] point3 3d point in camera frame
     *
     * @return bool_t true if the conversion is successful else false.
     *
     * @note The coordinate of this 3d point is in camera frame.
     */
    static bool_t ConvertByWidth(const Scalar image_width, const Scalar real_width, const Point2Type& point2,
                                 const CameraBaseT<Scalar>& camera, Point3Type& point3);

    /**
     * @brief Convert 2d point to 3d point using target object height.
     *
     * @param[in] image_height target object height on image (pixel)
     * @param[in] real_height target object real height (meter)
     * @param[in] point2 a undistorted 2d point on image, indicating target object angle of X_camera and Y_camera
     * direction.
     * @param[in] camera the camera model to undistort 2d point
     * @param[out] point3 3d point in camera frame
     *
     * @return bool_t true if the conversion is successful else false.
     *
     * @note The coordinate of this 3d point is in camera frame
     */
    static bool_t ConvertByHeight(const Scalar image_height, const Scalar real_height, const Point2Type& point2,
                                  const CameraBaseT<Scalar>& camera, Point3Type& point3);

private:
    /**
     * @brief Convert 2d point to 3d point using target object size and specified focal_length.
     *
     * @param[in] focal_legnth the focal length used to compute Z_camera coordinate.
     * @param[in] image_size target object size on image (pixel)
     * @param[in] real_size target object real size (meter)
     * @param[in] point2 a undistorted 2d point on image, indicating target object angle of X_camera and Y_camera
     * direction.
     * @param[in] camera the camera model to undistort 2d point
     * @param[out] point3 3d point in camera frame
     *
     * @return bool_t true if the conversion is successful else false.
     *
     * @note The coordinate of this 3d point is in camera frame
     */
    static bool_t ConvertBySize(const Scalar focal_legnth, const Scalar image_size, const Scalar real_size,
                                const Point2Type& point2, const CameraBaseT<Scalar>& camera, Point3Type& point3);
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_SPACE_CONVERTOR_SIZE_CONVERTOR_H_
