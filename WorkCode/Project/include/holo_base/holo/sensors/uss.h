/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file app_status.h
 * @brief This header file defines AppStatus class
 * @author Zhangjiannan(zhangjiannan@holomatic.com)
 * @date 2020-08-27
 */

#ifndef HOLO_SENSORS_USS_H_
#define HOLO_SENSORS_USS_H_

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/container/details/fixed_size_vector.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/rot2.h>

namespace holo
{
namespace sensors
{
/**
 * @brief Object detected by USS
 */
class UssObject
{
public:
    using ScalarType = holo::float32_t;                      ///< Scalar type to describe the uss object.
    using PointType  = holo::geometry::Point2T<ScalarType>;  ///< Point type to describe the uss object.

    /**
     * @brief Type of detected dimension of the uss object.
     */
    enum class Type
    {
        INVALID,  ///< Invalid object.
        POINT,    ///< pt1 = pt2.
        LINE,     ///< The real dimension of the object could not be detected. The detected line section is pt1 to pt2.
        RAY,      ///< Only one object corner could be detected. Object demension is a ray from pt1 to pt2.
        SEGMENT,  ///< The real demension of the object could be detected. The detected line segment is pt1 to pt2.
    };

    /**
     * @brief Height of uss object.
     */
    enum class Height
    {
        UNKNOWN,  ///< Unknown height
        LOW,      ///< Height low
        HIGH,     ///< Height high
    };

    /**
     * @brief Set confidence of the object
     *
     * @param confidence confidence value. range from 0.0 to 1.0
     */
    void SetConfidence(holo::float32_t confidence) noexcept
    {
        confidence_ = confidence;
    }

    /**
     * @brief Set point1 value
     *
     * @param pt Point value
     */
    void SetPoint1(PointType const& pt) noexcept
    {
        pt1_ = pt;
    }

    /**
     * @brief Set point2 value
     *
     * @param pt Point value
     */
    void SetPoint2(PointType const& pt) noexcept
    {
        pt2_ = pt;
    }

    /**
     * @brief Set object dimension type
     *
     * @param type Type of dimension
     */
    void SetType(Type type) noexcept
    {
        type_ = type;
    }

    /**
     * @brief Set object height
     *
     * @param height Height of object.
     */
    void SetHeight(Height height) noexcept
    {
        height_ = height;
    }

    /**
     * @brief Get confidence value
     *
     * @return Confidence  value
     */
    holo::float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }

    /**
     * @brief Get point1 value
     *
     * @return Point1 value
     */
    PointType const& GetPoint1() const noexcept
    {
        return pt1_;
    }

    /**
     * @brief Get point1 value
     *
     * @return Point1 value
     */
    PointType& GetPoint1() noexcept
    {
        return pt1_;
    }

    /**
     * @brief Get point2 value
     *
     * @return Point2 value
     */
    PointType const& GetPoint2() const noexcept
    {
        return pt2_;
    }

    /**
     * @brief Get point2 value
     *
     * @return Point2 value
     */
    PointType& GetPoint2() noexcept
    {
        return pt2_;
    }

    /**
     * @brief Get dimension type
     *
     * @return Dimension type
     */
    Type GetType() const noexcept
    {
        return type_;
    }

    /**
     * @brief Get height type
     *
     * @return Height type
     */
    Height GetHeight() const noexcept
    {
        return height_;
    }

private:
    holo::float32_t confidence_;  ///< Existence confidence of the uss object.
    PointType       pt1_;         ///< First point to describe the object dimension.
    PointType       pt2_;         ///< Second point to describe the object dimension.
    Type            type_;        ///< Type of the object dimension.
    Height          height_;      ///< Height type of the object.
};

/**
 * @brief Uss objects frame.
 *
 * @tparam SIZE Max number of objects.
 */
template <size_t SIZE>
class UssObjects : public holo::container::details::FixedSizeVector<UssObject, SIZE>
{
public:
    using Base = holo::container::details::FixedSizeVector<UssObject, SIZE>;  ///< Base container class
    using Base::Base;                                                         ///< Inherit constructor

    /**
     * @brief Set timestamp of objects
     *
     * @param stamp Timestamp
     */
    void SetTimestamp(holo::common::Timestamp const& stamp) noexcept
    {
        stamp_ = stamp;
    }

    /**
     * @brief Set coordinate of objects
     *
     * @param coordinate Coordinate
     */
    void SetCoordiante(holo::common::Coordinate coordinate) noexcept
    {
        coordinate_ = coordinate;
    }

    /**
     * @brief Get timestamp of objects
     *
     * @return Timestamp
     */
    holo::common::Timestamp GetTimestamp() const noexcept
    {
        return stamp_;
    }

    /**
     * @brief Get coordinate of objects.
     *
     * @return Coordinate
     */
    holo::common::Coordinate GetCoordinate() const noexcept
    {
        return coordinate_;
    }

private:
    holo::common::Timestamp  stamp_{};       ///< Timestamp of objects
    holo::common::Coordinate coordinate_{};  ///< Coordinate of objects.
};

/**
 * @brief Parking slot detected by USS
 * @details USS parking slot are described by two rays.
 */
class UssParkingSlot
{
public:
    using ScalarType   = holo::float32_t;                      ///< Scalar type to describe parking slot.
    using PointType    = holo::geometry::Point2T<ScalarType>;  ///< Point type to describe parking slot.
    using RotationType = holo::geometry::Rot2T<ScalarType>;    ///< Rotation type to describe parking slot.

    /**
     * @brief Set start point of ray1
     *
     * @param value Point value
     */
    void SetPoint1(PointType const& value) noexcept
    {
        pt1_ = value;
    }

    /**
     * @brief Set rotation of ray1
     *
     * @param value Rotation value
     */
    void SetRotation1(RotationType const& value) noexcept
    {
        rot1_ = value;
    }

    /**
     * @brief Set start point of ray1
     *
     * @param value Point value
     */
    void SetPoint2(PointType const& value) noexcept
    {
        pt2_ = value;
    }

    /**
     * @brief Set rotation of ray2
     *
     * @param value Rotation value
     */
    void SetRotation2(RotationType const& value) noexcept
    {
        rot2_ = value;
    }

    /**
     * @brief Get start point of ray1
     *
     * @return Start point
     */
    PointType const& GetPoint1() const noexcept
    {
        return pt1_;
    }

    /**
     * @brief Get start point of ray1
     *
     * @return Start point
     */
    PointType& GetPoint1() noexcept
    {
        return pt1_;
    }

    /**
     * @brief Get rotation of ray1
     *
     * @return Rotation of ray1
     */
    RotationType const& GetRotation1() const noexcept
    {
        return rot1_;
    }

    /**
     * @brief Get rotation of ray1
     *
     * @return Rotation of ray1
     */
    RotationType& GetRotation1() noexcept
    {
        return rot1_;
    }

    /**
     * @brief Get start point of ray2
     *
     * @return Start point
     */
    PointType const& GetPoint2() const noexcept
    {
        return pt2_;
    }

    /**
     * @brief Get start point of ray2
     *
     * @return Start point
     */
    PointType& GetPoint2() noexcept
    {
        return pt2_;
    }

    /**
     * @brief Get rotation of ray2
     *
     * @return Rotation of ray2
     */
    RotationType const& GetRotation2() const noexcept
    {
        return rot2_;
    }

    /**
     * @brief Get rotation of ray2
     *
     * @return Rotation of ray2
     */
    RotationType& GetRotation2() noexcept
    {
        return rot2_;
    }

private:
    PointType    pt1_;   // Start point of ray1
    RotationType rot1_;  // Rotation of ray1
    PointType    pt2_;   // Start point of ray2
    RotationType rot2_;  // Rotation of ray2
};

/**
 * @brief Uss parking slots frame.
 *
 * @tparam SIZE Max number of slots.
 */
template <size_t SIZE>
class UssParkingSlots : public holo::container::details::FixedSizeVector<UssParkingSlot, SIZE>
{
public:
    using Base = holo::container::details::FixedSizeVector<UssParkingSlot, SIZE>;  ///< Base container class
    using Base::Base;                                                              ///< Inherit constructor

    /**
     * @brief Set timestamp of objects
     *
     * @param stamp Timestamp
     */
    void SetTimestamp(holo::common::Timestamp const& stamp) noexcept
    {
        stamp_ = stamp;
    }

    /**
     * @brief Set coordinate of objects
     *
     * @param coordinate Coordinate
     */
    void SetCoordiante(holo::common::Coordinate coordinate) noexcept
    {
        coordinate_ = coordinate;
    }

    /**
     * @brief Get timestamp of objects
     *
     * @return Timestamp
     */
    holo::common::Timestamp GetTimestamp() const noexcept
    {
        return stamp_;
    }

    /**
     * @brief Get coordinate of objects.
     *
     * @return Coordinate
     */
    holo::common::Coordinate GetCoordinate() const noexcept
    {
        return coordinate_;
    }

private:
    holo::common::Timestamp  stamp_{};       ///< Timestamp of objects
    holo::common::Coordinate coordinate_{};  ///< Coordinate of objects.
};

}  // namespace sensors
}  // namespace holo

#endif

