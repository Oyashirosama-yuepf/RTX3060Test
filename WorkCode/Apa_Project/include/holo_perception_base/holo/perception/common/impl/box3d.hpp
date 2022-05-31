/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box3d.hpp
 * @brief This header file defines .
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2020-09-16"
 */

#ifndef HOLO_PERCEPTION_COMMON_BOX3D_HPP_
#define HOLO_PERCEPTION_COMMON_BOX3D_HPP_

#include <holo/perception/common/box3d.h>

namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
Box3DT<T>::Box3DT(Point3Type const& center_point, Scalar x_dim, Scalar y_dim, Scalar z_dim, Scalar rx, Scalar ry,
                  Scalar rz)
  : center_point_(center_point), x_dim_(x_dim), y_dim_(y_dim), z_dim_(z_dim), rx_(rx), ry_(ry), rz_(rz)
{
    if (x_dim < static_cast<Scalar>(0.0))
    {
        throw std::range_error("x_dim should be a non-negative value!");
    }
    if (y_dim < static_cast<Scalar>(0.0))
    {
        throw std::range_error("y_dim should be a non-negative value!");
    }
    if (z_dim < static_cast<Scalar>(0.0))
    {
        throw std::range_error("z_dim should be a non-negative value!");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
Box3DT<T>::Box3DT(Scalar x, Scalar y, Scalar z, Scalar x_dim, Scalar y_dim, Scalar z_dim, Scalar rx, Scalar ry,
                  Scalar rz) noexcept
  : Box3DT(Point3Type(x, y, z), x_dim, y_dim, z_dim, rx, ry, rz)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
Box3DT<T>::Box3DT(Box3Type const& box3) noexcept
  : center_point_(box3.center_point_)
  , x_dim_(box3.x_dim_)
  , y_dim_(box3.y_dim_)
  , z_dim_(box3.z_dim_)
  , rx_(box3.rx_)
  , ry_(box3.ry_)
  , rz_(box3.rz_)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
Box3DT<T>& Box3DT<T>::operator=(Box3Type const& box3) noexcept
{
    if (this == &box3)
    {
        return *this;
    }

    center_point_ = box3.center_point_;
    x_dim_        = box3.x_dim_;
    y_dim_        = box3.y_dim_;
    z_dim_        = box3.z_dim_;
    rx_           = box3.rx_;
    ry_           = box3.ry_;
    rz_           = box3.rz_;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t Box3DT<T>::operator==(Box3Type const& box3) const noexcept
{
    Scalar dx_dim = std::abs(x_dim_ - box3.x_dim_);
    Scalar dy_dim = std::abs(y_dim_ - box3.y_dim_);
    Scalar dz_dim = std::abs(z_dim_ - box3.z_dim_);
    Scalar err_rx = std::abs(rx_ - box3.rx_);
    Scalar err_ry = std::abs(ry_ - box3.ry_);
    Scalar err_rz = std::abs(rz_ - box3.rz_);
    return (center_point_ == box3.center_point_ && dx_dim <= tol && dy_dim <= tol && dz_dim <= tol && err_rx <= tol &&
            err_ry <= tol && err_rz <= tol);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t Box3DT<T>::IsValid() const noexcept
{
    return (center_point_.IsValid() && x_dim_ > tol && y_dim_ > tol && z_dim_ > tol && rx_ >= tol && ry_ >= tol &&
            rz_ >= tol);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void Box3DT<T>::ConvertToBaseBox3(BaseBox3Type& box3_out) const noexcept
{
    // step1: transfrom center point to coordinate's origin
    /**                                y ^
     *        y ^                        |
     *          |********            ****|****
     *          |       *      ==> --*---o---*--> x
     *          o********--->x       ****|****
     *                                   |
     */
    Pose3Type T1 =
        Pose3Type(Rot3Type(), Point3Type(static_cast<Scalar>(-0.5) * x_dim_, static_cast<Scalar>(-0.5) * y_dim_,
                                         static_cast<Scalar>(-0.5) * z_dim_));

    // step2: transform box with rotation
    /**         y ^                    y ^
     *            |                      |*
     *        ****|****                * |  *
     *      --*---o---*--> x   ==> -*----o----*--> x
     *        ****|****               *  | *
     *                                  *|
     */
    Pose3Type T2 = Pose3Type(Rot3Type::RzRyRx(rx_, ry_, rz_), Point3Type());

    // step3: transform box from center to the target position
    /**
     *         y ^                  y ^
     *           |*                   |         *
     *         * |  *                 |      *    *
     *     -*----o----*--> x   ==>    |   *         *
     *        *  | *                  |     *    *
     *          *|                    |       *
     *                                o----------------> x
     */
    Pose3Type T3   = Pose3Type(Rot3Type(), Point3Type(center_point_));
    Pose3Type pose = T3 * T2 * T1;
    box3_out       = BaseBox3Type(y_dim_, z_dim_, x_dim_, pose);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void Box3DT<T>::ConvertFromBaseBox3(BaseBox3Type const& box3_in) noexcept
{
    center_point_ = box3_in.GetCenter();
    x_dim_        = box3_in.GetDepth();
    y_dim_        = box3_in.GetWidth();
    z_dim_        = box3_in.GetHeight();

    Vector3Type rpy = box3_in.GetPose().GetRotation().RPY();
    rx_             = rpy[0u];
    ry_             = rpy[1u];
    rz_             = rpy[2u];
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_COMMON_BOX3D_HPP_
