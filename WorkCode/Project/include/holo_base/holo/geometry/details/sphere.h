/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sphere.h
 * @brief this file defines a sphere
 * @author Yanwei. Du (duyanwei@holomatic.com)
 * @date Mar-05-2021
 */

#ifndef HOLO_GEOMETRY_DETAILS_SPHERE_H_
#define HOLO_GEOMETRY_DETAILS_SPHERE_H_

#include <string>

#include <holo/core/epsilon.h>
#include <holo/core/exception.h>
#include <holo/geometry/details/pose3.h>
#include <holo/geometry/details/sphere_point3.h>

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
 * @brief this class defines a sphere
 *
 * @tparam T floating type
 */
template <typename T>
class Sphere3T
{
public:
    using ScalarType                = T;
    using Pose3Type                 = Pose3T<ScalarType>;
    using Point3Type                = Point3T<ScalarType>;
    using Rot3Type                  = Rot3T<ScalarType>;
    using SPoint3Type               = SpherePoint3T<ScalarType>;
    using Sphere3Type               = Sphere3T<ScalarType>;
    using EpsilonType [[deprecated]] = EpsilonT<ScalarType>;

    /**
     * @brief Construct a new Sphere 3 T object
     *
     * @details an unit sphere is created
     *
     */
    Sphere3T() noexcept : Sphere3T(static_cast<ScalarType>(1.0))
    {
    }

    /**
     * @brief Construct a new Sphere 3 T object
     *
     * @param r radius in meter
     */
    Sphere3T(ScalarType r) noexcept : pose_(Pose3Type::Identity()), radius_(r)
    {
    }

    /**
     * @brief Construct a new Sphere 3 T object
     *
     * @param pose pose
     * @param r radius in meter
     */
    Sphere3T(const Pose3Type& pose, ScalarType r) noexcept : pose_(pose), radius_(r)
    {
    }

    /**
     * @brief Construct a new Sphere 3 T object
     *
     * @param p point of pose in meter
     * @param r radius in meter
     */
    Sphere3T(const Point3Type& p, ScalarType r) noexcept : pose_(Pose3Type(Rot3Type(), p)), radius_(r)
    {
    }

    /**
     * @brief Construct a new Sphere 3 T object
     *
     * @param other the other sphere
     */
    Sphere3T(const Sphere3T& other) noexcept : pose_(other.pose_), radius_(other.radius_)
    {
    }

    /**
     * @brief Destroy the Sphere 3 T object
     *
     */
    ~Sphere3T() noexcept
    {
    }

    /**
     * @brief assignment operator
     *
     * @param other other sphere
     * @return Sphere3T&
     */
    Sphere3T& operator=(const Sphere3T& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        this->pose_   = other.pose_;
        this->radius_ = other.radius_;
        return *this;
    }

    /**
     * @brief check if two spheres are equal
     *
     * @param other the other sphere
     * @return true
     * @return false
     */
    bool_t operator==(const Sphere3T& other) const noexcept
    {
        return IsEqual(other);
    }

    /**
     * @brief output stream
     *
     * @param os std::ostream
     * @param s sphere
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const Sphere3Type& s) noexcept
    {
        os << s.ToString();
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
        ss << "Sphere: radius = " << radius_ << ", pose = " << pose_;
        return ss.str();
    }

    /**
     * @brief check if a point is in sphere
     *
     * @param p point
     * @param tol tolerance
     * @return bool_t
     */
    bool_t Contains(const Point3Type& p, const ScalarType tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept
    {
        return (pose_.GetTranslation().Dist(p) < radius_ + tol);
    }

    /**
     * @brief check if a point is in sphere
     *
     * @param p sphere point
     * @param tol tolerance
     * @return bool_t
     */
    bool_t Contains(const SPoint3Type& p, const ScalarType tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept
    {
        return Contains(p.ToPoint3(), tol);
    }

    /**
     * @brief check if two sphere are equal
     *
     * @param s
     * @param tol
     * @return bool_t
     */
    bool_t IsEqual(const Sphere3T& s, const ScalarType tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept
    {
        return pose_.IsEqual(s.pose_, tol) && std::fabs(radius_ - s.radius_) <= tol;
    }

    /**
     * @brief check if the sphere is valid
     *
     * @return bool_t
     */
    bool_t IsValid() const noexcept
    {
        return (radius_ > ScalarEqualT<ScalarType>().GetEpsilonValue()) && (pose_.IsValid());
    }

    /**
     * @brief return volume of the sphere
     *
     * @return ScalarType
     */
    ScalarType GetVolume() const noexcept
    {
        return 4.0 / 3.0 * M_PI * radius_ * radius_ * radius_;
    }

    /**
     * @brief get center
     *
     * @return const Point3Type&
     */
    const Point3Type& GetCenter() const noexcept
    {
        return pose_.GetTranslation();
    }

    /**
     * @brief get pose
     *
     * @return const Pose3Type&
     */
    const Pose3Type& GetPose() const noexcept
    {
        return pose_;
    }

    /**
     * @brief get radius
     *
     * @return ScalarType
     */
    ScalarType GetRadius() const noexcept
    {
        return radius_;
    }

    /**
     * @brief Set the Radius object
     *
     * @param radius the radius
     */
    void SetRadius(ScalarType const& radius) noexcept
    {
        radius_ = radius;
    }

protected:
    Pose3Type  pose_;    ///< pose of the sphere
    ScalarType radius_;  ///< radius of the sphere

};  // Sphere3T

}  // namespace details

}  // namespace geometry

}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_SPHERE3_H_