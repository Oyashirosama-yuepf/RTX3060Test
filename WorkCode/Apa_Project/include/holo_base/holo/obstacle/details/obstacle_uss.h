/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_uss.h
 * @brief This header file defines ObstacleUssT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-05
 */

#ifndef HOLO_OBSTACLE_DETAILS_OBSTACLE_USS_H_
#define HOLO_OBSTACLE_DETAILS_OBSTACLE_USS_H_

#include <limits>

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
 * @brief Obstacle from uss sensor
 *
 * @tparam T obstacle type, only support float32_t and float64_t
 */
template <typename T>
class ObstacleUssT : public ObstacleBaseT<T>
{
public:
    using Scalar             = T;
    using Point3Type         = holo::geometry::Point3T<Scalar>;
    using Vector3Type        = holo::numerics::Vector3T<Scalar>;
    using Coordinate         = holo::common::Coordinate;
    using Timestamp          = holo::common::Timestamp;
    using Base               = ObstacleBaseT<Scalar>;
    using SensorIdType       = typename Base::SensorId;
    using ClassificationType = typename Base::Classification;

    using SensorId[[deprecated]]       = typename Base::SensorId;
    using Classification[[deprecated]] = typename Base::Classification;

    /**
     * @brief Default constructor
     */
    ObstacleUssT() noexcept : Base(), position_sigma_(Point3Type::Zero()), fov_(static_cast<Scalar>(0))
    {
    }

    /**
     * @brief Constructor with parameters
     *
     * @param timestamp Obstacle time stamp
     * @param coord Obstacle coordinate
     * @param obstacle_id Obstacle id
     * @param sensor_id Obstacle sensor id
     * @param classification Obstacle classification, for uss, it is UNKNOWN
     * @param obstacle_exist_score Obstacle existence confidence
     * @param position Obstacle position
     * @param position_sigma Obstacle poistion standard deviation
     * @param fov Uss field of view
     */
    ObstacleUssT(const Timestamp& timestamp, const Coordinate coord, const uint32_t obstacle_id,
                 const SensorIdType& sensor_id, const ClassificationType& classification,
                 const float32_t obstacle_exist_score, const Point3Type& position, const Point3Type& position_sigma,
                 const Scalar fov) noexcept
      : Base(timestamp, coord, obstacle_id, sensor_id, classification, obstacle_exist_score, position)
      , position_sigma_(position_sigma)
      , fov_(fov)
    {
    }

    /**
     * @brief Copy constructor
     *
     * @param other other obstacle
     */
    ObstacleUssT(const ObstacleUssT<Scalar>& other) noexcept
      : Base(other.timestamp_, other.coordinate_, other.obstacle_id_, other.sensor_id_, other.classification_,
             other.obstacle_exist_score_, other.position_)
      , position_sigma_(other.position_sigma_)
      , fov_(other.fov_)
    {
    }

    /**
     * @brief Move constructor
     *
     * @param other other obstacle
     */
    ObstacleUssT(ObstacleUssT<Scalar>&& other) noexcept
      : Base(other.timestamp_, other.coordinate_, other.obstacle_id_, other.sensor_id_, other.classification_,
             other.obstacle_exist_score_, other.position_)
      , position_sigma_(std::move(other.position_sigma_))
      , fov_(other.fov_)
    {
    }

    /**
     * @brief Copy assignment
     *
     * @param other other obstacle
     * @return new obstacle
     */
    ObstacleUssT<Scalar>& operator=(const ObstacleUssT<Scalar>& other) noexcept
    {
        this->timestamp_            = other.timestamp_;
        this->coordinate_           = other.coordinate_;
        this->obstacle_id_          = other.obstacle_id_;
        this->sensor_id_            = other.sensor_id_;
        this->classification_       = other.classification_;
        this->obstacle_exist_score_ = other.obstacle_exist_score_;
        this->position_             = other.position_;
        this->position_sigma_       = other.position_sigma_;
        this->fov_                  = other.fov_;

        return *this;
    }

    /**
     * @brief Move assignment
     *
     * @param other other obstacle
     * @return new obstacle
     */
    ObstacleUssT<Scalar>& operator=(ObstacleUssT<Scalar>&& other) noexcept
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
        this->position_sigma_       = std::move(other.position_sigma_);
        this->fov_                  = other.fov_;

        return *this;
    }

    /**
     * @brief Destructor
     */
    virtual ~ObstacleUssT() noexcept
    {
    }

    /**
     * @brief Get obstacle position standard deviation
     *
     * @return obstacle position standard deviation
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
     * @brief Get uss obstacle field of view
     *
     * @return fov_
     */
    Scalar GetFov() const noexcept
    {
        return fov_;
    }

    /**
     * @brief Set uss obstacle field of view
     *
     * @param[in] fov - uss obstacle field of view
     */
    void SetFov(const Scalar fov) noexcept
    {
        this->fov_ = fov;
    }

    /**
     * @brief serialize content to string
     *
     * @return std::string
     */
    virtual std::string ToString() const noexcept override
    {
        std::stringstream ss;
        ss << "ObstacleUssT: (" << obstacle::ObstacleBaseT<T>::ToString()
           << ", position_sigma_: " << this->position_sigma_ << ", fov_: " << this->fov_ << ")" << std::endl;

        return ss.str();
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return Base::template GetSerializedSize<ALIGN>() + position_sigma_.template GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(fov_);
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
        serializer << position_sigma_ << fov_ << holo::serialization::align;
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
        Base::Deserialize(deserializer);
        deserializer >> position_sigma_ >> fov_ >> holo::serialization::align;
    }

private:
    Point3Type position_sigma_;
    Scalar     fov_;
};  // ObstacleUssT

/**
 * @}
 */

}  // namespace details
}  // namespace obstacle
}  // namespace holo

#endif  // !HOLO_OBSTACLE_DETAILS_OBSTACLE_USS_H_
