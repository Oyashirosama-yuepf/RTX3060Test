/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point3.h
 * @brief A point in 3D space
 * @author Li Chao
 * @author duyanwei@holomatic.com
 * @date 09-17-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_POINT3_H_
#define HOLO_GEOMETRY_DETAILS_POINT3_H_

#include <cmath>
#include <iomanip>
#include <string>

#include <holo/core/exception.h>
#include <holo/geometry/point2.h>
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
 * @brief point in 3D
 *
 * @tparam T float32_t or float64_t
 */
template <typename T>
class Point3T
{
public:
    using ScalarType                = T;
    using Point2Type                = Point2T<ScalarType>;
    using Point3Type                = Point3T<ScalarType>;
    using Vector3Type               = holo::numerics::Vector3T<ScalarType>;
    using Vector4Type               = holo::numerics::Vector4T<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    static size_t const SIZE_VALUE = 3U;

    static_assert(std::is_floating_point<ScalarType>::value, "Point3T needs to take floating type");

    /**
     * @brief default constructor
     */
    Point3T() noexcept;

    /**
     * @brief constructor
     *
     * @param x x value
     * @param y y value
     * @param z z value
     */
    Point3T(ScalarType const x, ScalarType const y, ScalarType const z) noexcept;

    /**
     * @brief constructor
     *
     * @param v vector3
     */
    explicit Point3T(Vector3Type const& v) noexcept;

    /**
     * @brief constructor from point2, z is set to zero
     *
     * @param pt2 Point2Type
     */
    Point3T(Point2Type const& pt2) noexcept;

    /**
     * @brief Get index-th element of point type.
     *
     * @param index element index. Valid range is [0, SIZE_VALUE)
     *
     * @return index-th element
     */
    ScalarType const& operator[](size_t index) const noexcept
    {
        assert(index < SIZE_VALUE);
        return data_[index];
    }

    /**
     * @brief Get index-th element of point type.
     *
     * @param index element index. Valid range is [0, SIZE_VALUE)
     *
     * @return index-th element
     */
    ScalarType& operator[](size_t index) noexcept
    {
        assert(index < SIZE_VALUE);
        return data_[index];
    }

    /**
     * @brief operator-()
     *
     * @return negative point3
     */
    Point3Type operator-() const noexcept;

    /**
     * @brief operator+
     *
     * @param p point3
     *
     * @return point3
     */
    Point3Type operator+(Point3Type const& p) const noexcept;

    /**
     * @brief operator-
     *
     * @param p point3
     *
     * @return point3
     */
    Point3Type operator-(Point3Type const& p) const noexcept;

    /**
     * @brief operator+=
     *
     * @param p point3
     *
     * @return point3
     */
    Point3Type& operator+=(Point3Type const& p) noexcept;

    /**
     * @brief operator-=
     *
     * @param p point3
     *
     * @return point3
     */
    Point3Type& operator-=(Point3Type const& p) noexcept;

    /**
     * @brief operator==
     *
     * @param p point3
     *
     * @return equal or not
     */
    bool_t operator==(Point3Type const& p) const noexcept;

    /**
     * @brief operator+
     *
     * @param v vector3
     *
     * @return point3
     */
    [[deprecated("pass Point3Type instead")]] Point3Type operator+(const Vector3Type& v) const noexcept
    {
        return this->operator+(Point3Type(v));
    }

    /**
     * @brief operator-
     *
     * @param v vector3
     *
     * @return point3
     */
    [[deprecated("pass Point3Type instead")]] Point3Type operator-(const Vector3Type& v) const noexcept
    {
        return this->operator-(Point3Type(v));
    }

    /**
     * @brief operator+=
     *
     * @param v vector3
     *
     * @return point3
     */
    [[deprecated("pass Point3Type instead")]] Point3Type& operator+=(Vector3Type const& v) noexcept
    {
        return this->operator+=(Point3Type(v));
    }

    /**
     * @brief operator-=
     *
     * @param v vector3
     *
     * @return point3
     */
    [[deprecated("pass Point3Type instead")]] Point3Type& operator-=(Vector3Type const& v) noexcept
    {
        return this->operator-=(Point3Type(v));
    }

    /**
     * @brief operator* (q = s * p)
     *
     * @param s scalar
     * @param p point3
     *
     * @return point3
     */
    friend Point3Type operator*(ScalarType s, Point3Type const& p) noexcept
    {
        return Point3Type(s * p.GetX(), s * p.GetY(), s * p.GetZ());
    }

    /**
     * @brief operator* (q = p * s)
     *
     * @param s scalar
     */
    Point3Type operator*(ScalarType s) const noexcept;

    /**
     * @brief operator/
     *
     * @param s scalar
     *
     * @return point3
     *
     * @throw std::runtime_error if scalar s is zero
     */
    Point3Type operator/(ScalarType s) const;

    /**
     * @brief conversion operator
     *
     * @tparam OutputScalar
     *
     * @return point3
     */
    template <typename OutputScalar>
    explicit operator Point3T<OutputScalar>() const noexcept
    {
        return Point3T<OutputScalar>(static_cast<OutputScalar>(data_[0]), static_cast<OutputScalar>(data_[1]),
                                     static_cast<OutputScalar>(data_[2]));
    }

    /**
     * @brief operator <<
     *
     * @param os std::ostream
     * @param p point3
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, Point3Type const& p) noexcept
    {
        os << p.ToString(os.precision(), os.width());
        return os;
    }

    /**
     * @brief convert point3 to string
     *
     * @param precision output precision
     * @param width ouput width
     *
     * @return std::string
     */
    std::string ToString(uint8_t precision = 6u, uint8_t width = 0u) const noexcept
    {
        std::stringstream ss;
        ss << std::setprecision(precision) << std::setw(width) << "point3: (" << data_[0] << ", " << data_[1] << ","
           << data_[2] << ")" << std::endl;
        return ss.str();
    }

    /**
     * @brief convert point3 to different scalar types
     *
     * @tparam OutputScalar
     *
     * @return point3
     */
    template <typename OutputScalar>
    [[deprecated]] Point3T<OutputScalar> Cast() const noexcept
    {
        return Point3T<OutputScalar>(static_cast<OutputScalar>(data_[0]), static_cast<OutputScalar>(data_[1]),
                                     static_cast<OutputScalar>(data_[2]));
    }

    /**
     * @brief to vector
     *
     * @return vector3
     */
    [[deprecated]] Vector3Type ToVector() const noexcept;

    template <typename CastType>
    CastType As() const noexcept
    {
        return {data_[0U], data_[1U], data_[2U]};
    }

    /**
     * @brief point in xy plane
     *
     * @return point2
     */
    Point2Type GetPointXY() const noexcept;

    /**
     * @brief check zero
     *
     * @return
     */
    bool_t IsZero() const noexcept;

    /**
     * @brief homogeneous coordinate
     *
     * @return vector4
     */
    Vector4Type Homogeneous() const noexcept;

    /**
     * @brief squared distance
     *
     * @param target poitn3
     *
     * @return scalar
     */
    ScalarType DistSqr(Point3Type const& target) const noexcept;

    /**
     * @brief distance
     *
     * @param target point3
     *
     * @return scalar
     */
    ScalarType Dist(Point3Type const& target) const noexcept;

    /**
     * @brief equals test
     *
     * @param target point3
     * @param threshold tolerance
     *
     * @return true for equal, otherwise false
     */
    bool_t IsEqual(Point3Type const& target, ScalarType threshold = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept;

    /**
     * @brief all finite check
     *
     * @return true for finite, otherwise false
     */
    bool_t IsFinite() const noexcept;

    /**
     * @brief valid
     *
     * @return true for valid
     */
    bool_t IsValid() const noexcept;

    /**
     * @brief get x
     *
     * @return ScalarType
     */
    ScalarType GetX() const noexcept
    {
        return data_[0];
    }

    /**
     * @brief get y
     *
     * @return ScalarType
     */
    ScalarType GetY() const noexcept
    {
        return data_[1];
    }

    /**
     * @brief get z
     *
     * @return ScalarType
     */
    ScalarType GetZ() const noexcept
    {
        return data_[2];
    }

    /**
     * @brief Get Ith element of Point
     *
     * @tparam I Index
     *
     * @return reference of Ith index element
     */
    template <size_t I, typename std::enable_if<(I < SIZE_VALUE), void>::type* = nullptr>
    ScalarType& Get() noexcept
    {
        return data_[I];
    }

    /**
     * @brief Get Ith element of Point
     *
     * @tparam I Index
     *
     * @return reference of Ith index element
     */
    template <size_t I, typename std::enable_if<(I < SIZE_VALUE), void>::type* = nullptr>
    ScalarType const& Get() const noexcept
    {
        return data_[I];
    }

    /**
     * @brief set x
     *
     * @param v value
     */
    void SetX(ScalarType v) noexcept
    {
        data_[0] = v;
    }

    /**
     * @brief set y
     *
     * @param v value
     */
    void SetY(ScalarType v) noexcept
    {
        data_[1] = v;
    }

    /**
     * @brief set z
     *
     * @param v value
     */
    void SetZ(ScalarType v) noexcept
    {
        data_[2] = v;
    }

    /**
     * @brief set x, y and z
     *
     * @param x x value
     * @param y y value
     * @param z z value
     */
    void Set(ScalarType x, ScalarType y, ScalarType z) noexcept
    {
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
    }

    /**
     * @brief set x, y and z from vector3
     *
     * @param v vector3
     */
    void Set(Vector3Type const& v) noexcept
    {
        static_cast<void>(data_[0] = v(0u));
        static_cast<void>(data_[1] = v(1u));
        static_cast<void>(data_[2] = v(2u));
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
        return holo::serialization::AlignedSize<ALIGN>(3 * sizeof(ScalarType));
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << data_[0] << data_[1] << data_[2] << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
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
        deserializer >> holo::serialization::align >> data_[0] >> data_[1] >> data_[2] >> holo::serialization::align;
    }

    /// static functions

    /**
     * @brief dimension
     *
     * @return 3
     */
    static uint8_t Dim() noexcept;

    /**
     * @brief zero point
     *
     * @return point3
     */
    static Point3Type Zero() noexcept;

    /**
     * @brief one point
     *
     * @return point3
     */
    static Point3Type One() noexcept;

    /**
     * @brief unit x
     *
     * @return point3 on x axis with unit length
     */
    static Point3Type UnitX() noexcept;

    /**
     * @brief unit y
     *
     * @return point3 on y axis with unit length
     */
    static Point3Type UnitY() noexcept;

    /**
     * @brief unit z
     *
     * @return point3 on z axis with unit length
     */
    static Point3Type UnitZ() noexcept;

    /**
     * @brief lie group exponential map
     *
     * @param v vector3
     *
     * @return point3
     */
    static Point3Type Expmap(Vector3Type const& v) noexcept;

    /**
     * @brief lie group log map
     *
     * @param p point3
     *
     * @return vector3
     */
    static Vector3Type Logmap(Point3Type const& p) noexcept;

private:
    /**
     * @brief internal memory layout
     */
    ScalarType data_[SIZE_VALUE];  ///< internal memory layout

};  // class Point3T

/**
 * @}
 *
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#include "./impl/point3.hpp"

#endif  // HOLO_GEOMETRY_DETAILS_POINT3_H_
