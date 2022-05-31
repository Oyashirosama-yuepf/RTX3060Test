/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line2.hpp
 * @brief a line in 2D space
 * @author duyanwei@holomatic.com
 * @date 2019-09-02
 */

#ifndef HOLO_GEOMETRY_DETAILS_IMPL_LINE2_HPP_
#define HOLO_GEOMETRY_DETAILS_IMPL_LINE2_HPP_

namespace holo
{
namespace geometry
{
namespace details
{
template <typename T>
Line2T<T>::Line2T() noexcept : a_(static_cast<T>(1.0)), b_(static_cast<T>(0.0)), c_(static_cast<T>(0.0))
{
}

template <typename T>
Line2T<T>::Line2T(Point2Type const& p1, Point2Type const& p2) : Line2T(p1, (p2 - p1).ToVector())
{
}

template <typename T>
Line2T<T>::Line2T(Point2Type const& p, Vector2Type const& v)
  : Line2T(Vector3Type(v(1u), -v(0u), p.GetY() * v(0u) - p.GetX() * v(1u)))
{
}

template <typename T>
Line2T<T>::Line2T(Vector3Type const& v) : a_(v(0u)), b_(v(1u)), c_(v(2u))
{
    // in-class normalize
    Normalize();

    // reinforce the sign of coefficients to be positive as defined
    int32_t sign = 1;

    // case 1: the first coefficient is negative
    if (a_ < static_cast<ScalarType>(0.0))
    {
        sign = -1;
    }
    // case 2: the first coefficient is zero
    else if (ScalarEqualT<ScalarType>()(a_, static_cast<ScalarType>(0.0)))
    {
        // case 2-1: the second coefficient is negative
        if (b_ < static_cast<ScalarType>(0.0))
        {
            sign = -1;
        }
        // case 2-2: the second coefficient is zero
        else if (ScalarEqualT<ScalarType>()(b_, static_cast<ScalarType>(0.0)))
        {
            std::stringstream ss;
            ss << "Line2T --- Invalid line coefficients: " << *this;
            throw std::runtime_error(ss.str());
        }
    }

    // update the sign
    a_ *= sign;
    b_ *= sign;
    c_ *= sign;
}

template <typename T>
Line2T<T>::Line2T(Line2T const& other) noexcept : a_(other.a_), b_(other.b_), c_(other.c_)
{
}

template <typename T>
Line2T<T>::~Line2T() noexcept
{
}

template <typename T>
Line2T<T>& Line2T<T>::operator=(Line2T const& other) noexcept
{
    a_ = other.a_;
    b_ = other.b_;
    c_ = other.c_;

    return *this;
}

template <typename T>
bool_t Line2T<T>::operator==(Line2T const& other) const noexcept
{
    return IsEqual(other);
}

template <typename T>
bool_t Line2T<T>::Contains(Point2Type const& p, ScalarType const tol) const noexcept
{
    return (Dist(p) <= tol);
}

template <typename T>
bool_t Line2T<T>::IsEqual(Line2T const& other, ScalarType const tol) const noexcept
{
    return (std::fabs(other.a_ - a_) <= tol && std::fabs(other.b_ - b_) <= tol && std::fabs(other.c_ - c_) <= tol);
}

template <typename T>
bool_t Line2T<T>::IsValid() const noexcept
{
    // check the sign and value of the leading coefficients
    if (a_ < static_cast<ScalarType>(0.0))
    {
        return false;
    }
    else if (ScalarEqualT<ScalarType>()(a_, static_cast<ScalarType>(0.0)))
    {
        if (b_ < static_cast<ScalarType>(0.0))
        {
            return false;
        }
        else if (ScalarEqualT<ScalarType>()(b_, static_cast<ScalarType>(0.0)) &&
                 !ScalarEqualT<ScalarType>()(c_, static_cast<ScalarType>(0.0)))
        {
            return false;
        }
    }

    return true;
}

template <typename T>
typename Line2T<T>::ScalarType Line2T<T>::Dist(Point2Type const& p) const noexcept
{
    return std::fabs(a_ * p.GetX() + b_ * p.GetY() + c_);
}

template <typename T>
typename Line2T<T>::Point2Type Line2T<T>::Project(Point2Type const& p) const noexcept
{
    ScalarType x = b_ * (b_ * p.GetX() - a_ * p.GetY()) - a_ * c_;
    ScalarType y = a_ * (a_ * p.GetY() - b_ * p.GetX()) - b_ * c_;
    return Point2Type(x, y);
}

template <typename T>
bool_t Line2T<T>::IsParallel(Line2T const& other, ScalarType const tol) const noexcept
{
    return std::fabs(a_ * other.b_ - b_ * other.a_) <= tol;
}

template <typename T>
bool_t Line2T<T>::Intersect(Line2T const& other, Point2Type& p) const noexcept
{
    if (IsParallel(other))
    {
        return false;
    }

    // convert to the same vector type
    Vector3Type vec = GetCoeffs().Cross(other.GetCoeffs());
    p.Set(vec(0u) / vec(2u), vec(1u) / vec(2u));

    return true;
}

template <typename T>
typename Line2T<T>::Vector2Type Line2T<T>::GetNormal() const noexcept
{
    return Vector2Type(a_, b_);
}

template <typename T>
typename Line2T<T>::Vector2Type Line2T<T>::GetDirection() const noexcept
{
    // the vector has already been normalized
    Vector2Type vec(b_, -a_);

    // reinforce the first nonzero element to be positive
    if ((vec(0u) < static_cast<ScalarType>(0.0)) ||
        (vec(0u) == static_cast<ScalarType>(0.0) && vec(1u) < static_cast<ScalarType>(0.0)))
    {
        vec *= static_cast<ScalarType>(-1.0);
    }
    return vec;
}

template <typename T>
typename Line2T<T>::Vector3Type Line2T<T>::GetCoeffs() const noexcept
{
    return Vector3Type(a_, b_, c_);
}

template <typename T>
void Line2T<T>::Normalize() noexcept
{
    ScalarType norm = std::sqrt(a_ * a_ + b_ * b_);

    // normalize
    if (norm > ScalarEqualT<T>().GetEpsilonValue())
    {
        a_ /= norm;
        b_ /= norm;
        c_ /= norm;
    }
    if (std::fabs(a_) <= ScalarEqualT<T>().GetEpsilonValue())
    {
        a_ = static_cast<ScalarType>(0.0);
    }
    if (std::fabs(b_) <= ScalarEqualT<T>().GetEpsilonValue())
    {
        b_ = static_cast<ScalarType>(0.0);
    }
    if (std::fabs(c_) <= ScalarEqualT<T>().GetEpsilonValue())
    {
        c_ = static_cast<ScalarType>(0.0);
    }
}

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // HOLO_GEOMETRY_LINE2_HPP_
