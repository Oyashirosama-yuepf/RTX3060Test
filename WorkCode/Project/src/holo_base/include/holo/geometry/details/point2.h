/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point2.h
 * @brief This header file defines point in 2d.
 * @author duyanwei@holomatic.com
 * @date 2019-08-30
 */

#ifndef HOLO_GEOMETRY_DETAILS_POINT2_H_
#define HOLO_GEOMETRY_DETAILS_POINT2_H_

#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <type_traits>

#include <holo/core/epsilon.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
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
 * @brief point in 2D
 *
 * @tparam T float32_t or float64_t
 */
template <typename T>
class Point2T
{
public:
    using ScalarType                = T;
    using Point2Type                = Point2T<ScalarType>;
    using Vector2Type               = holo::numerics::VectorT<ScalarType, 2>;
    using Vector3Type               = holo::numerics::VectorT<ScalarType, 3>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    static size_t const SIZE_VALUE = 2U;

    static_assert(std::is_floating_point<ScalarType>::value, "Point2T needs to take floating type");

    /**
     * @brief default constructor
     */
    Point2T() noexcept;

    /**
     * @brief constructor take x, y as parameters
     *
     * @param x x value
     * @param y y value
     */
    Point2T(ScalarType const x, ScalarType const y) noexcept;

    /**
     * @brief constructor take x, y, z as parameters where z is nonsense.
     *
     * @note it enables the templated assignment in terms of Point3T
     *
     * @param x x value
     * @param y y value
     */
    Point2T(ScalarType const x, ScalarType const y, ScalarType const /*z*/) noexcept;

    /**
     * @brief initialize from vector
     *
     * @param v vector2
     */
    explicit Point2T(Vector2Type const& v) noexcept;

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
     * @return negative point2
     */
    Point2Type operator-() const noexcept;

    /**
     * @brief operator+
     *
     * @param p point2
     *
     * @return point2
     */
    Point2Type operator+(Point2Type const& p) const noexcept;

    /**
     * @brief operator-
     *
     * @param p point2
     *
     * @return point2
     */
    Point2Type operator-(Point2Type const& p) const noexcept;

    /**
     * @brief operator+=
     *
     * @param p point2
     *
     * @return point2
     */
    Point2Type& operator+=(Point2Type const& p) noexcept;

    /**
     * @brief operator-=
     *
     * @param p point2
     *
     * @return point2
     */
    Point2Type& operator-=(Point2Type const& p) noexcept;

    /**
     * @brief operator==
     *
     * @param p point2
     *
     * @return equal or not
     */
    bool_t operator==(Point2Type const& p) const noexcept;

    /**
     * @brief operator+
     *
     * @param v vector2
     *
     * @return point2
     */
    [[deprecated("pass Point2Type instead")]] Point2Type operator+(Vector2Type const& v) const noexcept
    {
        return this->operator+(Point2Type(v));
    }

    /**
     * @brief operator-
     *
     * @param v vector2
     *
     * @return point2
     */
    [[deprecated("pass Point2Type instead")]] Point2Type operator-(Vector2Type const& v) const noexcept
    {
        return this->operator-(Point2Type(v));
    }

    /**
     * @brief operator+=
     *
     * @param v vector2
     *
     * @return point2
     */
    [[deprecated("pass Point2Type instead")]] Point2Type& operator+=(Vector2Type const& v) noexcept
    {
        return this->operator+=(Point2Type(v));
    }

    /**
     * @brief operator-=
     *
     * @param v vector2
     *
     * @return point2
     */
    [[deprecated("pass Point2Type instead")]] Point2Type& operator-=(Vector2Type const& v) noexcept
    {
        return this->operator-=(Point2Type(v));
    }

    /**
     * @brief operator*, multiply by a scalar (q = s * p)
     *
     * @param s scalar
     * @param p point2
     *
     * @return point2
     */
    friend Point2Type operator*(ScalarType s, Point2Type const& p) noexcept
    {
        return Point2Type(s * p.GetX(), s * p.GetY());
    }

    /**
     * @brief operator*, multiply a scalar (q = p * s)
     *
     * @param s scalar
     *
     * @return point2
     */
    Point2Type operator*(ScalarType s) const noexcept;

    /**
     * @brief operator/, divide a scalar
     *
     * @param s scalar
     *
     * @return point2
     * @throw std::runtime_error if scalar s is zero
     */
    Point2Type operator/(ScalarType s) const;

    /**
     * @brief conversion operator
     *
     * @tparam OutputScalar
     *
     * @return point2
     */
    template <typename OutputScalar>
    explicit operator Point2T<OutputScalar>() const noexcept
    {
        return Point2T<OutputScalar>(static_cast<OutputScalar>(data_[0]), static_cast<OutputScalar>(data_[1]));
    }

    /**
     * @brief output operator
     *
     * @param os std::ostream
     * @param p point2
     *
     * @return std::ostream
     */
    inline friend std::ostream& operator<<(std::ostream& os, Point2Type const& p) noexcept
    {
        os << p.ToString();
        return os;
    }

    /**
     * @brief cast to different scalar types
     *
     * @tparam OutScalar
     *
     * @return point2
     */
    template <typename OutScalar>
    [[deprecated]] Point2T<OutScalar> Cast() const noexcept
    {
        return Point2T<OutScalar>(static_cast<OutScalar>(data_[0]), static_cast<OutScalar>(data_[1]));
    }

    /**
     * @brief convert point2 to string
     *
     * @return std::string
     */
    std::string ToString() const noexcept
    {
        std::stringstream ss;
        ss << "point2: (" << data_[0] << ", " << data_[1] << ")" << std::endl;
        return ss.str();
    }

    /**
     * @brief check point's validation
     *
     * @return valid or not
     */
    bool_t IsValid() const noexcept;

    /**
     * @brief point2 to vector2
     *
     * @return vector2
     */
    Vector2Type ToVector() const noexcept;

    template <typename CastType>
    CastType As() const noexcept
    {
        return {data_[0U], data_[1U]};
    }

    /**
     * @brief check *this equals another point
     *
     * @param other point2
     * @param tol tolerance
     *
     * @return true for equal
     */
    bool_t IsEqual(Point2Type const& other, ScalarType tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept;

    /**
     * @brief squared distance between two points
     *
     * @param target point2
     *
     * @return squared distance
     */
    ScalarType DistSqr(Point2Type const& target) const noexcept;

    /**
     * @brief distance between two points
     *
     * @param target point2
     *
     * @return distance
     */
    ScalarType Dist(Point2Type const& target) const noexcept;

    /**
     * @brief check if point2 is finite
     *
     * @return true for finite, otherwise false
     */
    bool IsFinite() const noexcept;

    /**
     * @brief get X of point2
     *
     * @return ScalarType
     */
    inline ScalarType GetX() const noexcept
    {
        return data_[0];
    }

    /**
     * @brief get Y of point2
     *
     * @return ScalarType
     */
    inline ScalarType GetY() const noexcept
    {
        return data_[1];
    }

    /**
     * @brief get Z of point2 (0.0)
     *
     * @return ScalarType
     */
    inline ScalarType GetZ() const noexcept
    {
        return static_cast<ScalarType>(0.0);
    }

    /**
     * @brief get point xy
     *
     */
    inline Point2Type GetPointXY() const noexcept
    {
        return Point2Type(data_[0], data_[1]);
    }

    /**
     * @brief set X of point2
     *
     * @param v value
     */
    inline void SetX(ScalarType v) noexcept
    {
        data_[0] = v;
    }

    /**
     * @brief set Y of point2
     *
     * @param v value
     */
    inline void SetY(ScalarType v) noexcept
    {
        data_[1] = v;
    }

    /**
     * @brief set x, y
     *
     * @param x x value
     * @param y y value
     */
    inline void Set(ScalarType x, ScalarType y) noexcept
    {
        data_[0] = x;
        data_[1] = y;
    }

    /**
     * @brief point2 in homogeneous coordinates
     *
     * @return vector3
     */
    Vector3Type Homogeneous() const noexcept;

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::AlignedSize<ALIGN>(2U * sizeof(ScalarType));
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << data_[0U] << data_[1U] << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> holo::serialization::align >> data_[0U] >> data_[1U] >> holo::serialization::align;
    }

    /**
     * @brief lie group exponential map
     *
     * @param v vector2
     *
     * @return point2
     */
    static Point2Type Expmap(Vector2Type const& v) noexcept;

    /**
     * @brief lie group log map
     *
     * @param p point2
     *
     * @return vector2
     */
    static Vector2Type Logmap(Point2Type const& p) noexcept;

    /**
     * @brief static function return zero point
     *
     * @return zero point
     */
    static Point2Type Zero() noexcept;

    /**
     * @brief static function return one point
     *
     * @return one point
     */
    static Point2Type One() noexcept;

    /**
     * @brief static function return a point on x axis with unit length
     *
     * @return a point on x axis with unit length
     */
    static Point2Type UnitX() noexcept;

    /**
     * @brief static function return a point on y axis with unit length
     *
     * @return a point on y axis with unit length
     */
    static Point2Type UnitY() noexcept;

    /**
     * @brief return the dimension of point2
     *
     * @return dimension
     */
    static uint8_t Dim() noexcept;

private:
    ScalarType data_[SIZE_VALUE];  ///< internal memory layout
};

/**
 * @}
 *
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#include "impl/point2.hpp"

#endif  // HOLO_GEOMETRY_DETAILS_POINT2_H_
