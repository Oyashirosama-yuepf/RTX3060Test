/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rot3.hpp
 * @brief the template implementation of rot3
 * @author Li Chao (lichao@holomatic.ai)
 * @author Yanwei. Du (duyanwei@holomatic.com)
 * @date Sep-27-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_IMPL_ROT3_HPP_
#define HOLO_GEOMETRY_DETAILS_IMPL_ROT3_HPP_

namespace holo
{
namespace geometry
{
namespace details
{
template <typename T>
Rot3T<T>::Rot3T() noexcept : Rot3T(Matrix3Type::Identity())
{
}

template <typename T>
Rot3T<T>::Rot3T(Vector3Type const& c0, Vector3Type const& c1, Vector3Type const& c2)
  : Rot3T(Matrix3Type(c0(0u), c1(0u), c2(0u), c0(1u), c1(1u), c2(1u), c0(2u), c1(2u), c2(2u)))
{
}

template <typename T>
Rot3T<T>::Rot3T(Point3Type const& p0, Point3Type const& p1, Point3Type const& p2)
  : Rot3T(Vector3Type(p0[0], p0[1], p0[2]), Vector3Type(p1[0], p1[1], p1[2]), Vector3Type(p2[0], p2[1], p2[2]))

{
}

template <typename T>
Rot3T<T>::Rot3T(ScalarType const r00, ScalarType const r01, ScalarType const r02, ScalarType const r10,
                ScalarType const r11, ScalarType const r12, ScalarType const r20, ScalarType const r21,
                ScalarType const r22)
  : Rot3T(Matrix3Type(r00, r01, r02, r10, r11, r12, r20, r21, r22))
{
}

template <typename T>
Rot3T<T>::Rot3T(Matrix3Type const& m) : m_(m)
{
    assert(IsValid());
}

template <typename T>
Rot3T<T>::Rot3T(Rot3Type const& other) noexcept : m_(other.m_)
{
}

template <typename T>
Rot3T<T>::~Rot3T() noexcept
{
}

template <typename T>
typename Rot3T<T>::Rot3Type& Rot3T<T>::operator=(Rot3Type const& other) noexcept
{
    m_ = other.m_;
    return *this;
}

template <typename T>
typename Rot3T<T>::Vector3Type Rot3T<T>::operator*(Vector3Type const& v) const noexcept
{
    return Rotate(v);
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::operator*(Rot3Type const& other) const noexcept
{
    return Compose(other);
}

template <typename T>
typename Rot3T<T>::Point3Type Rot3T<T>::operator*(Point3Type const& p) const noexcept
{
    return Rotate(p);
}

template <typename T>
bool_t Rot3T<T>::operator==(Rot3Type const& other) const noexcept
{
    return IsEqual(other);
}

template <typename T>
typename Rot3T<T>::ScalarType Rot3T<T>::ComputeAngle(Rot3Type const& other) const noexcept
{
    const Vector3Type v = Rot3Type::Logmap(Transpose().Compose(other));
    return Degree(v.GetNorm());
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::Compose(Rot3Type const& other) const noexcept
{
    return Rot3T(m_ * other.m_);
}

template <typename T>
typename Rot3T<T>::Point3Type Rot3T<T>::Rotate(Point3Type const& p) const noexcept
{
    return Point3Type(m_ * Vector3Type(p[0], p[1], p[2]));
}

template <typename T>
typename Rot3T<T>::Point3Type Rot3T<T>::Unrotate(Point3Type const& p) const noexcept
{
    return Point3Type(Transpose().Rotate(p));
}

template <typename T>
typename Rot3T<T>::Vector3Type Rot3T<T>::Rotate(Vector3Type const& v) const noexcept
{
    return m_ * v;
}

template <typename T>
typename Rot3T<T>::Vector3Type Rot3T<T>::Unrotate(Vector3Type const& v) const noexcept
{
    return m_.Transpose() * v;
}

template <typename T>
bool_t Rot3T<T>::IsEqual(Rot3Type const& other, ScalarType const tol) const noexcept
{
    bool_t            flag = true;
    const Matrix3Type diff = m_ - other.ToMatrix();
    for (uint8_t i = 0u; i < 3u; i++)
    {
        for (uint8_t j = 0u; j < 3u; j++)
        {
            if (std::fabs(diff(i, j)) > tol)
            {
                flag = false;
                break;
            }
        }
    }

    return flag;
}

template <typename T>
typename Rot3T<T>::Matrix3Type const& Rot3T<T>::ToMatrix() const noexcept
{
    return m_;
}

template <typename T>
typename Rot3T<T>::QuaternionType Rot3T<T>::ToQuaternion() const noexcept
{
    return QuaternionType(m_);
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::Transpose() const noexcept
{
    return Rot3Type(m_.Transpose());
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::Inverse() const noexcept
{
    return Transpose();
}

template <typename T>
bool_t Rot3T<T>::IsValid() const noexcept
{
    // check m.inverse() == m.transpose()
    const Matrix3Type inverse_m   = m_.Inverse();
    const Matrix3Type transpose_m = m_.Transpose();
    const Matrix3Type diff        = inverse_m - transpose_m;

    bool_t flag = true;
    for (uint16_t i = 0u; i < diff.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < diff.GetCols(); j++)
        {
            if (std::fabs(diff(i, j)) > 1e-3)
            {
                flag = false;
                break;
            }
        }
    }

    if (flag)
    {
        // check det(m) == 1
        ScalarType const det = m_.GetDeterminant();
        if (std::fabs(det - static_cast<ScalarType>(1.0)) > 1e-3)
        {
            flag = false;
        }
    }

    return flag;
}

template <typename T>
typename Rot3T<T>::Vector3Type Rot3T<T>::RPY() const noexcept
{
    Matrix3Type I;
    Vector3Type q;
    std::tie(I, q) = RQ(m_);
    return q;
}

template <typename T>
typename Rot3T<T>::Vector3Type Rot3T<T>::YPR() const noexcept
{
    const Vector3Type q = RPY();
    return Vector3Type(q(2u), q(1u), q(0u));
}

template <typename T>
typename Rot3T<T>::Vector3Type Rot3T<T>::GetCol(const uint8_t index) const
{
    if (index > 2u)
    {
        throw std::out_of_range("index out of bundary!");
    }
    return Vector3Type(m_(0u, index), m_(1u, index), m_(2u, index));
}

template <typename T>
typename Rot3T<T>::Vector3Type Rot3T<T>::GetRow(const uint8_t index) const
{
    if (index > 2u)
    {
        throw std::out_of_range("index out of bundary!");
    }
    return Vector3Type(m_(index, 0u), m_(index, 1u), m_(index, 2u));
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::Rx(ScalarType const t) noexcept
{
    ScalarType const cn = std::cos(t), sn = std::sin(t);
    return Rot3Type(static_cast<ScalarType>(1.0), static_cast<ScalarType>(0.0), static_cast<ScalarType>(0.0),
                    static_cast<ScalarType>(0.0), cn, -sn, static_cast<ScalarType>(0.0), sn, cn);
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::Ry(ScalarType const t) noexcept
{
    ScalarType const cn = std::cos(t), sn = std::sin(t);
    return Rot3Type(cn, static_cast<ScalarType>(0.0), sn, static_cast<ScalarType>(0.0), static_cast<ScalarType>(1.0),
                    static_cast<ScalarType>(0.0), -sn, static_cast<ScalarType>(0.0), cn);
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::Rz(ScalarType const t) noexcept
{
    ScalarType const cn = std::cos(t), sn = std::sin(t);
    return Rot3Type(cn, -sn, static_cast<ScalarType>(0.0), sn, cn, static_cast<ScalarType>(0.0),
                    static_cast<ScalarType>(0.0), static_cast<ScalarType>(0.0), static_cast<ScalarType>(1.0));
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::RzRyRx(ScalarType const x, ScalarType const y, ScalarType const z) noexcept
{
    ScalarType const cnx = static_cast<ScalarType>(cos(x)), snx = static_cast<ScalarType>(sin(x));
    ScalarType const cny = static_cast<ScalarType>(cos(y)), sny = static_cast<ScalarType>(sin(y));
    ScalarType const cnz = static_cast<ScalarType>(cos(z)), snz = static_cast<ScalarType>(sin(z));
    ScalarType const c00 = cnz * cny;
    ScalarType const c01 = cnz * sny * snx - snz * cnx;
    ScalarType const c02 = cnz * sny * cnx + snz * snx;
    ScalarType const c10 = snz * cny;
    ScalarType const c11 = snz * sny * snx + cnz * cnx;
    ScalarType const c12 = snz * sny * cnx - cnz * snx;
    ScalarType const c20 = -sny;
    ScalarType const c21 = cny * snx;
    ScalarType const c22 = cny * cnx;

    return Rot3Type(c00, c01, c02, c10, c11, c12, c20, c21, c22);
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::RzRyRx(Vector3Type const& v) noexcept
{
    return RzRyRx(v(0u), v(1u), v(2u));
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::Yaw(ScalarType const t) noexcept
{
    return Rz(t);
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::Pitch(ScalarType const t) noexcept
{
    return Ry(t);
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::Roll(ScalarType const t) noexcept
{
    return Rx(t);
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::YPR(ScalarType const r, ScalarType const p, ScalarType const y) noexcept
{
    return RzRyRx(r, p, y);
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::Rodriguez(Vector3Type const& w, ScalarType const theta)
{
    if (!ScalarEqualT<T>()(w.GetNorm(), static_cast<ScalarType>(1.0)))
    {
        throw std::runtime_error("Rodriguez: norm of vector should be 1");
    }

    ScalarType const wx = w(0u), wy = w(1u), wz = w(2u);
    ScalarType const cn = std::cos(theta), sn = std::sin(theta);
    ScalarType const c00 = (static_cast<ScalarType>(1.0) - cn) * wx * wx;
    ScalarType const c10 = (static_cast<ScalarType>(1.0) - cn) * wy * wx;
    ScalarType const c11 = (static_cast<ScalarType>(1.0) - cn) * wy * wy;
    ScalarType const c20 = (static_cast<ScalarType>(1.0) - cn) * wz * wx;
    ScalarType const c21 = (static_cast<ScalarType>(1.0) - cn) * wz * wy;
    ScalarType const c22 = (static_cast<ScalarType>(1.0) - cn) * wz * wz;

    const Matrix3Type s = sn * w.ToSkewSymmetric();

    return Rot3Type(cn + c00, c10 + s(0u, 1u), c20 + s(0u, 2u), c10 + s(1u, 0u), cn + c11, c21 + s(1u, 2u),
                    c20 + s(2u, 0u), c21 + s(2u, 1u), cn + c22);
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::Rodriguez(Vector3Type const& w) noexcept
{
    ScalarType const t = w.GetNorm();

    if (t <= ScalarEqualT<T>().GetEpsilonValue())
    {
        return Rot3Type();
    }

    return Rodriguez(w / t, t);
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::Rodriguez(ScalarType const wx, ScalarType const wy, ScalarType const wz) noexcept
{
    return Rodriguez(Vector3Type(wx, wy, wz));
}

template <typename T>
uint8_t Rot3T<T>::Dim() noexcept
{
    return 3u;
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::Identity() noexcept
{
    return Rot3Type();
}

template <typename T>
typename Rot3T<T>::Rot3Type Rot3T<T>::Expmap(Vector3Type const& w) noexcept
{
    ScalarType const t = w.GetNorm();

    if (t <= ScalarEqualT<T>().GetEpsilonValue())
    {
        return Rot3Type();
    }
    else
    {
        return Rodriguez(w);
    }
}

template <typename T>
typename Rot3T<T>::Vector3Type Rot3T<T>::Logmap(Rot3Type const& R) noexcept
{
    const float64_t tr = static_cast<float64_t>(R.m_.GetTrace());
    const float64_t pi = M_PI;

    const float64_t x     = static_cast<float64_t>(R.R21()) - static_cast<float64_t>(R.R12());
    const float64_t y     = static_cast<float64_t>(R.R02()) - static_cast<float64_t>(R.R20());
    const float64_t z     = static_cast<float64_t>(R.R10()) - static_cast<float64_t>(R.R01());
    const float64_t r     = static_cast<float64_t>(Vector3Type(x, y, z).GetNorm());
    const float64_t theta = std::atan2(r, tr - 1.0);

    if (theta < 1e-15)
    {
        // when theta = 0, +-2pi, +-4pi, etc. (or trace > 3 + 1E-10)
        return Vector3Type::Zero();
    }
    else if (theta < 1e-10)
    {
        // when theta near 0, +-2pi, +-4pi, etc. (or trace > 3 + 1E-3)
        // using Taylor expansion: theta/(2*sin(theta))
        // \approx: 1/2+theta^2/12+O(theta^4)
        return static_cast<ScalarType>(0.5 + theta * theta / 12.0) * Vector3Type(x, y, z);
    }
    else if (theta > pi - 1e-10)
    {
        // when theta = +-pi, +-3pi, +-5pi, etc.
        ScalarType const max = std::max(R.R00(), (std::max(R.R11(), R.R22())));

        if (std::fabs(R.R22() - max) < 1e-10)
        {
            return static_cast<ScalarType>(pi / std::sqrt(2.0 + static_cast<ScalarType>(2.0) * R.R22())) *
                   Vector3Type(R.R02(), R.R12(), 1.0 + R.R22());
        }
        else if (std::fabs(R.R11() - max) < 1e-10)
        {
            return static_cast<ScalarType>(pi / std::sqrt(2.0 + static_cast<ScalarType>(2.0) * R.R11())) *
                   Vector3Type(R.R01(), R.R11(), 1.0 + R.R21());
        }
        else  // if(std::fabs(R.R00() - max) < 1e-10) This is implicit
        {
            return static_cast<ScalarType>(pi / std::sqrt(2.0 + static_cast<ScalarType>(2.0) * R.R00())) *
                   Vector3Type(R.R00(), R.R10(), 1.0 + R.R20());
        }
    }
    else
    {
        return static_cast<ScalarType>(theta / 2.0 / std::sin(theta)) * Vector3Type(x, y, z);
    }
}

template <typename T>
std::pair<typename Rot3T<T>::Matrix3Type, typename Rot3T<T>::Vector3Type> Rot3T<T>::RQ(Matrix3Type const& A) noexcept
{
    ScalarType  x  = -std::atan2(-A(2u, 1u), A(2u, 2u));
    Rot3Type    Qx = Rot3Type::Rx(-x);
    Matrix3Type B  = A * Qx.ToMatrix();

    ScalarType  y  = -std::atan2(B(2u, 0u), B(2u, 2u));
    Rot3Type    Qy = Rot3Type::Ry(-y);
    Matrix3Type C  = B * Qy.ToMatrix();

    ScalarType  z  = -std::atan2(-C(1u, 0u), C(1u, 1u));
    Rot3Type    Qz = Rot3Type::Rz(-z);
    Matrix3Type R  = C * Qz.ToMatrix();

    Vector3Type xyz = Vector3Type(x, y, z);
    return std::make_pair(R, xyz);
}

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_IMPL_ROT3_HPP_
