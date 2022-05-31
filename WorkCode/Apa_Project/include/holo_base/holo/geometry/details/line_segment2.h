/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line_segment2.h
 * @brief a line segment in 2D space
 * @author duyanwei@holomatic.com
 * @date 2019-09-24
 */

#ifndef HOLO_GEOMETRY_DETAILS_LINE_SEGMENT2_H_
#define HOLO_GEOMETRY_DETAILS_LINE_SEGMENT2_H_

#include <holo/geometry/line2.h>
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
 */

/**
 * @brief A line segment in 2-D
 *
 * @details line segment equation: pt + t * v, where t belongs to [0,1],
 *          and in vector form [pt.x, pt.y, v(0), v(1)]
 *
 * @tparam T float32_t or float64_t
 */
template <typename T>
class LineSegment2T
{
public:
    using This                      = LineSegment2T<T>;
    using ScalarType                = T;
    using Point2Type                = Point2T<ScalarType>;
    using Vector2Type               = holo::numerics::Vector2T<ScalarType>;
    using Vector3Type               = holo::numerics::Vector3T<ScalarType>;
    using Vector4Type               = holo::numerics::Vector4T<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    static_assert(std::is_floating_point<ScalarType>::value, "LineSegment2T needs to take floating type");

    /**
     * @brief default constructor
     */
    LineSegment2T() noexcept;

    /**
     * @brief constructed from two points (p1 and p2)
     *
     * @details particularly linesegment: p1 + t \times (p2 - p1), with t \in [0, 1]
     *
     * @param p1 point1
     * @param p2 point2
     * @throw std::runtime_error if p1 and p2 does NOT form a line segment
     */
    LineSegment2T(Point2Type const& p1, Point2Type const& p2);

    /**
     * @brief copy constructor
     *
     * @param other line segment
     */
    LineSegment2T(LineSegment2T const& other) noexcept;

    /**
     * @brief destructor
     */
    ~LineSegment2T() noexcept;

    /**
     * @brief assignment operator
     *
     * @param other line segment
     */
    LineSegment2T& operator=(LineSegment2T const& other) noexcept;

    /**
     * @brief cast to different type
     *
     * @return new line segment2 type
     */
    template <typename OutputScalarType>
    explicit operator LineSegment2T<OutputScalarType>() const noexcept
    {
        return Cast<OutputScalarType>();
    }

    /**
     * @brief operator ==, check if two line segments are equal
     *
     * @param other line segment
     * @return true or false
     */
    bool_t operator==(LineSegment2T const& other) const noexcept;

    /**
     * @brief output stream
     *
     * @param os std::ostream
     * @param ls line segment
     * @return std::ostream
     */
    friend std::ostream& operator<<(std::ostream& os, LineSegment2T<T> const& ls) noexcept
    {
        os << ls.ToString();
        return os;
    }

    /**
     * @brief convert data to string
     *
     * @return std::string
     */
    std::string ToString() const noexcept
    {
        std::stringstream ss;
        ss << "lineSegment2: start point (" << x_ << ", " << y_ << "), direction (" << v0_ << ", " << v1_ << ")";
        return ss.str();
    }

    /**
     * @brief cast to different type
     *
     * @return new line segment2 type
     */
    template <typename OutputScalarType>
    LineSegment2T<OutputScalarType> Cast() const noexcept
    {
        return LineSegment2T<OutputScalarType>(static_cast<Point2T<OutputScalarType>>(GetStartPoint()),
                                               static_cast<Point2T<OutputScalarType>>(GetEndPoint()));
    }

    /**
     * @brief check if a point is on the line segment
     *
     * @param pt point
     * @param tol tolerance
     *
     * @return true or false
     */
    bool_t Contains(Point2Type const& pt, ScalarType const tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept;

    /**
     * @brief check if two line segments are equal
     *
     * @param other line segment
     * @param tol tolerance
     *
     * @return true or false
     */
    bool_t IsEqual(LineSegment2T const& other,
                   ScalarType const     tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const noexcept;

    /**
     * @brief check if the data satisfies the definition of line segment
     *
     * @return true or false
     */
    bool_t IsValid() const noexcept;

    /**
     * @brief compute the shortest distance from a point to the line segment
     *
     * @param pt point
     * @return distance of point to line segment
     */
    ScalarType Dist(Point2Type const& pt) const noexcept;

    /**
     * @brief compute the nearest point that is on linesegment to pt
     *
     * @param pt point
     * @return projected point on line segment
     */
    Point2Type Project(Point2Type const& pt) const noexcept;

    /**
     * @brief check if two line segments are parallel
     *
     * @param other line segment
     * @param tol tolerance
     * @return true or false
     */
    bool_t IsParallel(LineSegment2T const& other,
                      ScalarType const     tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const noexcept;

    /**
     * @brief find the intersection of two line segments if any
     *
     * @param other line segment
     * @param pt intersected point if any
     * @return true of false
     */
    bool_t Intersect(LineSegment2T const& ls, Point2Type& pt) const noexcept;

    /**
     * @brief return the point given t in [0, 1] inclusive
     *
     * @param t ratio within [0, 1]
     * @return interpolated point
     */
    Point2Type Interpolate(ScalarType const t) const noexcept;

    /**
     * @brief return the startpoint of line segment
     */
    Point2Type GetStartPoint() const noexcept;

    /**
     * @brief return the endpoint of line segment
     */
    Point2Type GetEndPoint() const noexcept;

    /**
     * @brief return the length of line segment
     */
    ScalarType GetLength() const noexcept;

    /**
     * @brief return the normalized normal vector of the line segment,
     *        where the first non-zero element is positive
     */
    Vector2Type GetNormal() const noexcept;

    /**
     * @brief return the normalized direction vector of the line segment
     */
    Vector2Type GetDirection() const noexcept;

    /**
     * @brief return the data vector
     *
     * @details the first two stores the start point,
     *          the last two stores the direction vector which is not
     *          necessarily normalized, please refer to the definition
     */
    Vector4Type GetCoeffs() const noexcept;

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
        return holo::serialization::SerializedSize<ALIGN>(x_, y_, v0_, v1_);
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
        serializer << holo::serialization::align << x_ << y_ << v0_ << v1_ << holo::serialization::align;
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
        deserializer >> holo::serialization::align >> x_ >> y_ >> v0_ >> v1_ >> holo::serialization::align;
    }

private:
    /**
     * @brief line segment coefficients
     */
    ScalarType x_;
    ScalarType y_;
    ScalarType v0_;
    ScalarType v1_;

};  // LineSegment2T

/**
 * @}
 *
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#include "./impl/line_segment2.hpp"

#endif  // HOLO_GEOMETRY_DETAILS_LINE_SEGMENT2_H_
