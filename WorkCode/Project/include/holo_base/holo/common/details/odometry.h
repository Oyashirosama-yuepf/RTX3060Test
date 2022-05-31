/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file odometry.h
 * @brief This header file define generic odometry measurement
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @author Zhou Huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-10-11
 */

#ifndef HOLO_COMMON_DETAILS_ODOMETRY_H_
#define HOLO_COMMON_DETAILS_ODOMETRY_H_

#include <cassert>

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/geometry/pose3.h>
#include <holo/geometry/quaternion.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace common
{
namespace details
{
class OdometryPrecision
{
public:
    enum class Precision : uint32_t
    {
        UNKNOWN = 0U,
        LOW     = 1U,
        MEDIUM  = 2U,
        HIGH    = 3U,
    };

    enum class Field : uint32_t
    {
        POSITION_X            = 0U,
        POSITION_Y            = 1U,
        POSITION_Z            = 2U,
        ROTATION_X            = 3U,
        ROTATION_Y            = 4U,
        ROTATION_Z            = 5U,
        LINEAR_VELOCITY_X     = 6U,
        LINEAR_VELOCITY_Y     = 7U,
        LINEAR_VELOCITY_Z     = 8U,
        ANGULAR_VELOCITY_X    = 9U,
        ANGULAR_VELOCITY_Y    = 10U,
        ANGULAR_VELOCITY_Z    = 11U,
        LINEAR_ACCELERATION_X = 12U,
        LINEAR_ACCELERATION_Y = 13U,
        LINEAR_ACCELERATION_Z = 14U,
    };

    OdometryPrecision() noexcept : precision_{0}
    {
    }

    OdometryPrecision(uint32_t value) noexcept : precision_{value}
    {
    }

    explicit operator uint32_t() const noexcept
    {
        return precision_;
    }

    OdometryPrecision& operator=(uint32_t const value) noexcept
    {
        precision_ = value;
        return *this;
    }

    bool operator==(OdometryPrecision const other) const noexcept
    {
        return precision_ == other.precision_;
    }

    bool operator!=(OdometryPrecision const other) const noexcept
    {
        return precision_ != other.precision_;
    }

    void SetPrecision(Field const field, Precision const value) noexcept
    {
        precision_ &= ~generatePrecisionMask(field);
        precision_ |= static_cast<uint32_t>(value) << (static_cast<uint32_t>(field) * 2U);
    }

    template <typename... Args>
    void SetHighPrecision(Args&&... args) noexcept
    {
        precision_ |= generateHighPrecisionMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void SetMediumPrecision(Args&&... args) noexcept
    {
        precision_ &= ~generatePrecisionMask(std::forward<Args>(args)...);
        precision_ |= generateMediumPrecisionMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void SetLowPrecision(Args&&... args) noexcept
    {
        precision_ &= ~generatePrecisionMask(std::forward<Args>(args)...);
        precision_ |= generateLowPrecisionMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void SetUnknownPrecision(Args&&... args) noexcept
    {
        precision_ &= ~generatePrecisionMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    holo::bool_t IsHighPrecision(Args&&... args) const noexcept
    {
        return static_cast<holo::bool_t>((precision_ & generateHighPrecisionMask(std::forward<Args>(args)...)) ==
                                         generateHighPrecisionMask(std::forward<Args>(args)...));
    }

    template <typename... Args>
    holo::bool_t IsMediumPrecision(Args&&... args) const noexcept
    {
        return static_cast<holo::bool_t>((precision_ & generatePrecisionMask(std::forward<Args>(args)...)) ==
                                         generateMediumPrecisionMask(std::forward<Args>(args)...));
    }

    template <typename... Args>
    holo::bool_t IsLowPrecision(Args&&... args) const noexcept
    {
        return static_cast<holo::bool_t>((precision_ & generatePrecisionMask(std::forward<Args>(args)...)) ==
                                         generateLowPrecisionMask(std::forward<Args>(args)...));
    }

    template <typename... Args>
    holo::bool_t IsUnknownPrecision(Args&&... args) const noexcept
    {
        return static_cast<holo::bool_t>((precision_ & generatePrecisionMask(std::forward<Args>(args)...)) == 0U);
    }

    void SetPosePrecision(Precision const value) noexcept
    {
        value == Precision::HIGH ?
            SetHighPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z, Field::ROTATION_X,
                             Field::ROTATION_Y, Field::ROTATION_Z) :
            value == Precision::MEDIUM ?
            SetMediumPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z, Field::ROTATION_X,
                               Field::ROTATION_Y, Field::ROTATION_Z) :
            value == Precision::LOW ? SetLowPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z,
                                                      Field::ROTATION_X, Field::ROTATION_Y, Field::ROTATION_Z) :
                                      SetUnknownPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z,
                                                          Field::ROTATION_X, Field::ROTATION_Y, Field::ROTATION_Z);
    }

    void SetPositionPrecision(Precision const value) noexcept
    {
        value == Precision::HIGH ?
            SetHighPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z) :
            value == Precision::MEDIUM ?
            SetMediumPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z) :
            value == Precision::LOW ? SetLowPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z) :
                                      SetUnknownPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z);
    }

    void SetRotationPrecision(Precision const value) noexcept
    {
        value == Precision::HIGH ?
            SetHighPrecision(Field::ROTATION_X, Field::ROTATION_Y, Field::ROTATION_Z) :
            value == Precision::MEDIUM ?
            SetMediumPrecision(Field::ROTATION_X, Field::ROTATION_Y, Field::ROTATION_Z) :
            value == Precision::LOW ? SetLowPrecision(Field::ROTATION_X, Field::ROTATION_Y, Field::ROTATION_Z) :
                                      SetUnknownPrecision(Field::ROTATION_X, Field::ROTATION_Y, Field::ROTATION_Z);
    }

    void SetVelocityPrecision(Precision const value) noexcept
    {
        value == Precision::HIGH ?
            SetHighPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z,
                             Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z) :
            value == Precision::MEDIUM ?
            SetMediumPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z,
                               Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z) :
            value == Precision::LOW ?
            SetLowPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z,
                            Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z) :
            SetUnknownPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z,
                                Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z);
    }

    void SetLinearVelocityPrecision(Precision const value) noexcept
    {
        value == Precision::HIGH ?
            SetHighPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z) :
            value == Precision::MEDIUM ?
            SetMediumPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z) :
            value == Precision::LOW ?
            SetLowPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z) :
            SetUnknownPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z);
    }

    void SetAngularVelocityPrecision(Precision const value) noexcept
    {
        value == Precision::HIGH ?
            SetHighPrecision(Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z) :
            value == Precision::MEDIUM ?
            SetMediumPrecision(Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z) :
            value == Precision::LOW ?
            SetLowPrecision(Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z) :
            SetUnknownPrecision(Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z);
    }

    void SetLinearAccelerationPrecision(Precision const value) noexcept
    {
        value == Precision::HIGH ?
            SetHighPrecision(Field::LINEAR_ACCELERATION_X, Field::LINEAR_ACCELERATION_Y, Field::LINEAR_ACCELERATION_Z) :
            value == Precision::MEDIUM ?
            SetMediumPrecision(Field::LINEAR_ACCELERATION_X, Field::LINEAR_ACCELERATION_Y,
                               Field::LINEAR_ACCELERATION_Z) :
            value == Precision::LOW ?
            SetLowPrecision(Field::LINEAR_ACCELERATION_X, Field::LINEAR_ACCELERATION_Y, Field::LINEAR_ACCELERATION_Z) :
            SetUnknownPrecision(Field::LINEAR_ACCELERATION_X, Field::LINEAR_ACCELERATION_Y,
                                Field::LINEAR_ACCELERATION_Z);
    }

    Precision GetPrecision(Field const field) const noexcept
    {
        return static_cast<Precision>((precision_ >> (static_cast<uint32_t>(field) * 2U)) & 0x03U);
    }

    holo::bool_t IsPoseHighPrecision() const noexcept
    {
        return IsHighPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z, Field::ROTATION_X,
                               Field::ROTATION_Y, Field::ROTATION_Z);
    }

    holo::bool_t IsPoseMediumPrecision() const noexcept
    {
        return IsMediumPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z, Field::ROTATION_X,
                                 Field::ROTATION_Y, Field::ROTATION_Z);
    }

    holo::bool_t IsPoseLowPrecision() const noexcept
    {
        return IsLowPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z, Field::ROTATION_X,
                              Field::ROTATION_Y, Field::ROTATION_Z);
    }

    holo::bool_t IsPoseUnknownPrecision() const noexcept
    {
        return IsUnknownPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z, Field::ROTATION_X,
                                  Field::ROTATION_Y, Field::ROTATION_Z);
    }

    holo::bool_t IsPositionHighPrecision() const noexcept
    {
        return IsHighPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z);
    }

    holo::bool_t IsPositionMediumPrecision() const noexcept
    {
        return IsMediumPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z);
    }

    holo::bool_t IsPositionLowPrecision() const noexcept
    {
        return IsLowPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z);
    }

    holo::bool_t IsPositionUnknownPrecision() const noexcept
    {
        return IsUnknownPrecision(Field::POSITION_X, Field::POSITION_Y, Field::POSITION_Z);
    }

    holo::bool_t IsRotationHighPrecision() const noexcept
    {
        return IsHighPrecision(Field::ROTATION_X, Field::ROTATION_Y, Field::ROTATION_Z);
    }

    holo::bool_t IsRotationMediumPrecision() const noexcept
    {
        return IsMediumPrecision(Field::ROTATION_X, Field::ROTATION_Y, Field::ROTATION_Z);
    }

    holo::bool_t IsRotationLowPrecision() const noexcept
    {
        return IsLowPrecision(Field::ROTATION_X, Field::ROTATION_Y, Field::ROTATION_Z);
    }

    holo::bool_t IsRotationUnknownPrecision() const noexcept
    {
        return IsUnknownPrecision(Field::ROTATION_X, Field::ROTATION_Y, Field::ROTATION_Z);
    }

    holo::bool_t IsVelocityHighPrecision() const noexcept
    {
        return IsHighPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z,
                               Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z);
    }

    holo::bool_t IsVelocityMediumPrecision() const noexcept
    {
        return IsMediumPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z,
                                 Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z);
    }

    holo::bool_t IsVelocityLowPrecision() const noexcept
    {
        return IsLowPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z,
                              Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z);
    }

    holo::bool_t IsVelocityUnknownPrecision() const noexcept
    {
        return IsUnknownPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z,
                                  Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z);
    }

    holo::bool_t IsLinearVelocityHighPrecision() const noexcept
    {
        return IsHighPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z);
    }

    holo::bool_t IsLinearVelocityMediumPrecision() const noexcept
    {
        return IsMediumPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z);
    }

    holo::bool_t IsLinearVelocityLowPrecision() const noexcept
    {
        return IsLowPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z);
    }

    holo::bool_t IsLinearVelocityUnknownPrecision() const noexcept
    {
        return IsUnknownPrecision(Field::LINEAR_VELOCITY_X, Field::LINEAR_VELOCITY_Y, Field::LINEAR_VELOCITY_Z);
    }

    holo::bool_t IsAngularVelocityHighPrecision() const noexcept
    {
        return IsHighPrecision(Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z);
    }

    holo::bool_t IsAngularVelocityMediumPrecision() const noexcept
    {
        return IsMediumPrecision(Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z);
    }

    holo::bool_t IsAngularVelocityLowPrecision() const noexcept
    {
        return IsLowPrecision(Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z);
    }

    holo::bool_t IsAngularVelocityUnknownPrecision() const noexcept
    {
        return IsUnknownPrecision(Field::ANGULAR_VELOCITY_X, Field::ANGULAR_VELOCITY_Y, Field::ANGULAR_VELOCITY_Z);
    }

    holo::bool_t IsLinearAccelerationHighPrecision() const noexcept
    {
        return IsHighPrecision(Field::LINEAR_ACCELERATION_X, Field::LINEAR_ACCELERATION_Y,
                               Field::LINEAR_ACCELERATION_Z);
    }

    holo::bool_t IsLinearAccelerationMediumPrecision() const noexcept
    {
        return IsMediumPrecision(Field::LINEAR_ACCELERATION_X, Field::LINEAR_ACCELERATION_Y,
                                 Field::LINEAR_ACCELERATION_Z);
    }

    holo::bool_t IsLinearAccelerationLowPrecision() const noexcept
    {
        return IsLowPrecision(Field::LINEAR_ACCELERATION_X, Field::LINEAR_ACCELERATION_Y, Field::LINEAR_ACCELERATION_Z);
    }

    holo::bool_t IsLinearAccelerationUnknownPrecision() const noexcept
    {
        return IsUnknownPrecision(Field::LINEAR_ACCELERATION_X, Field::LINEAR_ACCELERATION_Y,
                                  Field::LINEAR_ACCELERATION_Z);
    }

private:
    uint32_t precision_;

private:
    template <typename... Args>
    uint32_t generatePrecisionMask(Field field, Args&&... args) const noexcept
    {
        return (static_cast<uint32_t>(0x03U) << (static_cast<uint32_t>(field) * 2U)) | generatePrecisionMask(std::forward<Args>(args)...);
    }

    uint32_t generatePrecisionMask(Field field) const noexcept
    {
        return static_cast<uint32_t>(0x03U) << (static_cast<uint32_t>(field) * 2U);
    }

    template <typename... Args>
    uint32_t generateHighPrecisionMask(Args&&... args) const noexcept
    {
        return generatePrecisionMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    uint32_t generateMediumPrecisionMask(Field field, Args&&... args) const noexcept
    {
        return (static_cast<uint32_t>(0x02U) << (static_cast<uint32_t>(field) * 2U)) |
               generateMediumPrecisionMask(std::forward<Args>(args)...);
    }

    uint32_t generateMediumPrecisionMask(Field field) const noexcept
    {
        return static_cast<uint32_t>(0x02U) << (static_cast<uint32_t>(field) * 2U);
    }

    template <typename... Args>
    uint32_t generateLowPrecisionMask(Field field, Args&&... args) const noexcept
    {
        return (static_cast<uint32_t>(0x01U) << (static_cast<uint32_t>(field) * 2U)) | generateLowPrecisionMask(std::forward<Args>(args)...);
    }

    uint32_t generateLowPrecisionMask(Field field) const noexcept
    {
        return static_cast<uint32_t>(0x01U) << (static_cast<uint32_t>(field) * 2U);
    }
};

/**
 * @brief This class defines odometry measurement base in 3D space. It contains 3D pose, 3D linear velocity, 3D angular
 * velocity, 3D linear acceleration and corresponding uncertainties.
 *
 * @tparam Scalar the precision type
 */
template <typename Scalar>
class OdometryBaseT
{
public:
    using Vector3Type               = holo::numerics::VectorT<Scalar, 3u>;
    using Vector6Type               = holo::numerics::VectorT<Scalar, 6u>;
    using Matrix6Type               = holo::numerics::MatrixT<Scalar, 6u, 6u>;
    using Pose3Type                 = holo::geometry::Pose3T<Scalar>;
    using CoordinateType            = holo::common::Coordinate;
    using TimestampType             = holo::common::Timestamp;
    using Coordinate [[deprecated]] = holo::common::Coordinate;
    using Timestamp [[deprecated]]  = holo::common::Timestamp;
    using Precision [[deprecated]]  = OdometryPrecision::Precision;
    using Field [[deprecated]]      = OdometryPrecision::Field;
    using PrecisionValueType        = OdometryPrecision::Precision;
    using PrecisionFieldType        = OdometryPrecision::Field;
    /**
     * @brief Define odometry status types
     *
     */
    enum class Status : uint16_t
    {
        ALLGOOD                    = 0x0000,  ///< solution is good
        SOLUTIONNOGOOD             = 0x0001,  ///< solution is bad
        POSITIONINACTIVE           = 0x0002,  ///< position field of solution is inactive
        ORIENTATIONINACTIVE        = 0x0004,  ///< orientation field of solution is inactive
        LINEARVELOCITYINACTIVE     = 0x0008,  ///< linear velocity field of solution is inactive
        ANGULARVELOCITYINACTIVE    = 0x0010,  ///< angular velocity field of solution is inactive
        LINEARACCELERATIONINACTIVE = 0x0020,  ///< linear acceleration field of solution is inactive
        UNKNOWN                    = 0xFFFF,  ///< undefined status */
    };

    /**
     * @brief Define odometry source types
     *
     */
    enum class Source : uint16_t
    {
        NONE          = 0x0000,  ///< none source
        GNSS          = 0x0001,  ///< from Global Navigation Staellite System (GNSS)
        IMU           = 0x0002,  ///< from Inertial Measurement Unit (IMU)
        VISION        = 0x0004,  ///< from camera
        WHEEL         = 0x0008,  ///< from vehicle wheel speed sensor
        RADAR         = 0x0010,  ///< from Radar
        LIDAR         = 0x0020,  ///< from LiDAR
        SEMANTIC      = 0x0040,  ///< from semantic measurement which provided by Machine Learning
        HD_MAP        = 0x0080,  ///< from High Definition Map (HD Map)
        RTK           = 0x0100,  ///< from RTK Base Station
        DETECTED_LANE = 0x0200,  ///< from detected lanes which provided by Smart Camera
        UNKNOWN       = 0xFFFF,  ///< from undefined source
    };

    /**
     * @brief Check odometry measurement quality
     *
     * @return If solution is good, return true, otherwise return false
     */
    bool_t IsSolutionGood() const noexcept
    {
        static uint16_t bad_solution_mask =
            static_cast<uint16_t>(Status::SOLUTIONNOGOOD) | static_cast<uint16_t>(Status::POSITIONINACTIVE) |
            static_cast<uint16_t>(Status::ORIENTATIONINACTIVE) | static_cast<uint16_t>(Status::LINEARVELOCITYINACTIVE) |
            static_cast<uint16_t>(Status::ANGULARVELOCITYINACTIVE);
        return !(static_cast<uint16_t>(status_) & bad_solution_mask);
    }

    /**
     * @brief Get odometry timestamp
     *
     * @return Reference of odometry timestamp
     */
    TimestampType GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set odometry timestamp
     *
     * @param timestamp Odometry timestamp
     */
    void SetTimestamp(TimestampType const timestamp) noexcept
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Get parent coordinate
     *
     * @return Parent coordinate
     */
    CoordinateType GetCoordinate() const noexcept
    {
        return parent_coordinate_;
    }

    /**
     * @brief Set parent coordinate
     *
     * @param parent_coordinate Coordinate
     */
    void SetCoordinate(CoordinateType const parent_coordinate) noexcept
    {
        parent_coordinate_ = parent_coordinate;
    }

    /**
     * @brief Get parent coordinate
     *
     * @return Parent coordinate
     */
    CoordinateType GetParentCoordinate() const noexcept
    {
        return parent_coordinate_;
    }

    /**
     * @brief Set parent coordinate
     *
     * @param parent_coordinate Coordinate
     */
    void SetParentCoordinate(CoordinateType const parent_coordinate) noexcept
    {
        parent_coordinate_ = parent_coordinate;
    }

    /**
     * @brief Get child coordinate
     *
     * @return Const reference of child coordinate
     */
    CoordinateType GetChildCoordinate() const noexcept
    {
        return child_coordinate_;
    }

    /**
     * @brief Set child coordinate
     *
     * @param child_coordinate Coordinate
     */
    void SetChildCoordinate(CoordinateType const child_coordinate) noexcept
    {
        child_coordinate_ = child_coordinate;
    }

    /**
     * @brief Return odometry status
     *
     * @return Odometry status
     */
    Status GetStatus() const noexcept
    {
        return status_;
    }

    /**
     * @brief Set odometry status
     *
     * @param status Odometry status
     */
    void SetStatus(Status const status) noexcept
    {
        status_ = status;
    }

    /**
     * @brief Return odometry source
     *
     * @return Odometry source
     */
    Source GetSource() const noexcept
    {
        return source_;
    }

    /**
     * @brief Set odometry source
     *
     * @param source Odometry source
     */
    void SetSource(Source const source) noexcept
    {
        source_ = source;
    }

    /**
     * @brief Get 3D pose which contains 3D rotation and 3D translation
     *
     * @return Reference of 3D pose
     */
    Pose3Type& GetPose() noexcept
    {
        return pose_;
    }

    /**
     * @brief Get 3D pose which contains 3D rotation and 3D translation
     *
     * @return Const reference of 3D pose
     */
    Pose3Type const& GetPose() const noexcept
    {
        return pose_;
    }

    /**
     * @brief Set 3D pose which contains 3D rotation and 3D translation
     *
     * @param pose 3D pose
     */
    void SetPose(Pose3Type const& pose) noexcept
    {
        pose_ = pose;
    }

    /**
     * @brief Set 3D pose which contains 3D rotation and 3D translation
     *
     * @param pose 3D pose
     */
    void SetPose(Pose3Type&& pose) noexcept
    {
        pose_ = std::move(pose);
    }

    /**
     * @brief Get velocity which contains 3D linear velocity and 3D angular velocity
     *
     * @return Reference of 6D vector which contains (Vx, Vy, Vz, Vroll, Vpitch, Vyaw) in the unit of (m/s, m/s, m/s,
     * rad/s, rad/s, rad/s)
     */
    Vector6Type& GetVelocity() noexcept
    {
        return velocity_;
    }

    /**
     * @brief Get velocity which contains 3D linear velocity and 3D angular velocity
     *
     * @return Const reference of 6D vector which contains (Vx, Vy, Vz, Vroll, Vpitch, Vyaw) in the unit of (m/s, m/s,
     * m/s, rad/s, rad/s, rad/s)
     */
    Vector6Type const& GetVelocity() const noexcept
    {
        return velocity_;
    }

    /**
     * @brief Set velocity which contains 3D linear velocity and 3D angular velocity
     *
     * @param velocity 6D vector which contains (Vx, Vy, Vz, Vroll, Vpitch, Vyaw) in the unit of (m/s, m/s, m/s, rad/s,
     * rad/s, rad/s)
     */
    void SetVelocity(Vector6Type const& velocity) noexcept
    {
        velocity_ = velocity;
    }

    /**
     * @brief Set velocity which contains 3D linear velocity and 3D angular velocity
     *
     * @param velocity 6D vector which contains (Vx, Vy, Vz, Vroll, Vpitch, Vyaw) in the unit of (m/s, m/s, m/s, rad/s,
     * rad/s, rad/s)
     */
    void SetVelocity(Vector6Type&& velocity) noexcept
    {
        velocity_ = std::move(velocity);
    }

    /**
     * @brief Get pose covariance
     *
     * @return Reference of pose covariance matrix
     */
    Matrix6Type& GetPoseCovariance() noexcept
    {
        return pose_covariance_;
    }

    /**
     * @brief Get pose covariance
     *
     * @return Const reference of pose covariance matrix
     */
    Matrix6Type const& GetPoseCovariance() const noexcept
    {
        return pose_covariance_;
    }

    /**
     * @brief Set pose covariance
     *
     * @param pose_covariance Pose covariance
     */
    void SetPoseCovariance(Matrix6Type const& pose_covariance) noexcept
    {
        pose_covariance_ = pose_covariance;
    }

    /**
     * @brief Set pose covariance
     *
     * @param pose_covariance Pose covariance
     */
    void SetPoseCovariance(Matrix6Type&& pose_covariance) noexcept
    {
        pose_covariance_ = std::move(pose_covariance);
    }

    /**
     * @brief Get velocity covariance
     *
     * @return Reference of velocity covariance
     */
    Matrix6Type& GetVelocityCovariance() noexcept
    {
        return velocity_covariance_;
    }

    /**
     * @brief Get velocity covariance
     *
     * @return Const reference of velocity covariance
     */
    Matrix6Type const& GetVelocityCovariance() const noexcept
    {
        return velocity_covariance_;
    }

    /**
     * @brief Set velocity covariance
     *
     * @param velocity_covariance Velocity covariance
     */
    void SetVelocityCovariance(Matrix6Type const& velocity_covariance) noexcept
    {
        velocity_covariance_ = velocity_covariance;
    }

    /**
     * @brief Set velocity covariance
     *
     * @param velocity_covariance Velocity covariance
     */
    void SetVelocityCovariance(Matrix6Type&& velocity_covariance) noexcept
    {
        velocity_covariance_ = std::move(velocity_covariance);
    }

    /**
     * @brief Get linear acceleration which in the order of acc_x, acc_y, acc_z
     *
     * @return Reference of linear acceleration in the unit of m/s^2
     */
    Vector3Type& GetLinearAcceleration() noexcept
    {
        return linear_acceleration_;
    }

    /**
     * @brief Get linear acceleration which in the order of acc_x, acc_y, acc_z
     *
     * @return Const reference of linear acceleration in the unit of m/s^2
     */
    Vector3Type const& GetLinearAcceleration() const noexcept
    {
        return linear_acceleration_;
    }

    /**
     * @brief Set linear acceleration which in the order of acc_x, acc_y, acc_z
     *
     * @param linear_acceleration Linear acceleration in the unit of m/s^2
     */
    void SetLinearAcceleration(Vector3Type const& linear_acceleration) noexcept
    {
        linear_acceleration_ = linear_acceleration;
    }

    /**
     * @brief Set linear acceleration which in the order of acc_x, acc_y, acc_z
     *
     * @param linear_acceleration Linear acceleration in the unit of m/s^2
     */
    void SetLinearAcceleration(Vector3Type&& linear_acceleration) noexcept
    {
        linear_acceleration_ = std::move(linear_acceleration);
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(
                   static_cast<uint32_t>(parent_coordinate_), static_cast<uint32_t>(child_coordinate_),
                   static_cast<uint16_t>(status_), static_cast<uint16_t>(source_), static_cast<uint32_t>(precision_)) +
               pose_.template GetSerializedSize<ALIGN>() + velocity_.template GetSerializedSize<ALIGN>() +
               linear_acceleration_.template GetSerializedSize<ALIGN>() +
               pose_covariance_.template GetSerializedSize<ALIGN>() +
               velocity_covariance_.template GetSerializedSize<ALIGN>();
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
        serializer << timestamp_ << parent_coordinate_ << child_coordinate_ << static_cast<uint16_t>(status_)
                   << static_cast<uint16_t>(source_) << static_cast<uint32_t>(precision_) << pose_ << velocity_
                   << linear_acceleration_ << pose_covariance_ << velocity_covariance_;
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
        uint16_t status, source, precision;
        deserializer >> timestamp_ >> parent_coordinate_ >> child_coordinate_ >> status >> source >> precision >>
            pose_ >> velocity_ >> linear_acceleration_ >> pose_covariance_ >> velocity_covariance_;
        precision_ = precision;
        status_    = static_cast<Status>(status);
        source_    = static_cast<Source>(source);
    }

    uint32_t GetPrecisionFlags() const noexcept
    {
        return static_cast<uint32_t>(precision_);
    }

    void SetPrecisionFlags(uint32_t const value) noexcept
    {
        precision_ = value;
    }

    void SetPrecision(PrecisionFieldType const field, PrecisionValueType const value) noexcept
    {
        precision_.SetPrecision(field, value);
    }

    template <typename... Args>
    void SetHighPrecision(Args&&... args) noexcept
    {
        precision_.SetHighPrecision(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void SetMediumPrecision(Args&&... args) noexcept
    {
        precision_.SetMediumPrecision(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void SetLowPrecision(Args&&... args) noexcept
    {
        precision_.SetLowPrecision(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void SetUnknownPrecision(Args&&... args) noexcept
    {
        precision_.SetUnknownPrecision(std::forward<Args>(args)...);
    }

    template <typename... Args>
    holo::bool_t IsHighPrecision(Args&&... args) const noexcept
    {
        return precision_.IsHighPrecision(std::forward<Args>(args)...);
    }

    template <typename... Args>
    holo::bool_t IsMediumPrecision(Args&&... args) const noexcept
    {
        return precision_.IsMediumPrecision(std::forward<Args>(args)...);
    }

    template <typename... Args>
    holo::bool_t IsLowPrecision(Args&&... args) const noexcept
    {
        return precision_.IsLowPrecision(std::forward<Args>(args)...);
    }

    template <typename... Args>
    holo::bool_t IsUnknownPrecision(Args&&... args) const noexcept
    {
        return precision_.IsUnknownPrecision(std::forward<Args>(args)...);
    }

    void SetPosePrecision(PrecisionValueType const value) noexcept
    {
        precision_.SetPosePrecision(value);
    }

    void SetPositionPrecision(PrecisionValueType const value) noexcept
    {
        precision_.SetPositionPrecision(value);
    }

    void SetRotationPrecision(PrecisionValueType const value) noexcept
    {
        precision_.SetRotationPrecision(value);
    }

    void SetVelocityPrecision(PrecisionValueType const value) noexcept
    {
        precision_.SetVelocityPrecision(value);
    }

    void SetLinearVelocityPrecision(PrecisionValueType const value) noexcept
    {
        precision_.SetLinearVelocityPrecision(value);
    }

    void SetAngularVelocityPrecision(PrecisionValueType const value) noexcept
    {
        precision_.SetAngularVelocityPrecision(value);
    }

    void SetLinearAccelerationPrecision(PrecisionValueType const value) noexcept
    {
        precision_.SetLinearAccelerationPrecision(value);
    }

    PrecisionValueType GetPrecision(PrecisionFieldType const field) const noexcept
    {
        return precision_.GetPrecision(field);
    }

    holo::bool_t IsPoseHighPrecision() const noexcept
    {
        return precision_.IsPoseHighPrecision();
    }

    holo::bool_t IsPoseMediumPrecision() const noexcept
    {
        return precision_.IsPoseMediumPrecision();
    }

    holo::bool_t IsPoseLowPrecision() const noexcept
    {
        return precision_.IsPoseLowPrecision();
    }

    holo::bool_t IsPoseUnknownPrecision() const noexcept
    {
        return precision_.IsPoseUnknownPrecision();
    }

    holo::bool_t IsPositionHighPrecision() const noexcept
    {
        return precision_.IsPositionHighPrecision();
    }

    holo::bool_t IsPositionMediumPrecision() const noexcept
    {
        return precision_.IsPositionMediumPrecision();
    }

    holo::bool_t IsPositionLowPrecision() const noexcept
    {
        return precision_.IsPositionLowPrecision();
    }

    holo::bool_t IsPositionUnknownPrecision() const noexcept
    {
        return precision_.IsPositionUnknownPrecision();
    }

    holo::bool_t IsRotationHighPrecision() const noexcept
    {
        return precision_.IsRotationHighPrecision();
    }

    holo::bool_t IsRotationMediumPrecision() const noexcept
    {
        return precision_.IsRotationMediumPrecision();
    }

    holo::bool_t IsRotationLowPrecision() const noexcept
    {
        return precision_.IsRotationLowPrecision();
    }

    holo::bool_t IsRotationUnknownPrecision() const noexcept
    {
        return precision_.IsRotationUnknownPrecision();
    }

    holo::bool_t IsVelocityHighPrecision() const noexcept
    {
        return precision_.IsVelocityHighPrecision();
    }

    holo::bool_t IsVelocityMediumPrecision() const noexcept
    {
        return precision_.IsVelocityMediumPrecision();
    }

    holo::bool_t IsVelocityLowPrecision() const noexcept
    {
        return precision_.IsVelocityLowPrecision();
    }

    holo::bool_t IsVelocityUnknownPrecision() const noexcept
    {
        return precision_.IsVelocityUnknownPrecision();
    }

    holo::bool_t IsLinearVelocityHighPrecision() const noexcept
    {
        return precision_.IsLinearVelocityHighPrecision();
    }

    holo::bool_t IsLinearVelocityMediumPrecision() const noexcept
    {
        return precision_.IsLinearVelocityMediumPrecision();
    }

    holo::bool_t IsLinearVelocityLowPrecision() const noexcept
    {
        return precision_.IsLinearVelocityLowPrecision();
    }

    holo::bool_t IsLinearVelocityUnknownPrecision() const noexcept
    {
        return precision_.IsLinearVelocityUnknownPrecision();
    }

    holo::bool_t IsAngularVelocityHighPrecision() const noexcept
    {
        return precision_.IsAngularVelocityHighPrecision();
    }

    holo::bool_t IsAngularVelocityMediumPrecision() const noexcept
    {
        return precision_.IsAngularVelocityMediumPrecision();
    }

    holo::bool_t IsAngularVelocityLowPrecision() const noexcept
    {
        return precision_.IsAngularVelocityLowPrecision();
    }

    holo::bool_t IsAngularVelocityUnknownPrecision() const noexcept
    {
        return precision_.IsAngularVelocityUnknownPrecision();
    }

    holo::bool_t IsLinearAccelerationHighPrecision() const noexcept
    {
        return precision_.IsLinearAccelerationHighPrecision();
    }

    holo::bool_t IsLinearAccelerationMediumPrecision() const noexcept
    {
        return precision_.IsLinearAccelerationMediumPrecision();
    }

    holo::bool_t IsLinearAccelerationLowPrecision() const noexcept
    {
        return precision_.IsLinearAccelerationLowPrecision();
    }

    holo::bool_t IsLinearAccelerationUnknownPrecision() const noexcept
    {
        return precision_.IsLinearAccelerationUnknownPrecision();
    }

protected:
    /**
     * @brief Default constructor
     */
    OdometryBaseT()
      : timestamp_{}
      , parent_coordinate_{}
      , child_coordinate_{}
      , status_{Status::ALLGOOD}
      , source_{Source::NONE}
      , precision_{0U}
      , pose_{Pose3::Identity()}
      , velocity_{}
      , linear_acceleration_{}
      , pose_covariance_{Matrix6Type::Identity()}
      , velocity_covariance_{Matrix6Type::Identity()}
    {
    }

    /**
     * @brief Copy constructor
     *
     * @param other other odometry
     */
    OdometryBaseT(OdometryBaseT const&) = default;

    /**
     * @brief Move constructor
     *
     * @param other other odometry
     */
    OdometryBaseT(OdometryBaseT&&) = default;

    /**
     * @brief Copy assignment
     *
     * @param other odometry to assign
     * @return new odometry
     */
    OdometryBaseT& operator=(OdometryBaseT const&) = default;

    /**
     * @brief Move assignment
     *
     * @param other other odometry
     * @return new odometry
     */
    OdometryBaseT& operator=(OdometryBaseT&&) = default;

    /**
     * @brief destructor
     */
    ~OdometryBaseT() noexcept = default;

private:
    TimestampType     timestamp_;          ///< timestamp
    CoordinateType    parent_coordinate_;  ///< parent coordinate
    CoordinateType    child_coordinate_;   ///< child coordinate
    Status            status_;             ///< odometry status
    Source            source_;             ///< odometry source
    OdometryPrecision precision_;          ///< Precision
    Pose3Type         pose_;               ///< 3D pose including position in meters and rotation in radians
    Vector6Type       velocity_;  ///< 3D velocity including linear velocity in meter/s and angular velocity in radian/s
    Vector3Type       linear_acceleration_;  ///< 3D linear acceleration in meter/s^2
    Matrix6Type       pose_covariance_;      ///< position covariance in meter^2 and rotation covariance in radian^2
    Matrix6Type velocity_covariance_;  /// linear velocity covariance in (meter/s)^2 and angular velocity covariance in
                                       /// (radian/s)^2
};

/**
 * @brief This class defines odometry measurement in 3D space. It contains 3D pose, 3D linear velocity, 3D angular
 * velocity, 3D linear acceleration, corresponding uncertainties,
 *
 * @tparam Scalar the precision type
 */
template <typename Scalar>
class OdometryT : public OdometryBaseT<Scalar>
{
public:
    using Base           = OdometryBaseT<Scalar>;
    using Vector3Type    = typename Base::Vector3Type;
    using Vector6Type    = typename Base::Vector6Type;
    using Matrix6Type    = typename Base::Matrix6Type;
    using Pose3Type      = typename Base::Pose3Type;
    using CoordinateType = typename Base::CoordinateType;
    using TimestampType  = typename Base::TimestampType;
    using Status         = typename Base::Status;
    using Source         = typename Base::Source;

    using Precision [[deprecated]] = typename Base::Precision;
    using Field [[deprecated]]     = typename Base::Field;
    using PrecisionValueType       = typename Base::Precision;
    using PrecisionFieldType       = typename Base::Field;
};

/**
 * @brief This class defines local map odometry measurement in 3D space. It contains point, rotation, status, speed,
 * heading, actived, matching_results in addition to the odometry base attribute
 *
 * @tparam Scalar the precision type
 */
template <typename Scalar, size_t SIZE_VALUE>
class LocalMapOdometryT : public OdometryBaseT<Scalar>
{
public:
    using Base           = OdometryBaseT<Scalar>;
    using QuaternionType = holo::geometry::QuaternionT<Scalar>;
    using Point3Type     = holo::geometry::Point3T<Scalar>;

    using Vector3Type    = typename Base::Vector3Type;
    using Vector6Type    = typename Base::Vector6Type;
    using Matrix6Type    = typename Base::Matrix6Type;
    using Pose3Type      = typename Base::Pose3Type;
    using CoordinateType = typename Base::CoordinateType;
    using TimestampType  = typename Base::TimestampType;
    using Source         = typename Base::Source;

    using Precision [[deprecated]] = typename Base::Precision;
    using Field [[deprecated]]     = typename Base::Field;
    using PrecisionValueType       = typename Base::Precision;
    using PrecisionFieldType       = typename Base::Field;

    /**
     * @brief Define local map odometry location status types
     *
     */
    enum class LocalMapOdometryStatus : uint8_t
    {
        UNKNOWN          = 0x0000,  ///< invalid state
        LOW              = 0x0001,  ///< passthrough RTK/GNSS
        MIDDLE           = 0x0002,  ///< integrated navigation
        LATERALHIGH      = 0x0003,  ///< lateral high precision
        LONGITUDINALHIGH = 0x0004,  ///< longitudinal high precision
    };

    struct MatchingResult
    {
        MatchingResult()
          : link_id{0}
          , lane_id{0}
          , longitudinal_off_start{0}
          , longitudinal_off_end{0}
          , accuracy{0.0f}
          , relative_heading{0}
          , lateral_off_left{0}
          , lateral_off_right{0}
          , lateral_off_middle{0}
          , probobility{0}
        {
        }

        ~MatchingResult() = default;

        template <size_t ALIGN = 4U>
        size_t GetSerializedSize() const noexcept
        {
            return holo::serialization::SerializedSize<ALIGN>(
                link_id, lane_id, longitudinal_off_start, longitudinal_off_end, accuracy, relative_heading,
                lateral_off_left, lateral_off_right, lateral_off_middle, probobility);
        }

        template <typename S>
        void Serialize(S& serializer) const
        {
            serializer << holo::serialization::align << link_id << lane_id << longitudinal_off_start
                       << longitudinal_off_end << accuracy << relative_heading << lateral_off_left << lateral_off_right
                       << lateral_off_middle << probobility << holo::serialization::align;
        }

        template <typename D>
        void Deserialize(D& deserializer)
        {
            deserializer >> holo::serialization::align >> link_id >> lane_id >> longitudinal_off_start >>
                longitudinal_off_end >> accuracy >> relative_heading >> lateral_off_left >> lateral_off_right >>
                lateral_off_middle >> probobility >> holo::serialization::align;
        }

        uint64_t link_id;                 ///< road id
        uint64_t lane_id;                 ///< lane id
        int32_t  longitudinal_off_start;  /// locate path distance between projection point and starting position of
                                          /// lane (unit: cm)
        int32_t longitudinal_off_end;     /// path distance between positioning projection point and lane termination
                                          /// position (unit: cm)
        float32_t accuracy;               ///< standard deviation of longitudinal offset
        int32_t   relative_heading;       /// Angle between car heading and lane heading; value range: [-π, +π],
                                          /// coefficient: 0.00001, unit radian, counterclockwise positive
        int32_t lateral_off_left;         /// distance between registration point and lane line on the left of the lane;
                                          /// (Unit: cm)
        int32_t  lateral_off_right;  ///< distance between registration point and right lane line of the lane (Unit: cm)
        int32_t  lateral_off_middle;  ///< distance between anchor point and lane centerline (unit: cm)
        uint16_t probobility;         ///< global map matching confidence (range: [0, 100])
    };

    /**
     * @brief Default constructor
     */
    LocalMapOdometryT()
      : Base{}
      , status_{LocalMapOdometryStatus::UNKNOWN}
      , vehicle_speed_{0}
      , vehicle_heading_{0}
      , is_matching_results_actived_{false}
      , matching_results_{}
    {
    }

    /**
     * @brief Set local map odometry status
     *
     * @param status local map odometry status
     */
    void SetLocalMapOdometryStatus(LocalMapOdometryStatus status) noexcept
    {
        status_ = status;
    }

    /**
     * @brief Get local map odometry status
     *
     * @return LocalMapOdometryStatus
     */
    LocalMapOdometryStatus GetLocalMapOdometryStatus() const noexcept
    {
        return status_;
    }

    /**
     * @brief Set vehicle speed
     *
     * @param speed
     */
    void SetSpeed(int16_t const speed) noexcept
    {
        vehicle_speed_ = speed;
    }

    /**
     * @brief Get vehicle speed
     *
     * @return int16_t
     */
    int16_t GetSpeed() const noexcept
    {
        return vehicle_speed_;
    }

    /**
     * @brief Set heading
     *
     * @param heading
     */
    void SetHeading(int32_t const heading) noexcept
    {
        vehicle_heading_ = heading;
    }

    /**
     * @brief Get heading
     *
     * @return int32_t
     */
    int32_t GetHeading() const noexcept
    {
        return vehicle_heading_;
    }

    /**
     * @brief Set matching results actived
     *
     * @param actived
     */
    void SetMatchingResultsActived(bool_t const actived) noexcept
    {
        is_matching_results_actived_ = actived;
    }

    /**
     * @brief Get actived matching results status
     *
     * @return bool_t
     */
    bool_t GetMatchingResultsActived() const noexcept
    {
        return is_matching_results_actived_;
    }

    /**
     * @brief Get matching results
     *
     * @return Const reference of holo::container::Vector<MatchingResult, SIZE_VALUE>
     */
    holo::container::Vector<MatchingResult, SIZE_VALUE> const& GetMatchingResults() const noexcept
    {
        return matching_results_;
    }

    /**
     * @brief Get matching results
     *
     * @return reference of holo::container::Vector<MatchingResult, SIZE_VALUE>
     */
    holo::container::Vector<MatchingResult, SIZE_VALUE>& GetMatchingResults() noexcept
    {
        return matching_results_;
    }

    /**
     * @brief Set matching results
     *
     * @param matching_results
     */
    void SetMatchingResults(holo::container::Vector<MatchingResult, SIZE_VALUE> const& matching_results) noexcept
    {
        matching_results_ = matching_results;
    }

    /**
     * @brief Get location covariance
     *
     * @return location covariance
     */
    Vector3Type GetLocationCovariance() const noexcept
    {
        return Vector3Type(Base::GetPoseCovariance()(3, 3), Base::GetPoseCovariance()(4, 4),
                           Base::GetPoseCovariance()(5, 5));
    }

    /**
     * @brief Set location covariance
     *
     * @param location_covariance location covariance
     */
    void SetLocationCovariance(Vector3Type const& location_covariance) noexcept
    {
        Base::GetPoseCovariance()(3, 3) = location_covariance[0];
        Base::GetPoseCovariance()(4, 4) = location_covariance[1];
        Base::GetPoseCovariance()(5, 5) = location_covariance[2];
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
        return Base::template GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint8_t>(status_), vehicle_speed_,
                                                          vehicle_heading_, is_matching_results_actived_) +
               matching_results_.template GetSerializedSize<ALIGN>();
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
        Base::Serialize(serializer);
        serializer << static_cast<uint8_t>(status_) << vehicle_speed_ << vehicle_heading_
                   << is_matching_results_actived_ << matching_results_;
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
        uint8_t status;

        Base::Deserialize(deserializer);
        deserializer >> status >> vehicle_speed_ >> vehicle_heading_ >> is_matching_results_actived_ >>
            matching_results_;

        status_ = static_cast<LocalMapOdometryStatus>(status);
    }

private:
    LocalMapOdometryStatus status_;           ///< positioning state
    int16_t                vehicle_speed_;    ///< vehicle speed, unit: 0.01m/s
    int32_t                vehicle_heading_;  /// heading angle of vehicle itself, unit: 0.00001 radian; Starting due
                                              /// east,anticlockwise is positive
    bool_t is_matching_results_actived_;      ///< whether matching results is actived
    holo::container::Vector<MatchingResult, SIZE_VALUE> matching_results_;  ///< Lane-level location results
};

/**
 * @brief This class defines dr odometry measurement in 3D space. It contains rotation
 * in addition to the odometry base attribute
 *
 * @tparam Scalar the precision type
 */
template <typename Scalar>
class DrOdometryT : public OdometryBaseT<Scalar>
{
public:
    using Base           = OdometryBaseT<Scalar>;
    using QuaternionType = holo::geometry::QuaternionT<Scalar>;
    using Vector3Type    = typename Base::Vector3Type;
    using Vector6Type    = typename Base::Vector6Type;
    using Matrix6Type    = typename Base::Matrix6Type;
    using Pose3Type      = typename Base::Pose3Type;
    using CoordinateType = typename Base::CoordinateType;
    using TimestampType  = typename Base::TimestampType;

    using Precision [[deprecated]] = typename Base::Precision;
    using Field [[deprecated]]     = typename Base::Field;
    using PrecisionValueType       = typename Base::Precision;
    using PrecisionFieldType       = typename Base::Field;

    using Status = typename Base::Status;
    using Source = typename Base::Source;

    /**
     * @brief Default constructor
     */
    DrOdometryT() : Base{}, ground_rotation_{}
    {
    }

    /**
     * @brief Set rotation
     *
     * @param rotation Odometry rotation
     */
    void SetGroundRotation(QuaternionType const& rotation) noexcept
    {
        ground_rotation_ = rotation;
    }

    /**
     * @brief Get rotation relative to the ground
     *
     * @return Const reference of rotation
     */
    QuaternionType const& GetGroundRotation() const noexcept
    {
        return ground_rotation_;
    }

    /**
     * @brief Get rotation relative to the ground
     *
     * @return Reference of rotation
     */
    QuaternionType& GetGroundRotation() noexcept
    {
        return ground_rotation_;
    }

    /**
     * @brief Get location relative to the ground
     *
     * @return location covariance
     */
    Vector3Type GetLocationCovariance() const noexcept
    {
        return Vector3Type(Base::GetPoseCovariance()(3, 3), Base::GetPoseCovariance()(4, 4),
                           Base::GetPoseCovariance()(5, 5));
    }

    /**
     * @brief Set location covariance
     *
     * @param location_covariance location covariance
     */
    void SetLocationCovariance(Vector3Type const& location_covariance) noexcept
    {
        Base::GetPoseCovariance()(3, 3) = location_covariance[0];
        Base::GetPoseCovariance()(4, 4) = location_covariance[1];
        Base::GetPoseCovariance()(5, 5) = location_covariance[2];
    }

    /**
     * @brief Get angular velocity
     *
     * @return Angular velocity which contains (Vroll, Vpitch, Vyaw) in the unit of (rad/s, rad/s, rad/s)
     */
    Vector3Type GetAngularVelocity() const noexcept
    {
        return Vector3Type(Base::GetVelocity()[3], Base::GetVelocity()[4], Base::GetVelocity()[5]);
    }

    /**
     * @brief Set angular velocity
     *
     * @param velocity 6D vector which contains (Vx, Vy, Vz, Vroll, Vpitch, Vyaw) in the unit of (m/s, m/s, m/s, rad/s,
     * rad/s, rad/s)
     */
    void SetAngularVelocity(Vector3Type const& angular_velocity) noexcept
    {
        Base::GetVelocity()[3] = angular_velocity[0];
        Base::GetVelocity()[4] = angular_velocity[1];
        Base::GetVelocity()[5] = angular_velocity[2];
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
        return Base::template GetSerializedSize<ALIGN>() + ground_rotation_.template GetSerializedSize<ALIGN>();
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
        Base::Serialize(serializer);
        serializer << ground_rotation_;
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
        Base::Deserialize(deserializer);
        deserializer >> ground_rotation_;
    }

private:
    QuaternionType ground_rotation_;  ///< attitude relative to the ground
};

/**
 * @}
 *
 */

}  // namespace details
}  // namespace common
}  // namespace holo

#endif
