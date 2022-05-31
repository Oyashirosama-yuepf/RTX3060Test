/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pose2.hpp
 * @brief This header file defines rotation
 * @author duyanwei@holomatic.com
 * @date Sep-25-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_IMPL_P0SE2_HPP_
#define HOLO_GEIMETRY_DETAILS_IMPL_P0SE2_HPP_

namespace holo
{
namespace geometry
{
namespace details
{
template <typename T>
Pose2T<T>::Pose2T() noexcept : Pose2T(Rot2Type(), Point2Type())
{
}

template <typename T>
Pose2T<T>::Pose2T(const Rot2Type& r, Point2Type const& t) noexcept : rotation_(r), translation_(t)
{
}

template <typename T>
Pose2T<T>::Pose2T(ScalarType const theta, Point2Type const& t) noexcept : Pose2T(theta, t.GetX(), t.GetY())
{
}

template <typename T>
Pose2T<T>::Pose2T(ScalarType const theta, ScalarType const x, ScalarType const y) noexcept
  : rotation_(theta), translation_(x, y)
{
}

template <typename T>
Pose2T<T>::Pose2T(const Matrix3Type& m)
  : rotation_(Matrix2Type(m(0u, 0u), m(0u, 1u), m(1u, 0u), m(1u, 1u))), translation_(m(0u, 2u), m(1u, 2u))
{
}

template <typename T>
Pose2T<T>::Pose2T(Pose2Type const& other) noexcept : rotation_(other.GetRotation()), translation_(other.GetTranslation())
{
}

template <typename T>
typename Pose2T<T>::Pose2Type& Pose2T<T>::operator=(Pose2Type const& other) noexcept
{
    rotation_    = other.rotation_;
    translation_ = other.translation_;
    return *this;
}

template <typename T>
typename Pose2T<T>::Pose2Type Pose2T<T>::operator*(Pose2Type const& other) const noexcept
{
    const Matrix3Type m = ToMatrix() * other.ToMatrix();
    return Pose2Type(m);
}

template <typename T>
typename Pose2T<T>::Point2Type Pose2T<T>::operator*(Point2Type const& p) const noexcept
{
    return TransformFrom(p);
}

template <typename T>
typename Pose2T<T>::Vector2Type Pose2T<T>::operator*(Vector2Type const& v) const noexcept
{
    return TransformFrom(v);
}

template <typename T>
bool_t Pose2T<T>::operator==(Pose2Type const& other) const noexcept
{
    return IsEqual(other);
}

template <typename T>
bool Pose2T<T>::IsEqual(Pose2Type const& other, ScalarType const tol) const noexcept
{
    return translation_.IsEqual(other.GetTranslation(), tol) && rotation_.IsEqual(other.GetRotation(), tol);
}

template <typename T>
bool_t Pose2T<T>::IsValid() const noexcept
{
    return rotation_.IsValid() && translation_.IsValid();
}

template <typename T>
typename Pose2T<T>::Pose2Type Pose2T<T>::Inverse() const noexcept
{
    return Pose2Type(rotation_.Inverse(), rotation_.Unrotate(-translation_));
}

template <typename T>
typename Pose2T<T>::Pose2Type Pose2T<T>::Between(const Pose2Type& other) const noexcept
{
    return Inverse() * other;
}

template <typename T>
typename Pose2T<T>::Point2Type Pose2T<T>::TransformTo(Point2Type const& p) const noexcept
{
    return Point2Type(rotation_.Unrotate(p - translation_));
}

template <typename T>
typename Pose2T<T>::Vector2Type Pose2T<T>::TransformTo(Vector2Type const& v) const noexcept
{
    return rotation_.Unrotate(v);
}

template <typename T>
typename Pose2T<T>::Point2Type Pose2T<T>::TransformFrom(Point2Type const& p) const noexcept
{
    return translation_ + rotation_.Rotate(p);
}

template <typename T>
typename Pose2T<T>::Vector2Type Pose2T<T>::TransformFrom(Vector2Type const& v) const noexcept
{
    return rotation_.Rotate(v);
}

template <typename T>
typename Pose2T<T>::Matrix3Type Pose2T<T>::ToMatrix() const noexcept
{
    const Matrix2Type rot = rotation_.ToMatrix();
    return Matrix3Type(rot(0u, 0u), rot(0u, 1u), translation_.GetX(), rot(1u, 0u), rot(1u, 1u), translation_.GetY(),
                       static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(1.0));
}

template <typename T>
typename Pose2T<T>::Pose2Type Pose2T<T>::Identity() noexcept
{
    return Pose2Type();
}

template <typename T>
uint8_t Pose2T<T>::Dim() noexcept
{
    return 3u;
}

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_IMPL_P0SE2_HPP_
