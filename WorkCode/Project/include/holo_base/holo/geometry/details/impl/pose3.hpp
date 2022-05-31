/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pose3.hpp
 * @brief the template implementation of pose3
 * @author Li Chao (lichao@holomatic.ai)
 * @author Yanwei. Du (duyanwei@holomatic.com)
 * @date Sep-27-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_IMPL_POSE3_HPP_
#define HOLO_GEOMETRY_DETAILS_IMPL_POSE3_HPP_

namespace holo
{
namespace geometry
{
namespace details
{
template <typename T>
Pose3T<T>::Pose3T() noexcept : rotation_(Rot3Type()), translation_(Point3Type())
{
}

template <typename T>
Pose3T<T>::Pose3T(Rot3Type const& r, Point3Type const& t) noexcept : rotation_(r), translation_(t)
{
    assert(IsValid());
}

template <typename T>
Pose3T<T>::Pose3T(Matrix4Type const& m) noexcept
  : rotation_(m(0u, 0u), m(0u, 1u), m(0u, 2u), m(1u, 0u), m(1u, 1u), m(1u, 2u), m(2u, 0u), m(2u, 1u), m(2u, 2u))
  , translation_(m(0u, 3u), m(1u, 3u), m(2u, 3u))
{
    assert(IsValid());
}

template <typename T>
Pose3T<T>::Pose3T(Pose3Type const& other) noexcept : rotation_(other.rotation_), translation_(other.translation_)
{
}

template <typename T>
Pose3T<T>::~Pose3T() noexcept
{
}

template <typename T>
typename Pose3T<T>::Pose3Type Pose3T<T>::operator*(Pose3Type const& other) const noexcept
{
    return Compose(other);
}

template <typename T>
typename Pose3T<T>::Point3Type Pose3T<T>::operator*(Point3Type const& p) const noexcept
{
    return TransformFrom(p);
}

template <typename T>
typename Pose3T<T>::Vector3Type Pose3T<T>::operator*(Vector3Type const& v) const noexcept
{
    return TransformFrom(v);
}

template <typename T>
typename Pose3T<T>::Pose3Type& Pose3T<T>::operator=(Pose3Type const& other) noexcept
{
    rotation_    = other.rotation_;
    translation_ = other.translation_;
    return *this;
}

template <typename T>
bool_t Pose3T<T>::operator==(Pose3Type const& other) const noexcept
{
    return IsEqual(other);
}

template <typename T>
bool_t Pose3T<T>::IsValid() const noexcept
{
    return (rotation_.IsValid()) && (translation_.IsValid());
}

template <typename T>
typename Pose3T<T>::Matrix4Type Pose3T<T>::ToMatrix() const noexcept
{
    Matrix4Type       m   = Matrix4Type::Identity();
    const holo::numerics::Matrix3T<T> rot = rotation_.ToMatrix();
    for (uint8_t i = 0u; i < 3u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            m(i, j) = rot(i, j);
        }
    }
    m(0u, 3u) = translation_.GetX();
    m(1u, 3u) = translation_.GetY();
    m(2u, 3u) = translation_.GetZ();

    return m;
}

template <typename T>
bool Pose3T<T>::IsEqual(Pose3Type const& other, ScalarType const tol) const noexcept
{
    return rotation_.IsEqual(other.rotation_, tol) && translation_.IsEqual(other.translation_, tol);
}

template <typename T>
typename Pose3T<T>::ScalarType Pose3T<T>::Dist(Pose3Type const& other) const noexcept
{
    return translation_.Dist(other.GetTranslation());
}

template <typename T>
typename Pose3T<T>::Pose3Type Pose3T<T>::Compose(Pose3Type const& other) const noexcept
{
    return Pose3Type(rotation_ * other.rotation_, translation_ + rotation_ * other.translation_);
}

template <typename T>
typename Pose3T<T>::Pose3Type Pose3T<T>::Inverse() const noexcept
{
    const Rot3Type rt = rotation_.Transpose();
    return Pose3Type(rt, rt * (-translation_));
}

template <typename T>
typename Pose3T<T>::Point3Type Pose3T<T>::TransformFrom(Point3Type const& p) const noexcept
{
    const Point3Type rp = rotation_.Rotate(p);
    return Point3Type(rp + translation_);
}

template <typename T>
typename Pose3T<T>::Point3Type Pose3T<T>::TransformTo(Point3Type const& p) const noexcept
{
    return rotation_.Unrotate(Point3Type(p - translation_));
}

template <typename T>
typename Pose3T<T>::Vector3Type Pose3T<T>::TransformFrom(Vector3Type const& v) const noexcept
{
    // only applied rotation
    return rotation_.Rotate(v);
}

template <typename T>
typename Pose3T<T>::Vector3Type Pose3T<T>::TransformTo(Vector3Type const& v) const noexcept
{
    // only applied rotation
    return rotation_.Unrotate(v);
}

template <typename T>
typename Pose3T<T>::Pose3Type Pose3T<T>::Between(Pose3Type const& other) const noexcept
{
    return Inverse() * other;
}

template <typename T>
uint8_t Pose3T<T>::Dim() noexcept
{
    return 6u;
}

template <typename T>
typename Pose3T<T>::Pose3Type Pose3T<T>::Identity() noexcept
{
    return Pose3Type();
}

template <typename T>
typename Pose3T<T>::Pose3Type Pose3T<T>::Expmap(const Vector6Type& v) noexcept
{
    return Pose3Type(Rot3Type::Expmap(Vector3Type(v(0u), v(1u), v(2u))),
                     Point3Type::Expmap(Vector3Type(v(3u), v(4u), v(5u))));
}

template <typename T>
typename Pose3T<T>::Vector6Type Pose3T<T>::Logmap(Pose3Type const& pose) noexcept
{
    const Vector3Type vr = Rot3Type::Logmap(pose.GetRotation());
    const Vector3Type vt = Point3Type::Logmap(pose.GetTranslation());
    return Vector6Type(vr(0u), vr(1u), vr(2u), vt(0u), vt(1u), vt(2u));
}

template <typename T>
Pose3T<T> Pose3T<T>::Interpolate(Pose3Type const& left, Pose3Type const& right, ScalarType const ratio) noexcept
{
    if (ratio >= static_cast<ScalarType>(0.0) && ratio <= static_cast<ScalarType>(1.0))
    {
        // interpolation
        const QuaternionType q1 = left.GetRotation().ToQuaternion();
        const QuaternionType q2 = right.GetRotation().ToQuaternion();
        Point3Type const&    p1 = left.GetTranslation();
        Point3Type const&    p2 = right.GetTranslation();

        return Pose3Type(Rot3Type(q1.Slerp(ratio, q2).ToRotationMatrix()),
                         Point3Type((static_cast<ScalarType>(1.0) - ratio) * p1 + ratio * p2));
    }
    else
    {
        // extrapolation
        const Pose3Type   diff = right * left.Inverse();
        const Vector3Type aa   = ratio * Rot3Type::Logmap(diff.GetRotation());
        Point3Type const& p1   = left.GetTranslation();
        Point3Type const& p2   = right.GetTranslation();

        return Pose3Type(Rot3Type::Expmap(aa) * left.GetRotation(),
                         Point3Type((static_cast<ScalarType>(1.0) - ratio) * p1 + ratio * p2));
    }
}

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_IMPL_POSE3_HPP_
