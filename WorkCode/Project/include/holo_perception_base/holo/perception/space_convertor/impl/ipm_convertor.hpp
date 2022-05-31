/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ipm_convertor.hpp
 * @brief This header file defines implement of IPMConvertor.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2019-12-09"
 */

#include <cmath>

#include <holo/log/hololog.h>
#include <holo/core/epsilon.h>
#include <holo/numerics/vector.h>
#include <holo/perception/space_convertor/ipm_convertor.h>

namespace holo
{
namespace perception
{
template <typename Scalar>
bool_t IPMConvertor<Scalar>::Convert(const Point2Type& point2, const CameraBaseT<Scalar>& camera,
                                     const Pose3Type& ground2camera_pose, Point3Type& point3)
{
    // 1. prepare resources
    const numerics::Matrix3T<Scalar>&   R = ground2camera_pose.GetRotation().ToMatrix();
    const numerics::VectorT<Scalar, 3>& t =
        ground2camera_pose.GetTranslation().template As<numerics::VectorT<Scalar, 3>>();
    // 2. unproject point2
    Point3Type                   point_unprojected  = camera.Unproject(point2);
    numerics::VectorT<Scalar, 3> vector_unprojected = point_unprojected.template As<numerics::VectorT<Scalar, 3>>();
    vector_unprojected.Normalize();
    // 3. compute ray direction
    numerics::VectorT<Scalar, 3> direction = R.Transpose() * vector_unprojected;
    // 4. compute camera frame origin in ground frame
    numerics::VectorT<Scalar, 3> origin = R.Transpose() * t * static_cast<Scalar>(-1.0);
    // avoid divide by zero (e.g. the direction is parallel to ground plane)
    if (fabs(direction(2U)) <= EpsilonT<Scalar>::value)
    {
        return false;
    }
    // 5. compute scale factor
    Scalar scale = static_cast<Scalar>(-1.0) * origin(2U) / direction(2U);
    // scale < 0 means ray goes in wrong direction (the oppsite position)
    if (scale < static_cast<Scalar>(0))
    {
        return false;
    }
    // 6. compute final result
    numerics::VectorT<Scalar, 3> result = scale * direction + origin;
    // 7. convert to camera coord
    result = R * result + t;
    point3 = Point3Type(result);
    return true;
}

template <typename Scalar>
bool_t IPMConvertor<Scalar>::Convert2BodyFrame(const numerics::Vector3T<Scalar>& ground_normal_body,
                                               const Point3Type& point_uv1, const Scalar& height_camera_ground,
                                               const CameraBaseT<Scalar>& camera, const Pose3Type& camera2body_pose,
                                               Point3Type& point3)
{
    Scalar const height_body_ground = height_camera_ground - camera2body_pose.GetTranslation().GetZ();
    Scalar const s                  = -(ground_normal_body.Transpose() *
                           camera2body_pose.GetTranslation().template As<numerics::VectorT<Scalar, 3>>() +
                       ::holo::Matrix1f(height_body_ground))
                          .Sum() /
                     (ground_normal_body.Transpose() * camera2body_pose.GetRotation().ToMatrix() * camera.GetKInv() *
                      point_uv1.template As<numerics::VectorT<Scalar, 3>>())
                         .Sum();
    ::holo::numerics::VectorT<Scalar, 3> const point_body =
        camera2body_pose.GetRotation().ToMatrix() * camera.GetKInv() *
            point_uv1.template As<numerics::VectorT<Scalar, 3>>() * s +
        camera2body_pose.GetTranslation().template As<numerics::VectorT<Scalar, 3>>();

    if (point_body[0u] <= 0)
    {
        LOG(ERROR) << "IPM convert to body frame point ERROR!";
        return false;
    }

    point3.Set(point_body);
    return true;
}

}  // namespace perception
}  // namespace holo
