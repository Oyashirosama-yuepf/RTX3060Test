/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pose3.h
 * @brief A pose in 3D space
 * @author Li Chao (lichao@holomatic.ai)
 * @author Yanwei. Du (duyanwei@holomatic.com)
 * @date Sep-27-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_POSE3_H_
#define HOLO_GEOMETRY_DETAILS_POSE3_H_

#include <holo/core/epsilon.h>
#include <holo/geometry/angle.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/rot3.h>

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
 * @brief pose in 3D
 *
 * @tparam T float32_t or float64_t
 */
template <typename T>
class Pose3T
{
public:
    using ScalarType                = T;
    using Pose3Type                 = Pose3T<ScalarType>;
    using Rot3Type                  = Rot3T<ScalarType>;
    using Point3Type                = Point3T<ScalarType>;
    using Matrix4Type               = holo::numerics::Matrix4T<ScalarType>;
    using Vector3Type               = holo::numerics::Vector3T<ScalarType>;
    using Vector6Type               = holo::numerics::Vector6T<ScalarType>;
    using QuaternionType            = QuaternionT<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    static_assert(std::is_floating_point<ScalarType>::value, "Pose3T needs to take floating type");

    /**
     * @brief default constructor
     */
    Pose3T() noexcept;

    /**
     * @brief construct from rot3 and point3
     *
     * @param r rotation
     * @param t translation
     */
    Pose3T(Rot3Type const& r, Point3Type const& t) noexcept;

    /**
     * @brief construct from matrix4
     *
     * @param m matrix
     */
    explicit Pose3T(const Matrix4Type& m) noexcept;

    /**
     * @brief copy constructor
     *
     * @param other pose3
     */
    Pose3T(Pose3Type const& other) noexcept;

    /**
     * @brief destructor
     */
    ~Pose3T() noexcept;

    /**
     * @brief operator*
     *
     * @param other pose3
     *
     * @return pose3
     */
    Pose3Type operator*(Pose3Type const& other) const noexcept;

    /**
     * @brief operator*
     *
     * @details \f$ q = Rp + t \f$
     * @param p point
     *
     * @return point3
     */
    Point3Type operator*(Point3Type const& p) const noexcept;

    /**
     * @brief transform a vector (e.g. velocity vector) from local to global frame
     *
     * @details \f$ w = Rv \f$, only rotation takes effect
     * @param v vector
     *
     * @return vector3
     */
    Vector3Type operator*(Vector3Type const& v) const noexcept;

    /**
     * @brief operator=
     *
     * @param other pose3
     *
     * @return *this
     */
    Pose3Type& operator=(Pose3Type const& other) noexcept;

    /**
     * @brief operator==
     *
     * @param other pose3
     *
     * @return bool
     */
    bool_t operator==(Pose3Type const& other) const noexcept;

    /**
     * @brief conversion operator
     *
     * @tparam OutputScalar
     *
     * @return pose3
     */
    template <typename OutputScalar>
    explicit operator Pose3T<OutputScalar>() const noexcept
    {
        return Cast<OutputScalar>();
    }

    /**
     * @brief operator<<
     *
     * @param os std::ostream
     * @param p pose3
     *
     * @return ostream
     */
    friend std::ostream& operator<<(std::ostream& os, const Pose3T& p) noexcept
    {
        os << p.ToString();
        return os;
    }

    /**
     * @brief pose3 to string
     *
     * @return string
     */
    std::string ToString() const noexcept
    {
        std::stringstream ss;
        ss << "pose3: (" << rotation_ << ", " << translation_ << ")" << std::endl;
        return ss.str();
    }

    /**
     * @brief cast to different scalar types
     *
     * @tparam OutputScalar
     *
     * @return pose3
     */
    template <typename OutputScalar>
    Pose3T<OutputScalar> Cast() const noexcept
    {
        return Pose3T<OutputScalar>(rotation_.template Cast<OutputScalar>(),
                                    static_cast<Point3T<OutputScalar>>(translation_));
    }

    /**
     * @brief check if pose3 valid
     *
     * @details \f$ T \in SE(3) \f$
     *
     * @return true for valid otherwise false
     */
    bool_t IsValid() const noexcept;

    /**
     * @brief convert to matrix
     *
     * @return matrix4
     */
    Matrix4Type ToMatrix() const noexcept;

    /**
     * @brief check if two poses are equal
     *
     * @param other pose3
     * @param tol tolerance
     *
     * @return bool
     */
    bool_t IsEqual(Pose3Type const& pose, const ScalarType tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept;

    /**
     * @brief return distance between ego and other poses in global frame
     *
     * @details \f$ d = ||t_1 - t_2|| \f$
     * @param other pose3
     *
     * @return scalar
     */
    ScalarType Dist(Pose3Type const& other) const noexcept;

    /**
     * @brief compose 2 poses
     *
     * @details \f$ T = T_1T_2 \f$
     * @param other pose3
     *
     * @return pose3
     */
    Pose3Type Compose(Pose3Type const& other) const noexcept;

    /**
     * @brief inverse
     *
     * @return pose3
     */
    Pose3Type Inverse() const noexcept;

    /**
     * @brief transform a point p from local frame to global frame
     *
     * @details \f$ q = Rp + t \f$
     * @param p point3
     *
     * @return point3
     */
    Point3Type TransformFrom(Point3Type const& p) const noexcept;

    /**
     * @brief transform a point p from global frame to local frame
     *
     * @details \f$ q = R^T (p - t) \f$
     * @param p point3
     *
     * @return point3
     */
    Point3Type TransformTo(Point3Type const& p) const noexcept;

    /**
     * @brief transform a vector (e.g. velocity vector) from local to global frame
     *
     * @details \f$ w = Rv \f$
     * @param v vector3
     *
     * @return vector3
     */
    Vector3Type TransformFrom(Vector3Type const& v) const noexcept;

    /**
     * @brief transform a vector (e.g. velocity vector) from global to local frame
     *
     * @details \f$ w = R^T v \f$
     * @param v vector3
     *
     * @return vector3
     */
    Vector3Type TransformTo(Vector3Type const& v) const noexcept;

    /**
     * @brief compute this->inverse() * pose, compute pose in *this coordinate system
     *
     * @param other pose3
     *
     * @return pose3
     */
    Pose3Type Between(Pose3Type const& other) const noexcept;

    /**
     * @brief get rotation
     *
     * @return Rot3Type const&
     */
    inline Rot3Type const& GetRotation() const noexcept
    {
        return rotation_;
    }

    /**
     * @brief Set the Rotation object
     *
     * @param r rotation
     */
    inline void SetRotation(Rot3Type const& r) noexcept
    {
        rotation_ = r;
    }

    /**
     * @brief get translation
     *
     * @return Point3Type const&
     */
    inline Point3Type const& GetTranslation() const noexcept
    {
        return translation_;
    }

    /**
     * @brief Set the Translation object
     *
     * @param t translation
     */
    inline void SetTranslation(Point3Type const& t) noexcept
    {
        translation_ = t;
    }

    /**
     * @brief get x
     *
     * @return ScalarType
     */
    inline ScalarType GetX() const noexcept
    {
        return translation_.GetX();
    }

    /**
     * @brief get y
     *
     * @return ScalarType
     */
    inline ScalarType GetY() const noexcept
    {
        return translation_.GetY();
    }

    /**
     * @brief get z
     *
     * @return ScalarType
     */
    inline ScalarType GetZ() const noexcept
    {
        return translation_.GetZ();
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return rotation_.template GetSerializedSize<ALIGN>() + translation_.template GetSerializedSize<ALIGN>();
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << rotation_ << translation_;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> rotation_ >> translation_;
    }

    /**
     * @brief dimension of pose3
     *
     * @return uint8_t
     */
    static uint8_t Dim() noexcept;

    /**
     * @brief identity
     *
     * @return pose3
     */
    static Pose3Type Identity() noexcept;

    /**
     * @brief lie group exponential map
     *
     * @param v angle_axis + point3
     *
     * @return pose3
     */
    static Pose3Type Expmap(const Vector6Type& v) noexcept;

    /**
     * @brief lie group logarithmic map
     *
     * @param p pose3
     *
     * @return vector6 containing angle_axis + point3
     */
    static Vector6Type Logmap(Pose3Type const& p) noexcept;

    /**
     * @brief interpolate between two poses
     *
     * @details support interpolate and extrapolate
     *
     * @verbatim
     *     ratio = (interpolate - left) / (right - left)
     *     if ratio in [0.0, 1.0] :
     *         (rotation: quaternion slerp, translation: linear interpolation)
     *     else if ratio < 0.0 || ratio > 1.0 :
     *         (rotation: angle axis, translation: linear extrapolation)
     * @endverbatim
     * @param left left pose
     * @param right right pose
     * @param ratio ratio
     *
     * @return pose3
     */
    static Pose3Type Interpolate(Pose3Type const& left, Pose3Type const& right, const ScalarType ratio) noexcept;

private:
    /**
     * @brief rotation matrix
     */
    Rot3Type rotation_;

    /**
     * @brief translation vector
     */
    Point3Type translation_;

};  // Pose3T

/**
 * @}
 *
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#include "./impl/pose3.hpp"

#endif  // HOLO_GEOMETRY_DETAILS_POSE3_H_
