/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file angle_axis.hpp
 * @brief holo angle_axis type
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date 2019-08-26
 */

#ifndef HOLO_GEOMETRY_DETAILS_IMPL_ANGLE_AXIS_HPP_
#define HOLO_GEOMETRY_DETAILS_IMPL_ANGLE_AXIS_HPP_

#include <Eigen/Geometry>

namespace holo
{
namespace geometry
{
namespace details
{
template <typename T>
struct AngleAxisT<T>::Implementation
{
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    using EigenAngleAxisType  = Eigen::AngleAxis<T>;
    using EigenMatrix3Type    = Eigen::Matrix<T, 3, 3>;
    using EigenVector3Type    = Eigen::Matrix<T, 3, 1>;
    using EigenQuaternionType = Eigen::Quaternion<T>;

    /**
     * @brief Construct a new Implementation object
     *
     * @param angle
     * @param axis
     */
    Implementation(ScalarType const angle, Vector3Type const& axis)
      : data(angle, EigenVector3Type(axis(0u), axis(1u), axis(2u)))
    {
    }

    /**
     * @brief Construct a new Implementation object
     *
     * @param q
     */
    Implementation(QuaternionType const& q) : data(EigenQuaternionType(q.GetW(), q.GetX(), q.GetY(), q.GetZ()))
    {
    }

    /**
     * @brief Construct a new Implementation object
     *
     * @param m
     */
    Implementation(Matrix3Type const& m)
      : data((EigenMatrix3Type() << m(0u, 0u), m(0u, 1u), m(0u, 2u), m(1u, 0u), m(1u, 1u), m(1u, 2u), m(2u, 0u),
              m(2u, 1u), m(2u, 2u))
                 .finished())
    {
    }

    /**
     * @brief Set the Axis object
     *
     * @param axis
     */
    void SetAxis(Vector3Type const& axis)
    {
        data.axis() = EigenVector3Type(axis(0u), axis(1u), axis(2u));
    }

    /**
     * @brief take inverse
     *
     * @return AngleAxisType
     */
    AngleAxisT<T> Inverse() const
    {
        EigenAngleAxisType const aa = data.inverse();
        return AngleAxisT<T>(aa.angle(), Vector3Type(aa.axis().x(), aa.axis().y(), aa.axis().z()));
    }

    /**
     * @brief convert to rotation matrix
     *
     * @return Matrix3Type
     */
    Matrix3Type ToRotationMatrix() const
    {
        EigenMatrix3Type const m = data.toRotationMatrix();
        return Matrix3Type(m(0u, 0u), m(0u, 1u), m(0u, 2u), m(1u, 0u), m(1u, 1u), m(1u, 2u), m(2u, 0u), m(2u, 1u),
                           m(2u, 2u));
    }

    EigenAngleAxisType data;  ///< internal data layout
};

template <typename T>
AngleAxisT<T>::AngleAxisT() : AngleAxisT(0.0, Vector3Type::One())
{
}

template <typename T>
AngleAxisT<T>::AngleAxisT(ScalarType const angle, Vector3Type const& axis)
{
    ScalarType const norm = axis.GetNorm();
    if (norm == ScalarType(0.0))
    {
        throw std::runtime_error("axis norm is zero");
    }
    impl_ptr_.reset(new Implementation(angle, axis / norm));
}

template <typename T>
AngleAxisT<T>::AngleAxisT(QuaternionType const& q)
{
    *this = q;
}

template <typename T>
AngleAxisT<T>::AngleAxisT(Matrix3Type const& m)
{
    *this = m;
}

template <typename T>
AngleAxisT<T>::AngleAxisT(Rot3Type const& r) : AngleAxisT(r.ToMatrix())
{
}

template <typename T>
AngleAxisT<T>::AngleAxisT(AngleAxisT const& other)
{
    impl_ptr_.reset(new Implementation(*(other.impl_ptr_)));
}

template <typename T>
AngleAxisT<T>::~AngleAxisT() noexcept
{
}

template <typename T>
AngleAxisT<T>& AngleAxisT<T>::operator=(AngleAxisT const& other)
{
    impl_ptr_.reset(new Implementation(*(other.impl_ptr_)));
    return *this;
}

template <typename T>
AngleAxisT<T>& AngleAxisT<T>::operator=(QuaternionType const& q)
{
    impl_ptr_.reset(new Implementation(q));
    return *this;
}

template <typename T>
AngleAxisT<T>& AngleAxisT<T>::operator=(Matrix3Type const& m)
{
    if (!m.Inverse().IsApprox(m.Transpose(), 1e-3) || std::fabs(m.GetDeterminant() - (T)1.0) > 1e-3)
    {
        throw std::runtime_error("matrix m is not a rotation matrix");
    }
    impl_ptr_.reset(new Implementation(m));
    return *this;
}

template <typename T>
typename AngleAxisT<T>::ScalarType AngleAxisT<T>::GetAngle() const noexcept
{
    return impl_ptr_->data.angle();
}

template <typename T>
void AngleAxisT<T>::SetAngle(ScalarType const angle) noexcept
{
    impl_ptr_->data.angle() = angle;  // reference
}

template <typename T>
typename AngleAxisT<T>::Vector3Type AngleAxisT<T>::GetAxis() const noexcept
{
    return Vector3Type(impl_ptr_->data.axis().x(), impl_ptr_->data.axis().y(), impl_ptr_->data.axis().z());
}

template <typename T>
void AngleAxisT<T>::SetAxis(Vector3Type const& axis)
{
    ScalarType const norm = axis.GetNorm();
    if (norm == ScalarType(0.0))
    {
        throw std::runtime_error("axis norm is zero");
    }
    impl_ptr_->SetAxis(axis / norm);
}

template <typename T>
AngleAxisT<T> AngleAxisT<T>::Inverse() const noexcept
{
    return impl_ptr_->Inverse();
}

template <typename T>
bool_t AngleAxisT<T>::IsApprox(AngleAxisT const& other, ScalarType const tol) const noexcept
{
    return impl_ptr_->data.isApprox(other.impl_ptr_->data, tol);
}

template <typename T>
typename AngleAxisT<T>::Matrix3Type AngleAxisT<T>::ToRotationMatrix() const noexcept
{
    return impl_ptr_->ToRotationMatrix();
}

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_IMPL_ANGLE_AXIS_HPP_
