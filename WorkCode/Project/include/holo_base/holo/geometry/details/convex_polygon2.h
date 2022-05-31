/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file convex_polygon2.h
 * @brief polygon in 2D space
 * @author duyanwei@holomatic.com
 * @date Sep-27-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_CONVEX_POLYGON2_H_
#define HOLO_GEOMETRY_DETAILS_CONVEX_POLYGON2_H_

#include <array>
#include <cassert>
#include <utility>

#include <holo/geometry/line_segment2.h>
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
 * @brief create a convex polygon in 2D which contains at least 3 vertices.
 *
 * @details the vertices MUST be in an order (clockwise or counterclockwise) and must NOT be collinear.
 *
 * @tparam T float32_t or float64_t
 * @tparam MAXIMUM_SIZE maximum number of vertices of convex polygon2
 */
template <typename T, uint8_t MAXIMUM_SIZE = 20u>
class ConvexPolygon2T
{
public:
    using ScalarType                = T;
    using Point2Type                = Point2T<ScalarType>;
    using Vector2Type               = holo::numerics::Vector2T<ScalarType>;
    using LineSegment2Type          = LineSegment2T<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    /**
     * @brief constructor to create an empty 2D convex polygon
     */
    ConvexPolygon2T() noexcept : size_(0u)
    {
    }

    /**
     * @brief copy constructor
     *
     * @param other convex polygon2
     */
    ConvexPolygon2T(ConvexPolygon2T const& other) noexcept : vertices_(other.vertices_), size_(other.size_)
    {
    }

    /**
     * @brief move constructor
     *
     * @param other convex polygon2
     */
    ConvexPolygon2T(ConvexPolygon2T&& other) noexcept : vertices_(std::move(other.vertices_)), size_(other.size_)
    {
    }

    /**
     * @brief destructor
     */
    ~ConvexPolygon2T() noexcept
    {
    }

    /**
     * @brief assignment operator
     *
     * @param other convex polygon2
     */
    ConvexPolygon2T& operator=(ConvexPolygon2T const& other) noexcept
    {
        vertices_ = other.vertices_;
        size_     = other.size_;
        return *this;
    }

    /**
     * @brief move operator
     *
     * @param other convex polygon2
     */
    ConvexPolygon2T& operator=(ConvexPolygon2T&& other) noexcept
    {
        vertices_ = std::move(other.vertices_);
        size_     = other.size_;
        return *this;
    }

    /**
     * @brief cast to a different floating type
     *
     * @tparam OutputScalar
     * @return ConvexPolygon2T<OutputScalar>
     */
    template <typename OutputScalar>
    explicit operator ConvexPolygon2T<OutputScalar>() const noexcept
    {
        return Cast<OutputScalar>();
    }

    /**
     * @brief operator==, check if two convex_polygons are equal
     *
     * @param other convex polygon2
     * @return true of false
     */
    bool_t operator==(ConvexPolygon2T const& other) const noexcept
    {
        return IsEqual(other);
    }

    /**
     * @brief output stream
     *
     * @param os std::ostream
     * @param cp convex polygon2
     * @return std::ostream
     */
    friend std::ostream& operator<<(std::ostream& os, ConvexPolygon2T const& cp) noexcept
    {
        os << cp.ToString();
        return os;
    }

    /**
     * @brief to string
     *
     * @return std::string
     */
    std::string ToString() const noexcept
    {
        std::stringstream ss;
        ss << "ConvexPolygon2: (size = " << size_ << ", vertices = ";
        for (uint8_t i = 0u; i < size_; i++)
        {
            ss << vertices_.at(i) << " ";
        }
        ss << std::endl;
        return ss.str();
    }

    /**
     * @brief cast to a different floating type
     *
     * @tparam OutputScalar
     * @return ConvexPolygon2T<OutputScalar>
     */
    template <typename OutputScalar>
    ConvexPolygon2T<OutputScalar> Cast() const noexcept
    {
        ConvexPolygon2T<OutputScalar> out;

        for (uint8_t i = 0u; i < GetSize(); i++)
        {
            out.AppendVertex(static_cast<Point2T<OutputScalar>>(GetVertex(i)));
        }

        return out;
    }

    /**
     * @brief check if the convex_polygon contains a point
     *
     * @param pt point
     * @param tol tolerance
     * @return true or false
     */
    bool_t Contains(Point2Type const& pt, ScalarType const tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept
    {
        Point2Type const pt2(pt.GetX(), pt.GetY());
        int32_t          sign = 0;
        for (uint8_t i = 0u; i < GetSize(); i++)
        {
            Point2Type const& pt0 = vertices_[i];
            Point2Type const& pt1 = (i == (uint8_t)(GetSize() - 1u)) ? vertices_[0u] : vertices_[i + 1u];

            const int32_t val = Convexity(pt0, pt1, pt0, pt2, tol);

            // on edge
            if (val == 0)
            {
                return false;
            }

            // record the first result
            if (i == 0u)
            {
                sign = val;
            }
            // check the sign consistency
            else if (sign != val)
            {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief equals, check if two equals
     *
     * @param other convex polygon2
     * @param tol equal tolerance
     * @return true or false
     */
    bool_t IsEqual(ConvexPolygon2T const& other,
                   ScalarType const       tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const noexcept
    {
        if (GetSize() != other.GetSize())
        {
            return false;
        }

        for (uint8_t i = 0u; i < GetSize(); i++)
        {
            if (!GetVertex(i).IsEqual(other.GetVertex(i), tol))
            {
                return false;
            }
        }

        return true;
    }

    /**
     * @brief check if the convex polygon satisfies our definition
     *
     * @return true or false
     */
    bool_t IsValid() const noexcept
    {
        // @STEP1: a convex polygon must have at least 3 vertices
        if (GetSize() < 3u)
        {
            // "insufficient number of vertices ( < 3)";
            return false;
        }

        // @STEP2: a polygon must be a convex polygon
        int32_t sign = 1;
        for (size_t i = 0u; i < GetSize(); i++)
        {
            // retrieve candidate point
            Point2Type const& pt1 = vertices_.at(i);
            Point2Type const& pt0 = (i == 0u) ? vertices_.at(GetSize() - 1u) : vertices_.at(i - 1u);
            Point2Type const& pt2 = (i == (uint8_t)(GetSize() - 1u)) ? vertices_.at(0u) : vertices_.at(i + 1u);

            const int32_t val = Convexity(pt0, pt1, pt1, pt2);

            // on edge
            if (val == 0)
            {
                // "assert convexity failed"
                return false;
            }

            // record the first result
            if (i == 0u)
            {
                sign = val;
            }
            // check the sign consistency
            else if (sign != val)
            {
                // "assert convexity failed"
                return false;
            }
        }
        return true;
    }

    /**
     * @brief append new vertex, it'll return false if it fails to add the vertex
     *
     * @param vertex
     * @return true or false
     */
    bool_t AppendVertex(Point2Type const& vertex) noexcept
    {
        bool_t flag = true;

        if (GetSize() == MAXIMUM_SIZE)
        {
            flag = false;
        }
        else
        {
            vertices_.at(size_) = vertex;
            size_++;

            if (size_ < 3u)
            {
                flag = true;
            }
            else if (!IsValid())
            {
                flag = false;
                size_--;
            }
        }
        return flag;
    }

    /**
     * @brief return size of convex polygon
     */
    inline uint8_t GetSize() const noexcept
    {
        return size_;
    }

    /**
     * @brief return corresponding vertex
     *
     * @param index vertex index
     * @return vertex
     */
    Point2Type const& GetVertex(uint8_t const index) const noexcept
    {
        assert(index < GetSize());
        return vertices_.at(index);
    }

    /**
     * @brief return corresponding edge as a line segment in 2D
     *
     * @note edge of index i connects vertices of index i and i + 1
     * @param index edge index
     * @return edge as line segment format
     */
    LineSegment2Type GetEdge(uint8_t const index) const noexcept
    {
        assert(index < GetSize());
        uint8_t const j = (index == GetSize() - 1u) ? (0u) : (index + 1u);
        return LineSegment2Type(vertices_.at(index), vertices_.at(j));
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
        size_t aligned_size = holo::serialization::SerializedSize<ALIGN>(size_);
        if (vertices_.size() > 0)
        {
            aligned_size += size_ * vertices_[0].template GetSerializedSize<ALIGN>();
        }
        return aligned_size;
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        /* serialize data */
        serializer << size_ << holo::serialization::align;
        for (uint8_t i = 0; i < size_; ++i)
        {
            serializer << vertices_[i];
        }
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
        deserializer >> size_ >> holo::serialization::align;
        for (uint8_t i = 0u; i < size_; ++i)
        {
            deserializer >> vertices_[i];
        }
    }

private:
    /**
     * @brief untility function to check convexity
     *
     * @param pt1 point1
     * @param pt2 point2
     * @param pt3 point3
     * @param pt4 point4
     * @param tol equal tolerance
     * @return -1 or 1
     */
    int32_t Convexity(Point2Type const& pt1, Point2Type const& pt2, Point2Type const& pt3, Point2Type const& pt4,
                      ScalarType const tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
    {
        // construct vector
        Point2Type v1 = pt2 - pt1;
        Point2Type v2 = pt4 - pt3;

        // cross product
        ScalarType val = v1[0u] * v2[1u] - v1[1u] * v2[0u];

        // outside or on edge
        if (std::fabs(val) <= tol)
        {
            return 0;
        }

        return (val > static_cast<ScalarType>(0.0) ? 1 : -1);
    }

    /**
     * @brief vertices buffer
     *
     */
    std::array<Point2Type, MAXIMUM_SIZE> vertices_;

    /**
     * @brief vertex size
     *
     */
    uint8_t size_;

};  // ConvexPolygon2T

/**
 * @}
 *
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_CONVEX_POLYGON2_H_
