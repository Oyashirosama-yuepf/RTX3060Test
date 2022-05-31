/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line_segment2.hpp
 * @brief a line segment in 2D space
 * @author duyanwei@holomatic.com
 * @date 2020-09-24
 */

#ifndef HOLO_GEOMETRY_DETAILS_IMPL_LINE_SEGMENT2_HPP_
#define HOLO_GEOMETRY_DETAILS_IMPL_LINE_SEGMENT2_HPP_

namespace holo
{
namespace geometry
{
namespace details
{
template <typename T>
LineSegment2T<T>::LineSegment2T() noexcept : LineSegment2T(Point2Type::Zero(), Point2Type::UnitY())
{
}

template <typename T>
LineSegment2T<T>::LineSegment2T(Point2Type const& p1, Point2Type const& p2)
{
    // direction vector
    Point2Type v = p2 - p1;

    if (ScalarEqualT<T>()(v[0u], static_cast<T>(0.0)))
    {
        v[0u] = static_cast<ScalarType>(0.0);
    }

    if (ScalarEqualT<T>()(v[1u], static_cast<T>(0.0)))
    {
        v[1u] = static_cast<ScalarType>(0.0);
    }

    // assign value
    x_  = p1.GetX();
    y_  = p1.GetY();
    v0_ = v[0u];
    v1_ = v[1u];

    // valid checking
    if (!IsValid())
    {
        std::stringstream ss;
        ss << "LineSegment2T --- invalid linesegment coefficients: " << *this;
        throw std::runtime_error(ss.str());
    }
}

template <typename T>
LineSegment2T<T>::LineSegment2T(LineSegment2T const& other) noexcept
  : x_(other.x_), y_(other.y_), v0_(other.v0_), v1_(other.v1_)
{
}

template <typename T>
LineSegment2T<T>::~LineSegment2T() noexcept
{
}

template <typename T>
LineSegment2T<T>& LineSegment2T<T>::operator=(LineSegment2T const& other) noexcept
{
    x_  = other.x_;
    y_  = other.y_;
    v0_ = other.v0_;
    v1_ = other.v1_;

    return *this;
}

template <typename T>
bool_t LineSegment2T<T>::operator==(LineSegment2T const& other) const noexcept
{
    return IsEqual(other);
}

template <typename T>
bool_t LineSegment2T<T>::Contains(Point2Type const& pt, ScalarType const tol) const noexcept
{
    return Dist(pt) <= tol;
}

template <typename T>
bool_t LineSegment2T<T>::IsEqual(LineSegment2T const& other, ScalarType const tol) const noexcept
{
    return (std::fabs(other.x_ - x_) <= tol && std::fabs(other.y_ - y_) <= tol && std::fabs(other.v0_ - v0_) <= tol &&
            std::fabs(other.v1_ - v1_) <= tol);
}

template <typename T>
bool_t LineSegment2T<T>::IsValid() const noexcept
{
    if (ScalarEqualT<T>()(v0_, static_cast<T>(0.0)) && ScalarEqualT<T>()(v1_, static_cast<T>(0.0)))
    {
        return false;
    }
    return true;
}

template <typename T>
typename LineSegment2T<T>::ScalarType LineSegment2T<T>::Dist(Point2Type const& pt) const noexcept
{
    // find projection of v onto line segment
    const Point2Type pt_p = Project(pt);

    // return the distance of two points
    return pt.Dist(pt_p);
}

template <typename T>
typename LineSegment2T<T>::Point2Type LineSegment2T<T>::Project(Point2Type const& pt) const noexcept
{
    // vector connects pt and start point of line segment
    Point2Type q = pt - GetStartPoint();

    // projection of v onto line segment
    ScalarType t = q.ToVector().Dot(GetDirection());

    if (t > GetLength())
    {
        // pt is close to endpoint of line segment
        q = pt - GetEndPoint();
    }
    else if (t > static_cast<ScalarType>(0.0))
    {
        // pt is within the ragne of line segment
        q = pt - Interpolate(t / GetLength());
    }

    return pt - q;
}

template <typename T>
bool LineSegment2T<T>::IsParallel(LineSegment2T const& other, ScalarType const tol) const noexcept
{
    Vector4Type lsv = other.GetCoeffs();
    return std::fabs(v1_ * lsv(2u) - v0_ * lsv(3u)) <= tol;
}

template <typename T>
bool LineSegment2T<T>::Intersect(LineSegment2T const& other, Point2Type& pt) const noexcept
{
    // construct lines from line segments
    Line2T<ScalarType> l1(GetStartPoint(), GetEndPoint());
    Line2T<ScalarType> l2(other.GetStartPoint(), other.GetEndPoint());

    return l1.Intersect(l2, pt) && other.Contains(pt) && Contains(pt);
}

template <typename T>
typename LineSegment2T<T>::Point2Type LineSegment2T<T>::Interpolate(ScalarType const t) const noexcept
{
    return Point2Type(x_ + v0_ * t, y_ + v1_ * t);
}

template <typename T>
typename LineSegment2T<T>::Point2Type LineSegment2T<T>::GetStartPoint() const noexcept
{
    return Interpolate(static_cast<ScalarType>(0.0));
}

template <typename T>
typename LineSegment2T<T>::Point2Type LineSegment2T<T>::GetEndPoint() const noexcept
{
    return Interpolate(static_cast<ScalarType>(1.0));
}

template <typename T>
typename LineSegment2T<T>::ScalarType LineSegment2T<T>::GetLength() const noexcept
{
    return std::sqrt(v0_ * v0_ + v1_ * v1_);
}

template <typename T>
typename LineSegment2T<T>::Vector2Type LineSegment2T<T>::GetNormal() const noexcept
{
    Vector2Type vec(-v1_, v0_);
    if (vec(0u) < static_cast<ScalarType>(0.0) ||
        (vec(0u) == static_cast<ScalarType>(0.0) && vec(1u) < static_cast<ScalarType>(0.0)))
    {
        vec *= static_cast<ScalarType>(-1);
    }
    vec.Normalize();
    return vec;
}

template <typename T>
typename LineSegment2T<T>::Vector2Type LineSegment2T<T>::GetDirection() const noexcept
{
    Vector2Type v(v0_, v1_);
    v.Normalize();
    return v;
}

template <typename T>
typename LineSegment2T<T>::Vector4Type LineSegment2T<T>::GetCoeffs() const noexcept
{
    return Vector4Type(x_, y_, v0_, v1_);
}

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_IMPL_LINE_SEGMENT2_HPP_
