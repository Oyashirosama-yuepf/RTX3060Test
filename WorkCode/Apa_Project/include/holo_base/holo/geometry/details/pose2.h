/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pose2.h
 * @brief pose in 2D space
 * @author duyanwei@holomatic.com
 * @date Sep-25-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_POSE2_H_
#define HOLO_GEOMETRY_DETAILS_POSE2_H_

#include <holo/core/epsilon.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/rot2.h>

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
 * @brief pose in 2D
 *
 * @tparam T float32_t or float64_t
 */
template <typename T>
class Pose2T
{
public:
    using ScalarType                = T;
    using Pose2Type                 = Pose2T<ScalarType>;
    using Point2Type                = Point2T<ScalarType>;
    using Rot2Type                  = Rot2T<ScalarType>;
    using Vector2Type               = holo::numerics::Vector2T<ScalarType>;
    using Matrix2Type               = holo::numerics::Matrix2T<ScalarType>;
    using Matrix3Type               = holo::numerics::Matrix3T<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    static_assert(std::is_floating_point<ScalarType>::value, "Pose2T needs to take floating type");

    /**
     * @brief default constructor
     */
    Pose2T() noexcept;

    /**
     * @brief construct from rotation and translation
     *
     * @param r rotation
     * @param t translation
     */
    Pose2T(Rot2Type const& r, Point2Type const& t) noexcept;

    /**
     * @brief construct from theta angle in radian and translation
     *
     * @param theta angle in radian
     * @param t translation point
     */
    Pose2T(ScalarType const theta, Point2Type const& t) noexcept;

    /**
     * @brief construct from theta angle in radian and translation (x, y)
     *
     * @param theta angle in radian
     * @param x value of x
     * @param y value of y
     */
    Pose2T(ScalarType const theta, ScalarType const x, ScalarType const y) noexcept;

    /**
     * @brief constructor from 3x3 matrix
     *
     * @param m matrix
     * @throw std::runtimer_error if m is not pose
     */
    explicit Pose2T(Matrix3Type const& m);

    /**
     * @brief copy constructor
     *
     * @param other pose2
     */
    Pose2T(Pose2Type const& other) noexcept;

    /**
     * @brief operator=
     *
     * @param other pose2
     *
     * @return pose2
     */
    Pose2Type& operator=(Pose2Type const& other) noexcept;

    /**
     * @brief operator*
     *
     * @param other pose2
     *
     * @return pose2
     */
    Pose2Type operator*(Pose2Type const& other) const noexcept;

    /**
     * @brief operator*
     *
     * @param p point2
     *
     * @return point2
     */
    Point2Type operator*(Point2Type const& p) const noexcept;

    /**
     * @brief operator*
     *
     * @param v vector2
     *
     * @return vector2
     */
    Vector2Type operator*(Vector2Type const& v) const noexcept;

    /**
     * @brief operator==, check if two pose2 are equal
     *
     * @param other pose
     *
     * @return bool_t
     */
    bool_t operator==(Pose2Type const& other) const noexcept;

    /**
     * @brief conversion operator
     *
     * @tparam OutputScalar
     *
     * @return pose2
     */
    template <typename OutputScalar>
    explicit operator Pose2T<OutputScalar>() const noexcept
    {
        return Cast<OutputScalar>();
    }

    /**
     * @brief operator<<
     *
     * @param os std::ostream
     * @param pose pose2
     *
     * @return ostream
     */
    friend std::ostream& operator<<(std::ostream& os, const Pose2T& pose) noexcept
    {
        os << pose.ToString();
        return os;
    }

    /**
     * @brief pose2 to string
     *
     * @return string
     */
    std::string ToString() const noexcept
    {
        std::stringstream ss;
        ss << "pose2: (" << rotation_ << ", " << translation_ << ")" << std::endl;
        return ss.str();
    }

    /**
     * @brief cast to different scalar types
     *
     * @tparam OutputScalar
     *
     * @return point2
     */
    template <typename OutputScalar>
    Pose2T<OutputScalar> Cast() const noexcept
    {
        return Pose2T<OutputScalar>(rotation_.template Cast<OutputScalar>(),
                                    static_cast<Point2T<OutputScalar>>(translation_));
    }

    /**
     * @brief check if two poses are equal
     *
     * @param pose pose2
     * @param tol tolerance
     *
     * @return bool_t
     */
    bool_t IsEqual(Pose2Type const& other, ScalarType const tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept;

    /**
     * @brief valid
     *
     * @return bool_t
     */
    bool_t IsValid() const noexcept;

    /**
     * @brief inverse
     *
     * @return pose2
     */
    Pose2Type Inverse() const noexcept;

    /**
     * @brief represent other's relative pose using 'this' as coordinate system
     *
     * @param other pose
     *
     * @return pose2
     */
    Pose2Type Between(const Pose2Type& other) const noexcept;

    /**
     * @brief return point coordinates in pose coordinate frame
     *
     * @param p point2
     *
     * @return point2
     */
    Point2Type TransformTo(Point2Type const& p) const noexcept;

    /**
     * @brief transform to vector version
     *
     * @param v vector2
     *
     * @return vector2
     */
    Vector2Type TransformTo(Vector2Type const& v) const noexcept;

    /**
     * @brief return point coordinates in global frame
     *
     * @param p point2
     *
     * @return point2
     */
    Point2Type TransformFrom(Point2Type const& p) const noexcept;

    /**
     * @brief transform from vector version
     *
     * @param v vector2
     *
     * @return vector2
     */
    Vector2Type TransformFrom(Vector2Type const& v) const noexcept;

    /**
     * @brief translation
     *
     * @return point2
     */
    inline Point2Type const& GetTranslation() const noexcept
    {
        return translation_;
    }

    /**
     * @brief rotation
     *
     * @return rot2
     */
    inline Rot2Type const& GetRotation() const noexcept
    {
        return rotation_;
    }

    /**
     * @brief return transformation matrix
     *
     * @return matrix3
     */
    Matrix3Type ToMatrix() const noexcept;

    /**
     * @brief return x value of pose2
     */
    inline ScalarType GetX() const noexcept
    {
        return translation_.GetX();
    }

    /**
     * @brief return y value of pose2
     */
    inline ScalarType GetY() const noexcept
    {
        return translation_.GetY();
    }

    /**
     * @brief return the angle of pose2
     */
    inline ScalarType GetTheta() const noexcept
    {
        return rotation_.GetTheta();
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
     * @brief identity
     *
     * @return pose2
     */
    static Pose2Type Identity() noexcept;

    /**
     * @brief dimension
     *
     * @return uint8_t
     */
    static uint8_t Dim() noexcept;

private:
    /**
     * @brief rotation
     */
    Rot2Type rotation_;

    /**
     * @brief translation
     */
    Point2Type translation_;

};  // Pose2T

/**
 * @}
 *
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#include "./impl/pose2.hpp"

#endif  // HOLO_GEOMETRY_DETAILS_POSE2_H_
