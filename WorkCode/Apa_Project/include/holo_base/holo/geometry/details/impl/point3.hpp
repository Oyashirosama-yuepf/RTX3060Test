/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point3.hpp
 * @brief point in 3D
 * @author luopei (), luopei@holomatic.com
 * @author duyanwei@holomatic.com
 * @date 09-17-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_IMPL_POINT3_HPP_
#define HOLO_GEOMETRY_DETAILS_IMPL_POINT3_HPP_

namespace holo
{
namespace geometry
{
namespace details
{
template <typename T>
Point3T<T>::Point3T() noexcept
  : data_{static_cast<ScalarType>(0.0), static_cast<ScalarType>(0.0), static_cast<ScalarType>(0.0)}
{
}

template <typename T>
Point3T<T>::Point3T(ScalarType const x, ScalarType const y, ScalarType const z) noexcept : data_{x, y, z}
{
}

template <typename T>
Point3T<T>::Point3T(Vector3Type const& v) noexcept : data_{v(0u), v(1u), v(2u)}
{
}

template <typename T>
Point3T<T>::Point3T(Point2Type const& pt2) noexcept : data_{pt2[0], pt2[1], static_cast<T>(0.0)}
{
}

template <typename T>
typename Point3T<T>::Point3Type Point3T<T>::operator-() const noexcept
{
    return Point3Type(-data_[0], -data_[1], -data_[2]);
}

template <typename T>
typename Point3T<T>::Point3Type Point3T<T>::operator+(Point3Type const& p) const noexcept
{
    return Point3Type(data_[0] + p.GetX(), data_[1] + p.GetY(), data_[2] + p.GetZ());
}

template <typename T>
typename Point3T<T>::Point3Type Point3T<T>::operator-(Point3Type const& p) const noexcept
{
    return Point3Type(data_[0u] - p.GetX(), data_[1u] - p.GetY(), data_[2u] - p.GetZ());
}

template <typename T>
typename Point3T<T>::Point3Type& Point3T<T>::operator+=(Point3Type const& p) noexcept
{
    data_[0] += p.GetX();
    data_[1] += p.GetY();
    data_[2] += p.GetZ();
    return *this;
}

template <typename T>
typename Point3T<T>::Point3Type& Point3T<T>::operator-=(Point3Type const& p) noexcept
{
    data_[0] -= p.GetX();
    data_[1] -= p.GetY();
    data_[2] -= p.GetZ();
    return *this;
}

template <typename T>
bool_t Point3T<T>::operator==(Point3Type const& p) const noexcept
{
    return IsEqual(p);
}

template <typename T>
typename Point3T<T>::Point3Type Point3T<T>::operator*(ScalarType s) const noexcept
{
    return Point3T<T>(s * data_[0], s * data_[1], s * data_[2]);
}

template <typename T>
typename Point3T<T>::Point3Type Point3T<T>::operator/(ScalarType s) const
{
    if (ScalarEqualT<T>()(s, static_cast<T>(0.0)))
    {
        std::string msg = "division by zero is not defined!";
        // LOG(ERROR) << s;
        throw std::runtime_error(msg);
    }

    return Point3Type(data_[0] / s, data_[1] / s, data_[2] / s);
}

template <typename T>
typename Point3T<T>::Vector3Type Point3T<T>::ToVector() const noexcept
{
    return Vector3Type(data_[0], data_[1], data_[2]);
}

template <typename T>
typename Point3T<T>::Point2Type Point3T<T>::GetPointXY() const noexcept
{
    return Point2Type(data_[0], data_[1]);
}

template <typename T>
bool_t Point3T<T>::IsZero() const noexcept
{
    return (ScalarEqualT<T>()(data_[0], static_cast<T>(0.0)) &&
            ScalarEqualT<T>()(data_[1], static_cast<T>(0.0)) &&
            ScalarEqualT<T>()(data_[2], static_cast<T>(0.0)));
}

template <typename T>
typename Point3T<T>::Vector4Type Point3T<T>::Homogeneous() const noexcept
{
    return Vector4Type(data_[0], data_[1], data_[2], static_cast<ScalarType>(1.0));
}

template <typename T>
typename Point3T<T>::ScalarType Point3T<T>::DistSqr(Point3Type const& target) const noexcept
{
    const ScalarType dx = (data_[0] - target.GetX());
    const ScalarType dy = (data_[1] - target.GetY());
    const ScalarType dz = (data_[2] - target.GetZ());
    return (dx * dx) + (dy * dy) + (dz * dz);
}

template <typename T>
typename Point3T<T>::ScalarType Point3T<T>::Dist(Point3Type const& target) const noexcept
{
    return std::sqrt(DistSqr(target));
}

template <typename T>
bool_t Point3T<T>::IsEqual(Point3Type const& target, ScalarType threshold) const noexcept
{
    return (Dist(target) <= threshold);
}

template <typename T>
bool_t Point3T<T>::IsFinite() const noexcept
{
    return std::isfinite(data_[0]) && std::isfinite(data_[1]) && std::isfinite(data_[2]);
}

template <typename T>
bool_t Point3T<T>::IsValid() const noexcept
{
    return IsFinite();
}

template <typename T>
uint8_t Point3T<T>::Dim() noexcept
{
    return 3u;
}

template <typename T>
typename Point3T<T>::Point3Type Point3T<T>::Zero() noexcept
{
    return Point3Type(static_cast<ScalarType>(0.0), static_cast<ScalarType>(0.0), static_cast<ScalarType>(0.0));
}

template <typename T>
typename Point3T<T>::Point3Type Point3T<T>::One() noexcept
{
    return Point3Type(static_cast<ScalarType>(1.0), static_cast<ScalarType>(1.0), static_cast<ScalarType>(1.0));
}

template <typename T>
typename Point3T<T>::Point3Type Point3T<T>::UnitX() noexcept
{
    return Point3Type(static_cast<ScalarType>(1.0), static_cast<ScalarType>(0.0), static_cast<ScalarType>(0.0));
}

template <typename T>
typename Point3T<T>::Point3Type Point3T<T>::UnitY() noexcept
{
    return Point3Type(static_cast<ScalarType>(0.0), static_cast<ScalarType>(1.0), static_cast<ScalarType>(0.0));
}

template <typename T>
typename Point3T<T>::Point3Type Point3T<T>::UnitZ() noexcept
{
    return Point3Type(static_cast<ScalarType>(0.0), static_cast<ScalarType>(0.0), static_cast<ScalarType>(1.0));
}

template <typename T>
typename Point3T<T>::Point3Type Point3T<T>::Expmap(Vector3Type const& v) noexcept
{
    return Point3Type(v(0u), v(1u), v(2u));
}

template <typename T>
typename Point3T<T>::Vector3Type Point3T<T>::Logmap(Point3Type const& p) noexcept
{
    return Vector3Type(p.GetX(), p.GetY(), p.GetZ());
}

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_IMPL_POINT3_HPP_
