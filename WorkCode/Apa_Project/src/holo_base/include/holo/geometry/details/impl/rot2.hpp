/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rot2.hpp
 * @brief This header file defines rotation
 * @author duyanwei@holomatic.com
 * @date Sep-25-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_IMPL_ROT2_HPP_
#define HOLO_GEIMETRY_DETAILS_IMPL_ROT2_HPP_

namespace holo
{
namespace geometry
{
namespace details
{
template <typename T>
Rot2T<T>::Rot2T() noexcept : Rot2T(static_cast<ScalarType>(0.0))
{
}

template <typename T>
Rot2T<T>::Rot2T(ScalarType const theta) noexcept : c_(std::cos(theta)), s_(std::sin(theta))
{
}

template <typename T>
Rot2T<T>::Rot2T(Matrix2Type const& m) : c_(m(0u, 0u)), s_(m(1u, 0u))
{
    Normalize();
    assert(IsValid());
}

template <typename T>
Rot2T<T>::Rot2T(Rot2Type const& other) noexcept : c_(other.c_), s_(other.s_)
{
}

template <typename T>
Rot2T<T>::~Rot2T() noexcept
{
}

template <typename T>
typename Rot2T<T>::Rot2Type& Rot2T<T>::operator=(Rot2Type const& other) noexcept
{
    c_ = other.c_;
    s_ = other.s_;
    return *this;
}

template <typename T>
typename Rot2T<T>::Rot2Type Rot2T<T>::operator*(Rot2Type const& other) const noexcept
{
    return Rot2Type(c_ * other.c_ - s_ * other.s_, s_ * other.c_ + c_ * other.s_);
}

template <typename T>
typename Rot2T<T>::Point2Type Rot2T<T>::operator*(Point2Type const& p) const noexcept
{
    return Rotate(p);
}

template <typename T>
typename Rot2T<T>::Vector2Type Rot2T<T>::operator*(Vector2Type const& v) const noexcept
{
    return Rotate(v);
}

template <typename T>
bool_t Rot2T<T>::operator==(Rot2Type const& other) const noexcept
{
    return IsEqual(other);
}

template <typename T>
bool_t Rot2T<T>::IsValid() const noexcept
{
    return ScalarEqualT<T>()(c_ * c_ + s_ * s_, static_cast<ScalarType>(1.0));
}

template <typename T>
bool_t Rot2T<T>::IsEqual(Rot2Type const& other, ScalarType const tol) const noexcept
{
    return std::fabs(c_ - other.c_) <= tol && std::fabs(s_ - other.s_) <= tol;
}

template <typename T>
typename Rot2T<T>::Rot2Type Rot2T<T>::Inverse() const noexcept
{
    return Rot2Type(c_, -s_);
}

template <typename T>
typename Rot2T<T>::Point2Type Rot2T<T>::Rotate(Point2Type const& p) const noexcept
{
    return Point2Type(Rotate(p.ToVector()));
}

template <typename T>
typename Rot2T<T>::Vector2Type Rot2T<T>::Rotate(Vector2Type const& v) const noexcept
{
    return ToMatrix() * v;
}

template <typename T>
typename Rot2T<T>::Point2Type Rot2T<T>::Unrotate(Point2Type const& p) const noexcept
{
    return Point2Type(Unrotate(p.ToVector()));
}

template <typename T>
typename Rot2T<T>::Vector2Type Rot2T<T>::Unrotate(Vector2Type const& v) const noexcept
{
    return ToMatrix().Inverse() * v;
}

template <typename T>
typename Rot2T<T>::Matrix2Type Rot2T<T>::ToMatrix() const noexcept
{
    return Matrix2Type(c_, -s_, s_, c_);
}

template <typename T>
typename Rot2T<T>::ScalarType Rot2T<T>::GetTheta() const noexcept
{
    return std::atan2(s_, c_);
}

template <typename T>
typename Rot2T<T>::Rot2Type Rot2T<T>::FromDegree(ScalarType const degree) noexcept
{
    return Rot2Type(Radian(degree));
}

template <typename T>
typename Rot2T<T>::Rot2Type Rot2T<T>::Identity() noexcept
{
    return Rot2Type(static_cast<ScalarType>(0.0));
}

template <typename T>
uint8_t Rot2T<T>::Dim() noexcept
{
    return 1u;
}

template <typename T>
Rot2T<T>::Rot2T(ScalarType const c, ScalarType const s) noexcept : c_(c), s_(s)
{
    Normalize();
}

template <typename T>
void Rot2T<T>::Normalize(ScalarType const epsilon) noexcept
{
    ScalarType norm = c_ * c_ + s_ * s_;

    if (!ScalarEqualT<ScalarType>()(norm, static_cast<ScalarType>(1.0), epsilon))
    {
        norm = std::pow(norm, static_cast<ScalarType>(-0.5));
        c_ *= norm;
        s_ *= norm;
    }
}

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // HOLO_GEIMETRY_DETAILS_IMPL_ROT2_HPP_
