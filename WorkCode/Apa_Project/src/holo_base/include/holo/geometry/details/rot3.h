/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rot3.h
 * @brief A rotation in 3D space
 * @author Li Chao (lichao@holomatic.ai)
 * @author Yanwei. Du (duyanwei@holomatic.com)
 * @date Sep-27-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_ROT3_H_
#define HOLO_GEOMETRY_DETAILS_ROT3_H_

#include <cassert>

#include <holo/core/epsilon.h>
#include <holo/core/types.h>
#include <holo/geometry/angle.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/quaternion.h>
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
 * @brief rotation in 3D
 *
 * @tparam T float32_t or float64_t
 */
template <typename T>
class Rot3T
{
public:
    using ScalarType                = T;
    using Rot3Type                  = Rot3T<ScalarType>;
    using Point3Type                = Point3T<ScalarType>;
    using Vector3Type               = holo::numerics::Vector3T<ScalarType>;
    using Matrix3Type               = holo::numerics::Matrix3T<ScalarType>;
    using QuaternionType            = QuaternionT<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    static_assert(std::is_floating_point<ScalarType>::value, "Rot3T needs to take floating type");

    /**
     * @brief default constructor
     */
    Rot3T() noexcept;

    /**
     * @brief constructor from column vectors
     *
     * @details \f$ R = (c_0, c_1, c_2) \f$
     * @param c0 column0
     * @param c1 column1
     * @param c2 column2
     * @throw std::runtime_error if c0, c1, c2 do NOT compose a rotation matrix
     */
    Rot3T(Vector3Type const& c0, Vector3Type const& c1, Vector3Type const& c2);

    /**
     * @brief constructor from 3d points in column order
     *
     * @details \f$ R = (p_0, p_1, p_2) \f$
     * @param p0 column0
     * @param p1 column1
     * @param p2 column2
     * @throw std::runtime_error if p0, p1, p2 do NOT compose a rotation matrix
     */
    Rot3T(Point3Type const& p0, Point3Type const& p1, Point3Type const& p2);

    /**
     * @brief constructor from scalars in a row-majored order
     *
     * @details
     * @f$ R =
     * \begin{bmatrix}
     * r_{00} & r_{01} & r_{02} \\
     * r_{10} & r_{11} & r_{12} \\
     * r_{20} & r_{21} & r_{22} \\
     * \end{bmatrix}
     * @f$
     * @param r00 element value
     * @param r01 element value
     * @param r02 element value
     * @param r10 element value
     * @param r11 element value
     * @param r12 element value
     * @param r20 element value
     * @param r21 element value
     * @param r22 element value
     * @throw std::runtime_error if all the elements does NOT compose a rotation matrix
     */
    Rot3T(ScalarType const r00, ScalarType const r01, ScalarType const r02, ScalarType const r10, ScalarType const r11,
          ScalarType const r12, ScalarType const r20, ScalarType const r21, ScalarType const r22);

    /**
     * @brief constructor from matrix
     *
     * @param m matrix
     * @throw std::runtime_error if m is NOT a rotation matrix
     */
    Rot3T(Matrix3Type const& m);

    /**
     * @brief copy constructor
     *
     * @param other rot3
     */
    Rot3T(Rot3Type const& other) noexcept;

    /**
     * @brief destructor
     */
    ~Rot3T() noexcept;

    /**
     * @brief operator=
     *
     * @param other rot3
     *
     * @return rot3
     */
    Rot3Type& operator=(Rot3Type const& other) noexcept;

    /**
     * @brief operator*
     *
     * @param v vector3
     *
     * @return vector3
     */
    Vector3Type operator*(Vector3Type const& v) const noexcept;

    /**
     * @brief operator*
     *
     * @param other rot3
     *
     * @return rot3
     */
    Rot3Type operator*(Rot3Type const& other) const noexcept;

    /**
     * @brief operator*
     *
     * @param p point3
     *
     * @return point3
     */
    Point3Type operator*(Point3Type const& p) const noexcept;

    /**
     * @brief operator==
     *
     * @param other rot3
     *
     * @return bool
     */
    bool_t operator==(Rot3Type const& other) const noexcept;

    /**
     * @brief conversion operator
     *
     * @tparam OutputScalar
     *
     * @return rot3
     */
    template <typename OutputScalar>
    explicit operator Rot3T<OutputScalar>() const noexcept
    {
        return Cast<OutputScalar>();
    }

    /**
     * @brief operator<<
     *
     * @param os std::ostream
     * @param R rot3
     *
     * @return ostream
     */
    friend std::ostream& operator<<(std::ostream& os, Rot3Type const& R) noexcept
    {
        os << R.ToString();
        return os;
    }

    /**
     * @brief rot3 to string
     *
     * @return string
     */
    std::string ToString() const noexcept
    {
        std::stringstream ss;
        ss << "rot3: (" << m_(0u, 0u) << ", " << m_(0u, 1u) << ", " << m_(0u, 2u) << ", " << m_(1u, 0u) << ", "
           << m_(1u, 1u) << ", " << m_(1u, 2u) << ", " << m_(2u, 0u) << ", " << m_(2u, 1u) << ", " << m_(2u, 2u) << ")"
           << std::endl;
        return ss.str();
    }

    /**
     * @brief cast to different scalar type
     *
     * @tparam OutputScalar
     *
     * @return rot3
     */
    template <typename OutputScalar>
    Rot3T<OutputScalar> Cast() const noexcept
    {
        return Rot3T<OutputScalar>(m_.template Cast<OutputScalar>());
    }

    /**
     * @brief return the angular difference in degree between two rotations
     *
     * @param other rot3
     *
     * @return scalar [degree]
     */
    ScalarType ComputeAngle(Rot3Type const& other = Rot3Type()) const noexcept;

    /**
     * @brief compose 2 rotations
     *
     * @param other rot3
     *
     * @return rot3
     */
    Rot3T Compose(Rot3Type const& other) const noexcept;

    /**
     * @brief rotate a 3D point
     *
     * @details \f$ q = Rp \f$
     * @param p point3
     *
     * @return point3
     */
    Point3Type Rotate(Point3Type const& p) const noexcept;

    /**
     * @brief unrotate a 3D point
     *
     * @details \f$ q = R^T p \f$
     * @param p point3
     *
     * @return point3
     */
    Point3Type Unrotate(Point3Type const& p) const noexcept;

    /**
     * @brief rotate a 3D vector
     *
     * @details \f$ w = Rv \f$
     * @param v vector3
     *
     * @return vector3
     */
    Vector3Type Rotate(Vector3Type const& v) const noexcept;

    /**
     * @brief unrotate a 3D vector
     *
     * @details \f$ w = R^T v \f$
     * @param v vector3
     *
     * @return vector3
     */
    Vector3Type Unrotate(Vector3Type const& v) const noexcept;

    /**
     * @brief is equal
     *
     * @param other rot3
     * @param tol tolerance
     *
     * @return bool
     */
    bool_t IsEqual(Rot3Type const& other, ScalarType const tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept;

    /**
     * @brief convert to matrix
     *
     * @return matrix3
     */
    Matrix3Type const& ToMatrix() const noexcept;

    /**
     * @brief convert to quaternion
     *
     * @return quaternion
     */
    QuaternionType ToQuaternion() const noexcept;

    /**
     * @brief transpose
     *
     * @return rot3
     */
    Rot3Type Transpose() const noexcept;

    /**
     * @brief inverse
     *
     * @return rot3
     */
    Rot3Type Inverse() const noexcept;

    /**
     * @brief check if a rotation matrix is valid
     *
     * @details \f$ {R \in SO(3)} \f$
     *
     * @return bool
     */
    bool_t IsValid() const noexcept;

    /**
     * @brief get the euler angles from rotation matrix
     *
     * @details R is decomposed by RQ in a composed order of Z-Y-X (yaw-pitch-roll)
     *
     * @return a vector containing the angle-order as (roll-pitch-yaw)
     */
    Vector3Type RPY() const noexcept;

    /**
     * @brief get the euler angles from rotation matrix
     *
     * @details R is decomposed by RQ in a composed order of Z-Y-X (yaw-pitch-roll)
     *
     * @return a vector containing the angle-order as (yaw-pitch-roll)
     */
    Vector3Type YPR() const noexcept;

    /**
     * @brief return column vector specified by index
     *
     * @param index column index
     *
     * @return vector3
     *
     * @throw std::out_of_range if index is out of matrix range (i.e. index > 2u)
     */
    Vector3Type GetCol(uint8_t const index) const;

    /**
     * @brief return row vector specified by index
     *
     * @param index row index
     *
     * @return vector3
     *
     * @throw std::out_of_range if index is out of matrix range (i.e. index > 2u)
     */
    Vector3Type GetRow(uint8_t const index) const;

    /**
     * @brief return r00
     *
     * @return ScalarType
     */
    inline ScalarType R00() const noexcept
    {
        return m_(0u, 0u);
    }

    /**
     * @brief return r01
     *
     * @return ScalarType
     */
    inline ScalarType R01() const noexcept
    {
        return m_(0u, 1u);
    }

    /**
     * @brief return r02
     *
     * @return ScalarType
     */
    inline ScalarType R02() const noexcept
    {
        return m_(0u, 2u);
    }

    /**
     * @brief return r10
     *
     * @return ScalarType
     */
    inline ScalarType R10() const noexcept
    {
        return m_(1u, 0u);
    }

    /**
     * @brief return r11
     *
     * @return ScalarType
     */
    inline ScalarType R11() const noexcept
    {
        return m_(1u, 1u);
    }

    /**
     * @brief return r12
     *
     * @return ScalarType
     */
    inline ScalarType R12() const noexcept
    {
        return m_(1u, 2u);
    }

    /**
     * @brief return r20
     *
     * @return ScalarType
     */
    inline ScalarType R20() const noexcept
    {
        return m_(2u, 0u);
    }

    /**
     * @brief return r21
     *
     * @return ScalarType
     */
    inline ScalarType R21() const noexcept
    {
        return m_(2u, 1u);
    }

    /**
     * @brief return r22
     *
     * @return ScalarType
     */
    inline ScalarType R22() const noexcept
    {
        return m_(2u, 2u);
    }

    /**
     * @brief Get serialized size with given alignment value
     *
     * @tparam ALIGN Buffer alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return m_.template GetSerializedSize<ALIGN>();
    }

    /**
     * @brief Serialize to serializer.
     *
     * @tparam S Serializer type.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << m_;
    }

    /**
     * @brief Deserialize from deserializer.
     *
     * @tparam D Deserializer type
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> m_;
    }

    /**
     * @brief rotation around x-axis in counterclock wise
     *
     * @param t rotation angle in radian around x-axis
     *
     * @return rot3
     */
    static Rot3Type Rx(ScalarType const t) noexcept;

    /**
     * @brief rotation around y-axis in counterclock wise
     *
     * @param t rotation angle in radian around y-axis
     *
     * @return rot3
     */
    static Rot3Type Ry(ScalarType const t) noexcept;

    /**
     * @brief rotation around z-axis in counterclock wise
     *
     * @param t rotation angle in radian around z-axis
     *
     * @return rot3
     */
    static Rot3Type Rz(ScalarType const t) noexcept;

    /**
     * @brief general matrix consists of roll, pitch and yaw angles (radian)
     *
     * @param x roll  angle in radian around x-axis
     * @param y pitch angle in radian around y-axis
     * @param z yaw   angle in radian around z-axis
     *
     * @return rot3
     */
    static Rot3Type RzRyRx(ScalarType const x, ScalarType const y, ScalarType const z) noexcept;

    /**
     * @brief general matrix consist of roll, pitch and yaw angle (radian)
     *
     * @param v is euler angles in roll, pitch and yaw ordering
     *
     * @return
     */
    static Rot3Type RzRyRx(Vector3Type const& v) noexcept;

    /**
     * @brief construct rot3 from yaw angle (radian)
     *
     * @details Tait-Bryan system from Spatial Reference Model (SRM) (x, y, z) = (roll, pitch, yaw) as describe in
     *          http://www.sedris.org/wg8home/Documents/WG80462.pdf
     *          Assume vehicle coordinate frame X forward, Y right, Z down
     *          positive yaw is to right (as in aircraft heading)
     *
     * @param t
     *
     * @return rot3
     */
    static Rot3Type Yaw(ScalarType const t) noexcept;

    /**
     * @brief construct rot3 from pitch angle (radian)
     *
     * @details positive pitch is to up (increasing aircraft altitude)
     *
     * @param t
     *
     * @return rot3
     */
    static Rot3Type Pitch(ScalarType const t) noexcept;

    /**
     * @brief construct rot3 from roll angle (radian)
     *
     * @details positive roll is to right (increasing yaw in altitude)
     *
     * @param t
     *
     * @return rot3
     */
    static Rot3Type Roll(ScalarType const t) noexcept;

    /**
     * @brief general rotation consist of yaw, pitch and roll angles
     *
     * @param r is roll  angle in radian
     * @param p is pitch angle in radian
     * @param y is yaw   angle in radian
     *
     * @return rot3
     */
    static Rot3Type YPR(ScalarType const r, ScalarType const p, ScalarType const y) noexcept;

    /**
     * @brief Rodriguez' formula to compute an incremental rotation matrix
     *
     * @param w is the rotation axis, unit length
     * @param theta rotation angle in radian
     *
     * @return rot3 incremental rotation matrix
     * @throw std::runtime_error if w is not an unit vector
     */
    static Rot3T Rodriguez(Vector3Type const& w, ScalarType const theta);

    /**
     * @brief Rodriguez' formula to compute an incremental rotation matrix
     *
     * @param w is a vector of incremental roll, pitch, yaw in radian
     *
     * @return rot3 incremental rotation matrix
     */
    static Rot3T Rodriguez(Vector3Type const& w) noexcept;

    /**
     * @brief Rodriguez' formula to compute an incremental rotation matrix
     *
     * @param wx is incremental roll angle in radian
     * @param wy is incremental pitch angle in radian
     * @param wz is incremental yaw angle in radian
     *
     * @return rot3 incremental rotation matrix
     */
    static Rot3T Rodriguez(ScalarType const wx, ScalarType const wy, ScalarType const wz) noexcept;

    /**
     * @brief dimension
     *
     * @return uint8_t
     */
    static uint8_t Dim() noexcept;

    /**
     * @brief identity
     *
     * @return rot3
     */
    static Rot3Type Identity() noexcept;

    /**
     * @brief lie group exponential map
     *
     * @param v
     *
     * @return rot3
     */
    static Rot3Type Expmap(Vector3Type const& v) noexcept;

    /**
     * @brief lie group log map
     *
     * @param R
     *
     * @return vector3
     */
    static Vector3Type Logmap(Rot3Type const& R) noexcept;

    /**
     * @brief RQ decomposition to get euler angles
     *
     * @details [RQ] receives a 3 by 3 matrix and returns an upper triangular
     * matrix R and 3 rotation angles corresponding to the rotation matrix
     * Q=Qz'*Qy'*Qx' such that A = R*Q = R*Qz'*Qy'*Qx'. When A is a rotation
     * matrix, R will be the identity and Q is a yaw-pitch-roll decomposition
     * of A. The implementation uses Givens rotations and is based on Harley-
     * Zisserman
     *
     * @param A A = RQ
     *
     * @return pair of matrix3 and vector3
     * @return an upper trianular matrix R
     * @return a vector [thetax, thetay, thetaz] in radians.
     */
    static std::pair<Matrix3Type, Vector3Type> RQ(Matrix3Type const& A) noexcept;

private:
    /**
     * @brief rotation matrix
     */
    Matrix3Type m_;

};  // class Rot3T

/**
 * @}
 *
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#include "./impl/rot3.hpp"

#endif  // HOLO_GEOMETRY_DETAILS_ROT3_H_
