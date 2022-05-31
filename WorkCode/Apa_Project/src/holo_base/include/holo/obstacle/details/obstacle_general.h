/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_general.h
 * @brief This header file defines ObstacleGeneralT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-03
 */

#ifndef HOLO_OBSTACLE_DETAILS_OBSTACLE_GENERAL_H_
#define HOLO_OBSTACLE_DETAILS_OBSTACLE_GENERAL_H_

#include <holo/common/classification.h>
#include <holo/common/sensor_id.h>
#include <holo/core/types.h>
#include <holo/geometry/box3.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/numerics/vector.h>
#include <holo/obstacle/obstacle_base.h>
#include <holo/serialization/serialization.h>
#include <vector>

namespace holo
{
namespace obstacle
{
namespace details
{
/**
 * @brief Obstacle general type
 *
 * @tparam T obstacle type, only support float32_t and float64_t
 */
template <typename T>
class ObstacleGeneralT : public ObstacleBaseT<T>
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
     * @brief Default constructor
     */
    ObstacleGeneralT() noexcept
      : ObstacleBaseT<T>()
      , relative_velocity_(Vector3Type::Zero())
      , absolute_velocity_(Vector3Type::Zero())
      , acceleration_()
      , cut_in_cut_out_(CutInCutOut::UNKNOWN)
      , motion_status_(MotionStatus::UNKNOWN)
      , num_contour_points_(0U)
      , bounding_box3d_()
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
     * @param absolute_velocity Obstacle absolute velocity
     * @param acceleration Obstacle acceleration
     * @param orientation Obstacle orientation
     * @param motion_status Obstacle motion state
     * @param bounding_box3 Obstacle 3D bbox in real world
     * @param cut_in_cut_out Obstacle prediction state
     * @param num_contour_points Real contour points count in contour points array
     * @param contour_points Array of contour points
     */
    ObstacleGeneralT(const Timestamp& timestamp, const Coordinate coord, const uint32_t obstacle_id,
                     const SensorIdType& sensor_id, const ClassificationType& classification,
                     const float32_t obstacle_exist_score, const Point3Type& position,
                     const Vector3Type& relative_velocity, const Vector3Type& absolute_velocity,
                     const Vector3Type& acceleration, const MotionStatus motion_status,
                     const holo::geometry::Box3f& bounding_box3d, const CutInCutOut cut_in_cut_out,
                     const uint32_t                                                 num_contour_points,
                     const std::array<Point3Type, OBSTACLE_MAX_NUM_CONTOUR_POINTS>& contour_points) noexcept
      : ObstacleBaseT<T>(timestamp, coord, obstacle_id, sensor_id, classification, obstacle_exist_score, position)
      , relative_velocity_(relative_velocity)
      , absolute_velocity_(absolute_velocity)
      , acceleration_(acceleration)
      , cut_in_cut_out_(cut_in_cut_out)
      , motion_status_(motion_status)
      , num_contour_points_(num_contour_points)
      , bounding_box3d_(bounding_box3d)
      , contour_points_(contour_points)
    {
    }

    /**
     * @brief Copy constructor
     *
     * @param other other obstacle
     */
    ObstacleGeneralT(const ObstacleGeneralT<T>& other) noexcept
      : ObstacleBaseT<T>(other.timestamp_, other.coordinate_, other.obstacle_id_, other.sensor_id_,
                         other.classification_, other.obstacle_exist_score_, other.position_)
      , relative_velocity_(other.relative_velocity_)
      , absolute_velocity_(other.absolute_velocity_)
      , acceleration_(other.acceleration_)
      , cut_in_cut_out_(other.cut_in_cut_out_)
      , motion_status_(other.motion_status_)
      , num_contour_points_(other.num_contour_points_)
      , bounding_box3d_(other.bounding_box3d_)
      , contour_points_(other.contour_points_)
    {
    }

    /**
     * @brief Move constructor
     *
     * @param other other obstacle
     */
    ObstacleGeneralT(ObstacleGeneralT<T>&& other) noexcept
      : ObstacleBaseT<T>(other.timestamp_, other.coordinate_, other.obstacle_id_, other.sensor_id_,
                         other.classification_, other.obstacle_exist_score_, other.position_)
      , relative_velocity_(std::move(other.relative_velocity_))
      , absolute_velocity_(std::move(other.absolute_velocity_))
      , acceleration_(std::move(other.acceleration_))
      , cut_in_cut_out_(other.cut_in_cut_out_)
      , motion_status_(other.motion_status_)
      , num_contour_points_(other.num_contour_points_)
      , bounding_box3d_(other.bounding_box3d_)
      , contour_points_(std::move(other.contour_points_))
    {
    }
    /**
     * @brief Copy assignment
     *
     * @param other other obstacle.
     * @return new obstacle
     */
    ObstacleGeneralT<T>& operator=(const ObstacleGeneralT<T>& other) noexcept
    {
        this->timestamp_            = other.timestamp_;
        this->coordinate_           = other.coordinate_;
        this->obstacle_id_          = other.obstacle_id_;
        this->sensor_id_            = other.sensor_id_;
        this->classification_       = other.classification_;
        this->obstacle_exist_score_ = other.obstacle_exist_score_;
        this->position_             = other.position_;
        this->relative_velocity_    = other.relative_velocity_;
        this->absolute_velocity_    = other.absolute_velocity_;
        this->acceleration_         = other.acceleration_;
        this->bounding_box3d_       = other.bounding_box3d_;
        this->cut_in_cut_out_       = other.cut_in_cut_out_;
        this->motion_status_        = other.motion_status_;
        this->num_contour_points_   = other.num_contour_points_;

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
    ObstacleGeneralT<T>& operator=(ObstacleGeneralT<T>&& other) noexcept
    {
        // avoid self = std::move(self)
        if (this == &other)
        {
            return *this;
        }

        this->timestamp_            = other.timestamp_;
        this->coordinate_           = other.coordinate_;
        this->obstacle_id_          = other.obstacle_id_;
        this->sensor_id_            = other.sensor_id_;
        this->classification_       = other.classification_;
        this->obstacle_exist_score_ = other.obstacle_exist_score_;
        this->position_             = std::move(other.position_);
        this->relative_velocity_    = std::move(other.relative_velocity_);
        this->absolute_velocity_    = std::move(other.absolute_velocity_);
        this->acceleration_         = std::move(other.acceleration_);
        this->bounding_box3d_       = other.bounding_box3d_;
        this->cut_in_cut_out_       = other.cut_in_cut_out_;
        this->motion_status_        = other.motion_status_;
        this->num_contour_points_   = other.num_contour_points_;
        this->contour_points_       = std::move(other.contour_points_);

        return *this;
    }
    /**
     * @brief Destructor
     */
    virtual ~ObstacleGeneralT() noexcept
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
     * @brief Get obstacle absolute velocity
     *
     * @return obstacle absolute velocity
     */
    const Vector3Type& GetAbsoluteVelocity() const noexcept
    {
        return absolute_velocity_;
    }

    /**
     * @brief Set obstacle relative velocity
     *
     * @param absolute_velocity obstacle absolute velocity
     */
    void SetAbsoluteVelocity(const Vector3Type& absolute_velocity) noexcept
    {
        this->absolute_velocity_ = absolute_velocity;
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
     * @brief Get obstacle motion status
     *
     * @return obstalce motion status
     */
    MotionStatus GetMotionStatus() const noexcept
    {
        return motion_status_;
    }

    /**
     * @brief Set obstacle motion status
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
     * @return obstacle bbox3d
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
     * @brief Get obstacle prediction information
     *
     * @return obstacle cut in cut out information
     */
    CutInCutOut GetCutInCutOut() const noexcept
    {
        return cut_in_cut_out_;
    }

    /**
     * @brief Set obstacle prediction information
     *
     * @param cut_in_cut_out obstacle cut in cut out information
     */
    void SetCutInCutOut(const CutInCutOut cut_in_cut_out) noexcept
    {
        this->cut_in_cut_out_ = cut_in_cut_out;
    }

    /**
     * @brief Get count of obstacle contour points
     *
     * @return size of contour points of obstacle
     */
    uint32_t GetNumContourPoints() const noexcept
    {
        return num_contour_points_;
    }

    /**
     * @brief Set count of obstacle contour points
     *
     * @param num_contour_points number of contour points
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
     * @brief Set obstacle contour points array
     *
     * @param contour_points obstacle contour points
     */
    void SetContourPoints(const std::array<Point3Type, OBSTACLE_MAX_NUM_CONTOUR_POINTS>& contour_points) noexcept
    {
        this->contour_points_ = contour_points;
    }

    /**
     * @brief Set obstacle contour points in efficient way
     *
     * @param contour_points obstacle contour points
     */
    void SetContourPoints(std::array<Point3Type, OBSTACLE_MAX_NUM_CONTOUR_POINTS>&& contour_points) noexcept
    {
        std::swap(this->contour_points_, contour_points);
    }

    /**
     * @brief Serialize content to string
     *
     * @return serialized string
     */
    virtual std::string ToString() const noexcept override
    {
        std::stringstream ss;

        ss << "ObstacleGenerator: (" << ObstacleBaseT<T>::ToString()
           << ", relative_velocity_: " << this->relative_velocity_
           << ", absolute_velocity_: " << this->absolute_velocity_ << ", acceleration_: " << this->acceleration_
           << ", motion_status_: " << static_cast<uint32_t>(this->motion_status_)
           << ", bounding_box3d_: " << this->bounding_box3d_.ToString()
           << ", cut_in_cut_out_: " << static_cast<uint32_t>(this->cut_in_cut_out_)
           << ", num_contour_points_: " << this->num_contour_points_ << ", points: ";
        for (auto pt : this->contour_points_)
        {
            ss << pt << ", ";
        }
        ss << ")" << std::endl;

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
               absolute_velocity_.template GetSerializedSize<ALIGN>() +
               acceleration_.template GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint8_t>(cut_in_cut_out_),
                                                          static_cast<uint8_t>(motion_status_), num_contour_points_) +
               bounding_box3d_.GetSerializedSize<ALIGN>() +
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
        ObstacleBaseT<T>::Serialize(serializer);
        serializer << relative_velocity_ << absolute_velocity_ << acceleration_ << static_cast<uint8_t>(cut_in_cut_out_)
                   << static_cast<uint8_t>(motion_status_) << num_contour_points_ << bounding_box3d_;
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
        uint8_t cur_motion_status = 0U, cur_cut_in_cut_out = 0U;
        ObstacleBaseT<T>::Deserialize(deserializer);
        deserializer >> relative_velocity_ >> absolute_velocity_ >> acceleration_ >> cur_cut_in_cut_out >>
            cur_motion_status >> num_contour_points_ >> bounding_box3d_;
        for (uint32_t i = 0; i < num_contour_points_; i++)
        {
            deserializer >> contour_points_[i];
        }

        motion_status_  = static_cast<MotionStatus>(cur_motion_status);
        cut_in_cut_out_ = static_cast<CutInCutOut>(cur_cut_in_cut_out);
    }

private:
    Vector3Type                                             relative_velocity_;
    Vector3Type                                             absolute_velocity_;
    Vector3Type                                             acceleration_;
    CutInCutOut                                             cut_in_cut_out_;
    MotionStatus                                            motion_status_;
    uint32_t                                                num_contour_points_;
    holo::geometry::Box3f                                   bounding_box3d_;
    std::array<Point3Type, OBSTACLE_MAX_NUM_CONTOUR_POINTS> contour_points_;
};

}  // namespace details
}  // namespace obstacle
}  // namespace holo

#endif
