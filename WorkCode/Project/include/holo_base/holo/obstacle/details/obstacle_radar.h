/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_radar.h
 * @brief This header file defines ObstacleRadarT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-03
 */

#ifndef HOLO_OBSTACLE_DETAILS_OBSTACLE_RADAR_H_
#define HOLO_OBSTACLE_DETAILS_OBSTACLE_RADAR_H_

#include <limits>

#include <holo/common/classification.h>
#include <holo/common/sensor_id.h>
#include <holo/core/types.h>
#include <holo/geometry/box2.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/numerics/vector.h>
#include <holo/obstacle/obstacle_base.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace obstacle
{
namespace details
{
/**
 * @brief Obstacle from radar sensor
 *
 * @tparam T obstacle type, only support float32_t and float64_t
 */
template <typename T>
class ObstacleRadarT : public ObstacleBaseT<T>
{
public:
    using Scalar             = T;
    using Point3Type         = holo::geometry::Point3T<Scalar>;
    using Vector3Type        = holo::numerics::Vector3T<Scalar>;
    using Coordinate         = holo::common::Coordinate;
    using Timestamp          = holo::common::Timestamp;
    using Base               = ObstacleBaseT<T>;
    using SensorIdType       = typename Base::SensorId;
    using ClassificationType = typename Base::Classification;

    using SensorId[[deprecated]]       = typename Base::SensorId;
    using Classification[[deprecated]] = typename Base::Classification;
    /**
     * @brief Constructor
     */
    ObstacleRadarT() noexcept
      : Base()
      , relative_velocity_(Vector3Type::Zero())
      , acceleration_(Vector3Type::Zero())
      , relative_velocity_sigma_(Vector3Type::Zero())
      , acceleration_sigma_(Vector3Type::Zero())
      , shape_(Vector3Type::Zero())
      , position_sigma_(Point3Type::Zero())
      , motion_status_(MotionStatus::UNKNOWN)
      , obstacle_rcs_(static_cast<Scalar>(0.0))
    {
    }

    /**
     * @brief Constructor with parameters
     *
     * @param timestamp Obstacle time stamp
     * @param coord  Obstacle coordinate
     * @param obstacle_id  Obstacle id
     * @param sensor_id  Obstacle sensor id
     * @param classification  Obstacle classification
     * @param obstacle_exist_score  Obstacle existence confidence
     * @param position  Obstacle position
     * @param relative_velocity Obstacle relative velocity
     * @param acceleration  Obstacle acceleration
     * @param position_sigma  Obstacle position standard deviation
     * @param relative_velocity_sigma Obstacle relative velocity standard deviation
     * @param acceleration_sigma Obstacle acceleration standard deviation
     * @param obstacle_rcs Radar cross section property
     * @param shape Obstacle shape in w-h-l order
     * @param motion_status Obstacle motion state
     */
    ObstacleRadarT(const Timestamp& timestamp, const Coordinate coord, const uint32_t obstacle_id,
                   const SensorIdType& sensor_id, const ClassificationType& classification,
                   const float32_t obstacle_exist_score, const Point3Type& position,
                   const Vector3Type& relative_velocity, const Vector3Type& acceleration,
                   const Point3Type& position_sigma, const Vector3Type& relative_velocity_sigma,
                   const Vector3Type& acceleration_sigma, const MotionStatus motion_status, const Vector3Type& shape,
                   const T obstacle_rcs) noexcept
      : Base(timestamp, coord, obstacle_id, sensor_id, classification, obstacle_exist_score, position)
      , relative_velocity_(relative_velocity)
      , acceleration_(acceleration)
      , relative_velocity_sigma_(relative_velocity_sigma)
      , acceleration_sigma_(acceleration_sigma)
      , shape_(shape)
      , position_sigma_(position_sigma)
      , motion_status_(motion_status)
      , obstacle_rcs_(obstacle_rcs)
    {
    }

    /**
     * @brief Copy constructor
     *
     * @param other other obstacle
     */
    ObstacleRadarT(const ObstacleRadarT<T>& other) noexcept
      : Base(other.timestamp_, other.coordinate_, other.obstacle_id_, other.sensor_id_, other.classification_,
             other.obstacle_exist_score_, other.position_)
      , relative_velocity_(other.relative_velocity_)
      , acceleration_(other.acceleration_)
      , relative_velocity_sigma_(other.relative_velocity_sigma_)
      , acceleration_sigma_(other.acceleration_sigma_)
      , shape_(other.shape_)
      , position_sigma_(other.position_sigma_)
      , motion_status_(other.motion_status_)
      , obstacle_rcs_(other.obstacle_rcs_)
    {
    }

    /**
     * @brief Move constructor
     *
     * @param other other obstacle
     */
    ObstacleRadarT(ObstacleRadarT<T>&& other) noexcept
      : Base(other.timestamp_, other.coordinate_, other.obstacle_id_, other.sensor_id_, other.classification_,
             other.obstacle_exist_score_, other.position_)
      , relative_velocity_(std::move(other.relative_velocity_))
      , acceleration_(std::move(other.acceleration_))
      , relative_velocity_sigma_(std::move(other.relative_velocity_sigma_))
      , acceleration_sigma_(std::move(other.acceleration_sigma_))
      , shape_(other.shape_)
      , position_sigma_(std::move(other.position_sigma_))
      , motion_status_(other.motion_status_)
      , obstacle_rcs_(other.obstacle_rcs_)
    {
    }

    /**
     * @brief Copy assignment
     *
     * @param other other obstacle
     * @return new obstacle
     */
    ObstacleRadarT<Scalar>& operator=(const ObstacleRadarT<Scalar>& other) noexcept
    {
        this->timestamp_               = other.timestamp_;
        this->coordinate_              = other.coordinate_;
        this->obstacle_id_             = other.obstacle_id_;
        this->sensor_id_               = other.sensor_id_;
        this->classification_          = other.classification_;
        this->obstacle_exist_score_    = other.obstacle_exist_score_;
        this->position_                = other.position_;
        this->relative_velocity_       = other.relative_velocity_;
        this->acceleration_            = other.acceleration_;
        this->position_sigma_          = other.position_sigma_;
        this->relative_velocity_sigma_ = other.relative_velocity_sigma_;
        this->acceleration_sigma_      = other.acceleration_sigma_;
        this->motion_status_           = other.motion_status_;
        this->shape_                   = other.shape_;
        this->obstacle_rcs_            = other.obstacle_rcs_;

        return *this;
    }

    /**
     * @brief Move assignment
     *
     * @param other other obstacle
     * @return new obstacle
     */
    ObstacleRadarT<Scalar>& operator=(ObstacleRadarT<Scalar>&& other) noexcept
    {
        // avoid self = std::move(self)
        if (this == &other)
        {
            return *this;
        }

        this->timestamp_               = other.timestamp_;
        this->coordinate_              = other.coordinate_;
        this->obstacle_id_             = other.obstacle_id_;
        this->sensor_id_               = other.sensor_id_;
        this->classification_          = other.classification_;
        this->obstacle_exist_score_    = other.obstacle_exist_score_;
        this->position_                = std::move(other.position_);
        this->relative_velocity_       = std::move(other.relative_velocity_);
        this->acceleration_            = std::move(other.acceleration_);
        this->position_sigma_          = std::move(other.position_sigma_);
        this->relative_velocity_sigma_ = std::move(other.relative_velocity_sigma_);
        this->acceleration_sigma_      = std::move(other.acceleration_sigma_);
        this->motion_status_           = other.motion_status_;
        this->shape_                   = other.shape_;
        this->obstacle_rcs_            = other.obstacle_rcs_;

        return *this;
    }

    /**
     * @brief Destructor
     */
    virtual ~ObstacleRadarT() noexcept
    {
    }

    /**
     * @brief Get obstacle relative velocity
     *
     * @return obstacle relative velocity
     */
    const Vector3Type& GetRelativeVelocity() const noexcept
    {
        return relative_velocity_;
    }

    /**
     * @brief Set obstacle relative velocity
     *
     * @param relative_velocity obstacle relative velocity
     */
    void SetRelativeVelocity(const Vector3Type& relative_velocity) noexcept
    {
        this->relative_velocity_ = relative_velocity;
    }

    /**
     * @brief Get obstacle acceleration
     *
     * @return obstacle acceleration
     */
    const Vector3Type& GetAcceleration() const noexcept
    {
        return acceleration_;
    }

    /**
     * @brief Set obstacle acceleration
     *
     * @param acceleration obstacle acceleration
     */
    void SetAcceleration(const Vector3Type& acceleration) noexcept
    {
        this->acceleration_ = acceleration;
    }

    /**
     * @brief Get osbtacle position standard deviation
     *
     * @return osbtacle position standard deviation
     */
    const Point3Type& GetPositionSigma() const noexcept
    {
        return position_sigma_;
    }

    /**
     * @brief Set obstacle position standard deviation
     *
     * @param position_sigma obstacle position standard deviation
     */
    void SetPositionSigma(const Point3Type& position_sigma) noexcept
    {
        this->position_sigma_ = position_sigma;
    }

    /**
     * @brief Get obstacle relative velocity standard deviation
     *
     * @return obstacle relative velocity standard deviation
     */
    const Vector3Type& GetRelativeVelocitySigma() const noexcept
    {
        return relative_velocity_sigma_;
    }

    /**
     * @brief Set obstacle velocity standard deviation
     *
     * @param relative_velocity_sigma obstacle velocity standard deviation
     */
    void SetRelativeVelocitySigma(const Vector3Type& relative_velocity_sigma) noexcept
    {
        this->relative_velocity_sigma_ = relative_velocity_sigma;
    }

    /**
     * @brief Get obstacle acceleration standard deviation
     *
     * @return obstacle acceleration standard deviation
     */
    const Vector3Type& GetAccelerationSigma() const noexcept
    {
        return acceleration_sigma_;
    }

    /**
     * @brief Set obstacle acceleration standard deviation
     *
     * @param acceleration_sigma obstacle acceleration standard deviation
     */
    void SetAccelerationSigma(const Vector3Type& acceleration_sigma) noexcept
    {
        this->acceleration_sigma_ = acceleration_sigma;
    }

    /**
     * @brief Get obstacle length from shape
     *
     * @return obstacle length
     */
    Scalar GetObstacleLength() const noexcept
    {
        return shape_[2];
    }

    /**
     * @brief Get obstacle width from shape
     *
     * @return obstacle width
     */
    Scalar GetObstacleWidth() const noexcept
    {
        return shape_[0];
    }

    /**
     * @brief Get obstacle motion status
     *
     * @return obstacle motion status
     */
    MotionStatus GetMotionStatus() const noexcept
    {
        return motion_status_;
    }

    /**
     * @brief Get obstacle motion status
     *
     * @param motion_status obstacle motion status
     */
    void SetMotionStatus(const MotionStatus motion_status) noexcept
    {
        this->motion_status_ = motion_status;
    }

    /**
     * @brief Get obstacle shape in 3D world
     *
     * @return obstacle shape
     */
    const Vector3Type& GetObstacleShape() const noexcept
    {
        return shape_;
    }

    /**
     * @brief Set obstacle shape in 3D world
     *
     * @param shape shape in 3D world
     */
    void SetObstacleShape(const Vector3Type& shape) noexcept
    {
        this->shape_ = shape;
    }

    /**
     * @brief Get radar cross section
     *
     * @return radar cross section
     */
    Scalar GetObstacleRCS() const noexcept
    {
        return obstacle_rcs_;
    }

    /**
     * @brief Set radar cross section
     *
     * @param obstacle_rcs obstacle radar cross section
     */
    void SetObstacleRCS(const Scalar obstacle_rcs) noexcept
    {
        this->obstacle_rcs_ = obstacle_rcs;
    }

    /**
     * @brief serialize content to string
     *
     * @return serialized string
     */
    virtual std::string ToString() const noexcept override
    {
        std::stringstream ss;
        ss << "ObstacleRadarT: (" << Base::ToString() << ", relative_velocity_: " << this->relative_velocity_
           << ", acceleration_: " << this->acceleration_ << ", position_sigma_: " << this->position_sigma_
           << ", relative_velocity_sigma_: " << this->relative_velocity_sigma_
           << ", acceleration_sigma_: " << this->acceleration_sigma_ << ", obstacle_rcs_: " << this->obstacle_rcs_
           << ", shape_: " << this->shape_ << ", motion_status_: " << static_cast<uint32_t>(this->motion_status_) << ")"
           << std::endl;

        return ss.str();
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
        return Base::template GetSerializedSize<ALIGN>() + relative_velocity_.template GetSerializedSize<ALIGN>() +
               acceleration_.template GetSerializedSize<ALIGN>() +
               relative_velocity_sigma_.template GetSerializedSize<ALIGN>() +
               acceleration_sigma_.template GetSerializedSize<ALIGN>() + shape_.template GetSerializedSize<ALIGN>() +
               position_sigma_.template GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint8_t>(motion_status_), obstacle_rcs_);
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
        Base::Serialize(serializer);
        serializer << relative_velocity_ << acceleration_ << relative_velocity_sigma_ << acceleration_sigma_ << shape_
                   << position_sigma_ << static_cast<uint8_t>(motion_status_) << obstacle_rcs_
                   << holo::serialization::align;
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
        uint8_t cur_motion_status = 0U;
        Base::Deserialize(deserializer);
        deserializer >> relative_velocity_ >> acceleration_ >> relative_velocity_sigma_ >> acceleration_sigma_ >>
            shape_ >> position_sigma_ >> cur_motion_status >> obstacle_rcs_ >> holo::serialization::align;
        motion_status_ = static_cast<MotionStatus>(cur_motion_status);
    }

private:
    Vector3Type  relative_velocity_;
    Vector3Type  acceleration_;
    Vector3Type  relative_velocity_sigma_;
    Vector3Type  acceleration_sigma_;
    Vector3Type  shape_;  // width, height, length
    Point3Type   position_sigma_;
    MotionStatus motion_status_;
    Scalar       obstacle_rcs_;

};  // ObstacleRadarT

}  // namespace details
}  // namespace obstacle
}  // namespace holo
#endif  // !HOLO_OBSTACLE_DETAILS_OBSTACLE_RADAR_H_
