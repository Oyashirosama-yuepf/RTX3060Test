/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_fisheye.hpp
 * @brief This file implements CameraFisheyeT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-12-10
 */

#ifndef HOLO_COMMON_CAMERA_FISHEYE_HPP_
#define HOLO_COMMON_CAMERA_FISHEYE_HPP_

#include <holo/common/camera_fisheye.h>

namespace holo
{
template <typename T>
CameraFisheyeT<T>::CameraFisheyeT(const uint32_t width, const uint32_t height, const Matrix3Type& k,
                                  const Vector8Type& d) noexcept
  : CameraBaseT<T>(width, height, k, d)
{
}

template <typename T>
CameraFisheyeT<T>::CameraFisheyeT(const IntrinsicType& intrinsic) noexcept : CameraBaseT<T>(intrinsic)
{
}

template <typename T>
CameraFisheyeT<T>::CameraFisheyeT(const CameraFisheyeT& other) noexcept
  : CameraBaseT<T>(other.resolution_width_, other.resolution_height_, other.k_, other.d_)
{
}

template <typename T>
CameraFisheyeT<T>::CameraFisheyeT(CameraFisheyeT&& other) noexcept
  : CameraBaseT<T>(other.resolution_width_, other.resolution_height_, other.k_, other.d_)
{
}

template <typename T>
CameraFisheyeT<T>& CameraFisheyeT<T>::operator=(const CameraFisheyeT& other) noexcept
{
    this->resolution_width_  = other.resolution_width_;
    this->resolution_height_ = other.resolution_height_;
    this->k_                 = other.k_;
    this->d_                 = other.d_;
    this->k_inv_             = other.k_inv_;

    return *this;
}

template <typename T>
CameraFisheyeT<T>& CameraFisheyeT<T>::operator=(CameraFisheyeT&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    this->resolution_width_  = other.resolution_width_;
    this->resolution_height_ = other.resolution_height_;
    this->k_                 = std::move(other.k_);
    this->d_                 = std::move(other.d_);
    this->k_inv_             = std::move(other.k_inv_);

    return *this;
}

template <typename T>
typename CameraFisheyeT<T>::Point2Type CameraFisheyeT<T>::DistortPoint(const Point2Type& in) const
{
    float64_t           alpha = 0.0;
    Vector2T<float64_t> x(static_cast<float64_t>(in.GetX()), static_cast<float64_t>(in.GetY()));
    Vector2T<float64_t> f(static_cast<float64_t>(this->k_(0, 0)), static_cast<float64_t>(this->k_(1, 1)));
    Vector2T<float64_t> c(static_cast<float64_t>(this->k_(0, 2)), static_cast<float64_t>(this->k_(1, 2)));
    Vector4T<float64_t> k(static_cast<float64_t>(this->d_[0]), static_cast<float64_t>(this->d_[1]),
                          static_cast<float64_t>(this->d_[4]), static_cast<float64_t>(this->d_[5]));

    float64_t r2 = x.Dot(x);
    float64_t r  = std::sqrt(r2);

    // Angle of the incoming ray:
    float64_t theta = atan(r);

    float64_t theta2 = theta * theta, theta3 = theta2 * theta, theta4 = theta2 * theta2, theta5 = theta4 * theta,
              theta6 = theta3 * theta3, theta7 = theta6 * theta, theta8 = theta4 * theta4, theta9 = theta8 * theta;

    float64_t theta_d = theta + k[0] * theta3 + k[1] * theta5 + k[2] * theta7 + k[3] * theta9;

    float64_t inv_r = r > 1e-8 ? 1.0 / r : 1;
    float64_t cdist = r > 1e-8 ? theta_d * inv_r : 1;

    Vector2T<float64_t> xd1 = x * cdist;
    Vector2T<float64_t> xd3(xd1[0] + alpha * xd1[1], xd1[1]);
    Vector2T<float64_t> final_point(xd3[0] * f[0] + c[0], xd3[1] * f[1] + c[1]);

    return Point2Type(static_cast<T>(final_point[0]), static_cast<T>(final_point[1]));
}

template <typename T>
typename CameraFisheyeT<T>::Point2Type CameraFisheyeT<T>::UndistortPoint(const Point2Type&  in,
                                                                         const Matrix3Type& new_k) const
{
    Vector2T<float64_t>      f(static_cast<float64_t>(this->k_(0, 0)), static_cast<float64_t>(this->k_(1, 1)));
    Vector2T<float64_t>      c(static_cast<float64_t>(this->k_(0, 2)), static_cast<float64_t>(this->k_(1, 2)));
    Vector4T<float64_t>      k(static_cast<float64_t>(this->d_[0]), static_cast<float64_t>(this->d_[1]),
                          static_cast<float64_t>(this->d_[4]), static_cast<float64_t>(this->d_[5]));
    MatrixT<float64_t, 3, 3> RR = Matrix3T<float64_t>::Identity();  // no rectification transformation
    MatrixT<float64_t, 3, 3> PP = new_k.template Cast<float64_t>();

    RR = PP * RR;

    Vector2T<float64_t> pi(static_cast<float64_t>(in.GetX()), static_cast<float64_t>(in.GetY()));  // image point
    Vector2T<float64_t> pw((pi[0] - c[0]) / f[0], (pi[1] - c[1]) / f[1]);                          // world point
    float64_t           scale   = 1.0;
    float64_t           theta_d = std::sqrt(pw[0] * pw[0] + pw[1] * pw[1]);

    // the current camera model is only valid up to 180 FOV
    // for larger FOV the loop below does not converge
    // clip values so we still get plausible results for super fisheye images > 180 grad
    theta_d = std::min(std::max(-M_PI / 2., theta_d), M_PI / 2.);

    if (theta_d > 1e-8)
    {
        // compensate distortion iteratively
        float64_t theta = theta_d;
        for (int32_t j = 0; j < 10; j++)
        {
            float64_t theta2 = theta * theta, theta4 = theta2 * theta2, theta6 = theta4 * theta2,
                      theta8 = theta6 * theta2;
            theta            = theta_d / (1 + k[0] * theta2 + k[1] * theta4 + k[2] * theta6 + k[3] * theta8);
        }

        scale = std::tan(theta) / theta_d;
    }

    Vector2T<float64_t> pu = pw * scale;  // undistorted point

    // reproject
    Vector3T<float64_t> pr =
        RR * Vector3T<float64_t>(pu[0], pu[1], 1.0);  // rotated point optionally multiplied by new camera matrix
    Point2Type fi(static_cast<T>(pr[0] / pr[2]), static_cast<T>(pr[1] / pr[2]));  // final

    return fi;
}

template <typename T>
void CameraFisheyeT<T>::UndistortImage(const holo::Image& in, const Matrix3Type& new_k, holo::Image& out) const
{
    (void)in;
    (void)new_k;
    (void)out;
}
}  // namespace holo

#endif  // !HOLO_COMMON_CAMERA_FISHEYE_HPP_
