/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file plane3.h
 * @brief this file defines a plane in 3D
 * @author Yanwei. Du (duyanwei@holomatic.com)
 * @date Mar-08-2021
 */

#ifndef HOLO_GEOMETRY_DETAILS_PLANE3_H_
#define HOLO_GEOMETRY_DETAILS_PLANE3_H_

#include <string>

#include <holo/core/epsilon.h>
#include <holo/core/exception.h>
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
 * @brief this class defines a plane in 3D
 *
 *
 * @details plane equation: \f$ a * x + b * y + c * z + d = 0 $\f, the plane's normal vector is normalized,
 *          i.e. ||(a, b, c)|| = 1
 * @ref http://mathworld.wolfram.com/Plane.html
 * @tparam T floating type
 */
template <typename T>
class Plane3T
{
public:
    using ScalarType                = T;
    using Point3Type                = Point3T<ScalarType>;
    using Plane3Type                = Plane3T<ScalarType>;
    using Vector3Type               = Vector3T<ScalarType>;
    using Vector4Type               = Vector4T<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    /**
     * @brief Construct a new Plane 3 T object
     *
     * @details a xy plane is defined (i.e. z = 0)
     *
     */
    Plane3T() noexcept : Plane3T(0.0, 0.0, static_cast<ScalarType>(1.0), 0.0)
    {
    }

    /**
     * @brief Construct a new Plane 3 T object from three points on the plane
     *
     * @param p1 point1
     * @param p2 point2
     * @param p3 point3
     * @throw std::runtime_error if p1, p2, p3 do not form a plane
     */
    Plane3T(const Point3Type& p1, const Point3Type& p2, const Point3Type& p3)
      : Plane3T(p1, static_cast<Vector3Type>(p2.template As<Vector3Type>() - p1.template As<Vector3Type>())
                        .Cross(p3.template As<Vector3Type>() - p1.template As<Vector3Type>()))
    {
    }

    /**
     * @brief Construct a new Plane 3 T object a point and a normal vector
     *
     * @param p point on the plane
     * @param v normal vector of the plane
     * @throw std::runtime_error if p and v do not form a plane
     */
    Plane3T(const Point3Type& p, const Vector3Type& v)
      : Plane3T(v(0), v(1), v(2), -p.GetX() * v(0) - p.GetY() * v(1) - p.GetZ() * v(2))
    {
    }

    /**
     * @brief Construct a new Plane 3 T object
     *
     * @param a coefficient a
     * @param b coefficient b
     * @param c coefficient c
     * @param d coefficient d
     * @throw std::runtime_error if a, b, c, d does not form a plane
     */
    Plane3T(ScalarType a, ScalarType b, ScalarType c, ScalarType d) : a_(a), b_(b), c_(c), d_(d)
    {
        normalize();
    }

    /**
     * @brief Construct a new Plane 3 T object
     *
     * @param other the other plane
     */
    Plane3T(const Plane3T& other) noexcept : a_(other.a_), b_(other.b_), c_(other.c_), d_(other.d_)
    {
    }

    /**
     * @brief Destroy the Plane 3 T object
     *
     */
    ~Plane3T() noexcept
    {
    }

    /**
     * @brief assignment operator
     *
     * @param other the other plane
     * @return Plane3T&
     */
    Plane3T& operator=(const Plane3T& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        this->a_ = other.a_;
        this->b_ = other.b_;
        this->c_ = other.c_;
        this->d_ = other.d_;
        return *this;
    }

    /**
     * @brief check if two planes are equal
     *
     * @param other the other plane
     * @return bool_t
     */
    bool_t operator==(const Plane3T& other) const noexcept
    {
        return IsEqual(other);
    }

    /**
     * @brief output stream
     *
     * @param os std::ostream
     * @param plane plane
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const Plane3Type& plane) noexcept
    {
        os << plane.ToString();
        return os;
    }

    /**
     * @brief
     *
     * @return std::string
     */
    std::string ToString() const noexcept
    {
        std::stringstream ss;
        ss << "plane3: (" << a_ << ",  " << b_ << ", " << c_ << ", " << d_ << ")";
        return ss.str();
    }

    /**
     * @brief check if a point is on the plane, within a threshold
     *
     * @param pt point
     * @param tol tolerance
     * @return true
     * @return false
     */
    bool_t Contains(const Point3Type& pt, const ScalarType tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept
    {
        return (Dist(pt) <= tol);
    }

    /**
     * @brief check if two planes are equal
     *
     * @param other the other plane
     * @param tol tolerance
     * @return bool_t
     */
    bool_t IsEqual(const Plane3T& other, const ScalarType tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept
    {
        return Parallel(other, tol) && std::fabs(std::fabs(other.d_) - std::fabs(d_)) <= tol;
    }

    /**
     * @brief check if the plane is valid
     *
     * @return true
     * @return false
     */
    bool_t IsValid() const noexcept
    {
        bool_t const flag = std::isfinite(a_) && std::isfinite(b_) && std::isfinite(c_);
        if (!flag)
        {
            return false;
        }

        // all zeros
        if (a_ == 0.0 && b_ == 0.0 && c_ == 0.0)
        {
            return false;
        }

        return true;
    }

    /**
     * @brief compute the shortest distance from a point to the plane
     *
     * @param pt point
     * @return ScalarType
     */
    ScalarType Dist(const Point3Type& pt) const noexcept
    {
        return std::fabs(a_ * pt.GetX() + b_ * pt.GetY() + c_ * pt.GetZ() + d_);
    }

    /**
     * @brief compute the nearest point to pt that in on the plane
     *
     * @param pt point
     * @return Point3Type
     */
    Point3Type Project(const Point3Type& pt) const noexcept
    {
        ScalarType const signed_dist = a_ * pt.GetX() + b_ * pt.GetY() + c_ * pt.GetZ() + d_;
        return Point3Type(pt.GetX() - signed_dist * a_, pt.GetY() - signed_dist * b_, pt.GetZ() - signed_dist * c_);
    }

    /**
     * @brief check if two planes are parallel
     *
     * @param other the other plane
     * @param tol tolerance
     * @return bool_t
     */
    bool_t Parallel(const Plane3T& other, const ScalarType tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
    {
        Vector3Type const vec = GetNormal().Cross(other.GetNormal());
        return vec.GetNorm() <= tol;
    }

    /**
     * @brief find the dihedral angle in radian of two planes
     *
     * @param other the other plane
     * @return ScalarType
     */
    ScalarType DihedralAngle(const Plane3T& other) const noexcept
    {
        // get cos theta
        ScalarType ctheta = std::fabs(GetNormal().Dot(other.GetNormal()));

        // range check
        if (ctheta < -1.0)
        {
            ctheta = static_cast<ScalarType>(-1.0);
        }
        else if (ctheta > 1.0)
        {
            ctheta = static_cast<ScalarType>(1.0);
        }

        return std::acos(ctheta);  // [-pi, pi]
    }

    /**
     * @brief get the normal vector of the plane
     *
     * @return Vector3Type
     */
    Vector3Type GetNormal() const noexcept
    {
        return Vector3Type(a_, b_, c_);
    }

    /**
     * @brief return the coefficients vector
     */
    Vector4Type GetCoeffs() const noexcept
    {
        return Vector4Type(a_, b_, c_, d_);
    }

protected:
    /**
     * @brief for internal data normalization
     *
     * @throw std::runtime_error if plane is not valid
     */
    void normalize()
    {
        ScalarType const norm = std::sqrt(a_ * a_ + b_ * b_ + c_ * c_);

        if (norm <= ScalarEqualT<ScalarType>().GetEpsilonValue())
        {
            throw std::runtime_error("invalid plane coefficients");
        }

        // normalize
        a_ /= norm;
        b_ /= norm;
        c_ /= norm;
        d_ /= norm;

        if (ScalarEqualT<ScalarType>()(a_, static_cast<ScalarType>(0.0)))
        {
            a_ = 0.0;
        }
        if (ScalarEqualT<ScalarType>()(b_, static_cast<ScalarType>(0.0)))
        {
            b_ = 0.0;
        }
        if (ScalarEqualT<ScalarType>()(c_, static_cast<ScalarType>(0.0)))
        {
            c_ = 0.0;
        }
        if (ScalarEqualT<ScalarType>()(d_, static_cast<ScalarType>(0.0)))
        {
            d_ = 0.0;
        }
    }

    /**
     * @brief internal data layout
     */
    union
    {
        ScalarType data_[4u];
        struct
        {
            ScalarType a_, b_, c_, d_;
        };
    };

};  // Plane3T

}  // namespace details

}  // namespace geometry

}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_PLANE3_H_