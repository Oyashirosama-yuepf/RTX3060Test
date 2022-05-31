/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point2.hpp
 * @brief This header file defines point in 2d.
 * @author duyanwei@holomatic.com
 * @date 2019-08-30
 */

#ifndef HOLO_GEOMETRY_DETAILS_IMPL_POINT2_HPP_
#define HOLO_GEOMETRY_DETAILS_IMPL_POINT2_HPP_

namespace holo
{
namespace geometry
{
namespace details
{
template <typename T>
Point2T<T>::Point2T() noexcept : data_{static_cast<T>(0.0), static_cast<T>(0.0)}
{
}

template <typename T>
Point2T<T>::Point2T(ScalarType const x, ScalarType const y) noexcept : data_{x, y}
{
}

template <typename T>
Point2T<T>::Point2T(ScalarType const x, ScalarType const y, ScalarType const) noexcept : data_{x, y}
{
}

template <typename T>
Point2T<T>::Point2T(Vector2Type const& v) noexcept : Point2T(v(0u), v(1u))
{
}

template <typename T>
typename Point2T<T>::Point2Type Point2T<T>::operator-() const noexcept
{
    return Point2Type(-data_[0], -data_[1]);
}

template <typename T>
typename Point2T<T>::Point2Type Point2T<T>::operator+(Point2Type const& p) const noexcept
{
    return Point2Type(data_[0] + p.GetX(), data_[1] + p.GetY());
}

template <typename T>
typename Point2T<T>::Point2Type Point2T<T>::operator-(Point2Type const& p) const noexcept
{
    return Point2Type(data_[0u] - p.GetX(), data_[1u] - p.GetY());
}

template <typename T>
typename Point2T<T>::Point2Type& Point2T<T>::operator+=(Point2Type const& p) noexcept
{
    data_[0] += p.GetX();
    data_[1] += p.GetY();
    return *this;
}

template <typename T>
typename Point2T<T>::Point2Type& Point2T<T>::operator-=(Point2Type const& p) noexcept
{
    data_[0] -= p.GetX();
    data_[1] -= p.GetY();
    return *this;
}

template <typename T>
bool_t Point2T<T>::operator==(Point2Type const& p) const noexcept
{
    return IsEqual(p);
}

template <typename T>
Point2T<T> Point2T<T>::operator*(ScalarType s) const noexcept
{
    return Point2T<T>(s * data_[0], s * data_[1]);
}

template <typename T>
Point2T<T> Point2T<T>::operator/(ScalarType s) const
{
    if (ScalarEqualT<ScalarType>()(s, static_cast<ScalarType>(0.0)))
    {
        std::string msg = "division by zero is not defined!";
        throw std::runtime_error(msg);
    }
    return Point2Type(data_[0] / s, data_[1] / s);
}

template <typename T>
bool_t Point2T<T>::IsValid() const noexcept
{
    return IsFinite();
}

template <typename T>
typename Point2T<T>::Vector2Type Point2T<T>::ToVector() const noexcept
{
    return Vector2Type(data_[0], data_[1]);
}

template <typename T>
bool_t Point2T<T>::IsEqual(Point2Type const& q, ScalarType tol) const noexcept
{
    return Dist(q) <= tol;
}

template <typename T>
typename Point2T<T>::ScalarType Point2T<T>::DistSqr(Point2Type const& target) const noexcept
{
    ScalarType const dx = data_[0] - target.GetX();
    ScalarType const dy = data_[1] - target.GetY();
    return (dx * dx) + (dy * dy);
}

template <typename T>
typename Point2T<T>::ScalarType Point2T<T>::Dist(Point2Type const& target) const noexcept
{
    return std::sqrt(DistSqr(target));
}

template <typename T>
bool_t Point2T<T>::IsFinite() const noexcept
{
    return std::isfinite(data_[0]) && std::isfinite(data_[1]);
}

template <typename T>
typename Point2T<T>::Vector3Type Point2T<T>::Homogeneous() const noexcept
{
    return Vector3Type(data_[0], data_[1], static_cast<ScalarType>(1.0));
}

template <typename T>
typename Point2T<T>::Point2Type Point2T<T>::Expmap(const Vector2Type& v) noexcept
{
    return Point2Type(v(0u), v(1u));
}

template <typename T>
typename Point2T<T>::Vector2Type Point2T<T>::Logmap(Point2Type const& p) noexcept
{
    return Vector2Type(p.GetX(), p.GetY());
}

template <typename T>
typename Point2T<T>::Point2Type Point2T<T>::Zero() noexcept
{
    return Point2Type(static_cast<ScalarType>(0.0f), static_cast<ScalarType>(0.0f));
}

template <typename T>
typename Point2T<T>::Point2Type Point2T<T>::One() noexcept
{
    return Point2Type(static_cast<ScalarType>(1.0f), static_cast<ScalarType>(1.0f));
}

template <typename T>
typename Point2T<T>::Point2Type Point2T<T>::UnitX() noexcept
{
    return Point2Type(static_cast<ScalarType>(1.0f), static_cast<ScalarType>(0.0f));
}

template <typename T>
typename Point2T<T>::Point2Type Point2T<T>::UnitY() noexcept
{
    return Point2Type(static_cast<ScalarType>(0.0f), static_cast<ScalarType>(1.0f));
}

template <typename T>
uint8_t Point2T<T>::Dim() noexcept
{
    return 2u;
}

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_IMPL_POINT2_HPP_
