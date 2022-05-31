/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line_segment3.h
 * @brief this file defines a line segment in 3D
 * @author Yanwei. Du (duyanwei@holomatic.com)
 * @date Mar-10-2021
 */

#ifndef HOLO_GEOMETRY_DETAILS_LINE_SEGMENT3_H_
#define HOLO_GEOMETRY_DETAILS_LINE_SEGMENT3_H_

#include <string>

#include <holo/core/epsilon.h>
#include <holo/core/exception.h>
#include <holo/geometry/details/plane3.h>
#include <holo/geometry/details/point3.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace geometry
{
namespace details
{
/**
 * @addtogroup geometry
 * @{
 *
 */

/**
 * @brief this class defines a line segment in 3D
 *
 *
 * @details a line segment equation: pt + t * v, where t is in range of [0,1],
 *          in vector form the coefficients are [pt.x, pt.y, pt.z, v(0), v(1), v(2)]
 * @tparam T floating type
 */
template <typename T>
class LineSegment3T
{
public:
    using ScalarType                = T;
    using Point3Type                = Point3T<ScalarType>;
    using Plane3Type                = Plane3T<ScalarType>;
    using LineSegment3Type          = LineSegment3T<ScalarType>;
    using Vector3Type               = Vector3T<ScalarType>;
    using Vector6Type               = Vector6T<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    /**
     * @brief Construct a new LineSegment3 T object
     *
     */
    LineSegment3T() noexcept : LineSegment3T(Point3Type(0.0, 0.0, 0.0), Point3Type(0.0, 0.0, static_cast<ScalarType>(1.0)))
    {
    }

    /**
     * @brief Construct a new LineSegment3 T object from two points
     *
     * @param p1 point 1
     * @param p2 point 2
     */
    LineSegment3T(const Point3Type& p1, const Point3Type& p2) noexcept
    {
        // direction vector
        Vector3Type v = p2.ToVector() - p1.ToVector();

        if (ScalarEqualT<ScalarType>()(v(0), static_cast<ScalarType>(0.0)))
        {
            v(0) = 0.0;
        }

        if (ScalarEqualT<ScalarType>()(v(1), static_cast<ScalarType>(0.0)))
        {
            v(1) = 0.0;
        }

        if (ScalarEqualT<ScalarType>()(v(2), static_cast<ScalarType>(0.0)))
        {
            v(2) = 0.0;
        }

        // assign value
        x_  = p1.GetX();
        y_  = p1.GetY();
        z_  = p1.GetZ();
        v0_ = v(0);
        v1_ = v(1);
        v2_ = v(2);
    }

    /**
     * @brief Construct a new LineSegment3 T object
     *
     * @param other the other line
     */
    LineSegment3T(const LineSegment3T& other) noexcept
      : x_(other.x_), y_(other.y_), z_(other.z_), v0_(other.v0_), v1_(other.v1_), v2_(other.v2_)
    {
    }

    /**
     * @brief Destroy the LineSegment3 T object
     *
     */
    ~LineSegment3T() noexcept
    {
    }

    /**
     * @brief assignment operator
     *
     * @param other the other line segment3
     * @return LineSegment3T&
     */
    LineSegment3T& operator=(const LineSegment3T& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        this->x_  = other.x_;
        this->y_  = other.y_;
        this->z_  = other.z_;
        this->v0_ = other.v0_;
        this->v1_ = other.v1_;
        this->v2_ = other.v2_;

        return *this;
    }

    /**
     * @brief check if the two line segments are equal
     *
     * @param other the other line segment
     * @return bool_t
     */
    bool_t operator==(const LineSegment3T& other) const noexcept
    {
        return IsEqual(other);
    }

    /**
     * @brief output stream
     *
     * @param os std::ostream
     * @param line_segment line segment
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const LineSegment3T<T>& line_segment) noexcept
    {
        os << line_segment.ToString();
        return os;
    }

    /**
     * @brief convert to string
     *
     * @return std::string
     */
    std::string ToString() const noexcept
    {
        std::stringstream ss;
        ss << "lineSegment3: start point (" << x_ << ", " << y_ << ", " << z_ << "), direction (" << v0_ << ", " << v1_
           << ", " << v2_ << ")";
        return ss.str();
    }

    /**
     * @brief check if a point is on the line segment, within a threshold
     *
     * @param pt point
     * @param tol tolerance
     * @return bool_t
     */
    bool_t Contains(const Point3Type& pt, const ScalarType tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept
    {
        return (Dist(pt) <= tol);
    }

    /**
     * @brief check if two line segments are equal
     *
     * @param other the other line segment
     * @param tol tolerance
     * @return bool_t
     */
    bool_t IsEqual(const LineSegment3T& other,
                   const ScalarType     tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const noexcept
    {
        return (std::fabs(other.x_ - x_) <= tol && std::fabs(other.y_ - y_) <= tol && std::fabs(other.z_ - z_) <= tol &&
                std::fabs(other.v0_ - v0_) <= tol && std::fabs(other.v1_ - v1_) <= tol &&
                std::fabs(other.v2_ - v2_) <= tol);
    }

    /**
     * @brief check if the line segment is valid
     *
     * @return bool_t
     */
    bool_t IsValid() const noexcept
    {
        if (v0_ == 0.0 && v1_ == 0.0 && v2_ == 0.0)
        {
            return false;
        }

        return true;
    }

    /**
     * @brief compute the shortest distance from a point to the line segment
     *
     * @param pt point
     * @return ScalarType
     */
    ScalarType Dist(const Point3Type& pt) const noexcept
    {
        // find projection of v onto line segment
        Point3Type pt_p = Project(pt);

        // return the distance of two points
        return pt.Dist(pt_p);
    }

    /**
     * @brief compute the nearest point to pt that in on the line segment
     *
     * @param pt point
     * @return Point3Type
     */
    Point3Type Project(const Point3Type& pt) const noexcept
    {
        // vector connects pt and start point of line segment
        Vector3Type v = pt.ToVector() - GetStartPoint().ToVector();

        // projection of v onto line segment
        ScalarType t = v.Dot(GetDirection());

        if (t > GetLength())
        {
            // pt is close to endpoint of line segment
            v = pt.ToVector() - GetEndPoint().ToVector();
        }
        else if (t > 0.0)
        {
            // pt is within the ragne of line segment
            v = pt.ToVector() - Interpolate(t / GetLength()).ToVector();
        }

        return pt - Point3Type(v(0), v(1), v(2));
    }

    /**
     * @brief check if two line segments are parallel
     *
     * @param other the other line
     * @param tol tolerance
     *
     */
    bool_t IsParallel(const LineSegment3T& other,
                      const ScalarType     tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const noexcept
    {
        Vector3Type vec = GetDirection().Cross(other.GetDirection());
        return vec.GetNorm() <= tol;
    }

    /**
     * @brief find the intersect point of the other line segment
     *
     * @param other the other linesegment
     * @param pt the intersect point
     * @return true
     * @return false
     */
    bool_t Intersect(const LineSegment3T& other, Point3Type& pt) const
    {
        if (IsParallel(other) || IsSkew(other))
        {
            return false;
        }

        // compute intersection point on the other line segment
        Vector3Type v0 = GetCoeffs().GetTail(3);
        Vector3Type v1 = other.GetCoeffs().GetTail(3);
        Vector3Type v  = v0.Cross(v1);
        ScalarType  t1 =
            v.Dot(v0.Cross((GetStartPoint() - other.GetStartPoint()).template As<Vector3Type>())) / v.Dot(v);

        // check if point is on the other line segment
        if (t1 > 1.0 || t1 < 0.0)
        {
            return false;
        }

        // compute point on the other line segment
        pt = other.Interpolate(t1);

        return true;
    }

    /**
     * @brief find the intersect of plane
     *
     * @param plane plane
     * @param pt the intersect point
     * @return bool_t
     */
    bool_t Intersect(const Plane3Type& plane, Point3Type& pt) const
    {
        if (!plane.IsValid())
        {
            return false;
        }

        Vector3Type n = plane.GetNormal();

        // check if the line segment is parallel to the plane
        if (n.Dot(GetDirection()) == 0.0)
        {
            return false;
        }

        // compute intersection point on the line and plane
        ScalarType n_w = n(0) * x_ + n(1) * y_ + n(2) * z_ + plane.GetCoeffs()(3);
        ScalarType n_u = n(0) * v0_ + n(1) * v1_ + n(2) * v2_;
        ScalarType s   = -n_w / n_u;
        if (s < 0.0 || s > 1.0)
        {
            return false;
        }
        else
        {
            pt = Interpolate(s);
        }
        return true;
    }

    /**
     * @brief check if two line segments are skew
     * @ref https://en.wikipedia.org/wiki/Skew_lines
     *
     * @param other the other line segment
     * @param tol tolerance
     * @return bool_t
     */
    bool_t IsSkew(const LineSegment3T& other, const ScalarType tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
    {
        Vector3Type a   = (GetStartPoint() - GetEndPoint()).template As<Vector3Type>();
        Vector3Type b   = (other.GetStartPoint() - GetEndPoint()).template As<Vector3Type>();
        Vector3Type c   = (other.GetEndPoint() - GetEndPoint()).template As<Vector3Type>();
        ScalarType  vol = std::fabs(a.Dot(b.Cross(c)) / 6.0);

        return vol > tol;
    }

    /**
     * @brief interplate
     *
     * @param t range in [0, 1]
     * @return Point3Type
     */
    Point3Type Interpolate(const ScalarType t) const
    {
        return Point3Type(x_ + v0_ * t, y_ + v1_ * t, z_ + v2_ * t);
    }

    /**
     * @brief Get the Start Point object
     *
     * @return Point3Type
     */
    Point3Type GetStartPoint() const
    {
        return Interpolate(0.0);
    }

    /**
     * @brief Get the End Point object
     *
     * @return Point3Type
     */
    Point3Type GetEndPoint() const
    {
        return Interpolate(1.0);
    }

    /**
     * @brief Get the Length object
     *
     * @return ScalarType
     */
    ScalarType GetLength() const
    {
        return std::sqrt(v0_ * v0_ + v1_ * v1_ + v2_ * v2_);
    }

    /**
     * @brief Get the Direction object
     *
     * @return Vector3Type
     */
    Vector3Type GetDirection() const noexcept
    {
        Vector3Type v(v0_, v1_, v2_);
        v.Normalize();
        return v;
    }

    /**
     * @brief Get the coefficients
     *
     * @return Vector6Type
     */
    Vector6Type GetCoeffs() const noexcept
    {
        return Vector6Type(x_, y_, z_, v0_, v1_, v2_);
    }

private:
    /**
     * @brief internal data layout
     *
     */
    union
    {
        ScalarType data_[6];
        struct
        {
            ScalarType x_, y_, z_, v0_, v1_, v2_;
        };
    };
};  // LineSegment3T

}  // namespace details

}  // namespace geometry

}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_LINE_SEGMENT3_H_
