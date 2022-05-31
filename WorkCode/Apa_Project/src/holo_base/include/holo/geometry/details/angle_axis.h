/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file angle_axis.h
 * @brief holo angle_axis type
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date 2019-08-26
 */

#ifndef HOLO_GEOMETRY_DETAILS_ANGLE_AXIS_H_
#define HOLO_GEOMETRY_DETAILS_ANGLE_AXIS_H_

#include <memory>

#include <holo/core/types.h>
#include <holo/geometry/quaternion.h>
#include <holo/geometry/rot3.h>
#include <holo/numerics/matrix.h>
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
 */

/**
 * @brief AngleAxis represents a 3D rotation as a rotation angle (in radian) around an arbitrary 3D axis.
 *
 * @tparam T float32_t or float64_t
 */
template <typename T>
class AngleAxisT
{
public:
    using ScalarType                = T;
    using Vector3Type               = holo::numerics::Vector3T<ScalarType>;
    using Matrix3Type               = holo::numerics::Matrix3T<ScalarType>;
    using Rot3Type                  = Rot3T<ScalarType>;
    using QuaternionType            = QuaternionT<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    static_assert(std::is_floating_point<ScalarType>::value, "AngleAxisT needs to take floating type");

    /**
     * @brief Construct a new Angle Axis object
     *
     * @throw std::bad_alloc if initialization fails
     */
    AngleAxisT();

    /**
     * @brief Construct a new Angle Axis object
     *
     * @details initialize the angle-axis from an angle in radian and an axis which will be normalized inside
     * @param angle angle in radian
     * @param axis axis which will be normalized inside
     * @throw std::runtime_error if axis norm is zero
     * @throw std::bad_alloc if initialization fails
     */
    AngleAxisT(ScalarType const angle, Vector3Type const& axis);

    /**
     * @brief Construct a new Angle Axis T object
     *
     * @param q quaternion
     * @throw std::bad_alloc if initialization fails
     */
    AngleAxisT(QuaternionType const& q);

    /**
     * @brief Construct a new Angle Axis T object
     *
     * @param m rotation matrix in Matrix3Type
     * @throw std::runtime_error if m is not a rotation matrix
     * @throw std::bad_alloc if initialization fails
     */
    AngleAxisT(Matrix3Type const& m);

    /**
     * @brief Construct a new Angle Axis T object
     *
     * @param r rotation matrix in Rot3Type
     * @throw std::bad_alloc if initialization fails
     */
    AngleAxisT(Rot3Type const& r);

    /**
     * @brief Construct a new Angle Axis T object
     *
     * @param other other angle axis
     * @throw std::bad_alloc if initialization fails
     */
    AngleAxisT(AngleAxisT const& other);

    /**
     * @brief destruct
     *
     * @throw std::bad_alloc if it fails to destroy
     */
    ~AngleAxisT() noexcept;

    /**
     * @brief assignment operator
     *
     * @param other other angle axis
     * @return AngleAxisT&
     * @throw std::bad_alloc if assignment fails
     */
    AngleAxisT& operator=(AngleAxisT const& other);

    /**
     * @brief assignment operator from a quaternion
     *
     * @param q other quaternion
     * @return AngleAxisT&
     * @throw std::bad_alloc if assignment fails
     */
    AngleAxisT& operator=(QuaternionType const& q);

    /**
     * @brief assignment operator from a matrix
     *
     * @param m other matrix
     * @return AngleAxisT&
     * @throw std::runtime_error if m is not a rotation matrix
     * @throw std::bad_alloc if assignment fails
     */
    AngleAxisT& operator=(Matrix3Type const& m);

    /**
     * @brief Get the Angle object
     *
     * @return Scalar
     */
    ScalarType GetAngle() const noexcept;

    /**
     * @brief Set the Angle object
     *
     * @param angle angle in radian
     */
    void SetAngle(ScalarType const angle) noexcept;

    /**
     * @brief Get the axis
     *
     * @return Vector3Type
     */
    Vector3Type GetAxis() const noexcept;

    /**
     * @brief Set the Axis object
     *
     * @param axis axis which will be normalized inside
     * @throw std::runtime_error if axis norm is zero
     */
    void SetAxis(Vector3Type const& axis);

    /**
     * @brief take the inverse of angle axis
     *
     * @return AngleAxisT
     */
    AngleAxisT Inverse() const noexcept;

    /**
     * @brief check if two angle axis are equal within some tolerance
     *
     * @param other other angle axis
     * @param tol tolerance
     * @return bool_t
     */
    bool_t IsApprox(AngleAxisT const& other, ScalarType const tol = (ScalarType)0.0) const noexcept;

    /**
     * @brief convert to rotation matrix
     *
     * @return Matrix3Type
     */
    Matrix3Type ToRotationMatrix() const noexcept;

private:
    /**
     * @brief forward declaration of class Implementation
     */
    struct Implementation;

    /**
     * @brief real implementation
     */
    std::unique_ptr<Implementation> impl_ptr_;

};  // class AngleAxisT

/**
 * @}
 *
 */
}  // namespace details
}  // namespace geometry
}  // namespace holo

#include "./impl/angle_axis.hpp"

#endif  // HOLO_GEOMETRY_DETAILS_ANGLE_AXIS_H_
