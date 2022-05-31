/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sphere_point3.h
 * @brief define point3 on a sphere
 * @author Yanwei. Du (duyanwei@holomatic.com)
 * @date Mar-05-2021
 */

#ifndef HOLO_GEOMETRY_DETAILS_SPHERE_POINT3_H_
#define HOLO_GEOMETRY_DETAILS_SPHERE_POINT3_H_

#include <string>

#include <holo/core/epsilon.h>
#include <holo/core/exception.h>
#include <holo/geometry/details/point3.h>

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
 * @brief This class defines a 3d point in spherical coordinate.
 *
 * @details
 *     rho: is the depth, the distance between the sphere center and the points, which is local sphere coordinate.
 *     phi: is the angle between the directed line and the positive Z axis, range 0-pi, phi 0 means positive z, phi pi/2
 *          means positive x.
 *     theta: is the angle around the Z axis, turn the counterclockwise direction from the X axis, range 0-2pi, theta 0
 *            means positive x, theta pi/2 means positive y.
 *
 * @ref https://en.wikipedia.org/wiki/Sphere
 *
 * @tparam T floating type
 */
template <typename T>
class SpherePoint3T
{
public:
    using ScalarType                = T;
    using Point3Type                = Point3T<ScalarType>;
    using SpherePoint3Type          = SpherePoint3T<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    /**
     * @brief default constructor
     *
     * @details a point of unit length is created
     */
    SpherePoint3T() noexcept : SpherePoint3T(1.0, 0.0, 0.0)
    {
    }

    /**
     * @brief Construct a new Sphere Point 3 T object
     *
     * @param rho /f$\rho/f$
     * @param phi /f$\phi/f$
     * @param theta /f$\theta\f$
     */
    SpherePoint3T(ScalarType rho, ScalarType phi, ScalarType theta) noexcept : rho_(rho), phi_(phi), theta_(theta)
    {
        if (ScalarEqualT<ScalarType>()(theta_, 2.0 * M_PI))
        {
            theta_ = 0.0;
        }
    }

    /**
     * @brief Construct a new Sphere Point 3 T object
     *
     * @ref atan2() produces results in the range(-pi, pi] which can be mapped to
     *      [0, 2 * pi).Please reference: www.thefullwiki.org/Atan
     *
     * @param p point3
     */
    SpherePoint3T(Point3Type const& p) noexcept
    {
        rho_ = p.Dist(Point3Type::Zero());

        // negative means invalid
        phi_   = (rho_ == 0.0) ? static_cast<ScalarType>(-1.0) : std::acos(p.GetZ() / rho_);
        theta_ = std::atan2(p.GetY(), p.GetX());

        if (theta_ < 0.0)
        {
            theta_ += static_cast<ScalarType>(2.0 * M_PI);
        }

        if (ScalarEqualT<ScalarType>()(theta_, 2.0 * M_PI))
        {
            theta_ = 0.0;
        }
    }

    /**
     * @brief Construct a new Sphere Point 3 T object
     *
     * @param other input sphere point
     */
    SpherePoint3T(SpherePoint3T const& other) noexcept : rho_(other.rho_), phi_(other.phi_), theta_(other.theta_)
    {
    }

    /**
     * @brief Destroy the Sphere Point 3 T object
     *
     */
    ~SpherePoint3T() noexcept
    {
    }

    /**
     * @brief assignment operator
     *
     * @param other other point
     * @return SpherePoint3T&
     */
    SpherePoint3T& operator=(SpherePoint3T const& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        this->rho_   = other.rho_;
        this->phi_   = other.phi_;
        this->theta_ = other.theta_;

        return *this;
    }

    /**
     * @brief check if two points are equal
     *
     * @param other other point
     * @return true
     * @return false
     */
    bool_t operator==(SpherePoint3T const& other) const noexcept
    {
        return IsEqual(other);
    }

    /**
     * @brief check if two points are equal
     *
     * @param other other point
     * @return true
     * @return false
     */
    bool_t operator==(Point3Type const& other) const noexcept
    {
        return IsEqual(other);
    }

    /**
     * @brief output stream
     *
     * @param os os stream
     * @param sp sphere point
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, SpherePoint3T const& sp) noexcept
    {
        os << sp.ToString();
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
        ss << "Sphere point: rho(" << rho_ << ") phi(" << phi_ << ") theta(" << theta_ << ")";
        return ss.str();
    }

    /**
     * @brief check if two points are equal
     *
     * @param target target point
     * @param threshold threshold
     * @return bool_t
     */
    bool_t IsEqual(Point3Type const& target, ScalarType threshold = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept
    {
        return IsEqual(SpherePoint3Type(target), threshold);
    }

    /**
     * @brief check if two points are equal
     *
     * @param target target point
     * @param threshold threshold
     * @return bool_t
     */
    bool_t IsEqual(SpherePoint3Type const& target,
                   ScalarType              threshold = ScalarEqualT<ScalarType>().GetEpsilonValue()) const noexcept
    {
        return (std::fabs(rho_ - target.rho_) <= threshold) && (std::fabs(phi_ - target.phi_) <= threshold) &&
               (std::fabs(theta_ - target.theta_) <= threshold);
    }

    /**
     * @brief check if sphere point is valid
     *
     * @return bool_t
     */
    bool_t IsValid() const noexcept
    {
        return IsFinite() && (rho_ > 0.0) && (phi_ >= 0.0 && phi_ <= M_PI) && (theta_ >= 0.0 && theta_ < (2.0 * M_PI));
    }

    /**
     * @brief check if the data is finite
     *
     * @return bool_t
     */
    bool_t IsFinite() const noexcept
    {
        return std::isfinite(rho_) && std::isfinite(phi_) && std::isfinite(theta_);
    }

    /**
     * @brief given spherical polar coordinates to transform into spatial points
     *
     * @return Point3Type
     */
    Point3Type ToPoint3() const noexcept
    {
        const T temp = rho_ * std::sin(phi_);
        return Point3Type(temp * std::cos(theta_), temp * std::sin(theta_), rho_ * std::cos(phi_));
    }

    /**
     * @brief return rho
     *
     * @return ScalarType
     */
    ScalarType GetRho() const
    {
        return rho_;
    }

    /**
     * @brief Get the Phi object
     *
     * @return ScalarType
     */
    ScalarType GetPhi() const
    {
        return phi_;
    }

    /**
     * @brief Get the Theta object
     *
     * @return ScalarType
     */
    ScalarType GetTheta() const
    {
        return theta_;
    }

private:
    /**
     * @brief internal memory layout
     *
     */
    union
    {
        ScalarType data_[3];
        struct
        {
            ScalarType rho_;    ///< the distance between the sphere center and the point
            ScalarType phi_;    ///< included angle to z axis
            ScalarType theta_;  ///< included angle to x axis
        };
    };

};  // class SpherePoint3T

}  // namespace details

}  // namespace geometry

}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_SPHERE_POINT3_H_
