/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line2.h
 * @brief a line in 2D space
 * @author duyanwei@holomatic.com
 * @date 2019-09-02
 */

#ifndef HOLO_GEOMETRY_DETAILS_LINE2_H_
#define HOLO_GEOMETRY_DETAILS_LINE2_H_

#include <cmath>
#include <string>

#include <holo/core/epsilon.h>
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
 */

/**
 *
 * @brief A line in 2-D with equation a * x + b * y + c = 0
 *
 * @details It defines vector ||v|| = 1 where v = [a, b]',
 *          The leading coefficient of v has to be non-negative,
 *          i.e. if "a" is nonzero, it has to be positive,
 *          otherwise "b" is positive
 * @ref https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line/
 * @tparam T float32_t or float64_t
 */
template <typename T>
class Line2T
{
public:
    using This                      = Line2T<T>;
    using ScalarType                = T;
    using Point2Type                = Point2T<ScalarType>;
    using Vector2Type               = holo::numerics::Vector2T<ScalarType>;
    using Vector3Type               = holo::numerics::Vector3T<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    static_assert(std::is_floating_point<ScalarType>::value, "Line2T needs to take floating type");

    /**
     * @brief default constructor (defines a line of x = 0)
     *
     */
    Line2T() noexcept;

    /**
     * @brief construct a line given two points
     *
     * @param p1 point1
     * @param p2 point2
     * @throw std::runtime_error if two points do not form a line
     */
    Line2T(Point2Type const& p1, Point2Type const& p2);

    /**
     * @brief construct a line with its coefficients. ax + by + c = 0
     *
     * @param a coefficient a
     * @param b coefficient b
     * @param c coefficient c
     * @throw std::runtime_error if two points do not form a line
     */
    Line2T(ScalarType a, ScalarType b, ScalarType c)
    {
        a_ = a;
        b_ = b;
        c_ = c;
    }

    /**
     * @brief construct a line from a point and line direction
     *
     * @param p point that is on the line
     * @param v line direction
     * @throw std::runtime_error if direction is meaningless
     */
    Line2T(Point2Type const& p, Vector2Type const& v);

    /**
     * @brief construct a line with its coefficient-vector v
     *
     * @details particularly the line is formed as v(0) * x + v(1) * y + v(2) = 0
     * @param v line coefficient vector
     * @throw std::runtime_error if coefficients are invalid (e.g. all 0s or NaN)
     */
    explicit Line2T(Vector3Type const& v);

    /**
     * @brief copy constructor
     *
     * @param other the other line
     */
    Line2T(Line2T const& other) noexcept;

    /**
     * @brief destructor
     *
     */
    ~Line2T() noexcept;

    /**
     * @brief assignment operator
     *
     * @param other the other line
     */
    Line2T& operator=(Line2T const& other) noexcept;

    /**
     * @brief cast to different floating type
     *
     * @return a new line2 type
     */
    template <typename OutputScalar>
    explicit operator Line2T<OutputScalar>() const noexcept
    {
        return Cast<OutputScalar>();
    }

    /**
     * @brief operator ==
     *
     * @param other the other line
     * @return true of false
     */
    bool_t operator==(Line2T const& other) const noexcept;

    /**
     * @brief output stream
     *
     * @param os std::ostream
     * @param line line
     * @return std::ostream
     */
    friend std::ostream& operator<<(std::ostream& os, Line2T<T> const& line) noexcept
    {
        os << line.ToString();
        return os;
    }

    /**
     * @brief return a string for display
     *
     * @return std::string
     */
    std::string ToString() const noexcept
    {
        std::stringstream ss;
        ss << "line2: (" << a_ << ", " << b_ << ", " << c_ << ")" << std::endl;
        return ss.str();
    }

    /**
     * @brief cast to different type
     *
     * @return a new line2 type
     */
    template <typename OutputScalar>
    Line2T<OutputScalar> Cast() const noexcept
    {
        return Line2T<OutputScalar>(Vector3T<OutputScalar>(static_cast<OutputScalar>(a_), static_cast<OutputScalar>(b_),
                                                           static_cast<OutputScalar>(c_)));
    }

    /**
     * @brief check if a point is on the line, within a threshold
     *
     * @param p point
     * @param tol tolerance
     * @return true or false
     */
    bool_t Contains(Point2Type const& p, ScalarType const tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept;

    /**
     * @brief check if two lines are equal
     *
     * @param other the other line
     * @param tol tolerance
     * @return true or false
     */
    bool_t IsEqual(Line2T const& other, ScalarType const tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept;

    /**
     * @brief check if the data satisfies our definition
     *
     * @return true or false
     */
    bool_t IsValid() const noexcept;

    /**
     * @brief compute the shortest distance from a point to the line
     *
     * @param p point
     * @return distance from point to line
     */
    ScalarType Dist(Point2Type const& p) const noexcept;

    /**
     * @brief compute the nearest point to p that in on the line
     *
     * @param p point
     * @return projected point on line
     */
    Point2Type Project(Point2Type const& p) const noexcept;

    /**
     * @brief check if two lines are parallel
     *
     * @param other the other line
     * @param tol tolerance
     * @return true of false
     */
    bool_t IsParallel(Line2T const& other, ScalarType const tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept;

    /**
     * @brief find the intersection of two lines
     *
     * @param other the other line
     * @param p intersected point if any
     * @return true of false
     */
    bool_t Intersect(Line2T const& other, Point2Type& p) const noexcept;

    /**
     * @brief return the normal vector of the line2, where the first
     *        non-zero element is positive
     */
    Vector2Type GetNormal() const noexcept;

    /**
     * @brief return the direction vector of the line, where the first
     *        non-zero element is positive
     */
    Vector2Type GetDirection() const noexcept;

    /**
     * @brief return the data vector
     */
    Vector3Type GetCoeffs() const noexcept;

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(a_, b_, c_);
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << a_ << b_ << c_ << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> holo::serialization::align >> a_ >> b_ >> c_ >> holo::serialization::align;
    }

private:
    /**
     * @brief for internal data normalization
     */
    void Normalize() noexcept;

    ScalarType a_;
    ScalarType b_;
    ScalarType c_;

};  // class Line2T

/**
 * @}
 *
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#include "./impl/line2.hpp"

#endif  // HOLO_GEOMETRY_DETAILS_LINE2_H_
