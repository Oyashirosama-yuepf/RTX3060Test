/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file size_convertor.hpp
 * @brief This header file defines implement of SizeConvertor.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2019-12-09"
 */

#include <holo/core/epsilon.h>
#include <holo/perception/space_convertor/size_convertor.h>

namespace holo
{
namespace perception
{
template <typename Scalar>
bool_t SizeConvertor<Scalar>::ConvertByWidth(const Scalar image_width, const Scalar real_width,
                                             const Point2Type& point2, const CameraBaseT<Scalar>& camera,
                                             Point3Type& point3)
{
    Scalar focal_length = camera.GetK()(0U, 0U);
    return SizeConvertor<Scalar>::ConvertBySize(focal_length, image_width, real_width, point2, camera, point3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Scalar>
bool_t SizeConvertor<Scalar>::ConvertByHeight(const Scalar image_height, const Scalar real_height,
                                              const Point2Type& point2, const CameraBaseT<Scalar>& camera,
                                              Point3Type& point3)
{
    Scalar focal_length = camera.GetK()(1U, 1U);
    return SizeConvertor<Scalar>::ConvertBySize(focal_length, image_height, real_height, point2, camera, point3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Scalar>
bool_t SizeConvertor<Scalar>::ConvertBySize(const Scalar focal_length, const Scalar image_size, const Scalar real_size,
                                            const Point2Type& point2, const CameraBaseT<Scalar>& camera,
                                            Point3Type& point3)
{
    if (image_size <= EpsilonT<Scalar>::value || real_size <= EpsilonT<Scalar>::value)
    {
        return false;
    }
    // Get K matrix
    const numerics::Matrix3T<Scalar>& K = camera.GetK();
    // Compute coordinates
    Scalar z_camera  = real_size / image_size * focal_length;
    Scalar tangent_x = (point2.GetX() - K(0U, 2U)) / K(0U, 0U);
    Scalar tangent_y = (point2.GetY() - K(1U, 2U)) / K(1U, 1U);
    Scalar x_camera  = z_camera * tangent_x;
    Scalar y_camera  = z_camera * tangent_y;
    point3           = Point3Type(x_camera, y_camera, z_camera);
    return true;
}

}  // namespace perception
}  // namespace holo
