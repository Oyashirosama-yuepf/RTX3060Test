/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file quaternion.hpp
 * @brief holo quaternion type implementation
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date Oct-10-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_IMPL_QUATERNION_HPP_
#define HOLO_GEOMETRY_DETAILS_IMPL_QUATERNION_HPP_

#include <assert.h>

#include <Eigen/Geometry>

namespace holo
{
namespace geometry
{
namespace details
{
template <typename T>
struct QuaternionT<T>::Implementation
{
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    using EigenQuaternionType = Eigen::Quaternion<T>;
    using EigenMatrixType     = Eigen::Matrix<T, 3, 3>;

    /**
     * @brief Construct a new Implementation object
     *
     * @param w w value
     * @param x x value
     * @param y y value
     * @param z z value
     */
    Implementation(ScalarType const w, ScalarType const x, ScalarType const y, ScalarType const z) noexcept
      : data(w, x, y, z)
    {
    }

    /**
     * @brief Construct a new Implementation object
     *
     * @param matrix rotation matrix
     */
    Implementation(Matrix3Type const& matrix) noexcept
      : data((EigenMatrixType() << matrix(0, 0), matrix(0, 1), matrix(0, 2), matrix(1, 0), matrix(1, 1), matrix(1, 2),
              matrix(2, 0), matrix(2, 1), matrix(2, 2))
                 .finished())
    {
    }

    /**
     * @brief Construct a new Implementation object
     *
     * @param _data internal data
     */
    Implementation(EigenQuaternionType const& _data) noexcept : data(_data)
    {
    }

    /**
     * @brief copy constructor
     *
     */
    Implementation(Implementation const& impl) noexcept : data(impl.data)
    {
    }

    /**
     * @brief copy assignment
     */
    Implementation& operator=(Implementation const& impl) noexcept
    {
        data = impl.data;
        return *this;
    }

    EigenQuaternionType data;  ///< internal data layout
};

template <typename T>
QuaternionT<T>::QuaternionT()
  : QuaternionT(static_cast<ScalarType>(1.0), static_cast<ScalarType>(0.0), static_cast<ScalarType>(0.0),
                static_cast<ScalarType>(0.0))
{
}

template <typename T>
QuaternionT<T>::QuaternionT(ScalarType const w, ScalarType const x, ScalarType const y, ScalarType const z)
  : impl_ptr_(new Implementation(w, x, y, z))
{
    Normalize();
}

template <typename T>
QuaternionT<T>::QuaternionT(ScalarType const* array, uint32_t const array_size)
  : QuaternionT(array[3], array[0], array[1], array[2])
{
    if (array_size != 4u)
    {
        throw std::out_of_range("QuaternionT --- wrong array size");
    }
}

template <typename T>
QuaternionT<T>::QuaternionT(Matrix3Type const& matrix) : impl_ptr_(new Implementation(matrix))
{
    Normalize();
}

template <typename T>
QuaternionT<T>::QuaternionT(QuaternionT const& other) : impl_ptr_(new Implementation(*(other.impl_ptr_)))
{
}

template <typename T>
QuaternionT<T>::~QuaternionT() noexcept
{
}

template <typename T>
QuaternionT<T>& QuaternionT<T>::operator=(QuaternionT const& other)
{
    impl_ptr_.reset(new Implementation(*(other.impl_ptr_)));
    return *this;
}

template <typename InputScalar>
std::ostream& operator<<(std::ostream& os, QuaternionT<InputScalar> const& quaternion) noexcept
{
    os << quaternion.impl_ptr_->data.coeffs().transpose();
    return os;
}

template <typename T>
template <typename OutputScalar>
QuaternionT<OutputScalar> QuaternionT<T>::Cast() const noexcept
{
    static_assert(std::is_floating_point<OutputScalar>::value, "only floating type matrix is supported");
    return QuaternionT<OutputScalar>(static_cast<OutputScalar>(GetW()), static_cast<OutputScalar>(GetX()),
                                     static_cast<OutputScalar>(GetY()), static_cast<OutputScalar>(GetZ()));
}

template <typename T>
typename QuaternionT<T>::Matrix3Type QuaternionT<T>::ToRotationMatrix() const noexcept
{
    // get coefficients
    ScalarType const w = this->GetW();
    ScalarType const x = this->GetX();
    ScalarType const y = this->GetY();
    ScalarType const z = this->GetZ();

    ScalarType const one(static_cast<ScalarType>(1.0));
    ScalarType const two(static_cast<ScalarType>(2.0));

    // construct rotation matrix
    ScalarType const r00 = one - two * std::pow(y, two) - two * std::pow(z, two);
    ScalarType const r01 = two * x * y - two * z * w;
    ScalarType const r02 = two * x * z + two * y * w;
    ScalarType const r10 = two * x * y + two * z * w;
    ScalarType const r11 = one - two * std::pow(x, two) - two * std::pow(z, two);
    ScalarType const r12 = two * y * z - two * x * w;
    ScalarType const r20 = two * x * z - two * y * w;
    ScalarType const r21 = two * y * z + two * x * w;
    ScalarType const r22 = one - two * std::pow(x, two) - two * std::pow(y, two);

    return Matrix3Type(r00, r01, r02, r10, r11, r12, r20, r21, r22);
}

template <typename T>
typename QuaternionT<T>::ScalarType QuaternionT<T>::GetSquaredNorm() const noexcept
{
    return impl_ptr_->data.squaredNorm();
}

template <typename T>
typename QuaternionT<T>::ScalarType QuaternionT<T>::GetNorm() const noexcept
{
    return impl_ptr_->data.norm();
}

template <typename T>
QuaternionT<T> QuaternionT<T>::Inverse() const noexcept
{
    return QuaternionT<ScalarType>(Implementation(impl_ptr_->data.inverse()));
}

template <typename T>
QuaternionT<T> QuaternionT<T>::GetConjugate() const noexcept
{
    return QuaternionT<ScalarType>(Implementation(impl_ptr_->data.conjugate()));
}

template <typename T>
QuaternionT<T> QuaternionT<T>::Slerp(ScalarType const t, QuaternionT const& other) const
{
    if (t < static_cast<ScalarType>(0.0) || t > static_cast<ScalarType>(1.0))
    {
        throw std::out_of_range("interpolation ratio out of range");
    }

    return QuaternionT(Implementation(impl_ptr_->data.slerp(t, other.impl_ptr_->data)));
}

template <typename T>
typename QuaternionT<T>::ScalarType QuaternionT<T>::GetW() const noexcept
{
    return impl_ptr_->data.w();
}

template <typename T>
typename QuaternionT<T>::ScalarType QuaternionT<T>::GetX() const noexcept
{
    return impl_ptr_->data.x();
}

template <typename T>
typename QuaternionT<T>::ScalarType QuaternionT<T>::GetY() const noexcept
{
    return impl_ptr_->data.y();
}

template <typename T>
typename QuaternionT<T>::ScalarType QuaternionT<T>::GetZ() const noexcept
{
    return impl_ptr_->data.z();
}

template <typename T>
typename QuaternionT<T>::Vector3Type QuaternionT<T>::GetVector() const noexcept
{
    return Vector3Type(GetX(), GetY(), GetZ());
}

template <typename T>
void QuaternionT<T>::SetIdentity() noexcept
{
    impl_ptr_->data.setIdentity();
}

template <typename T>
QuaternionT<T> QuaternionT<T>::Identity() noexcept
{
    return QuaternionT(static_cast<ScalarType>(1.0), static_cast<ScalarType>(0.0), static_cast<ScalarType>(0.0),
                       static_cast<ScalarType>(0.0));
}

template <typename T>
void QuaternionT<T>::Normalize() noexcept
{
    impl_ptr_->data.normalize();
}

template <typename T>
QuaternionT<T>::QuaternionT(Implementation const& impl) noexcept : impl_ptr_(new Implementation(impl))
{
}

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_IMPL_QUATERNION_HPP_
