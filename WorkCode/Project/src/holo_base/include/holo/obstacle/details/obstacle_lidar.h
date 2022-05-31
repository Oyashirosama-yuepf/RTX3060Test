/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_lidar.h
 * @brief This header file defines ObstacleLidarT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-03
 */

#ifndef HOLO_OBSTACLE_DETAILS_OBSTACLE_LIDAR_H_
#define HOLO_OBSTACLE_DETAILS_OBSTACLE_LIDAR_H_

#include <array>
#include <limits>

#include <holo/common/classification.h>
#include <holo/common/sensor_id.h>
#include <holo/core/types.h>
#include <holo/geometry/box3.h>
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
 * @addtogroup obstacle
 *
 * @{
 */

/**
 * @brief Obstacle from lidar sensor
 *
 * @tparam T obstacle type, only support float32_t and float64_t
 */
template <typename T>
class ObstacleLidarT : public ObstacleBaseT<T>
{
public:
    using Scalar             = T;
    using Point3Type         = holo::geometry::Point3T<Scalar>;
    using Vector3Type        = holo::numerics::Vector3T<Scalar>;
    using Coordinate         = holo::common::Coordinate;
    using Timestamp          = holo::common::Timestamp;
    using MotionStatus       = obstacle::MotionStatus;
    using Base               = ObstacleBaseT<Scalar>;
    using SensorIdType       = typename Base::SensorId;
    using ClassificationType = typename Base::Classification;

    using SensorId[[deprecated]]       = typename Base::SensorId;
    using Classification[[deprecated]] = typename Base::Classification;

    /**
     * @brief Default constructor
     */
    ObstacleLidarT() noexcept
      : Base()
      , relative_velocity_(Vector3Type::Zero())
      , acceleration_(Vector3Type::Zero())
      , position_sigma_(Point3Type::Zero())
      , relative_velocity_sigma_(Vector3Type::Zero())
      , acceleration_sigma_(Vector3Type::Zero())
      , motion_status_(MotionStatus::UNKNOWN)
      , bounding_box3d_()
      , num_lidar_points_(0U)
      , num_contour_points_(0U)
    {
    }
    /**
     * @brief Constructor with parameters
     *
     * @param timestamp Obstacle time stamp
     * @param coord Obstacle coordinate
     * @param obstacle_id Obstacle id
     * @param sensor_id Obstacle sensor id
     * @param classification Obstacle classification
     * @param obstacle_exist_score Obstacle existence confidence
     * @param position Obstacle position
     * @param relative_velocity Obstacle relative velocity
     * @param acceleration Obstacle acceleration
     * @param position_sigma Obstacle position standard deviation
     * @param relative_velocity_sigma Obstacle relative velocity standard deviation
     * @param acceleration_sigma Obstacle acceleration standard deviation
     * @param motion_status Obstacle motion state
     * @param bounding_box3 Obstacle 3D bbox in real world
     * @param num_lidar_points Number of lidar laser points in lidar detected obstacle
     * @param num_contour_points Real contour points count in contour points array
     * @param contour_points Array of contour points
     */
    ObstacleLidarT(const Timestamp& timestamp, const Coordinate coord, const uint32_t obstacle_id,
                   const SensorIdType& sensor_id, const ClassificationType& classification,
                   const float32_t obstacle_exist_score, const Point3Type& position,
                   const Vector3Type& relative_velocity, const Vector3Type& acceleration,
                   const Point3Type& position_sigma, const Vector3Type& relative_velocity_sigma,
                   const Vector3Type& acceleration_sigma, const MotionStatus motion_status,
                   const holo::geometry::Box3f& bounding_box3d, const uint32_t num_lidar_points,
                   const uint32_t                                                 num_contour_points,
                   const std::array<Point3Type, OBSTACLE_MAX_NUM_CONTOUR_POINTS>& contour_points) noexcept
      : Base(timestamp, coord, obstacle_id, sensor_id, classification, obstacle_exist_score, position)
      , relative_velocity_(relative_velocity)
      , acceleration_(acceleration)
      , position_sigma_(position_sigma)
      , relative_velocity_sigma_(relative_velocity_sigma)
      , acceleration_sigma_(acceleration_sigma)
      , motion_status_(motion_status)
      , bounding_box3d_(bounding_box3d)
      , num_lidar_points_(num_lidar_points)
      , num_contour_points_(num_contour_points)
      , contour_points_(contour_points)
    {
    }

    /**
     * @brief Copy Constructor
     *
     * @param other other obstacle
     */
    ObstacleLidarT(const ObstacleLidarT<Scalar>& other) noexcept
      : Base(other.timestamp_, other.coordinate_, other.obstacle_id_, other.sensor_id_, other.classification_,
             other.obstacle_exist_score_, other.position_)
      , relative_velocity_(other.relative_velocity_)
      , acceleration_(other.acceleration_)
      , position_sigma_(other.position_sigma_)
      , relative_velocity_sigma_(other.relative_velocity_sigma_)
      , acceleration_sigma_(other.acceleration_sigma_)
      , motion_status_(other.motion_status_)
      , bounding_box3d_(other.bounding_box3d_)
      , num_lidar_points_(other.num_lidar_points_)
      , num_contour_points_(other.num_contour_points_)
      , contour_points_(other.contour_points_)
    {
    }

    /**
     * @brief Move constructor
     *
     * @param other other obstacle
     */
    ObstacleLidarT(ObstacleLidarT<Scalar>&& other) noexcept
      : Base(other.timestamp_, other.coordinate_, other.obstacle_id_, other.sensor_id_, other.classification_,
             other.obstacle_exist_score_, other.position_)
      , relative_velocity_(std::move(other.relative_velocity_))
      , acceleration_(std::move(other.acceleration_))
      , position_sigma_(std::move(other.position_sigma_))
      , relative_velocity_sigma_(std::move(other.relative_velocity_sigma_))
      , acceleration_sigma_(std::move(other.acceleration_sigma_))
      , motion_status_(other.motion_status_)
      , bounding_box3d_(other.bounding_box3d_)
      , num_lidar_points_(other.num_lidar_points_)
      , num_contour_points_(other.num_contour_points_)
      , contour_points_(std::move(other.contour_points_))
    {
    }

    /**
     * @brief Copy assignment
     *
     * @param other other obstacle
     */
    ObstacleLidarT<Scalar>& operator=(const ObstacleLidarT<Scalar>& other) noexcept
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
        this->bounding_box3d_          = other.bounding_box3d_;
        this->num_lidar_points_        = other.num_lidar_points_;
        this->num_contour_points_      = other.num_contour_points_;

        for (size_t i = 0UL; i < num_contour_points_; ++i)
        {
            contour_points_[i] = other.contour_points_[i];
        }

        return *this;
    }

    /**
     * @brief Move assignment
     *
     * @param other other obstacle
     * @return new obstacle
     */
    ObstacleLidarT<Scalar>& operator=(ObstacleLidarT<Scalar>&& other) noexcept
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
        this->bounding_box3d_          = other.bounding_box3d_;
        this->num_lidar_points_        = other.num_lidar_points_;
        this->num_contour_points_      = other.num_contour_points_;
        this->contour_points_          = std::move(other.contour_points_);

        return *this;
    }

    /**
     * @brief Default destructor
     */
    virtual ~ObstacleLidarT() noexcept
    {
    }

public:
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
     * @return obstacle obstacle standard deviation
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
     * @brief Get obstacle bounding box in 3D world
     *
     * @return obstacle bbox 3d
     */
    const holo::geometry::Box3f& GetObstacleBBox3D() const noexcept
    {
        return bounding_box3d_;
    }

    /**
     * @brief Set obstacle bounding box in 3D world
     *
     * @param bounding_box3d bounding box in 3D world
     */
    void SetObstacleBBox3D(const holo::geometry::Box3f& bounding_box3d) noexcept
    {
        this->bounding_box3d_ = bounding_box3d;
    }

    /**
     * @brief Get count of obstacle lidar points
     *
     * @return count of obstacle lidar points
     */
    uint32_t GetNumLidarPoints() const noexcept
    {
        return num_lidar_points_;
    }

    /**
     * @brief Set count of obstacle lidar points
     *
     * @param num_lidar_points count of lidar points
     */
    void SetNumLidarPoints(const uint32_t num_lidar_points) noexcept
    {
        this->num_lidar_points_ = num_lidar_points;
    }

    /**
     * @brief Get count of obstacle contour points
     *
     * @return count of obstacle contour points
     */
    uint32_t GetNumContourPoints() const noexcept
    {
        return num_contour_points_;
    }

    /**
     * @brief Set count of obstacle contour points
     *
     * @param num_contour_points count number of contour points
     */
    void SetNumContourPoints(const uint32_t num_contour_points) noexcept
    {
        this->num_contour_points_ = num_contour_points;
    }

    /**
     * @brief Get obstacle contour points
     *
     * @return obstacle contour points array
     */
    const std::array<Point3Type, OBSTACLE_MAX_NUM_CONTOUR_POINTS>& GetContourPoints() const noexcept
    {
        return contour_points_;
    }

    /**
     * @brief Set obstacle contour points one by one
     *
     * @param contour_points obstacle contour points array
     */
    void SetContourPoints(const std::array<Point3Type, OBSTACLE_MAX_NUM_CONTOUR_POINTS>& contour_points) noexcept
    {
        this->contour_points_ = contour_points;
    }

    /**
     * @brief Set obstacle contour points in efficient way
     *
     * @param contour_points obstacle contour points array
     */
    void SetContourPoints(std::array<Point3Type, OBSTACLE_MAX_NUM_CONTOUR_POINTS>&& contour_points) noexcept
    {
        std::swap(this->contour_points_, contour_points);
    }

    /**
     * @brief serialize content to string
     *
     * @return serialized string
     */
    virtual std::string ToString() const noexcept override
    {
        std::stringstream ss;
        ss << "ObstacleLidarT: (" << Base::ToString() << ", relative_velocity_: " << this->relative_velocity_
           << ", acceleration_: " << this->acceleration_ << ", position_sigma_: " << this->position_sigma_
           << ", relative_velocity_sigma_: " << this->relative_velocity_sigma_
           << ", acceleration_sigma_: " << this->acceleration_sigma_
           << ", motion_status_: " << static_cast<uint32_t>(this->motion_status_)
           << ", bounding_box3d_: " << this->bounding_box3d_.ToString()
           << ", num_lidar_points_: " << this->num_lidar_points_
           << ", num_contour_points_: " << this->num_contour_points_ << ", points: ";
        for (auto pt : this->contour_points_)
        {
            ss << pt << ", ";
        }
        ss << ")" << std::endl;
        return ss.str();
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return Base::template GetSerializedSize<ALIGN>() + relative_velocity_.template GetSerializedSize<ALIGN>() +
               acceleration_.template GetSerializedSize<ALIGN>() + position_sigma_.template GetSerializedSize<ALIGN>() +
               relative_velocity_sigma_.template GetSerializedSize<ALIGN>() +
               acceleration_sigma_.template GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint8_t>(motion_status_)) +
               bounding_box3d_.template GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(num_lidar_points_, num_contour_points_) +
               num_contour_points_ * contour_points_[0].template GetSerializedSize<ALIGN>();
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
        serializer << relative_velocity_ << acceleration_ << position_sigma_ << relative_velocity_sigma_
                   << acceleration_sigma_ << static_cast<uint8_t>(motion_status_) << bounding_box3d_
                   << num_lidar_points_ << num_contour_points_ << holo::serialization::align;
        for (uint32_t i = 0; i < num_contour_points_; i++)
        {
            serializer << contour_points_[i];
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
        uint8_t cur_motion_status = 0U;
        Base::Deserialize(deserializer);
        deserializer >> relative_velocity_ >> acceleration_ >> position_sigma_ >> relative_velocity_sigma_ >>
            acceleration_sigma_ >> cur_motion_status >> bounding_box3d_ >> num_lidar_points_ >> num_contour_points_ >>
            holo::serialization::align;
        for (uint32_t i = 0; i < num_contour_points_; i++)
        {
            deserializer >> contour_points_[i];
        }
        motion_status_ = static_cast<MotionStatus>(cur_motion_status);
    }

private:
    Vector3Type                                             relative_velocity_;
    Vector3Type                                             acceleration_;
    Point3Type                                              position_sigma_;
    Vector3Type                                             relative_velocity_sigma_;
    Vector3Type                                             acceleration_sigma_;
    MotionStatus                                            motion_status_;
    holo::geometry::Box3f                                   bounding_box3d_;
    uint32_t                                                num_lidar_points_;
    uint32_t                                                num_contour_points_;
    std::array<Point3Type, OBSTACLE_MAX_NUM_CONTOUR_POINTS> contour_points_;
};  // ObstacleLidarT

/**
 * @}
 */
}  // namespace details
}  // namespace obstacle
}  // namespace holo

#endif  // !HOLO_OBSTACLE_DETAILS_OBSTACLE_LIDAR_H_
