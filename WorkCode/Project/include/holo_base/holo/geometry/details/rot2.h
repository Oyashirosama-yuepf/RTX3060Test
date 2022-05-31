/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rot2.h
 * @brief rotation in 2D space
 * @author duyanwei@holomatic.com
 * @date Sep-25-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_ROT2_H_
#define HOLO_GEOMETRY_DETAILS_ROT2_H_

#include <holo/core/epsilon.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/geometry/angle.h>
#include <holo/geometry/point2.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>
#include <holo/serialization/serialization.h>

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
 * @brief rotation in 2D
 *
 * @tparam T float32_t or float64_t
 */
template <typename T>
class Rot2T
{
public:
    using This                      = Rot2T<T>;
    using ScalarType                = T;
    using Rot2Type                  = Rot2T<ScalarType>;
    using Point2Type                = Point2T<ScalarType>;
    using Matrix2Type               = holo::numerics::Matrix2T<ScalarType>;
    using Vector2Type               = holo::numerics::Vector2T<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    static_assert(std::is_floating_point<ScalarType>::value, "Rot2T needs to take floating type");

    /**
     * @brief default constructor
     */
    Rot2T() noexcept;

    /**
     * @brief constructor from angle in radian
     *
     * @param theta angle in radian
     */
    explicit Rot2T(ScalarType const theta) noexcept;

    /**
     * @brief constructor from 2x2 matrix
     *
     * @param m matrix
     * @throw std::runtime_error if m is not a rotation matrix
     */
    explicit Rot2T(Matrix2Type const& m);

    /**
     * @brief copy constructor
     *
     * @param other rotation
     */
    Rot2T(Rot2Type const& other) noexcept;

    /**
     * @brief destructor
     */
    ~Rot2T() noexcept;

    /**
     * @brief operator=
     *
     * @param other rotation
     *
     * @return rot2
     */
    Rot2Type& operator=(Rot2Type const& other) noexcept;

    /**
     * @brief operator* compose - make a new rotation by adding angles
     *
     * @param other rotation matrix
     *
     * @return rot2
     */
    Rot2Type operator*(Rot2Type const& other) const noexcept;

    /**
     * @brief operator*, rotate a point2
     *
     * @param p point2
     *
     * @return point2
     */
    Point2Type operator*(Point2Type const& p) const noexcept;

    /**
     * @brief operator*, rotate a vector2
     *
     * @param v vector2
     *
     * @return vector2
     */
    Vector2Type operator*(Vector2Type const& v) const noexcept;

    /**
     * @brief operator==, check if two rotation matrices are equal
     *
     * @param other rotation matrix
     *
     * @return bool_t
     */
    bool_t operator==(Rot2Type const& other) const noexcept;

    /**
     * @brief output stream operator
     *
     * @param os std::ostream
     * @param r rotation matrix
     *
     * @return ostream
     */
    friend std::ostream& operator<<(std::ostream& os, Rot2Type const& r) noexcept
    {
        os << r.ToString();
        return os;
    }

    /**
     * @brief conversion operator
     *
     * @tparam OutputScalar
     *
     * @return rot2
     */
    template <typename OutputScalar>
    explicit operator Rot2T<OutputScalar>() const noexcept
    {
        return Cast<OutputScalar>();
    }

    /**
     * @brief convert rot2 to string
     *
     * @return string
     */
    std::string ToString() const noexcept
    {
        std::stringstream ss;
        ss << "rot2: (" << c_ << ", " << s_ << ")" << std::endl;
        return ss.str();
    }

    /**
     * @brief cast to different ScalarType type
     *
     * @tparam OutputScalar
     *
     * @return rot2
     */
    template <typename OutputScalar>
    Rot2T<OutputScalar> Cast() const noexcept
    {
        return Rot2T<OutputScalar>(static_cast<OutputScalar>(GetTheta()));
    }

    /**
     * @brief check if a matrix is valid
     *
     * @return true for valid, otherwise false
     */
    bool_t IsValid() const noexcept;

    /**
     * @brief check if two matrices are equal
     *
     * @param other rotation matrix
     * @param tol tolerance
     *
     * @return true for equal
     */
    bool_t IsEqual(Rot2Type const& other, ScalarType const tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept;

    /**
     * @brief inverse rotation - negative angle
     *
     * @return rot2
     */
    Rot2Type Inverse() const noexcept;

    /**
     * @brief rotate point from rotated coordinate frame to world
     *
     * @param p point2
     *
     * @return point2
     */
    Point2Type Rotate(Point2Type const& p) const noexcept;

    /**
     * @brief rotate a vector from rotated frame to world
     *
     * @param v vector2
     *
     * @return vector2
     */
    Vector2Type Rotate(Vector2Type const& v) const noexcept;

    /**
     * @brief unrotate point from world to rotated frame \
     *
     * @param p point2
     *
     * @return point2
     */
    Point2Type Unrotate(Point2Type const& p) const noexcept;

    /**
     * @brief unrotate a vector from world to rotated frame
     *
     * @param v vector2
     *
     * @return vector2
     */
    Vector2Type Unrotate(Vector2Type const& v) const noexcept;

    /**
     * @brief 2x2 matrix
     *
     * @return return matrix22
     */
    Matrix2Type ToMatrix() const noexcept;

    /**
     * @brief rotation angle in radian
     *
     * @return ScalarType
     */
    ScalarType GetTheta() const noexcept;

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
        return holo::serialization::SerializedSize<ALIGN>(c_, s_);
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
        serializer << holo::serialization::align << c_ << s_ << holo::serialization::align;
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
        deserializer >> holo::serialization::align >> c_ >> s_ >> holo::serialization::align;
    }
    /**
     * @brief Named constructor from angle in degrees
     *
     * @param degree angle in degree
     *
     * @return
     */
    static Rot2Type FromDegree(ScalarType const degree) noexcept;

    /**
     * @brief identity
     *
     * @return rot2
     */
    static Rot2Type Identity() noexcept;

    /**
     * @brief dimension
     *
     * @return uint8_t
     */
    static uint8_t Dim() noexcept;

private:
    /**
     * @brief private constructor takes cos and sin as input parameters
     *
     * @param c consine value of angle
     * @param s sine value of angle
     */
    Rot2T(ScalarType const c, ScalarType const s) noexcept;

    /**
     * @brief normalize to make sure cos and sin form unit vector
     *
     * @param epsilon
     */
    void Normalize(ScalarType const epsilon = ScalarEqualT<ScalarType>().GetEpsilonValue()) noexcept;

    /**
     * @brief cos(theta)
     */
    ScalarType c_;

    /**
     * @brief sin(theta)
     */
    ScalarType s_;
};

/**
 * @}
 *
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#include "./impl/rot2.hpp"

#endif  // HOLO_GEOMETRY_DETAILS_ROT2_H_
